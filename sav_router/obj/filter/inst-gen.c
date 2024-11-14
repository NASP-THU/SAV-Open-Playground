#line 461 "filter/decl.m4"


#if defined(__GNUC__) && __GNUC__ >= 6
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#endif

#include "nest/bird.h"
#include "filter/filter.h"
#include "filter/f-inst.h"

/* Instruction codes to string */
static const char * const f_instruction_name_str[] = {
#line 284 "filter/f-inst.c"
 /* Code enum to string for FI_ADD */
#line 284
  [FI_ADD] = "FI_ADD",
#line 289 "filter/f-inst.c"
 /* Code enum to string for FI_SUBTRACT */
#line 289
  [FI_SUBTRACT] = "FI_SUBTRACT",
#line 294 "filter/f-inst.c"
 /* Code enum to string for FI_MULTIPLY */
#line 294
  [FI_MULTIPLY] = "FI_MULTIPLY",
#line 300 "filter/f-inst.c"
 /* Code enum to string for FI_DIVIDE */
#line 300
  [FI_DIVIDE] = "FI_DIVIDE",
#line 310 "filter/f-inst.c"
 /* Code enum to string for FI_AND */
#line 310
  [FI_AND] = "FI_AND",
#line 321 "filter/f-inst.c"
 /* Code enum to string for FI_OR */
#line 321
  [FI_OR] = "FI_OR",
#line 331 "filter/f-inst.c"
 /* Code enum to string for FI_PAIR_CONSTRUCT */
#line 331
  [FI_PAIR_CONSTRUCT] = "FI_PAIR_CONSTRUCT",
#line 371 "filter/f-inst.c"
 /* Code enum to string for FI_EC_CONSTRUCT */
#line 371
  [FI_EC_CONSTRUCT] = "FI_EC_CONSTRUCT",
#line 378 "filter/f-inst.c"
 /* Code enum to string for FI_LC_CONSTRUCT */
#line 378
  [FI_LC_CONSTRUCT] = "FI_LC_CONSTRUCT",
#line 428 "filter/f-inst.c"
 /* Code enum to string for FI_PATHMASK_CONSTRUCT */
#line 428
  [FI_PATHMASK_CONSTRUCT] = "FI_PATHMASK_CONSTRUCT",
#line 435 "filter/f-inst.c"
 /* Code enum to string for FI_NEQ */
#line 435
  [FI_NEQ] = "FI_NEQ",
#line 442 "filter/f-inst.c"
 /* Code enum to string for FI_EQ */
#line 442
  [FI_EQ] = "FI_EQ",
#line 453 "filter/f-inst.c"
 /* Code enum to string for FI_LT */
#line 453
  [FI_LT] = "FI_LT",
#line 464 "filter/f-inst.c"
 /* Code enum to string for FI_LTE */
#line 464
  [FI_LTE] = "FI_LTE",
#line 469 "filter/f-inst.c"
 /* Code enum to string for FI_NOT */
#line 469
  [FI_NOT] = "FI_NOT",
#line 478 "filter/f-inst.c"
 /* Code enum to string for FI_MATCH */
#line 478
  [FI_MATCH] = "FI_MATCH",
#line 487 "filter/f-inst.c"
 /* Code enum to string for FI_NOT_MATCH */
#line 487
  [FI_NOT_MATCH] = "FI_NOT_MATCH",
#line 492 "filter/f-inst.c"
 /* Code enum to string for FI_DEFINED */
#line 492
  [FI_DEFINED] = "FI_DEFINED",
#line 504 "filter/f-inst.c"
 /* Code enum to string for FI_TYPE */
#line 504
  [FI_TYPE] = "FI_TYPE",
#line 509 "filter/f-inst.c"
 /* Code enum to string for FI_IS_V4 */
#line 509
  [FI_IS_V4] = "FI_IS_V4",
#line 522 "filter/f-inst.c"
 /* Code enum to string for FI_VAR_INIT */
#line 522
  [FI_VAR_INIT] = "FI_VAR_INIT",
#line 531 "filter/f-inst.c"
 /* Code enum to string for FI_VAR_SET */
#line 531
  [FI_VAR_SET] = "FI_VAR_SET",
#line 538 "filter/f-inst.c"
 /* Code enum to string for FI_VAR_GET */
#line 538
  [FI_VAR_GET] = "FI_VAR_GET",
#line 551 "filter/f-inst.c"
 /* Code enum to string for FI_CONSTANT */
#line 551
  [FI_CONSTANT] = "FI_CONSTANT",
#line 585 "filter/f-inst.c"
 /* Code enum to string for FI_FOR_INIT */
#line 585
  [FI_FOR_INIT] = "FI_FOR_INIT",
#line 639 "filter/f-inst.c"
 /* Code enum to string for FI_FOR_NEXT */
#line 639
  [FI_FOR_NEXT] = "FI_FOR_NEXT",
#line 647 "filter/f-inst.c"
 /* Code enum to string for FI_CONDITION */
#line 647
  [FI_CONDITION] = "FI_CONDITION",
#line 656 "filter/f-inst.c"
 /* Code enum to string for FI_PRINT */
#line 656
  [FI_PRINT] = "FI_PRINT",
#line 663 "filter/f-inst.c"
 /* Code enum to string for FI_FLUSH */
#line 663
  [FI_FLUSH] = "FI_FLUSH",
#line 677 "filter/f-inst.c"
 /* Code enum to string for FI_DIE */
#line 677
  [FI_DIE] = "FI_DIE",
#line 704 "filter/f-inst.c"
 /* Code enum to string for FI_RTA_GET */
#line 704
  [FI_RTA_GET] = "FI_RTA_GET",
#line 810 "filter/f-inst.c"
 /* Code enum to string for FI_RTA_SET */
#line 810
  [FI_RTA_SET] = "FI_RTA_SET",
#line 882 "filter/f-inst.c"
 /* Code enum to string for FI_EA_GET */
#line 882
  [FI_EA_GET] = "FI_EA_GET",
#line 949 "filter/f-inst.c"
 /* Code enum to string for FI_EA_SET */
#line 949
  [FI_EA_SET] = "FI_EA_SET",
#line 958 "filter/f-inst.c"
 /* Code enum to string for FI_EA_UNSET */
#line 958
  [FI_EA_UNSET] = "FI_EA_UNSET",
#line 970 "filter/f-inst.c"
 /* Code enum to string for FI_LENGTH */
#line 970
  [FI_LENGTH] = "FI_LENGTH",
#line 1005 "filter/f-inst.c"
 /* Code enum to string for FI_NET_SRC */
#line 1005
  [FI_NET_SRC] = "FI_NET_SRC",
#line 1040 "filter/f-inst.c"
 /* Code enum to string for FI_NET_DST */
#line 1040
  [FI_NET_DST] = "FI_NET_DST",
#line 1050 "filter/f-inst.c"
 /* Code enum to string for FI_ROA_MAXLEN */
#line 1050
  [FI_ROA_MAXLEN] = "FI_ROA_MAXLEN",
#line 1077 "filter/f-inst.c"
 /* Code enum to string for FI_ASN */
#line 1077
  [FI_ASN] = "FI_ASN",
#line 1082 "filter/f-inst.c"
 /* Code enum to string for FI_IP */
#line 1082
  [FI_IP] = "FI_IP",
#line 1089 "filter/f-inst.c"
 /* Code enum to string for FI_ROUTE_DISTINGUISHER */
#line 1089
  [FI_ROUTE_DISTINGUISHER] = "FI_ROUTE_DISTINGUISHER",
#line 1096 "filter/f-inst.c"
 /* Code enum to string for FI_AS_PATH_FIRST */
#line 1096
  [FI_AS_PATH_FIRST] = "FI_AS_PATH_FIRST",
#line 1103 "filter/f-inst.c"
 /* Code enum to string for FI_AS_PATH_LAST */
#line 1103
  [FI_AS_PATH_LAST] = "FI_AS_PATH_LAST",
#line 1108 "filter/f-inst.c"
 /* Code enum to string for FI_AS_PATH_LAST_NAG */
#line 1108
  [FI_AS_PATH_LAST_NAG] = "FI_AS_PATH_LAST_NAG",
#line 1113 "filter/f-inst.c"
 /* Code enum to string for FI_PAIR_DATA */
#line 1113
  [FI_PAIR_DATA] = "FI_PAIR_DATA",
#line 1118 "filter/f-inst.c"
 /* Code enum to string for FI_LC_DATA1 */
#line 1118
  [FI_LC_DATA1] = "FI_LC_DATA1",
#line 1123 "filter/f-inst.c"
 /* Code enum to string for FI_LC_DATA2 */
#line 1123
  [FI_LC_DATA2] = "FI_LC_DATA2",
#line 1157 "filter/f-inst.c"
 /* Code enum to string for FI_MIN */
#line 1157
  [FI_MIN] = "FI_MIN",
#line 1191 "filter/f-inst.c"
 /* Code enum to string for FI_MAX */
#line 1191
  [FI_MAX] = "FI_MAX",
#line 1217 "filter/f-inst.c"
 /* Code enum to string for FI_RETURN */
#line 1217
  [FI_RETURN] = "FI_RETURN",
#line 1278 "filter/f-inst.c"
 /* Code enum to string for FI_CALL */
#line 1278
  [FI_CALL] = "FI_CALL",
#line 1283 "filter/f-inst.c"
 /* Code enum to string for FI_DROP_RESULT */
#line 1283
  [FI_DROP_RESULT] = "FI_DROP_RESULT",
#line 1306 "filter/f-inst.c"
 /* Code enum to string for FI_SWITCH */
#line 1306
  [FI_SWITCH] = "FI_SWITCH",
#line 1314 "filter/f-inst.c"
 /* Code enum to string for FI_IP_MASK */
#line 1314
  [FI_IP_MASK] = "FI_IP_MASK",
#line 1320 "filter/f-inst.c"
 /* Code enum to string for FI_PATH_PREPEND */
#line 1320
  [FI_PATH_PREPEND] = "FI_PATH_PREPEND",
#line 1377 "filter/f-inst.c"
 /* Code enum to string for FI_CLIST_ADD */
#line 1377
  [FI_CLIST_ADD] = "FI_CLIST_ADD",
#line 1432 "filter/f-inst.c"
 /* Code enum to string for FI_CLIST_DEL */
#line 1432
  [FI_CLIST_DEL] = "FI_CLIST_DEL",
#line 1478 "filter/f-inst.c"
 /* Code enum to string for FI_CLIST_FILTER */
#line 1478
  [FI_CLIST_FILTER] = "FI_CLIST_FILTER",
#line 1508 "filter/f-inst.c"
 /* Code enum to string for FI_ROA_CHECK_IMPLICIT */
#line 1508
  [FI_ROA_CHECK_IMPLICIT] = "FI_ROA_CHECK_IMPLICIT",
#line 1530 "filter/f-inst.c"
 /* Code enum to string for FI_ROA_CHECK_EXPLICIT */
#line 1530
  [FI_ROA_CHECK_EXPLICIT] = "FI_ROA_CHECK_EXPLICIT",
#line 1535 "filter/f-inst.c"
 /* Code enum to string for FI_FORMAT */
#line 1535
  [FI_FORMAT] = "FI_FORMAT",
#line 698 "filter/decl.m4"
 /* Code enum to string for FI_ASSERT */
#line 698
  [FI_ASSERT] = "FI_ASSERT",
#line 474 "filter/decl.m4"

};

const char *
f_instruction_name_(enum f_instruction_code fi)
{
  if (fi < (sizeof(f_instruction_name_str) / sizeof(f_instruction_name_str[0])))
    return f_instruction_name_str[fi];
  else
    bug("Got unknown instruction code: %d", fi);
}

static inline struct f_inst *
fi_new(enum f_instruction_code fi_code)
{
  struct f_inst *what = cfg_allocz(sizeof(struct f_inst));
  what->lineno = ifs->lino;
  what->size = 1;
  what->fi_code = fi_code;
  return what;
}

static inline struct f_inst *
fi_constant(struct f_inst *what, struct f_val val)
{
  what->fi_code = FI_CONSTANT;
  what->i_FI_CONSTANT.val = val;
  return what;
}

static int
f_const_promotion(struct f_inst *arg, enum f_type want)
{
  if (arg->fi_code != FI_CONSTANT)
    return 0;

  struct f_val *c = &arg->i_FI_CONSTANT.val;

  if ((c->type == T_IP) && ipa_is_ip4(c->val.ip) && (want == T_QUAD)) {
    *c = (struct f_val) {
      .type = T_QUAD,
      .val.i = ipa_to_u32(c->val.ip),
    };
    return 1;
  }

  else if ((c->type == T_SET) && (!c->val.t) && (want == T_PREFIX_SET)) {
    *c = f_const_empty_prefix_set;
    return 1;
  }

  return 0;
}

#define v1 whati->f1->i_FI_CONSTANT.val
#define v2 whati->f2->i_FI_CONSTANT.val
#define v3 whati->f3->i_FI_CONSTANT.val
#define vv(i) items[i]->i_FI_CONSTANT.val
#define runtime(fmt, ...) cf_error("filter preevaluation, line %d: " fmt, ifs->lino, ##__VA_ARGS__)
#define fpool cfg_mem
#define falloc(size) cfg_alloc(size)
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
)
#line 284
  {
#line 284
    /* Allocate the structure */
#line 284
    struct f_inst *what = fi_new(fi_code);
#line 284
    uint constargs = 1;
#line 284

#line 284
    /* Initialize all the members */
#line 284
  #define whati (&(what->i_FI_ADD))
#line 284
  #line 280 "filter/f-inst.c"
whati->f1 = f1;
#line 280
const struct f_inst *child1 = f1;
#line 280
do {
#line 280
  what->size += child1->size;
#line 280

#line 280
  if (child1->fi_code != FI_CONSTANT)
#line 280
    constargs = 0;
#line 280

#line 280
} while (child1 = child1->next);
#line 280 "filter/f-inst.c"
if (f1->type && (f1->type != (T_INT)) && !f_const_promotion(f1, (T_INT)))
#line 280
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 280
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f1->type));
#line 281 "filter/f-inst.c"
whati->f2 = f2;
#line 281
const struct f_inst *child2 = f2;
#line 281
do {
#line 281
  what->size += child2->size;
#line 281

#line 281
  if (child2->fi_code != FI_CONSTANT)
#line 281
    constargs = 0;
#line 281

#line 281
} while (child2 = child2->next);
#line 281 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 281
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 281
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 282 "filter/f-inst.c"
what->type = T_INT;

#line 284 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 284
    if (!constargs)
#line 284
      return what;
#line 284

#line 284
    /* Try to pre-calculate the result */
#line 284
    #line 279 "filter/f-inst.c"
 {
    
#line 280 "filter/f-inst.c"
 
#line 280 "filter/f-inst.c"
 
#line 280 "filter/f-inst.c"
;
    
#line 281 "filter/f-inst.c"
 
#line 281 "filter/f-inst.c"
 
#line 281 "filter/f-inst.c"
;
     
#line 282 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.i + v2.val.i } );
  }
  
  #undef whati
#line 284 "filter/f-inst.c"
  }
#line 284

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
)
#line 289
  {
#line 289
    /* Allocate the structure */
#line 289
    struct f_inst *what = fi_new(fi_code);
#line 289
    uint constargs = 1;
#line 289

#line 289
    /* Initialize all the members */
#line 289
  #define whati (&(what->i_FI_SUBTRACT))
#line 289
  #line 285 "filter/f-inst.c"
whati->f1 = f1;
#line 285
const struct f_inst *child1 = f1;
#line 285
do {
#line 285
  what->size += child1->size;
#line 285

#line 285
  if (child1->fi_code != FI_CONSTANT)
#line 285
    constargs = 0;
#line 285

#line 285
} while (child1 = child1->next);
#line 285 "filter/f-inst.c"
if (f1->type && (f1->type != (T_INT)) && !f_const_promotion(f1, (T_INT)))
#line 285
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 285
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f1->type));
#line 286 "filter/f-inst.c"
whati->f2 = f2;
#line 286
const struct f_inst *child2 = f2;
#line 286
do {
#line 286
  what->size += child2->size;
#line 286

#line 286
  if (child2->fi_code != FI_CONSTANT)
#line 286
    constargs = 0;
#line 286

#line 286
} while (child2 = child2->next);
#line 286 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 286
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 286
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 287 "filter/f-inst.c"
what->type = T_INT;

#line 289 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 289
    if (!constargs)
#line 289
      return what;
#line 289

#line 289
    /* Try to pre-calculate the result */
#line 289
    #line 284 "filter/f-inst.c"
 {
    
#line 285 "filter/f-inst.c"
 
#line 285 "filter/f-inst.c"
 
#line 285 "filter/f-inst.c"
;
    
#line 286 "filter/f-inst.c"
 
#line 286 "filter/f-inst.c"
 
#line 286 "filter/f-inst.c"
;
     
#line 287 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.i - v2.val.i } );
  }
  
  #undef whati
#line 289 "filter/f-inst.c"
  }
#line 289

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
)
#line 294
  {
#line 294
    /* Allocate the structure */
#line 294
    struct f_inst *what = fi_new(fi_code);
#line 294
    uint constargs = 1;
#line 294

#line 294
    /* Initialize all the members */
#line 294
  #define whati (&(what->i_FI_MULTIPLY))
#line 294
  #line 290 "filter/f-inst.c"
whati->f1 = f1;
#line 290
const struct f_inst *child1 = f1;
#line 290
do {
#line 290
  what->size += child1->size;
#line 290

#line 290
  if (child1->fi_code != FI_CONSTANT)
#line 290
    constargs = 0;
#line 290

#line 290
} while (child1 = child1->next);
#line 290 "filter/f-inst.c"
if (f1->type && (f1->type != (T_INT)) && !f_const_promotion(f1, (T_INT)))
#line 290
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 290
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f1->type));
#line 291 "filter/f-inst.c"
whati->f2 = f2;
#line 291
const struct f_inst *child2 = f2;
#line 291
do {
#line 291
  what->size += child2->size;
#line 291

#line 291
  if (child2->fi_code != FI_CONSTANT)
#line 291
    constargs = 0;
#line 291

#line 291
} while (child2 = child2->next);
#line 291 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 291
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 291
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 292 "filter/f-inst.c"
what->type = T_INT;

#line 294 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 294
    if (!constargs)
#line 294
      return what;
#line 294

#line 294
    /* Try to pre-calculate the result */
#line 294
    #line 289 "filter/f-inst.c"
 {
    
#line 290 "filter/f-inst.c"
 
#line 290 "filter/f-inst.c"
 
#line 290 "filter/f-inst.c"
;
    
#line 291 "filter/f-inst.c"
 
#line 291 "filter/f-inst.c"
 
#line 291 "filter/f-inst.c"
;
     
#line 292 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.i * v2.val.i } );
  }
  
  #undef whati
#line 294 "filter/f-inst.c"
  }
#line 294

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
)
#line 300
  {
#line 300
    /* Allocate the structure */
#line 300
    struct f_inst *what = fi_new(fi_code);
#line 300
    uint constargs = 1;
#line 300

#line 300
    /* Initialize all the members */
#line 300
  #define whati (&(what->i_FI_DIVIDE))
#line 300
  #line 295 "filter/f-inst.c"
whati->f1 = f1;
#line 295
const struct f_inst *child1 = f1;
#line 295
do {
#line 295
  what->size += child1->size;
#line 295

#line 295
  if (child1->fi_code != FI_CONSTANT)
#line 295
    constargs = 0;
#line 295

#line 295
} while (child1 = child1->next);
#line 295 "filter/f-inst.c"
if (f1->type && (f1->type != (T_INT)) && !f_const_promotion(f1, (T_INT)))
#line 295
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 295
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f1->type));
#line 296 "filter/f-inst.c"
whati->f2 = f2;
#line 296
const struct f_inst *child2 = f2;
#line 296
do {
#line 296
  what->size += child2->size;
#line 296

#line 296
  if (child2->fi_code != FI_CONSTANT)
#line 296
    constargs = 0;
#line 296

#line 296
} while (child2 = child2->next);
#line 296 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 296
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 296
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 298 "filter/f-inst.c"
what->type = T_INT;

#line 300 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 300
    if (!constargs)
#line 300
      return what;
#line 300

#line 300
    /* Try to pre-calculate the result */
#line 300
    #line 294 "filter/f-inst.c"
 {
    
#line 295 "filter/f-inst.c"
 
#line 295 "filter/f-inst.c"
 
#line 295 "filter/f-inst.c"
;
    
#line 296 "filter/f-inst.c"
 
#line 296 "filter/f-inst.c"
 
#line 296 "filter/f-inst.c"
;
    if (v2.val.i == 0) runtime( "Mother told me not to divide by 0" );
     
#line 298 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.i / v2.val.i } );
  }
  
  #undef whati
#line 300 "filter/f-inst.c"
  }
#line 300

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
)
#line 310
  {
#line 310
    /* Allocate the structure */
#line 310
    struct f_inst *what = fi_new(fi_code);
#line 310
    uint constargs = 1;
#line 310

#line 310
    /* Initialize all the members */
#line 310
  #define whati (&(what->i_FI_AND))
#line 310
  #line 301 "filter/f-inst.c"
whati->f1 = f1;
#line 301
const struct f_inst *child1 = f1;
#line 301
do {
#line 301
  what->size += child1->size;
#line 301

#line 301
  if (child1->fi_code != FI_CONSTANT)
#line 301
    constargs = 0;
#line 301

#line 301
} while (child1 = child1->next);
#line 301 "filter/f-inst.c"
if (f1->type && (f1->type != (T_BOOL)) && !f_const_promotion(f1, (T_BOOL)))
#line 301
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 301
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(f1->type));
#line 302 "filter/f-inst.c"
if (f2->type && (f2->type != (T_BOOL)) && !f_const_promotion(f2, (T_BOOL)))
#line 302
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 302
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(f2->type));
#line 303 "filter/f-inst.c"
what->type = T_BOOL;
#line 306 "filter/f-inst.c"
whati->f2 = f2;

#line 310 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 310
    if (!constargs)
#line 310
      return what;
#line 310

#line 310
    /* Try to pre-calculate the result */
#line 310
    #line 300 "filter/f-inst.c"
 {
    
#line 301 "filter/f-inst.c"
 
#line 301 "filter/f-inst.c"
 
#line 301 "filter/f-inst.c"
;
    
#line 302 "filter/f-inst.c"
;
     
#line 303 "filter/f-inst.c"
;

    if (v1.val.i)
      
#line 306 "filter/f-inst.c"
return whati->f2
#line 306
;
    else
      return fi_constant(what, v1);
  }
  
  #undef whati
#line 310 "filter/f-inst.c"
  }
#line 310

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
)
#line 321
  {
#line 321
    /* Allocate the structure */
#line 321
    struct f_inst *what = fi_new(fi_code);
#line 321
    uint constargs = 1;
#line 321

#line 321
    /* Initialize all the members */
#line 321
  #define whati (&(what->i_FI_OR))
#line 321
  #line 311 "filter/f-inst.c"
whati->f1 = f1;
#line 311
const struct f_inst *child1 = f1;
#line 311
do {
#line 311
  what->size += child1->size;
#line 311

#line 311
  if (child1->fi_code != FI_CONSTANT)
#line 311
    constargs = 0;
#line 311

#line 311
} while (child1 = child1->next);
#line 311 "filter/f-inst.c"
if (f1->type && (f1->type != (T_BOOL)) && !f_const_promotion(f1, (T_BOOL)))
#line 311
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 311
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(f1->type));
#line 312 "filter/f-inst.c"
if (f2->type && (f2->type != (T_BOOL)) && !f_const_promotion(f2, (T_BOOL)))
#line 312
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 312
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(f2->type));
#line 313 "filter/f-inst.c"
what->type = T_BOOL;
#line 316 "filter/f-inst.c"
whati->f2 = f2;

#line 321 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 321
    if (!constargs)
#line 321
      return what;
#line 321

#line 321
    /* Try to pre-calculate the result */
#line 321
    #line 310 "filter/f-inst.c"
 {
    
#line 311 "filter/f-inst.c"
 
#line 311 "filter/f-inst.c"
 
#line 311 "filter/f-inst.c"
;
    
#line 312 "filter/f-inst.c"
;
     
#line 313 "filter/f-inst.c"
;

    if (!v1.val.i)
      
#line 316 "filter/f-inst.c"
return whati->f2
#line 316
;
    else
      return fi_constant(what, v1);
  }

  
  #undef whati
#line 321 "filter/f-inst.c"
  }
#line 321

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
)
#line 331
  {
#line 331
    /* Allocate the structure */
#line 331
    struct f_inst *what = fi_new(fi_code);
#line 331
    uint constargs = 1;
#line 331

#line 331
    /* Initialize all the members */
#line 331
  #define whati (&(what->i_FI_PAIR_CONSTRUCT))
#line 331
  #line 322 "filter/f-inst.c"
whati->f1 = f1;
#line 322
const struct f_inst *child1 = f1;
#line 322
do {
#line 322
  what->size += child1->size;
#line 322

#line 322
  if (child1->fi_code != FI_CONSTANT)
#line 322
    constargs = 0;
#line 322

#line 322
} while (child1 = child1->next);
#line 322 "filter/f-inst.c"
if (f1->type && (f1->type != (T_INT)) && !f_const_promotion(f1, (T_INT)))
#line 322
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 322
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f1->type));
#line 323 "filter/f-inst.c"
whati->f2 = f2;
#line 323
const struct f_inst *child2 = f2;
#line 323
do {
#line 323
  what->size += child2->size;
#line 323

#line 323
  if (child2->fi_code != FI_CONSTANT)
#line 323
    constargs = 0;
#line 323

#line 323
} while (child2 = child2->next);
#line 323 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 323
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 323
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 328 "filter/f-inst.c"
what->type = T_PAIR;

#line 331 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 331
    if (!constargs)
#line 331
      return what;
#line 331

#line 331
    /* Try to pre-calculate the result */
#line 331
    #line 321 "filter/f-inst.c"
 {
    
#line 322 "filter/f-inst.c"
 
#line 322 "filter/f-inst.c"
 
#line 322 "filter/f-inst.c"
;
    
#line 323 "filter/f-inst.c"
 
#line 323 "filter/f-inst.c"
 
#line 323 "filter/f-inst.c"
;
    uint u1 = v1.val.i;
    uint u2 = v2.val.i;
    if ((u1 > 0xFFFF) || (u2 > 0xFFFF))
      runtime( "Can't operate with value out of bounds in pair constructor" );
     
#line 328 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_PAIR, .val.i = (u1 << 16) | u2 } );
  }

  
  #undef whati
#line 331 "filter/f-inst.c"
  }
#line 331

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
)
#line 371
  {
#line 371
    /* Allocate the structure */
#line 371
    struct f_inst *what = fi_new(fi_code);
#line 371
    uint constargs = 1;
#line 371

#line 371
    /* Initialize all the members */
#line 371
  #define whati (&(what->i_FI_EC_CONSTRUCT))
#line 371
  #line 332 "filter/f-inst.c"
whati->f1 = f1;
#line 332
const struct f_inst *child1 = f1;
#line 332
do {
#line 332
  what->size += child1->size;
#line 332

#line 332
  if (child1->fi_code != FI_CONSTANT)
#line 332
    constargs = 0;
#line 332

#line 332
} while (child1 = child1->next);
#line 333 "filter/f-inst.c"
whati->f2 = f2;
#line 333
const struct f_inst *child2 = f2;
#line 333
do {
#line 333
  what->size += child2->size;
#line 333

#line 333
  if (child2->fi_code != FI_CONSTANT)
#line 333
    constargs = 0;
#line 333

#line 333
} while (child2 = child2->next);
#line 333 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 333
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 333
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 335 "filter/f-inst.c"
whati->ecs = ecs;
#line 356 "filter/f-inst.c"
what->type = T_EC;

#line 371 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 371
    if (!constargs)
#line 371
      return what;
#line 371

#line 371
    /* Try to pre-calculate the result */
#line 371
    #line 331 "filter/f-inst.c"
 {
    
#line 332 "filter/f-inst.c"
;
    
#line 333 "filter/f-inst.c"
 
#line 333 "filter/f-inst.c"
 
#line 333 "filter/f-inst.c"
;

    #line 335 "filter/f-inst.c"
;

    int ipv4_used;
    u32 key, val;

    if (v1.type == T_INT) {
      ipv4_used = 0; key = v1.val.i;
    }
    else if (v1.type == T_QUAD) {
      ipv4_used = 1; key = v1.val.i;
    }
    /* IP->Quad implicit conversion */
    else if (val_is_ip4(&v1)) {
      ipv4_used = 1; key = ipa_to_u32(v1.val.ip);
    }
    else
      runtime("Argument 1 of EC constructor must be integer or IPv4 address, got 0x%02x", v1.type);

    val = v2.val.i;

    if (ecs == EC_GENERIC)
       
#line 356 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_EC, .val.ec = ec_generic(key, val) } );
    else if (ipv4_used)
      if (val <= 0xFFFF)
	 return fi_constant(what,  (struct f_val) { .type = T_EC, .val.ec = ec_ip4(ecs, key, val) } );
      else
	runtime("4-byte value %u can't be used with IP-address key in extended community", val);
    else if (key < 0x10000)
       return fi_constant(what,  (struct f_val) { .type = T_EC, .val.ec = ec_as2(ecs, key, val) } );
    else
      if (val <= 0xFFFF)
	 return fi_constant(what,  (struct f_val) { .type = T_EC, .val.ec = ec_as4(ecs, key, val) } );
      else
	runtime("4-byte value %u can't be used with 4-byte ASN in extended community", val);
  }

  
  #undef whati
#line 371 "filter/f-inst.c"
  }
#line 371

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
)
#line 378
  {
#line 378
    /* Allocate the structure */
#line 378
    struct f_inst *what = fi_new(fi_code);
#line 378
    uint constargs = 1;
#line 378

#line 378
    /* Initialize all the members */
#line 378
  #define whati (&(what->i_FI_LC_CONSTRUCT))
#line 378
  #line 372 "filter/f-inst.c"
whati->f1 = f1;
#line 372
const struct f_inst *child1 = f1;
#line 372
do {
#line 372
  what->size += child1->size;
#line 372

#line 372
  if (child1->fi_code != FI_CONSTANT)
#line 372
    constargs = 0;
#line 372

#line 372
} while (child1 = child1->next);
#line 372 "filter/f-inst.c"
if (f1->type && (f1->type != (T_INT)) && !f_const_promotion(f1, (T_INT)))
#line 372
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 372
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f1->type));
#line 373 "filter/f-inst.c"
whati->f2 = f2;
#line 373
const struct f_inst *child2 = f2;
#line 373
do {
#line 373
  what->size += child2->size;
#line 373

#line 373
  if (child2->fi_code != FI_CONSTANT)
#line 373
    constargs = 0;
#line 373

#line 373
} while (child2 = child2->next);
#line 373 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 373
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 373
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 374 "filter/f-inst.c"
whati->f3 = f3;
#line 374
const struct f_inst *child3 = f3;
#line 374
do {
#line 374
  what->size += child3->size;
#line 374

#line 374
  if (child3->fi_code != FI_CONSTANT)
#line 374
    constargs = 0;
#line 374

#line 374
} while (child3 = child3->next);
#line 374 "filter/f-inst.c"
if (f3->type && (f3->type != (T_INT)) && !f_const_promotion(f3, (T_INT)))
#line 374
  cf_error("Argument 3 of %s must be of type %s, got type %s",
#line 374
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f3->type));
#line 375 "filter/f-inst.c"
what->type = T_LC;

#line 378 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 378
    if (!constargs)
#line 378
      return what;
#line 378

#line 378
    /* Try to pre-calculate the result */
#line 378
    #line 371 "filter/f-inst.c"
 {
    
#line 372 "filter/f-inst.c"
 
#line 372 "filter/f-inst.c"
 
#line 372 "filter/f-inst.c"
;
    
#line 373 "filter/f-inst.c"
 
#line 373 "filter/f-inst.c"
 
#line 373 "filter/f-inst.c"
;
    
#line 374 "filter/f-inst.c"
 
#line 374 "filter/f-inst.c"
 
#line 374 "filter/f-inst.c"
;
     
#line 375 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_LC, .val.lc = (lcomm) { v1.val.i, v2.val.i, v3.val.i } } );
  }

  
  #undef whati
#line 378 "filter/f-inst.c"
  }
#line 378

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
)
#line 428
  {
#line 428
    /* Allocate the structure */
#line 428
    struct f_inst *what = fi_new(fi_code);
#line 428
    uint constargs = 1;
#line 428

#line 428
    /* Initialize all the members */
#line 428
  #define whati (&(what->i_FI_PATHMASK_CONSTRUCT))
#line 428
  #line 379 "filter/f-inst.c"
whati->varcount = 0;
#line 379
whati->fvar = fvar;
#line 379
for (const struct f_inst *child = fvar; child; child = child->next, whati->varcount++) {
#line 379
  what->size += child->size;
#line 379

#line 379
  if (child->fi_code != FI_CONSTANT)
#line 379
    constargs = 0;
#line 379

#line 379
}
#line 379

#line 379
  const struct f_inst **items = NULL;
#line 379
  if (constargs && whati->varcount) {
#line 379
    items = alloca(whati->varcount * sizeof(struct f_inst *));
#line 379
    const struct f_inst *child = fvar;
#line 379
    for (uint i=0; child; i++)
#line 379
      child = (items[i] = child)->next;
#line 379
  }
#line 379

#line 423 "filter/f-inst.c"
what->type = T_PATH_MASK;

#line 428 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 428
    if (!constargs)
#line 428
      return what;
#line 428

#line 428
    /* Try to pre-calculate the result */
#line 428
    #line 378 "filter/f-inst.c"
 {
    
#line 379 "filter/f-inst.c"

#line 379

#line 379
;

    struct f_path_mask *pm = falloc(sizeof(struct f_path_mask) + whati->varcount * sizeof(struct f_path_mask_item));
    pm->len = whati->varcount;

    for (uint i=0; i<whati->varcount; i++) {
      switch (vv(i).type) {
	case T_PATH_MASK_ITEM:
	  if (vv(i).val.pmi.kind == PM_LOOP)
	  {
	    if (i == 0)
	      runtime("Path mask iterator '+' cannot be first");

	    /* We want PM_LOOP as prefix operator */
	    pm->item[i] = pm->item[i - 1];
	    pm->item[i - 1] = vv(i).val.pmi;
	    break;
	  }

	  pm->item[i] = vv(i).val.pmi;
	  break;

	case T_INT:
	  pm->item[i] = (struct f_path_mask_item) {
	    .asn = vv(i).val.i,
	    .kind = PM_ASN,
	  };
	  break;

	case T_SET:
	  if (!path_set_type(vv(i).val.t))
	    runtime("Only integer sets allowed in path mask");

	  pm->item[i] = (struct f_path_mask_item) {
	    .set = vv(i).val.t,
	    .kind = PM_ASN_SET,
	  };
	  break;

	default:
	  runtime( "Error resolving path mask template: value not an integer" );
      }
    }

     
#line 423 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_PATH_MASK, .val.path_mask = pm } );
  }

/* Relational operators */

  
  #undef whati
#line 428 "filter/f-inst.c"
  }
#line 428

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
)
#line 435
  {
#line 435
    /* Allocate the structure */
#line 435
    struct f_inst *what = fi_new(fi_code);
#line 435
    uint constargs = 1;
#line 435

#line 435
    /* Initialize all the members */
#line 435
  #define whati (&(what->i_FI_NEQ))
#line 435
  #line 429 "filter/f-inst.c"
whati->f1 = f1;
#line 429
const struct f_inst *child1 = f1;
#line 429
do {
#line 429
  what->size += child1->size;
#line 429

#line 429
  if (child1->fi_code != FI_CONSTANT)
#line 429
    constargs = 0;
#line 429

#line 429
} while (child1 = child1->next);
#line 430 "filter/f-inst.c"
whati->f2 = f2;
#line 430
const struct f_inst *child2 = f2;
#line 430
do {
#line 430
  what->size += child2->size;
#line 430

#line 430
  if (child2->fi_code != FI_CONSTANT)
#line 430
    constargs = 0;
#line 430

#line 430
} while (child2 = child2->next);
#line 431 "filter/f-inst.c"
if (f1->type && f2->type && (f1->type != f2->type))
#line 431
   (void) (f_const_promotion(f2, f1->type) || f_const_promotion(f1, f2->type));
#line 432 "filter/f-inst.c"
what->type = T_BOOL;

#line 435 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 435
    if (!constargs)
#line 435
      return what;
#line 435

#line 435
    /* Try to pre-calculate the result */
#line 435
    #line 428 "filter/f-inst.c"
 {
    
#line 429 "filter/f-inst.c"
;
    
#line 430 "filter/f-inst.c"
;
    
#line 431 "filter/f-inst.c"
;
     
#line 432 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = !val_same(&v1, &v2) } );
  }

  
  #undef whati
#line 435 "filter/f-inst.c"
  }
#line 435

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
)
#line 442
  {
#line 442
    /* Allocate the structure */
#line 442
    struct f_inst *what = fi_new(fi_code);
#line 442
    uint constargs = 1;
#line 442

#line 442
    /* Initialize all the members */
#line 442
  #define whati (&(what->i_FI_EQ))
#line 442
  #line 436 "filter/f-inst.c"
whati->f1 = f1;
#line 436
const struct f_inst *child1 = f1;
#line 436
do {
#line 436
  what->size += child1->size;
#line 436

#line 436
  if (child1->fi_code != FI_CONSTANT)
#line 436
    constargs = 0;
#line 436

#line 436
} while (child1 = child1->next);
#line 437 "filter/f-inst.c"
whati->f2 = f2;
#line 437
const struct f_inst *child2 = f2;
#line 437
do {
#line 437
  what->size += child2->size;
#line 437

#line 437
  if (child2->fi_code != FI_CONSTANT)
#line 437
    constargs = 0;
#line 437

#line 437
} while (child2 = child2->next);
#line 438 "filter/f-inst.c"
if (f1->type && f2->type && (f1->type != f2->type))
#line 438
   (void) (f_const_promotion(f2, f1->type) || f_const_promotion(f1, f2->type));
#line 439 "filter/f-inst.c"
what->type = T_BOOL;

#line 442 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 442
    if (!constargs)
#line 442
      return what;
#line 442

#line 442
    /* Try to pre-calculate the result */
#line 442
    #line 435 "filter/f-inst.c"
 {
    
#line 436 "filter/f-inst.c"
;
    
#line 437 "filter/f-inst.c"
;
    
#line 438 "filter/f-inst.c"
;
     
#line 439 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = val_same(&v1, &v2) } );
  }

  
  #undef whati
#line 442 "filter/f-inst.c"
  }
#line 442

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
)
#line 453
  {
#line 453
    /* Allocate the structure */
#line 453
    struct f_inst *what = fi_new(fi_code);
#line 453
    uint constargs = 1;
#line 453

#line 453
    /* Initialize all the members */
#line 453
  #define whati (&(what->i_FI_LT))
#line 453
  #line 443 "filter/f-inst.c"
whati->f1 = f1;
#line 443
const struct f_inst *child1 = f1;
#line 443
do {
#line 443
  what->size += child1->size;
#line 443

#line 443
  if (child1->fi_code != FI_CONSTANT)
#line 443
    constargs = 0;
#line 443

#line 443
} while (child1 = child1->next);
#line 444 "filter/f-inst.c"
whati->f2 = f2;
#line 444
const struct f_inst *child2 = f2;
#line 444
do {
#line 444
  what->size += child2->size;
#line 444

#line 444
  if (child2->fi_code != FI_CONSTANT)
#line 444
    constargs = 0;
#line 444

#line 444
} while (child2 = child2->next);
#line 445 "filter/f-inst.c"
if (f1->type && f2->type && (f1->type != f2->type) &&
#line 445
   !f_const_promotion(f2, f1->type) && !f_const_promotion(f1, f2->type))
#line 445
  cf_error("Arguments 1 and 2 of %s must be of the same type", f_instruction_name(what->fi_code));
#line 450 "filter/f-inst.c"
what->type = T_BOOL;

#line 453 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 453
    if (!constargs)
#line 453
      return what;
#line 453

#line 453
    /* Try to pre-calculate the result */
#line 453
    #line 442 "filter/f-inst.c"
 {
    
#line 443 "filter/f-inst.c"
;
    
#line 444 "filter/f-inst.c"
;
    
#line 445 "filter/f-inst.c"
;

    int i = val_compare(&v1, &v2);
    if (i == F_CMP_ERROR)
      runtime( "Can't compare values of incompatible types" );
     
#line 450 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = (i == -1) } );
  }

  
  #undef whati
#line 453 "filter/f-inst.c"
  }
#line 453

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
)
#line 464
  {
#line 464
    /* Allocate the structure */
#line 464
    struct f_inst *what = fi_new(fi_code);
#line 464
    uint constargs = 1;
#line 464

#line 464
    /* Initialize all the members */
#line 464
  #define whati (&(what->i_FI_LTE))
#line 464
  #line 454 "filter/f-inst.c"
whati->f1 = f1;
#line 454
const struct f_inst *child1 = f1;
#line 454
do {
#line 454
  what->size += child1->size;
#line 454

#line 454
  if (child1->fi_code != FI_CONSTANT)
#line 454
    constargs = 0;
#line 454

#line 454
} while (child1 = child1->next);
#line 455 "filter/f-inst.c"
whati->f2 = f2;
#line 455
const struct f_inst *child2 = f2;
#line 455
do {
#line 455
  what->size += child2->size;
#line 455

#line 455
  if (child2->fi_code != FI_CONSTANT)
#line 455
    constargs = 0;
#line 455

#line 455
} while (child2 = child2->next);
#line 456 "filter/f-inst.c"
if (f1->type && f2->type && (f1->type != f2->type) &&
#line 456
   !f_const_promotion(f2, f1->type) && !f_const_promotion(f1, f2->type))
#line 456
  cf_error("Arguments 1 and 2 of %s must be of the same type", f_instruction_name(what->fi_code));
#line 461 "filter/f-inst.c"
what->type = T_BOOL;

#line 464 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 464
    if (!constargs)
#line 464
      return what;
#line 464

#line 464
    /* Try to pre-calculate the result */
#line 464
    #line 453 "filter/f-inst.c"
 {
    
#line 454 "filter/f-inst.c"
;
    
#line 455 "filter/f-inst.c"
;
    
#line 456 "filter/f-inst.c"
;

    int i = val_compare(&v1, &v2);
    if (i == F_CMP_ERROR)
      runtime( "Can't compare values of incompatible types" );
     
#line 461 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = (i != 1) } );
  }

  
  #undef whati
#line 464 "filter/f-inst.c"
  }
#line 464

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
)
#line 469
  {
#line 469
    /* Allocate the structure */
#line 469
    struct f_inst *what = fi_new(fi_code);
#line 469
    uint constargs = 1;
#line 469

#line 469
    /* Initialize all the members */
#line 469
  #define whati (&(what->i_FI_NOT))
#line 469
  #line 465 "filter/f-inst.c"
whati->f1 = f1;
#line 465
const struct f_inst *child1 = f1;
#line 465
do {
#line 465
  what->size += child1->size;
#line 465

#line 465
  if (child1->fi_code != FI_CONSTANT)
#line 465
    constargs = 0;
#line 465

#line 465
} while (child1 = child1->next);
#line 465 "filter/f-inst.c"
if (f1->type && (f1->type != (T_BOOL)) && !f_const_promotion(f1, (T_BOOL)))
#line 465
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 465
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(f1->type));
#line 466 "filter/f-inst.c"
what->type = T_BOOL;

#line 469 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 469
    if (!constargs)
#line 469
      return what;
#line 469

#line 469
    /* Try to pre-calculate the result */
#line 469
    #line 464 "filter/f-inst.c"
 {
    
#line 465 "filter/f-inst.c"
 
#line 465 "filter/f-inst.c"
 
#line 465 "filter/f-inst.c"
;
     
#line 466 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = !v1.val.i } );
  }

  
  #undef whati
#line 469 "filter/f-inst.c"
  }
#line 469

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
)
#line 478
  {
#line 478
    /* Allocate the structure */
#line 478
    struct f_inst *what = fi_new(fi_code);
#line 478
    uint constargs = 1;
#line 478

#line 478
    /* Initialize all the members */
#line 478
  #define whati (&(what->i_FI_MATCH))
#line 478
  #line 470 "filter/f-inst.c"
whati->f1 = f1;
#line 470
const struct f_inst *child1 = f1;
#line 470
do {
#line 470
  what->size += child1->size;
#line 470

#line 470
  if (child1->fi_code != FI_CONSTANT)
#line 470
    constargs = 0;
#line 470

#line 470
} while (child1 = child1->next);
#line 471 "filter/f-inst.c"
whati->f2 = f2;
#line 471
const struct f_inst *child2 = f2;
#line 471
do {
#line 471
  what->size += child2->size;
#line 471

#line 471
  if (child2->fi_code != FI_CONSTANT)
#line 471
    constargs = 0;
#line 471

#line 471
} while (child2 = child2->next);
#line 475 "filter/f-inst.c"
what->type = T_BOOL;

#line 478 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 478
    if (!constargs)
#line 478
      return what;
#line 478

#line 478
    /* Try to pre-calculate the result */
#line 478
    #line 469 "filter/f-inst.c"
 {
    
#line 470 "filter/f-inst.c"
;
    
#line 471 "filter/f-inst.c"
;
    int i = val_in_range(&v1, &v2);
    if (i == F_CMP_ERROR)
      runtime( "~ applied on unknown type pair" );
     
#line 475 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = !!i } );
  }

  
  #undef whati
#line 478 "filter/f-inst.c"
  }
#line 478

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
)
#line 487
  {
#line 487
    /* Allocate the structure */
#line 487
    struct f_inst *what = fi_new(fi_code);
#line 487
    uint constargs = 1;
#line 487

#line 487
    /* Initialize all the members */
#line 487
  #define whati (&(what->i_FI_NOT_MATCH))
#line 487
  #line 479 "filter/f-inst.c"
whati->f1 = f1;
#line 479
const struct f_inst *child1 = f1;
#line 479
do {
#line 479
  what->size += child1->size;
#line 479

#line 479
  if (child1->fi_code != FI_CONSTANT)
#line 479
    constargs = 0;
#line 479

#line 479
} while (child1 = child1->next);
#line 480 "filter/f-inst.c"
whati->f2 = f2;
#line 480
const struct f_inst *child2 = f2;
#line 480
do {
#line 480
  what->size += child2->size;
#line 480

#line 480
  if (child2->fi_code != FI_CONSTANT)
#line 480
    constargs = 0;
#line 480

#line 480
} while (child2 = child2->next);
#line 484 "filter/f-inst.c"
what->type = T_BOOL;

#line 487 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 487
    if (!constargs)
#line 487
      return what;
#line 487

#line 487
    /* Try to pre-calculate the result */
#line 487
    #line 478 "filter/f-inst.c"
 {
    
#line 479 "filter/f-inst.c"
;
    
#line 480 "filter/f-inst.c"
;
    int i = val_in_range(&v1, &v2);
    if (i == F_CMP_ERROR)
      runtime( "!~ applied on unknown type pair" );
     
#line 484 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = !i } );
  }

  
  #undef whati
#line 487 "filter/f-inst.c"
  }
#line 487

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
)
#line 492
  {
#line 492
    /* Allocate the structure */
#line 492
    struct f_inst *what = fi_new(fi_code);
#line 492
    uint constargs = 1;
#line 492

#line 492
    /* Initialize all the members */
#line 492
  #define whati (&(what->i_FI_DEFINED))
#line 492
  #line 488 "filter/f-inst.c"
whati->f1 = f1;
#line 488
const struct f_inst *child1 = f1;
#line 488
do {
#line 488
  what->size += child1->size;
#line 488

#line 488
  if (child1->fi_code != FI_CONSTANT)
#line 488
    constargs = 0;
#line 488

#line 488
} while (child1 = child1->next);
#line 489 "filter/f-inst.c"
what->type = T_BOOL;

#line 492 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 492
    if (!constargs)
#line 492
      return what;
#line 492

#line 492
    /* Try to pre-calculate the result */
#line 492
    #line 487 "filter/f-inst.c"
 {
    
#line 488 "filter/f-inst.c"
;
     
#line 489 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = (v1.type != T_VOID) && !undef_value(v1) } );
  }

  
  #undef whati
#line 492 "filter/f-inst.c"
  }
#line 492

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
)
#line 504
  {
#line 504
    /* Allocate the structure */
#line 504
    struct f_inst *what = fi_new(fi_code);
#line 504
    uint constargs = 1;
#line 504

#line 504
    /* Initialize all the members */
#line 504
  #define whati (&(what->i_FI_TYPE))
#line 504
  #line 493 "filter/f-inst.c"
whati->f1 = f1;
#line 493
const struct f_inst *child1 = f1;
#line 493
do {
#line 493
  what->size += child1->size;
#line 493

#line 493
  if (child1->fi_code != FI_CONSTANT)
#line 493
    constargs = 0;
#line 493

#line 493
} while (child1 = child1->next);
#line 497 "filter/f-inst.c"
what->type = T_ENUM_NETTYPE;

#line 504 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 504
    if (!constargs)
#line 504
      return what;
#line 504

#line 504
    /* Try to pre-calculate the result */
#line 504
    #line 492 "filter/f-inst.c"
 {
    
#line 493 "filter/f-inst.c"
; /* There may be more types supporting this operation */
    switch (v1.type)
    {
      case T_NET:
	 
#line 497 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_ENUM_NETTYPE, .val.i = v1.val.net->type } );
	break;
      default:
	runtime( "Can't determine type of this item" );
    }
  }

  
  #undef whati
#line 504 "filter/f-inst.c"
  }
#line 504

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
)
#line 509
  {
#line 509
    /* Allocate the structure */
#line 509
    struct f_inst *what = fi_new(fi_code);
#line 509
    uint constargs = 1;
#line 509

#line 509
    /* Initialize all the members */
#line 509
  #define whati (&(what->i_FI_IS_V4))
#line 509
  #line 505 "filter/f-inst.c"
whati->f1 = f1;
#line 505
const struct f_inst *child1 = f1;
#line 505
do {
#line 505
  what->size += child1->size;
#line 505

#line 505
  if (child1->fi_code != FI_CONSTANT)
#line 505
    constargs = 0;
#line 505

#line 505
} while (child1 = child1->next);
#line 505 "filter/f-inst.c"
if (f1->type && (f1->type != (T_IP)) && !f_const_promotion(f1, (T_IP)))
#line 505
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 505
	   f_instruction_name(what->fi_code), f_type_name(T_IP), f_type_name(f1->type));
#line 506 "filter/f-inst.c"
what->type = T_BOOL;

#line 509 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 509
    if (!constargs)
#line 509
      return what;
#line 509

#line 509
    /* Try to pre-calculate the result */
#line 509
    #line 504 "filter/f-inst.c"
 {
    
#line 505 "filter/f-inst.c"
 
#line 505 "filter/f-inst.c"
 
#line 505 "filter/f-inst.c"
;
     
#line 506 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_BOOL, .val.i = ipa_is_ip4(v1.val.ip) } );
  }

  
  #undef whati
#line 509 "filter/f-inst.c"
  }
#line 509

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
)
#line 522
  {
#line 522
    /* Allocate the structure */
#line 522
    struct f_inst *what = fi_new(fi_code);
#line 522
    
#line 522

#line 522
    /* Initialize all the members */
#line 522
  #define whati (&(what->i_FI_VAR_INIT))
#line 522
  #line 511 "filter/f-inst.c"
whati->f1 = f1;
#line 511
const struct f_inst *child1 = f1;
#line 511
do {
#line 511
  what->size += child1->size;
#line 511

#line 511
} while (child1 = child1->next);
#line 512 "filter/f-inst.c"
whati->sym = sym;
#line 513 "filter/f-inst.c"
if (f1->type && (f1->type != (sym->class & 0xff)) && !f_const_promotion(f1, (sym->class & 0xff)))
#line 513
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 513
	   f_instruction_name(what->fi_code), f_type_name(sym->class & 0xff), f_type_name(f1->type));

#line 522 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 522
    
#line 522
      return what;
#line 522

#line 522
    /* Try to pre-calculate the result */
#line 522
      #undef whati
#line 522
  }
#line 522

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
)
#line 531
  {
#line 531
    /* Allocate the structure */
#line 531
    struct f_inst *what = fi_new(fi_code);
#line 531
    
#line 531

#line 531
    /* Initialize all the members */
#line 531
  #define whati (&(what->i_FI_VAR_SET))
#line 531
  #line 524 "filter/f-inst.c"
whati->f1 = f1;
#line 524
const struct f_inst *child1 = f1;
#line 524
do {
#line 524
  what->size += child1->size;
#line 524

#line 524
} while (child1 = child1->next);
#line 525 "filter/f-inst.c"
whati->sym = sym;
#line 526 "filter/f-inst.c"
if (f1->type && (f1->type != (sym->class & 0xff)) && !f_const_promotion(f1, (sym->class & 0xff)))
#line 526
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 526
	   f_instruction_name(what->fi_code), f_type_name(sym->class & 0xff), f_type_name(f1->type));

#line 531 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 531
    
#line 531
      return what;
#line 531

#line 531
    /* Try to pre-calculate the result */
#line 531
      #undef whati
#line 531
  }
#line 531

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
)
#line 538
  {
#line 538
    /* Allocate the structure */
#line 538
    struct f_inst *what = fi_new(fi_code);
#line 538
    
#line 538

#line 538
    /* Initialize all the members */
#line 538
  #define whati (&(what->i_FI_VAR_GET))
#line 538
  #line 532 "filter/f-inst.c"
whati->sym = sym;
#line 534 "filter/f-inst.c"
what->type = sym->class & 0xff;

#line 538 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 538
    
#line 538
      return what;
#line 538

#line 538
    /* Try to pre-calculate the result */
#line 538
      #undef whati
#line 538
  }
#line 538

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
)
#line 551
  {
#line 551
    /* Allocate the structure */
#line 551
    struct f_inst *what = fi_new(fi_code);
#line 551
    uint constargs = 1;
#line 551

#line 551
    /* Initialize all the members */
#line 551
  #define whati (&(what->i_FI_CONSTANT))
#line 551
  #line 539 "filter/f-inst.c"
whati->val = val;
#line 547 "filter/f-inst.c"
what->type = val.type;

#line 551 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 551
    if (!constargs)
#line 551
      return what;
#line 551

#line 551
    /* Try to pre-calculate the result */
#line 551
    #line 538 "filter/f-inst.c"
 {
    #line 545 "filter/f-inst.c"
;

     
#line 547 "filter/f-inst.c"
;
    return fi_constant(what, val);
  }

  
  #undef whati
#line 551 "filter/f-inst.c"
  }
#line 551

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
)
#line 585
  {
#line 585
    /* Allocate the structure */
#line 585
    struct f_inst *what = fi_new(fi_code);
#line 585
    
#line 585

#line 585
    /* Initialize all the members */
#line 585
  #define whati (&(what->i_FI_FOR_INIT))
#line 585
  #line 553 "filter/f-inst.c"
whati->f1 = f1;
#line 553
const struct f_inst *child1 = f1;
#line 553
do {
#line 553
  what->size += child1->size;
#line 553

#line 553
} while (child1 = child1->next);
#line 554 "filter/f-inst.c"
whati->sym = sym;

#line 557 "filter/f-inst.c"
    ASSERT((sym->class & ~0xff) == SYM_VARIABLE);

    /* Static type check */
    if (f1->type)
    {
      enum f_type t_var = (sym->class & 0xff);
      enum f_type t_arg = f_type_element_type(f1->type);
      if (!t_arg)
        cf_error("Value of expression in FOR must be iterable, got %s",
		 f_type_name(f1->type));
      if (t_var != t_arg)
	cf_error("Loop variable '%s' in FOR must be %s, is %s",
		 sym->name, f_type_name(t_arg), f_type_name(t_var));
    }

    
#line 585 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 585
    
#line 585
      return what;
#line 585

#line 585
    /* Try to pre-calculate the result */
#line 585
      #undef whati
#line 585
  }
#line 585

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
)
#line 639
  {
#line 639
    /* Allocate the structure */
#line 639
    struct f_inst *what = fi_new(fi_code);
#line 639
    
#line 639

#line 639
    /* Initialize all the members */
#line 639
  #define whati (&(what->i_FI_FOR_NEXT))
#line 639
  #line 587 "filter/f-inst.c"
whati->sym = sym;
#line 630 "filter/f-inst.c"
whati->f1 = f1;

#line 639 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 639
    
#line 639
      return what;
#line 639

#line 639
    /* Try to pre-calculate the result */
#line 639
      #undef whati
#line 639
  }
#line 639

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
)
#line 647
  {
#line 647
    /* Allocate the structure */
#line 647
    struct f_inst *what = fi_new(fi_code);
#line 647
    uint constargs = 1;
#line 647

#line 647
    /* Initialize all the members */
#line 647
  #define whati (&(what->i_FI_CONDITION))
#line 647
  #line 640 "filter/f-inst.c"
whati->f1 = f1;
#line 640
const struct f_inst *child1 = f1;
#line 640
do {
#line 640
  what->size += child1->size;
#line 640

#line 640
  if (child1->fi_code != FI_CONSTANT)
#line 640
    constargs = 0;
#line 640

#line 640
} while (child1 = child1->next);
#line 640 "filter/f-inst.c"
if (f1->type && (f1->type != (T_BOOL)) && !f_const_promotion(f1, (T_BOOL)))
#line 640
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 640
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(f1->type));
#line 642 "filter/f-inst.c"
whati->f2 = f2;
#line 644 "filter/f-inst.c"
whati->f3 = f3;

#line 647 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 647
    if (!constargs)
#line 647
      return what;
#line 647

#line 647
    /* Try to pre-calculate the result */
#line 647
    #line 639 "filter/f-inst.c"
 {
    
#line 640 "filter/f-inst.c"
 
#line 640 "filter/f-inst.c"
 
#line 640 "filter/f-inst.c"
;
    if (v1.val.i)
      
#line 642 "filter/f-inst.c"
return whati->f2
#line 642
;
    else
      
#line 644 "filter/f-inst.c"
return whati->f3
#line 644
;
  }

  
  #undef whati
#line 647 "filter/f-inst.c"
  }
#line 647

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
)
#line 656
  {
#line 656
    /* Allocate the structure */
#line 656
    struct f_inst *what = fi_new(fi_code);
#line 656
    
#line 656

#line 656
    /* Initialize all the members */
#line 656
  #define whati (&(what->i_FI_PRINT))
#line 656
  #line 649 "filter/f-inst.c"
whati->varcount = 0;
#line 649
whati->fvar = fvar;
#line 649
for (const struct f_inst *child = fvar; child; child = child->next, whati->varcount++) {
#line 649
  what->size += child->size;
#line 649

#line 649
}
#line 649


#line 656 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 656
    
#line 656
      return what;
#line 656

#line 656
    /* Try to pre-calculate the result */
#line 656
      #undef whati
#line 656
  }
#line 656

#line 656

#line 663 "filter/f-inst.c"
 /* Constructor for FI_FLUSH */
#line 663
struct f_inst *
#line 663
f_new_inst_FI_FLUSH(enum f_instruction_code fi_code
#line 663
)
#line 663
  {
#line 663
    /* Allocate the structure */
#line 663
    struct f_inst *what = fi_new(fi_code);
#line 663
    
#line 663

#line 663
    /* Initialize all the members */
#line 663
  #define whati (&(what->i_FI_FLUSH))
#line 663
  
#line 663
    /* If not constant, return the instruction itself */
#line 663
    
#line 663
      return what;
#line 663

#line 663
    /* Try to pre-calculate the result */
#line 663
      #undef whati
#line 663
  }
#line 663

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
)
#line 677
  {
#line 677
    /* Allocate the structure */
#line 677
    struct f_inst *what = fi_new(fi_code);
#line 677
    
#line 677

#line 677
    /* Initialize all the members */
#line 677
  #define whati (&(what->i_FI_DIE))
#line 677
  #line 665 "filter/f-inst.c"
whati->fret = fret;

#line 677 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 677
    
#line 677
      return what;
#line 677

#line 677
    /* Try to pre-calculate the result */
#line 677
      #undef whati
#line 677
  }
#line 677

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
)
#line 704
  {
#line 704
    /* Allocate the structure */
#line 704
    struct f_inst *what = fi_new(fi_code);
#line 704
    
#line 704

#line 704
    /* Initialize all the members */
#line 704
  #define whati (&(what->i_FI_RTA_GET))
#line 704
  #line 679 "filter/f-inst.c"
whati->sa = sa;
#line 685 "filter/f-inst.c"
what->type = sa.f_type;

#line 704 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 704
    
#line 704
      return what;
#line 704

#line 704
    /* Try to pre-calculate the result */
#line 704
      #undef whati
#line 704
  }
#line 704

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
)
#line 810
  {
#line 810
    /* Allocate the structure */
#line 810
    struct f_inst *what = fi_new(fi_code);
#line 810
    
#line 810

#line 810
    /* Initialize all the members */
#line 810
  #define whati (&(what->i_FI_RTA_SET))
#line 810
  #line 706 "filter/f-inst.c"
whati->f1 = f1;
#line 706
const struct f_inst *child1 = f1;
#line 706
do {
#line 706
  what->size += child1->size;
#line 706

#line 706
} while (child1 = child1->next);
#line 707 "filter/f-inst.c"
whati->sa = sa;
#line 708 "filter/f-inst.c"
if (f1->type && (f1->type != (sa.f_type)) && !f_const_promotion(f1, (sa.f_type)))
#line 708
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 708
	   f_instruction_name(what->fi_code), f_type_name(sa.f_type), f_type_name(f1->type));

#line 810 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 810
    
#line 810
      return what;
#line 810

#line 810
    /* Try to pre-calculate the result */
#line 810
      #undef whati
#line 810
  }
#line 810

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
)
#line 882
  {
#line 882
    /* Allocate the structure */
#line 882
    struct f_inst *what = fi_new(fi_code);
#line 882
    
#line 882

#line 882
    /* Initialize all the members */
#line 882
  #define whati (&(what->i_FI_EA_GET))
#line 882
  #line 811 "filter/f-inst.c"
whati->da = da;
#line 814 "filter/f-inst.c"
what->type = da.f_type;

#line 882 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 882
    
#line 882
      return what;
#line 882

#line 882
    /* Try to pre-calculate the result */
#line 882
      #undef whati
#line 882
  }
#line 882

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
)
#line 949
  {
#line 949
    /* Allocate the structure */
#line 949
    struct f_inst *what = fi_new(fi_code);
#line 949
    
#line 949

#line 949
    /* Initialize all the members */
#line 949
  #define whati (&(what->i_FI_EA_SET))
#line 949
  #line 885 "filter/f-inst.c"
whati->f1 = f1;
#line 885
const struct f_inst *child1 = f1;
#line 885
do {
#line 885
  what->size += child1->size;
#line 885

#line 885
} while (child1 = child1->next);
#line 886 "filter/f-inst.c"
whati->da = da;
#line 887 "filter/f-inst.c"
if (f1->type && (f1->type != (da.f_type)) && !f_const_promotion(f1, (da.f_type)))
#line 887
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 887
	   f_instruction_name(what->fi_code), f_type_name(da.f_type), f_type_name(f1->type));

#line 949 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 949
    
#line 949
      return what;
#line 949

#line 949
    /* Try to pre-calculate the result */
#line 949
      #undef whati
#line 949
  }
#line 949

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
)
#line 958
  {
#line 958
    /* Allocate the structure */
#line 958
    struct f_inst *what = fi_new(fi_code);
#line 958
    
#line 958

#line 958
    /* Initialize all the members */
#line 958
  #define whati (&(what->i_FI_EA_UNSET))
#line 958
  #line 950 "filter/f-inst.c"
whati->da = da;

#line 958 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 958
    
#line 958
      return what;
#line 958

#line 958
    /* Try to pre-calculate the result */
#line 958
      #undef whati
#line 958
  }
#line 958

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
)
#line 970
  {
#line 970
    /* Allocate the structure */
#line 970
    struct f_inst *what = fi_new(fi_code);
#line 970
    uint constargs = 1;
#line 970

#line 970
    /* Initialize all the members */
#line 970
  #define whati (&(what->i_FI_LENGTH))
#line 970
  #line 959 "filter/f-inst.c"
whati->f1 = f1;
#line 959
const struct f_inst *child1 = f1;
#line 959
do {
#line 959
  what->size += child1->size;
#line 959

#line 959
  if (child1->fi_code != FI_CONSTANT)
#line 959
    constargs = 0;
#line 959

#line 959
} while (child1 = child1->next);
#line 961 "filter/f-inst.c"
what->type = T_INT;

#line 970 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 970
    if (!constargs)
#line 970
      return what;
#line 970

#line 970
    /* Try to pre-calculate the result */
#line 970
    #line 958 "filter/f-inst.c"
 {	/* Get length of */
    
#line 959 "filter/f-inst.c"
;
    switch(v1.type) {
    case T_NET:     
#line 961 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = net_pxlen(v1.val.net) } ); break;
    case T_PATH:    return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = as_path_getlen(v1.val.ad) } ); break;
    case T_CLIST:   return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = int_set_get_size(v1.val.ad) } ); break;
    case T_ECLIST:  return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = ec_set_get_size(v1.val.ad) } ); break;
    case T_LCLIST:  return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = lc_set_get_size(v1.val.ad) } ); break;
    default: runtime( "Prefix, path, clist or eclist expected" );
    }
  }

  
  #undef whati
#line 970 "filter/f-inst.c"
  }
#line 970

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
)
#line 1005
  {
#line 1005
    /* Allocate the structure */
#line 1005
    struct f_inst *what = fi_new(fi_code);
#line 1005
    uint constargs = 1;
#line 1005

#line 1005
    /* Initialize all the members */
#line 1005
  #define whati (&(what->i_FI_NET_SRC))
#line 1005
  #line 971 "filter/f-inst.c"
whati->f1 = f1;
#line 971
const struct f_inst *child1 = f1;
#line 971
do {
#line 971
  what->size += child1->size;
#line 971

#line 971
  if (child1->fi_code != FI_CONSTANT)
#line 971
    constargs = 0;
#line 971

#line 971
} while (child1 = child1->next);
#line 971 "filter/f-inst.c"
if (f1->type && (f1->type != (T_NET)) && !f_const_promotion(f1, (T_NET)))
#line 971
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 971
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(f1->type));
#line 1002 "filter/f-inst.c"
what->type = T_NET;

#line 1005 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1005
    if (!constargs)
#line 1005
      return what;
#line 1005

#line 1005
    /* Try to pre-calculate the result */
#line 1005
    #line 970 "filter/f-inst.c"
 { 	/* Get src prefix */
    
#line 971 "filter/f-inst.c"
 
#line 971 "filter/f-inst.c"
 
#line 971 "filter/f-inst.c"
;

    net_addr_union *net = (void *) v1.val.net;
    net_addr *src = falloc(sizeof(net_addr_ip6));
    const byte *part;

    switch(v1.val.net->type) {
    case NET_FLOW4:
      part = flow4_get_part(&net->flow4, FLOW_TYPE_SRC_PREFIX);
      if (part)
	net_fill_ip4(src, flow_read_ip4_part(part), flow_read_pxlen(part));
      else
	net_fill_ip4(src, IP4_NONE, 0);
      break;

    case NET_FLOW6:
      part = flow6_get_part(&net->flow6, FLOW_TYPE_SRC_PREFIX);
      if (part)
	net_fill_ip6(src, flow_read_ip6_part(part), flow_read_pxlen(part));
      else
	net_fill_ip6(src, IP6_NONE, 0);
      break;

    case NET_IP6_SADR:
      net_fill_ip6(src, net->ip6_sadr.src_prefix, net->ip6_sadr.src_pxlen);
      break;

    default:
      runtime( "Flow or SADR expected" );
    }

     
#line 1002 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_NET, .val.net = src } );
  }

  
  #undef whati
#line 1005 "filter/f-inst.c"
  }
#line 1005

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
)
#line 1040
  {
#line 1040
    /* Allocate the structure */
#line 1040
    struct f_inst *what = fi_new(fi_code);
#line 1040
    uint constargs = 1;
#line 1040

#line 1040
    /* Initialize all the members */
#line 1040
  #define whati (&(what->i_FI_NET_DST))
#line 1040
  #line 1006 "filter/f-inst.c"
whati->f1 = f1;
#line 1006
const struct f_inst *child1 = f1;
#line 1006
do {
#line 1006
  what->size += child1->size;
#line 1006

#line 1006
  if (child1->fi_code != FI_CONSTANT)
#line 1006
    constargs = 0;
#line 1006

#line 1006
} while (child1 = child1->next);
#line 1006 "filter/f-inst.c"
if (f1->type && (f1->type != (T_NET)) && !f_const_promotion(f1, (T_NET)))
#line 1006
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1006
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(f1->type));
#line 1037 "filter/f-inst.c"
what->type = T_NET;

#line 1040 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1040
    if (!constargs)
#line 1040
      return what;
#line 1040

#line 1040
    /* Try to pre-calculate the result */
#line 1040
    #line 1005 "filter/f-inst.c"
 { 	/* Get dst prefix */
    
#line 1006 "filter/f-inst.c"
 
#line 1006 "filter/f-inst.c"
 
#line 1006 "filter/f-inst.c"
;

    net_addr_union *net = (void *) v1.val.net;
    net_addr *dst = falloc(sizeof(net_addr_ip6));
    const byte *part;

    switch(v1.val.net->type) {
    case NET_FLOW4:
      part = flow4_get_part(&net->flow4, FLOW_TYPE_DST_PREFIX);
      if (part)
	net_fill_ip4(dst, flow_read_ip4_part(part), flow_read_pxlen(part));
      else
	net_fill_ip4(dst, IP4_NONE, 0);
      break;

    case NET_FLOW6:
      part = flow6_get_part(&net->flow6, FLOW_TYPE_DST_PREFIX);
      if (part)
	net_fill_ip6(dst, flow_read_ip6_part(part), flow_read_pxlen(part));
      else
	net_fill_ip6(dst, IP6_NONE, 0);
      break;

    case NET_IP6_SADR:
      net_fill_ip6(dst, net->ip6_sadr.dst_prefix, net->ip6_sadr.dst_pxlen);
      break;

    default:
      runtime( "Flow or SADR expected" );
    }

     
#line 1037 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_NET, .val.net = dst } );
  }

  
  #undef whati
#line 1040 "filter/f-inst.c"
  }
#line 1040

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
)
#line 1050
  {
#line 1050
    /* Allocate the structure */
#line 1050
    struct f_inst *what = fi_new(fi_code);
#line 1050
    uint constargs = 1;
#line 1050

#line 1050
    /* Initialize all the members */
#line 1050
  #define whati (&(what->i_FI_ROA_MAXLEN))
#line 1050
  #line 1041 "filter/f-inst.c"
whati->f1 = f1;
#line 1041
const struct f_inst *child1 = f1;
#line 1041
do {
#line 1041
  what->size += child1->size;
#line 1041

#line 1041
  if (child1->fi_code != FI_CONSTANT)
#line 1041
    constargs = 0;
#line 1041

#line 1041
} while (child1 = child1->next);
#line 1041 "filter/f-inst.c"
if (f1->type && (f1->type != (T_NET)) && !f_const_promotion(f1, (T_NET)))
#line 1041
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1041
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(f1->type));
#line 1045 "filter/f-inst.c"
what->type = T_INT;

#line 1050 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1050
    if (!constargs)
#line 1050
      return what;
#line 1050

#line 1050
    /* Try to pre-calculate the result */
#line 1050
    #line 1040 "filter/f-inst.c"
 { 	/* Get ROA max prefix length */
    
#line 1041 "filter/f-inst.c"
 
#line 1041 "filter/f-inst.c"
 
#line 1041 "filter/f-inst.c"
;
    if (!net_is_roa(v1.val.net))
      runtime( "ROA expected" );

     
#line 1045 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = (v1.val.net->type == NET_ROA4) ?
#line 1045
      ((net_addr_roa4 *) v1.val.net)->max_pxlen :
#line 1045
      ((net_addr_roa6 *) v1.val.net)->max_pxlen } );
#line 1048
  }

  
  #undef whati
#line 1050 "filter/f-inst.c"
  }
#line 1050

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
)
#line 1077
  {
#line 1077
    /* Allocate the structure */
#line 1077
    struct f_inst *what = fi_new(fi_code);
#line 1077
    uint constargs = 1;
#line 1077

#line 1077
    /* Initialize all the members */
#line 1077
  #define whati (&(what->i_FI_ASN))
#line 1077
  #line 1051 "filter/f-inst.c"
whati->f1 = f1;
#line 1051
const struct f_inst *child1 = f1;
#line 1051
do {
#line 1051
  what->size += child1->size;
#line 1051

#line 1051
  if (child1->fi_code != FI_CONSTANT)
#line 1051
    constargs = 0;
#line 1051

#line 1051
} while (child1 = child1->next);
#line 1052 "filter/f-inst.c"
what->type = T_INT;

#line 1077 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1077
    if (!constargs)
#line 1077
      return what;
#line 1077

#line 1077
    /* Try to pre-calculate the result */
#line 1077
    #line 1050 "filter/f-inst.c"
 { 	/* Get ROA ASN or community ASN part */
    
#line 1051 "filter/f-inst.c"
;
     
#line 1052 "filter/f-inst.c"
;
    switch(v1.type)
    {
      case T_NET:
        if (!net_is_roa(v1.val.net))
          runtime( "ROA expected" );

        return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = (v1.val.net->type == NET_ROA4) ?
#line 1059
          ((net_addr_roa4 *) v1.val.net)->asn :
#line 1059
          ((net_addr_roa6 *) v1.val.net)->asn } );
#line 1062
        break;

      case T_PAIR:
        return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.i >> 16 } );
        break;

      case T_LC:
        return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.lc.asn } );
        break;

      default:
        runtime( "Net, pair or lc expected" );
    }
  }

  
  #undef whati
#line 1077 "filter/f-inst.c"
  }
#line 1077

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
)
#line 1082
  {
#line 1082
    /* Allocate the structure */
#line 1082
    struct f_inst *what = fi_new(fi_code);
#line 1082
    uint constargs = 1;
#line 1082

#line 1082
    /* Initialize all the members */
#line 1082
  #define whati (&(what->i_FI_IP))
#line 1082
  #line 1078 "filter/f-inst.c"
whati->f1 = f1;
#line 1078
const struct f_inst *child1 = f1;
#line 1078
do {
#line 1078
  what->size += child1->size;
#line 1078

#line 1078
  if (child1->fi_code != FI_CONSTANT)
#line 1078
    constargs = 0;
#line 1078

#line 1078
} while (child1 = child1->next);
#line 1078 "filter/f-inst.c"
if (f1->type && (f1->type != (T_NET)) && !f_const_promotion(f1, (T_NET)))
#line 1078
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1078
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(f1->type));
#line 1079 "filter/f-inst.c"
what->type = T_IP;

#line 1082 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1082
    if (!constargs)
#line 1082
      return what;
#line 1082

#line 1082
    /* Try to pre-calculate the result */
#line 1082
    #line 1077 "filter/f-inst.c"
 {	/* Convert prefix to ... */
    
#line 1078 "filter/f-inst.c"
 
#line 1078 "filter/f-inst.c"
 
#line 1078 "filter/f-inst.c"
;
     
#line 1079 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_IP, .val.ip = net_prefix(v1.val.net) } );
  }

  
  #undef whati
#line 1082 "filter/f-inst.c"
  }
#line 1082

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
)
#line 1089
  {
#line 1089
    /* Allocate the structure */
#line 1089
    struct f_inst *what = fi_new(fi_code);
#line 1089
    uint constargs = 1;
#line 1089

#line 1089
    /* Initialize all the members */
#line 1089
  #define whati (&(what->i_FI_ROUTE_DISTINGUISHER))
#line 1089
  #line 1083 "filter/f-inst.c"
whati->f1 = f1;
#line 1083
const struct f_inst *child1 = f1;
#line 1083
do {
#line 1083
  what->size += child1->size;
#line 1083

#line 1083
  if (child1->fi_code != FI_CONSTANT)
#line 1083
    constargs = 0;
#line 1083

#line 1083
} while (child1 = child1->next);
#line 1083 "filter/f-inst.c"
if (f1->type && (f1->type != (T_NET)) && !f_const_promotion(f1, (T_NET)))
#line 1083
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1083
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(f1->type));
#line 1086 "filter/f-inst.c"
what->type = T_RD;

#line 1089 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1089
    if (!constargs)
#line 1089
      return what;
#line 1089

#line 1089
    /* Try to pre-calculate the result */
#line 1089
    #line 1082 "filter/f-inst.c"
 {
    
#line 1083 "filter/f-inst.c"
 
#line 1083 "filter/f-inst.c"
 
#line 1083 "filter/f-inst.c"
;
    if (!net_is_vpn(v1.val.net))
      runtime( "VPN address expected" );
     
#line 1086 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_RD, .val.ec = net_rd(v1.val.net) } );
  }

  
  #undef whati
#line 1089 "filter/f-inst.c"
  }
#line 1089

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
)
#line 1096
  {
#line 1096
    /* Allocate the structure */
#line 1096
    struct f_inst *what = fi_new(fi_code);
#line 1096
    uint constargs = 1;
#line 1096

#line 1096
    /* Initialize all the members */
#line 1096
  #define whati (&(what->i_FI_AS_PATH_FIRST))
#line 1096
  #line 1090 "filter/f-inst.c"
whati->f1 = f1;
#line 1090
const struct f_inst *child1 = f1;
#line 1090
do {
#line 1090
  what->size += child1->size;
#line 1090

#line 1090
  if (child1->fi_code != FI_CONSTANT)
#line 1090
    constargs = 0;
#line 1090

#line 1090
} while (child1 = child1->next);
#line 1090 "filter/f-inst.c"
if (f1->type && (f1->type != (T_PATH)) && !f_const_promotion(f1, (T_PATH)))
#line 1090
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1090
	   f_instruction_name(what->fi_code), f_type_name(T_PATH), f_type_name(f1->type));
#line 1093 "filter/f-inst.c"
what->type = T_INT;

#line 1096 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1096
    if (!constargs)
#line 1096
      return what;
#line 1096

#line 1096
    /* Try to pre-calculate the result */
#line 1096
    #line 1089 "filter/f-inst.c"
 {	/* Get first ASN from AS PATH */
    
#line 1090 "filter/f-inst.c"
 
#line 1090 "filter/f-inst.c"
 
#line 1090 "filter/f-inst.c"
;
    u32 as = 0;
    as_path_get_first(v1.val.ad, &as);
     
#line 1093 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = as } );
  }

  
  #undef whati
#line 1096 "filter/f-inst.c"
  }
#line 1096

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
)
#line 1103
  {
#line 1103
    /* Allocate the structure */
#line 1103
    struct f_inst *what = fi_new(fi_code);
#line 1103
    uint constargs = 1;
#line 1103

#line 1103
    /* Initialize all the members */
#line 1103
  #define whati (&(what->i_FI_AS_PATH_LAST))
#line 1103
  #line 1097 "filter/f-inst.c"
whati->f1 = f1;
#line 1097
const struct f_inst *child1 = f1;
#line 1097
do {
#line 1097
  what->size += child1->size;
#line 1097

#line 1097
  if (child1->fi_code != FI_CONSTANT)
#line 1097
    constargs = 0;
#line 1097

#line 1097
} while (child1 = child1->next);
#line 1097 "filter/f-inst.c"
if (f1->type && (f1->type != (T_PATH)) && !f_const_promotion(f1, (T_PATH)))
#line 1097
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1097
	   f_instruction_name(what->fi_code), f_type_name(T_PATH), f_type_name(f1->type));
#line 1100 "filter/f-inst.c"
what->type = T_INT;

#line 1103 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1103
    if (!constargs)
#line 1103
      return what;
#line 1103

#line 1103
    /* Try to pre-calculate the result */
#line 1103
    #line 1096 "filter/f-inst.c"
 {		/* Get last ASN from AS PATH */
    
#line 1097 "filter/f-inst.c"
 
#line 1097 "filter/f-inst.c"
 
#line 1097 "filter/f-inst.c"
;
    u32 as = 0;
    as_path_get_last(v1.val.ad, &as);
     
#line 1100 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = as } );
  }

  
  #undef whati
#line 1103 "filter/f-inst.c"
  }
#line 1103

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
)
#line 1108
  {
#line 1108
    /* Allocate the structure */
#line 1108
    struct f_inst *what = fi_new(fi_code);
#line 1108
    uint constargs = 1;
#line 1108

#line 1108
    /* Initialize all the members */
#line 1108
  #define whati (&(what->i_FI_AS_PATH_LAST_NAG))
#line 1108
  #line 1104 "filter/f-inst.c"
whati->f1 = f1;
#line 1104
const struct f_inst *child1 = f1;
#line 1104
do {
#line 1104
  what->size += child1->size;
#line 1104

#line 1104
  if (child1->fi_code != FI_CONSTANT)
#line 1104
    constargs = 0;
#line 1104

#line 1104
} while (child1 = child1->next);
#line 1104 "filter/f-inst.c"
if (f1->type && (f1->type != (T_PATH)) && !f_const_promotion(f1, (T_PATH)))
#line 1104
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1104
	   f_instruction_name(what->fi_code), f_type_name(T_PATH), f_type_name(f1->type));
#line 1105 "filter/f-inst.c"
what->type = T_INT;

#line 1108 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1108
    if (!constargs)
#line 1108
      return what;
#line 1108

#line 1108
    /* Try to pre-calculate the result */
#line 1108
    #line 1103 "filter/f-inst.c"
 {	/* Get last ASN from non-aggregated part of AS PATH */
    
#line 1104 "filter/f-inst.c"
 
#line 1104 "filter/f-inst.c"
 
#line 1104 "filter/f-inst.c"
;
     
#line 1105 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = as_path_get_last_nonaggregated(v1.val.ad) } );
  }

  
  #undef whati
#line 1108 "filter/f-inst.c"
  }
#line 1108

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
)
#line 1113
  {
#line 1113
    /* Allocate the structure */
#line 1113
    struct f_inst *what = fi_new(fi_code);
#line 1113
    uint constargs = 1;
#line 1113

#line 1113
    /* Initialize all the members */
#line 1113
  #define whati (&(what->i_FI_PAIR_DATA))
#line 1113
  #line 1109 "filter/f-inst.c"
whati->f1 = f1;
#line 1109
const struct f_inst *child1 = f1;
#line 1109
do {
#line 1109
  what->size += child1->size;
#line 1109

#line 1109
  if (child1->fi_code != FI_CONSTANT)
#line 1109
    constargs = 0;
#line 1109

#line 1109
} while (child1 = child1->next);
#line 1109 "filter/f-inst.c"
if (f1->type && (f1->type != (T_PAIR)) && !f_const_promotion(f1, (T_PAIR)))
#line 1109
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1109
	   f_instruction_name(what->fi_code), f_type_name(T_PAIR), f_type_name(f1->type));
#line 1110 "filter/f-inst.c"
what->type = T_INT;

#line 1113 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1113
    if (!constargs)
#line 1113
      return what;
#line 1113

#line 1113
    /* Try to pre-calculate the result */
#line 1113
    #line 1108 "filter/f-inst.c"
 {	/* Get data part from the standard community */
    
#line 1109 "filter/f-inst.c"
 
#line 1109 "filter/f-inst.c"
 
#line 1109 "filter/f-inst.c"
;
     
#line 1110 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.i & 0xFFFF } );
  }

  
  #undef whati
#line 1113 "filter/f-inst.c"
  }
#line 1113

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
)
#line 1118
  {
#line 1118
    /* Allocate the structure */
#line 1118
    struct f_inst *what = fi_new(fi_code);
#line 1118
    uint constargs = 1;
#line 1118

#line 1118
    /* Initialize all the members */
#line 1118
  #define whati (&(what->i_FI_LC_DATA1))
#line 1118
  #line 1114 "filter/f-inst.c"
whati->f1 = f1;
#line 1114
const struct f_inst *child1 = f1;
#line 1114
do {
#line 1114
  what->size += child1->size;
#line 1114

#line 1114
  if (child1->fi_code != FI_CONSTANT)
#line 1114
    constargs = 0;
#line 1114

#line 1114
} while (child1 = child1->next);
#line 1114 "filter/f-inst.c"
if (f1->type && (f1->type != (T_LC)) && !f_const_promotion(f1, (T_LC)))
#line 1114
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1114
	   f_instruction_name(what->fi_code), f_type_name(T_LC), f_type_name(f1->type));
#line 1115 "filter/f-inst.c"
what->type = T_INT;

#line 1118 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1118
    if (!constargs)
#line 1118
      return what;
#line 1118

#line 1118
    /* Try to pre-calculate the result */
#line 1118
    #line 1113 "filter/f-inst.c"
 {	/* Get data1 part from the large community */
    
#line 1114 "filter/f-inst.c"
 
#line 1114 "filter/f-inst.c"
 
#line 1114 "filter/f-inst.c"
;
     
#line 1115 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.lc.ldp1 } );
  }

  
  #undef whati
#line 1118 "filter/f-inst.c"
  }
#line 1118

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
)
#line 1123
  {
#line 1123
    /* Allocate the structure */
#line 1123
    struct f_inst *what = fi_new(fi_code);
#line 1123
    uint constargs = 1;
#line 1123

#line 1123
    /* Initialize all the members */
#line 1123
  #define whati (&(what->i_FI_LC_DATA2))
#line 1123
  #line 1119 "filter/f-inst.c"
whati->f1 = f1;
#line 1119
const struct f_inst *child1 = f1;
#line 1119
do {
#line 1119
  what->size += child1->size;
#line 1119

#line 1119
  if (child1->fi_code != FI_CONSTANT)
#line 1119
    constargs = 0;
#line 1119

#line 1119
} while (child1 = child1->next);
#line 1119 "filter/f-inst.c"
if (f1->type && (f1->type != (T_LC)) && !f_const_promotion(f1, (T_LC)))
#line 1119
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1119
	   f_instruction_name(what->fi_code), f_type_name(T_LC), f_type_name(f1->type));
#line 1120 "filter/f-inst.c"
what->type = T_INT;

#line 1123 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1123
    if (!constargs)
#line 1123
      return what;
#line 1123

#line 1123
    /* Try to pre-calculate the result */
#line 1123
    #line 1118 "filter/f-inst.c"
 {	/* Get data2 part from the large community */
    
#line 1119 "filter/f-inst.c"
 
#line 1119 "filter/f-inst.c"
 
#line 1119 "filter/f-inst.c"
;
     
#line 1120 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_INT, .val.i = v1.val.lc.ldp2 } );
  }

  
  #undef whati
#line 1123 "filter/f-inst.c"
  }
#line 1123

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
)
#line 1157
  {
#line 1157
    /* Allocate the structure */
#line 1157
    struct f_inst *what = fi_new(fi_code);
#line 1157
    uint constargs = 1;
#line 1157

#line 1157
    /* Initialize all the members */
#line 1157
  #define whati (&(what->i_FI_MIN))
#line 1157
  #line 1124 "filter/f-inst.c"
whati->f1 = f1;
#line 1124
const struct f_inst *child1 = f1;
#line 1124
do {
#line 1124
  what->size += child1->size;
#line 1124

#line 1124
  if (child1->fi_code != FI_CONSTANT)
#line 1124
    constargs = 0;
#line 1124

#line 1124
} while (child1 = child1->next);
#line 1125 "filter/f-inst.c"
what->type = f_type_element_type(v1.type);

#line 1157 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1157
    if (!constargs)
#line 1157
      return what;
#line 1157

#line 1157
    /* Try to pre-calculate the result */
#line 1157
    #line 1123 "filter/f-inst.c"
 {	/* Get minimum element from list */
    
#line 1124 "filter/f-inst.c"
;
     
#line 1125 "filter/f-inst.c"
;
    switch(v1.type)
    {
      case T_CLIST:
        {
          u32 val = 0;
          int_set_min(v1.val.ad, &val);
          return fi_constant(what,  (struct f_val) { .type = T_PAIR, .val.i = val } );
        }
        break;

      case T_ECLIST:
        {
          u64 val = 0;
          ec_set_min(v1.val.ad, &val);
          return fi_constant(what,  (struct f_val) { .type = T_EC, .val.ec = val } );
        }
        break;

      case T_LCLIST:
        {
          lcomm val = { 0, 0, 0 };
          lc_set_min(v1.val.ad, &val);
          return fi_constant(what,  (struct f_val) { .type = T_LC, .val.lc = val } );
        }
        break;

      default:
        runtime( "Clist or lclist expected" );
    }
  }

  
  #undef whati
#line 1157 "filter/f-inst.c"
  }
#line 1157

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
)
#line 1191
  {
#line 1191
    /* Allocate the structure */
#line 1191
    struct f_inst *what = fi_new(fi_code);
#line 1191
    uint constargs = 1;
#line 1191

#line 1191
    /* Initialize all the members */
#line 1191
  #define whati (&(what->i_FI_MAX))
#line 1191
  #line 1158 "filter/f-inst.c"
whati->f1 = f1;
#line 1158
const struct f_inst *child1 = f1;
#line 1158
do {
#line 1158
  what->size += child1->size;
#line 1158

#line 1158
  if (child1->fi_code != FI_CONSTANT)
#line 1158
    constargs = 0;
#line 1158

#line 1158
} while (child1 = child1->next);
#line 1159 "filter/f-inst.c"
what->type = f_type_element_type(v1.type);

#line 1191 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1191
    if (!constargs)
#line 1191
      return what;
#line 1191

#line 1191
    /* Try to pre-calculate the result */
#line 1191
    #line 1157 "filter/f-inst.c"
 {	/* Get maximum element from list */
    
#line 1158 "filter/f-inst.c"
;
     
#line 1159 "filter/f-inst.c"
;
    switch(v1.type)
    {
      case T_CLIST:
        {
          u32 val = 0;
          int_set_max(v1.val.ad, &val);
          return fi_constant(what,  (struct f_val) { .type = T_PAIR, .val.i = val } );
        }
        break;

      case T_ECLIST:
        {
          u64 val = 0;
          ec_set_max(v1.val.ad, &val);
          return fi_constant(what,  (struct f_val) { .type = T_EC, .val.ec = val } );
        }
        break;

      case T_LCLIST:
        {
          lcomm val = { 0, 0, 0 };
          lc_set_max(v1.val.ad, &val);
          return fi_constant(what,  (struct f_val) { .type = T_LC, .val.lc = val } );
        }
        break;

      default:
        runtime( "Clist or lclist expected" );
    }
  }

  
  #undef whati
#line 1191 "filter/f-inst.c"
  }
#line 1191

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
)
#line 1217
  {
#line 1217
    /* Allocate the structure */
#line 1217
    struct f_inst *what = fi_new(fi_code);
#line 1217
    
#line 1217

#line 1217
    /* Initialize all the members */
#line 1217
  #define whati (&(what->i_FI_RETURN))
#line 1217
  #line 1194 "filter/f-inst.c"
whati->f1 = f1;
#line 1194
const struct f_inst *child1 = f1;
#line 1194
do {
#line 1194
  what->size += child1->size;
#line 1194

#line 1194
} while (child1 = child1->next);

#line 1217 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1217
    
#line 1217
      return what;
#line 1217

#line 1217
    /* Try to pre-calculate the result */
#line 1217
      #undef whati
#line 1217
  }
#line 1217

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
)
#line 1278
  {
#line 1278
    /* Allocate the structure */
#line 1278
    struct f_inst *what = fi_new(fi_code);
#line 1278
    
#line 1278

#line 1278
    /* Initialize all the members */
#line 1278
  #define whati (&(what->i_FI_CALL))
#line 1278
  #line 1219 "filter/f-inst.c"
whati->varcount = 0;
#line 1219
whati->fvar = fvar;
#line 1219
for (const struct f_inst *child = fvar; child; child = child->next, whati->varcount++) {
#line 1219
  what->size += child->size;
#line 1219

#line 1219
}
#line 1219

#line 1220 "filter/f-inst.c"
whati->sym = sym;
#line 1223 "filter/f-inst.c"
what->type = T_VOID;

#line 1226 "filter/f-inst.c"
    ASSERT(sym->class == SYM_FUNCTION);

    if (whati->varcount != sym->function->args)
      cf_error("Function '%s' expects %u arguments, got %u arguments",
	       sym->name, sym->function->args, whati->varcount);

    /* Typecheck individual arguments */
    struct f_inst *a = fvar;
    struct f_arg *b = sym->function->arg_list;
    for (uint i = 1; a && b; a = a->next, b = b->next, i++)
    {
      enum f_type b_type = b->arg->class & 0xff;

      if (a->type && (a->type != b_type) && !f_const_promotion(a, b_type))
	cf_error("Argument %u of '%s' must be %s, got %s",
		 i, sym->name, f_type_name(b_type), f_type_name(a->type));
    }
    ASSERT(!a && !b);

    /* Add implicit void slot for the return value */
    struct f_inst *tmp = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_VOID });
    tmp->next = whati->fvar;
    whati->fvar = tmp;
    what->size += tmp->size;

    /* Mark recursive calls, they have dummy f_line */
    if (!sym->function->len)
      what->flags |= FIF_RECURSIVE;

    
#line 1278 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1278
    
#line 1278
      return what;
#line 1278

#line 1278
    /* Try to pre-calculate the result */
#line 1278
      #undef whati
#line 1278
  }
#line 1278

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
)
#line 1283
  {
#line 1283
    /* Allocate the structure */
#line 1283
    struct f_inst *what = fi_new(fi_code);
#line 1283
    
#line 1283

#line 1283
    /* Initialize all the members */
#line 1283
  #define whati (&(what->i_FI_DROP_RESULT))
#line 1283
  #line 1280 "filter/f-inst.c"
whati->f1 = f1;
#line 1280
const struct f_inst *child1 = f1;
#line 1280
do {
#line 1280
  what->size += child1->size;
#line 1280

#line 1280
} while (child1 = child1->next);

#line 1283 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1283
    
#line 1283
      return what;
#line 1283

#line 1283
    /* Try to pre-calculate the result */
#line 1283
      #undef whati
#line 1283
  }
#line 1283

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
)
#line 1306
  {
#line 1306
    /* Allocate the structure */
#line 1306
    struct f_inst *what = fi_new(fi_code);
#line 1306
    uint constargs = 1;
#line 1306

#line 1306
    /* Initialize all the members */
#line 1306
  #define whati (&(what->i_FI_SWITCH))
#line 1306
  #line 1284 "filter/f-inst.c"
whati->f1 = f1;
#line 1284
const struct f_inst *child1 = f1;
#line 1284
do {
#line 1284
  what->size += child1->size;
#line 1284

#line 1284
  if (child1->fi_code != FI_CONSTANT)
#line 1284
    constargs = 0;
#line 1284

#line 1284
} while (child1 = child1->next);
#line 1286 "filter/f-inst.c"
whati->tree = tree;

#line 1306 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1306
    if (!constargs)
#line 1306
      return what;
#line 1306

#line 1306
    /* Try to pre-calculate the result */
#line 1306
    #line 1283 "filter/f-inst.c"
 {
    
#line 1284 "filter/f-inst.c"
;

    #line 1286 "filter/f-inst.c"
;

    
#line 1292 "filter/f-inst.c"
    const struct f_tree *t = find_tree(tree, &v1);
    if (!t) {
      v1.type = T_VOID;
      t = find_tree(tree, &v1);
      if (!t) {
	debug( "No else statement?\n");
	return NULL;
      }
    }
    /* It is actually possible to have t->data NULL */

    return t->data ;
#line 1304 "filter/f-inst.c"
  }

  
  #undef whati
#line 1306 "filter/f-inst.c"
  }
#line 1306

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
)
#line 1314
  {
#line 1314
    /* Allocate the structure */
#line 1314
    struct f_inst *what = fi_new(fi_code);
#line 1314
    uint constargs = 1;
#line 1314

#line 1314
    /* Initialize all the members */
#line 1314
  #define whati (&(what->i_FI_IP_MASK))
#line 1314
  #line 1307 "filter/f-inst.c"
whati->f1 = f1;
#line 1307
const struct f_inst *child1 = f1;
#line 1307
do {
#line 1307
  what->size += child1->size;
#line 1307

#line 1307
  if (child1->fi_code != FI_CONSTANT)
#line 1307
    constargs = 0;
#line 1307

#line 1307
} while (child1 = child1->next);
#line 1307 "filter/f-inst.c"
if (f1->type && (f1->type != (T_IP)) && !f_const_promotion(f1, (T_IP)))
#line 1307
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1307
	   f_instruction_name(what->fi_code), f_type_name(T_IP), f_type_name(f1->type));
#line 1308 "filter/f-inst.c"
whati->f2 = f2;
#line 1308
const struct f_inst *child2 = f2;
#line 1308
do {
#line 1308
  what->size += child2->size;
#line 1308

#line 1308
  if (child2->fi_code != FI_CONSTANT)
#line 1308
    constargs = 0;
#line 1308

#line 1308
} while (child2 = child2->next);
#line 1308 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 1308
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 1308
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 1309 "filter/f-inst.c"
what->type = T_IP;

#line 1314 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1314
    if (!constargs)
#line 1314
      return what;
#line 1314

#line 1314
    /* Try to pre-calculate the result */
#line 1314
    #line 1306 "filter/f-inst.c"
 { /* IP.MASK(val) */
    
#line 1307 "filter/f-inst.c"
 
#line 1307 "filter/f-inst.c"
 
#line 1307 "filter/f-inst.c"
;
    
#line 1308 "filter/f-inst.c"
 
#line 1308 "filter/f-inst.c"
 
#line 1308 "filter/f-inst.c"
;
     
#line 1309 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_IP, .val.ip =  ipa_is_ip4(v1.val.ip) ?
#line 1309
      ipa_from_ip4(ip4_and(ipa_to_ip4(v1.val.ip), ip4_mkmask(v2.val.i))) :
#line 1309
      ipa_from_ip6(ip6_and(ipa_to_ip6(v1.val.ip), ip6_mkmask(v2.val.i)))  } );
#line 1312
  }

  
  #undef whati
#line 1314 "filter/f-inst.c"
  }
#line 1314

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
)
#line 1320
  {
#line 1320
    /* Allocate the structure */
#line 1320
    struct f_inst *what = fi_new(fi_code);
#line 1320
    uint constargs = 1;
#line 1320

#line 1320
    /* Initialize all the members */
#line 1320
  #define whati (&(what->i_FI_PATH_PREPEND))
#line 1320
  #line 1315 "filter/f-inst.c"
whati->f1 = f1;
#line 1315
const struct f_inst *child1 = f1;
#line 1315
do {
#line 1315
  what->size += child1->size;
#line 1315

#line 1315
  if (child1->fi_code != FI_CONSTANT)
#line 1315
    constargs = 0;
#line 1315

#line 1315
} while (child1 = child1->next);
#line 1315 "filter/f-inst.c"
if (f1->type && (f1->type != (T_PATH)) && !f_const_promotion(f1, (T_PATH)))
#line 1315
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1315
	   f_instruction_name(what->fi_code), f_type_name(T_PATH), f_type_name(f1->type));
#line 1316 "filter/f-inst.c"
whati->f2 = f2;
#line 1316
const struct f_inst *child2 = f2;
#line 1316
do {
#line 1316
  what->size += child2->size;
#line 1316

#line 1316
  if (child2->fi_code != FI_CONSTANT)
#line 1316
    constargs = 0;
#line 1316

#line 1316
} while (child2 = child2->next);
#line 1316 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 1316
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 1316
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 1317 "filter/f-inst.c"
what->type = T_PATH;

#line 1320 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1320
    if (!constargs)
#line 1320
      return what;
#line 1320

#line 1320
    /* Try to pre-calculate the result */
#line 1320
    #line 1314 "filter/f-inst.c"
 {	/* Path prepend */
    
#line 1315 "filter/f-inst.c"
 
#line 1315 "filter/f-inst.c"
 
#line 1315 "filter/f-inst.c"
;
    
#line 1316 "filter/f-inst.c"
 
#line 1316 "filter/f-inst.c"
 
#line 1316 "filter/f-inst.c"
;
     
#line 1317 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_PATH, .val.ad =  as_path_prepend(fpool, v1.val.ad, v2.val.i)  } );
  }

  
  #undef whati
#line 1320 "filter/f-inst.c"
  }
#line 1320

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
)
#line 1377
  {
#line 1377
    /* Allocate the structure */
#line 1377
    struct f_inst *what = fi_new(fi_code);
#line 1377
    uint constargs = 1;
#line 1377

#line 1377
    /* Initialize all the members */
#line 1377
  #define whati (&(what->i_FI_CLIST_ADD))
#line 1377
  #line 1321 "filter/f-inst.c"
whati->f1 = f1;
#line 1321
const struct f_inst *child1 = f1;
#line 1321
do {
#line 1321
  what->size += child1->size;
#line 1321

#line 1321
  if (child1->fi_code != FI_CONSTANT)
#line 1321
    constargs = 0;
#line 1321

#line 1321
} while (child1 = child1->next);
#line 1322 "filter/f-inst.c"
whati->f2 = f2;
#line 1322
const struct f_inst *child2 = f2;
#line 1322
do {
#line 1322
  what->size += child2->size;
#line 1322

#line 1322
  if (child2->fi_code != FI_CONSTANT)
#line 1322
    constargs = 0;
#line 1322

#line 1322
} while (child2 = child2->next);
#line 1323 "filter/f-inst.c"
what->type = f1->type;

#line 1377 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1377
    if (!constargs)
#line 1377
      return what;
#line 1377

#line 1377
    /* Try to pre-calculate the result */
#line 1377
    #line 1320 "filter/f-inst.c"
 {	/* (Extended) Community list add */
    
#line 1321 "filter/f-inst.c"
;
    
#line 1322 "filter/f-inst.c"
;
     
#line 1323 "filter/f-inst.c"
;

    if (v1.type == T_PATH)
      runtime("Can't add to path");

    else if (v1.type == T_CLIST)
    {
      /* Community (or cluster) list */
      struct f_val dummy;

      if ((v2.type == T_PAIR) || (v2.type == T_QUAD))
	return fi_constant(what,  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_add(fpool, v1.val.ad, v2.val.i)  } );
      /* IP->Quad implicit conversion */
      else if (val_is_ip4(&v2))
	return fi_constant(what,  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_add(fpool, v1.val.ad, ipa_to_u32(v2.val.ip))  } );
      else if ((v2.type == T_SET) && clist_set_type(v2.val.t, &dummy))
	runtime("Can't add set");
      else if (v2.type == T_CLIST)
	return fi_constant(what,  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_union(fpool, v1.val.ad, v2.val.ad)  } );
      else
	runtime("Can't add non-pair");
    }

    else if (v1.type == T_ECLIST)
    {
      /* v2.val is either EC or EC-set */
      if ((v2.type == T_SET) && eclist_set_type(v2.val.t))
	runtime("Can't add set");
      else if (v2.type == T_ECLIST)
	return fi_constant(what,  (struct f_val) { .type = T_ECLIST, .val.ad =  ec_set_union(fpool, v1.val.ad, v2.val.ad)  } );
      else if (v2.type != T_EC)
	runtime("Can't add non-ec");
      else
	return fi_constant(what,  (struct f_val) { .type = T_ECLIST, .val.ad =  ec_set_add(fpool, v1.val.ad, v2.val.ec)  } );
    }

    else if (v1.type == T_LCLIST)
    {
      /* v2.val is either LC or LC-set */
      if ((v2.type == T_SET) && lclist_set_type(v2.val.t))
	runtime("Can't add set");
      else if (v2.type == T_LCLIST)
	return fi_constant(what,  (struct f_val) { .type = T_LCLIST, .val.ad =  lc_set_union(fpool, v1.val.ad, v2.val.ad)  } );
      else if (v2.type != T_LC)
	runtime("Can't add non-lc");
      else
	return fi_constant(what,  (struct f_val) { .type = T_LCLIST, .val.ad =  lc_set_add(fpool, v1.val.ad, v2.val.lc)  } );

    }

    else
      runtime("Can't add to non-[e|l]clist");
  }

  
  #undef whati
#line 1377 "filter/f-inst.c"
  }
#line 1377

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
)
#line 1432
  {
#line 1432
    /* Allocate the structure */
#line 1432
    struct f_inst *what = fi_new(fi_code);
#line 1432
    uint constargs = 1;
#line 1432

#line 1432
    /* Initialize all the members */
#line 1432
  #define whati (&(what->i_FI_CLIST_DEL))
#line 1432
  #line 1378 "filter/f-inst.c"
whati->f1 = f1;
#line 1378
const struct f_inst *child1 = f1;
#line 1378
do {
#line 1378
  what->size += child1->size;
#line 1378

#line 1378
  if (child1->fi_code != FI_CONSTANT)
#line 1378
    constargs = 0;
#line 1378

#line 1378
} while (child1 = child1->next);
#line 1379 "filter/f-inst.c"
whati->f2 = f2;
#line 1379
const struct f_inst *child2 = f2;
#line 1379
do {
#line 1379
  what->size += child2->size;
#line 1379

#line 1379
  if (child2->fi_code != FI_CONSTANT)
#line 1379
    constargs = 0;
#line 1379

#line 1379
} while (child2 = child2->next);
#line 1380 "filter/f-inst.c"
what->type = f1->type;

#line 1432 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1432
    if (!constargs)
#line 1432
      return what;
#line 1432

#line 1432
    /* Try to pre-calculate the result */
#line 1432
    #line 1377 "filter/f-inst.c"
 {	/* (Extended) Community list add or delete */
    
#line 1378 "filter/f-inst.c"
;
    
#line 1379 "filter/f-inst.c"
;
     
#line 1380 "filter/f-inst.c"
;

    if (v1.type == T_PATH)
    {
      if ((v2.type == T_SET) && path_set_type(v2.val.t) || (v2.type == T_INT))
	return fi_constant(what,  (struct f_val) { .type = T_PATH, .val.ad =  as_path_filter(fpool, v1.val.ad, &v2, 0)  } );
      else
	runtime("Can't delete non-integer (set)");
    }

    else if (v1.type == T_CLIST)
    {
      /* Community (or cluster) list */
      struct f_val dummy;

      if ((v2.type == T_PAIR) || (v2.type == T_QUAD))
	return fi_constant(what,  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_del(fpool, v1.val.ad, v2.val.i)  } );
      /* IP->Quad implicit conversion */
      else if (val_is_ip4(&v2))
	return fi_constant(what,  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_del(fpool, v1.val.ad, ipa_to_u32(v2.val.ip))  } );
      else if ((v2.type == T_SET) && clist_set_type(v2.val.t, &dummy) || (v2.type == T_CLIST))
	return fi_constant(what,  (struct f_val) { .type = T_CLIST, .val.ad =  clist_filter(fpool, v1.val.ad, &v2, 0)  } );
      else
	runtime("Can't delete non-pair");
    }

    else if (v1.type == T_ECLIST)
    {
      /* v2.val is either EC or EC-set */
      if ((v2.type == T_SET) && eclist_set_type(v2.val.t) || (v2.type == T_ECLIST))
	return fi_constant(what,  (struct f_val) { .type = T_ECLIST, .val.ad =  eclist_filter(fpool, v1.val.ad, &v2, 0)  } );
      else if (v2.type != T_EC)
	runtime("Can't delete non-ec");
      else
	return fi_constant(what,  (struct f_val) { .type = T_ECLIST, .val.ad =  ec_set_del(fpool, v1.val.ad, v2.val.ec)  } );
    }

    else if (v1.type == T_LCLIST)
    {
      /* v2.val is either LC or LC-set */
      if ((v2.type == T_SET) && lclist_set_type(v2.val.t) || (v2.type == T_LCLIST))
	return fi_constant(what,  (struct f_val) { .type = T_LCLIST, .val.ad =  lclist_filter(fpool, v1.val.ad, &v2, 0)  } );
      else if (v2.type != T_LC)
	runtime("Can't delete non-lc");
      else
	return fi_constant(what,  (struct f_val) { .type = T_LCLIST, .val.ad =  lc_set_del(fpool, v1.val.ad, v2.val.lc)  } );
    }

    else
      runtime("Can't delete in non-[e|l]clist");
  }

  
  #undef whati
#line 1432 "filter/f-inst.c"
  }
#line 1432

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
)
#line 1478
  {
#line 1478
    /* Allocate the structure */
#line 1478
    struct f_inst *what = fi_new(fi_code);
#line 1478
    uint constargs = 1;
#line 1478

#line 1478
    /* Initialize all the members */
#line 1478
  #define whati (&(what->i_FI_CLIST_FILTER))
#line 1478
  #line 1433 "filter/f-inst.c"
whati->f1 = f1;
#line 1433
const struct f_inst *child1 = f1;
#line 1433
do {
#line 1433
  what->size += child1->size;
#line 1433

#line 1433
  if (child1->fi_code != FI_CONSTANT)
#line 1433
    constargs = 0;
#line 1433

#line 1433
} while (child1 = child1->next);
#line 1434 "filter/f-inst.c"
whati->f2 = f2;
#line 1434
const struct f_inst *child2 = f2;
#line 1434
do {
#line 1434
  what->size += child2->size;
#line 1434

#line 1434
  if (child2->fi_code != FI_CONSTANT)
#line 1434
    constargs = 0;
#line 1434

#line 1434
} while (child2 = child2->next);
#line 1435 "filter/f-inst.c"
what->type = f1->type;

#line 1478 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1478
    if (!constargs)
#line 1478
      return what;
#line 1478

#line 1478
    /* Try to pre-calculate the result */
#line 1478
    #line 1432 "filter/f-inst.c"
 {	/* (Extended) Community list add or delete */
    
#line 1433 "filter/f-inst.c"
;
    
#line 1434 "filter/f-inst.c"
;
     
#line 1435 "filter/f-inst.c"
;

    if (v1.type == T_PATH)
    {
      if ((v2.type == T_SET) && path_set_type(v2.val.t))
	return fi_constant(what,  (struct f_val) { .type = T_PATH, .val.ad =  as_path_filter(fpool, v1.val.ad, &v2, 1)  } );
      else
	runtime("Can't filter integer");
    }

    else if (v1.type == T_CLIST)
    {
      /* Community (or cluster) list */
      struct f_val dummy;

      if ((v2.type == T_SET) && clist_set_type(v2.val.t, &dummy) || (v2.type == T_CLIST))
	return fi_constant(what,  (struct f_val) { .type = T_CLIST, .val.ad =  clist_filter(fpool, v1.val.ad, &v2, 1)  } );
      else
	runtime("Can't filter pair");
    }

    else if (v1.type == T_ECLIST)
    {
      /* v2.val is either EC or EC-set */
      if ((v2.type == T_SET) && eclist_set_type(v2.val.t) || (v2.type == T_ECLIST))
	return fi_constant(what,  (struct f_val) { .type = T_ECLIST, .val.ad =  eclist_filter(fpool, v1.val.ad, &v2, 1)  } );
      else
	runtime("Can't filter ec");
    }

    else if (v1.type == T_LCLIST)
    {
      /* v2.val is either LC or LC-set */
      if ((v2.type == T_SET) && lclist_set_type(v2.val.t) || (v2.type == T_LCLIST))
	return fi_constant(what,  (struct f_val) { .type = T_LCLIST, .val.ad =  lclist_filter(fpool, v1.val.ad, &v2, 1)  } );
      else
	runtime("Can't filter lc");
    }

    else
      runtime("Can't filter non-[e|l]clist");
  }

  
  #undef whati
#line 1478 "filter/f-inst.c"
  }
#line 1478

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
)
#line 1508
  {
#line 1508
    /* Allocate the structure */
#line 1508
    struct f_inst *what = fi_new(fi_code);
#line 1508
    
#line 1508

#line 1508
    /* Initialize all the members */
#line 1508
  #define whati (&(what->i_FI_ROA_CHECK_IMPLICIT))
#line 1508
  #line 1480 "filter/f-inst.c"
whati->rtc = rtc;
#line 1503 "filter/f-inst.c"
what->type = T_ENUM_ROA;

#line 1508 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1508
    
#line 1508
      return what;
#line 1508

#line 1508
    /* Try to pre-calculate the result */
#line 1508
      #undef whati
#line 1508
  }
#line 1508

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
)
#line 1530
  {
#line 1530
    /* Allocate the structure */
#line 1530
    struct f_inst *what = fi_new(fi_code);
#line 1530
    
#line 1530

#line 1530
    /* Initialize all the members */
#line 1530
  #define whati (&(what->i_FI_ROA_CHECK_EXPLICIT))
#line 1530
  #line 1510 "filter/f-inst.c"
whati->f1 = f1;
#line 1510
const struct f_inst *child1 = f1;
#line 1510
do {
#line 1510
  what->size += child1->size;
#line 1510

#line 1510
} while (child1 = child1->next);
#line 1510 "filter/f-inst.c"
if (f1->type && (f1->type != (T_NET)) && !f_const_promotion(f1, (T_NET)))
#line 1510
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1510
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(f1->type));
#line 1511 "filter/f-inst.c"
whati->f2 = f2;
#line 1511
const struct f_inst *child2 = f2;
#line 1511
do {
#line 1511
  what->size += child2->size;
#line 1511

#line 1511
} while (child2 = child2->next);
#line 1511 "filter/f-inst.c"
if (f2->type && (f2->type != (T_INT)) && !f_const_promotion(f2, (T_INT)))
#line 1511
  cf_error("Argument 2 of %s must be of type %s, got type %s",
#line 1511
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(f2->type));
#line 1512 "filter/f-inst.c"
whati->rtc = rtc;
#line 1524 "filter/f-inst.c"
what->type = T_ENUM_ROA;

#line 1530 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1530
    
#line 1530
      return what;
#line 1530

#line 1530
    /* Try to pre-calculate the result */
#line 1530
      #undef whati
#line 1530
  }
#line 1530

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
)
#line 1535
  {
#line 1535
    /* Allocate the structure */
#line 1535
    struct f_inst *what = fi_new(fi_code);
#line 1535
    uint constargs = 1;
#line 1535

#line 1535
    /* Initialize all the members */
#line 1535
  #define whati (&(what->i_FI_FORMAT))
#line 1535
  #line 1531 "filter/f-inst.c"
whati->f1 = f1;
#line 1531
const struct f_inst *child1 = f1;
#line 1531
do {
#line 1531
  what->size += child1->size;
#line 1531

#line 1531
  if (child1->fi_code != FI_CONSTANT)
#line 1531
    constargs = 0;
#line 1531

#line 1531
} while (child1 = child1->next);
#line 1532 "filter/f-inst.c"
what->type = T_STRING;

#line 1535 "filter/f-inst.c"
    /* If not constant, return the instruction itself */
#line 1535
    if (!constargs)
#line 1535
      return what;
#line 1535

#line 1535
    /* Try to pre-calculate the result */
#line 1535
    #line 1530 "filter/f-inst.c"
 {	/* Format */
    
#line 1531 "filter/f-inst.c"
;
     
#line 1532 "filter/f-inst.c"
 return fi_constant(what,  (struct f_val) { .type = T_STRING, .val.s = val_format_str(fpool, &v1) } );
  }

  
  #undef whati
#line 1535 "filter/f-inst.c"
  }
#line 1535

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
)
#line 698
  {
#line 698
    /* Allocate the structure */
#line 698
    struct f_inst *what = fi_new(fi_code);
#line 698
    
#line 698

#line 698
    /* Initialize all the members */
#line 698
  #define whati (&(what->i_FI_ASSERT))
#line 698
  #line 1537 "filter/f-inst.c"
whati->f1 = f1;
#line 1537
const struct f_inst *child1 = f1;
#line 1537
do {
#line 1537
  what->size += child1->size;
#line 1537

#line 1537
} while (child1 = child1->next);
#line 1537 "filter/f-inst.c"
if (f1->type && (f1->type != (T_BOOL)) && !f_const_promotion(f1, (T_BOOL)))
#line 1537
  cf_error("Argument 1 of %s must be of type %s, got type %s",
#line 1537
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(f1->type));
#line 1539 "filter/f-inst.c"
whati->s = s;

#line 698 "filter/decl.m4"
    /* If not constant, return the instruction itself */
#line 698
    
#line 698
      return what;
#line 698

#line 698
    /* Try to pre-calculate the result */
#line 698
      #undef whati
#line 698
  }
#line 698

#line 698

#line 536 "filter/decl.m4"

#undef v1
#undef v2
#undef v3
#undef vv

/* Line dumpers */
#define INDENT (((const char *) f_dump_line_indent_str) + sizeof(f_dump_line_indent_str) - (indent) - 1)
static const char f_dump_line_indent_str[] = "                                ";

#line 284 "filter/f-inst.c"
 /* Dump line for FI_ADD */
#line 284
static inline void f_dump_line_item_FI_ADD(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 284

#line 284
{
#line 284
#define item (&(item_->i_FI_ADD))
#line 284
#undef item
#line 284
}
#line 284

#line 289 "filter/f-inst.c"
 /* Dump line for FI_SUBTRACT */
#line 289
static inline void f_dump_line_item_FI_SUBTRACT(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 289

#line 289
{
#line 289
#define item (&(item_->i_FI_SUBTRACT))
#line 289
#undef item
#line 289
}
#line 289

#line 294 "filter/f-inst.c"
 /* Dump line for FI_MULTIPLY */
#line 294
static inline void f_dump_line_item_FI_MULTIPLY(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 294

#line 294
{
#line 294
#define item (&(item_->i_FI_MULTIPLY))
#line 294
#undef item
#line 294
}
#line 294

#line 300 "filter/f-inst.c"
 /* Dump line for FI_DIVIDE */
#line 300
static inline void f_dump_line_item_FI_DIVIDE(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 300

#line 300
{
#line 300
#define item (&(item_->i_FI_DIVIDE))
#line 300
#undef item
#line 300
}
#line 300

#line 310 "filter/f-inst.c"
 /* Dump line for FI_AND */
#line 310
static inline void f_dump_line_item_FI_AND(const struct f_line_item *item_, const int indent)
#line 310

#line 310
{
#line 310
#define item (&(item_->i_FI_AND))
#line 306 "filter/f-inst.c"
f_dump_line(item->fl2, indent + 1);
#line 310 "filter/f-inst.c"
#undef item
#line 310
}
#line 310

#line 321 "filter/f-inst.c"
 /* Dump line for FI_OR */
#line 321
static inline void f_dump_line_item_FI_OR(const struct f_line_item *item_, const int indent)
#line 321

#line 321
{
#line 321
#define item (&(item_->i_FI_OR))
#line 316 "filter/f-inst.c"
f_dump_line(item->fl2, indent + 1);
#line 321 "filter/f-inst.c"
#undef item
#line 321
}
#line 321

#line 331 "filter/f-inst.c"
 /* Dump line for FI_PAIR_CONSTRUCT */
#line 331
static inline void f_dump_line_item_FI_PAIR_CONSTRUCT(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 331

#line 331
{
#line 331
#define item (&(item_->i_FI_PAIR_CONSTRUCT))
#line 331
#undef item
#line 331
}
#line 331

#line 371 "filter/f-inst.c"
 /* Dump line for FI_EC_CONSTRUCT */
#line 371
static inline void f_dump_line_item_FI_EC_CONSTRUCT(const struct f_line_item *item_, const int indent)
#line 371

#line 371
{
#line 371
#define item (&(item_->i_FI_EC_CONSTRUCT))
#line 335 "filter/f-inst.c"
debug("%s" "ec subtype %s" "\n", INDENT, ec_subtype_str(item->ecs));
#line 335

#line 371 "filter/f-inst.c"
#undef item
#line 371
}
#line 371

#line 378 "filter/f-inst.c"
 /* Dump line for FI_LC_CONSTRUCT */
#line 378
static inline void f_dump_line_item_FI_LC_CONSTRUCT(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 378

#line 378
{
#line 378
#define item (&(item_->i_FI_LC_CONSTRUCT))
#line 378
#undef item
#line 378
}
#line 378

#line 428 "filter/f-inst.c"
 /* Dump line for FI_PATHMASK_CONSTRUCT */
#line 428
static inline void f_dump_line_item_FI_PATHMASK_CONSTRUCT(const struct f_line_item *item_, const int indent)
#line 428

#line 428
{
#line 428
#define item (&(item_->i_FI_PATHMASK_CONSTRUCT))
#line 379 "filter/f-inst.c"
  debug("%snumber of varargs %u\n", INDENT, item->varcount);
#line 428 "filter/f-inst.c"
#undef item
#line 428
}
#line 428

#line 435 "filter/f-inst.c"
 /* Dump line for FI_NEQ */
#line 435
static inline void f_dump_line_item_FI_NEQ(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 435

#line 435
{
#line 435
#define item (&(item_->i_FI_NEQ))
#line 435
#undef item
#line 435
}
#line 435

#line 442 "filter/f-inst.c"
 /* Dump line for FI_EQ */
#line 442
static inline void f_dump_line_item_FI_EQ(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 442

#line 442
{
#line 442
#define item (&(item_->i_FI_EQ))
#line 442
#undef item
#line 442
}
#line 442

#line 453 "filter/f-inst.c"
 /* Dump line for FI_LT */
#line 453
static inline void f_dump_line_item_FI_LT(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 453

#line 453
{
#line 453
#define item (&(item_->i_FI_LT))
#line 453
#undef item
#line 453
}
#line 453

#line 464 "filter/f-inst.c"
 /* Dump line for FI_LTE */
#line 464
static inline void f_dump_line_item_FI_LTE(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 464

#line 464
{
#line 464
#define item (&(item_->i_FI_LTE))
#line 464
#undef item
#line 464
}
#line 464

#line 469 "filter/f-inst.c"
 /* Dump line for FI_NOT */
#line 469
static inline void f_dump_line_item_FI_NOT(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 469

#line 469
{
#line 469
#define item (&(item_->i_FI_NOT))
#line 469
#undef item
#line 469
}
#line 469

#line 478 "filter/f-inst.c"
 /* Dump line for FI_MATCH */
#line 478
static inline void f_dump_line_item_FI_MATCH(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 478

#line 478
{
#line 478
#define item (&(item_->i_FI_MATCH))
#line 478
#undef item
#line 478
}
#line 478

#line 487 "filter/f-inst.c"
 /* Dump line for FI_NOT_MATCH */
#line 487
static inline void f_dump_line_item_FI_NOT_MATCH(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 487

#line 487
{
#line 487
#define item (&(item_->i_FI_NOT_MATCH))
#line 487
#undef item
#line 487
}
#line 487

#line 492 "filter/f-inst.c"
 /* Dump line for FI_DEFINED */
#line 492
static inline void f_dump_line_item_FI_DEFINED(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 492

#line 492
{
#line 492
#define item (&(item_->i_FI_DEFINED))
#line 492
#undef item
#line 492
}
#line 492

#line 504 "filter/f-inst.c"
 /* Dump line for FI_TYPE */
#line 504
static inline void f_dump_line_item_FI_TYPE(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 504

#line 504
{
#line 504
#define item (&(item_->i_FI_TYPE))
#line 504
#undef item
#line 504
}
#line 504

#line 509 "filter/f-inst.c"
 /* Dump line for FI_IS_V4 */
#line 509
static inline void f_dump_line_item_FI_IS_V4(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 509

#line 509
{
#line 509
#define item (&(item_->i_FI_IS_V4))
#line 509
#undef item
#line 509
}
#line 509

#line 522 "filter/f-inst.c"
 /* Dump line for FI_VAR_INIT */
#line 522
static inline void f_dump_line_item_FI_VAR_INIT(const struct f_line_item *item_, const int indent)
#line 522

#line 522
{
#line 522
#define item (&(item_->i_FI_VAR_INIT))
#line 512 "filter/f-inst.c"
debug("%s" "symbol %s" "\n", INDENT, item->sym->name);
#line 512

#line 522 "filter/f-inst.c"
#undef item
#line 522
}
#line 522

#line 531 "filter/f-inst.c"
 /* Dump line for FI_VAR_SET */
#line 531
static inline void f_dump_line_item_FI_VAR_SET(const struct f_line_item *item_, const int indent)
#line 531

#line 531
{
#line 531
#define item (&(item_->i_FI_VAR_SET))
#line 525 "filter/f-inst.c"
debug("%s" "symbol %s" "\n", INDENT, item->sym->name);
#line 525

#line 531 "filter/f-inst.c"
#undef item
#line 531
}
#line 531

#line 538 "filter/f-inst.c"
 /* Dump line for FI_VAR_GET */
#line 538
static inline void f_dump_line_item_FI_VAR_GET(const struct f_line_item *item_, const int indent)
#line 538

#line 538
{
#line 538
#define item (&(item_->i_FI_VAR_GET))
#line 532 "filter/f-inst.c"
debug("%s" "symbol %s" "\n", INDENT, item->sym->name);
#line 532

#line 538 "filter/f-inst.c"
#undef item
#line 538
}
#line 538

#line 551 "filter/f-inst.c"
 /* Dump line for FI_CONSTANT */
#line 551
static inline void f_dump_line_item_FI_CONSTANT(const struct f_line_item *item_, const int indent)
#line 551

#line 551
{
#line 551
#define item (&(item_->i_FI_CONSTANT))
#line 539 "filter/f-inst.c"
debug("%s" "value %s" "\n", INDENT, val_dump(&(item->val))
#line 539
    );
#line 539

#line 551 "filter/f-inst.c"
#undef item
#line 551
}
#line 551

#line 585 "filter/f-inst.c"
 /* Dump line for FI_FOR_INIT */
#line 585
static inline void f_dump_line_item_FI_FOR_INIT(const struct f_line_item *item_, const int indent)
#line 585

#line 585
{
#line 585
#define item (&(item_->i_FI_FOR_INIT))
#line 554 "filter/f-inst.c"
debug("%s" "symbol %s" "\n", INDENT, item->sym->name);
#line 554

#line 585 "filter/f-inst.c"
#undef item
#line 585
}
#line 585

#line 639 "filter/f-inst.c"
 /* Dump line for FI_FOR_NEXT */
#line 639
static inline void f_dump_line_item_FI_FOR_NEXT(const struct f_line_item *item_, const int indent)
#line 639

#line 639
{
#line 639
#define item (&(item_->i_FI_FOR_NEXT))
#line 587 "filter/f-inst.c"
debug("%s" "symbol %s" "\n", INDENT, item->sym->name);
#line 587

#line 630 "filter/f-inst.c"
f_dump_line(item->fl1, indent + 1);
#line 639 "filter/f-inst.c"
#undef item
#line 639
}
#line 639

#line 647 "filter/f-inst.c"
 /* Dump line for FI_CONDITION */
#line 647
static inline void f_dump_line_item_FI_CONDITION(const struct f_line_item *item_, const int indent)
#line 647

#line 647
{
#line 647
#define item (&(item_->i_FI_CONDITION))
#line 642 "filter/f-inst.c"
f_dump_line(item->fl2, indent + 1);
#line 644 "filter/f-inst.c"
f_dump_line(item->fl3, indent + 1);
#line 647 "filter/f-inst.c"
#undef item
#line 647
}
#line 647

#line 656 "filter/f-inst.c"
 /* Dump line for FI_PRINT */
#line 656
static inline void f_dump_line_item_FI_PRINT(const struct f_line_item *item_, const int indent)
#line 656

#line 656
{
#line 656
#define item (&(item_->i_FI_PRINT))
#line 649 "filter/f-inst.c"
  debug("%snumber of varargs %u\n", INDENT, item->varcount);
#line 656 "filter/f-inst.c"
#undef item
#line 656
}
#line 656

#line 663 "filter/f-inst.c"
 /* Dump line for FI_FLUSH */
#line 663
static inline void f_dump_line_item_FI_FLUSH(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 663

#line 663
{
#line 663
#define item (&(item_->i_FI_FLUSH))
#line 663
#undef item
#line 663
}
#line 663

#line 677 "filter/f-inst.c"
 /* Dump line for FI_DIE */
#line 677
static inline void f_dump_line_item_FI_DIE(const struct f_line_item *item_, const int indent)
#line 677

#line 677
{
#line 677
#define item (&(item_->i_FI_DIE))
#line 665 "filter/f-inst.c"
debug("%s" "%s" "\n", INDENT, filter_return_str(item->fret));
#line 665

#line 677 "filter/f-inst.c"
#undef item
#line 677
}
#line 677

#line 704 "filter/f-inst.c"
 /* Dump line for FI_RTA_GET */
#line 704
static inline void f_dump_line_item_FI_RTA_GET(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 704

#line 704
{
#line 704
#define item (&(item_->i_FI_RTA_GET))
#line 704
#undef item
#line 704
}
#line 704

#line 810 "filter/f-inst.c"
 /* Dump line for FI_RTA_SET */
#line 810
static inline void f_dump_line_item_FI_RTA_SET(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 810

#line 810
{
#line 810
#define item (&(item_->i_FI_RTA_SET))
#line 810
#undef item
#line 810
}
#line 810

#line 882 "filter/f-inst.c"
 /* Dump line for FI_EA_GET */
#line 882
static inline void f_dump_line_item_FI_EA_GET(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 882

#line 882
{
#line 882
#define item (&(item_->i_FI_EA_GET))
#line 882
#undef item
#line 882
}
#line 882

#line 949 "filter/f-inst.c"
 /* Dump line for FI_EA_SET */
#line 949
static inline void f_dump_line_item_FI_EA_SET(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 949

#line 949
{
#line 949
#define item (&(item_->i_FI_EA_SET))
#line 949
#undef item
#line 949
}
#line 949

#line 958 "filter/f-inst.c"
 /* Dump line for FI_EA_UNSET */
#line 958
static inline void f_dump_line_item_FI_EA_UNSET(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 958

#line 958
{
#line 958
#define item (&(item_->i_FI_EA_UNSET))
#line 958
#undef item
#line 958
}
#line 958

#line 970 "filter/f-inst.c"
 /* Dump line for FI_LENGTH */
#line 970
static inline void f_dump_line_item_FI_LENGTH(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 970

#line 970
{
#line 970
#define item (&(item_->i_FI_LENGTH))
#line 970
#undef item
#line 970
}
#line 970

#line 1005 "filter/f-inst.c"
 /* Dump line for FI_NET_SRC */
#line 1005
static inline void f_dump_line_item_FI_NET_SRC(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1005

#line 1005
{
#line 1005
#define item (&(item_->i_FI_NET_SRC))
#line 1005
#undef item
#line 1005
}
#line 1005

#line 1040 "filter/f-inst.c"
 /* Dump line for FI_NET_DST */
#line 1040
static inline void f_dump_line_item_FI_NET_DST(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1040

#line 1040
{
#line 1040
#define item (&(item_->i_FI_NET_DST))
#line 1040
#undef item
#line 1040
}
#line 1040

#line 1050 "filter/f-inst.c"
 /* Dump line for FI_ROA_MAXLEN */
#line 1050
static inline void f_dump_line_item_FI_ROA_MAXLEN(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1050

#line 1050
{
#line 1050
#define item (&(item_->i_FI_ROA_MAXLEN))
#line 1050
#undef item
#line 1050
}
#line 1050

#line 1077 "filter/f-inst.c"
 /* Dump line for FI_ASN */
#line 1077
static inline void f_dump_line_item_FI_ASN(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1077

#line 1077
{
#line 1077
#define item (&(item_->i_FI_ASN))
#line 1077
#undef item
#line 1077
}
#line 1077

#line 1082 "filter/f-inst.c"
 /* Dump line for FI_IP */
#line 1082
static inline void f_dump_line_item_FI_IP(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1082

#line 1082
{
#line 1082
#define item (&(item_->i_FI_IP))
#line 1082
#undef item
#line 1082
}
#line 1082

#line 1089 "filter/f-inst.c"
 /* Dump line for FI_ROUTE_DISTINGUISHER */
#line 1089
static inline void f_dump_line_item_FI_ROUTE_DISTINGUISHER(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1089

#line 1089
{
#line 1089
#define item (&(item_->i_FI_ROUTE_DISTINGUISHER))
#line 1089
#undef item
#line 1089
}
#line 1089

#line 1096 "filter/f-inst.c"
 /* Dump line for FI_AS_PATH_FIRST */
#line 1096
static inline void f_dump_line_item_FI_AS_PATH_FIRST(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1096

#line 1096
{
#line 1096
#define item (&(item_->i_FI_AS_PATH_FIRST))
#line 1096
#undef item
#line 1096
}
#line 1096

#line 1103 "filter/f-inst.c"
 /* Dump line for FI_AS_PATH_LAST */
#line 1103
static inline void f_dump_line_item_FI_AS_PATH_LAST(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1103

#line 1103
{
#line 1103
#define item (&(item_->i_FI_AS_PATH_LAST))
#line 1103
#undef item
#line 1103
}
#line 1103

#line 1108 "filter/f-inst.c"
 /* Dump line for FI_AS_PATH_LAST_NAG */
#line 1108
static inline void f_dump_line_item_FI_AS_PATH_LAST_NAG(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1108

#line 1108
{
#line 1108
#define item (&(item_->i_FI_AS_PATH_LAST_NAG))
#line 1108
#undef item
#line 1108
}
#line 1108

#line 1113 "filter/f-inst.c"
 /* Dump line for FI_PAIR_DATA */
#line 1113
static inline void f_dump_line_item_FI_PAIR_DATA(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1113

#line 1113
{
#line 1113
#define item (&(item_->i_FI_PAIR_DATA))
#line 1113
#undef item
#line 1113
}
#line 1113

#line 1118 "filter/f-inst.c"
 /* Dump line for FI_LC_DATA1 */
#line 1118
static inline void f_dump_line_item_FI_LC_DATA1(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1118

#line 1118
{
#line 1118
#define item (&(item_->i_FI_LC_DATA1))
#line 1118
#undef item
#line 1118
}
#line 1118

#line 1123 "filter/f-inst.c"
 /* Dump line for FI_LC_DATA2 */
#line 1123
static inline void f_dump_line_item_FI_LC_DATA2(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1123

#line 1123
{
#line 1123
#define item (&(item_->i_FI_LC_DATA2))
#line 1123
#undef item
#line 1123
}
#line 1123

#line 1157 "filter/f-inst.c"
 /* Dump line for FI_MIN */
#line 1157
static inline void f_dump_line_item_FI_MIN(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1157

#line 1157
{
#line 1157
#define item (&(item_->i_FI_MIN))
#line 1157
#undef item
#line 1157
}
#line 1157

#line 1191 "filter/f-inst.c"
 /* Dump line for FI_MAX */
#line 1191
static inline void f_dump_line_item_FI_MAX(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1191

#line 1191
{
#line 1191
#define item (&(item_->i_FI_MAX))
#line 1191
#undef item
#line 1191
}
#line 1191

#line 1217 "filter/f-inst.c"
 /* Dump line for FI_RETURN */
#line 1217
static inline void f_dump_line_item_FI_RETURN(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1217

#line 1217
{
#line 1217
#define item (&(item_->i_FI_RETURN))
#line 1217
#undef item
#line 1217
}
#line 1217

#line 1278 "filter/f-inst.c"
 /* Dump line for FI_CALL */
#line 1278
static inline void f_dump_line_item_FI_CALL(const struct f_line_item *item_, const int indent)
#line 1278

#line 1278
{
#line 1278
#define item (&(item_->i_FI_CALL))
#line 1219 "filter/f-inst.c"
  debug("%snumber of varargs %u\n", INDENT, item->varcount);
#line 1220 "filter/f-inst.c"
debug("%s" "symbol %s" "\n", INDENT, item->sym->name);
#line 1220

#line 1278 "filter/f-inst.c"
#undef item
#line 1278
}
#line 1278

#line 1283 "filter/f-inst.c"
 /* Dump line for FI_DROP_RESULT */
#line 1283
static inline void f_dump_line_item_FI_DROP_RESULT(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1283

#line 1283
{
#line 1283
#define item (&(item_->i_FI_DROP_RESULT))
#line 1283
#undef item
#line 1283
}
#line 1283

#line 1306 "filter/f-inst.c"
 /* Dump line for FI_SWITCH */
#line 1306
static inline void f_dump_line_item_FI_SWITCH(const struct f_line_item *item_, const int indent)
#line 1306

#line 1306
{
#line 1306
#define item (&(item_->i_FI_SWITCH))
#line 1286 "filter/f-inst.c"
debug("%s" "tree %p" "\n", INDENT, item->tree);
#line 1286

#line 1306 "filter/f-inst.c"
#undef item
#line 1306
}
#line 1306

#line 1314 "filter/f-inst.c"
 /* Dump line for FI_IP_MASK */
#line 1314
static inline void f_dump_line_item_FI_IP_MASK(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1314

#line 1314
{
#line 1314
#define item (&(item_->i_FI_IP_MASK))
#line 1314
#undef item
#line 1314
}
#line 1314

#line 1320 "filter/f-inst.c"
 /* Dump line for FI_PATH_PREPEND */
#line 1320
static inline void f_dump_line_item_FI_PATH_PREPEND(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1320

#line 1320
{
#line 1320
#define item (&(item_->i_FI_PATH_PREPEND))
#line 1320
#undef item
#line 1320
}
#line 1320

#line 1377 "filter/f-inst.c"
 /* Dump line for FI_CLIST_ADD */
#line 1377
static inline void f_dump_line_item_FI_CLIST_ADD(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1377

#line 1377
{
#line 1377
#define item (&(item_->i_FI_CLIST_ADD))
#line 1377
#undef item
#line 1377
}
#line 1377

#line 1432 "filter/f-inst.c"
 /* Dump line for FI_CLIST_DEL */
#line 1432
static inline void f_dump_line_item_FI_CLIST_DEL(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1432

#line 1432
{
#line 1432
#define item (&(item_->i_FI_CLIST_DEL))
#line 1432
#undef item
#line 1432
}
#line 1432

#line 1478 "filter/f-inst.c"
 /* Dump line for FI_CLIST_FILTER */
#line 1478
static inline void f_dump_line_item_FI_CLIST_FILTER(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1478

#line 1478
{
#line 1478
#define item (&(item_->i_FI_CLIST_FILTER))
#line 1478
#undef item
#line 1478
}
#line 1478

#line 1508 "filter/f-inst.c"
 /* Dump line for FI_ROA_CHECK_IMPLICIT */
#line 1508
static inline void f_dump_line_item_FI_ROA_CHECK_IMPLICIT(const struct f_line_item *item_, const int indent)
#line 1508

#line 1508
{
#line 1508
#define item (&(item_->i_FI_ROA_CHECK_IMPLICIT))
#line 1480 "filter/f-inst.c"
debug("%s" "route table %s" "\n", INDENT, item->rtc->name);
#line 1480

#line 1508 "filter/f-inst.c"
#undef item
#line 1508
}
#line 1508

#line 1530 "filter/f-inst.c"
 /* Dump line for FI_ROA_CHECK_EXPLICIT */
#line 1530
static inline void f_dump_line_item_FI_ROA_CHECK_EXPLICIT(const struct f_line_item *item_, const int indent)
#line 1530

#line 1530
{
#line 1530
#define item (&(item_->i_FI_ROA_CHECK_EXPLICIT))
#line 1512 "filter/f-inst.c"
debug("%s" "route table %s" "\n", INDENT, item->rtc->name);
#line 1512

#line 1530 "filter/f-inst.c"
#undef item
#line 1530
}
#line 1530

#line 1535 "filter/f-inst.c"
 /* Dump line for FI_FORMAT */
#line 1535
static inline void f_dump_line_item_FI_FORMAT(const struct f_line_item *item UNUSED, const int indent UNUSED)
#line 1535

#line 1535
{
#line 1535
#define item (&(item_->i_FI_FORMAT))
#line 1535
#undef item
#line 1535
}
#line 1535

#line 698 "filter/decl.m4"
 /* Dump line for FI_ASSERT */
#line 698
static inline void f_dump_line_item_FI_ASSERT(const struct f_line_item *item_, const int indent)
#line 698

#line 698
{
#line 698
#define item (&(item_->i_FI_ASSERT))
#line 1539 "filter/f-inst.c"
debug("%s" "string %s" "\n", INDENT, item->s);
#line 1539

#line 698 "filter/decl.m4"
#undef item
#line 698
}
#line 698

#line 546 "filter/decl.m4"


void f_dump_line(const struct f_line *dest, uint indent)
{
  if (!dest) {
    debug("%sNo filter line (NULL)\n", INDENT);
    return;
  }
  debug("%sFilter line %p (len=%u)\n", INDENT, dest, dest->len);
  for (uint i=0; i<dest->len; i++) {
    const struct f_line_item *item = &dest->items[i];
    debug("%sInstruction %s at line %u\n", INDENT, f_instruction_name_(item->fi_code), item->lineno);
    switch (item->fi_code) {
#line 284 "filter/f-inst.c"
 /* Dump line caller for FI_ADD */
#line 284
case FI_ADD: f_dump_line_item_FI_ADD(item, indent + 1); break;
#line 284

#line 289 "filter/f-inst.c"
 /* Dump line caller for FI_SUBTRACT */
#line 289
case FI_SUBTRACT: f_dump_line_item_FI_SUBTRACT(item, indent + 1); break;
#line 289

#line 294 "filter/f-inst.c"
 /* Dump line caller for FI_MULTIPLY */
#line 294
case FI_MULTIPLY: f_dump_line_item_FI_MULTIPLY(item, indent + 1); break;
#line 294

#line 300 "filter/f-inst.c"
 /* Dump line caller for FI_DIVIDE */
#line 300
case FI_DIVIDE: f_dump_line_item_FI_DIVIDE(item, indent + 1); break;
#line 300

#line 310 "filter/f-inst.c"
 /* Dump line caller for FI_AND */
#line 310
case FI_AND: f_dump_line_item_FI_AND(item, indent + 1); break;
#line 310

#line 321 "filter/f-inst.c"
 /* Dump line caller for FI_OR */
#line 321
case FI_OR: f_dump_line_item_FI_OR(item, indent + 1); break;
#line 321

#line 331 "filter/f-inst.c"
 /* Dump line caller for FI_PAIR_CONSTRUCT */
#line 331
case FI_PAIR_CONSTRUCT: f_dump_line_item_FI_PAIR_CONSTRUCT(item, indent + 1); break;
#line 331

#line 371 "filter/f-inst.c"
 /* Dump line caller for FI_EC_CONSTRUCT */
#line 371
case FI_EC_CONSTRUCT: f_dump_line_item_FI_EC_CONSTRUCT(item, indent + 1); break;
#line 371

#line 378 "filter/f-inst.c"
 /* Dump line caller for FI_LC_CONSTRUCT */
#line 378
case FI_LC_CONSTRUCT: f_dump_line_item_FI_LC_CONSTRUCT(item, indent + 1); break;
#line 378

#line 428 "filter/f-inst.c"
 /* Dump line caller for FI_PATHMASK_CONSTRUCT */
#line 428
case FI_PATHMASK_CONSTRUCT: f_dump_line_item_FI_PATHMASK_CONSTRUCT(item, indent + 1); break;
#line 428

#line 435 "filter/f-inst.c"
 /* Dump line caller for FI_NEQ */
#line 435
case FI_NEQ: f_dump_line_item_FI_NEQ(item, indent + 1); break;
#line 435

#line 442 "filter/f-inst.c"
 /* Dump line caller for FI_EQ */
#line 442
case FI_EQ: f_dump_line_item_FI_EQ(item, indent + 1); break;
#line 442

#line 453 "filter/f-inst.c"
 /* Dump line caller for FI_LT */
#line 453
case FI_LT: f_dump_line_item_FI_LT(item, indent + 1); break;
#line 453

#line 464 "filter/f-inst.c"
 /* Dump line caller for FI_LTE */
#line 464
case FI_LTE: f_dump_line_item_FI_LTE(item, indent + 1); break;
#line 464

#line 469 "filter/f-inst.c"
 /* Dump line caller for FI_NOT */
#line 469
case FI_NOT: f_dump_line_item_FI_NOT(item, indent + 1); break;
#line 469

#line 478 "filter/f-inst.c"
 /* Dump line caller for FI_MATCH */
#line 478
case FI_MATCH: f_dump_line_item_FI_MATCH(item, indent + 1); break;
#line 478

#line 487 "filter/f-inst.c"
 /* Dump line caller for FI_NOT_MATCH */
#line 487
case FI_NOT_MATCH: f_dump_line_item_FI_NOT_MATCH(item, indent + 1); break;
#line 487

#line 492 "filter/f-inst.c"
 /* Dump line caller for FI_DEFINED */
#line 492
case FI_DEFINED: f_dump_line_item_FI_DEFINED(item, indent + 1); break;
#line 492

#line 504 "filter/f-inst.c"
 /* Dump line caller for FI_TYPE */
#line 504
case FI_TYPE: f_dump_line_item_FI_TYPE(item, indent + 1); break;
#line 504

#line 509 "filter/f-inst.c"
 /* Dump line caller for FI_IS_V4 */
#line 509
case FI_IS_V4: f_dump_line_item_FI_IS_V4(item, indent + 1); break;
#line 509

#line 522 "filter/f-inst.c"
 /* Dump line caller for FI_VAR_INIT */
#line 522
case FI_VAR_INIT: f_dump_line_item_FI_VAR_INIT(item, indent + 1); break;
#line 522

#line 531 "filter/f-inst.c"
 /* Dump line caller for FI_VAR_SET */
#line 531
case FI_VAR_SET: f_dump_line_item_FI_VAR_SET(item, indent + 1); break;
#line 531

#line 538 "filter/f-inst.c"
 /* Dump line caller for FI_VAR_GET */
#line 538
case FI_VAR_GET: f_dump_line_item_FI_VAR_GET(item, indent + 1); break;
#line 538

#line 551 "filter/f-inst.c"
 /* Dump line caller for FI_CONSTANT */
#line 551
case FI_CONSTANT: f_dump_line_item_FI_CONSTANT(item, indent + 1); break;
#line 551

#line 585 "filter/f-inst.c"
 /* Dump line caller for FI_FOR_INIT */
#line 585
case FI_FOR_INIT: f_dump_line_item_FI_FOR_INIT(item, indent + 1); break;
#line 585

#line 639 "filter/f-inst.c"
 /* Dump line caller for FI_FOR_NEXT */
#line 639
case FI_FOR_NEXT: f_dump_line_item_FI_FOR_NEXT(item, indent + 1); break;
#line 639

#line 647 "filter/f-inst.c"
 /* Dump line caller for FI_CONDITION */
#line 647
case FI_CONDITION: f_dump_line_item_FI_CONDITION(item, indent + 1); break;
#line 647

#line 656 "filter/f-inst.c"
 /* Dump line caller for FI_PRINT */
#line 656
case FI_PRINT: f_dump_line_item_FI_PRINT(item, indent + 1); break;
#line 656

#line 663 "filter/f-inst.c"
 /* Dump line caller for FI_FLUSH */
#line 663
case FI_FLUSH: f_dump_line_item_FI_FLUSH(item, indent + 1); break;
#line 663

#line 677 "filter/f-inst.c"
 /* Dump line caller for FI_DIE */
#line 677
case FI_DIE: f_dump_line_item_FI_DIE(item, indent + 1); break;
#line 677

#line 704 "filter/f-inst.c"
 /* Dump line caller for FI_RTA_GET */
#line 704
case FI_RTA_GET: f_dump_line_item_FI_RTA_GET(item, indent + 1); break;
#line 704

#line 810 "filter/f-inst.c"
 /* Dump line caller for FI_RTA_SET */
#line 810
case FI_RTA_SET: f_dump_line_item_FI_RTA_SET(item, indent + 1); break;
#line 810

#line 882 "filter/f-inst.c"
 /* Dump line caller for FI_EA_GET */
#line 882
case FI_EA_GET: f_dump_line_item_FI_EA_GET(item, indent + 1); break;
#line 882

#line 949 "filter/f-inst.c"
 /* Dump line caller for FI_EA_SET */
#line 949
case FI_EA_SET: f_dump_line_item_FI_EA_SET(item, indent + 1); break;
#line 949

#line 958 "filter/f-inst.c"
 /* Dump line caller for FI_EA_UNSET */
#line 958
case FI_EA_UNSET: f_dump_line_item_FI_EA_UNSET(item, indent + 1); break;
#line 958

#line 970 "filter/f-inst.c"
 /* Dump line caller for FI_LENGTH */
#line 970
case FI_LENGTH: f_dump_line_item_FI_LENGTH(item, indent + 1); break;
#line 970

#line 1005 "filter/f-inst.c"
 /* Dump line caller for FI_NET_SRC */
#line 1005
case FI_NET_SRC: f_dump_line_item_FI_NET_SRC(item, indent + 1); break;
#line 1005

#line 1040 "filter/f-inst.c"
 /* Dump line caller for FI_NET_DST */
#line 1040
case FI_NET_DST: f_dump_line_item_FI_NET_DST(item, indent + 1); break;
#line 1040

#line 1050 "filter/f-inst.c"
 /* Dump line caller for FI_ROA_MAXLEN */
#line 1050
case FI_ROA_MAXLEN: f_dump_line_item_FI_ROA_MAXLEN(item, indent + 1); break;
#line 1050

#line 1077 "filter/f-inst.c"
 /* Dump line caller for FI_ASN */
#line 1077
case FI_ASN: f_dump_line_item_FI_ASN(item, indent + 1); break;
#line 1077

#line 1082 "filter/f-inst.c"
 /* Dump line caller for FI_IP */
#line 1082
case FI_IP: f_dump_line_item_FI_IP(item, indent + 1); break;
#line 1082

#line 1089 "filter/f-inst.c"
 /* Dump line caller for FI_ROUTE_DISTINGUISHER */
#line 1089
case FI_ROUTE_DISTINGUISHER: f_dump_line_item_FI_ROUTE_DISTINGUISHER(item, indent + 1); break;
#line 1089

#line 1096 "filter/f-inst.c"
 /* Dump line caller for FI_AS_PATH_FIRST */
#line 1096
case FI_AS_PATH_FIRST: f_dump_line_item_FI_AS_PATH_FIRST(item, indent + 1); break;
#line 1096

#line 1103 "filter/f-inst.c"
 /* Dump line caller for FI_AS_PATH_LAST */
#line 1103
case FI_AS_PATH_LAST: f_dump_line_item_FI_AS_PATH_LAST(item, indent + 1); break;
#line 1103

#line 1108 "filter/f-inst.c"
 /* Dump line caller for FI_AS_PATH_LAST_NAG */
#line 1108
case FI_AS_PATH_LAST_NAG: f_dump_line_item_FI_AS_PATH_LAST_NAG(item, indent + 1); break;
#line 1108

#line 1113 "filter/f-inst.c"
 /* Dump line caller for FI_PAIR_DATA */
#line 1113
case FI_PAIR_DATA: f_dump_line_item_FI_PAIR_DATA(item, indent + 1); break;
#line 1113

#line 1118 "filter/f-inst.c"
 /* Dump line caller for FI_LC_DATA1 */
#line 1118
case FI_LC_DATA1: f_dump_line_item_FI_LC_DATA1(item, indent + 1); break;
#line 1118

#line 1123 "filter/f-inst.c"
 /* Dump line caller for FI_LC_DATA2 */
#line 1123
case FI_LC_DATA2: f_dump_line_item_FI_LC_DATA2(item, indent + 1); break;
#line 1123

#line 1157 "filter/f-inst.c"
 /* Dump line caller for FI_MIN */
#line 1157
case FI_MIN: f_dump_line_item_FI_MIN(item, indent + 1); break;
#line 1157

#line 1191 "filter/f-inst.c"
 /* Dump line caller for FI_MAX */
#line 1191
case FI_MAX: f_dump_line_item_FI_MAX(item, indent + 1); break;
#line 1191

#line 1217 "filter/f-inst.c"
 /* Dump line caller for FI_RETURN */
#line 1217
case FI_RETURN: f_dump_line_item_FI_RETURN(item, indent + 1); break;
#line 1217

#line 1278 "filter/f-inst.c"
 /* Dump line caller for FI_CALL */
#line 1278
case FI_CALL: f_dump_line_item_FI_CALL(item, indent + 1); break;
#line 1278

#line 1283 "filter/f-inst.c"
 /* Dump line caller for FI_DROP_RESULT */
#line 1283
case FI_DROP_RESULT: f_dump_line_item_FI_DROP_RESULT(item, indent + 1); break;
#line 1283

#line 1306 "filter/f-inst.c"
 /* Dump line caller for FI_SWITCH */
#line 1306
case FI_SWITCH: f_dump_line_item_FI_SWITCH(item, indent + 1); break;
#line 1306

#line 1314 "filter/f-inst.c"
 /* Dump line caller for FI_IP_MASK */
#line 1314
case FI_IP_MASK: f_dump_line_item_FI_IP_MASK(item, indent + 1); break;
#line 1314

#line 1320 "filter/f-inst.c"
 /* Dump line caller for FI_PATH_PREPEND */
#line 1320
case FI_PATH_PREPEND: f_dump_line_item_FI_PATH_PREPEND(item, indent + 1); break;
#line 1320

#line 1377 "filter/f-inst.c"
 /* Dump line caller for FI_CLIST_ADD */
#line 1377
case FI_CLIST_ADD: f_dump_line_item_FI_CLIST_ADD(item, indent + 1); break;
#line 1377

#line 1432 "filter/f-inst.c"
 /* Dump line caller for FI_CLIST_DEL */
#line 1432
case FI_CLIST_DEL: f_dump_line_item_FI_CLIST_DEL(item, indent + 1); break;
#line 1432

#line 1478 "filter/f-inst.c"
 /* Dump line caller for FI_CLIST_FILTER */
#line 1478
case FI_CLIST_FILTER: f_dump_line_item_FI_CLIST_FILTER(item, indent + 1); break;
#line 1478

#line 1508 "filter/f-inst.c"
 /* Dump line caller for FI_ROA_CHECK_IMPLICIT */
#line 1508
case FI_ROA_CHECK_IMPLICIT: f_dump_line_item_FI_ROA_CHECK_IMPLICIT(item, indent + 1); break;
#line 1508

#line 1530 "filter/f-inst.c"
 /* Dump line caller for FI_ROA_CHECK_EXPLICIT */
#line 1530
case FI_ROA_CHECK_EXPLICIT: f_dump_line_item_FI_ROA_CHECK_EXPLICIT(item, indent + 1); break;
#line 1530

#line 1535 "filter/f-inst.c"
 /* Dump line caller for FI_FORMAT */
#line 1535
case FI_FORMAT: f_dump_line_item_FI_FORMAT(item, indent + 1); break;
#line 1535

#line 698 "filter/decl.m4"
 /* Dump line caller for FI_ASSERT */
#line 698
case FI_ASSERT: f_dump_line_item_FI_ASSERT(item, indent + 1); break;
#line 698

#line 559 "filter/decl.m4"

      default: bug("Unknown instruction %x in f_dump_line", item->fi_code);
    }
  }
  debug("%sFilter line %p dump done\n", INDENT, dest);
}

/* Linearize */
static uint
linearize(struct f_line *dest, const struct f_inst *what, uint pos)
{
  for ( ; what; what = what->next) {
    switch (what->fi_code) {
#line 284 "filter/f-inst.c"
 /* Linearize for FI_ADD */
#line 284
case FI_ADD: {
#line 284
#define whati (&(what->i_FI_ADD))
#line 284
#define item (&(dest->items[pos].i_FI_ADD))
#line 284
  #line 280 "filter/f-inst.c"

#line 280
pos = linearize(dest, whati->f1, pos);
#line 281 "filter/f-inst.c"

#line 281
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 284 "filter/f-inst.c"
#undef item
#line 284
  dest->items[pos].fi_code = what->fi_code;
#line 284
  dest->items[pos].flags = what->flags;
#line 284
  dest->items[pos].lineno = what->lineno;
#line 284
  break;
#line 284
}
#line 284

#line 289 "filter/f-inst.c"
 /* Linearize for FI_SUBTRACT */
#line 289
case FI_SUBTRACT: {
#line 289
#define whati (&(what->i_FI_SUBTRACT))
#line 289
#define item (&(dest->items[pos].i_FI_SUBTRACT))
#line 289
  #line 285 "filter/f-inst.c"

#line 285
pos = linearize(dest, whati->f1, pos);
#line 286 "filter/f-inst.c"

#line 286
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 289 "filter/f-inst.c"
#undef item
#line 289
  dest->items[pos].fi_code = what->fi_code;
#line 289
  dest->items[pos].flags = what->flags;
#line 289
  dest->items[pos].lineno = what->lineno;
#line 289
  break;
#line 289
}
#line 289

#line 294 "filter/f-inst.c"
 /* Linearize for FI_MULTIPLY */
#line 294
case FI_MULTIPLY: {
#line 294
#define whati (&(what->i_FI_MULTIPLY))
#line 294
#define item (&(dest->items[pos].i_FI_MULTIPLY))
#line 294
  #line 290 "filter/f-inst.c"

#line 290
pos = linearize(dest, whati->f1, pos);
#line 291 "filter/f-inst.c"

#line 291
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 294 "filter/f-inst.c"
#undef item
#line 294
  dest->items[pos].fi_code = what->fi_code;
#line 294
  dest->items[pos].flags = what->flags;
#line 294
  dest->items[pos].lineno = what->lineno;
#line 294
  break;
#line 294
}
#line 294

#line 300 "filter/f-inst.c"
 /* Linearize for FI_DIVIDE */
#line 300
case FI_DIVIDE: {
#line 300
#define whati (&(what->i_FI_DIVIDE))
#line 300
#define item (&(dest->items[pos].i_FI_DIVIDE))
#line 300
  #line 295 "filter/f-inst.c"

#line 295
pos = linearize(dest, whati->f1, pos);
#line 296 "filter/f-inst.c"

#line 296
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 300 "filter/f-inst.c"
#undef item
#line 300
  dest->items[pos].fi_code = what->fi_code;
#line 300
  dest->items[pos].flags = what->flags;
#line 300
  dest->items[pos].lineno = what->lineno;
#line 300
  break;
#line 300
}
#line 300

#line 310 "filter/f-inst.c"
 /* Linearize for FI_AND */
#line 310
case FI_AND: {
#line 310
#define whati (&(what->i_FI_AND))
#line 310
#define item (&(dest->items[pos].i_FI_AND))
#line 310
  #line 301 "filter/f-inst.c"

#line 301
pos = linearize(dest, whati->f1, pos);
#line 306 "filter/f-inst.c"
item->fl2 = f_linearize(whati->f2, 1);
#undef whati
#line 310 "filter/f-inst.c"
#undef item
#line 310
  dest->items[pos].fi_code = what->fi_code;
#line 310
  dest->items[pos].flags = what->flags;
#line 310
  dest->items[pos].lineno = what->lineno;
#line 310
  break;
#line 310
}
#line 310

#line 321 "filter/f-inst.c"
 /* Linearize for FI_OR */
#line 321
case FI_OR: {
#line 321
#define whati (&(what->i_FI_OR))
#line 321
#define item (&(dest->items[pos].i_FI_OR))
#line 321
  #line 311 "filter/f-inst.c"

#line 311
pos = linearize(dest, whati->f1, pos);
#line 316 "filter/f-inst.c"
item->fl2 = f_linearize(whati->f2, 1);
#undef whati
#line 321 "filter/f-inst.c"
#undef item
#line 321
  dest->items[pos].fi_code = what->fi_code;
#line 321
  dest->items[pos].flags = what->flags;
#line 321
  dest->items[pos].lineno = what->lineno;
#line 321
  break;
#line 321
}
#line 321

#line 331 "filter/f-inst.c"
 /* Linearize for FI_PAIR_CONSTRUCT */
#line 331
case FI_PAIR_CONSTRUCT: {
#line 331
#define whati (&(what->i_FI_PAIR_CONSTRUCT))
#line 331
#define item (&(dest->items[pos].i_FI_PAIR_CONSTRUCT))
#line 331
  #line 322 "filter/f-inst.c"

#line 322
pos = linearize(dest, whati->f1, pos);
#line 323 "filter/f-inst.c"

#line 323
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 331 "filter/f-inst.c"
#undef item
#line 331
  dest->items[pos].fi_code = what->fi_code;
#line 331
  dest->items[pos].flags = what->flags;
#line 331
  dest->items[pos].lineno = what->lineno;
#line 331
  break;
#line 331
}
#line 331

#line 371 "filter/f-inst.c"
 /* Linearize for FI_EC_CONSTRUCT */
#line 371
case FI_EC_CONSTRUCT: {
#line 371
#define whati (&(what->i_FI_EC_CONSTRUCT))
#line 371
#define item (&(dest->items[pos].i_FI_EC_CONSTRUCT))
#line 371
  #line 332 "filter/f-inst.c"

#line 332
pos = linearize(dest, whati->f1, pos);
#line 333 "filter/f-inst.c"

#line 333
pos = linearize(dest, whati->f2, pos);
#line 335 "filter/f-inst.c"
item->ecs = whati->ecs;
#line 335

#undef whati
#line 371 "filter/f-inst.c"
#undef item
#line 371
  dest->items[pos].fi_code = what->fi_code;
#line 371
  dest->items[pos].flags = what->flags;
#line 371
  dest->items[pos].lineno = what->lineno;
#line 371
  break;
#line 371
}
#line 371

#line 378 "filter/f-inst.c"
 /* Linearize for FI_LC_CONSTRUCT */
#line 378
case FI_LC_CONSTRUCT: {
#line 378
#define whati (&(what->i_FI_LC_CONSTRUCT))
#line 378
#define item (&(dest->items[pos].i_FI_LC_CONSTRUCT))
#line 378
  #line 372 "filter/f-inst.c"

#line 372
pos = linearize(dest, whati->f1, pos);
#line 373 "filter/f-inst.c"

#line 373
pos = linearize(dest, whati->f2, pos);
#line 374 "filter/f-inst.c"

#line 374
pos = linearize(dest, whati->f3, pos);
#undef whati
#line 378 "filter/f-inst.c"
#undef item
#line 378
  dest->items[pos].fi_code = what->fi_code;
#line 378
  dest->items[pos].flags = what->flags;
#line 378
  dest->items[pos].lineno = what->lineno;
#line 378
  break;
#line 378
}
#line 378

#line 428 "filter/f-inst.c"
 /* Linearize for FI_PATHMASK_CONSTRUCT */
#line 428
case FI_PATHMASK_CONSTRUCT: {
#line 428
#define whati (&(what->i_FI_PATHMASK_CONSTRUCT))
#line 428
#define item (&(dest->items[pos].i_FI_PATHMASK_CONSTRUCT))
#line 428
  #line 379 "filter/f-inst.c"
  pos = linearize(dest, whati->fvar, pos);
#line 379
  item->varcount = whati->varcount;
#undef whati
#line 428 "filter/f-inst.c"
#undef item
#line 428
  dest->items[pos].fi_code = what->fi_code;
#line 428
  dest->items[pos].flags = what->flags;
#line 428
  dest->items[pos].lineno = what->lineno;
#line 428
  break;
#line 428
}
#line 428

#line 435 "filter/f-inst.c"
 /* Linearize for FI_NEQ */
#line 435
case FI_NEQ: {
#line 435
#define whati (&(what->i_FI_NEQ))
#line 435
#define item (&(dest->items[pos].i_FI_NEQ))
#line 435
  #line 429 "filter/f-inst.c"

#line 429
pos = linearize(dest, whati->f1, pos);
#line 430 "filter/f-inst.c"

#line 430
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 435 "filter/f-inst.c"
#undef item
#line 435
  dest->items[pos].fi_code = what->fi_code;
#line 435
  dest->items[pos].flags = what->flags;
#line 435
  dest->items[pos].lineno = what->lineno;
#line 435
  break;
#line 435
}
#line 435

#line 442 "filter/f-inst.c"
 /* Linearize for FI_EQ */
#line 442
case FI_EQ: {
#line 442
#define whati (&(what->i_FI_EQ))
#line 442
#define item (&(dest->items[pos].i_FI_EQ))
#line 442
  #line 436 "filter/f-inst.c"

#line 436
pos = linearize(dest, whati->f1, pos);
#line 437 "filter/f-inst.c"

#line 437
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 442 "filter/f-inst.c"
#undef item
#line 442
  dest->items[pos].fi_code = what->fi_code;
#line 442
  dest->items[pos].flags = what->flags;
#line 442
  dest->items[pos].lineno = what->lineno;
#line 442
  break;
#line 442
}
#line 442

#line 453 "filter/f-inst.c"
 /* Linearize for FI_LT */
#line 453
case FI_LT: {
#line 453
#define whati (&(what->i_FI_LT))
#line 453
#define item (&(dest->items[pos].i_FI_LT))
#line 453
  #line 443 "filter/f-inst.c"

#line 443
pos = linearize(dest, whati->f1, pos);
#line 444 "filter/f-inst.c"

#line 444
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 453 "filter/f-inst.c"
#undef item
#line 453
  dest->items[pos].fi_code = what->fi_code;
#line 453
  dest->items[pos].flags = what->flags;
#line 453
  dest->items[pos].lineno = what->lineno;
#line 453
  break;
#line 453
}
#line 453

#line 464 "filter/f-inst.c"
 /* Linearize for FI_LTE */
#line 464
case FI_LTE: {
#line 464
#define whati (&(what->i_FI_LTE))
#line 464
#define item (&(dest->items[pos].i_FI_LTE))
#line 464
  #line 454 "filter/f-inst.c"

#line 454
pos = linearize(dest, whati->f1, pos);
#line 455 "filter/f-inst.c"

#line 455
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 464 "filter/f-inst.c"
#undef item
#line 464
  dest->items[pos].fi_code = what->fi_code;
#line 464
  dest->items[pos].flags = what->flags;
#line 464
  dest->items[pos].lineno = what->lineno;
#line 464
  break;
#line 464
}
#line 464

#line 469 "filter/f-inst.c"
 /* Linearize for FI_NOT */
#line 469
case FI_NOT: {
#line 469
#define whati (&(what->i_FI_NOT))
#line 469
#define item (&(dest->items[pos].i_FI_NOT))
#line 469
  #line 465 "filter/f-inst.c"

#line 465
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 469 "filter/f-inst.c"
#undef item
#line 469
  dest->items[pos].fi_code = what->fi_code;
#line 469
  dest->items[pos].flags = what->flags;
#line 469
  dest->items[pos].lineno = what->lineno;
#line 469
  break;
#line 469
}
#line 469

#line 478 "filter/f-inst.c"
 /* Linearize for FI_MATCH */
#line 478
case FI_MATCH: {
#line 478
#define whati (&(what->i_FI_MATCH))
#line 478
#define item (&(dest->items[pos].i_FI_MATCH))
#line 478
  #line 470 "filter/f-inst.c"

#line 470
pos = linearize(dest, whati->f1, pos);
#line 471 "filter/f-inst.c"

#line 471
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 478 "filter/f-inst.c"
#undef item
#line 478
  dest->items[pos].fi_code = what->fi_code;
#line 478
  dest->items[pos].flags = what->flags;
#line 478
  dest->items[pos].lineno = what->lineno;
#line 478
  break;
#line 478
}
#line 478

#line 487 "filter/f-inst.c"
 /* Linearize for FI_NOT_MATCH */
#line 487
case FI_NOT_MATCH: {
#line 487
#define whati (&(what->i_FI_NOT_MATCH))
#line 487
#define item (&(dest->items[pos].i_FI_NOT_MATCH))
#line 487
  #line 479 "filter/f-inst.c"

#line 479
pos = linearize(dest, whati->f1, pos);
#line 480 "filter/f-inst.c"

#line 480
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 487 "filter/f-inst.c"
#undef item
#line 487
  dest->items[pos].fi_code = what->fi_code;
#line 487
  dest->items[pos].flags = what->flags;
#line 487
  dest->items[pos].lineno = what->lineno;
#line 487
  break;
#line 487
}
#line 487

#line 492 "filter/f-inst.c"
 /* Linearize for FI_DEFINED */
#line 492
case FI_DEFINED: {
#line 492
#define whati (&(what->i_FI_DEFINED))
#line 492
#define item (&(dest->items[pos].i_FI_DEFINED))
#line 492
  #line 488 "filter/f-inst.c"

#line 488
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 492 "filter/f-inst.c"
#undef item
#line 492
  dest->items[pos].fi_code = what->fi_code;
#line 492
  dest->items[pos].flags = what->flags;
#line 492
  dest->items[pos].lineno = what->lineno;
#line 492
  break;
#line 492
}
#line 492

#line 504 "filter/f-inst.c"
 /* Linearize for FI_TYPE */
#line 504
case FI_TYPE: {
#line 504
#define whati (&(what->i_FI_TYPE))
#line 504
#define item (&(dest->items[pos].i_FI_TYPE))
#line 504
  #line 493 "filter/f-inst.c"

#line 493
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 504 "filter/f-inst.c"
#undef item
#line 504
  dest->items[pos].fi_code = what->fi_code;
#line 504
  dest->items[pos].flags = what->flags;
#line 504
  dest->items[pos].lineno = what->lineno;
#line 504
  break;
#line 504
}
#line 504

#line 509 "filter/f-inst.c"
 /* Linearize for FI_IS_V4 */
#line 509
case FI_IS_V4: {
#line 509
#define whati (&(what->i_FI_IS_V4))
#line 509
#define item (&(dest->items[pos].i_FI_IS_V4))
#line 509
  #line 505 "filter/f-inst.c"

#line 505
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 509 "filter/f-inst.c"
#undef item
#line 509
  dest->items[pos].fi_code = what->fi_code;
#line 509
  dest->items[pos].flags = what->flags;
#line 509
  dest->items[pos].lineno = what->lineno;
#line 509
  break;
#line 509
}
#line 509

#line 522 "filter/f-inst.c"
 /* Linearize for FI_VAR_INIT */
#line 522
case FI_VAR_INIT: {
#line 522
#define whati (&(what->i_FI_VAR_INIT))
#line 522
#define item (&(dest->items[pos].i_FI_VAR_INIT))
#line 522
  #line 511 "filter/f-inst.c"

#line 511
pos = linearize(dest, whati->f1, pos);
#line 512 "filter/f-inst.c"
item->sym = whati->sym;
#line 512

#undef whati
#line 522 "filter/f-inst.c"
#undef item
#line 522
  dest->items[pos].fi_code = what->fi_code;
#line 522
  dest->items[pos].flags = what->flags;
#line 522
  dest->items[pos].lineno = what->lineno;
#line 522
  break;
#line 522
}
#line 522

#line 531 "filter/f-inst.c"
 /* Linearize for FI_VAR_SET */
#line 531
case FI_VAR_SET: {
#line 531
#define whati (&(what->i_FI_VAR_SET))
#line 531
#define item (&(dest->items[pos].i_FI_VAR_SET))
#line 531
  #line 524 "filter/f-inst.c"

#line 524
pos = linearize(dest, whati->f1, pos);
#line 525 "filter/f-inst.c"
item->sym = whati->sym;
#line 525

#undef whati
#line 531 "filter/f-inst.c"
#undef item
#line 531
  dest->items[pos].fi_code = what->fi_code;
#line 531
  dest->items[pos].flags = what->flags;
#line 531
  dest->items[pos].lineno = what->lineno;
#line 531
  break;
#line 531
}
#line 531

#line 538 "filter/f-inst.c"
 /* Linearize for FI_VAR_GET */
#line 538
case FI_VAR_GET: {
#line 538
#define whati (&(what->i_FI_VAR_GET))
#line 538
#define item (&(dest->items[pos].i_FI_VAR_GET))
#line 538
  #line 532 "filter/f-inst.c"
item->sym = whati->sym;
#line 532

#undef whati
#line 538 "filter/f-inst.c"
#undef item
#line 538
  dest->items[pos].fi_code = what->fi_code;
#line 538
  dest->items[pos].flags = what->flags;
#line 538
  dest->items[pos].lineno = what->lineno;
#line 538
  break;
#line 538
}
#line 538

#line 551 "filter/f-inst.c"
 /* Linearize for FI_CONSTANT */
#line 551
case FI_CONSTANT: {
#line 551
#define whati (&(what->i_FI_CONSTANT))
#line 551
#define item (&(dest->items[pos].i_FI_CONSTANT))
#line 551
  #line 539 "filter/f-inst.c"
item->val = whati->val;
#line 539

#undef whati
#line 551 "filter/f-inst.c"
#undef item
#line 551
  dest->items[pos].fi_code = what->fi_code;
#line 551
  dest->items[pos].flags = what->flags;
#line 551
  dest->items[pos].lineno = what->lineno;
#line 551
  break;
#line 551
}
#line 551

#line 585 "filter/f-inst.c"
 /* Linearize for FI_FOR_INIT */
#line 585
case FI_FOR_INIT: {
#line 585
#define whati (&(what->i_FI_FOR_INIT))
#line 585
#define item (&(dest->items[pos].i_FI_FOR_INIT))
#line 585
  #line 553 "filter/f-inst.c"

#line 553
pos = linearize(dest, whati->f1, pos);
#line 554 "filter/f-inst.c"
item->sym = whati->sym;
#line 554

#undef whati
#line 585 "filter/f-inst.c"
#undef item
#line 585
  dest->items[pos].fi_code = what->fi_code;
#line 585
  dest->items[pos].flags = what->flags;
#line 585
  dest->items[pos].lineno = what->lineno;
#line 585
  break;
#line 585
}
#line 585

#line 639 "filter/f-inst.c"
 /* Linearize for FI_FOR_NEXT */
#line 639
case FI_FOR_NEXT: {
#line 639
#define whati (&(what->i_FI_FOR_NEXT))
#line 639
#define item (&(dest->items[pos].i_FI_FOR_NEXT))
#line 639
  #line 587 "filter/f-inst.c"
item->sym = whati->sym;
#line 587

#line 630 "filter/f-inst.c"
item->fl1 = f_linearize(whati->f1, 0);
#undef whati
#line 639 "filter/f-inst.c"
#undef item
#line 639
  dest->items[pos].fi_code = what->fi_code;
#line 639
  dest->items[pos].flags = what->flags;
#line 639
  dest->items[pos].lineno = what->lineno;
#line 639
  break;
#line 639
}
#line 639

#line 647 "filter/f-inst.c"
 /* Linearize for FI_CONDITION */
#line 647
case FI_CONDITION: {
#line 647
#define whati (&(what->i_FI_CONDITION))
#line 647
#define item (&(dest->items[pos].i_FI_CONDITION))
#line 647
  #line 640 "filter/f-inst.c"

#line 640
pos = linearize(dest, whati->f1, pos);
#line 642 "filter/f-inst.c"
item->fl2 = f_linearize(whati->f2, 0);
#line 644 "filter/f-inst.c"
item->fl3 = f_linearize(whati->f3, 0);
#undef whati
#line 647 "filter/f-inst.c"
#undef item
#line 647
  dest->items[pos].fi_code = what->fi_code;
#line 647
  dest->items[pos].flags = what->flags;
#line 647
  dest->items[pos].lineno = what->lineno;
#line 647
  break;
#line 647
}
#line 647

#line 656 "filter/f-inst.c"
 /* Linearize for FI_PRINT */
#line 656
case FI_PRINT: {
#line 656
#define whati (&(what->i_FI_PRINT))
#line 656
#define item (&(dest->items[pos].i_FI_PRINT))
#line 656
  #line 649 "filter/f-inst.c"
  pos = linearize(dest, whati->fvar, pos);
#line 649
  item->varcount = whati->varcount;
#undef whati
#line 656 "filter/f-inst.c"
#undef item
#line 656
  dest->items[pos].fi_code = what->fi_code;
#line 656
  dest->items[pos].flags = what->flags;
#line 656
  dest->items[pos].lineno = what->lineno;
#line 656
  break;
#line 656
}
#line 656

#line 663 "filter/f-inst.c"
 /* Linearize for FI_FLUSH */
#line 663
case FI_FLUSH: {
#line 663
#define whati (&(what->i_FI_FLUSH))
#line 663
#define item (&(dest->items[pos].i_FI_FLUSH))
#line 663
  #undef whati
#line 663
#undef item
#line 663
  dest->items[pos].fi_code = what->fi_code;
#line 663
  dest->items[pos].flags = what->flags;
#line 663
  dest->items[pos].lineno = what->lineno;
#line 663
  break;
#line 663
}
#line 663

#line 677 "filter/f-inst.c"
 /* Linearize for FI_DIE */
#line 677
case FI_DIE: {
#line 677
#define whati (&(what->i_FI_DIE))
#line 677
#define item (&(dest->items[pos].i_FI_DIE))
#line 677
  #line 665 "filter/f-inst.c"
item->fret = whati->fret;
#line 665

#undef whati
#line 677 "filter/f-inst.c"
#undef item
#line 677
  dest->items[pos].fi_code = what->fi_code;
#line 677
  dest->items[pos].flags = what->flags;
#line 677
  dest->items[pos].lineno = what->lineno;
#line 677
  break;
#line 677
}
#line 677

#line 704 "filter/f-inst.c"
 /* Linearize for FI_RTA_GET */
#line 704
case FI_RTA_GET: {
#line 704
#define whati (&(what->i_FI_RTA_GET))
#line 704
#define item (&(dest->items[pos].i_FI_RTA_GET))
#line 704
  #line 679 "filter/f-inst.c"
item->sa = whati->sa;
#line 679

#undef whati
#line 704 "filter/f-inst.c"
#undef item
#line 704
  dest->items[pos].fi_code = what->fi_code;
#line 704
  dest->items[pos].flags = what->flags;
#line 704
  dest->items[pos].lineno = what->lineno;
#line 704
  break;
#line 704
}
#line 704

#line 810 "filter/f-inst.c"
 /* Linearize for FI_RTA_SET */
#line 810
case FI_RTA_SET: {
#line 810
#define whati (&(what->i_FI_RTA_SET))
#line 810
#define item (&(dest->items[pos].i_FI_RTA_SET))
#line 810
  #line 706 "filter/f-inst.c"

#line 706
pos = linearize(dest, whati->f1, pos);
#line 707 "filter/f-inst.c"
item->sa = whati->sa;
#line 707

#undef whati
#line 810 "filter/f-inst.c"
#undef item
#line 810
  dest->items[pos].fi_code = what->fi_code;
#line 810
  dest->items[pos].flags = what->flags;
#line 810
  dest->items[pos].lineno = what->lineno;
#line 810
  break;
#line 810
}
#line 810

#line 882 "filter/f-inst.c"
 /* Linearize for FI_EA_GET */
#line 882
case FI_EA_GET: {
#line 882
#define whati (&(what->i_FI_EA_GET))
#line 882
#define item (&(dest->items[pos].i_FI_EA_GET))
#line 882
  #line 811 "filter/f-inst.c"
item->da = whati->da;
#line 811

#undef whati
#line 882 "filter/f-inst.c"
#undef item
#line 882
  dest->items[pos].fi_code = what->fi_code;
#line 882
  dest->items[pos].flags = what->flags;
#line 882
  dest->items[pos].lineno = what->lineno;
#line 882
  break;
#line 882
}
#line 882

#line 949 "filter/f-inst.c"
 /* Linearize for FI_EA_SET */
#line 949
case FI_EA_SET: {
#line 949
#define whati (&(what->i_FI_EA_SET))
#line 949
#define item (&(dest->items[pos].i_FI_EA_SET))
#line 949
  #line 885 "filter/f-inst.c"

#line 885
pos = linearize(dest, whati->f1, pos);
#line 886 "filter/f-inst.c"
item->da = whati->da;
#line 886

#undef whati
#line 949 "filter/f-inst.c"
#undef item
#line 949
  dest->items[pos].fi_code = what->fi_code;
#line 949
  dest->items[pos].flags = what->flags;
#line 949
  dest->items[pos].lineno = what->lineno;
#line 949
  break;
#line 949
}
#line 949

#line 958 "filter/f-inst.c"
 /* Linearize for FI_EA_UNSET */
#line 958
case FI_EA_UNSET: {
#line 958
#define whati (&(what->i_FI_EA_UNSET))
#line 958
#define item (&(dest->items[pos].i_FI_EA_UNSET))
#line 958
  #line 950 "filter/f-inst.c"
item->da = whati->da;
#line 950

#undef whati
#line 958 "filter/f-inst.c"
#undef item
#line 958
  dest->items[pos].fi_code = what->fi_code;
#line 958
  dest->items[pos].flags = what->flags;
#line 958
  dest->items[pos].lineno = what->lineno;
#line 958
  break;
#line 958
}
#line 958

#line 970 "filter/f-inst.c"
 /* Linearize for FI_LENGTH */
#line 970
case FI_LENGTH: {
#line 970
#define whati (&(what->i_FI_LENGTH))
#line 970
#define item (&(dest->items[pos].i_FI_LENGTH))
#line 970
  #line 959 "filter/f-inst.c"

#line 959
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 970 "filter/f-inst.c"
#undef item
#line 970
  dest->items[pos].fi_code = what->fi_code;
#line 970
  dest->items[pos].flags = what->flags;
#line 970
  dest->items[pos].lineno = what->lineno;
#line 970
  break;
#line 970
}
#line 970

#line 1005 "filter/f-inst.c"
 /* Linearize for FI_NET_SRC */
#line 1005
case FI_NET_SRC: {
#line 1005
#define whati (&(what->i_FI_NET_SRC))
#line 1005
#define item (&(dest->items[pos].i_FI_NET_SRC))
#line 1005
  #line 971 "filter/f-inst.c"

#line 971
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1005 "filter/f-inst.c"
#undef item
#line 1005
  dest->items[pos].fi_code = what->fi_code;
#line 1005
  dest->items[pos].flags = what->flags;
#line 1005
  dest->items[pos].lineno = what->lineno;
#line 1005
  break;
#line 1005
}
#line 1005

#line 1040 "filter/f-inst.c"
 /* Linearize for FI_NET_DST */
#line 1040
case FI_NET_DST: {
#line 1040
#define whati (&(what->i_FI_NET_DST))
#line 1040
#define item (&(dest->items[pos].i_FI_NET_DST))
#line 1040
  #line 1006 "filter/f-inst.c"

#line 1006
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1040 "filter/f-inst.c"
#undef item
#line 1040
  dest->items[pos].fi_code = what->fi_code;
#line 1040
  dest->items[pos].flags = what->flags;
#line 1040
  dest->items[pos].lineno = what->lineno;
#line 1040
  break;
#line 1040
}
#line 1040

#line 1050 "filter/f-inst.c"
 /* Linearize for FI_ROA_MAXLEN */
#line 1050
case FI_ROA_MAXLEN: {
#line 1050
#define whati (&(what->i_FI_ROA_MAXLEN))
#line 1050
#define item (&(dest->items[pos].i_FI_ROA_MAXLEN))
#line 1050
  #line 1041 "filter/f-inst.c"

#line 1041
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1050 "filter/f-inst.c"
#undef item
#line 1050
  dest->items[pos].fi_code = what->fi_code;
#line 1050
  dest->items[pos].flags = what->flags;
#line 1050
  dest->items[pos].lineno = what->lineno;
#line 1050
  break;
#line 1050
}
#line 1050

#line 1077 "filter/f-inst.c"
 /* Linearize for FI_ASN */
#line 1077
case FI_ASN: {
#line 1077
#define whati (&(what->i_FI_ASN))
#line 1077
#define item (&(dest->items[pos].i_FI_ASN))
#line 1077
  #line 1051 "filter/f-inst.c"

#line 1051
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1077 "filter/f-inst.c"
#undef item
#line 1077
  dest->items[pos].fi_code = what->fi_code;
#line 1077
  dest->items[pos].flags = what->flags;
#line 1077
  dest->items[pos].lineno = what->lineno;
#line 1077
  break;
#line 1077
}
#line 1077

#line 1082 "filter/f-inst.c"
 /* Linearize for FI_IP */
#line 1082
case FI_IP: {
#line 1082
#define whati (&(what->i_FI_IP))
#line 1082
#define item (&(dest->items[pos].i_FI_IP))
#line 1082
  #line 1078 "filter/f-inst.c"

#line 1078
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1082 "filter/f-inst.c"
#undef item
#line 1082
  dest->items[pos].fi_code = what->fi_code;
#line 1082
  dest->items[pos].flags = what->flags;
#line 1082
  dest->items[pos].lineno = what->lineno;
#line 1082
  break;
#line 1082
}
#line 1082

#line 1089 "filter/f-inst.c"
 /* Linearize for FI_ROUTE_DISTINGUISHER */
#line 1089
case FI_ROUTE_DISTINGUISHER: {
#line 1089
#define whati (&(what->i_FI_ROUTE_DISTINGUISHER))
#line 1089
#define item (&(dest->items[pos].i_FI_ROUTE_DISTINGUISHER))
#line 1089
  #line 1083 "filter/f-inst.c"

#line 1083
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1089 "filter/f-inst.c"
#undef item
#line 1089
  dest->items[pos].fi_code = what->fi_code;
#line 1089
  dest->items[pos].flags = what->flags;
#line 1089
  dest->items[pos].lineno = what->lineno;
#line 1089
  break;
#line 1089
}
#line 1089

#line 1096 "filter/f-inst.c"
 /* Linearize for FI_AS_PATH_FIRST */
#line 1096
case FI_AS_PATH_FIRST: {
#line 1096
#define whati (&(what->i_FI_AS_PATH_FIRST))
#line 1096
#define item (&(dest->items[pos].i_FI_AS_PATH_FIRST))
#line 1096
  #line 1090 "filter/f-inst.c"

#line 1090
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1096 "filter/f-inst.c"
#undef item
#line 1096
  dest->items[pos].fi_code = what->fi_code;
#line 1096
  dest->items[pos].flags = what->flags;
#line 1096
  dest->items[pos].lineno = what->lineno;
#line 1096
  break;
#line 1096
}
#line 1096

#line 1103 "filter/f-inst.c"
 /* Linearize for FI_AS_PATH_LAST */
#line 1103
case FI_AS_PATH_LAST: {
#line 1103
#define whati (&(what->i_FI_AS_PATH_LAST))
#line 1103
#define item (&(dest->items[pos].i_FI_AS_PATH_LAST))
#line 1103
  #line 1097 "filter/f-inst.c"

#line 1097
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1103 "filter/f-inst.c"
#undef item
#line 1103
  dest->items[pos].fi_code = what->fi_code;
#line 1103
  dest->items[pos].flags = what->flags;
#line 1103
  dest->items[pos].lineno = what->lineno;
#line 1103
  break;
#line 1103
}
#line 1103

#line 1108 "filter/f-inst.c"
 /* Linearize for FI_AS_PATH_LAST_NAG */
#line 1108
case FI_AS_PATH_LAST_NAG: {
#line 1108
#define whati (&(what->i_FI_AS_PATH_LAST_NAG))
#line 1108
#define item (&(dest->items[pos].i_FI_AS_PATH_LAST_NAG))
#line 1108
  #line 1104 "filter/f-inst.c"

#line 1104
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1108 "filter/f-inst.c"
#undef item
#line 1108
  dest->items[pos].fi_code = what->fi_code;
#line 1108
  dest->items[pos].flags = what->flags;
#line 1108
  dest->items[pos].lineno = what->lineno;
#line 1108
  break;
#line 1108
}
#line 1108

#line 1113 "filter/f-inst.c"
 /* Linearize for FI_PAIR_DATA */
#line 1113
case FI_PAIR_DATA: {
#line 1113
#define whati (&(what->i_FI_PAIR_DATA))
#line 1113
#define item (&(dest->items[pos].i_FI_PAIR_DATA))
#line 1113
  #line 1109 "filter/f-inst.c"

#line 1109
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1113 "filter/f-inst.c"
#undef item
#line 1113
  dest->items[pos].fi_code = what->fi_code;
#line 1113
  dest->items[pos].flags = what->flags;
#line 1113
  dest->items[pos].lineno = what->lineno;
#line 1113
  break;
#line 1113
}
#line 1113

#line 1118 "filter/f-inst.c"
 /* Linearize for FI_LC_DATA1 */
#line 1118
case FI_LC_DATA1: {
#line 1118
#define whati (&(what->i_FI_LC_DATA1))
#line 1118
#define item (&(dest->items[pos].i_FI_LC_DATA1))
#line 1118
  #line 1114 "filter/f-inst.c"

#line 1114
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1118 "filter/f-inst.c"
#undef item
#line 1118
  dest->items[pos].fi_code = what->fi_code;
#line 1118
  dest->items[pos].flags = what->flags;
#line 1118
  dest->items[pos].lineno = what->lineno;
#line 1118
  break;
#line 1118
}
#line 1118

#line 1123 "filter/f-inst.c"
 /* Linearize for FI_LC_DATA2 */
#line 1123
case FI_LC_DATA2: {
#line 1123
#define whati (&(what->i_FI_LC_DATA2))
#line 1123
#define item (&(dest->items[pos].i_FI_LC_DATA2))
#line 1123
  #line 1119 "filter/f-inst.c"

#line 1119
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1123 "filter/f-inst.c"
#undef item
#line 1123
  dest->items[pos].fi_code = what->fi_code;
#line 1123
  dest->items[pos].flags = what->flags;
#line 1123
  dest->items[pos].lineno = what->lineno;
#line 1123
  break;
#line 1123
}
#line 1123

#line 1157 "filter/f-inst.c"
 /* Linearize for FI_MIN */
#line 1157
case FI_MIN: {
#line 1157
#define whati (&(what->i_FI_MIN))
#line 1157
#define item (&(dest->items[pos].i_FI_MIN))
#line 1157
  #line 1124 "filter/f-inst.c"

#line 1124
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1157 "filter/f-inst.c"
#undef item
#line 1157
  dest->items[pos].fi_code = what->fi_code;
#line 1157
  dest->items[pos].flags = what->flags;
#line 1157
  dest->items[pos].lineno = what->lineno;
#line 1157
  break;
#line 1157
}
#line 1157

#line 1191 "filter/f-inst.c"
 /* Linearize for FI_MAX */
#line 1191
case FI_MAX: {
#line 1191
#define whati (&(what->i_FI_MAX))
#line 1191
#define item (&(dest->items[pos].i_FI_MAX))
#line 1191
  #line 1158 "filter/f-inst.c"

#line 1158
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1191 "filter/f-inst.c"
#undef item
#line 1191
  dest->items[pos].fi_code = what->fi_code;
#line 1191
  dest->items[pos].flags = what->flags;
#line 1191
  dest->items[pos].lineno = what->lineno;
#line 1191
  break;
#line 1191
}
#line 1191

#line 1217 "filter/f-inst.c"
 /* Linearize for FI_RETURN */
#line 1217
case FI_RETURN: {
#line 1217
#define whati (&(what->i_FI_RETURN))
#line 1217
#define item (&(dest->items[pos].i_FI_RETURN))
#line 1217
  #line 1194 "filter/f-inst.c"

#line 1194
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1217 "filter/f-inst.c"
#undef item
#line 1217
  dest->items[pos].fi_code = what->fi_code;
#line 1217
  dest->items[pos].flags = what->flags;
#line 1217
  dest->items[pos].lineno = what->lineno;
#line 1217
  break;
#line 1217
}
#line 1217

#line 1278 "filter/f-inst.c"
 /* Linearize for FI_CALL */
#line 1278
case FI_CALL: {
#line 1278
#define whati (&(what->i_FI_CALL))
#line 1278
#define item (&(dest->items[pos].i_FI_CALL))
#line 1278
  #line 1219 "filter/f-inst.c"
  pos = linearize(dest, whati->fvar, pos);
#line 1219
  item->varcount = whati->varcount;
#line 1220 "filter/f-inst.c"
item->sym = whati->sym;
#line 1220

#undef whati
#line 1278 "filter/f-inst.c"
#undef item
#line 1278
  dest->items[pos].fi_code = what->fi_code;
#line 1278
  dest->items[pos].flags = what->flags;
#line 1278
  dest->items[pos].lineno = what->lineno;
#line 1278
  break;
#line 1278
}
#line 1278

#line 1283 "filter/f-inst.c"
 /* Linearize for FI_DROP_RESULT */
#line 1283
case FI_DROP_RESULT: {
#line 1283
#define whati (&(what->i_FI_DROP_RESULT))
#line 1283
#define item (&(dest->items[pos].i_FI_DROP_RESULT))
#line 1283
  #line 1280 "filter/f-inst.c"

#line 1280
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1283 "filter/f-inst.c"
#undef item
#line 1283
  dest->items[pos].fi_code = what->fi_code;
#line 1283
  dest->items[pos].flags = what->flags;
#line 1283
  dest->items[pos].lineno = what->lineno;
#line 1283
  break;
#line 1283
}
#line 1283

#line 1306 "filter/f-inst.c"
 /* Linearize for FI_SWITCH */
#line 1306
case FI_SWITCH: {
#line 1306
#define whati (&(what->i_FI_SWITCH))
#line 1306
#define item (&(dest->items[pos].i_FI_SWITCH))
#line 1306
  #line 1284 "filter/f-inst.c"

#line 1284
pos = linearize(dest, whati->f1, pos);
#line 1286 "filter/f-inst.c"
item->tree = whati->tree;
#line 1286

#undef whati
#line 1306 "filter/f-inst.c"
#undef item
#line 1306
  dest->items[pos].fi_code = what->fi_code;
#line 1306
  dest->items[pos].flags = what->flags;
#line 1306
  dest->items[pos].lineno = what->lineno;
#line 1306
  break;
#line 1306
}
#line 1306

#line 1314 "filter/f-inst.c"
 /* Linearize for FI_IP_MASK */
#line 1314
case FI_IP_MASK: {
#line 1314
#define whati (&(what->i_FI_IP_MASK))
#line 1314
#define item (&(dest->items[pos].i_FI_IP_MASK))
#line 1314
  #line 1307 "filter/f-inst.c"

#line 1307
pos = linearize(dest, whati->f1, pos);
#line 1308 "filter/f-inst.c"

#line 1308
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 1314 "filter/f-inst.c"
#undef item
#line 1314
  dest->items[pos].fi_code = what->fi_code;
#line 1314
  dest->items[pos].flags = what->flags;
#line 1314
  dest->items[pos].lineno = what->lineno;
#line 1314
  break;
#line 1314
}
#line 1314

#line 1320 "filter/f-inst.c"
 /* Linearize for FI_PATH_PREPEND */
#line 1320
case FI_PATH_PREPEND: {
#line 1320
#define whati (&(what->i_FI_PATH_PREPEND))
#line 1320
#define item (&(dest->items[pos].i_FI_PATH_PREPEND))
#line 1320
  #line 1315 "filter/f-inst.c"

#line 1315
pos = linearize(dest, whati->f1, pos);
#line 1316 "filter/f-inst.c"

#line 1316
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 1320 "filter/f-inst.c"
#undef item
#line 1320
  dest->items[pos].fi_code = what->fi_code;
#line 1320
  dest->items[pos].flags = what->flags;
#line 1320
  dest->items[pos].lineno = what->lineno;
#line 1320
  break;
#line 1320
}
#line 1320

#line 1377 "filter/f-inst.c"
 /* Linearize for FI_CLIST_ADD */
#line 1377
case FI_CLIST_ADD: {
#line 1377
#define whati (&(what->i_FI_CLIST_ADD))
#line 1377
#define item (&(dest->items[pos].i_FI_CLIST_ADD))
#line 1377
  #line 1321 "filter/f-inst.c"

#line 1321
pos = linearize(dest, whati->f1, pos);
#line 1322 "filter/f-inst.c"

#line 1322
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 1377 "filter/f-inst.c"
#undef item
#line 1377
  dest->items[pos].fi_code = what->fi_code;
#line 1377
  dest->items[pos].flags = what->flags;
#line 1377
  dest->items[pos].lineno = what->lineno;
#line 1377
  break;
#line 1377
}
#line 1377

#line 1432 "filter/f-inst.c"
 /* Linearize for FI_CLIST_DEL */
#line 1432
case FI_CLIST_DEL: {
#line 1432
#define whati (&(what->i_FI_CLIST_DEL))
#line 1432
#define item (&(dest->items[pos].i_FI_CLIST_DEL))
#line 1432
  #line 1378 "filter/f-inst.c"

#line 1378
pos = linearize(dest, whati->f1, pos);
#line 1379 "filter/f-inst.c"

#line 1379
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 1432 "filter/f-inst.c"
#undef item
#line 1432
  dest->items[pos].fi_code = what->fi_code;
#line 1432
  dest->items[pos].flags = what->flags;
#line 1432
  dest->items[pos].lineno = what->lineno;
#line 1432
  break;
#line 1432
}
#line 1432

#line 1478 "filter/f-inst.c"
 /* Linearize for FI_CLIST_FILTER */
#line 1478
case FI_CLIST_FILTER: {
#line 1478
#define whati (&(what->i_FI_CLIST_FILTER))
#line 1478
#define item (&(dest->items[pos].i_FI_CLIST_FILTER))
#line 1478
  #line 1433 "filter/f-inst.c"

#line 1433
pos = linearize(dest, whati->f1, pos);
#line 1434 "filter/f-inst.c"

#line 1434
pos = linearize(dest, whati->f2, pos);
#undef whati
#line 1478 "filter/f-inst.c"
#undef item
#line 1478
  dest->items[pos].fi_code = what->fi_code;
#line 1478
  dest->items[pos].flags = what->flags;
#line 1478
  dest->items[pos].lineno = what->lineno;
#line 1478
  break;
#line 1478
}
#line 1478

#line 1508 "filter/f-inst.c"
 /* Linearize for FI_ROA_CHECK_IMPLICIT */
#line 1508
case FI_ROA_CHECK_IMPLICIT: {
#line 1508
#define whati (&(what->i_FI_ROA_CHECK_IMPLICIT))
#line 1508
#define item (&(dest->items[pos].i_FI_ROA_CHECK_IMPLICIT))
#line 1508
  #line 1480 "filter/f-inst.c"
item->rtc = whati->rtc;
#line 1480

#undef whati
#line 1508 "filter/f-inst.c"
#undef item
#line 1508
  dest->items[pos].fi_code = what->fi_code;
#line 1508
  dest->items[pos].flags = what->flags;
#line 1508
  dest->items[pos].lineno = what->lineno;
#line 1508
  break;
#line 1508
}
#line 1508

#line 1530 "filter/f-inst.c"
 /* Linearize for FI_ROA_CHECK_EXPLICIT */
#line 1530
case FI_ROA_CHECK_EXPLICIT: {
#line 1530
#define whati (&(what->i_FI_ROA_CHECK_EXPLICIT))
#line 1530
#define item (&(dest->items[pos].i_FI_ROA_CHECK_EXPLICIT))
#line 1530
  #line 1510 "filter/f-inst.c"

#line 1510
pos = linearize(dest, whati->f1, pos);
#line 1511 "filter/f-inst.c"

#line 1511
pos = linearize(dest, whati->f2, pos);
#line 1512 "filter/f-inst.c"
item->rtc = whati->rtc;
#line 1512

#undef whati
#line 1530 "filter/f-inst.c"
#undef item
#line 1530
  dest->items[pos].fi_code = what->fi_code;
#line 1530
  dest->items[pos].flags = what->flags;
#line 1530
  dest->items[pos].lineno = what->lineno;
#line 1530
  break;
#line 1530
}
#line 1530

#line 1535 "filter/f-inst.c"
 /* Linearize for FI_FORMAT */
#line 1535
case FI_FORMAT: {
#line 1535
#define whati (&(what->i_FI_FORMAT))
#line 1535
#define item (&(dest->items[pos].i_FI_FORMAT))
#line 1535
  #line 1531 "filter/f-inst.c"

#line 1531
pos = linearize(dest, whati->f1, pos);
#undef whati
#line 1535 "filter/f-inst.c"
#undef item
#line 1535
  dest->items[pos].fi_code = what->fi_code;
#line 1535
  dest->items[pos].flags = what->flags;
#line 1535
  dest->items[pos].lineno = what->lineno;
#line 1535
  break;
#line 1535
}
#line 1535

#line 698 "filter/decl.m4"
 /* Linearize for FI_ASSERT */
#line 698
case FI_ASSERT: {
#line 698
#define whati (&(what->i_FI_ASSERT))
#line 698
#define item (&(dest->items[pos].i_FI_ASSERT))
#line 698
  #line 1537 "filter/f-inst.c"

#line 1537
pos = linearize(dest, whati->f1, pos);
#line 1539 "filter/f-inst.c"
item->s = whati->s;
#line 1539

#undef whati
#line 698 "filter/decl.m4"
#undef item
#line 698
  dest->items[pos].fi_code = what->fi_code;
#line 698
  dest->items[pos].flags = what->flags;
#line 698
  dest->items[pos].lineno = what->lineno;
#line 698
  break;
#line 698
}
#line 698

#line 572 "filter/decl.m4"

    }
    pos++;
  }
  return pos;
}

struct f_line *
f_linearize_concat(const struct f_inst * const inst[], uint count, uint results)
{
  uint len = 0;
  for (uint i=0; i<count; i++)
    for (const struct f_inst *what = inst[i]; what; what = what->next)
      len += what->size;

  struct f_line *out = cfg_allocz(sizeof(struct f_line) + sizeof(struct f_line_item)*len);

  for (uint i=0; i<count; i++)
    out->len = linearize(out, inst[i], out->len);

    out->results = results;

#ifdef LOCAL_DEBUG
  f_dump_line(out, 0);
#endif
  return out;
}

/* Filter line comparison */
int
f_same(const struct f_line *fl1, const struct f_line *fl2)
{
  if ((!fl1) && (!fl2))
    return 1;
  if ((!fl1) || (!fl2))
    return 0;
  if (fl1->len != fl2->len)
    return 0;
  for (uint i=0; i<fl1->len; i++) {
#define f1_ (&(fl1->items[i]))
#define f2_ (&(fl2->items[i]))
    if (f1_->fi_code != f2_->fi_code)
      return 0;
    if (f1_->flags != f2_->flags)
      return 0;

    switch(f1_->fi_code) {
#line 284 "filter/f-inst.c"
 /* Comparison for FI_ADD */
#line 284
case FI_ADD:
#line 284
#define f1 (&(f1_->i_FI_ADD))
#line 284
#define f2 (&(f2_->i_FI_ADD))
#line 284
#undef f1
#line 284
#undef f2
#line 284
break;
#line 284

#line 289 "filter/f-inst.c"
 /* Comparison for FI_SUBTRACT */
#line 289
case FI_SUBTRACT:
#line 289
#define f1 (&(f1_->i_FI_SUBTRACT))
#line 289
#define f2 (&(f2_->i_FI_SUBTRACT))
#line 289
#undef f1
#line 289
#undef f2
#line 289
break;
#line 289

#line 294 "filter/f-inst.c"
 /* Comparison for FI_MULTIPLY */
#line 294
case FI_MULTIPLY:
#line 294
#define f1 (&(f1_->i_FI_MULTIPLY))
#line 294
#define f2 (&(f2_->i_FI_MULTIPLY))
#line 294
#undef f1
#line 294
#undef f2
#line 294
break;
#line 294

#line 300 "filter/f-inst.c"
 /* Comparison for FI_DIVIDE */
#line 300
case FI_DIVIDE:
#line 300
#define f1 (&(f1_->i_FI_DIVIDE))
#line 300
#define f2 (&(f2_->i_FI_DIVIDE))
#line 300
#undef f1
#line 300
#undef f2
#line 300
break;
#line 300

#line 310 "filter/f-inst.c"
 /* Comparison for FI_AND */
#line 310
case FI_AND:
#line 310
#define f1 (&(f1_->i_FI_AND))
#line 310
#define f2 (&(f2_->i_FI_AND))
#line 306 "filter/f-inst.c"
if (!f_same(f1->fl2, f2->fl2)) return 0;
#line 310 "filter/f-inst.c"
#undef f1
#line 310
#undef f2
#line 310
break;
#line 310

#line 321 "filter/f-inst.c"
 /* Comparison for FI_OR */
#line 321
case FI_OR:
#line 321
#define f1 (&(f1_->i_FI_OR))
#line 321
#define f2 (&(f2_->i_FI_OR))
#line 316 "filter/f-inst.c"
if (!f_same(f1->fl2, f2->fl2)) return 0;
#line 321 "filter/f-inst.c"
#undef f1
#line 321
#undef f2
#line 321
break;
#line 321

#line 331 "filter/f-inst.c"
 /* Comparison for FI_PAIR_CONSTRUCT */
#line 331
case FI_PAIR_CONSTRUCT:
#line 331
#define f1 (&(f1_->i_FI_PAIR_CONSTRUCT))
#line 331
#define f2 (&(f2_->i_FI_PAIR_CONSTRUCT))
#line 331
#undef f1
#line 331
#undef f2
#line 331
break;
#line 331

#line 371 "filter/f-inst.c"
 /* Comparison for FI_EC_CONSTRUCT */
#line 371
case FI_EC_CONSTRUCT:
#line 371
#define f1 (&(f1_->i_FI_EC_CONSTRUCT))
#line 371
#define f2 (&(f2_->i_FI_EC_CONSTRUCT))
#line 335 "filter/f-inst.c"
if (f1->ecs != f2->ecs) return 0;
#line 335

#line 335

#line 371 "filter/f-inst.c"
#undef f1
#line 371
#undef f2
#line 371
break;
#line 371

#line 378 "filter/f-inst.c"
 /* Comparison for FI_LC_CONSTRUCT */
#line 378
case FI_LC_CONSTRUCT:
#line 378
#define f1 (&(f1_->i_FI_LC_CONSTRUCT))
#line 378
#define f2 (&(f2_->i_FI_LC_CONSTRUCT))
#line 378
#undef f1
#line 378
#undef f2
#line 378
break;
#line 378

#line 428 "filter/f-inst.c"
 /* Comparison for FI_PATHMASK_CONSTRUCT */
#line 428
case FI_PATHMASK_CONSTRUCT:
#line 428
#define f1 (&(f1_->i_FI_PATHMASK_CONSTRUCT))
#line 428
#define f2 (&(f2_->i_FI_PATHMASK_CONSTRUCT))
#line 379 "filter/f-inst.c"
  if (f1->varcount != f2->varcount) return 0;
#line 428 "filter/f-inst.c"
#undef f1
#line 428
#undef f2
#line 428
break;
#line 428

#line 435 "filter/f-inst.c"
 /* Comparison for FI_NEQ */
#line 435
case FI_NEQ:
#line 435
#define f1 (&(f1_->i_FI_NEQ))
#line 435
#define f2 (&(f2_->i_FI_NEQ))
#line 435
#undef f1
#line 435
#undef f2
#line 435
break;
#line 435

#line 442 "filter/f-inst.c"
 /* Comparison for FI_EQ */
#line 442
case FI_EQ:
#line 442
#define f1 (&(f1_->i_FI_EQ))
#line 442
#define f2 (&(f2_->i_FI_EQ))
#line 442
#undef f1
#line 442
#undef f2
#line 442
break;
#line 442

#line 453 "filter/f-inst.c"
 /* Comparison for FI_LT */
#line 453
case FI_LT:
#line 453
#define f1 (&(f1_->i_FI_LT))
#line 453
#define f2 (&(f2_->i_FI_LT))
#line 453
#undef f1
#line 453
#undef f2
#line 453
break;
#line 453

#line 464 "filter/f-inst.c"
 /* Comparison for FI_LTE */
#line 464
case FI_LTE:
#line 464
#define f1 (&(f1_->i_FI_LTE))
#line 464
#define f2 (&(f2_->i_FI_LTE))
#line 464
#undef f1
#line 464
#undef f2
#line 464
break;
#line 464

#line 469 "filter/f-inst.c"
 /* Comparison for FI_NOT */
#line 469
case FI_NOT:
#line 469
#define f1 (&(f1_->i_FI_NOT))
#line 469
#define f2 (&(f2_->i_FI_NOT))
#line 469
#undef f1
#line 469
#undef f2
#line 469
break;
#line 469

#line 478 "filter/f-inst.c"
 /* Comparison for FI_MATCH */
#line 478
case FI_MATCH:
#line 478
#define f1 (&(f1_->i_FI_MATCH))
#line 478
#define f2 (&(f2_->i_FI_MATCH))
#line 478
#undef f1
#line 478
#undef f2
#line 478
break;
#line 478

#line 487 "filter/f-inst.c"
 /* Comparison for FI_NOT_MATCH */
#line 487
case FI_NOT_MATCH:
#line 487
#define f1 (&(f1_->i_FI_NOT_MATCH))
#line 487
#define f2 (&(f2_->i_FI_NOT_MATCH))
#line 487
#undef f1
#line 487
#undef f2
#line 487
break;
#line 487

#line 492 "filter/f-inst.c"
 /* Comparison for FI_DEFINED */
#line 492
case FI_DEFINED:
#line 492
#define f1 (&(f1_->i_FI_DEFINED))
#line 492
#define f2 (&(f2_->i_FI_DEFINED))
#line 492
#undef f1
#line 492
#undef f2
#line 492
break;
#line 492

#line 504 "filter/f-inst.c"
 /* Comparison for FI_TYPE */
#line 504
case FI_TYPE:
#line 504
#define f1 (&(f1_->i_FI_TYPE))
#line 504
#define f2 (&(f2_->i_FI_TYPE))
#line 504
#undef f1
#line 504
#undef f2
#line 504
break;
#line 504

#line 509 "filter/f-inst.c"
 /* Comparison for FI_IS_V4 */
#line 509
case FI_IS_V4:
#line 509
#define f1 (&(f1_->i_FI_IS_V4))
#line 509
#define f2 (&(f2_->i_FI_IS_V4))
#line 509
#undef f1
#line 509
#undef f2
#line 509
break;
#line 509

#line 522 "filter/f-inst.c"
 /* Comparison for FI_VAR_INIT */
#line 522
case FI_VAR_INIT:
#line 522
#define f1 (&(f1_->i_FI_VAR_INIT))
#line 522
#define f2 (&(f2_->i_FI_VAR_INIT))
#line 512 "filter/f-inst.c"
if (strcmp(f1->sym->name, f2->sym->name) || (f1->sym->class != f2->sym->class)) return 0;
#line 512

#line 512

#line 522 "filter/f-inst.c"
#undef f1
#line 522
#undef f2
#line 522
break;
#line 522

#line 531 "filter/f-inst.c"
 /* Comparison for FI_VAR_SET */
#line 531
case FI_VAR_SET:
#line 531
#define f1 (&(f1_->i_FI_VAR_SET))
#line 531
#define f2 (&(f2_->i_FI_VAR_SET))
#line 525 "filter/f-inst.c"
if (strcmp(f1->sym->name, f2->sym->name) || (f1->sym->class != f2->sym->class)) return 0;
#line 525

#line 525

#line 531 "filter/f-inst.c"
#undef f1
#line 531
#undef f2
#line 531
break;
#line 531

#line 538 "filter/f-inst.c"
 /* Comparison for FI_VAR_GET */
#line 538
case FI_VAR_GET:
#line 538
#define f1 (&(f1_->i_FI_VAR_GET))
#line 538
#define f2 (&(f2_->i_FI_VAR_GET))
#line 532 "filter/f-inst.c"
if (strcmp(f1->sym->name, f2->sym->name) || (f1->sym->class != f2->sym->class)) return 0;
#line 532

#line 532

#line 538 "filter/f-inst.c"
#undef f1
#line 538
#undef f2
#line 538
break;
#line 538

#line 551 "filter/f-inst.c"
 /* Comparison for FI_CONSTANT */
#line 551
case FI_CONSTANT:
#line 551
#define f1 (&(f1_->i_FI_CONSTANT))
#line 551
#define f2 (&(f2_->i_FI_CONSTANT))
#line 539 "filter/f-inst.c"
if ( !val_same(&(f1->val), &(f2->val)) ) return 0;
#line 539

#line 539

#line 551 "filter/f-inst.c"
#undef f1
#line 551
#undef f2
#line 551
break;
#line 551

#line 585 "filter/f-inst.c"
 /* Comparison for FI_FOR_INIT */
#line 585
case FI_FOR_INIT:
#line 585
#define f1 (&(f1_->i_FI_FOR_INIT))
#line 585
#define f2 (&(f2_->i_FI_FOR_INIT))
#line 554 "filter/f-inst.c"
if (strcmp(f1->sym->name, f2->sym->name) || (f1->sym->class != f2->sym->class)) return 0;
#line 554

#line 554

#line 585 "filter/f-inst.c"
#undef f1
#line 585
#undef f2
#line 585
break;
#line 585

#line 639 "filter/f-inst.c"
 /* Comparison for FI_FOR_NEXT */
#line 639
case FI_FOR_NEXT:
#line 639
#define f1 (&(f1_->i_FI_FOR_NEXT))
#line 639
#define f2 (&(f2_->i_FI_FOR_NEXT))
#line 587 "filter/f-inst.c"
if (strcmp(f1->sym->name, f2->sym->name) || (f1->sym->class != f2->sym->class)) return 0;
#line 587

#line 587

#line 630 "filter/f-inst.c"
if (!f_same(f1->fl1, f2->fl1)) return 0;
#line 639 "filter/f-inst.c"
#undef f1
#line 639
#undef f2
#line 639
break;
#line 639

#line 647 "filter/f-inst.c"
 /* Comparison for FI_CONDITION */
#line 647
case FI_CONDITION:
#line 647
#define f1 (&(f1_->i_FI_CONDITION))
#line 647
#define f2 (&(f2_->i_FI_CONDITION))
#line 642 "filter/f-inst.c"
if (!f_same(f1->fl2, f2->fl2)) return 0;
#line 644 "filter/f-inst.c"
if (!f_same(f1->fl3, f2->fl3)) return 0;
#line 647 "filter/f-inst.c"
#undef f1
#line 647
#undef f2
#line 647
break;
#line 647

#line 656 "filter/f-inst.c"
 /* Comparison for FI_PRINT */
#line 656
case FI_PRINT:
#line 656
#define f1 (&(f1_->i_FI_PRINT))
#line 656
#define f2 (&(f2_->i_FI_PRINT))
#line 649 "filter/f-inst.c"
  if (f1->varcount != f2->varcount) return 0;
#line 656 "filter/f-inst.c"
#undef f1
#line 656
#undef f2
#line 656
break;
#line 656

#line 663 "filter/f-inst.c"
 /* Comparison for FI_FLUSH */
#line 663
case FI_FLUSH:
#line 663
#define f1 (&(f1_->i_FI_FLUSH))
#line 663
#define f2 (&(f2_->i_FI_FLUSH))
#line 663
#undef f1
#line 663
#undef f2
#line 663
break;
#line 663

#line 677 "filter/f-inst.c"
 /* Comparison for FI_DIE */
#line 677
case FI_DIE:
#line 677
#define f1 (&(f1_->i_FI_DIE))
#line 677
#define f2 (&(f2_->i_FI_DIE))
#line 665 "filter/f-inst.c"
if (f1->fret != f2->fret) return 0;
#line 665

#line 665

#line 677 "filter/f-inst.c"
#undef f1
#line 677
#undef f2
#line 677
break;
#line 677

#line 704 "filter/f-inst.c"
 /* Comparison for FI_RTA_GET */
#line 704
case FI_RTA_GET:
#line 704
#define f1 (&(f1_->i_FI_RTA_GET))
#line 704
#define f2 (&(f2_->i_FI_RTA_GET))
#line 679 "filter/f-inst.c"
if (f1->sa.sa_code != f2->sa.sa_code) return 0;
#line 679

#line 679

#line 704 "filter/f-inst.c"
#undef f1
#line 704
#undef f2
#line 704
break;
#line 704

#line 810 "filter/f-inst.c"
 /* Comparison for FI_RTA_SET */
#line 810
case FI_RTA_SET:
#line 810
#define f1 (&(f1_->i_FI_RTA_SET))
#line 810
#define f2 (&(f2_->i_FI_RTA_SET))
#line 707 "filter/f-inst.c"
if (f1->sa.sa_code != f2->sa.sa_code) return 0;
#line 707

#line 707

#line 810 "filter/f-inst.c"
#undef f1
#line 810
#undef f2
#line 810
break;
#line 810

#line 882 "filter/f-inst.c"
 /* Comparison for FI_EA_GET */
#line 882
case FI_EA_GET:
#line 882
#define f1 (&(f1_->i_FI_EA_GET))
#line 882
#define f2 (&(f2_->i_FI_EA_GET))
#line 811 "filter/f-inst.c"
if (f1->da.ea_code != f2->da.ea_code) return 0;
#line 811

#line 811

#line 882 "filter/f-inst.c"
#undef f1
#line 882
#undef f2
#line 882
break;
#line 882

#line 949 "filter/f-inst.c"
 /* Comparison for FI_EA_SET */
#line 949
case FI_EA_SET:
#line 949
#define f1 (&(f1_->i_FI_EA_SET))
#line 949
#define f2 (&(f2_->i_FI_EA_SET))
#line 886 "filter/f-inst.c"
if (f1->da.ea_code != f2->da.ea_code) return 0;
#line 886

#line 886

#line 949 "filter/f-inst.c"
#undef f1
#line 949
#undef f2
#line 949
break;
#line 949

#line 958 "filter/f-inst.c"
 /* Comparison for FI_EA_UNSET */
#line 958
case FI_EA_UNSET:
#line 958
#define f1 (&(f1_->i_FI_EA_UNSET))
#line 958
#define f2 (&(f2_->i_FI_EA_UNSET))
#line 950 "filter/f-inst.c"
if (f1->da.ea_code != f2->da.ea_code) return 0;
#line 950

#line 950

#line 958 "filter/f-inst.c"
#undef f1
#line 958
#undef f2
#line 958
break;
#line 958

#line 970 "filter/f-inst.c"
 /* Comparison for FI_LENGTH */
#line 970
case FI_LENGTH:
#line 970
#define f1 (&(f1_->i_FI_LENGTH))
#line 970
#define f2 (&(f2_->i_FI_LENGTH))
#line 970
#undef f1
#line 970
#undef f2
#line 970
break;
#line 970

#line 1005 "filter/f-inst.c"
 /* Comparison for FI_NET_SRC */
#line 1005
case FI_NET_SRC:
#line 1005
#define f1 (&(f1_->i_FI_NET_SRC))
#line 1005
#define f2 (&(f2_->i_FI_NET_SRC))
#line 1005
#undef f1
#line 1005
#undef f2
#line 1005
break;
#line 1005

#line 1040 "filter/f-inst.c"
 /* Comparison for FI_NET_DST */
#line 1040
case FI_NET_DST:
#line 1040
#define f1 (&(f1_->i_FI_NET_DST))
#line 1040
#define f2 (&(f2_->i_FI_NET_DST))
#line 1040
#undef f1
#line 1040
#undef f2
#line 1040
break;
#line 1040

#line 1050 "filter/f-inst.c"
 /* Comparison for FI_ROA_MAXLEN */
#line 1050
case FI_ROA_MAXLEN:
#line 1050
#define f1 (&(f1_->i_FI_ROA_MAXLEN))
#line 1050
#define f2 (&(f2_->i_FI_ROA_MAXLEN))
#line 1050
#undef f1
#line 1050
#undef f2
#line 1050
break;
#line 1050

#line 1077 "filter/f-inst.c"
 /* Comparison for FI_ASN */
#line 1077
case FI_ASN:
#line 1077
#define f1 (&(f1_->i_FI_ASN))
#line 1077
#define f2 (&(f2_->i_FI_ASN))
#line 1077
#undef f1
#line 1077
#undef f2
#line 1077
break;
#line 1077

#line 1082 "filter/f-inst.c"
 /* Comparison for FI_IP */
#line 1082
case FI_IP:
#line 1082
#define f1 (&(f1_->i_FI_IP))
#line 1082
#define f2 (&(f2_->i_FI_IP))
#line 1082
#undef f1
#line 1082
#undef f2
#line 1082
break;
#line 1082

#line 1089 "filter/f-inst.c"
 /* Comparison for FI_ROUTE_DISTINGUISHER */
#line 1089
case FI_ROUTE_DISTINGUISHER:
#line 1089
#define f1 (&(f1_->i_FI_ROUTE_DISTINGUISHER))
#line 1089
#define f2 (&(f2_->i_FI_ROUTE_DISTINGUISHER))
#line 1089
#undef f1
#line 1089
#undef f2
#line 1089
break;
#line 1089

#line 1096 "filter/f-inst.c"
 /* Comparison for FI_AS_PATH_FIRST */
#line 1096
case FI_AS_PATH_FIRST:
#line 1096
#define f1 (&(f1_->i_FI_AS_PATH_FIRST))
#line 1096
#define f2 (&(f2_->i_FI_AS_PATH_FIRST))
#line 1096
#undef f1
#line 1096
#undef f2
#line 1096
break;
#line 1096

#line 1103 "filter/f-inst.c"
 /* Comparison for FI_AS_PATH_LAST */
#line 1103
case FI_AS_PATH_LAST:
#line 1103
#define f1 (&(f1_->i_FI_AS_PATH_LAST))
#line 1103
#define f2 (&(f2_->i_FI_AS_PATH_LAST))
#line 1103
#undef f1
#line 1103
#undef f2
#line 1103
break;
#line 1103

#line 1108 "filter/f-inst.c"
 /* Comparison for FI_AS_PATH_LAST_NAG */
#line 1108
case FI_AS_PATH_LAST_NAG:
#line 1108
#define f1 (&(f1_->i_FI_AS_PATH_LAST_NAG))
#line 1108
#define f2 (&(f2_->i_FI_AS_PATH_LAST_NAG))
#line 1108
#undef f1
#line 1108
#undef f2
#line 1108
break;
#line 1108

#line 1113 "filter/f-inst.c"
 /* Comparison for FI_PAIR_DATA */
#line 1113
case FI_PAIR_DATA:
#line 1113
#define f1 (&(f1_->i_FI_PAIR_DATA))
#line 1113
#define f2 (&(f2_->i_FI_PAIR_DATA))
#line 1113
#undef f1
#line 1113
#undef f2
#line 1113
break;
#line 1113

#line 1118 "filter/f-inst.c"
 /* Comparison for FI_LC_DATA1 */
#line 1118
case FI_LC_DATA1:
#line 1118
#define f1 (&(f1_->i_FI_LC_DATA1))
#line 1118
#define f2 (&(f2_->i_FI_LC_DATA1))
#line 1118
#undef f1
#line 1118
#undef f2
#line 1118
break;
#line 1118

#line 1123 "filter/f-inst.c"
 /* Comparison for FI_LC_DATA2 */
#line 1123
case FI_LC_DATA2:
#line 1123
#define f1 (&(f1_->i_FI_LC_DATA2))
#line 1123
#define f2 (&(f2_->i_FI_LC_DATA2))
#line 1123
#undef f1
#line 1123
#undef f2
#line 1123
break;
#line 1123

#line 1157 "filter/f-inst.c"
 /* Comparison for FI_MIN */
#line 1157
case FI_MIN:
#line 1157
#define f1 (&(f1_->i_FI_MIN))
#line 1157
#define f2 (&(f2_->i_FI_MIN))
#line 1157
#undef f1
#line 1157
#undef f2
#line 1157
break;
#line 1157

#line 1191 "filter/f-inst.c"
 /* Comparison for FI_MAX */
#line 1191
case FI_MAX:
#line 1191
#define f1 (&(f1_->i_FI_MAX))
#line 1191
#define f2 (&(f2_->i_FI_MAX))
#line 1191
#undef f1
#line 1191
#undef f2
#line 1191
break;
#line 1191

#line 1217 "filter/f-inst.c"
 /* Comparison for FI_RETURN */
#line 1217
case FI_RETURN:
#line 1217
#define f1 (&(f1_->i_FI_RETURN))
#line 1217
#define f2 (&(f2_->i_FI_RETURN))
#line 1217
#undef f1
#line 1217
#undef f2
#line 1217
break;
#line 1217

#line 1278 "filter/f-inst.c"
 /* Comparison for FI_CALL */
#line 1278
case FI_CALL:
#line 1278
#define f1 (&(f1_->i_FI_CALL))
#line 1278
#define f2 (&(f2_->i_FI_CALL))
#line 1219 "filter/f-inst.c"
  if (f1->varcount != f2->varcount) return 0;
#line 1220 "filter/f-inst.c"
if (strcmp(f1->sym->name, f2->sym->name) || (f1->sym->class != f2->sym->class)) return 0;
#line 1220

#line 1220


#line 1256 "filter/f-inst.c"
    if (!(f1->sym->flags & SYM_FLAG_SAME) && !(f1_->flags & FIF_RECURSIVE))
      return 0;

    #line 1278 "filter/f-inst.c"
#undef f1
#line 1278
#undef f2
#line 1278
break;
#line 1278

#line 1283 "filter/f-inst.c"
 /* Comparison for FI_DROP_RESULT */
#line 1283
case FI_DROP_RESULT:
#line 1283
#define f1 (&(f1_->i_FI_DROP_RESULT))
#line 1283
#define f2 (&(f2_->i_FI_DROP_RESULT))
#line 1283
#undef f1
#line 1283
#undef f2
#line 1283
break;
#line 1283

#line 1306 "filter/f-inst.c"
 /* Comparison for FI_SWITCH */
#line 1306
case FI_SWITCH:
#line 1306
#define f1 (&(f1_->i_FI_SWITCH))
#line 1306
#define f2 (&(f2_->i_FI_SWITCH))
#line 1286 "filter/f-inst.c"
if (!same_tree(f1->tree, f2->tree)) return 0;
#line 1286

#line 1286

#line 1306 "filter/f-inst.c"
#undef f1
#line 1306
#undef f2
#line 1306
break;
#line 1306

#line 1314 "filter/f-inst.c"
 /* Comparison for FI_IP_MASK */
#line 1314
case FI_IP_MASK:
#line 1314
#define f1 (&(f1_->i_FI_IP_MASK))
#line 1314
#define f2 (&(f2_->i_FI_IP_MASK))
#line 1314
#undef f1
#line 1314
#undef f2
#line 1314
break;
#line 1314

#line 1320 "filter/f-inst.c"
 /* Comparison for FI_PATH_PREPEND */
#line 1320
case FI_PATH_PREPEND:
#line 1320
#define f1 (&(f1_->i_FI_PATH_PREPEND))
#line 1320
#define f2 (&(f2_->i_FI_PATH_PREPEND))
#line 1320
#undef f1
#line 1320
#undef f2
#line 1320
break;
#line 1320

#line 1377 "filter/f-inst.c"
 /* Comparison for FI_CLIST_ADD */
#line 1377
case FI_CLIST_ADD:
#line 1377
#define f1 (&(f1_->i_FI_CLIST_ADD))
#line 1377
#define f2 (&(f2_->i_FI_CLIST_ADD))
#line 1377
#undef f1
#line 1377
#undef f2
#line 1377
break;
#line 1377

#line 1432 "filter/f-inst.c"
 /* Comparison for FI_CLIST_DEL */
#line 1432
case FI_CLIST_DEL:
#line 1432
#define f1 (&(f1_->i_FI_CLIST_DEL))
#line 1432
#define f2 (&(f2_->i_FI_CLIST_DEL))
#line 1432
#undef f1
#line 1432
#undef f2
#line 1432
break;
#line 1432

#line 1478 "filter/f-inst.c"
 /* Comparison for FI_CLIST_FILTER */
#line 1478
case FI_CLIST_FILTER:
#line 1478
#define f1 (&(f1_->i_FI_CLIST_FILTER))
#line 1478
#define f2 (&(f2_->i_FI_CLIST_FILTER))
#line 1478
#undef f1
#line 1478
#undef f2
#line 1478
break;
#line 1478

#line 1508 "filter/f-inst.c"
 /* Comparison for FI_ROA_CHECK_IMPLICIT */
#line 1508
case FI_ROA_CHECK_IMPLICIT:
#line 1508
#define f1 (&(f1_->i_FI_ROA_CHECK_IMPLICIT))
#line 1508
#define f2 (&(f2_->i_FI_ROA_CHECK_IMPLICIT))
#line 1480 "filter/f-inst.c"
if (strcmp(f1->rtc->name, f2->rtc->name)) return 0;
#line 1480

#line 1480

#line 1508 "filter/f-inst.c"
#undef f1
#line 1508
#undef f2
#line 1508
break;
#line 1508

#line 1530 "filter/f-inst.c"
 /* Comparison for FI_ROA_CHECK_EXPLICIT */
#line 1530
case FI_ROA_CHECK_EXPLICIT:
#line 1530
#define f1 (&(f1_->i_FI_ROA_CHECK_EXPLICIT))
#line 1530
#define f2 (&(f2_->i_FI_ROA_CHECK_EXPLICIT))
#line 1512 "filter/f-inst.c"
if (strcmp(f1->rtc->name, f2->rtc->name)) return 0;
#line 1512

#line 1512

#line 1530 "filter/f-inst.c"
#undef f1
#line 1530
#undef f2
#line 1530
break;
#line 1530

#line 1535 "filter/f-inst.c"
 /* Comparison for FI_FORMAT */
#line 1535
case FI_FORMAT:
#line 1535
#define f1 (&(f1_->i_FI_FORMAT))
#line 1535
#define f2 (&(f2_->i_FI_FORMAT))
#line 1535
#undef f1
#line 1535
#undef f2
#line 1535
break;
#line 1535

#line 698 "filter/decl.m4"
 /* Comparison for FI_ASSERT */
#line 698
case FI_ASSERT:
#line 698
#define f1 (&(f1_->i_FI_ASSERT))
#line 698
#define f2 (&(f2_->i_FI_ASSERT))
#line 1539 "filter/f-inst.c"
if (strcmp(f1->s, f2->s)) return 0;
#line 1539

#line 1539

#line 698 "filter/decl.m4"
#undef f1
#line 698
#undef f2
#line 698
break;
#line 698

#line 619 "filter/decl.m4"

    }
  }
#undef f1_
#undef f2_
  return 1;
}


/* Part of FI_SWITCH filter iterator */
static void
f_add_tree_lines(const struct f_tree *t, void *fit_)
{
  struct filter_iterator * fit = fit_;

  if (t->data)
    BUFFER_PUSH(fit->lines) = t->data;
}

/* Filter line iterator */
void
f_add_lines(const struct f_line_item *what, struct filter_iterator *fit)
{
  switch(what->fi_code) {
#line 284 "filter/f-inst.c"
 /* Iteration for FI_ADD */
#line 284
case FI_ADD:
#line 284
#define whati (&(what->i_FI_ADD))
#line 284
#undef whati
#line 284
break;
#line 284

#line 289 "filter/f-inst.c"
 /* Iteration for FI_SUBTRACT */
#line 289
case FI_SUBTRACT:
#line 289
#define whati (&(what->i_FI_SUBTRACT))
#line 289
#undef whati
#line 289
break;
#line 289

#line 294 "filter/f-inst.c"
 /* Iteration for FI_MULTIPLY */
#line 294
case FI_MULTIPLY:
#line 294
#define whati (&(what->i_FI_MULTIPLY))
#line 294
#undef whati
#line 294
break;
#line 294

#line 300 "filter/f-inst.c"
 /* Iteration for FI_DIVIDE */
#line 300
case FI_DIVIDE:
#line 300
#define whati (&(what->i_FI_DIVIDE))
#line 300
#undef whati
#line 300
break;
#line 300

#line 310 "filter/f-inst.c"
 /* Iteration for FI_AND */
#line 310
case FI_AND:
#line 310
#define whati (&(what->i_FI_AND))
#line 306 "filter/f-inst.c"
if (whati->fl2) BUFFER_PUSH(fit->lines) = whati->fl2;
#line 310 "filter/f-inst.c"
#undef whati
#line 310
break;
#line 310

#line 321 "filter/f-inst.c"
 /* Iteration for FI_OR */
#line 321
case FI_OR:
#line 321
#define whati (&(what->i_FI_OR))
#line 316 "filter/f-inst.c"
if (whati->fl2) BUFFER_PUSH(fit->lines) = whati->fl2;
#line 321 "filter/f-inst.c"
#undef whati
#line 321
break;
#line 321

#line 331 "filter/f-inst.c"
 /* Iteration for FI_PAIR_CONSTRUCT */
#line 331
case FI_PAIR_CONSTRUCT:
#line 331
#define whati (&(what->i_FI_PAIR_CONSTRUCT))
#line 331
#undef whati
#line 331
break;
#line 331

#line 371 "filter/f-inst.c"
 /* Iteration for FI_EC_CONSTRUCT */
#line 371
case FI_EC_CONSTRUCT:
#line 371
#define whati (&(what->i_FI_EC_CONSTRUCT))
#line 371
#undef whati
#line 371
break;
#line 371

#line 378 "filter/f-inst.c"
 /* Iteration for FI_LC_CONSTRUCT */
#line 378
case FI_LC_CONSTRUCT:
#line 378
#define whati (&(what->i_FI_LC_CONSTRUCT))
#line 378
#undef whati
#line 378
break;
#line 378

#line 428 "filter/f-inst.c"
 /* Iteration for FI_PATHMASK_CONSTRUCT */
#line 428
case FI_PATHMASK_CONSTRUCT:
#line 428
#define whati (&(what->i_FI_PATHMASK_CONSTRUCT))
#line 428
#undef whati
#line 428
break;
#line 428

#line 435 "filter/f-inst.c"
 /* Iteration for FI_NEQ */
#line 435
case FI_NEQ:
#line 435
#define whati (&(what->i_FI_NEQ))
#line 435
#undef whati
#line 435
break;
#line 435

#line 442 "filter/f-inst.c"
 /* Iteration for FI_EQ */
#line 442
case FI_EQ:
#line 442
#define whati (&(what->i_FI_EQ))
#line 442
#undef whati
#line 442
break;
#line 442

#line 453 "filter/f-inst.c"
 /* Iteration for FI_LT */
#line 453
case FI_LT:
#line 453
#define whati (&(what->i_FI_LT))
#line 453
#undef whati
#line 453
break;
#line 453

#line 464 "filter/f-inst.c"
 /* Iteration for FI_LTE */
#line 464
case FI_LTE:
#line 464
#define whati (&(what->i_FI_LTE))
#line 464
#undef whati
#line 464
break;
#line 464

#line 469 "filter/f-inst.c"
 /* Iteration for FI_NOT */
#line 469
case FI_NOT:
#line 469
#define whati (&(what->i_FI_NOT))
#line 469
#undef whati
#line 469
break;
#line 469

#line 478 "filter/f-inst.c"
 /* Iteration for FI_MATCH */
#line 478
case FI_MATCH:
#line 478
#define whati (&(what->i_FI_MATCH))
#line 478
#undef whati
#line 478
break;
#line 478

#line 487 "filter/f-inst.c"
 /* Iteration for FI_NOT_MATCH */
#line 487
case FI_NOT_MATCH:
#line 487
#define whati (&(what->i_FI_NOT_MATCH))
#line 487
#undef whati
#line 487
break;
#line 487

#line 492 "filter/f-inst.c"
 /* Iteration for FI_DEFINED */
#line 492
case FI_DEFINED:
#line 492
#define whati (&(what->i_FI_DEFINED))
#line 492
#undef whati
#line 492
break;
#line 492

#line 504 "filter/f-inst.c"
 /* Iteration for FI_TYPE */
#line 504
case FI_TYPE:
#line 504
#define whati (&(what->i_FI_TYPE))
#line 504
#undef whati
#line 504
break;
#line 504

#line 509 "filter/f-inst.c"
 /* Iteration for FI_IS_V4 */
#line 509
case FI_IS_V4:
#line 509
#define whati (&(what->i_FI_IS_V4))
#line 509
#undef whati
#line 509
break;
#line 509

#line 522 "filter/f-inst.c"
 /* Iteration for FI_VAR_INIT */
#line 522
case FI_VAR_INIT:
#line 522
#define whati (&(what->i_FI_VAR_INIT))
#line 522
#undef whati
#line 522
break;
#line 522

#line 531 "filter/f-inst.c"
 /* Iteration for FI_VAR_SET */
#line 531
case FI_VAR_SET:
#line 531
#define whati (&(what->i_FI_VAR_SET))
#line 531
#undef whati
#line 531
break;
#line 531

#line 538 "filter/f-inst.c"
 /* Iteration for FI_VAR_GET */
#line 538
case FI_VAR_GET:
#line 538
#define whati (&(what->i_FI_VAR_GET))
#line 538
#undef whati
#line 538
break;
#line 538

#line 551 "filter/f-inst.c"
 /* Iteration for FI_CONSTANT */
#line 551
case FI_CONSTANT:
#line 551
#define whati (&(what->i_FI_CONSTANT))
#line 551
#undef whati
#line 551
break;
#line 551

#line 585 "filter/f-inst.c"
 /* Iteration for FI_FOR_INIT */
#line 585
case FI_FOR_INIT:
#line 585
#define whati (&(what->i_FI_FOR_INIT))
#line 585
#undef whati
#line 585
break;
#line 585

#line 639 "filter/f-inst.c"
 /* Iteration for FI_FOR_NEXT */
#line 639
case FI_FOR_NEXT:
#line 639
#define whati (&(what->i_FI_FOR_NEXT))
#line 630 "filter/f-inst.c"
if (whati->fl1) BUFFER_PUSH(fit->lines) = whati->fl1;
#line 639 "filter/f-inst.c"
#undef whati
#line 639
break;
#line 639

#line 647 "filter/f-inst.c"
 /* Iteration for FI_CONDITION */
#line 647
case FI_CONDITION:
#line 647
#define whati (&(what->i_FI_CONDITION))
#line 642 "filter/f-inst.c"
if (whati->fl2) BUFFER_PUSH(fit->lines) = whati->fl2;
#line 644 "filter/f-inst.c"
if (whati->fl3) BUFFER_PUSH(fit->lines) = whati->fl3;
#line 647 "filter/f-inst.c"
#undef whati
#line 647
break;
#line 647

#line 656 "filter/f-inst.c"
 /* Iteration for FI_PRINT */
#line 656
case FI_PRINT:
#line 656
#define whati (&(what->i_FI_PRINT))
#line 656
#undef whati
#line 656
break;
#line 656

#line 663 "filter/f-inst.c"
 /* Iteration for FI_FLUSH */
#line 663
case FI_FLUSH:
#line 663
#define whati (&(what->i_FI_FLUSH))
#line 663
#undef whati
#line 663
break;
#line 663

#line 677 "filter/f-inst.c"
 /* Iteration for FI_DIE */
#line 677
case FI_DIE:
#line 677
#define whati (&(what->i_FI_DIE))
#line 677
#undef whati
#line 677
break;
#line 677

#line 704 "filter/f-inst.c"
 /* Iteration for FI_RTA_GET */
#line 704
case FI_RTA_GET:
#line 704
#define whati (&(what->i_FI_RTA_GET))
#line 704
#undef whati
#line 704
break;
#line 704

#line 810 "filter/f-inst.c"
 /* Iteration for FI_RTA_SET */
#line 810
case FI_RTA_SET:
#line 810
#define whati (&(what->i_FI_RTA_SET))
#line 810
#undef whati
#line 810
break;
#line 810

#line 882 "filter/f-inst.c"
 /* Iteration for FI_EA_GET */
#line 882
case FI_EA_GET:
#line 882
#define whati (&(what->i_FI_EA_GET))
#line 882
#undef whati
#line 882
break;
#line 882

#line 949 "filter/f-inst.c"
 /* Iteration for FI_EA_SET */
#line 949
case FI_EA_SET:
#line 949
#define whati (&(what->i_FI_EA_SET))
#line 949
#undef whati
#line 949
break;
#line 949

#line 958 "filter/f-inst.c"
 /* Iteration for FI_EA_UNSET */
#line 958
case FI_EA_UNSET:
#line 958
#define whati (&(what->i_FI_EA_UNSET))
#line 958
#undef whati
#line 958
break;
#line 958

#line 970 "filter/f-inst.c"
 /* Iteration for FI_LENGTH */
#line 970
case FI_LENGTH:
#line 970
#define whati (&(what->i_FI_LENGTH))
#line 970
#undef whati
#line 970
break;
#line 970

#line 1005 "filter/f-inst.c"
 /* Iteration for FI_NET_SRC */
#line 1005
case FI_NET_SRC:
#line 1005
#define whati (&(what->i_FI_NET_SRC))
#line 1005
#undef whati
#line 1005
break;
#line 1005

#line 1040 "filter/f-inst.c"
 /* Iteration for FI_NET_DST */
#line 1040
case FI_NET_DST:
#line 1040
#define whati (&(what->i_FI_NET_DST))
#line 1040
#undef whati
#line 1040
break;
#line 1040

#line 1050 "filter/f-inst.c"
 /* Iteration for FI_ROA_MAXLEN */
#line 1050
case FI_ROA_MAXLEN:
#line 1050
#define whati (&(what->i_FI_ROA_MAXLEN))
#line 1050
#undef whati
#line 1050
break;
#line 1050

#line 1077 "filter/f-inst.c"
 /* Iteration for FI_ASN */
#line 1077
case FI_ASN:
#line 1077
#define whati (&(what->i_FI_ASN))
#line 1077
#undef whati
#line 1077
break;
#line 1077

#line 1082 "filter/f-inst.c"
 /* Iteration for FI_IP */
#line 1082
case FI_IP:
#line 1082
#define whati (&(what->i_FI_IP))
#line 1082
#undef whati
#line 1082
break;
#line 1082

#line 1089 "filter/f-inst.c"
 /* Iteration for FI_ROUTE_DISTINGUISHER */
#line 1089
case FI_ROUTE_DISTINGUISHER:
#line 1089
#define whati (&(what->i_FI_ROUTE_DISTINGUISHER))
#line 1089
#undef whati
#line 1089
break;
#line 1089

#line 1096 "filter/f-inst.c"
 /* Iteration for FI_AS_PATH_FIRST */
#line 1096
case FI_AS_PATH_FIRST:
#line 1096
#define whati (&(what->i_FI_AS_PATH_FIRST))
#line 1096
#undef whati
#line 1096
break;
#line 1096

#line 1103 "filter/f-inst.c"
 /* Iteration for FI_AS_PATH_LAST */
#line 1103
case FI_AS_PATH_LAST:
#line 1103
#define whati (&(what->i_FI_AS_PATH_LAST))
#line 1103
#undef whati
#line 1103
break;
#line 1103

#line 1108 "filter/f-inst.c"
 /* Iteration for FI_AS_PATH_LAST_NAG */
#line 1108
case FI_AS_PATH_LAST_NAG:
#line 1108
#define whati (&(what->i_FI_AS_PATH_LAST_NAG))
#line 1108
#undef whati
#line 1108
break;
#line 1108

#line 1113 "filter/f-inst.c"
 /* Iteration for FI_PAIR_DATA */
#line 1113
case FI_PAIR_DATA:
#line 1113
#define whati (&(what->i_FI_PAIR_DATA))
#line 1113
#undef whati
#line 1113
break;
#line 1113

#line 1118 "filter/f-inst.c"
 /* Iteration for FI_LC_DATA1 */
#line 1118
case FI_LC_DATA1:
#line 1118
#define whati (&(what->i_FI_LC_DATA1))
#line 1118
#undef whati
#line 1118
break;
#line 1118

#line 1123 "filter/f-inst.c"
 /* Iteration for FI_LC_DATA2 */
#line 1123
case FI_LC_DATA2:
#line 1123
#define whati (&(what->i_FI_LC_DATA2))
#line 1123
#undef whati
#line 1123
break;
#line 1123

#line 1157 "filter/f-inst.c"
 /* Iteration for FI_MIN */
#line 1157
case FI_MIN:
#line 1157
#define whati (&(what->i_FI_MIN))
#line 1157
#undef whati
#line 1157
break;
#line 1157

#line 1191 "filter/f-inst.c"
 /* Iteration for FI_MAX */
#line 1191
case FI_MAX:
#line 1191
#define whati (&(what->i_FI_MAX))
#line 1191
#undef whati
#line 1191
break;
#line 1191

#line 1217 "filter/f-inst.c"
 /* Iteration for FI_RETURN */
#line 1217
case FI_RETURN:
#line 1217
#define whati (&(what->i_FI_RETURN))
#line 1217
#undef whati
#line 1217
break;
#line 1217

#line 1278 "filter/f-inst.c"
 /* Iteration for FI_CALL */
#line 1278
case FI_CALL:
#line 1278
#define whati (&(what->i_FI_CALL))

#line 1260 "filter/f-inst.c"
    if (!(what->flags & FIF_RECURSIVE))
      BUFFER_PUSH(fit->lines) = whati->sym->function;

    #line 1278 "filter/f-inst.c"
#undef whati
#line 1278
break;
#line 1278

#line 1283 "filter/f-inst.c"
 /* Iteration for FI_DROP_RESULT */
#line 1283
case FI_DROP_RESULT:
#line 1283
#define whati (&(what->i_FI_DROP_RESULT))
#line 1283
#undef whati
#line 1283
break;
#line 1283

#line 1306 "filter/f-inst.c"
 /* Iteration for FI_SWITCH */
#line 1306
case FI_SWITCH:
#line 1306
#define whati (&(what->i_FI_SWITCH))

#line 1289 "filter/f-inst.c"
      tree_walk(whati->tree, f_add_tree_lines, fit);

    #line 1306 "filter/f-inst.c"
#undef whati
#line 1306
break;
#line 1306

#line 1314 "filter/f-inst.c"
 /* Iteration for FI_IP_MASK */
#line 1314
case FI_IP_MASK:
#line 1314
#define whati (&(what->i_FI_IP_MASK))
#line 1314
#undef whati
#line 1314
break;
#line 1314

#line 1320 "filter/f-inst.c"
 /* Iteration for FI_PATH_PREPEND */
#line 1320
case FI_PATH_PREPEND:
#line 1320
#define whati (&(what->i_FI_PATH_PREPEND))
#line 1320
#undef whati
#line 1320
break;
#line 1320

#line 1377 "filter/f-inst.c"
 /* Iteration for FI_CLIST_ADD */
#line 1377
case FI_CLIST_ADD:
#line 1377
#define whati (&(what->i_FI_CLIST_ADD))
#line 1377
#undef whati
#line 1377
break;
#line 1377

#line 1432 "filter/f-inst.c"
 /* Iteration for FI_CLIST_DEL */
#line 1432
case FI_CLIST_DEL:
#line 1432
#define whati (&(what->i_FI_CLIST_DEL))
#line 1432
#undef whati
#line 1432
break;
#line 1432

#line 1478 "filter/f-inst.c"
 /* Iteration for FI_CLIST_FILTER */
#line 1478
case FI_CLIST_FILTER:
#line 1478
#define whati (&(what->i_FI_CLIST_FILTER))
#line 1478
#undef whati
#line 1478
break;
#line 1478

#line 1508 "filter/f-inst.c"
 /* Iteration for FI_ROA_CHECK_IMPLICIT */
#line 1508
case FI_ROA_CHECK_IMPLICIT:
#line 1508
#define whati (&(what->i_FI_ROA_CHECK_IMPLICIT))
#line 1508
#undef whati
#line 1508
break;
#line 1508

#line 1530 "filter/f-inst.c"
 /* Iteration for FI_ROA_CHECK_EXPLICIT */
#line 1530
case FI_ROA_CHECK_EXPLICIT:
#line 1530
#define whati (&(what->i_FI_ROA_CHECK_EXPLICIT))
#line 1530
#undef whati
#line 1530
break;
#line 1530

#line 1535 "filter/f-inst.c"
 /* Iteration for FI_FORMAT */
#line 1535
case FI_FORMAT:
#line 1535
#define whati (&(what->i_FI_FORMAT))
#line 1535
#undef whati
#line 1535
break;
#line 1535

#line 698 "filter/decl.m4"
 /* Iteration for FI_ASSERT */
#line 698
case FI_ASSERT:
#line 698
#define whati (&(what->i_FI_ASSERT))
#line 698
#undef whati
#line 698
break;
#line 698

#line 643 "filter/decl.m4"

  }
}


#if defined(__GNUC__) && __GNUC__ >= 6
#pragma GCC diagnostic pop
#endif

