#!/usr/bin/python3
# -*-coding:utf-8 -*-
"""
@File    :   sav_common.py
@Time    :   2023/01/17 16:04:22
@Version :   0.1

@Desc    :   The sav_common.py contains shared functions and classes
"""

import os
import subprocess
import requests
from common.sav_data_structure import *
import pickle
from pyroute2 import IPDB
import time
import logging
import logging.handlers
import copy


def get_logger(file_name) -> logging.Logger:
    """
    get logger function for all modules
    """
    maxsize = 1024 * 1024 * 50
    backup_num = 1
    # level = logging.WARN
    level = logging.DEBUG
    logger = logging.getLogger(__name__)
    logger.setLevel(level)
    log_file = os.path.dirname(os.path.abspath(__file__))
    log_file = os.path.dirname(os.path.dirname(log_file))
    log_file = os.path.join(log_file, "logs", f"{file_name}.log")
    with open(log_file, "w") as f:
        pass
    handler = logging.handlers.RotatingFileHandler(
        log_file, maxBytes=maxsize, backupCount=backup_num
    )
    handler.setLevel(level)

    formatter = logging.Formatter(
        "[%(asctime)s]  [%(filename)s:%(lineno)s-%(funcName)s] [%(levelname)s] %(message)s"
    )
    formatter.converter = time.gmtime
    handler.setFormatter(formatter)

    logger.addHandler(handler)
    return logger


class RPDPPeer:
    def __init__(self, asn, port, ip, is_as4) -> None:
        self.asn = asn
        self.port = port
        self.ip = ip
        self.is_as4 = is_as4

    def __str__(self) -> str:
        return f"{self.asn},{self.ip}:{self.ip}"


RPDP_PEER_TYPE = RPDPPeer


def _trim_table(table):
    """
    remove the first and last line
    """
    table = table.split("\n")
    while "" in table:
        table.remove("")
    table_name = table.pop(0)[1:-1]
    parsed_rows = {}
    stack = []
    for line in table:
        level = 0
        while line.startswith("\t"):
            level += 1
            line = line[1:]
        while len(stack) > level:
            stack.pop()
        if level == 0:
            stack = [line]
        else:
            parent = stack[-1]
            if parent not in parsed_rows:
                parsed_rows[parent] = []
            parsed_rows[parent].append(line)
            stack.append(line)
    return table_name, parsed_rows


def parse_bird_table(table, logger=None):
    """
    return table_name(string) and parsed_rows(dict)
    """
    table_name, table_content = _trim_table(table)
    new_table_content = {}
    for k, v in table_content.items():
        try:
            p = netaddr.IPNetwork(k.split(" ")[0])
        except Exception as e:
            logger.debug(k.split(" ")[0])
            logger.exception(e)
            new_table_content[k] = v
            continue
        # get info from k
        while "  " in k:
            k = k.replace("  ", " ")
        k = k.split("[")
        prefix_type = k[0].split(" ")[1]
        k = k[1]
        link_name = k.split(" ")[0]
        time_str = k.split(" ")[1][:-1]
        k = k.split("]")[1].strip()
        k = k.split(" ")
        unknown_value = k[0]
        metric = int(k[1][1:-1])
        if not p in new_table_content:
            new_table_content[p] = {
                "srcs": [],
                "origin_ases": set(),
                "origin_ids": set(),
            }
        this_src = {
            "type": prefix_type,
            "link_name": link_name,
            "time_str": time_str,
            "unknown_value": unknown_value,
            "metric": metric,
            "unprocessed_lines": [],
        }
        for l in v:
            try:
                sub_k, sub_v = translate_bird_out(l)
                if sub_k == "via":
                    this_src["interface_name"] = sub_v.split("on ")[-1]
                    this_src[sub_k] = netaddr.IPAddress(sub_v.split(" ")[0])
                    new_table_content[p]["origin_ids"].add(this_src[sub_k])
                elif sub_k in ["type", "origin"]:
                    this_src[sub_k] = sub_v
                elif sub_k == "as_path":
                    while "  " in sub_v:
                        sub_v = sub_v.replace("  ", " ")
                    sub_v = sub_v.strip().split(" ")
                    while "" in sub_v:
                        sub_v.remove("")
                    this_src[sub_k] = list(map(int, sub_v))
                    this_src[sub_k].reverse()
                    if not len(this_src[sub_k]) == 0:
                        new_table_content[p]["origin_ases"].add(this_src[sub_k][0])
                elif sub_k in ["next_hop", "origin_router_id"]:
                    this_src[sub_k] = netaddr.IPAddress(sub_v)
                    if sub_k == "origin_router_id":
                        new_table_content[p]["origin_ids"].add(this_src[sub_k])
                elif sub_k == "metric":
                    if not int(sub_v) == this_src["metric"]:
                        logger.warning(f"metric not match:{sub_v}:{this_src['metric']}")
                elif sub_k == "only_to_customer":
                    this_src[sub_k] = int(sub_v.strip())
                elif sub_k == "cluster_list":
                    sub_v = sub_v.split(" ")
                    while "" in sub_v:
                        sub_v.remove("")
                    this_src[sub_k] = list(map(netaddr.IPAddress, sub_v))
                else:
                    this_src["unprocessed_lines"].append(l)
                    logger.warning(f"unprocessed line:[{sub_k}:{sub_v}]")
            except Exception as e:
                logger.debug(l)
                logger.exception(e)
                this_src["unprocessed_lines"].append(l)
                logger.debug(l)
                continue
        new_table_content[p]["srcs"].append(this_src)
    for k, v in new_table_content.items():
        new_table_content[k]["origin_ases"] = list(v["origin_ases"])
        new_table_content[k]["origin_ids"] = list(v["origin_ids"])
        if len(v["origin_ases"]) == 0:
            # logger.debug(f"no origin as for {k}")
            # new_table_content[p]["prefix_type"] = MULT_HOMING_FULL
            new_table_content[p]["prefix_type"] = SOLE_HOMING
        elif len(v["origin_ases"]) == 1:
            new_table_content[p]["prefix_type"] = SOLE_HOMING
        elif len(v["origin_ases"]) > 1:
            new_table_content[p]["prefix_type"] = MULT_HOMING_PARTIAL

    return table_name, new_table_content


def check_msg(key, msg, meta=SAV_META):
    """check msg before sending to ensure the msg can be processed properly"""
    if key not in SAV_META:
        raise KeyError(f"key {key} not in SAV_META")
    keys_types_check(msg, meta[key])


def sav_rule_diff(old_rules: dict, new_rules: dict) -> tuple[dict, set]:
    """
    return add_dict and del_set
    """
    add_dict = {}
    del_set = set()
    for r_k, r in new_rules.items():
        if r_k not in old_rules:
            add_dict[r_k] = r
    for r_k, r in old_rules.items():
        if r_k not in new_rules:
            del_set.add(r_k)
    return add_dict, del_set


def run_cmd(
    cmd,
    expected_return_code=0,
    capture_output=True,
    timeout=None,
    shell=True,
    encoding="utf-8",
):
    ret = subprocess.run(
        cmd,
        shell=shell,
        capture_output=capture_output,
        encoding=encoding,
        timeout=timeout,
    )
    if ret.returncode != expected_return_code:
        print(ret)
    return ret


def get_host_interface_list() -> list[str]:
    """
    return a list of 'clean' interface names
    """
    command = "ip link|grep -v 'link' | grep -v -E 'docker0|lo' | awk -F: '{ print $2 }' | sed 's/ //g'"
    std_out = run_cmd(command).stdout
    result = std_out.split("\n")[:-1]
    result = list(map(lambda x: x.split("@")[0], result))
    result = [i for i in result if len(i) != 0]
    # TODO demo filter
    # only include interfaces start with eth_, for demo
    result = [i for i in result if i.startswith("eth_")]
    return result


def get_next_hop(target_ip):
    """
    find next hop for the given ip using ip route get
    """
    hex_hop = run_cmd(f"ip route get {target_ip}").stdout.split(" ")
    for i in range(len(hex_hop)):
        if hex_hop[i] == "via":
            return netaddr.IPAddress(hex_hop[i + 1])


def tell_str_is_interior(input_str):
    """
    tell the given str contains as_number or ip
    return True if AS number detected.
    return False if ip detected.
    """
    if len(input_str) == 0:
        raise ValueError("empty string")
    if "," in input_str:
        input_str = input_str.split(",")
    else:
        input_str = [input_str]
    while "" in input_str:
        input_str.remove("")
    try:
        map(int, input_str)
        return True
    except ValueError:
        pass
    try:
        map(netaddr.IPAddress, input_str)
        return False
    except BaseException:
        raise ValueError("invalid string: " + input_str)


def ln(list_of_interface):
    """
    return a a list of protocol_names
    """
    result = []
    for i in list_of_interface:
        result.append(i["protocol_name"])
    return result


def get_kv_match(list_of_dict, key, value):
    result = []
    for data_dict in list_of_dict:
        if data_dict[key] == value:
            result.append(data_dict)
    return result


def ipv4_str_to_hex(ip_str):
    """
    convert ipv4 to hex
    :param ipv4: ipv4 address
    :return: hex value list (u8)
    """
    return ip_str.split(".")


def scope_to_hex_str(scope, is_inter, is_as4=True):
    temp = [str(len(scope))]
    if is_inter:
        for path in scope:
            temp.append(str(len(path)))
            temp += path2hex(path, is_as4)
        return ",".join(temp)

    for path in scope:
        temp.append(str(len(path)))
        for ipv4 in path:
            temp += ipv4_str_to_hex(ipv4)
    return ",".join(temp)


def get_ifa_by_ip(ip: str) -> str:
    """
    return interface name by ip
    """
    with IPDB() as ipdb:
        for interface in ipdb.interfaces.values():
            for ip_info in interface.ipaddr:
                if ip_info[0] == ip:
                    return interface.ifname
    raise ValueError(f"unable to get interface for {ip}")


def get_all_interfaces():
    """
    return a list of all interface names
    """
    ret = []
    with IPDB() as ipdb:
        for interface in ipdb.interfaces:
            # TODO SAV filter
            if str(interface).startswith("eth"):
                ret.append(interface)
    return ret


def read_json(path_to_json):
    with open(path_to_json, "r", encoding="utf-8") as json_file:
        return json.loads(json_file.read())


def json_w(path_to_json, json_obj):
    with open(path_to_json, "w", encoding="utf-8") as json_file:
        json_file.write(json.dumps(json_obj, indent=4, sort_keys=True))


class SavApp:
    """
    SavApp class helps receive and send massage using links
    SavAgent do not detect the link status,
    it is the app"s responsibility to manipulate the link status.
    one app can manage multiple links
    app manage the links status by inserting update msg
    """

    def __init__(self, agent, app_id, logger):
        self.logger = logger
        self.status = True
        self.app_id = app_id
        self.agent = agent

    def is_up(self):
        return self.status is True

    def send_msg(self, msg):
        raise NotImplementedError

    def recv_msg(self):
        raise NotImplementedError

    def check_status(self):
        raise NotImplementedError

    def generate_sav_rules(self, fib_adds, fib_dels, old_rules):
        """
        generate sav rules based on the current information
        """
        raise NotImplementedError

    def put_link_up(self, link_name, link_type):
        # this msg may incur creating of new link, so we need to know the type
        msg = {
            "msg_type": "link_state_change",
            "source_app": self.app_id,
            "source_link": link_name,
            "link_type": link_type,
            "msg": True,
            "pkt_rec_dt": time.time(),
        }
        self.agent.put_msg(msg)

    def set_link_type(self, link_name, link_type):
        # this msg may incur creating of new link, so we need to know the type
        msg = {
            "msg_type": "set_link_type",
            "source_app": self.app_id,
            "source_link": link_name,
            "msg": link_type,
            "pkt_rec_dt": time.time(),
        }
        self.agent.put_msg(msg)

    def put_link_down(self, link_name):
        msg = {
            "msg_type": "link_state_change",
            "source_app": self.app_id,
            "source_link": link_name,
            "msg": False,
            "pkt_rec_dt": time.time(),
        }
        self.agent.put_msg(msg)

    # def _bird_cmd(self, cmd):
    #     return birdc_cmd(self.logger, cmd)


def birdc_cmd(logger, cmd, log_err=True):
    """
    execute bird command and return the output in std
    """
    t0 = time.time()
    cmd = f"/usr/local/sbin/birdc {cmd}"
    try:
        # logger.debug("birdc_cmd")
        if "call_agent" in cmd:
            proc = subprocess.Popen(
                ["/usr/local/sbin/birdc", "call_agent"],
                stdout=subprocess.PIPE,
                stdin=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
            proc.stdin.write("\n".encode("utf-8"))
            proc.stdin.flush()
            proc.wait()
            out = proc.stdout.read().decode()
        else:
            cmd = cmd.split(" ")
            proc = subprocess.Popen(
                cmd,
                stdout=subprocess.PIPE,
                stdin=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
            out = proc.stdout.read()
            out = out.decode()
        proc.kill()
    except Exception as e:
        logger.debug(cmd)
        logger.debug(type(e))
        logger.error(e)
    t = time.time() - t0
    if t > TIMEIT_THRESHOLD:
        logger.debug(cmd)
        logger.warning(f"TIMEIT {time.time() - t0:.4f} seconds")
    temp = out.split("\n")[0]
    temp = temp.split()
    if len(temp) < 2:
        if log_err:
            logger.debug(cmd)
            logger.debug(proc.stderr.read())
            logger.error(temp)
            logger.error("length to short")
        return None
    if not (temp[0] == "BIRD" and temp[-1] == "ready."):
        logger.error(f"birdc execute error:{out}")
        return None
    out = "\n".join(out.split("\n")[1:])
    t = time.time() - t0
    # if t> TIMEIT_THRESHOLD:
    #     logger.warning(f"TIMEIT {time.time()-t0:.4f} seconds")
    return out


def birdc_show_protocols(logger):
    """
    execute show protocols
    """
    data = birdc_cmd(logger, cmd="show protocols")
    if data is None:
        return {}
    data = data.split("\n")
    while "" in data:
        data.remove("")
    return data


def birdc_get_protos_by(logger, key, value):
    data = birdc_show_protocols(logger)
    title = data.pop(0).split()
    result = []
    for row in data:
        temp = row.split()
        a = {}
        for i in range(min(len(title), len(temp))):
            a[title[i]] = temp[i]
        if key not in a:
            logger.error(f"key {key} missing in:{list(a.keys())}")
            return result
        if a[key] == value:
            result.append(a)
    return result


def birdc_get_import(logger, protocol_name, channel_name="ipv4"):
    """
    using birdc show all import to get import table
    return a list
    """
    default = {}
    cmd = f"show route all import table {protocol_name}.{channel_name}"
    # logger.debug(cmd)
    data = birdc_cmd(logger, cmd)
    # logger.debug(data)
    if data is None:
        return default
    if data.startswith("No import table in channel"):
        logger.warning(data[:-1])
        logger.debug(cmd)
        return default
    if data is None:
        return default
    data = data.split("Table")
    while "" in data:
        data.remove("")
    for table in data:
        table_name, table_data = parse_bird_table(table, logger)
        if table_name == "import":
            # logger.debug(table_data)
            return table_data
        else:
            logger.warning(f"table_name:{table_name}:{table_data}")
    return default


def get_p_by_asn(asn, roa, aspa):
    """
    return a a dict(key is prefix,value is origin as) of unique prefix that could be used as src in packet from this as using aspa an roa info
    customer and peer is considered
    """
    result = {}
    for p in roa[asn]:
        result[p] = asn
    added = True
    ass = [asn]
    while added:
        added = False
        for customer_asn, providers in aspa.items():
            if element_exist_check(ass, providers):
                if customer_asn not in ass:
                    ass.append(customer_asn)
                    for p in roa[customer_asn]:
                        if p not in result:
                            result[p] = customer_asn
                    added = True
    return result


def element_exist_check(a, b):
    """
    return True if any element in a exists in b
    """
    for e in a:
        if e in b:
            return True
    return False


# class Link():
#     """
#     the intermedia between two sav agents
#     """
# def
# __init__(self,link_name,source_app,remote_addr,remote_as,local_addr,local_as,interface,type):


def get_agent_app_msg(link_meta, msg_meta, logger):
    """
    message between agent and app
    """
    # self.as4_session = link_meta["as4_session"]
    # self.protocol_name = link_meta["protocol_name"]
    if not isinstance(msg_meta["is_interior"], bool):
        raise ValueError("is_interior type error,   ")
    if not isinstance(link_meta["src"], str):
        raise ValueError("src type error, should be a string")
    if not isinstance(link_meta["dst"], str):
        raise ValueError("dst type error, should be a string")
    if not isinstance(msg_meta["scope"], list):
        raise ValueError("scope type error, should be a list")
    if not isinstance(msg_meta["nlri"], list):
        raise ValueError("nlri type error, should be a list")
    if not isinstance(msg_meta["path"], list):
        logger.error(msg_meta["path"])
        logger.error(type(msg_meta["path"]))
        raise ValueError("path type error, should be a list")
    if not isinstance(msg_meta["origin"], str):
        raise ValueError("origin type error")
    if msg_meta["is_interior"]:
        if not tell_str_is_interior(msg_meta["path"]) or not tell_str_is_interior(
            msg_meta["origin"]
        ):
            raise ValueError("interior msg should have interior path and origin")
    for path in msg_meta["scope"]:
        if not tell_str_is_interior(path):
            raise ValueError("interior msg should have interior scope")


def str_to_scope(input_str):
    temp = decode_csv(input_str)
    result = []
    while len(temp) > 0:
        scope_len = int(temp.pop(0))
        for _ in range(scope_len):
            path_len = int(temp.pop(0))
            path = []
            for _ in range(path_len):
                path.append(temp.pop(0))
            result.append(path)
    return result


def sav_timer(logger):
    def timer_func(func):
        # This function shows the execution time of
        # the function object passed
        def wrap_func(*args, **kwargs):
            t1 = time.time()
            result = func(*args, **kwargs)
            t2 = time.time()
            logger.debug(f"Function {func.__name__!r} executed in {(t2 - t1):.4f}s")
            return result

        return wrap_func

    return timer_func
