# -*- coding: utf-8 -*-
"""
-------------------------------------------------
   File Name:     access_control_list
   Description :
   date:          2023/12/27
-------------------------------------------------
   Change Activity:
                   2023/12/27:
-------------------------------------------------
"""
import os
from common import run_cmd, get_host_interface_list

CURRENT_DIR = os.path.dirname(os.path.realpath(__file__))

class AccessControlListManager:
    def huawei_acl_generator(self, acl_sav_rule):
        run_cmd(cmd=f"cat /dev/null > {CURRENT_DIR}/huawei_acl_rule.txt")
        run_cmd(cmd=f'echo "system-view" >> {CURRENT_DIR}/huawei_acl_rule.txt')
        for iface, prefix_set in acl_sav_rule.items():
            run_cmd(                cmd=f'echo "acl name sav_{iface}" >> {CURRENT_DIR}/huawei_acl_rule.txt'            )
            for prefix in prefix_set:
                run_cmd(
                    command=f'echo "rule deny {prefix} 0.0.0.255" >> {CURRENT_DIR}/huawei_acl_rule.txt')
            run_cmd(
                command=f'echo "quit" >> {CURRENT_DIR}/huawei_acl_rule.txt')
            run_cmd(
                command=f'echo "interface Ethernet {iface}" >> {CURRENT_DIR}/huawei_acl_rule.txt')
            run_cmd(
                command=f'echo acl sav_{iface} inbound >> {CURRENT_DIR}/huawei_acl_rule.txt')
            run_cmd(
                command=f'echo "quit" >> {CURRENT_DIR}/huawei_acl_rule.txt')
        run_cmd(
            command=f'echo "save" >> {CURRENT_DIR}/huawei_acl_rule.txt')

    def h3c_acl_generator(self, acl_sav_rule):
        run_cmd(
            command=f'cat /dev/null > {CURRENT_DIR}/h3c_acl_rule.txt')
        run_cmd(
            command=f'echo "system-view" >> {CURRENT_DIR}/h3c_acl_rule.txt')
        for iface, prefix_set in acl_sav_rule.items():
            run_cmd(
                command=f'echo "acl name sav_{iface}" >> {CURRENT_DIR}/h3c_acl_rule.txt')
            for prefix in prefix_set:
                run_cmd(
                    command=f'echo "rule deny {prefix} 0.0.0.255" >> {CURRENT_DIR}/h3c_acl_rule.txt')
            run_cmd(
                command=f'echo "quit" >> {CURRENT_DIR}/h3c_acl_rule.txt')
            run_cmd(
                command=f'echo "interface Ethernet {iface}" >> {CURRENT_DIR}/h3c_acl_rule.txt')
            run_cmd(
                command=f'echo acl sav_{iface} inbound >> {CURRENT_DIR}/h3c_acl_rule.txt')
            run_cmd(
                command=f'echo "quit" >> {CURRENT_DIR}/h3c_acl_rule.txt')
        run_cmd(
            command=f'echo "save" >> {CURRENT_DIR}/h3c_acl_rule.txt')

    def acl_generator(self, rules):
        interface_set = set(get_host_interface_list())
        sav_rule = {}
        for rule in list(rules.values()):
            prefix, interface = str(rule["prefix"].ip), rule["interface_name"]
            if interface == "*":
                continue
            if prefix not in sav_rule.keys():
                sav_rule[prefix] = {interface}
            else:
                sav_rule[prefix].add(interface)
        for key, value in sav_rule.items():
            sav_rule[key] = interface_set - value
        acl_sav_rule = {}
        for prefix, iface_set in sav_rule.items():
            for iface in iface_set:
                if iface not in acl_sav_rule:
                    acl_sav_rule[iface] = {prefix}
                else:
                    acl_sav_rule[iface].add(prefix)
        # acl rule generator
        self.huawei_acl_generator(acl_sav_rule=acl_sav_rule)
        self.h3c_acl_generator(acl_sav_rule=acl_sav_rule)
