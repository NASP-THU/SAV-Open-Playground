#!/usr/bin/python3
# -*-coding:utf-8 -*-
"""
@File    :   script_consts.py
@Time    :   2024/04/11
@Version :   0.1
@Desc    :   The script_consts.py has constants for the script_builder
"""

REP_KEY_IP_VERSION = "IP_VERSION"
REP_KEY_MY_AS = "MY_AS"
REP_KEY_PEER_ID = "PEER_ID"
DEFAULT_FIB_THRESHOLD = 300
DEFAULT_ORIGINAL_BIRD = False
REP_KEY_BGPONLY = "opbgp"
REP_KEY_BGPRPDP = "opsavbgp"
REP_KEY_SAV = "opsav"
BIRD_BASIC = """
ipv4 table master4;
ipv6 table master6;
protocol device {
  scan time 60;
  interface "eth_*";
};
protocol kernel {
  scan time 60;
  ipv4 {
    export all;
    import all;
  };
  learn;
};
protocol kernel {
  scan time 60;
  ipv6 {
    export all;
    import all;
  };
  learn;
};
protocol direct {
  ipv4;
  interface "eth_*";
};
protocol static {
  ipv4 {
    export all;
    import all;
  };
};
protocol static {
  ipv6 {
    export all;
    import all;
  };
};
template bgp basic {
  local as MY_AS;
  long lived graceful restart on;
  debug all;
  enable extended messages;
};
template bgp opbgp from basic {
  ipv4 {
    import all;
    import table on;
    export all;
  };
};
template bgp opsav from basic {
  rpdp4 {
    import none;
    export none;
  };
};
template bgp opsavbgp from basic {
  rpdp4 {
    import none;
    export none;
  };
  ipv4 {
    export all;
    import all;
    import table on;
  };
};
"""
NO_EXPORT_STR = """  ipv4 {
    import all;
    export filter noexport_PEER_ID;
    import table on;
  };
  ipv6 {
    import all;
    export filter noexport_PEER_ID;
    import table on;
  };
"""