/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_CF_OBJ_CONF_CF_PARSE_TAB_H_INCLUDED
# define YY_CF_OBJ_CONF_CF_PARSE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int cf_debug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    QUIT = 258,                    /* QUIT  */
    EXIT = 259,                    /* EXIT  */
    HELP = 260,                    /* HELP  */
    END = 261,                     /* END  */
    CLI_MARKER = 262,              /* CLI_MARKER  */
    INVALID_TOKEN = 263,           /* INVALID_TOKEN  */
    ELSECOL = 264,                 /* ELSECOL  */
    DDOT = 265,                    /* DDOT  */
    GEQ = 266,                     /* GEQ  */
    LEQ = 267,                     /* LEQ  */
    NEQ = 268,                     /* NEQ  */
    AND = 269,                     /* AND  */
    OR = 270,                      /* OR  */
    PO = 271,                      /* PO  */
    PC = 272,                      /* PC  */
    NUM = 273,                     /* NUM  */
    ENUM = 274,                    /* ENUM  */
    IP4 = 275,                     /* IP4  */
    IP6 = 276,                     /* IP6  */
    VPN_RD = 277,                  /* VPN_RD  */
    CF_SYM_KNOWN = 278,            /* CF_SYM_KNOWN  */
    CF_SYM_UNDEFINED = 279,        /* CF_SYM_UNDEFINED  */
    TEXT = 280,                    /* TEXT  */
    BYTESTRING = 281,              /* BYTESTRING  */
    PREFIX_DUMMY = 282,            /* PREFIX_DUMMY  */
    NMA = 283,                     /* NMA  */
    DEFINE = 284,                  /* DEFINE  */
    ON = 285,                      /* ON  */
    OFF = 286,                     /* OFF  */
    YES = 287,                     /* YES  */
    NO = 288,                      /* NO  */
    S = 289,                       /* S  */
    MS = 290,                      /* MS  */
    US = 291,                      /* US  */
    PORT = 292,                    /* PORT  */
    VPN = 293,                     /* VPN  */
    MPLS = 294,                    /* MPLS  */
    FROM = 295,                    /* FROM  */
    FLOW4 = 296,                   /* FLOW4  */
    FLOW6 = 297,                   /* FLOW6  */
    DST = 298,                     /* DST  */
    SRC = 299,                     /* SRC  */
    PROTO = 300,                   /* PROTO  */
    NEXT = 301,                    /* NEXT  */
    HEADER = 302,                  /* HEADER  */
    DPORT = 303,                   /* DPORT  */
    SPORT = 304,                   /* SPORT  */
    ICMP = 305,                    /* ICMP  */
    TYPE = 306,                    /* TYPE  */
    CODE = 307,                    /* CODE  */
    TCP = 308,                     /* TCP  */
    FLAGS = 309,                   /* FLAGS  */
    LENGTH = 310,                  /* LENGTH  */
    DSCP = 311,                    /* DSCP  */
    DONT_FRAGMENT = 312,           /* DONT_FRAGMENT  */
    IS_FRAGMENT = 313,             /* IS_FRAGMENT  */
    FIRST_FRAGMENT = 314,          /* FIRST_FRAGMENT  */
    LAST_FRAGMENT = 315,           /* LAST_FRAGMENT  */
    FRAGMENT = 316,                /* FRAGMENT  */
    LABEL = 317,                   /* LABEL  */
    OFFSET = 318,                  /* OFFSET  */
    FUNCTION = 319,                /* FUNCTION  */
    PRINT = 320,                   /* PRINT  */
    PRINTN = 321,                  /* PRINTN  */
    UNSET = 322,                   /* UNSET  */
    RETURN = 323,                  /* RETURN  */
    ACCEPT = 324,                  /* ACCEPT  */
    REJECT = 325,                  /* REJECT  */
    ERROR = 326,                   /* ERROR  */
    INT = 327,                     /* INT  */
    BOOL = 328,                    /* BOOL  */
    IP = 329,                      /* IP  */
    PREFIX = 330,                  /* PREFIX  */
    RD = 331,                      /* RD  */
    PAIR = 332,                    /* PAIR  */
    QUAD = 333,                    /* QUAD  */
    EC = 334,                      /* EC  */
    LC = 335,                      /* LC  */
    SET = 336,                     /* SET  */
    STRING = 337,                  /* STRING  */
    BGPMASK = 338,                 /* BGPMASK  */
    BGPPATH = 339,                 /* BGPPATH  */
    CLIST = 340,                   /* CLIST  */
    ECLIST = 341,                  /* ECLIST  */
    LCLIST = 342,                  /* LCLIST  */
    IF = 343,                      /* IF  */
    THEN = 344,                    /* THEN  */
    ELSE = 345,                    /* ELSE  */
    CASE = 346,                    /* CASE  */
    FOR = 347,                     /* FOR  */
    IN = 348,                      /* IN  */
    DO = 349,                      /* DO  */
    TRUE = 350,                    /* TRUE  */
    FALSE = 351,                   /* FALSE  */
    RT = 352,                      /* RT  */
    RO = 353,                      /* RO  */
    UNKNOWN = 354,                 /* UNKNOWN  */
    GENERIC = 355,                 /* GENERIC  */
    GW = 356,                      /* GW  */
    NET = 357,                     /* NET  */
    MASK = 358,                    /* MASK  */
    SOURCE = 359,                  /* SOURCE  */
    SCOPE = 360,                   /* SCOPE  */
    DEST = 361,                    /* DEST  */
    IFNAME = 362,                  /* IFNAME  */
    IFINDEX = 363,                 /* IFINDEX  */
    WEIGHT = 364,                  /* WEIGHT  */
    GW_MPLS = 365,                 /* GW_MPLS  */
    PREFERENCE = 366,              /* PREFERENCE  */
    ROA_CHECK = 367,               /* ROA_CHECK  */
    ASN = 368,                     /* ASN  */
    IS_V4 = 369,                   /* IS_V4  */
    IS_V6 = 370,                   /* IS_V6  */
    LEN = 371,                     /* LEN  */
    MAXLEN = 372,                  /* MAXLEN  */
    DATA = 373,                    /* DATA  */
    DATA1 = 374,                   /* DATA1  */
    DATA2 = 375,                   /* DATA2  */
    DEFINED = 376,                 /* DEFINED  */
    ADD = 377,                     /* ADD  */
    DELETE = 378,                  /* DELETE  */
    CONTAINS = 379,                /* CONTAINS  */
    RESET = 380,                   /* RESET  */
    PREPEND = 381,                 /* PREPEND  */
    FIRST = 382,                   /* FIRST  */
    LAST = 383,                    /* LAST  */
    LAST_NONAGGREGATED = 384,      /* LAST_NONAGGREGATED  */
    MATCH = 385,                   /* MATCH  */
    MIN = 386,                     /* MIN  */
    MAX = 387,                     /* MAX  */
    EMPTY = 388,                   /* EMPTY  */
    FILTER = 389,                  /* FILTER  */
    WHERE = 390,                   /* WHERE  */
    EVAL = 391,                    /* EVAL  */
    ATTRIBUTE = 392,               /* ATTRIBUTE  */
    BT_ASSERT = 393,               /* BT_ASSERT  */
    BT_TEST_SUITE = 394,           /* BT_TEST_SUITE  */
    BT_CHECK_ASSIGN = 395,         /* BT_CHECK_ASSIGN  */
    BT_TEST_SAME = 396,            /* BT_TEST_SAME  */
    FORMAT = 397,                  /* FORMAT  */
    ROUTER = 398,                  /* ROUTER  */
    ID = 399,                      /* ID  */
    HOSTNAME = 400,                /* HOSTNAME  */
    PROTOCOL = 401,                /* PROTOCOL  */
    TEMPLATE = 402,                /* TEMPLATE  */
    DISABLED = 403,                /* DISABLED  */
    DEBUG = 404,                   /* DEBUG  */
    ALL = 405,                     /* ALL  */
    DIRECT = 406,                  /* DIRECT  */
    INTERFACE = 407,               /* INTERFACE  */
    IMPORT = 408,                  /* IMPORT  */
    EXPORT = 409,                  /* EXPORT  */
    NONE = 410,                    /* NONE  */
    VRF = 411,                     /* VRF  */
    DEFAULT = 412,                 /* DEFAULT  */
    TABLE = 413,                   /* TABLE  */
    STATES = 414,                  /* STATES  */
    ROUTES = 415,                  /* ROUTES  */
    FILTERS = 416,                 /* FILTERS  */
    IPV4 = 417,                    /* IPV4  */
    IPV6 = 418,                    /* IPV6  */
    VPN4 = 419,                    /* VPN4  */
    VPN6 = 420,                    /* VPN6  */
    ROA4 = 421,                    /* ROA4  */
    ROA6 = 422,                    /* ROA6  */
    SADR = 423,                    /* SADR  */
    RECEIVE = 424,                 /* RECEIVE  */
    LIMIT = 425,                   /* LIMIT  */
    ACTION = 426,                  /* ACTION  */
    WARN = 427,                    /* WARN  */
    BLOCK = 428,                   /* BLOCK  */
    RESTART = 429,                 /* RESTART  */
    DISABLE = 430,                 /* DISABLE  */
    KEEP = 431,                    /* KEEP  */
    FILTERED = 432,                /* FILTERED  */
    RPKI = 433,                    /* RPKI  */
    PASSWORD = 434,                /* PASSWORD  */
    KEY = 435,                     /* KEY  */
    PASSIVE = 436,                 /* PASSIVE  */
    TO = 437,                      /* TO  */
    EVENTS = 438,                  /* EVENTS  */
    PACKETS = 439,                 /* PACKETS  */
    PROTOCOLS = 440,               /* PROTOCOLS  */
    CHANNELS = 441,                /* CHANNELS  */
    INTERFACES = 442,              /* INTERFACES  */
    ALGORITHM = 443,               /* ALGORITHM  */
    KEYED = 444,                   /* KEYED  */
    HMAC = 445,                    /* HMAC  */
    MD5 = 446,                     /* MD5  */
    SHA1 = 447,                    /* SHA1  */
    SHA256 = 448,                  /* SHA256  */
    SHA384 = 449,                  /* SHA384  */
    SHA512 = 450,                  /* SHA512  */
    BLAKE2S128 = 451,              /* BLAKE2S128  */
    BLAKE2S256 = 452,              /* BLAKE2S256  */
    BLAKE2B256 = 453,              /* BLAKE2B256  */
    BLAKE2B512 = 454,              /* BLAKE2B512  */
    PRIMARY = 455,                 /* PRIMARY  */
    STATS = 456,                   /* STATS  */
    COUNT = 457,                   /* COUNT  */
    BY = 458,                      /* BY  */
    COMMANDS = 459,                /* COMMANDS  */
    PREEXPORT = 460,               /* PREEXPORT  */
    NOEXPORT = 461,                /* NOEXPORT  */
    EXPORTED = 462,                /* EXPORTED  */
    GENERATE = 463,                /* GENERATE  */
    BGP = 464,                     /* BGP  */
    PASSWORDS = 465,               /* PASSWORDS  */
    DESCRIPTION = 466,             /* DESCRIPTION  */
    RELOAD = 467,                  /* RELOAD  */
    OUT = 468,                     /* OUT  */
    MRTDUMP = 469,                 /* MRTDUMP  */
    MESSAGES = 470,                /* MESSAGES  */
    RESTRICT = 471,                /* RESTRICT  */
    MEMORY = 472,                  /* MEMORY  */
    IGP_METRIC = 473,              /* IGP_METRIC  */
    CLASS = 474,                   /* CLASS  */
    TIMEFORMAT = 475,              /* TIMEFORMAT  */
    ISO = 476,                     /* ISO  */
    SHORT = 477,                   /* SHORT  */
    LONG = 478,                    /* LONG  */
    ROUTE = 479,                   /* ROUTE  */
    BASE = 480,                    /* BASE  */
    LOG = 481,                     /* LOG  */
    GRACEFUL = 482,                /* GRACEFUL  */
    WAIT = 483,                    /* WAIT  */
    FLUSH = 484,                   /* FLUSH  */
    AS = 485,                      /* AS  */
    IDLE = 486,                    /* IDLE  */
    RX = 487,                      /* RX  */
    TX = 488,                      /* TX  */
    INTERVAL = 489,                /* INTERVAL  */
    MULTIPLIER = 490,              /* MULTIPLIER  */
    CHECK = 491,                   /* CHECK  */
    LINK = 492,                    /* LINK  */
    SORTED = 493,                  /* SORTED  */
    TRIE = 494,                    /* TRIE  */
    SETTLE = 495,                  /* SETTLE  */
    TIME = 496,                    /* TIME  */
    GC = 497,                      /* GC  */
    THRESHOLD = 498,               /* THRESHOLD  */
    PERIOD = 499,                  /* PERIOD  */
    IPV4_MC = 500,                 /* IPV4_MC  */
    IPV4_MPLS = 501,               /* IPV4_MPLS  */
    IPV6_MC = 502,                 /* IPV6_MC  */
    IPV6_MPLS = 503,               /* IPV6_MPLS  */
    IPV6_SADR = 504,               /* IPV6_SADR  */
    VPN4_MC = 505,                 /* VPN4_MC  */
    VPN4_MPLS = 506,               /* VPN4_MPLS  */
    VPN6_MC = 507,                 /* VPN6_MC  */
    VPN6_MPLS = 508,               /* VPN6_MPLS  */
    PRI = 509,                     /* PRI  */
    SEC = 510,                     /* SEC  */
    SHOW = 511,                    /* SHOW  */
    STATUS = 512,                  /* STATUS  */
    CALL_AGENT = 513,              /* CALL_AGENT  */
    TEST_LOG = 514,                /* TEST_LOG  */
    TEST_SEND = 515,               /* TEST_SEND  */
    SUMMARY = 516,                 /* SUMMARY  */
    SYMBOLS = 517,                 /* SYMBOLS  */
    DUMP = 518,                    /* DUMP  */
    RESOURCES = 519,               /* RESOURCES  */
    SOCKETS = 520,                 /* SOCKETS  */
    NEIGHBORS = 521,               /* NEIGHBORS  */
    ATTRIBUTES = 522,              /* ATTRIBUTES  */
    ECHO = 523,                    /* ECHO  */
    ENABLE = 524,                  /* ENABLE  */
    BABEL = 525,                   /* BABEL  */
    METRIC = 526,                  /* METRIC  */
    RXCOST = 527,                  /* RXCOST  */
    HELLO = 528,                   /* HELLO  */
    UPDATE = 529,                  /* UPDATE  */
    WIRED = 530,                   /* WIRED  */
    WIRELESS = 531,                /* WIRELESS  */
    BUFFER = 532,                  /* BUFFER  */
    PRIORITY = 533,                /* PRIORITY  */
    HOP = 534,                     /* HOP  */
    BABEL_METRIC = 535,            /* BABEL_METRIC  */
    ENTRIES = 536,                 /* ENTRIES  */
    RANDOMIZE = 537,               /* RANDOMIZE  */
    MAC = 538,                     /* MAC  */
    PERMISSIVE = 539,              /* PERMISSIVE  */
    BFD = 540,                     /* BFD  */
    MULTIHOP = 541,                /* MULTIHOP  */
    NEIGHBOR = 542,                /* NEIGHBOR  */
    DEV = 543,                     /* DEV  */
    LOCAL = 544,                   /* LOCAL  */
    AUTHENTICATION = 545,          /* AUTHENTICATION  */
    SIMPLE = 546,                  /* SIMPLE  */
    METICULOUS = 547,              /* METICULOUS  */
    STRICT = 548,                  /* STRICT  */
    BIND = 549,                    /* BIND  */
    SESSIONS = 550,                /* SESSIONS  */
    HOLD = 551,                    /* HOLD  */
    CONNECT = 552,                 /* CONNECT  */
    RETRY = 553,                   /* RETRY  */
    KEEPALIVE = 554,               /* KEEPALIVE  */
    STARTUP = 555,                 /* STARTUP  */
    VIA = 556,                     /* VIA  */
    SELF = 557,                    /* SELF  */
    PATH = 558,                    /* PATH  */
    START = 559,                   /* START  */
    DELAY = 560,                   /* DELAY  */
    FORGET = 561,                  /* FORGET  */
    AFTER = 562,                   /* AFTER  */
    BGP_PATH = 563,                /* BGP_PATH  */
    BGP_LOCAL_PREF = 564,          /* BGP_LOCAL_PREF  */
    BGP_MED = 565,                 /* BGP_MED  */
    BGP_ORIGIN = 566,              /* BGP_ORIGIN  */
    BGP_NEXT_HOP = 567,            /* BGP_NEXT_HOP  */
    BGP_ATOMIC_AGGR = 568,         /* BGP_ATOMIC_AGGR  */
    BGP_AGGREGATOR = 569,          /* BGP_AGGREGATOR  */
    BGP_COMMUNITY = 570,           /* BGP_COMMUNITY  */
    BGP_EXT_COMMUNITY = 571,       /* BGP_EXT_COMMUNITY  */
    BGP_LARGE_COMMUNITY = 572,     /* BGP_LARGE_COMMUNITY  */
    ADDRESS = 573,                 /* ADDRESS  */
    RR = 574,                      /* RR  */
    RS = 575,                      /* RS  */
    CLIENT = 576,                  /* CLIENT  */
    CLUSTER = 577,                 /* CLUSTER  */
    AS4 = 578,                     /* AS4  */
    ADVERTISE = 579,               /* ADVERTISE  */
    CAPABILITIES = 580,            /* CAPABILITIES  */
    PREFER = 581,                  /* PREFER  */
    OLDER = 582,                   /* OLDER  */
    MISSING = 583,                 /* MISSING  */
    LLADDR = 584,                  /* LLADDR  */
    DROP = 585,                    /* DROP  */
    IGNORE = 586,                  /* IGNORE  */
    REFRESH = 587,                 /* REFRESH  */
    INTERPRET = 588,               /* INTERPRET  */
    COMMUNITIES = 589,             /* COMMUNITIES  */
    BGP_ORIGINATOR_ID = 590,       /* BGP_ORIGINATOR_ID  */
    BGP_CLUSTER_LIST = 591,        /* BGP_CLUSTER_LIST  */
    IGP = 592,                     /* IGP  */
    GATEWAY = 593,                 /* GATEWAY  */
    RECURSIVE = 594,               /* RECURSIVE  */
    MED = 595,                     /* MED  */
    TTL = 596,                     /* TTL  */
    SECURITY = 597,                /* SECURITY  */
    DETERMINISTIC = 598,           /* DETERMINISTIC  */
    SECONDARY = 599,               /* SECONDARY  */
    ALLOW = 600,                   /* ALLOW  */
    PATHS = 601,                   /* PATHS  */
    AWARE = 602,                   /* AWARE  */
    EXTENDED = 603,                /* EXTENDED  */
    SETKEY = 604,                  /* SETKEY  */
    CONFEDERATION = 605,           /* CONFEDERATION  */
    MEMBER = 606,                  /* MEMBER  */
    MULTICAST = 607,               /* MULTICAST  */
    LIVED = 608,                   /* LIVED  */
    STALE = 609,                   /* STALE  */
    IBGP = 610,                    /* IBGP  */
    EBGP = 611,                    /* EBGP  */
    MANDATORY = 612,               /* MANDATORY  */
    INTERNAL = 613,                /* INTERNAL  */
    EXTERNAL = 614,                /* EXTERNAL  */
    SETS = 615,                    /* SETS  */
    DYNAMIC = 616,                 /* DYNAMIC  */
    RANGE = 617,                   /* RANGE  */
    NAME = 618,                    /* NAME  */
    DIGITS = 619,                  /* DIGITS  */
    BGP_AIGP = 620,                /* BGP_AIGP  */
    AIGP = 621,                    /* AIGP  */
    ORIGINATE = 622,               /* ORIGINATE  */
    COST = 623,                    /* COST  */
    ENFORCE = 624,                 /* ENFORCE  */
    FREE = 625,                    /* FREE  */
    VALIDATE = 626,                /* VALIDATE  */
    ROLE = 627,                    /* ROLE  */
    ROLES = 628,                   /* ROLES  */
    PEER = 629,                    /* PEER  */
    PROVIDER = 630,                /* PROVIDER  */
    CUSTOMER = 631,                /* CUSTOMER  */
    RS_SERVER = 632,               /* RS_SERVER  */
    RS_CLIENT = 633,               /* RS_CLIENT  */
    REQUIRE = 634,                 /* REQUIRE  */
    BGP_OTC = 635,                 /* BGP_OTC  */
    GLOBAL = 636,                  /* GLOBAL  */
    RPDP4 = 637,                   /* RPDP4  */
    RPDP6 = 638,                   /* RPDP6  */
    CEASE = 639,                   /* CEASE  */
    HIT = 640,                     /* HIT  */
    ADMINISTRATIVE = 641,          /* ADMINISTRATIVE  */
    SHUTDOWN = 642,                /* SHUTDOWN  */
    CONFIGURATION = 643,           /* CONFIGURATION  */
    CHANGE = 644,                  /* CHANGE  */
    DECONFIGURED = 645,            /* DECONFIGURED  */
    CONNECTION = 646,              /* CONNECTION  */
    REJECTED = 647,                /* REJECTED  */
    COLLISION = 648,               /* COLLISION  */
    OF = 649,                      /* OF  */
    MRT = 650,                     /* MRT  */
    FILENAME = 651,                /* FILENAME  */
    ALWAYS = 652,                  /* ALWAYS  */
    OSPF = 653,                    /* OSPF  */
    V2 = 654,                      /* V2  */
    V3 = 655,                      /* V3  */
    OSPF_METRIC1 = 656,            /* OSPF_METRIC1  */
    OSPF_METRIC2 = 657,            /* OSPF_METRIC2  */
    OSPF_TAG = 658,                /* OSPF_TAG  */
    OSPF_ROUTER_ID = 659,          /* OSPF_ROUTER_ID  */
    AREA = 660,                    /* AREA  */
    RFC1583COMPAT = 661,           /* RFC1583COMPAT  */
    STUB = 662,                    /* STUB  */
    TICK = 663,                    /* TICK  */
    COST2 = 664,                   /* COST2  */
    RETRANSMIT = 665,              /* RETRANSMIT  */
    TRANSMIT = 666,                /* TRANSMIT  */
    DEAD = 667,                    /* DEAD  */
    BROADCAST = 668,               /* BROADCAST  */
    BCAST = 669,                   /* BCAST  */
    NONBROADCAST = 670,            /* NONBROADCAST  */
    NBMA = 671,                    /* NBMA  */
    POINTOPOINT = 672,             /* POINTOPOINT  */
    PTP = 673,                     /* PTP  */
    POINTOMULTIPOINT = 674,        /* POINTOMULTIPOINT  */
    PTMP = 675,                    /* PTMP  */
    CRYPTOGRAPHIC = 676,           /* CRYPTOGRAPHIC  */
    ELIGIBLE = 677,                /* ELIGIBLE  */
    POLL = 678,                    /* POLL  */
    NETWORKS = 679,                /* NETWORKS  */
    HIDDEN = 680,                  /* HIDDEN  */
    VIRTUAL = 681,                 /* VIRTUAL  */
    ONLY = 682,                    /* ONLY  */
    LARGE = 683,                   /* LARGE  */
    NORMAL = 684,                  /* NORMAL  */
    STUBNET = 685,                 /* STUBNET  */
    TAG = 686,                     /* TAG  */
    LSADB = 687,                   /* LSADB  */
    ECMP = 688,                    /* ECMP  */
    NSSA = 689,                    /* NSSA  */
    TRANSLATOR = 690,              /* TRANSLATOR  */
    STABILITY = 691,               /* STABILITY  */
    LSID = 692,                    /* LSID  */
    INSTANCE = 693,                /* INSTANCE  */
    REAL = 694,                    /* REAL  */
    NETMASK = 695,                 /* NETMASK  */
    MERGE = 696,                   /* MERGE  */
    LSA = 697,                     /* LSA  */
    SUPPRESSION = 698,             /* SUPPRESSION  */
    RFC5838 = 699,                 /* RFC5838  */
    PE = 700,                      /* PE  */
    TOPOLOGY = 701,                /* TOPOLOGY  */
    STATE = 702,                   /* STATE  */
    PERF = 703,                    /* PERF  */
    EXP = 704,                     /* EXP  */
    REPEAT = 705,                  /* REPEAT  */
    MODE = 706,                    /* MODE  */
    PIPE = 707,                    /* PIPE  */
    RADV = 708,                    /* RADV  */
    RA = 709,                      /* RA  */
    SOLICITED = 710,               /* SOLICITED  */
    UNICAST = 711,                 /* UNICAST  */
    MANAGED = 712,                 /* MANAGED  */
    OTHER = 713,                   /* OTHER  */
    CONFIG = 714,                  /* CONFIG  */
    LINGER = 715,                  /* LINGER  */
    MTU = 716,                     /* MTU  */
    REACHABLE = 717,               /* REACHABLE  */
    RETRANS = 718,                 /* RETRANS  */
    TIMER = 719,                   /* TIMER  */
    CURRENT = 720,                 /* CURRENT  */
    VALID = 721,                   /* VALID  */
    PREFERRED = 722,               /* PREFERRED  */
    MULT = 723,                    /* MULT  */
    LIFETIME = 724,                /* LIFETIME  */
    SKIP = 725,                    /* SKIP  */
    ONLINK = 726,                  /* ONLINK  */
    AUTONOMOUS = 727,              /* AUTONOMOUS  */
    RDNSS = 728,                   /* RDNSS  */
    DNSSL = 729,                   /* DNSSL  */
    NS = 730,                      /* NS  */
    DOMAIN = 731,                  /* DOMAIN  */
    TRIGGER = 732,                 /* TRIGGER  */
    SENSITIVE = 733,               /* SENSITIVE  */
    LOW = 734,                     /* LOW  */
    MEDIUM = 735,                  /* MEDIUM  */
    HIGH = 736,                    /* HIGH  */
    PROPAGATE = 737,               /* PROPAGATE  */
    RA_PREFERENCE = 738,           /* RA_PREFERENCE  */
    RA_LIFETIME = 739,             /* RA_LIFETIME  */
    RIP = 740,                     /* RIP  */
    NG = 741,                      /* NG  */
    INFINITY = 742,                /* INFINITY  */
    TIMEOUT = 743,                 /* TIMEOUT  */
    GARBAGE = 744,                 /* GARBAGE  */
    VERSION = 745,                 /* VERSION  */
    SPLIT = 746,                   /* SPLIT  */
    HORIZON = 747,                 /* HORIZON  */
    POISON = 748,                  /* POISON  */
    REVERSE = 749,                 /* REVERSE  */
    ZERO = 750,                    /* ZERO  */
    PLAINTEXT = 751,               /* PLAINTEXT  */
    DEMAND = 752,                  /* DEMAND  */
    CIRCUIT = 753,                 /* CIRCUIT  */
    RIP_METRIC = 754,              /* RIP_METRIC  */
    RIP_TAG = 755,                 /* RIP_TAG  */
    REMOTE = 756,                  /* REMOTE  */
    BIRD = 757,                    /* BIRD  */
    PRIVATE = 758,                 /* PRIVATE  */
    PUBLIC = 759,                  /* PUBLIC  */
    SSH = 760,                     /* SSH  */
    TRANSPORT = 761,               /* TRANSPORT  */
    USER = 762,                    /* USER  */
    EXPIRE = 763,                  /* EXPIRE  */
    STATIC = 764,                  /* STATIC  */
    PROHIBIT = 765,                /* PROHIBIT  */
    BLACKHOLE = 766,               /* BLACKHOLE  */
    UNREACHABLE = 767,             /* UNREACHABLE  */
    KERNEL = 768,                  /* KERNEL  */
    NETLINK = 769,                 /* NETLINK  */
    KRT_PREFSRC = 770,             /* KRT_PREFSRC  */
    KRT_REALM = 771,               /* KRT_REALM  */
    KRT_SCOPE = 772,               /* KRT_SCOPE  */
    KRT_MTU = 773,                 /* KRT_MTU  */
    KRT_WINDOW = 774,              /* KRT_WINDOW  */
    KRT_RTT = 775,                 /* KRT_RTT  */
    KRT_RTTVAR = 776,              /* KRT_RTTVAR  */
    KRT_SSTRESH = 777,             /* KRT_SSTRESH  */
    KRT_CWND = 778,                /* KRT_CWND  */
    KRT_ADVMSS = 779,              /* KRT_ADVMSS  */
    KRT_REORDERING = 780,          /* KRT_REORDERING  */
    KRT_HOPLIMIT = 781,            /* KRT_HOPLIMIT  */
    KRT_INITCWND = 782,            /* KRT_INITCWND  */
    KRT_RTO_MIN = 783,             /* KRT_RTO_MIN  */
    KRT_INITRWND = 784,            /* KRT_INITRWND  */
    KRT_QUICKACK = 785,            /* KRT_QUICKACK  */
    KRT_LOCK_MTU = 786,            /* KRT_LOCK_MTU  */
    KRT_LOCK_WINDOW = 787,         /* KRT_LOCK_WINDOW  */
    KRT_LOCK_RTT = 788,            /* KRT_LOCK_RTT  */
    KRT_LOCK_RTTVAR = 789,         /* KRT_LOCK_RTTVAR  */
    KRT_LOCK_SSTRESH = 790,        /* KRT_LOCK_SSTRESH  */
    KRT_LOCK_CWND = 791,           /* KRT_LOCK_CWND  */
    KRT_LOCK_ADVMSS = 792,         /* KRT_LOCK_ADVMSS  */
    KRT_LOCK_REORDERING = 793,     /* KRT_LOCK_REORDERING  */
    KRT_LOCK_HOPLIMIT = 794,       /* KRT_LOCK_HOPLIMIT  */
    KRT_LOCK_RTO_MIN = 795,        /* KRT_LOCK_RTO_MIN  */
    KRT_FEATURE_ECN = 796,         /* KRT_FEATURE_ECN  */
    KRT_FEATURE_ALLFRAG = 797,     /* KRT_FEATURE_ALLFRAG  */
    SYSLOG = 798,                  /* SYSLOG  */
    TRACE = 799,                   /* TRACE  */
    INFO = 800,                    /* INFO  */
    WARNING = 801,                 /* WARNING  */
    AUTH = 802,                    /* AUTH  */
    FATAL = 803,                   /* FATAL  */
    BUG = 804,                     /* BUG  */
    STDERR = 805,                  /* STDERR  */
    SOFT = 806,                    /* SOFT  */
    CONFIRM = 807,                 /* CONFIRM  */
    UNDO = 808,                    /* UNDO  */
    LATENCY = 809,                 /* LATENCY  */
    WATCHDOG = 810,                /* WATCHDOG  */
    CONFIGURE = 811,               /* CONFIGURE  */
    DOWN = 812,                    /* DOWN  */
    PERSIST = 813,                 /* PERSIST  */
    SCAN = 814,                    /* SCAN  */
    LEARN = 815,                   /* LEARN  */
    DEVICE = 816,                  /* DEVICE  */
    KRT_SOURCE = 817,              /* KRT_SOURCE  */
    KRT_METRIC = 818               /* KRT_METRIC  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 54 "conf/confbase.Y"

  uint i;
  u32 i32;
  u64 i64;
  ip_addr a;
  ip4_addr ip4;
  ip6_addr ip6;
  net_addr net;
  net_addr *net_ptr;
  struct symbol *s;
  const char *t;
  struct rtable_config *r;
  struct channel_config *cc;
  struct channel *c;
  struct f_inst *x;
  struct {
    struct f_inst *begin, *end;
  } xp;
  enum filter_return fret;
  enum ec_subtype ecs;
  struct f_dynamic_attr fda;
  struct f_static_attr fsa;
  struct f_lval flv;
  struct f_line *fl;
  struct f_arg *fa;
  const struct filter *f;
  struct f_tree *e;
  struct f_trie *trie;
  struct f_val v;
  struct password_item *p;
  struct rt_show_data *ra;
  struct sym_show_data *sd;
  struct lsadb_show_data *ld;
  struct mrt_dump_data *md;
  struct iface *iface;
  void *g;
  btime time;
  struct f_prefix px;
  struct proto_spec ps;
  struct channel_limit cl;
  struct timeformat *tf;
  mpls_label_stack *mls;
  struct bytestring *bs;

#line 672 "obj/conf/cf-parse.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE cf_lval;


int cf_parse (void);


#endif /* !YY_CF_OBJ_CONF_CF_PARSE_TAB_H_INCLUDED  */
