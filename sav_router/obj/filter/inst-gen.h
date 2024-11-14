#line 652 "filter/decl.m4"

/* Filter instruction codes */
enum f_instruction_code {
#line 284 "filter/f-inst.c"
 /* Code enum for FI_ADD */
#line 284
  FI_ADD,
#line 289 "filter/f-inst.c"
 /* Code enum for FI_SUBTRACT */
#line 289
  FI_SUBTRACT,
#line 294 "filter/f-inst.c"
 /* Code enum for FI_MULTIPLY */
#line 294
  FI_MULTIPLY,
#line 300 "filter/f-inst.c"
 /* Code enum for FI_DIVIDE */
#line 300
  FI_DIVIDE,
#line 310 "filter/f-inst.c"
 /* Code enum for FI_AND */
#line 310
  FI_AND,
#line 321 "filter/f-inst.c"
 /* Code enum for FI_OR */
#line 321
  FI_OR,
#line 331 "filter/f-inst.c"
 /* Code enum for FI_PAIR_CONSTRUCT */
#line 331
  FI_PAIR_CONSTRUCT,
#line 371 "filter/f-inst.c"
 /* Code enum for FI_EC_CONSTRUCT */
#line 371
  FI_EC_CONSTRUCT,
#line 378 "filter/f-inst.c"
 /* Code enum for FI_LC_CONSTRUCT */
#line 378
  FI_LC_CONSTRUCT,
#line 428 "filter/f-inst.c"
 /* Code enum for FI_PATHMASK_CONSTRUCT */
#line 428
  FI_PATHMASK_CONSTRUCT,
#line 435 "filter/f-inst.c"
 /* Code enum for FI_NEQ */
#line 435
  FI_NEQ,
#line 442 "filter/f-inst.c"
 /* Code enum for FI_EQ */
#line 442
  FI_EQ,
#line 453 "filter/f-inst.c"
 /* Code enum for FI_LT */
#line 453
  FI_LT,
#line 464 "filter/f-inst.c"
 /* Code enum for FI_LTE */
#line 464
  FI_LTE,
#line 469 "filter/f-inst.c"
 /* Code enum for FI_NOT */
#line 469
  FI_NOT,
#line 478 "filter/f-inst.c"
 /* Code enum for FI_MATCH */
#line 478
  FI_MATCH,
#line 487 "filter/f-inst.c"
 /* Code enum for FI_NOT_MATCH */
#line 487
  FI_NOT_MATCH,
#line 492 "filter/f-inst.c"
 /* Code enum for FI_DEFINED */
#line 492
  FI_DEFINED,
#line 504 "filter/f-inst.c"
 /* Code enum for FI_TYPE */
#line 504
  FI_TYPE,
#line 509 "filter/f-inst.c"
 /* Code enum for FI_IS_V4 */
#line 509
  FI_IS_V4,
#line 522 "filter/f-inst.c"
 /* Code enum for FI_VAR_INIT */
#line 522
  FI_VAR_INIT,
#line 531 "filter/f-inst.c"
 /* Code enum for FI_VAR_SET */
#line 531
  FI_VAR_SET,
#line 538 "filter/f-inst.c"
 /* Code enum for FI_VAR_GET */
#line 538
  FI_VAR_GET,
#line 551 "filter/f-inst.c"
 /* Code enum for FI_CONSTANT */
#line 551
  FI_CONSTANT,
#line 585 "filter/f-inst.c"
 /* Code enum for FI_FOR_INIT */
#line 585
  FI_FOR_INIT,
#line 639 "filter/f-inst.c"
 /* Code enum for FI_FOR_NEXT */
#line 639
  FI_FOR_NEXT,
#line 647 "filter/f-inst.c"
 /* Code enum for FI_CONDITION */
#line 647
  FI_CONDITION,
#line 656 "filter/f-inst.c"
 /* Code enum for FI_PRINT */
#line 656
  FI_PRINT,
#line 663 "filter/f-inst.c"
 /* Code enum for FI_FLUSH */
#line 663
  FI_FLUSH,
#line 677 "filter/f-inst.c"
 /* Code enum for FI_DIE */
#line 677
  FI_DIE,
#line 704 "filter/f-inst.c"
 /* Code enum for FI_RTA_GET */
#line 704
  FI_RTA_GET,
#line 810 "filter/f-inst.c"
 /* Code enum for FI_RTA_SET */
#line 810
  FI_RTA_SET,
#line 882 "filter/f-inst.c"
 /* Code enum for FI_EA_GET */
#line 882
  FI_EA_GET,
#line 949 "filter/f-inst.c"
 /* Code enum for FI_EA_SET */
#line 949
  FI_EA_SET,
#line 958 "filter/f-inst.c"
 /* Code enum for FI_EA_UNSET */
#line 958
  FI_EA_UNSET,
#line 970 "filter/f-inst.c"
 /* Code enum for FI_LENGTH */
#line 970
  FI_LENGTH,
#line 1005 "filter/f-inst.c"
 /* Code enum for FI_NET_SRC */
#line 1005
  FI_NET_SRC,
#line 1040 "filter/f-inst.c"
 /* Code enum for FI_NET_DST */
#line 1040
  FI_NET_DST,
#line 1050 "filter/f-inst.c"
 /* Code enum for FI_ROA_MAXLEN */
#line 1050
  FI_ROA_MAXLEN,
#line 1077 "filter/f-inst.c"
 /* Code enum for FI_ASN */
#line 1077
  FI_ASN,
#line 1082 "filter/f-inst.c"
 /* Code enum for FI_IP */
#line 1082
  FI_IP,
#line 1089 "filter/f-inst.c"
 /* Code enum for FI_ROUTE_DISTINGUISHER */
#line 1089
  FI_ROUTE_DISTINGUISHER,
#line 1096 "filter/f-inst.c"
 /* Code enum for FI_AS_PATH_FIRST */
#line 1096
  FI_AS_PATH_FIRST,
#line 1103 "filter/f-inst.c"
 /* Code enum for FI_AS_PATH_LAST */
#line 1103
  FI_AS_PATH_LAST,
#line 1108 "filter/f-inst.c"
 /* Code enum for FI_AS_PATH_LAST_NAG */
#line 1108
  FI_AS_PATH_LAST_NAG,
#line 1113 "filter/f-inst.c"
 /* Code enum for FI_PAIR_DATA */
#line 1113
  FI_PAIR_DATA,
#line 1118 "filter/f-inst.c"
 /* Code enum for FI_LC_DATA1 */
#line 1118
  FI_LC_DATA1,
#line 1123 "filter/f-inst.c"
 /* Code enum for FI_LC_DATA2 */
#line 1123
  FI_LC_DATA2,
#line 1157 "filter/f-inst.c"
 /* Code enum for FI_MIN */
#line 1157
  FI_MIN,
#line 1191 "filter/f-inst.c"
 /* Code enum for FI_MAX */
#line 1191
  FI_MAX,
#line 1217 "filter/f-inst.c"
 /* Code enum for FI_RETURN */
#line 1217
  FI_RETURN,
#line 1278 "filter/f-inst.c"
 /* Code enum for FI_CALL */
#line 1278
  FI_CALL,
#line 1283 "filter/f-inst.c"
 /* Code enum for FI_DROP_RESULT */
#line 1283
  FI_DROP_RESULT,
#line 1306 "filter/f-inst.c"
 /* Code enum for FI_SWITCH */
#line 1306
  FI_SWITCH,
#line 1314 "filter/f-inst.c"
 /* Code enum for FI_IP_MASK */
#line 1314
  FI_IP_MASK,
#line 1320 "filter/f-inst.c"
 /* Code enum for FI_PATH_PREPEND */
#line 1320
  FI_PATH_PREPEND,
#line 1377 "filter/f-inst.c"
 /* Code enum for FI_CLIST_ADD */
#line 1377
  FI_CLIST_ADD,
#line 1432 "filter/f-inst.c"
 /* Code enum for FI_CLIST_DEL */
#line 1432
  FI_CLIST_DEL,
#line 1478 "filter/f-inst.c"
 /* Code enum for FI_CLIST_FILTER */
#line 1478
  FI_CLIST_FILTER,
#line 1508 "filter/f-inst.c"
 /* Code enum for FI_ROA_CHECK_IMPLICIT */
#line 1508
  FI_ROA_CHECK_IMPLICIT,
#line 1530 "filter/f-inst.c"
 /* Code enum for FI_ROA_CHECK_EXPLICIT */
#line 1530
  FI_ROA_CHECK_EXPLICIT,
#line 1535 "filter/f-inst.c"
 /* Code enum for FI_FORMAT */
#line 1535
  FI_FORMAT,
#line 698 "filter/decl.m4"
 /* Code enum for FI_ASSERT */
#line 698
  FI_ASSERT,
#line 656 "filter/decl.m4"
} PACKED;

/* Filter instruction structure for config */
struct f_inst {
  struct f_inst *next;			/* Next instruction */
  enum f_instruction_code fi_code;	/* Instruction code */
  enum f_instruction_flags flags;	/* Flags, instruction-specific */
  enum f_type type;			/* Type of returned value, if known */
  int size;				/* How many instructions are underneath */
  int lineno;				/* Line number */
  union {
#line 284 "filter/f-inst.c"
 /* Instruction structure for config for FI_ADD */
#line 284
    struct {
#line 280 "filter/f-inst.c"
      struct f_inst * f1;
#line 281 "filter/f-inst.c"
      struct f_inst * f2;
#line 284 "filter/f-inst.c"
    } i_FI_ADD;
#line 289 "filter/f-inst.c"
 /* Instruction structure for config for FI_SUBTRACT */
#line 289
    struct {
#line 285 "filter/f-inst.c"
      struct f_inst * f1;
#line 286 "filter/f-inst.c"
      struct f_inst * f2;
#line 289 "filter/f-inst.c"
    } i_FI_SUBTRACT;
#line 294 "filter/f-inst.c"
 /* Instruction structure for config for FI_MULTIPLY */
#line 294
    struct {
#line 290 "filter/f-inst.c"
      struct f_inst * f1;
#line 291 "filter/f-inst.c"
      struct f_inst * f2;
#line 294 "filter/f-inst.c"
    } i_FI_MULTIPLY;
#line 300 "filter/f-inst.c"
 /* Instruction structure for config for FI_DIVIDE */
#line 300
    struct {
#line 295 "filter/f-inst.c"
      struct f_inst * f1;
#line 296 "filter/f-inst.c"
      struct f_inst * f2;
#line 300 "filter/f-inst.c"
    } i_FI_DIVIDE;
#line 310 "filter/f-inst.c"
 /* Instruction structure for config for FI_AND */
#line 310
    struct {
#line 301 "filter/f-inst.c"
      struct f_inst * f1;
#line 306 "filter/f-inst.c"
      struct f_inst * f2;
#line 310 "filter/f-inst.c"
    } i_FI_AND;
#line 321 "filter/f-inst.c"
 /* Instruction structure for config for FI_OR */
#line 321
    struct {
#line 311 "filter/f-inst.c"
      struct f_inst * f1;
#line 316 "filter/f-inst.c"
      struct f_inst * f2;
#line 321 "filter/f-inst.c"
    } i_FI_OR;
#line 331 "filter/f-inst.c"
 /* Instruction structure for config for FI_PAIR_CONSTRUCT */
#line 331
    struct {
#line 322 "filter/f-inst.c"
      struct f_inst * f1;
#line 323 "filter/f-inst.c"
      struct f_inst * f2;
#line 331 "filter/f-inst.c"
    } i_FI_PAIR_CONSTRUCT;
#line 371 "filter/f-inst.c"
 /* Instruction structure for config for FI_EC_CONSTRUCT */
#line 371
    struct {
#line 332 "filter/f-inst.c"
      struct f_inst * f1;
#line 333 "filter/f-inst.c"
      struct f_inst * f2;
#line 335 "filter/f-inst.c"
      enum ec_subtype ecs;
#line 371 "filter/f-inst.c"
    } i_FI_EC_CONSTRUCT;
#line 378 "filter/f-inst.c"
 /* Instruction structure for config for FI_LC_CONSTRUCT */
#line 378
    struct {
#line 372 "filter/f-inst.c"
      struct f_inst * f1;
#line 373 "filter/f-inst.c"
      struct f_inst * f2;
#line 374 "filter/f-inst.c"
      struct f_inst * f3;
#line 378 "filter/f-inst.c"
    } i_FI_LC_CONSTRUCT;
#line 428 "filter/f-inst.c"
 /* Instruction structure for config for FI_PATHMASK_CONSTRUCT */
#line 428
    struct {
#line 379 "filter/f-inst.c"
      struct f_inst * fvar;
#line 379
      uint varcount;
#line 428 "filter/f-inst.c"
    } i_FI_PATHMASK_CONSTRUCT;
#line 435 "filter/f-inst.c"
 /* Instruction structure for config for FI_NEQ */
#line 435
    struct {
#line 429 "filter/f-inst.c"
      struct f_inst * f1;
#line 430 "filter/f-inst.c"
      struct f_inst * f2;
#line 435 "filter/f-inst.c"
    } i_FI_NEQ;
#line 442 "filter/f-inst.c"
 /* Instruction structure for config for FI_EQ */
#line 442
    struct {
#line 436 "filter/f-inst.c"
      struct f_inst * f1;
#line 437 "filter/f-inst.c"
      struct f_inst * f2;
#line 442 "filter/f-inst.c"
    } i_FI_EQ;
#line 453 "filter/f-inst.c"
 /* Instruction structure for config for FI_LT */
#line 453
    struct {
#line 443 "filter/f-inst.c"
      struct f_inst * f1;
#line 444 "filter/f-inst.c"
      struct f_inst * f2;
#line 453 "filter/f-inst.c"
    } i_FI_LT;
#line 464 "filter/f-inst.c"
 /* Instruction structure for config for FI_LTE */
#line 464
    struct {
#line 454 "filter/f-inst.c"
      struct f_inst * f1;
#line 455 "filter/f-inst.c"
      struct f_inst * f2;
#line 464 "filter/f-inst.c"
    } i_FI_LTE;
#line 469 "filter/f-inst.c"
 /* Instruction structure for config for FI_NOT */
#line 469
    struct {
#line 465 "filter/f-inst.c"
      struct f_inst * f1;
#line 469 "filter/f-inst.c"
    } i_FI_NOT;
#line 478 "filter/f-inst.c"
 /* Instruction structure for config for FI_MATCH */
#line 478
    struct {
#line 470 "filter/f-inst.c"
      struct f_inst * f1;
#line 471 "filter/f-inst.c"
      struct f_inst * f2;
#line 478 "filter/f-inst.c"
    } i_FI_MATCH;
#line 487 "filter/f-inst.c"
 /* Instruction structure for config for FI_NOT_MATCH */
#line 487
    struct {
#line 479 "filter/f-inst.c"
      struct f_inst * f1;
#line 480 "filter/f-inst.c"
      struct f_inst * f2;
#line 487 "filter/f-inst.c"
    } i_FI_NOT_MATCH;
#line 492 "filter/f-inst.c"
 /* Instruction structure for config for FI_DEFINED */
#line 492
    struct {
#line 488 "filter/f-inst.c"
      struct f_inst * f1;
#line 492 "filter/f-inst.c"
    } i_FI_DEFINED;
#line 504 "filter/f-inst.c"
 /* Instruction structure for config for FI_TYPE */
#line 504
    struct {
#line 493 "filter/f-inst.c"
      struct f_inst * f1;
#line 504 "filter/f-inst.c"
    } i_FI_TYPE;
#line 509 "filter/f-inst.c"
 /* Instruction structure for config for FI_IS_V4 */
#line 509
    struct {
#line 505 "filter/f-inst.c"
      struct f_inst * f1;
#line 509 "filter/f-inst.c"
    } i_FI_IS_V4;
#line 522 "filter/f-inst.c"
 /* Instruction structure for config for FI_VAR_INIT */
#line 522
    struct {
#line 511 "filter/f-inst.c"
      struct f_inst * f1;
#line 512 "filter/f-inst.c"
      struct symbol * sym;
#line 522 "filter/f-inst.c"
    } i_FI_VAR_INIT;
#line 531 "filter/f-inst.c"
 /* Instruction structure for config for FI_VAR_SET */
#line 531
    struct {
#line 524 "filter/f-inst.c"
      struct f_inst * f1;
#line 525 "filter/f-inst.c"
      struct symbol * sym;
#line 531 "filter/f-inst.c"
    } i_FI_VAR_SET;
#line 538 "filter/f-inst.c"
 /* Instruction structure for config for FI_VAR_GET */
#line 538
    struct {
#line 532 "filter/f-inst.c"
      struct symbol * sym;
#line 538 "filter/f-inst.c"
    } i_FI_VAR_GET;
#line 551 "filter/f-inst.c"
 /* Instruction structure for config for FI_CONSTANT */
#line 551
    struct {
#line 539 "filter/f-inst.c"
      struct f_val val;
#line 551 "filter/f-inst.c"
    } i_FI_CONSTANT;
#line 585 "filter/f-inst.c"
 /* Instruction structure for config for FI_FOR_INIT */
#line 585
    struct {
#line 553 "filter/f-inst.c"
      struct f_inst * f1;
#line 554 "filter/f-inst.c"
      struct symbol * sym;
#line 585 "filter/f-inst.c"
    } i_FI_FOR_INIT;
#line 639 "filter/f-inst.c"
 /* Instruction structure for config for FI_FOR_NEXT */
#line 639
    struct {
#line 587 "filter/f-inst.c"
      struct symbol * sym;
#line 630 "filter/f-inst.c"
      struct f_inst * f1;
#line 639 "filter/f-inst.c"
    } i_FI_FOR_NEXT;
#line 647 "filter/f-inst.c"
 /* Instruction structure for config for FI_CONDITION */
#line 647
    struct {
#line 640 "filter/f-inst.c"
      struct f_inst * f1;
#line 642 "filter/f-inst.c"
      struct f_inst * f2;
#line 644 "filter/f-inst.c"
      struct f_inst * f3;
#line 647 "filter/f-inst.c"
    } i_FI_CONDITION;
#line 656 "filter/f-inst.c"
 /* Instruction structure for config for FI_PRINT */
#line 656
    struct {
#line 649 "filter/f-inst.c"
      struct f_inst * fvar;
#line 649
      uint varcount;
#line 656 "filter/f-inst.c"
    } i_FI_PRINT;
#line 663 "filter/f-inst.c"
 /* Instruction structure for config for FI_FLUSH */
#line 663
    struct {
#line 663
    } i_FI_FLUSH;
#line 677 "filter/f-inst.c"
 /* Instruction structure for config for FI_DIE */
#line 677
    struct {
#line 665 "filter/f-inst.c"
      enum filter_return fret;
#line 677 "filter/f-inst.c"
    } i_FI_DIE;
#line 704 "filter/f-inst.c"
 /* Instruction structure for config for FI_RTA_GET */
#line 704
    struct {
#line 679 "filter/f-inst.c"
      struct f_static_attr sa;
#line 704 "filter/f-inst.c"
    } i_FI_RTA_GET;
#line 810 "filter/f-inst.c"
 /* Instruction structure for config for FI_RTA_SET */
#line 810
    struct {
#line 706 "filter/f-inst.c"
      struct f_inst * f1;
#line 707 "filter/f-inst.c"
      struct f_static_attr sa;
#line 810 "filter/f-inst.c"
    } i_FI_RTA_SET;
#line 882 "filter/f-inst.c"
 /* Instruction structure for config for FI_EA_GET */
#line 882
    struct {
#line 811 "filter/f-inst.c"
      struct f_dynamic_attr da;
#line 882 "filter/f-inst.c"
    } i_FI_EA_GET;
#line 949 "filter/f-inst.c"
 /* Instruction structure for config for FI_EA_SET */
#line 949
    struct {
#line 885 "filter/f-inst.c"
      struct f_inst * f1;
#line 886 "filter/f-inst.c"
      struct f_dynamic_attr da;
#line 949 "filter/f-inst.c"
    } i_FI_EA_SET;
#line 958 "filter/f-inst.c"
 /* Instruction structure for config for FI_EA_UNSET */
#line 958
    struct {
#line 950 "filter/f-inst.c"
      struct f_dynamic_attr da;
#line 958 "filter/f-inst.c"
    } i_FI_EA_UNSET;
#line 970 "filter/f-inst.c"
 /* Instruction structure for config for FI_LENGTH */
#line 970
    struct {
#line 959 "filter/f-inst.c"
      struct f_inst * f1;
#line 970 "filter/f-inst.c"
    } i_FI_LENGTH;
#line 1005 "filter/f-inst.c"
 /* Instruction structure for config for FI_NET_SRC */
#line 1005
    struct {
#line 971 "filter/f-inst.c"
      struct f_inst * f1;
#line 1005 "filter/f-inst.c"
    } i_FI_NET_SRC;
#line 1040 "filter/f-inst.c"
 /* Instruction structure for config for FI_NET_DST */
#line 1040
    struct {
#line 1006 "filter/f-inst.c"
      struct f_inst * f1;
#line 1040 "filter/f-inst.c"
    } i_FI_NET_DST;
#line 1050 "filter/f-inst.c"
 /* Instruction structure for config for FI_ROA_MAXLEN */
#line 1050
    struct {
#line 1041 "filter/f-inst.c"
      struct f_inst * f1;
#line 1050 "filter/f-inst.c"
    } i_FI_ROA_MAXLEN;
#line 1077 "filter/f-inst.c"
 /* Instruction structure for config for FI_ASN */
#line 1077
    struct {
#line 1051 "filter/f-inst.c"
      struct f_inst * f1;
#line 1077 "filter/f-inst.c"
    } i_FI_ASN;
#line 1082 "filter/f-inst.c"
 /* Instruction structure for config for FI_IP */
#line 1082
    struct {
#line 1078 "filter/f-inst.c"
      struct f_inst * f1;
#line 1082 "filter/f-inst.c"
    } i_FI_IP;
#line 1089 "filter/f-inst.c"
 /* Instruction structure for config for FI_ROUTE_DISTINGUISHER */
#line 1089
    struct {
#line 1083 "filter/f-inst.c"
      struct f_inst * f1;
#line 1089 "filter/f-inst.c"
    } i_FI_ROUTE_DISTINGUISHER;
#line 1096 "filter/f-inst.c"
 /* Instruction structure for config for FI_AS_PATH_FIRST */
#line 1096
    struct {
#line 1090 "filter/f-inst.c"
      struct f_inst * f1;
#line 1096 "filter/f-inst.c"
    } i_FI_AS_PATH_FIRST;
#line 1103 "filter/f-inst.c"
 /* Instruction structure for config for FI_AS_PATH_LAST */
#line 1103
    struct {
#line 1097 "filter/f-inst.c"
      struct f_inst * f1;
#line 1103 "filter/f-inst.c"
    } i_FI_AS_PATH_LAST;
#line 1108 "filter/f-inst.c"
 /* Instruction structure for config for FI_AS_PATH_LAST_NAG */
#line 1108
    struct {
#line 1104 "filter/f-inst.c"
      struct f_inst * f1;
#line 1108 "filter/f-inst.c"
    } i_FI_AS_PATH_LAST_NAG;
#line 1113 "filter/f-inst.c"
 /* Instruction structure for config for FI_PAIR_DATA */
#line 1113
    struct {
#line 1109 "filter/f-inst.c"
      struct f_inst * f1;
#line 1113 "filter/f-inst.c"
    } i_FI_PAIR_DATA;
#line 1118 "filter/f-inst.c"
 /* Instruction structure for config for FI_LC_DATA1 */
#line 1118
    struct {
#line 1114 "filter/f-inst.c"
      struct f_inst * f1;
#line 1118 "filter/f-inst.c"
    } i_FI_LC_DATA1;
#line 1123 "filter/f-inst.c"
 /* Instruction structure for config for FI_LC_DATA2 */
#line 1123
    struct {
#line 1119 "filter/f-inst.c"
      struct f_inst * f1;
#line 1123 "filter/f-inst.c"
    } i_FI_LC_DATA2;
#line 1157 "filter/f-inst.c"
 /* Instruction structure for config for FI_MIN */
#line 1157
    struct {
#line 1124 "filter/f-inst.c"
      struct f_inst * f1;
#line 1157 "filter/f-inst.c"
    } i_FI_MIN;
#line 1191 "filter/f-inst.c"
 /* Instruction structure for config for FI_MAX */
#line 1191
    struct {
#line 1158 "filter/f-inst.c"
      struct f_inst * f1;
#line 1191 "filter/f-inst.c"
    } i_FI_MAX;
#line 1217 "filter/f-inst.c"
 /* Instruction structure for config for FI_RETURN */
#line 1217
    struct {
#line 1194 "filter/f-inst.c"
      struct f_inst * f1;
#line 1217 "filter/f-inst.c"
    } i_FI_RETURN;
#line 1278 "filter/f-inst.c"
 /* Instruction structure for config for FI_CALL */
#line 1278
    struct {
#line 1219 "filter/f-inst.c"
      struct f_inst * fvar;
#line 1219
      uint varcount;
#line 1220 "filter/f-inst.c"
      struct symbol * sym;
#line 1278 "filter/f-inst.c"
    } i_FI_CALL;
#line 1283 "filter/f-inst.c"
 /* Instruction structure for config for FI_DROP_RESULT */
#line 1283
    struct {
#line 1280 "filter/f-inst.c"
      struct f_inst * f1;
#line 1283 "filter/f-inst.c"
    } i_FI_DROP_RESULT;
#line 1306 "filter/f-inst.c"
 /* Instruction structure for config for FI_SWITCH */
#line 1306
    struct {
#line 1284 "filter/f-inst.c"
      struct f_inst * f1;
#line 1286 "filter/f-inst.c"
      struct f_tree * tree;
#line 1306 "filter/f-inst.c"
    } i_FI_SWITCH;
#line 1314 "filter/f-inst.c"
 /* Instruction structure for config for FI_IP_MASK */
#line 1314
    struct {
#line 1307 "filter/f-inst.c"
      struct f_inst * f1;
#line 1308 "filter/f-inst.c"
      struct f_inst * f2;
#line 1314 "filter/f-inst.c"
    } i_FI_IP_MASK;
#line 1320 "filter/f-inst.c"
 /* Instruction structure for config for FI_PATH_PREPEND */
#line 1320
    struct {
#line 1315 "filter/f-inst.c"
      struct f_inst * f1;
#line 1316 "filter/f-inst.c"
      struct f_inst * f2;
#line 1320 "filter/f-inst.c"
    } i_FI_PATH_PREPEND;
#line 1377 "filter/f-inst.c"
 /* Instruction structure for config for FI_CLIST_ADD */
#line 1377
    struct {
#line 1321 "filter/f-inst.c"
      struct f_inst * f1;
#line 1322 "filter/f-inst.c"
      struct f_inst * f2;
#line 1377 "filter/f-inst.c"
    } i_FI_CLIST_ADD;
#line 1432 "filter/f-inst.c"
 /* Instruction structure for config for FI_CLIST_DEL */
#line 1432
    struct {
#line 1378 "filter/f-inst.c"
      struct f_inst * f1;
#line 1379 "filter/f-inst.c"
      struct f_inst * f2;
#line 1432 "filter/f-inst.c"
    } i_FI_CLIST_DEL;
#line 1478 "filter/f-inst.c"
 /* Instruction structure for config for FI_CLIST_FILTER */
#line 1478
    struct {
#line 1433 "filter/f-inst.c"
      struct f_inst * f1;
#line 1434 "filter/f-inst.c"
      struct f_inst * f2;
#line 1478 "filter/f-inst.c"
    } i_FI_CLIST_FILTER;
#line 1508 "filter/f-inst.c"
 /* Instruction structure for config for FI_ROA_CHECK_IMPLICIT */
#line 1508
    struct {
#line 1480 "filter/f-inst.c"
      struct rtable_config * rtc;
#line 1508 "filter/f-inst.c"
    } i_FI_ROA_CHECK_IMPLICIT;
#line 1530 "filter/f-inst.c"
 /* Instruction structure for config for FI_ROA_CHECK_EXPLICIT */
#line 1530
    struct {
#line 1510 "filter/f-inst.c"
      struct f_inst * f1;
#line 1511 "filter/f-inst.c"
      struct f_inst * f2;
#line 1512 "filter/f-inst.c"
      struct rtable_config * rtc;
#line 1530 "filter/f-inst.c"
    } i_FI_ROA_CHECK_EXPLICIT;
#line 1535 "filter/f-inst.c"
 /* Instruction structure for config for FI_FORMAT */
#line 1535
    struct {
#line 1531 "filter/f-inst.c"
      struct f_inst * f1;
#line 1535 "filter/f-inst.c"
    } i_FI_FORMAT;
#line 698 "filter/decl.m4"
 /* Instruction structure for config for FI_ASSERT */
#line 698
    struct {
#line 1537 "filter/f-inst.c"
      struct f_inst * f1;
#line 1539 "filter/f-inst.c"
      char * s;
#line 698 "filter/decl.m4"
    } i_FI_ASSERT;
#line 668 "filter/decl.m4"
  };
};

/* Filter line item */
struct f_line_item {
  enum f_instruction_code fi_code;	/* What to do */
  enum f_instruction_flags flags;	/* Flags, instruction-specific */
  uint lineno;				/* Where */
  union {
#line 284 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_ADD */
#line 284
    struct {
#line 284
    } i_FI_ADD;
#line 289 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_SUBTRACT */
#line 289
    struct {
#line 289
    } i_FI_SUBTRACT;
#line 294 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_MULTIPLY */
#line 294
    struct {
#line 294
    } i_FI_MULTIPLY;
#line 300 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_DIVIDE */
#line 300
    struct {
#line 300
    } i_FI_DIVIDE;
#line 310 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_AND */
#line 310
    struct {
#line 306 "filter/f-inst.c"
      const struct f_line * fl2;
#line 310 "filter/f-inst.c"
    } i_FI_AND;
#line 321 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_OR */
#line 321
    struct {
#line 316 "filter/f-inst.c"
      const struct f_line * fl2;
#line 321 "filter/f-inst.c"
    } i_FI_OR;
#line 331 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_PAIR_CONSTRUCT */
#line 331
    struct {
#line 331
    } i_FI_PAIR_CONSTRUCT;
#line 371 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_EC_CONSTRUCT */
#line 371
    struct {
      enum ec_subtype ecs;
#line 371 "filter/f-inst.c"
    } i_FI_EC_CONSTRUCT;
#line 378 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_LC_CONSTRUCT */
#line 378
    struct {
#line 378
    } i_FI_LC_CONSTRUCT;
#line 428 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_PATHMASK_CONSTRUCT */
#line 428
    struct {
#line 379 "filter/f-inst.c"
      uint varcount;
#line 428 "filter/f-inst.c"
    } i_FI_PATHMASK_CONSTRUCT;
#line 435 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_NEQ */
#line 435
    struct {
#line 435
    } i_FI_NEQ;
#line 442 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_EQ */
#line 442
    struct {
#line 442
    } i_FI_EQ;
#line 453 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_LT */
#line 453
    struct {
#line 453
    } i_FI_LT;
#line 464 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_LTE */
#line 464
    struct {
#line 464
    } i_FI_LTE;
#line 469 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_NOT */
#line 469
    struct {
#line 469
    } i_FI_NOT;
#line 478 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_MATCH */
#line 478
    struct {
#line 478
    } i_FI_MATCH;
#line 487 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_NOT_MATCH */
#line 487
    struct {
#line 487
    } i_FI_NOT_MATCH;
#line 492 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_DEFINED */
#line 492
    struct {
#line 492
    } i_FI_DEFINED;
#line 504 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_TYPE */
#line 504
    struct {
#line 504
    } i_FI_TYPE;
#line 509 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_IS_V4 */
#line 509
    struct {
#line 509
    } i_FI_IS_V4;
#line 522 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_VAR_INIT */
#line 522
    struct {
      struct symbol * sym;
#line 522 "filter/f-inst.c"
    } i_FI_VAR_INIT;
#line 531 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_VAR_SET */
#line 531
    struct {
      struct symbol * sym;
#line 531 "filter/f-inst.c"
    } i_FI_VAR_SET;
#line 538 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_VAR_GET */
#line 538
    struct {
      struct symbol * sym;
#line 538 "filter/f-inst.c"
    } i_FI_VAR_GET;
#line 551 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_CONSTANT */
#line 551
    struct {
      struct f_val val;
#line 551 "filter/f-inst.c"
    } i_FI_CONSTANT;
#line 585 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_FOR_INIT */
#line 585
    struct {
      struct symbol * sym;
#line 585 "filter/f-inst.c"
    } i_FI_FOR_INIT;
#line 639 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_FOR_NEXT */
#line 639
    struct {
      struct symbol * sym;
#line 630 "filter/f-inst.c"
      const struct f_line * fl1;
#line 639 "filter/f-inst.c"
    } i_FI_FOR_NEXT;
#line 647 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_CONDITION */
#line 647
    struct {
#line 642 "filter/f-inst.c"
      const struct f_line * fl2;
#line 644 "filter/f-inst.c"
      const struct f_line * fl3;
#line 647 "filter/f-inst.c"
    } i_FI_CONDITION;
#line 656 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_PRINT */
#line 656
    struct {
#line 649 "filter/f-inst.c"
      uint varcount;
#line 656 "filter/f-inst.c"
    } i_FI_PRINT;
#line 663 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_FLUSH */
#line 663
    struct {
#line 663
    } i_FI_FLUSH;
#line 677 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_DIE */
#line 677
    struct {
      enum filter_return fret;
#line 677 "filter/f-inst.c"
    } i_FI_DIE;
#line 704 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_RTA_GET */
#line 704
    struct {
      struct f_static_attr sa;
#line 704 "filter/f-inst.c"
    } i_FI_RTA_GET;
#line 810 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_RTA_SET */
#line 810
    struct {
      struct f_static_attr sa;
#line 810 "filter/f-inst.c"
    } i_FI_RTA_SET;
#line 882 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_EA_GET */
#line 882
    struct {
      struct f_dynamic_attr da;
#line 882 "filter/f-inst.c"
    } i_FI_EA_GET;
#line 949 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_EA_SET */
#line 949
    struct {
      struct f_dynamic_attr da;
#line 949 "filter/f-inst.c"
    } i_FI_EA_SET;
#line 958 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_EA_UNSET */
#line 958
    struct {
      struct f_dynamic_attr da;
#line 958 "filter/f-inst.c"
    } i_FI_EA_UNSET;
#line 970 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_LENGTH */
#line 970
    struct {
#line 970
    } i_FI_LENGTH;
#line 1005 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_NET_SRC */
#line 1005
    struct {
#line 1005
    } i_FI_NET_SRC;
#line 1040 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_NET_DST */
#line 1040
    struct {
#line 1040
    } i_FI_NET_DST;
#line 1050 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_ROA_MAXLEN */
#line 1050
    struct {
#line 1050
    } i_FI_ROA_MAXLEN;
#line 1077 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_ASN */
#line 1077
    struct {
#line 1077
    } i_FI_ASN;
#line 1082 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_IP */
#line 1082
    struct {
#line 1082
    } i_FI_IP;
#line 1089 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_ROUTE_DISTINGUISHER */
#line 1089
    struct {
#line 1089
    } i_FI_ROUTE_DISTINGUISHER;
#line 1096 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_AS_PATH_FIRST */
#line 1096
    struct {
#line 1096
    } i_FI_AS_PATH_FIRST;
#line 1103 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_AS_PATH_LAST */
#line 1103
    struct {
#line 1103
    } i_FI_AS_PATH_LAST;
#line 1108 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_AS_PATH_LAST_NAG */
#line 1108
    struct {
#line 1108
    } i_FI_AS_PATH_LAST_NAG;
#line 1113 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_PAIR_DATA */
#line 1113
    struct {
#line 1113
    } i_FI_PAIR_DATA;
#line 1118 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_LC_DATA1 */
#line 1118
    struct {
#line 1118
    } i_FI_LC_DATA1;
#line 1123 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_LC_DATA2 */
#line 1123
    struct {
#line 1123
    } i_FI_LC_DATA2;
#line 1157 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_MIN */
#line 1157
    struct {
#line 1157
    } i_FI_MIN;
#line 1191 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_MAX */
#line 1191
    struct {
#line 1191
    } i_FI_MAX;
#line 1217 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_RETURN */
#line 1217
    struct {
#line 1217
    } i_FI_RETURN;
#line 1278 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_CALL */
#line 1278
    struct {
#line 1219 "filter/f-inst.c"
      uint varcount;
      struct symbol * sym;
#line 1278 "filter/f-inst.c"
    } i_FI_CALL;
#line 1283 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_DROP_RESULT */
#line 1283
    struct {
#line 1283
    } i_FI_DROP_RESULT;
#line 1306 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_SWITCH */
#line 1306
    struct {
      struct f_tree * tree;
#line 1306 "filter/f-inst.c"
    } i_FI_SWITCH;
#line 1314 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_IP_MASK */
#line 1314
    struct {
#line 1314
    } i_FI_IP_MASK;
#line 1320 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_PATH_PREPEND */
#line 1320
    struct {
#line 1320
    } i_FI_PATH_PREPEND;
#line 1377 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_CLIST_ADD */
#line 1377
    struct {
#line 1377
    } i_FI_CLIST_ADD;
#line 1432 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_CLIST_DEL */
#line 1432
    struct {
#line 1432
    } i_FI_CLIST_DEL;
#line 1478 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_CLIST_FILTER */
#line 1478
    struct {
#line 1478
    } i_FI_CLIST_FILTER;
#line 1508 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_ROA_CHECK_IMPLICIT */
#line 1508
    struct {
      struct rtable_config * rtc;
#line 1508 "filter/f-inst.c"
    } i_FI_ROA_CHECK_IMPLICIT;
#line 1530 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_ROA_CHECK_EXPLICIT */
#line 1530
    struct {
      struct rtable_config * rtc;
#line 1530 "filter/f-inst.c"
    } i_FI_ROA_CHECK_EXPLICIT;
#line 1535 "filter/f-inst.c"
 /* Instruction structure for interpreter for FI_FORMAT */
#line 1535
    struct {
#line 1535
    } i_FI_FORMAT;
#line 698 "filter/decl.m4"
 /* Instruction structure for interpreter for FI_ASSERT */
#line 698
    struct {
      char * s;
#line 698 "filter/decl.m4"
    } i_FI_ASSERT;
#line 678 "filter/decl.m4"
  };
};

/* Instruction constructors */
#line 284 "filter/f-inst.c"
 /* Constructor for FI_ADD */
#line 284
struct f_inst *
#line 280 "filter/f-inst.c"
NONNULL(2)
#line 281 "filter/f-inst.c"
NONNULL(3)
#line 284 "filter/f-inst.c"
f_new_inst_FI_ADD(enum f_instruction_code fi_code
#line 280 "filter/f-inst.c"
  , struct f_inst * f1
#line 281 "filter/f-inst.c"
  , struct f_inst * f2
#line 284 "filter/f-inst.c"
);
#line 284

#line 289 "filter/f-inst.c"
 /* Constructor for FI_SUBTRACT */
#line 289
struct f_inst *
#line 285 "filter/f-inst.c"
NONNULL(2)
#line 286 "filter/f-inst.c"
NONNULL(3)
#line 289 "filter/f-inst.c"
f_new_inst_FI_SUBTRACT(enum f_instruction_code fi_code
#line 285 "filter/f-inst.c"
  , struct f_inst * f1
#line 286 "filter/f-inst.c"
  , struct f_inst * f2
#line 289 "filter/f-inst.c"
);
#line 289

#line 294 "filter/f-inst.c"
 /* Constructor for FI_MULTIPLY */
#line 294
struct f_inst *
#line 290 "filter/f-inst.c"
NONNULL(2)
#line 291 "filter/f-inst.c"
NONNULL(3)
#line 294 "filter/f-inst.c"
f_new_inst_FI_MULTIPLY(enum f_instruction_code fi_code
#line 290 "filter/f-inst.c"
  , struct f_inst * f1
#line 291 "filter/f-inst.c"
  , struct f_inst * f2
#line 294 "filter/f-inst.c"
);
#line 294

#line 300 "filter/f-inst.c"
 /* Constructor for FI_DIVIDE */
#line 300
struct f_inst *
#line 295 "filter/f-inst.c"
NONNULL(2)
#line 296 "filter/f-inst.c"
NONNULL(3)
#line 300 "filter/f-inst.c"
f_new_inst_FI_DIVIDE(enum f_instruction_code fi_code
#line 295 "filter/f-inst.c"
  , struct f_inst * f1
#line 296 "filter/f-inst.c"
  , struct f_inst * f2
#line 300 "filter/f-inst.c"
);
#line 300

#line 310 "filter/f-inst.c"
 /* Constructor for FI_AND */
#line 310
struct f_inst *
#line 301 "filter/f-inst.c"
NONNULL(2)
#line 310 "filter/f-inst.c"
f_new_inst_FI_AND(enum f_instruction_code fi_code
#line 301 "filter/f-inst.c"
  , struct f_inst * f1
#line 306 "filter/f-inst.c"
  , struct f_inst * f2
#line 310 "filter/f-inst.c"
);
#line 310

#line 321 "filter/f-inst.c"
 /* Constructor for FI_OR */
#line 321
struct f_inst *
#line 311 "filter/f-inst.c"
NONNULL(2)
#line 321 "filter/f-inst.c"
f_new_inst_FI_OR(enum f_instruction_code fi_code
#line 311 "filter/f-inst.c"
  , struct f_inst * f1
#line 316 "filter/f-inst.c"
  , struct f_inst * f2
#line 321 "filter/f-inst.c"
);
#line 321

#line 331 "filter/f-inst.c"
 /* Constructor for FI_PAIR_CONSTRUCT */
#line 331
struct f_inst *
#line 322 "filter/f-inst.c"
NONNULL(2)
#line 323 "filter/f-inst.c"
NONNULL(3)
#line 331 "filter/f-inst.c"
f_new_inst_FI_PAIR_CONSTRUCT(enum f_instruction_code fi_code
#line 322 "filter/f-inst.c"
  , struct f_inst * f1
#line 323 "filter/f-inst.c"
  , struct f_inst * f2
#line 331 "filter/f-inst.c"
);
#line 331

#line 371 "filter/f-inst.c"
 /* Constructor for FI_EC_CONSTRUCT */
#line 371
struct f_inst *
#line 332 "filter/f-inst.c"
NONNULL(2)
#line 333 "filter/f-inst.c"
NONNULL(3)
#line 371 "filter/f-inst.c"
f_new_inst_FI_EC_CONSTRUCT(enum f_instruction_code fi_code
#line 332 "filter/f-inst.c"
  , struct f_inst * f1
#line 333 "filter/f-inst.c"
  , struct f_inst * f2
#line 335 "filter/f-inst.c"
  , enum ec_subtype ecs
#line 371 "filter/f-inst.c"
);
#line 371

#line 378 "filter/f-inst.c"
 /* Constructor for FI_LC_CONSTRUCT */
#line 378
struct f_inst *
#line 372 "filter/f-inst.c"
NONNULL(2)
#line 373 "filter/f-inst.c"
NONNULL(3)
#line 374 "filter/f-inst.c"
NONNULL(4)
#line 378 "filter/f-inst.c"
f_new_inst_FI_LC_CONSTRUCT(enum f_instruction_code fi_code
#line 372 "filter/f-inst.c"
  , struct f_inst * f1
#line 373 "filter/f-inst.c"
  , struct f_inst * f2
#line 374 "filter/f-inst.c"
  , struct f_inst * f3
#line 378 "filter/f-inst.c"
);
#line 378

#line 428 "filter/f-inst.c"
 /* Constructor for FI_PATHMASK_CONSTRUCT */
#line 428
struct f_inst *
#line 428
f_new_inst_FI_PATHMASK_CONSTRUCT(enum f_instruction_code fi_code
#line 379 "filter/f-inst.c"
  , struct f_inst * fvar
#line 428 "filter/f-inst.c"
);
#line 428

#line 435 "filter/f-inst.c"
 /* Constructor for FI_NEQ */
#line 435
struct f_inst *
#line 429 "filter/f-inst.c"
NONNULL(2)
#line 430 "filter/f-inst.c"
NONNULL(3)
#line 435 "filter/f-inst.c"
f_new_inst_FI_NEQ(enum f_instruction_code fi_code
#line 429 "filter/f-inst.c"
  , struct f_inst * f1
#line 430 "filter/f-inst.c"
  , struct f_inst * f2
#line 435 "filter/f-inst.c"
);
#line 435

#line 442 "filter/f-inst.c"
 /* Constructor for FI_EQ */
#line 442
struct f_inst *
#line 436 "filter/f-inst.c"
NONNULL(2)
#line 437 "filter/f-inst.c"
NONNULL(3)
#line 442 "filter/f-inst.c"
f_new_inst_FI_EQ(enum f_instruction_code fi_code
#line 436 "filter/f-inst.c"
  , struct f_inst * f1
#line 437 "filter/f-inst.c"
  , struct f_inst * f2
#line 442 "filter/f-inst.c"
);
#line 442

#line 453 "filter/f-inst.c"
 /* Constructor for FI_LT */
#line 453
struct f_inst *
#line 443 "filter/f-inst.c"
NONNULL(2)
#line 444 "filter/f-inst.c"
NONNULL(3)
#line 453 "filter/f-inst.c"
f_new_inst_FI_LT(enum f_instruction_code fi_code
#line 443 "filter/f-inst.c"
  , struct f_inst * f1
#line 444 "filter/f-inst.c"
  , struct f_inst * f2
#line 453 "filter/f-inst.c"
);
#line 453

#line 464 "filter/f-inst.c"
 /* Constructor for FI_LTE */
#line 464
struct f_inst *
#line 454 "filter/f-inst.c"
NONNULL(2)
#line 455 "filter/f-inst.c"
NONNULL(3)
#line 464 "filter/f-inst.c"
f_new_inst_FI_LTE(enum f_instruction_code fi_code
#line 454 "filter/f-inst.c"
  , struct f_inst * f1
#line 455 "filter/f-inst.c"
  , struct f_inst * f2
#line 464 "filter/f-inst.c"
);
#line 464

#line 469 "filter/f-inst.c"
 /* Constructor for FI_NOT */
#line 469
struct f_inst *
#line 465 "filter/f-inst.c"
NONNULL(2)
#line 469 "filter/f-inst.c"
f_new_inst_FI_NOT(enum f_instruction_code fi_code
#line 465 "filter/f-inst.c"
  , struct f_inst * f1
#line 469 "filter/f-inst.c"
);
#line 469

#line 478 "filter/f-inst.c"
 /* Constructor for FI_MATCH */
#line 478
struct f_inst *
#line 470 "filter/f-inst.c"
NONNULL(2)
#line 471 "filter/f-inst.c"
NONNULL(3)
#line 478 "filter/f-inst.c"
f_new_inst_FI_MATCH(enum f_instruction_code fi_code
#line 470 "filter/f-inst.c"
  , struct f_inst * f1
#line 471 "filter/f-inst.c"
  , struct f_inst * f2
#line 478 "filter/f-inst.c"
);
#line 478

#line 487 "filter/f-inst.c"
 /* Constructor for FI_NOT_MATCH */
#line 487
struct f_inst *
#line 479 "filter/f-inst.c"
NONNULL(2)
#line 480 "filter/f-inst.c"
NONNULL(3)
#line 487 "filter/f-inst.c"
f_new_inst_FI_NOT_MATCH(enum f_instruction_code fi_code
#line 479 "filter/f-inst.c"
  , struct f_inst * f1
#line 480 "filter/f-inst.c"
  , struct f_inst * f2
#line 487 "filter/f-inst.c"
);
#line 487

#line 492 "filter/f-inst.c"
 /* Constructor for FI_DEFINED */
#line 492
struct f_inst *
#line 488 "filter/f-inst.c"
NONNULL(2)
#line 492 "filter/f-inst.c"
f_new_inst_FI_DEFINED(enum f_instruction_code fi_code
#line 488 "filter/f-inst.c"
  , struct f_inst * f1
#line 492 "filter/f-inst.c"
);
#line 492

#line 504 "filter/f-inst.c"
 /* Constructor for FI_TYPE */
#line 504
struct f_inst *
#line 493 "filter/f-inst.c"
NONNULL(2)
#line 504 "filter/f-inst.c"
f_new_inst_FI_TYPE(enum f_instruction_code fi_code
#line 493 "filter/f-inst.c"
  , struct f_inst * f1
#line 504 "filter/f-inst.c"
);
#line 504

#line 509 "filter/f-inst.c"
 /* Constructor for FI_IS_V4 */
#line 509
struct f_inst *
#line 505 "filter/f-inst.c"
NONNULL(2)
#line 509 "filter/f-inst.c"
f_new_inst_FI_IS_V4(enum f_instruction_code fi_code
#line 505 "filter/f-inst.c"
  , struct f_inst * f1
#line 509 "filter/f-inst.c"
);
#line 509

#line 522 "filter/f-inst.c"
 /* Constructor for FI_VAR_INIT */
#line 522
struct f_inst *
#line 511 "filter/f-inst.c"
NONNULL(2)
#line 522 "filter/f-inst.c"
f_new_inst_FI_VAR_INIT(enum f_instruction_code fi_code
#line 511 "filter/f-inst.c"
  , struct f_inst * f1
#line 512 "filter/f-inst.c"
  , struct symbol * sym
#line 522 "filter/f-inst.c"
);
#line 522

#line 531 "filter/f-inst.c"
 /* Constructor for FI_VAR_SET */
#line 531
struct f_inst *
#line 524 "filter/f-inst.c"
NONNULL(2)
#line 531 "filter/f-inst.c"
f_new_inst_FI_VAR_SET(enum f_instruction_code fi_code
#line 524 "filter/f-inst.c"
  , struct f_inst * f1
#line 525 "filter/f-inst.c"
  , struct symbol * sym
#line 531 "filter/f-inst.c"
);
#line 531

#line 538 "filter/f-inst.c"
 /* Constructor for FI_VAR_GET */
#line 538
struct f_inst *
#line 538
f_new_inst_FI_VAR_GET(enum f_instruction_code fi_code
#line 532 "filter/f-inst.c"
  , struct symbol * sym
#line 538 "filter/f-inst.c"
);
#line 538

#line 551 "filter/f-inst.c"
 /* Constructor for FI_CONSTANT */
#line 551
struct f_inst *
#line 551
f_new_inst_FI_CONSTANT(enum f_instruction_code fi_code
#line 539 "filter/f-inst.c"
  , struct f_val val
#line 551 "filter/f-inst.c"
);
#line 551

#line 585 "filter/f-inst.c"
 /* Constructor for FI_FOR_INIT */
#line 585
struct f_inst *
#line 553 "filter/f-inst.c"
NONNULL(2)
#line 585 "filter/f-inst.c"
f_new_inst_FI_FOR_INIT(enum f_instruction_code fi_code
#line 553 "filter/f-inst.c"
  , struct f_inst * f1
#line 554 "filter/f-inst.c"
  , struct symbol * sym
#line 585 "filter/f-inst.c"
);
#line 585

#line 639 "filter/f-inst.c"
 /* Constructor for FI_FOR_NEXT */
#line 639
struct f_inst *
#line 639
f_new_inst_FI_FOR_NEXT(enum f_instruction_code fi_code
#line 587 "filter/f-inst.c"
  , struct symbol * sym
#line 630 "filter/f-inst.c"
  , struct f_inst * f1
#line 639 "filter/f-inst.c"
);
#line 639

#line 647 "filter/f-inst.c"
 /* Constructor for FI_CONDITION */
#line 647
struct f_inst *
#line 640 "filter/f-inst.c"
NONNULL(2)
#line 647 "filter/f-inst.c"
f_new_inst_FI_CONDITION(enum f_instruction_code fi_code
#line 640 "filter/f-inst.c"
  , struct f_inst * f1
#line 642 "filter/f-inst.c"
  , struct f_inst * f2
#line 644 "filter/f-inst.c"
  , struct f_inst * f3
#line 647 "filter/f-inst.c"
);
#line 647

#line 656 "filter/f-inst.c"
 /* Constructor for FI_PRINT */
#line 656
struct f_inst *
#line 656
f_new_inst_FI_PRINT(enum f_instruction_code fi_code
#line 649 "filter/f-inst.c"
  , struct f_inst * fvar
#line 656 "filter/f-inst.c"
);
#line 656

#line 663 "filter/f-inst.c"
 /* Constructor for FI_FLUSH */
#line 663
struct f_inst *
#line 663
f_new_inst_FI_FLUSH(enum f_instruction_code fi_code
#line 663
);
#line 663

#line 677 "filter/f-inst.c"
 /* Constructor for FI_DIE */
#line 677
struct f_inst *
#line 677
f_new_inst_FI_DIE(enum f_instruction_code fi_code
#line 665 "filter/f-inst.c"
  , enum filter_return fret
#line 677 "filter/f-inst.c"
);
#line 677

#line 704 "filter/f-inst.c"
 /* Constructor for FI_RTA_GET */
#line 704
struct f_inst *
#line 704
f_new_inst_FI_RTA_GET(enum f_instruction_code fi_code
#line 679 "filter/f-inst.c"
  , struct f_static_attr sa
#line 704 "filter/f-inst.c"
);
#line 704

#line 810 "filter/f-inst.c"
 /* Constructor for FI_RTA_SET */
#line 810
struct f_inst *
#line 706 "filter/f-inst.c"
NONNULL(2)
#line 810 "filter/f-inst.c"
f_new_inst_FI_RTA_SET(enum f_instruction_code fi_code
#line 706 "filter/f-inst.c"
  , struct f_inst * f1
#line 707 "filter/f-inst.c"
  , struct f_static_attr sa
#line 810 "filter/f-inst.c"
);
#line 810

#line 882 "filter/f-inst.c"
 /* Constructor for FI_EA_GET */
#line 882
struct f_inst *
#line 882
f_new_inst_FI_EA_GET(enum f_instruction_code fi_code
#line 811 "filter/f-inst.c"
  , struct f_dynamic_attr da
#line 882 "filter/f-inst.c"
);
#line 882

#line 949 "filter/f-inst.c"
 /* Constructor for FI_EA_SET */
#line 949
struct f_inst *
#line 885 "filter/f-inst.c"
NONNULL(2)
#line 949 "filter/f-inst.c"
f_new_inst_FI_EA_SET(enum f_instruction_code fi_code
#line 885 "filter/f-inst.c"
  , struct f_inst * f1
#line 886 "filter/f-inst.c"
  , struct f_dynamic_attr da
#line 949 "filter/f-inst.c"
);
#line 949

#line 958 "filter/f-inst.c"
 /* Constructor for FI_EA_UNSET */
#line 958
struct f_inst *
#line 958
f_new_inst_FI_EA_UNSET(enum f_instruction_code fi_code
#line 950 "filter/f-inst.c"
  , struct f_dynamic_attr da
#line 958 "filter/f-inst.c"
);
#line 958

#line 970 "filter/f-inst.c"
 /* Constructor for FI_LENGTH */
#line 970
struct f_inst *
#line 959 "filter/f-inst.c"
NONNULL(2)
#line 970 "filter/f-inst.c"
f_new_inst_FI_LENGTH(enum f_instruction_code fi_code
#line 959 "filter/f-inst.c"
  , struct f_inst * f1
#line 970 "filter/f-inst.c"
);
#line 970

#line 1005 "filter/f-inst.c"
 /* Constructor for FI_NET_SRC */
#line 1005
struct f_inst *
#line 971 "filter/f-inst.c"
NONNULL(2)
#line 1005 "filter/f-inst.c"
f_new_inst_FI_NET_SRC(enum f_instruction_code fi_code
#line 971 "filter/f-inst.c"
  , struct f_inst * f1
#line 1005 "filter/f-inst.c"
);
#line 1005

#line 1040 "filter/f-inst.c"
 /* Constructor for FI_NET_DST */
#line 1040
struct f_inst *
#line 1006 "filter/f-inst.c"
NONNULL(2)
#line 1040 "filter/f-inst.c"
f_new_inst_FI_NET_DST(enum f_instruction_code fi_code
#line 1006 "filter/f-inst.c"
  , struct f_inst * f1
#line 1040 "filter/f-inst.c"
);
#line 1040

#line 1050 "filter/f-inst.c"
 /* Constructor for FI_ROA_MAXLEN */
#line 1050
struct f_inst *
#line 1041 "filter/f-inst.c"
NONNULL(2)
#line 1050 "filter/f-inst.c"
f_new_inst_FI_ROA_MAXLEN(enum f_instruction_code fi_code
#line 1041 "filter/f-inst.c"
  , struct f_inst * f1
#line 1050 "filter/f-inst.c"
);
#line 1050

#line 1077 "filter/f-inst.c"
 /* Constructor for FI_ASN */
#line 1077
struct f_inst *
#line 1051 "filter/f-inst.c"
NONNULL(2)
#line 1077 "filter/f-inst.c"
f_new_inst_FI_ASN(enum f_instruction_code fi_code
#line 1051 "filter/f-inst.c"
  , struct f_inst * f1
#line 1077 "filter/f-inst.c"
);
#line 1077

#line 1082 "filter/f-inst.c"
 /* Constructor for FI_IP */
#line 1082
struct f_inst *
#line 1078 "filter/f-inst.c"
NONNULL(2)
#line 1082 "filter/f-inst.c"
f_new_inst_FI_IP(enum f_instruction_code fi_code
#line 1078 "filter/f-inst.c"
  , struct f_inst * f1
#line 1082 "filter/f-inst.c"
);
#line 1082

#line 1089 "filter/f-inst.c"
 /* Constructor for FI_ROUTE_DISTINGUISHER */
#line 1089
struct f_inst *
#line 1083 "filter/f-inst.c"
NONNULL(2)
#line 1089 "filter/f-inst.c"
f_new_inst_FI_ROUTE_DISTINGUISHER(enum f_instruction_code fi_code
#line 1083 "filter/f-inst.c"
  , struct f_inst * f1
#line 1089 "filter/f-inst.c"
);
#line 1089

#line 1096 "filter/f-inst.c"
 /* Constructor for FI_AS_PATH_FIRST */
#line 1096
struct f_inst *
#line 1090 "filter/f-inst.c"
NONNULL(2)
#line 1096 "filter/f-inst.c"
f_new_inst_FI_AS_PATH_FIRST(enum f_instruction_code fi_code
#line 1090 "filter/f-inst.c"
  , struct f_inst * f1
#line 1096 "filter/f-inst.c"
);
#line 1096

#line 1103 "filter/f-inst.c"
 /* Constructor for FI_AS_PATH_LAST */
#line 1103
struct f_inst *
#line 1097 "filter/f-inst.c"
NONNULL(2)
#line 1103 "filter/f-inst.c"
f_new_inst_FI_AS_PATH_LAST(enum f_instruction_code fi_code
#line 1097 "filter/f-inst.c"
  , struct f_inst * f1
#line 1103 "filter/f-inst.c"
);
#line 1103

#line 1108 "filter/f-inst.c"
 /* Constructor for FI_AS_PATH_LAST_NAG */
#line 1108
struct f_inst *
#line 1104 "filter/f-inst.c"
NONNULL(2)
#line 1108 "filter/f-inst.c"
f_new_inst_FI_AS_PATH_LAST_NAG(enum f_instruction_code fi_code
#line 1104 "filter/f-inst.c"
  , struct f_inst * f1
#line 1108 "filter/f-inst.c"
);
#line 1108

#line 1113 "filter/f-inst.c"
 /* Constructor for FI_PAIR_DATA */
#line 1113
struct f_inst *
#line 1109 "filter/f-inst.c"
NONNULL(2)
#line 1113 "filter/f-inst.c"
f_new_inst_FI_PAIR_DATA(enum f_instruction_code fi_code
#line 1109 "filter/f-inst.c"
  , struct f_inst * f1
#line 1113 "filter/f-inst.c"
);
#line 1113

#line 1118 "filter/f-inst.c"
 /* Constructor for FI_LC_DATA1 */
#line 1118
struct f_inst *
#line 1114 "filter/f-inst.c"
NONNULL(2)
#line 1118 "filter/f-inst.c"
f_new_inst_FI_LC_DATA1(enum f_instruction_code fi_code
#line 1114 "filter/f-inst.c"
  , struct f_inst * f1
#line 1118 "filter/f-inst.c"
);
#line 1118

#line 1123 "filter/f-inst.c"
 /* Constructor for FI_LC_DATA2 */
#line 1123
struct f_inst *
#line 1119 "filter/f-inst.c"
NONNULL(2)
#line 1123 "filter/f-inst.c"
f_new_inst_FI_LC_DATA2(enum f_instruction_code fi_code
#line 1119 "filter/f-inst.c"
  , struct f_inst * f1
#line 1123 "filter/f-inst.c"
);
#line 1123

#line 1157 "filter/f-inst.c"
 /* Constructor for FI_MIN */
#line 1157
struct f_inst *
#line 1124 "filter/f-inst.c"
NONNULL(2)
#line 1157 "filter/f-inst.c"
f_new_inst_FI_MIN(enum f_instruction_code fi_code
#line 1124 "filter/f-inst.c"
  , struct f_inst * f1
#line 1157 "filter/f-inst.c"
);
#line 1157

#line 1191 "filter/f-inst.c"
 /* Constructor for FI_MAX */
#line 1191
struct f_inst *
#line 1158 "filter/f-inst.c"
NONNULL(2)
#line 1191 "filter/f-inst.c"
f_new_inst_FI_MAX(enum f_instruction_code fi_code
#line 1158 "filter/f-inst.c"
  , struct f_inst * f1
#line 1191 "filter/f-inst.c"
);
#line 1191

#line 1217 "filter/f-inst.c"
 /* Constructor for FI_RETURN */
#line 1217
struct f_inst *
#line 1194 "filter/f-inst.c"
NONNULL(2)
#line 1217 "filter/f-inst.c"
f_new_inst_FI_RETURN(enum f_instruction_code fi_code
#line 1194 "filter/f-inst.c"
  , struct f_inst * f1
#line 1217 "filter/f-inst.c"
);
#line 1217

#line 1278 "filter/f-inst.c"
 /* Constructor for FI_CALL */
#line 1278
struct f_inst *
#line 1278
f_new_inst_FI_CALL(enum f_instruction_code fi_code
#line 1219 "filter/f-inst.c"
  , struct f_inst * fvar
#line 1220 "filter/f-inst.c"
  , struct symbol * sym
#line 1278 "filter/f-inst.c"
);
#line 1278

#line 1283 "filter/f-inst.c"
 /* Constructor for FI_DROP_RESULT */
#line 1283
struct f_inst *
#line 1280 "filter/f-inst.c"
NONNULL(2)
#line 1283 "filter/f-inst.c"
f_new_inst_FI_DROP_RESULT(enum f_instruction_code fi_code
#line 1280 "filter/f-inst.c"
  , struct f_inst * f1
#line 1283 "filter/f-inst.c"
);
#line 1283

#line 1306 "filter/f-inst.c"
 /* Constructor for FI_SWITCH */
#line 1306
struct f_inst *
#line 1284 "filter/f-inst.c"
NONNULL(2)
#line 1306 "filter/f-inst.c"
f_new_inst_FI_SWITCH(enum f_instruction_code fi_code
#line 1284 "filter/f-inst.c"
  , struct f_inst * f1
#line 1286 "filter/f-inst.c"
  , struct f_tree * tree
#line 1306 "filter/f-inst.c"
);
#line 1306

#line 1314 "filter/f-inst.c"
 /* Constructor for FI_IP_MASK */
#line 1314
struct f_inst *
#line 1307 "filter/f-inst.c"
NONNULL(2)
#line 1308 "filter/f-inst.c"
NONNULL(3)
#line 1314 "filter/f-inst.c"
f_new_inst_FI_IP_MASK(enum f_instruction_code fi_code
#line 1307 "filter/f-inst.c"
  , struct f_inst * f1
#line 1308 "filter/f-inst.c"
  , struct f_inst * f2
#line 1314 "filter/f-inst.c"
);
#line 1314

#line 1320 "filter/f-inst.c"
 /* Constructor for FI_PATH_PREPEND */
#line 1320
struct f_inst *
#line 1315 "filter/f-inst.c"
NONNULL(2)
#line 1316 "filter/f-inst.c"
NONNULL(3)
#line 1320 "filter/f-inst.c"
f_new_inst_FI_PATH_PREPEND(enum f_instruction_code fi_code
#line 1315 "filter/f-inst.c"
  , struct f_inst * f1
#line 1316 "filter/f-inst.c"
  , struct f_inst * f2
#line 1320 "filter/f-inst.c"
);
#line 1320

#line 1377 "filter/f-inst.c"
 /* Constructor for FI_CLIST_ADD */
#line 1377
struct f_inst *
#line 1321 "filter/f-inst.c"
NONNULL(2)
#line 1322 "filter/f-inst.c"
NONNULL(3)
#line 1377 "filter/f-inst.c"
f_new_inst_FI_CLIST_ADD(enum f_instruction_code fi_code
#line 1321 "filter/f-inst.c"
  , struct f_inst * f1
#line 1322 "filter/f-inst.c"
  , struct f_inst * f2
#line 1377 "filter/f-inst.c"
);
#line 1377

#line 1432 "filter/f-inst.c"
 /* Constructor for FI_CLIST_DEL */
#line 1432
struct f_inst *
#line 1378 "filter/f-inst.c"
NONNULL(2)
#line 1379 "filter/f-inst.c"
NONNULL(3)
#line 1432 "filter/f-inst.c"
f_new_inst_FI_CLIST_DEL(enum f_instruction_code fi_code
#line 1378 "filter/f-inst.c"
  , struct f_inst * f1
#line 1379 "filter/f-inst.c"
  , struct f_inst * f2
#line 1432 "filter/f-inst.c"
);
#line 1432

#line 1478 "filter/f-inst.c"
 /* Constructor for FI_CLIST_FILTER */
#line 1478
struct f_inst *
#line 1433 "filter/f-inst.c"
NONNULL(2)
#line 1434 "filter/f-inst.c"
NONNULL(3)
#line 1478 "filter/f-inst.c"
f_new_inst_FI_CLIST_FILTER(enum f_instruction_code fi_code
#line 1433 "filter/f-inst.c"
  , struct f_inst * f1
#line 1434 "filter/f-inst.c"
  , struct f_inst * f2
#line 1478 "filter/f-inst.c"
);
#line 1478

#line 1508 "filter/f-inst.c"
 /* Constructor for FI_ROA_CHECK_IMPLICIT */
#line 1508
struct f_inst *
#line 1508
f_new_inst_FI_ROA_CHECK_IMPLICIT(enum f_instruction_code fi_code
#line 1480 "filter/f-inst.c"
  , struct rtable_config * rtc
#line 1508 "filter/f-inst.c"
);
#line 1508

#line 1530 "filter/f-inst.c"
 /* Constructor for FI_ROA_CHECK_EXPLICIT */
#line 1530
struct f_inst *
#line 1510 "filter/f-inst.c"
NONNULL(2)
#line 1511 "filter/f-inst.c"
NONNULL(3)
#line 1530 "filter/f-inst.c"
f_new_inst_FI_ROA_CHECK_EXPLICIT(enum f_instruction_code fi_code
#line 1510 "filter/f-inst.c"
  , struct f_inst * f1
#line 1511 "filter/f-inst.c"
  , struct f_inst * f2
#line 1512 "filter/f-inst.c"
  , struct rtable_config * rtc
#line 1530 "filter/f-inst.c"
);
#line 1530

#line 1535 "filter/f-inst.c"
 /* Constructor for FI_FORMAT */
#line 1535
struct f_inst *
#line 1531 "filter/f-inst.c"
NONNULL(2)
#line 1535 "filter/f-inst.c"
f_new_inst_FI_FORMAT(enum f_instruction_code fi_code
#line 1531 "filter/f-inst.c"
  , struct f_inst * f1
#line 1535 "filter/f-inst.c"
);
#line 1535

#line 698 "filter/decl.m4"
 /* Constructor for FI_ASSERT */
#line 698
struct f_inst *
#line 1537 "filter/f-inst.c"
NONNULL(2)
#line 698 "filter/decl.m4"
f_new_inst_FI_ASSERT(enum f_instruction_code fi_code
#line 1537 "filter/f-inst.c"
  , struct f_inst * f1
#line 1539 "filter/f-inst.c"
  , char * s
#line 698 "filter/decl.m4"
);
#line 698

#line 682 "filter/decl.m4"

