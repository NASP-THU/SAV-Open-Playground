#!/usr/bin/python3
# -*-coding:utf-8 -*-
"""
@File    :   kill-all.py
@Time    :   2023/12/29
@Version :   0.1
@Desc    :   
- kill all pid
- remove all containers
"""

import os
cmds = [
    "ps -aux | grep 'sav_control_master'|awk '{print $2}' | xargs kill -9",
    "ps -aux | grep 'sav_control_host'|awk '{print $2}' | xargs kill -9",
    "docker ps -a | awk '{print $1}' | xargs docker rm -f",
    "ps -aux | grep 'dstat -f -m'|awk '{print $2}' | xargs kill -9",
    "ps -aux | grep 'docker stat'|awk '{print $2}' | xargs kill -9",
    "docker image prune -f --filter \"dangling=true\""
]
for cmd in cmds:
    os.system(cmd)
# for i in range(246):
#     cmd = f"docker rm -f r{i+1}"
#     if i+1==80:
#         continue
#     os.system(cmd)
