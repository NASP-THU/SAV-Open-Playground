import random
import json
import sys
import datetime
import time


def gen(ratio, method, sav_prefix_num, prefix, pkt_num):
    match method:
        case "dsav":
            sav_sample = {
                "as_path": "2,1,0,0,13,28",
                "as_path_len": 6,
                "is_interior": 1,
                "next_hop": "4,10,0,0,2",
                "nlri_len": 0,
                "protocol_name": "savbgp_34224_3356",
                "sav_nlri": "",
                "sav_origin": "0,0,133,176",
                "sav_scope": "1,1,0,0,13,28",
                "withdraws": "0,0",
                "is_native_bgp": 0,
                "msg_type": "dsav"
            }
            for i in range(sav_prefix_num):
                sav_sample["sav_nlri"] += f"24,{prefix.replace('.',',')},{i+1},"
                sav_sample["nlri_len"] += 4
            sav_sample["sav_nlri"] = sav_sample["sav_nlri"][:-1]
        case "quic":
            sav_sample = {
                "msg": {
                    "src": "10.0.0.1", "dst": "10.0.0.2",
                    "msg_type": "origin",
                    "is_interior": True,
                    "as4_session": True,
                    "protocol_name": "savbgp_34224_3356",
                    "is_native_bgp": 0,
                    "sav_origin": "34224",
                    "sav_scope": [[3356]], "sav_path": [34224], "sav_nlri": []
                },
                "msg_type": "quic"
            }
            for i in range(nlri_num):
                sav_sample["msg"]["sav_nlri"].append(f"{prefix}.{i+1}.0/24")
        case "grpc":
            sav_sample = {
                "msg": {
                    "src": "10.0.0.1", "dst": "10.0.0.2",
                    "msg_type": "origin",
                    "is_interior": True, "as4_session": True,
                    "protocol_name": "savbgp_34224_3356",
                    "is_native_bgp": 0,
                    "sav_origin": "34224",
                    "sav_scope": [[3356]], "sav_path": [34224], "sav_nlri": []
                },
                "msg_type": "grpc",
            }
            for i in range(nlri_num):
                sav_sample["msg"]["sav_nlri"].append(f"{prefix}.{i+1}.0/24")
    bgp_sample = {
        "as_path": "2,1,0,0,13,28",
        "as_path_len": 6,
        "is_interior": 1,
        "next_hop": "4,10,0,0,2",
        "nlri_len": 0,
        "protocol_name": "savbgp_34224_3356",
        "bgp_nlri": "",
        "sav_origin": "0,0,133,176",
        "sav_scope": "1,1,0,0,13,28",
        "withdraws": "0,0",
        "is_native_bgp": 1,
        "msg_type": "bgp"
    }
    bgp_num = int(pkt_num * (1-ratio))
    sav_num = pkt_num - bgp_num
    sav_pkts = []
    bgp_pkts = []
    for _ in range(bgp_num):
        bgp_pkts.append(json.dumps(bgp_sample))
    for _ in range(sav_num):
        sav_pkts.append(json.dumps(sav_sample))
    all_pkts = bgp_pkts + sav_pkts
    random.shuffle(all_pkts)
    with open(r"/root/savop-dev/sav_agent/perf_test.json", "w") as f:
        f.write("\n".join(all_pkts))
    print(
        f"ratio: {ratio}, nlri_len: {nlri_num}, native_bgp_len: {bgp_num}, sav_len: {sav_num}")


def send(p=r"test_send.json"):
    f = open(p, "r")
    pkts = f.readlines()
    f.close()
    for p in pkts:
        print(p)


def check_sav():
    f = open(r"/root/savop/logs/server.log", "r")
    lines = f.readlines()
    f.close()
    test_begin = False
    start = None
    end = None
    accu = 0
    num = 0
    pkt_start = None
    for l in lines:
        if "PERF-TEST: TEST BEGIN" in l:
            test_begin = True
        elif (test_begin) and ("PERF-TEST: got " in l):
            pkt_start = float(l.split(" ")[-1])
            if start is None:
                start = pkt_start
        elif (test_begin) and ("finished PROCESSING" in l):
            end = float(l.split(" ")[-1])
            accu += (end-pkt_start)
            pkt_start = None
            num = int(l.split("(")[1].split(")")[0])
    return start, end, num, accu


def str_to_dt(s):
    print(s)
    re = datetime.datetime.strptime(s, '%Y-%m-%d %H:%M:%S.%f')
    re = re.timestamp()
    print(re)
    return re


def int_to_dt(l):
    re = l.split(' ')[-1]
    re = int(re)/1000
    return re


def check_bgp():
    f = open(r"/root/savop/logs/bird.log", "r")
    lines = f.readlines()
    f.close()
    test_begin = False
    start = None
    end = None
    num = 0
    begin_pkt = None
    accum = 0
    a = 0
    b = 0
    # row_number = 0
    for l in lines:
        # row_number += 1
        if "<DBG> cmd test_log received" in l:
            test_begin = True
        if not test_begin:
            continue
        if "BGP UPDATE PROCESSING STARTED" in l:
            temp = int_to_dt(l)
            a += 1
            if start is None:
                start = temp
            begin_pkt = temp
        if "BGP UPDATE PROCESSING FINISHED" in l:
            end = int_to_dt(l)
            accum += (end - begin_pkt)
            begin_pkt = None
            b += 1
            if test_begin:
                num += 1
    return start, end, num, accum


def check_dsav():
    f = open(r"/root/savop/logs/bird.log", "r")
    lines = f.readlines()
    f.close()
    test_begin = False
    start = None
    end = None
    num = 0
    begin_pkt = None
    accum = 0
    a = 0
    b = 0
    good_pkt = False
    # row_number = 0
    for l in lines:
        # row_number += 1
        if "<DBG> cmd test_log received" in l:
            test_begin = True
        if not test_begin:
            continue
        if "SAV UPDATE PROCESSING STARTED" in l:
            temp = int_to_dt(l)
            a += 1
            if start is None:
                start = temp
            begin_pkt = temp
        if "SAV UPDATE PROCESSING FINISHED" in l:
            end = int_to_dt(l)
            accum += (end - begin_pkt)
            begin_pkt = None
            b += 1
            if test_begin:
                num += 1
    return start, end, num, accum


def check():
    bgp_start, bgp_end, bgp_num, bgp_accu = check_bgp()
    # print(bgp_start, bgp_end, bgp_num,bgp_accu)
    sav_start, sav_end, sav_num, sav_accu = check_sav()
    # print(sav_start, sav_end, sav_num,sav_accu)
    # Dsav_start, Dsav_end, Dsav_num,Dsav_accu = check_dsav()
    # print(Dsav_start, Dsav_end, Dsav_num,Dsav_accu)
    if bgp_start == None:
        bgp_start = sav_start
    if sav_start == None:
        sav_start = bgp_start
    if bgp_end == None:
        bgp_end = sav_end
    if sav_end == None:
        sav_end = bgp_end
    start = min(bgp_start, sav_start)
    end = max(bgp_end, sav_end)
    if bgp_num == None:
        bgp_num = 0
    if sav_num == None:
        sav_num = 0
    duration = end - start
    msg = f"processed {bgp_num} bgp pkts in {bgp_end - bgp_start} processing time:{bgp_accu}\n"
    msg += f"processed {sav_num} sav pkts in {sav_end - sav_start} processing time:{sav_accu}\n"
    msg += f"processed {bgp_num+sav_num} pkts in {duration} start: {start} end: {end}"
    return bgp_num+sav_num, msg


if __name__ == "__main__":
    if len(sys.argv) > 2:
        ratio = float(sys.argv[1])/100
        msg_type = sys.argv[2]
        pkt_num = int(sys.argv[3])
        nlri_num = int(sys.argv[4])
        prefix = sys.argv[5]
        gen(ratio, msg_type, nlri_num, prefix, pkt_num)

    else:
        given_total_num = int(sys.argv[1])
        while True:
            try:
                total_num, msg = check()
                if total_num >= given_total_num:
                    print(msg)
                    exit(0)
            except Exception as e:
                print(e)
                continue
            time.sleep(0.5)
