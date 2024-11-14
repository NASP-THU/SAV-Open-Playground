#line 459 "filter/decl.m4"

#line 284 "filter/f-inst.c"
 /* Constructor for FI_ADD */
#line 284
  case FI_ADD:
#line 284
  #define whati (&(what->i_FI_ADD))
#line 284
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 284
  #line 279 "filter/f-inst.c"
 {
    
#line 280 "filter/f-inst.c"
 
#line 280 "filter/f-inst.c"
 
#line 280
if (v1.type != (T_INT))
#line 280
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 280
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v1.type));
#line 280
;
    
#line 281 "filter/f-inst.c"
 
#line 281 "filter/f-inst.c"
 
#line 281
if (v2.type != (T_INT))
#line 281
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 281
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 281
;
     
#line 282 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.i + v2.val.i } ; fstk->vcnt++; } while (0);
  }
  
  #undef whati
#line 284 "filter/f-inst.c"
  break;
#line 284

#line 284

#line 289 "filter/f-inst.c"
 /* Constructor for FI_SUBTRACT */
#line 289
  case FI_SUBTRACT:
#line 289
  #define whati (&(what->i_FI_SUBTRACT))
#line 289
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 289
  #line 284 "filter/f-inst.c"
 {
    
#line 285 "filter/f-inst.c"
 
#line 285 "filter/f-inst.c"
 
#line 285
if (v1.type != (T_INT))
#line 285
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 285
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v1.type));
#line 285
;
    
#line 286 "filter/f-inst.c"
 
#line 286 "filter/f-inst.c"
 
#line 286
if (v2.type != (T_INT))
#line 286
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 286
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 286
;
     
#line 287 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.i - v2.val.i } ; fstk->vcnt++; } while (0);
  }
  
  #undef whati
#line 289 "filter/f-inst.c"
  break;
#line 289

#line 289

#line 294 "filter/f-inst.c"
 /* Constructor for FI_MULTIPLY */
#line 294
  case FI_MULTIPLY:
#line 294
  #define whati (&(what->i_FI_MULTIPLY))
#line 294
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 294
  #line 289 "filter/f-inst.c"
 {
    
#line 290 "filter/f-inst.c"
 
#line 290 "filter/f-inst.c"
 
#line 290
if (v1.type != (T_INT))
#line 290
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 290
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v1.type));
#line 290
;
    
#line 291 "filter/f-inst.c"
 
#line 291 "filter/f-inst.c"
 
#line 291
if (v2.type != (T_INT))
#line 291
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 291
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 291
;
     
#line 292 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.i * v2.val.i } ; fstk->vcnt++; } while (0);
  }
  
  #undef whati
#line 294 "filter/f-inst.c"
  break;
#line 294

#line 294

#line 300 "filter/f-inst.c"
 /* Constructor for FI_DIVIDE */
#line 300
  case FI_DIVIDE:
#line 300
  #define whati (&(what->i_FI_DIVIDE))
#line 300
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 300
  #line 294 "filter/f-inst.c"
 {
    
#line 295 "filter/f-inst.c"
 
#line 295 "filter/f-inst.c"
 
#line 295
if (v1.type != (T_INT))
#line 295
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 295
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v1.type));
#line 295
;
    
#line 296 "filter/f-inst.c"
 
#line 296 "filter/f-inst.c"
 
#line 296
if (v2.type != (T_INT))
#line 296
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 296
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 296
;
    if (v2.val.i == 0) runtime( "Mother told me not to divide by 0" );
     
#line 298 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.i / v2.val.i } ; fstk->vcnt++; } while (0);
  }
  
  #undef whati
#line 300 "filter/f-inst.c"
  break;
#line 300

#line 300

#line 310 "filter/f-inst.c"
 /* Constructor for FI_AND */
#line 310
  case FI_AND:
#line 310
  #define whati (&(what->i_FI_AND))
#line 310
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 310
  #line 300 "filter/f-inst.c"
 {
    
#line 301 "filter/f-inst.c"
 
#line 301 "filter/f-inst.c"
 
#line 301
if (v1.type != (T_BOOL))
#line 301
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 301
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(v1.type));
#line 301
;
    
#line 302 "filter/f-inst.c"
;
     
#line 303 "filter/f-inst.c"
;

    if (v1.val.i)
      
#line 306 "filter/f-inst.c"
do { if (whati->fl2) {
#line 306
  do {
#line 306
  fstk->estk[fstk->ecnt].pos = 0;
#line 306
  fstk->estk[fstk->ecnt].line = whati->fl2;
#line 306
  fstk->estk[fstk->ecnt].ventry = fstk->vcnt;
#line 306
  fstk->estk[fstk->ecnt].vbase = fstk->estk[fstk->ecnt-1].vbase;
#line 306
  fstk->estk[fstk->ecnt].emask = 0;
#line 306
  fstk->ecnt++;
#line 306
} while (0);
#line 306
} } while(0)
#line 306 "filter/f-inst.c"
;
    else
      do { res = v1; fstk->vcnt++; } while (0);
  }
  
  #undef whati
#line 310 "filter/f-inst.c"
  break;
#line 310

#line 310

#line 321 "filter/f-inst.c"
 /* Constructor for FI_OR */
#line 321
  case FI_OR:
#line 321
  #define whati (&(what->i_FI_OR))
#line 321
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 321
  #line 310 "filter/f-inst.c"
 {
    
#line 311 "filter/f-inst.c"
 
#line 311 "filter/f-inst.c"
 
#line 311
if (v1.type != (T_BOOL))
#line 311
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 311
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(v1.type));
#line 311
;
    
#line 312 "filter/f-inst.c"
;
     
#line 313 "filter/f-inst.c"
;

    if (!v1.val.i)
      
#line 316 "filter/f-inst.c"
do { if (whati->fl2) {
#line 316
  do {
#line 316
  fstk->estk[fstk->ecnt].pos = 0;
#line 316
  fstk->estk[fstk->ecnt].line = whati->fl2;
#line 316
  fstk->estk[fstk->ecnt].ventry = fstk->vcnt;
#line 316
  fstk->estk[fstk->ecnt].vbase = fstk->estk[fstk->ecnt-1].vbase;
#line 316
  fstk->estk[fstk->ecnt].emask = 0;
#line 316
  fstk->ecnt++;
#line 316
} while (0);
#line 316
} } while(0)
#line 316 "filter/f-inst.c"
;
    else
      do { res = v1; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 321 "filter/f-inst.c"
  break;
#line 321

#line 321

#line 331 "filter/f-inst.c"
 /* Constructor for FI_PAIR_CONSTRUCT */
#line 331
  case FI_PAIR_CONSTRUCT:
#line 331
  #define whati (&(what->i_FI_PAIR_CONSTRUCT))
#line 331
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 331
  #line 321 "filter/f-inst.c"
 {
    
#line 322 "filter/f-inst.c"
 
#line 322 "filter/f-inst.c"
 
#line 322
if (v1.type != (T_INT))
#line 322
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 322
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v1.type));
#line 322
;
    
#line 323 "filter/f-inst.c"
 
#line 323 "filter/f-inst.c"
 
#line 323
if (v2.type != (T_INT))
#line 323
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 323
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 323
;
    uint u1 = v1.val.i;
    uint u2 = v2.val.i;
    if ((u1 > 0xFFFF) || (u2 > 0xFFFF))
      runtime( "Can't operate with value out of bounds in pair constructor" );
     
#line 328 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_PAIR, .val.i = (u1 << 16) | u2 } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 331 "filter/f-inst.c"
  break;
#line 331

#line 331

#line 371 "filter/f-inst.c"
 /* Constructor for FI_EC_CONSTRUCT */
#line 371
  case FI_EC_CONSTRUCT:
#line 371
  #define whati (&(what->i_FI_EC_CONSTRUCT))
#line 371
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 371
  #line 331 "filter/f-inst.c"
 {
    
#line 332 "filter/f-inst.c"
;
    
#line 333 "filter/f-inst.c"
 
#line 333 "filter/f-inst.c"
 
#line 333
if (v2.type != (T_INT))
#line 333
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 333
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 333
;

    #line 335 "filter/f-inst.c"
const enum ec_subtype ecs = whati->ecs
#line 335
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
 do { res =  (struct f_val) { .type = T_EC, .val.ec = ec_generic(key, val) } ; fstk->vcnt++; } while (0);
    else if (ipv4_used)
      if (val <= 0xFFFF)
	 do { res =  (struct f_val) { .type = T_EC, .val.ec = ec_ip4(ecs, key, val) } ; fstk->vcnt++; } while (0);
      else
	runtime("4-byte value %u can't be used with IP-address key in extended community", val);
    else if (key < 0x10000)
       do { res =  (struct f_val) { .type = T_EC, .val.ec = ec_as2(ecs, key, val) } ; fstk->vcnt++; } while (0);
    else
      if (val <= 0xFFFF)
	 do { res =  (struct f_val) { .type = T_EC, .val.ec = ec_as4(ecs, key, val) } ; fstk->vcnt++; } while (0);
      else
	runtime("4-byte value %u can't be used with 4-byte ASN in extended community", val);
  }

  
  #undef whati
#line 371 "filter/f-inst.c"
  break;
#line 371

#line 371

#line 378 "filter/f-inst.c"
 /* Constructor for FI_LC_CONSTRUCT */
#line 378
  case FI_LC_CONSTRUCT:
#line 378
  #define whati (&(what->i_FI_LC_CONSTRUCT))
#line 378
  if (fstk->vcnt < 3) runtime("Stack underflow"); fstk->vcnt -= 3; 
#line 378
  #line 371 "filter/f-inst.c"
 {
    
#line 372 "filter/f-inst.c"
 
#line 372 "filter/f-inst.c"
 
#line 372
if (v1.type != (T_INT))
#line 372
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 372
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v1.type));
#line 372
;
    
#line 373 "filter/f-inst.c"
 
#line 373 "filter/f-inst.c"
 
#line 373
if (v2.type != (T_INT))
#line 373
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 373
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 373
;
    
#line 374 "filter/f-inst.c"
 
#line 374 "filter/f-inst.c"
 
#line 374
if (v3.type != (T_INT))
#line 374
  runtime("Argument 3 of %s must be of type %s, got type %s",
#line 374
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v3.type));
#line 374
;
     
#line 375 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_LC, .val.lc = (lcomm) { v1.val.i, v2.val.i, v3.val.i } } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 378 "filter/f-inst.c"
  break;
#line 378

#line 378

#line 428 "filter/f-inst.c"
 /* Constructor for FI_PATHMASK_CONSTRUCT */
#line 428
  case FI_PATHMASK_CONSTRUCT:
#line 428
  #define whati (&(what->i_FI_PATHMASK_CONSTRUCT))
#line 428
  
#line 428
  #line 378 "filter/f-inst.c"
 {
    
#line 379 "filter/f-inst.c"

#line 379

#line 379
  if (fstk->vcnt < whati->varcount) runtime("Stack underflow");
#line 379
  fstk->vcnt -= whati->varcount;
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
 do { res =  (struct f_val) { .type = T_PATH_MASK, .val.path_mask = pm } ; fstk->vcnt++; } while (0);
  }

/* Relational operators */

  
  #undef whati
#line 428 "filter/f-inst.c"
  break;
#line 428

#line 428

#line 435 "filter/f-inst.c"
 /* Constructor for FI_NEQ */
#line 435
  case FI_NEQ:
#line 435
  #define whati (&(what->i_FI_NEQ))
#line 435
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = !val_same(&v1, &v2) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 435 "filter/f-inst.c"
  break;
#line 435

#line 435

#line 442 "filter/f-inst.c"
 /* Constructor for FI_EQ */
#line 442
  case FI_EQ:
#line 442
  #define whati (&(what->i_FI_EQ))
#line 442
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = val_same(&v1, &v2) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 442 "filter/f-inst.c"
  break;
#line 442

#line 442

#line 453 "filter/f-inst.c"
 /* Constructor for FI_LT */
#line 453
  case FI_LT:
#line 453
  #define whati (&(what->i_FI_LT))
#line 453
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = (i == -1) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 453 "filter/f-inst.c"
  break;
#line 453

#line 453

#line 464 "filter/f-inst.c"
 /* Constructor for FI_LTE */
#line 464
  case FI_LTE:
#line 464
  #define whati (&(what->i_FI_LTE))
#line 464
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = (i != 1) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 464 "filter/f-inst.c"
  break;
#line 464

#line 464

#line 469 "filter/f-inst.c"
 /* Constructor for FI_NOT */
#line 469
  case FI_NOT:
#line 469
  #define whati (&(what->i_FI_NOT))
#line 469
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 469
  #line 464 "filter/f-inst.c"
 {
    
#line 465 "filter/f-inst.c"
 
#line 465 "filter/f-inst.c"
 
#line 465
if (v1.type != (T_BOOL))
#line 465
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 465
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(v1.type));
#line 465
;
     
#line 466 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = !v1.val.i } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 469 "filter/f-inst.c"
  break;
#line 469

#line 469

#line 478 "filter/f-inst.c"
 /* Constructor for FI_MATCH */
#line 478
  case FI_MATCH:
#line 478
  #define whati (&(what->i_FI_MATCH))
#line 478
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = !!i } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 478 "filter/f-inst.c"
  break;
#line 478

#line 478

#line 487 "filter/f-inst.c"
 /* Constructor for FI_NOT_MATCH */
#line 487
  case FI_NOT_MATCH:
#line 487
  #define whati (&(what->i_FI_NOT_MATCH))
#line 487
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = !i } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 487 "filter/f-inst.c"
  break;
#line 487

#line 487

#line 492 "filter/f-inst.c"
 /* Constructor for FI_DEFINED */
#line 492
  case FI_DEFINED:
#line 492
  #define whati (&(what->i_FI_DEFINED))
#line 492
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 492
  #line 487 "filter/f-inst.c"
 {
    
#line 488 "filter/f-inst.c"
;
     
#line 489 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = (v1.type != T_VOID) && !undef_value(v1) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 492 "filter/f-inst.c"
  break;
#line 492

#line 492

#line 504 "filter/f-inst.c"
 /* Constructor for FI_TYPE */
#line 504
  case FI_TYPE:
#line 504
  #define whati (&(what->i_FI_TYPE))
#line 504
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 504
  #line 492 "filter/f-inst.c"
 {
    
#line 493 "filter/f-inst.c"
; /* There may be more types supporting this operation */
    switch (v1.type)
    {
      case T_NET:
	 
#line 497 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_ENUM_NETTYPE, .val.i = v1.val.net->type } ; fstk->vcnt++; } while (0);
	break;
      default:
	runtime( "Can't determine type of this item" );
    }
  }

  
  #undef whati
#line 504 "filter/f-inst.c"
  break;
#line 504

#line 504

#line 509 "filter/f-inst.c"
 /* Constructor for FI_IS_V4 */
#line 509
  case FI_IS_V4:
#line 509
  #define whati (&(what->i_FI_IS_V4))
#line 509
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 509
  #line 504 "filter/f-inst.c"
 {
    
#line 505 "filter/f-inst.c"
 
#line 505 "filter/f-inst.c"
 
#line 505
if (v1.type != (T_IP))
#line 505
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 505
	   f_instruction_name(what->fi_code), f_type_name(T_IP), f_type_name(v1.type));
#line 505
;
     
#line 506 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_BOOL, .val.i = ipa_is_ip4(v1.val.ip) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 509 "filter/f-inst.c"
  break;
#line 509

#line 509

#line 522 "filter/f-inst.c"
 /* Constructor for FI_VAR_INIT */
#line 522
  case FI_VAR_INIT:
#line 522
  #define whati (&(what->i_FI_VAR_INIT))
#line 522
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 522
  #line 509 "filter/f-inst.c"
 {
    ;
    
#line 511 "filter/f-inst.c"
;
    #line 512 "filter/f-inst.c"
const struct symbol * sym = whati->sym
#line 512
;
    
#line 513 "filter/f-inst.c"
 
#line 513
if (v1.type != (sym->class & 0xff))
#line 513
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 513
	   f_instruction_name(what->fi_code), f_type_name(sym->class & 0xff), f_type_name(v1.type));
#line 513
;

    /* New variable is always the last on stack */
    uint pos = curline.vbase + sym->offset;
    fstk->vstk[pos] = v1;
    fstk->vcnt = pos + 1;
  }

  /* Set to indirect value prepared in v1 */
  
  #undef whati
#line 522 "filter/f-inst.c"
  break;
#line 522

#line 522

#line 531 "filter/f-inst.c"
 /* Constructor for FI_VAR_SET */
#line 531
  case FI_VAR_SET:
#line 531
  #define whati (&(what->i_FI_VAR_SET))
#line 531
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 531
  #line 522 "filter/f-inst.c"
 {
    ;
    
#line 524 "filter/f-inst.c"
;
    #line 525 "filter/f-inst.c"
const struct symbol * sym = whati->sym
#line 525
;
    
#line 526 "filter/f-inst.c"
 
#line 526
if (v1.type != (sym->class & 0xff))
#line 526
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 526
	   f_instruction_name(what->fi_code), f_type_name(sym->class & 0xff), f_type_name(v1.type));
#line 526
;

    fstk->vstk[curline.vbase + sym->offset] = v1;
  }

  
  #undef whati
#line 531 "filter/f-inst.c"
  break;
#line 531

#line 531

#line 538 "filter/f-inst.c"
 /* Constructor for FI_VAR_GET */
#line 538
  case FI_VAR_GET:
#line 538
  #define whati (&(what->i_FI_VAR_GET))
#line 538
  
#line 538
  #line 531 "filter/f-inst.c"
 {
    #line 532 "filter/f-inst.c"
const struct symbol * sym = whati->sym
#line 532
;
    ;
     
#line 534 "filter/f-inst.c"
;
    do { res = fstk->vstk[curline.vbase + sym->offset]; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 538 "filter/f-inst.c"
  break;
#line 538

#line 538

#line 551 "filter/f-inst.c"
 /* Constructor for FI_CONSTANT */
#line 551
  case FI_CONSTANT:
#line 551
  #define whati (&(what->i_FI_CONSTANT))
#line 551
  
#line 551
  #line 538 "filter/f-inst.c"
 {
    #line 539 "filter/f-inst.c"
const struct f_val val = whati->val
#line 545
;

     
#line 547 "filter/f-inst.c"
;
    do { res = val; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 551 "filter/f-inst.c"
  break;
#line 551

#line 551

#line 585 "filter/f-inst.c"
 /* Constructor for FI_FOR_INIT */
#line 585
  case FI_FOR_INIT:
#line 585
  #define whati (&(what->i_FI_FOR_INIT))
#line 585
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 585
  #line 551 "filter/f-inst.c"
 {
    ;
    
#line 553 "filter/f-inst.c"
;
    #line 554 "filter/f-inst.c"
const struct symbol * sym = whati->sym
#line 554
;

    
#line 573 "filter/f-inst.c"

    /* Dynamic type check */
    if ((sym->class & 0xff) != f_type_element_type(v1.type))
      runtime("Mismatched argument and variable type");

    /* Setup the index */
    v2 = (struct f_val) { .type = T_INT, .val.i = 0 };

    /* Keep v1 and v2 on the stack */
    fstk->vcnt += 2;
  }

  
  #undef whati
#line 585 "filter/f-inst.c"
  break;
#line 585

#line 585

#line 639 "filter/f-inst.c"
 /* Constructor for FI_FOR_NEXT */
#line 639
  case FI_FOR_NEXT:
#line 639
  #define whati (&(what->i_FI_FOR_NEXT))
#line 639
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 639
  #line 585 "filter/f-inst.c"
 {
    ;
    #line 587 "filter/f-inst.c"
const struct symbol * sym = whati->sym
#line 587
;

    /* Type checks are done in FI_FOR_INIT */

    /* Loop variable */
    struct f_val *var = &fstk->vstk[curline.vbase + sym->offset];
    int step = 0;

    switch(v1.type)
    {
    case T_PATH:
      var->type = T_INT;
      step = as_path_walk(v1.val.ad, &v2.val.i, &var->val.i);
      break;

    case T_CLIST:
      var->type = T_PAIR;
      step = int_set_walk(v1.val.ad, &v2.val.i, &var->val.i);
      break;

    case T_ECLIST:
      var->type = T_EC;
      step = ec_set_walk(v1.val.ad, &v2.val.i, &var->val.ec);
      break;

    case T_LCLIST:
      var->type = T_LC;
      step = lc_set_walk(v1.val.ad, &v2.val.i, &var->val.lc);
      break;

    default:
      runtime( "Clist or lclist expected" );
    }

    if (step)
    {
      /* Keep v1 and v2 on the stack */
      fstk->vcnt += 2;

      /* Repeat this instruction */
      curline.pos--;

      /* Execute the loop body */
      
#line 630 "filter/f-inst.c"
do { if (whati->fl1) {
#line 630
  do {
#line 630
  fstk->estk[fstk->ecnt].pos = 0;
#line 630
  fstk->estk[fstk->ecnt].line = whati->fl1;
#line 630
  fstk->estk[fstk->ecnt].ventry = fstk->vcnt;
#line 630
  fstk->estk[fstk->ecnt].vbase = fstk->estk[fstk->ecnt-1].vbase;
#line 630
  fstk->estk[fstk->ecnt].emask = 0;
#line 630
  fstk->ecnt++;
#line 630
} while (0);
#line 630
} } while(0)
#line 630 "filter/f-inst.c"
;

      /* Space for loop variable, may be unused */
      fstk->vcnt += 1;
    }
    else
      var->type = T_VOID;
  }

  
  #undef whati
#line 639 "filter/f-inst.c"
  break;
#line 639

#line 639

#line 647 "filter/f-inst.c"
 /* Constructor for FI_CONDITION */
#line 647
  case FI_CONDITION:
#line 647
  #define whati (&(what->i_FI_CONDITION))
#line 647
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 647
  #line 639 "filter/f-inst.c"
 {
    
#line 640 "filter/f-inst.c"
 
#line 640 "filter/f-inst.c"
 
#line 640
if (v1.type != (T_BOOL))
#line 640
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 640
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(v1.type));
#line 640
;
    if (v1.val.i)
      
#line 642 "filter/f-inst.c"
do { if (whati->fl2) {
#line 642
  do {
#line 642
  fstk->estk[fstk->ecnt].pos = 0;
#line 642
  fstk->estk[fstk->ecnt].line = whati->fl2;
#line 642
  fstk->estk[fstk->ecnt].ventry = fstk->vcnt;
#line 642
  fstk->estk[fstk->ecnt].vbase = fstk->estk[fstk->ecnt-1].vbase;
#line 642
  fstk->estk[fstk->ecnt].emask = 0;
#line 642
  fstk->ecnt++;
#line 642
} while (0);
#line 642
} } while(0)
#line 642 "filter/f-inst.c"
;
    else
      
#line 644 "filter/f-inst.c"
do { if (whati->fl3) {
#line 644
  do {
#line 644
  fstk->estk[fstk->ecnt].pos = 0;
#line 644
  fstk->estk[fstk->ecnt].line = whati->fl3;
#line 644
  fstk->estk[fstk->ecnt].ventry = fstk->vcnt;
#line 644
  fstk->estk[fstk->ecnt].vbase = fstk->estk[fstk->ecnt-1].vbase;
#line 644
  fstk->estk[fstk->ecnt].emask = 0;
#line 644
  fstk->ecnt++;
#line 644
} while (0);
#line 644
} } while(0)
#line 644 "filter/f-inst.c"
;
  }

  
  #undef whati
#line 647 "filter/f-inst.c"
  break;
#line 647

#line 647

#line 656 "filter/f-inst.c"
 /* Constructor for FI_PRINT */
#line 656
  case FI_PRINT:
#line 656
  #define whati (&(what->i_FI_PRINT))
#line 656
  
#line 656
  #line 647 "filter/f-inst.c"
 {
    ;
    
#line 649 "filter/f-inst.c"

#line 649

#line 649
  if (fstk->vcnt < whati->varcount) runtime("Stack underflow");
#line 649
  fstk->vcnt -= whati->varcount;
#line 649

#line 649
;

    if (whati->varcount && !(fs->flags & FF_SILENT))
      for (uint i=0; i<whati->varcount; i++)
	val_format(&(vv(i)), &fs->buf);
  }

  
  #undef whati
#line 656 "filter/f-inst.c"
  break;
#line 656

#line 656

#line 663 "filter/f-inst.c"
 /* Constructor for FI_FLUSH */
#line 663
  case FI_FLUSH:
#line 663
  #define whati (&(what->i_FI_FLUSH))
#line 663
  
#line 663
  #line 656 "filter/f-inst.c"
 {
    ;
    if (!(fs->flags & FF_SILENT))
      /* After log_commit, the buffer is reset */
      log_commit(*L_INFO, &fs->buf);
  }

  
  #undef whati
#line 663 "filter/f-inst.c"
  break;
#line 663

#line 663

#line 677 "filter/f-inst.c"
 /* Constructor for FI_DIE */
#line 677
  case FI_DIE:
#line 677
  #define whati (&(what->i_FI_DIE))
#line 677
  
#line 677
  #line 663 "filter/f-inst.c"
 {
    ;
    #line 665 "filter/f-inst.c"
const enum filter_return fret = whati->fret
#line 665
;

    switch (whati->fret) {
    case F_ACCEPT:	/* Should take care about turning ACCEPT into MODIFY */
    case F_ERROR:
    case F_REJECT:	/* Maybe print complete route along with reason to reject route? */
      return fret;	/* We have to return now, no more processing. */
    default:
      bug( "unknown return type: Can't happen");
    }
  }

  
  #undef whati
#line 677 "filter/f-inst.c"
  break;
#line 677

#line 677

#line 704 "filter/f-inst.c"
 /* Constructor for FI_RTA_GET */
#line 704
  case FI_RTA_GET:
#line 704
  #define whati (&(what->i_FI_RTA_GET))
#line 704
  
#line 704
  #line 677 "filter/f-inst.c"
 {
    {
      #line 679 "filter/f-inst.c"
const struct f_static_attr sa = whati->sa
#line 679
;
      do { if (!fs->rte) runtime("No route to access"); } while (0);
      struct rta *rta = (*fs->rte)->attrs;

      switch (sa.sa_code)
      {
      case SA_FROM:	 
#line 685 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = sa.f_type, .val.ip = rta->from } ; fstk->vcnt++; } while (0); break;
      case SA_GW:	 do { res =  (struct f_val) { .type = sa.f_type, .val.ip = rta->nh.gw } ; fstk->vcnt++; } while (0); break;
      case SA_NET:	 do { res =  (struct f_val) { .type = sa.f_type, .val.net = (*fs->rte)->net->n.addr } ; fstk->vcnt++; } while (0); break;
      case SA_PROTO:	 do { res =  (struct f_val) { .type = sa.f_type, .val.s = (*fs->rte)->src->proto->name } ; fstk->vcnt++; } while (0); break;
      case SA_SOURCE:	 do { res =  (struct f_val) { .type = sa.f_type, .val.i = rta->source } ; fstk->vcnt++; } while (0); break;
      case SA_SCOPE:	 do { res =  (struct f_val) { .type = sa.f_type, .val.i = rta->scope } ; fstk->vcnt++; } while (0); break;
      case SA_DEST:	 do { res =  (struct f_val) { .type = sa.f_type, .val.i = rta->dest } ; fstk->vcnt++; } while (0); break;
      case SA_IFNAME:	 do { res =  (struct f_val) { .type = sa.f_type, .val.s = rta->nh.iface ? rta->nh.iface->name : "" } ; fstk->vcnt++; } while (0); break;
      case SA_IFINDEX:	 do { res =  (struct f_val) { .type = sa.f_type, .val.i = rta->nh.iface ? rta->nh.iface->index : 0 } ; fstk->vcnt++; } while (0); break;
      case SA_WEIGHT:	 do { res =  (struct f_val) { .type = sa.f_type, .val.i = rta->nh.weight + 1 } ; fstk->vcnt++; } while (0); break;
      case SA_PREF:	 do { res =  (struct f_val) { .type = sa.f_type, .val.i = rta->pref } ; fstk->vcnt++; } while (0); break;
      case SA_GW_MPLS:	 do { res =  (struct f_val) { .type = sa.f_type, .val.i = rta->nh.labels ? rta->nh.label[0] : MPLS_NULL } ; fstk->vcnt++; } while (0); break;

      default:
	bug("Invalid static attribute access (%u/%u)", sa.f_type, sa.sa_code);
      }
    }
  }

  
  #undef whati
#line 704 "filter/f-inst.c"
  break;
#line 704

#line 704

#line 810 "filter/f-inst.c"
 /* Constructor for FI_RTA_SET */
#line 810
  case FI_RTA_SET:
#line 810
  #define whati (&(what->i_FI_RTA_SET))
#line 810
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 810
  #line 704 "filter/f-inst.c"
 {
    do { if (!fs->rte) runtime("No route to access"); } while (0);
    
#line 706 "filter/f-inst.c"
;
    #line 707 "filter/f-inst.c"
const struct f_static_attr sa = whati->sa
#line 707
;
    
#line 708 "filter/f-inst.c"
 
#line 708
if (v1.type != (sa.f_type))
#line 708
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 708
	   f_instruction_name(what->fi_code), f_type_name(sa.f_type), f_type_name(v1.type));
#line 708
;

    f_rta_cow(fs);
    {
      struct rta *rta = (*fs->rte)->attrs;

      switch (sa.sa_code)
      {
      case SA_FROM:
	rta->from = v1.val.ip;
	break;

      case SA_GW:
	{
	  ip_addr ip = v1.val.ip;
	  struct iface *ifa = ipa_is_link_local(ip) ? rta->nh.iface : NULL;
	  neighbor *n = neigh_find((*fs->rte)->src->proto, ip, ifa, 0);
	  if (!n || (n->scope == SCOPE_HOST))
	    runtime( "Invalid gw address" );

	  rta->dest = RTD_UNICAST;
	  rta->nh.gw = ip;
	  rta->nh.iface = n->iface;
	  rta->nh.next = NULL;
	  rta->hostentry = NULL;
	  rta->nh.labels = 0;
	}
	break;

      case SA_SCOPE:
	rta->scope = v1.val.i;
	break;

      case SA_DEST:
	{
	  int i = v1.val.i;
	  if ((i != RTD_BLACKHOLE) && (i != RTD_UNREACHABLE) && (i != RTD_PROHIBIT))
	    runtime( "Destination can be changed only to blackhole, unreachable or prohibit" );

	  rta->dest = i;
	  rta->nh.gw = IPA_NONE;
	  rta->nh.iface = NULL;
	  rta->nh.next = NULL;
	  rta->hostentry = NULL;
	  rta->nh.labels = 0;
	}
	break;

      case SA_IFNAME:
	{
	  struct iface *ifa = if_find_by_name(v1.val.s);
	  if (!ifa)
	    runtime( "Invalid iface name" );

	  rta->dest = RTD_UNICAST;
	  rta->nh.gw = IPA_NONE;
	  rta->nh.iface = ifa;
	  rta->nh.next = NULL;
	  rta->hostentry = NULL;
	  rta->nh.labels = 0;
	}
	break;

      case SA_GW_MPLS:
	{
	  if (v1.val.i >= 0x100000)
	    runtime( "Invalid MPLS label" );

	  if (v1.val.i != MPLS_NULL)
	  {
	    rta->nh.label[0] = v1.val.i;
	    rta->nh.labels = 1;
	  }
	  else
	    rta->nh.labels = 0;
	}
	break;

      case SA_WEIGHT:
        {
	  int i = v1.val.i;
	  if (i < 1 || i > 256)
	    runtime( "Setting weight value out of bounds" );
	  if (rta->dest != RTD_UNICAST)
	    runtime( "Setting weight needs regular nexthop " );

	  /* Set weight on all next hops */
	  for (struct nexthop *nh = &rta->nh; nh; nh = nh->next)
	    nh->weight = i - 1;
        }
	break;

      case SA_PREF:
	rta->pref = v1.val.i;
	break;

      default:
	bug("Invalid static attribute access (%u/%u)", sa.f_type, sa.sa_code);
      }
    }
  }

  
  #undef whati
#line 810 "filter/f-inst.c"
  break;
#line 810

#line 810

#line 882 "filter/f-inst.c"
 /* Constructor for FI_EA_GET */
#line 882
  case FI_EA_GET:
#line 882
  #define whati (&(what->i_FI_EA_GET))
#line 882
  
#line 882
  #line 810 "filter/f-inst.c"
 {	/* Access to extended attributes */
    #line 811 "filter/f-inst.c"
const struct f_dynamic_attr da = whati->da
#line 811
;
    do { if (!fs->rte) runtime("No route to access"); } while (0);
    ACCESS_EATTRS;
     
#line 814 "filter/f-inst.c"
;
    {
      eattr *e = ea_find(*fs->eattrs, da.ea_code);

      if (!e) {
	/* A special case: undefined as_path looks like empty as_path */
	if (da.type == EAF_TYPE_AS_PATH) {
	  do { res =  (struct f_val) { .type = T_PATH, .val.ad = &null_adata } ; fstk->vcnt++; } while (0);
	  break;
	}

	/* The same special case for int_set */
	if (da.type == EAF_TYPE_INT_SET) {
	  do { res =  (struct f_val) { .type = T_CLIST, .val.ad = &null_adata } ; fstk->vcnt++; } while (0);
	  break;
	}

	/* The same special case for ec_set */
	if (da.type == EAF_TYPE_EC_SET) {
	  do { res =  (struct f_val) { .type = T_ECLIST, .val.ad = &null_adata } ; fstk->vcnt++; } while (0);
	  break;
	}

	/* The same special case for lc_set */
	if (da.type == EAF_TYPE_LC_SET) {
	  do { res =  (struct f_val) { .type = T_LCLIST, .val.ad = &null_adata } ; fstk->vcnt++; } while (0);
	  break;
	}

	/* Undefined value */
	do { res =  (struct f_val) { .type = T_VOID } ; fstk->vcnt++; } while (0);
	break;
      }

      switch (e->type & EAF_TYPE_MASK) {
      case EAF_TYPE_INT:
	do { res =  (struct f_val) { .type = da.f_type, .val.i = e->u.data } ; fstk->vcnt++; } while (0);
	break;
      case EAF_TYPE_ROUTER_ID:
	do { res =  (struct f_val) { .type = T_QUAD, .val.i = e->u.data } ; fstk->vcnt++; } while (0);
	break;
      case EAF_TYPE_OPAQUE:
	do { res =  (struct f_val) { .type = T_ENUM_EMPTY, .val.i = 0 } ; fstk->vcnt++; } while (0);
	break;
      case EAF_TYPE_IP_ADDRESS:
	do { res =  (struct f_val) { .type = T_IP, .val.ip = *((ip_addr *) e->u.ptr->data) } ; fstk->vcnt++; } while (0);
	break;
      case EAF_TYPE_AS_PATH:
	do { res =  (struct f_val) { .type = T_PATH, .val.ad = e->u.ptr } ; fstk->vcnt++; } while (0);
	break;
      case EAF_TYPE_BITFIELD:
	do { res =  (struct f_val) { .type = T_BOOL, .val.i = !!(e->u.data & (1u << da.bit)) } ; fstk->vcnt++; } while (0);
	break;
      case EAF_TYPE_INT_SET:
	do { res =  (struct f_val) { .type = T_CLIST, .val.ad = e->u.ptr } ; fstk->vcnt++; } while (0);
	break;
      case EAF_TYPE_EC_SET:
	do { res =  (struct f_val) { .type = T_ECLIST, .val.ad = e->u.ptr } ; fstk->vcnt++; } while (0);
	break;
      case EAF_TYPE_LC_SET:
	do { res =  (struct f_val) { .type = T_LCLIST, .val.ad = e->u.ptr } ; fstk->vcnt++; } while (0);
	break;
      default:
	bug("Unknown dynamic attribute type");
      }
    }
  }

  
  #undef whati
#line 882 "filter/f-inst.c"
  break;
#line 882

#line 882

#line 949 "filter/f-inst.c"
 /* Constructor for FI_EA_SET */
#line 949
  case FI_EA_SET:
#line 949
  #define whati (&(what->i_FI_EA_SET))
#line 949
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 949
  #line 882 "filter/f-inst.c"
 {
    do { if (!fs->rte) runtime("No route to access"); } while (0);
    ACCESS_EATTRS;
    
#line 885 "filter/f-inst.c"
;
    #line 886 "filter/f-inst.c"
const struct f_dynamic_attr da = whati->da
#line 886
;
    
#line 887 "filter/f-inst.c"
 
#line 887
if (v1.type != (da.f_type))
#line 887
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 887
	   f_instruction_name(what->fi_code), f_type_name(da.f_type), f_type_name(v1.type));
#line 887
;
    {
      struct ea_list *l = lp_alloc(fs->pool, sizeof(struct ea_list) + sizeof(eattr));

      l->next = NULL;
      l->flags = EALF_SORTED;
      l->count = 1;
      l->attrs[0].id = da.ea_code;
      l->attrs[0].flags = 0;
      l->attrs[0].type = da.type;
      l->attrs[0].originated = 1;
      l->attrs[0].fresh = 1;
      l->attrs[0].undef = 0;

      switch (da.type) {
      case EAF_TYPE_INT:
      case EAF_TYPE_ROUTER_ID:
	l->attrs[0].u.data = v1.val.i;
	break;

      case EAF_TYPE_OPAQUE:
	runtime( "Setting opaque attribute is not allowed" );
	break;

      case EAF_TYPE_IP_ADDRESS:;
	int len = sizeof(ip_addr);
	struct adata *ad = lp_alloc(fs->pool, sizeof(struct adata) + len);
	ad->length = len;
	(* (ip_addr *) ad->data) = v1.val.ip;
	l->attrs[0].u.ptr = ad;
	break;

      case EAF_TYPE_AS_PATH:
      case EAF_TYPE_INT_SET:
      case EAF_TYPE_EC_SET:
      case EAF_TYPE_LC_SET:
	l->attrs[0].u.ptr = v1.val.ad;
	break;

      case EAF_TYPE_BITFIELD:
	{
	  /* First, we have to find the old value */
	  eattr *e = ea_find(*fs->eattrs, da.ea_code);
	  u32 data = e ? e->u.data : 0;

	  if (v1.val.i)
	    l->attrs[0].u.data = data | (1u << da.bit);
	  else
	    l->attrs[0].u.data = data & ~(1u << da.bit);
	}
	break;

      default:
	bug("Unknown dynamic attribute type");
      }

      f_rta_cow(fs);
      l->next = *fs->eattrs;
      *fs->eattrs = l;
    }
  }

  
  #undef whati
#line 949 "filter/f-inst.c"
  break;
#line 949

#line 949

#line 958 "filter/f-inst.c"
 /* Constructor for FI_EA_UNSET */
#line 958
  case FI_EA_UNSET:
#line 958
  #define whati (&(what->i_FI_EA_UNSET))
#line 958
  
#line 958
  #line 949 "filter/f-inst.c"
 {
    #line 950 "filter/f-inst.c"
const struct f_dynamic_attr da = whati->da
#line 950
;
    do { if (!fs->rte) runtime("No route to access"); } while (0);
    ACCESS_EATTRS;

    f_rta_cow(fs);
    ea_unset_attr(fs->eattrs, fs->pool, 1, da.ea_code);
  }

  
  #undef whati
#line 958 "filter/f-inst.c"
  break;
#line 958

#line 958

#line 970 "filter/f-inst.c"
 /* Constructor for FI_LENGTH */
#line 970
  case FI_LENGTH:
#line 970
  #define whati (&(what->i_FI_LENGTH))
#line 970
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 970
  #line 958 "filter/f-inst.c"
 {	/* Get length of */
    
#line 959 "filter/f-inst.c"
;
    switch(v1.type) {
    case T_NET:     
#line 961 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = net_pxlen(v1.val.net) } ; fstk->vcnt++; } while (0); break;
    case T_PATH:    do { res =  (struct f_val) { .type = T_INT, .val.i = as_path_getlen(v1.val.ad) } ; fstk->vcnt++; } while (0); break;
    case T_CLIST:   do { res =  (struct f_val) { .type = T_INT, .val.i = int_set_get_size(v1.val.ad) } ; fstk->vcnt++; } while (0); break;
    case T_ECLIST:  do { res =  (struct f_val) { .type = T_INT, .val.i = ec_set_get_size(v1.val.ad) } ; fstk->vcnt++; } while (0); break;
    case T_LCLIST:  do { res =  (struct f_val) { .type = T_INT, .val.i = lc_set_get_size(v1.val.ad) } ; fstk->vcnt++; } while (0); break;
    default: runtime( "Prefix, path, clist or eclist expected" );
    }
  }

  
  #undef whati
#line 970 "filter/f-inst.c"
  break;
#line 970

#line 970

#line 1005 "filter/f-inst.c"
 /* Constructor for FI_NET_SRC */
#line 1005
  case FI_NET_SRC:
#line 1005
  #define whati (&(what->i_FI_NET_SRC))
#line 1005
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1005
  #line 970 "filter/f-inst.c"
 { 	/* Get src prefix */
    
#line 971 "filter/f-inst.c"
 
#line 971 "filter/f-inst.c"
 
#line 971
if (v1.type != (T_NET))
#line 971
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 971
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(v1.type));
#line 971
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
 do { res =  (struct f_val) { .type = T_NET, .val.net = src } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1005 "filter/f-inst.c"
  break;
#line 1005

#line 1005

#line 1040 "filter/f-inst.c"
 /* Constructor for FI_NET_DST */
#line 1040
  case FI_NET_DST:
#line 1040
  #define whati (&(what->i_FI_NET_DST))
#line 1040
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1040
  #line 1005 "filter/f-inst.c"
 { 	/* Get dst prefix */
    
#line 1006 "filter/f-inst.c"
 
#line 1006 "filter/f-inst.c"
 
#line 1006
if (v1.type != (T_NET))
#line 1006
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1006
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(v1.type));
#line 1006
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
 do { res =  (struct f_val) { .type = T_NET, .val.net = dst } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1040 "filter/f-inst.c"
  break;
#line 1040

#line 1040

#line 1050 "filter/f-inst.c"
 /* Constructor for FI_ROA_MAXLEN */
#line 1050
  case FI_ROA_MAXLEN:
#line 1050
  #define whati (&(what->i_FI_ROA_MAXLEN))
#line 1050
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1050
  #line 1040 "filter/f-inst.c"
 { 	/* Get ROA max prefix length */
    
#line 1041 "filter/f-inst.c"
 
#line 1041 "filter/f-inst.c"
 
#line 1041
if (v1.type != (T_NET))
#line 1041
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1041
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(v1.type));
#line 1041
;
    if (!net_is_roa(v1.val.net))
      runtime( "ROA expected" );

     
#line 1045 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = (v1.val.net->type == NET_ROA4) ?
#line 1045
      ((net_addr_roa4 *) v1.val.net)->max_pxlen :
#line 1045
      ((net_addr_roa6 *) v1.val.net)->max_pxlen } ; fstk->vcnt++; } while (0);
#line 1048
  }

  
  #undef whati
#line 1050 "filter/f-inst.c"
  break;
#line 1050

#line 1050

#line 1077 "filter/f-inst.c"
 /* Constructor for FI_ASN */
#line 1077
  case FI_ASN:
#line 1077
  #define whati (&(what->i_FI_ASN))
#line 1077
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
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

        do { res =  (struct f_val) { .type = T_INT, .val.i = (v1.val.net->type == NET_ROA4) ?
#line 1059
          ((net_addr_roa4 *) v1.val.net)->asn :
#line 1059
          ((net_addr_roa6 *) v1.val.net)->asn } ; fstk->vcnt++; } while (0);
#line 1062
        break;

      case T_PAIR:
        do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.i >> 16 } ; fstk->vcnt++; } while (0);
        break;

      case T_LC:
        do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.lc.asn } ; fstk->vcnt++; } while (0);
        break;

      default:
        runtime( "Net, pair or lc expected" );
    }
  }

  
  #undef whati
#line 1077 "filter/f-inst.c"
  break;
#line 1077

#line 1077

#line 1082 "filter/f-inst.c"
 /* Constructor for FI_IP */
#line 1082
  case FI_IP:
#line 1082
  #define whati (&(what->i_FI_IP))
#line 1082
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1082
  #line 1077 "filter/f-inst.c"
 {	/* Convert prefix to ... */
    
#line 1078 "filter/f-inst.c"
 
#line 1078 "filter/f-inst.c"
 
#line 1078
if (v1.type != (T_NET))
#line 1078
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1078
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(v1.type));
#line 1078
;
     
#line 1079 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_IP, .val.ip = net_prefix(v1.val.net) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1082 "filter/f-inst.c"
  break;
#line 1082

#line 1082

#line 1089 "filter/f-inst.c"
 /* Constructor for FI_ROUTE_DISTINGUISHER */
#line 1089
  case FI_ROUTE_DISTINGUISHER:
#line 1089
  #define whati (&(what->i_FI_ROUTE_DISTINGUISHER))
#line 1089
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1089
  #line 1082 "filter/f-inst.c"
 {
    
#line 1083 "filter/f-inst.c"
 
#line 1083 "filter/f-inst.c"
 
#line 1083
if (v1.type != (T_NET))
#line 1083
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1083
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(v1.type));
#line 1083
;
    if (!net_is_vpn(v1.val.net))
      runtime( "VPN address expected" );
     
#line 1086 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_RD, .val.ec = net_rd(v1.val.net) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1089 "filter/f-inst.c"
  break;
#line 1089

#line 1089

#line 1096 "filter/f-inst.c"
 /* Constructor for FI_AS_PATH_FIRST */
#line 1096
  case FI_AS_PATH_FIRST:
#line 1096
  #define whati (&(what->i_FI_AS_PATH_FIRST))
#line 1096
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1096
  #line 1089 "filter/f-inst.c"
 {	/* Get first ASN from AS PATH */
    
#line 1090 "filter/f-inst.c"
 
#line 1090 "filter/f-inst.c"
 
#line 1090
if (v1.type != (T_PATH))
#line 1090
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1090
	   f_instruction_name(what->fi_code), f_type_name(T_PATH), f_type_name(v1.type));
#line 1090
;
    u32 as = 0;
    as_path_get_first(v1.val.ad, &as);
     
#line 1093 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = as } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1096 "filter/f-inst.c"
  break;
#line 1096

#line 1096

#line 1103 "filter/f-inst.c"
 /* Constructor for FI_AS_PATH_LAST */
#line 1103
  case FI_AS_PATH_LAST:
#line 1103
  #define whati (&(what->i_FI_AS_PATH_LAST))
#line 1103
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1103
  #line 1096 "filter/f-inst.c"
 {		/* Get last ASN from AS PATH */
    
#line 1097 "filter/f-inst.c"
 
#line 1097 "filter/f-inst.c"
 
#line 1097
if (v1.type != (T_PATH))
#line 1097
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1097
	   f_instruction_name(what->fi_code), f_type_name(T_PATH), f_type_name(v1.type));
#line 1097
;
    u32 as = 0;
    as_path_get_last(v1.val.ad, &as);
     
#line 1100 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = as } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1103 "filter/f-inst.c"
  break;
#line 1103

#line 1103

#line 1108 "filter/f-inst.c"
 /* Constructor for FI_AS_PATH_LAST_NAG */
#line 1108
  case FI_AS_PATH_LAST_NAG:
#line 1108
  #define whati (&(what->i_FI_AS_PATH_LAST_NAG))
#line 1108
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1108
  #line 1103 "filter/f-inst.c"
 {	/* Get last ASN from non-aggregated part of AS PATH */
    
#line 1104 "filter/f-inst.c"
 
#line 1104 "filter/f-inst.c"
 
#line 1104
if (v1.type != (T_PATH))
#line 1104
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1104
	   f_instruction_name(what->fi_code), f_type_name(T_PATH), f_type_name(v1.type));
#line 1104
;
     
#line 1105 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = as_path_get_last_nonaggregated(v1.val.ad) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1108 "filter/f-inst.c"
  break;
#line 1108

#line 1108

#line 1113 "filter/f-inst.c"
 /* Constructor for FI_PAIR_DATA */
#line 1113
  case FI_PAIR_DATA:
#line 1113
  #define whati (&(what->i_FI_PAIR_DATA))
#line 1113
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1113
  #line 1108 "filter/f-inst.c"
 {	/* Get data part from the standard community */
    
#line 1109 "filter/f-inst.c"
 
#line 1109 "filter/f-inst.c"
 
#line 1109
if (v1.type != (T_PAIR))
#line 1109
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1109
	   f_instruction_name(what->fi_code), f_type_name(T_PAIR), f_type_name(v1.type));
#line 1109
;
     
#line 1110 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.i & 0xFFFF } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1113 "filter/f-inst.c"
  break;
#line 1113

#line 1113

#line 1118 "filter/f-inst.c"
 /* Constructor for FI_LC_DATA1 */
#line 1118
  case FI_LC_DATA1:
#line 1118
  #define whati (&(what->i_FI_LC_DATA1))
#line 1118
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1118
  #line 1113 "filter/f-inst.c"
 {	/* Get data1 part from the large community */
    
#line 1114 "filter/f-inst.c"
 
#line 1114 "filter/f-inst.c"
 
#line 1114
if (v1.type != (T_LC))
#line 1114
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1114
	   f_instruction_name(what->fi_code), f_type_name(T_LC), f_type_name(v1.type));
#line 1114
;
     
#line 1115 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.lc.ldp1 } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1118 "filter/f-inst.c"
  break;
#line 1118

#line 1118

#line 1123 "filter/f-inst.c"
 /* Constructor for FI_LC_DATA2 */
#line 1123
  case FI_LC_DATA2:
#line 1123
  #define whati (&(what->i_FI_LC_DATA2))
#line 1123
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1123
  #line 1118 "filter/f-inst.c"
 {	/* Get data2 part from the large community */
    
#line 1119 "filter/f-inst.c"
 
#line 1119 "filter/f-inst.c"
 
#line 1119
if (v1.type != (T_LC))
#line 1119
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1119
	   f_instruction_name(what->fi_code), f_type_name(T_LC), f_type_name(v1.type));
#line 1119
;
     
#line 1120 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_INT, .val.i = v1.val.lc.ldp2 } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1123 "filter/f-inst.c"
  break;
#line 1123

#line 1123

#line 1157 "filter/f-inst.c"
 /* Constructor for FI_MIN */
#line 1157
  case FI_MIN:
#line 1157
  #define whati (&(what->i_FI_MIN))
#line 1157
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
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
          do { res =  (struct f_val) { .type = T_PAIR, .val.i = val } ; fstk->vcnt++; } while (0);
        }
        break;

      case T_ECLIST:
        {
          u64 val = 0;
          ec_set_min(v1.val.ad, &val);
          do { res =  (struct f_val) { .type = T_EC, .val.ec = val } ; fstk->vcnt++; } while (0);
        }
        break;

      case T_LCLIST:
        {
          lcomm val = { 0, 0, 0 };
          lc_set_min(v1.val.ad, &val);
          do { res =  (struct f_val) { .type = T_LC, .val.lc = val } ; fstk->vcnt++; } while (0);
        }
        break;

      default:
        runtime( "Clist or lclist expected" );
    }
  }

  
  #undef whati
#line 1157 "filter/f-inst.c"
  break;
#line 1157

#line 1157

#line 1191 "filter/f-inst.c"
 /* Constructor for FI_MAX */
#line 1191
  case FI_MAX:
#line 1191
  #define whati (&(what->i_FI_MAX))
#line 1191
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
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
          do { res =  (struct f_val) { .type = T_PAIR, .val.i = val } ; fstk->vcnt++; } while (0);
        }
        break;

      case T_ECLIST:
        {
          u64 val = 0;
          ec_set_max(v1.val.ad, &val);
          do { res =  (struct f_val) { .type = T_EC, .val.ec = val } ; fstk->vcnt++; } while (0);
        }
        break;

      case T_LCLIST:
        {
          lcomm val = { 0, 0, 0 };
          lc_set_max(v1.val.ad, &val);
          do { res =  (struct f_val) { .type = T_LC, .val.lc = val } ; fstk->vcnt++; } while (0);
        }
        break;

      default:
        runtime( "Clist or lclist expected" );
    }
  }

  
  #undef whati
#line 1191 "filter/f-inst.c"
  break;
#line 1191

#line 1191

#line 1217 "filter/f-inst.c"
 /* Constructor for FI_RETURN */
#line 1217
  case FI_RETURN:
#line 1217
  #define whati (&(what->i_FI_RETURN))
#line 1217
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1217
  #line 1191 "filter/f-inst.c"
 {
    ;
    /* Acquire the return value */
    
#line 1194 "filter/f-inst.c"
;
    uint retpos = fstk->vcnt;

    /* Drop every sub-block including ourselves */
    do fstk->ecnt--;
    while ((fstk->ecnt > 0) && !(fstk->estk[fstk->ecnt].emask & FE_RETURN));

    /* Now we are at the caller frame; if no such, try to convert to accept/reject. */
    if (!fstk->ecnt)
    {
      if (fstk->vstk[retpos].type == T_BOOL)
	return (fstk->vstk[retpos].val.i) ? F_ACCEPT :  F_REJECT;
      else
	runtime("Can't return non-bool from non-function");
    }

    /* Set the value stack position, overwriting the former implicit void */
    fstk->vcnt = fstk->estk[fstk->ecnt].ventry - 1;

    /* Copy the return value */
    do { res = fstk->vstk[retpos]; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1217 "filter/f-inst.c"
  break;
#line 1217

#line 1217

#line 1278 "filter/f-inst.c"
 /* Constructor for FI_CALL */
#line 1278
  case FI_CALL:
#line 1278
  #define whati (&(what->i_FI_CALL))
#line 1278
  
#line 1278
  #line 1217 "filter/f-inst.c"
 {
    ;
    
#line 1219 "filter/f-inst.c"

#line 1219

#line 1219
  if (fstk->vcnt < whati->varcount) runtime("Stack underflow");
#line 1219
  fstk->vcnt -= whati->varcount;
#line 1219

#line 1219
;
    #line 1220 "filter/f-inst.c"
const struct symbol * sym = whati->sym
#line 1220
;

    /* Fake result type declaration */
     
#line 1223 "filter/f-inst.c"
;

    
#line 1264 "filter/f-inst.c"

    /* Push the body on stack */
    do {
#line 1266
  fstk->estk[fstk->ecnt].pos = 0;
#line 1266
  fstk->estk[fstk->ecnt].line = sym->function;
#line 1266
  fstk->estk[fstk->ecnt].ventry = fstk->vcnt;
#line 1266
  fstk->estk[fstk->ecnt].vbase = fstk->estk[fstk->ecnt-1].vbase;
#line 1266
  fstk->estk[fstk->ecnt].emask = 0;
#line 1266
  fstk->ecnt++;
#line 1266
} while (0);
#line 1267 "filter/f-inst.c"
    curline.vbase = curline.ventry;
    curline.emask |= FE_RETURN;

    /* Arguments on stack */
    fstk->vcnt += sym->function->args;

    /* Storage for local variables */
    memset(&(fstk->vstk[fstk->vcnt]), 0, sizeof(struct f_val) * sym->function->vars);
    fstk->vcnt += sym->function->vars;
  }

  
  #undef whati
#line 1278 "filter/f-inst.c"
  break;
#line 1278

#line 1278

#line 1283 "filter/f-inst.c"
 /* Constructor for FI_DROP_RESULT */
#line 1283
  case FI_DROP_RESULT:
#line 1283
  #define whati (&(what->i_FI_DROP_RESULT))
#line 1283
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1283
  #line 1278 "filter/f-inst.c"
 {
    ;
    
#line 1280 "filter/f-inst.c"
;
  }

  
  #undef whati
#line 1283 "filter/f-inst.c"
  break;
#line 1283

#line 1283

#line 1306 "filter/f-inst.c"
 /* Constructor for FI_SWITCH */
#line 1306
  case FI_SWITCH:
#line 1306
  #define whati (&(what->i_FI_SWITCH))
#line 1306
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1306
  #line 1283 "filter/f-inst.c"
 {
    
#line 1284 "filter/f-inst.c"
;

    #line 1286 "filter/f-inst.c"
const struct f_tree * tree = whati->tree
#line 1286
;

    
#line 1292 "filter/f-inst.c"
    const struct f_tree *t = find_tree(tree, &v1);
    if (!t) {
      v1.type = T_VOID;
      t = find_tree(tree, &v1);
      if (!t) {
	debug( "No else statement?\n");
	break;
      }
    }
    /* It is actually possible to have t->data NULL */

    do {
#line 1303
  fstk->estk[fstk->ecnt].pos = 0;
#line 1303
  fstk->estk[fstk->ecnt].line = t->data;
#line 1303
  fstk->estk[fstk->ecnt].ventry = fstk->vcnt;
#line 1303
  fstk->estk[fstk->ecnt].vbase = fstk->estk[fstk->ecnt-1].vbase;
#line 1303
  fstk->estk[fstk->ecnt].emask = 0;
#line 1303
  fstk->ecnt++;
#line 1303
} while (0);
#line 1304 "filter/f-inst.c"
  }

  
  #undef whati
#line 1306 "filter/f-inst.c"
  break;
#line 1306

#line 1306

#line 1314 "filter/f-inst.c"
 /* Constructor for FI_IP_MASK */
#line 1314
  case FI_IP_MASK:
#line 1314
  #define whati (&(what->i_FI_IP_MASK))
#line 1314
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 1314
  #line 1306 "filter/f-inst.c"
 { /* IP.MASK(val) */
    
#line 1307 "filter/f-inst.c"
 
#line 1307 "filter/f-inst.c"
 
#line 1307
if (v1.type != (T_IP))
#line 1307
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1307
	   f_instruction_name(what->fi_code), f_type_name(T_IP), f_type_name(v1.type));
#line 1307
;
    
#line 1308 "filter/f-inst.c"
 
#line 1308 "filter/f-inst.c"
 
#line 1308
if (v2.type != (T_INT))
#line 1308
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 1308
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 1308
;
     
#line 1309 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_IP, .val.ip =  ipa_is_ip4(v1.val.ip) ?
#line 1309
      ipa_from_ip4(ip4_and(ipa_to_ip4(v1.val.ip), ip4_mkmask(v2.val.i))) :
#line 1309
      ipa_from_ip6(ip6_and(ipa_to_ip6(v1.val.ip), ip6_mkmask(v2.val.i)))  } ; fstk->vcnt++; } while (0);
#line 1312
  }

  
  #undef whati
#line 1314 "filter/f-inst.c"
  break;
#line 1314

#line 1314

#line 1320 "filter/f-inst.c"
 /* Constructor for FI_PATH_PREPEND */
#line 1320
  case FI_PATH_PREPEND:
#line 1320
  #define whati (&(what->i_FI_PATH_PREPEND))
#line 1320
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 1320
  #line 1314 "filter/f-inst.c"
 {	/* Path prepend */
    
#line 1315 "filter/f-inst.c"
 
#line 1315 "filter/f-inst.c"
 
#line 1315
if (v1.type != (T_PATH))
#line 1315
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1315
	   f_instruction_name(what->fi_code), f_type_name(T_PATH), f_type_name(v1.type));
#line 1315
;
    
#line 1316 "filter/f-inst.c"
 
#line 1316 "filter/f-inst.c"
 
#line 1316
if (v2.type != (T_INT))
#line 1316
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 1316
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 1316
;
     
#line 1317 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_PATH, .val.ad =  as_path_prepend(fpool, v1.val.ad, v2.val.i)  } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1320 "filter/f-inst.c"
  break;
#line 1320

#line 1320

#line 1377 "filter/f-inst.c"
 /* Constructor for FI_CLIST_ADD */
#line 1377
  case FI_CLIST_ADD:
#line 1377
  #define whati (&(what->i_FI_CLIST_ADD))
#line 1377
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
	do { res =  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_add(fpool, v1.val.ad, v2.val.i)  } ; fstk->vcnt++; } while (0);
      /* IP->Quad implicit conversion */
      else if (val_is_ip4(&v2))
	do { res =  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_add(fpool, v1.val.ad, ipa_to_u32(v2.val.ip))  } ; fstk->vcnt++; } while (0);
      else if ((v2.type == T_SET) && clist_set_type(v2.val.t, &dummy))
	runtime("Can't add set");
      else if (v2.type == T_CLIST)
	do { res =  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_union(fpool, v1.val.ad, v2.val.ad)  } ; fstk->vcnt++; } while (0);
      else
	runtime("Can't add non-pair");
    }

    else if (v1.type == T_ECLIST)
    {
      /* v2.val is either EC or EC-set */
      if ((v2.type == T_SET) && eclist_set_type(v2.val.t))
	runtime("Can't add set");
      else if (v2.type == T_ECLIST)
	do { res =  (struct f_val) { .type = T_ECLIST, .val.ad =  ec_set_union(fpool, v1.val.ad, v2.val.ad)  } ; fstk->vcnt++; } while (0);
      else if (v2.type != T_EC)
	runtime("Can't add non-ec");
      else
	do { res =  (struct f_val) { .type = T_ECLIST, .val.ad =  ec_set_add(fpool, v1.val.ad, v2.val.ec)  } ; fstk->vcnt++; } while (0);
    }

    else if (v1.type == T_LCLIST)
    {
      /* v2.val is either LC or LC-set */
      if ((v2.type == T_SET) && lclist_set_type(v2.val.t))
	runtime("Can't add set");
      else if (v2.type == T_LCLIST)
	do { res =  (struct f_val) { .type = T_LCLIST, .val.ad =  lc_set_union(fpool, v1.val.ad, v2.val.ad)  } ; fstk->vcnt++; } while (0);
      else if (v2.type != T_LC)
	runtime("Can't add non-lc");
      else
	do { res =  (struct f_val) { .type = T_LCLIST, .val.ad =  lc_set_add(fpool, v1.val.ad, v2.val.lc)  } ; fstk->vcnt++; } while (0);

    }

    else
      runtime("Can't add to non-[e|l]clist");
  }

  
  #undef whati
#line 1377 "filter/f-inst.c"
  break;
#line 1377

#line 1377

#line 1432 "filter/f-inst.c"
 /* Constructor for FI_CLIST_DEL */
#line 1432
  case FI_CLIST_DEL:
#line 1432
  #define whati (&(what->i_FI_CLIST_DEL))
#line 1432
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
	do { res =  (struct f_val) { .type = T_PATH, .val.ad =  as_path_filter(fpool, v1.val.ad, &v2, 0)  } ; fstk->vcnt++; } while (0);
      else
	runtime("Can't delete non-integer (set)");
    }

    else if (v1.type == T_CLIST)
    {
      /* Community (or cluster) list */
      struct f_val dummy;

      if ((v2.type == T_PAIR) || (v2.type == T_QUAD))
	do { res =  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_del(fpool, v1.val.ad, v2.val.i)  } ; fstk->vcnt++; } while (0);
      /* IP->Quad implicit conversion */
      else if (val_is_ip4(&v2))
	do { res =  (struct f_val) { .type = T_CLIST, .val.ad =  int_set_del(fpool, v1.val.ad, ipa_to_u32(v2.val.ip))  } ; fstk->vcnt++; } while (0);
      else if ((v2.type == T_SET) && clist_set_type(v2.val.t, &dummy) || (v2.type == T_CLIST))
	do { res =  (struct f_val) { .type = T_CLIST, .val.ad =  clist_filter(fpool, v1.val.ad, &v2, 0)  } ; fstk->vcnt++; } while (0);
      else
	runtime("Can't delete non-pair");
    }

    else if (v1.type == T_ECLIST)
    {
      /* v2.val is either EC or EC-set */
      if ((v2.type == T_SET) && eclist_set_type(v2.val.t) || (v2.type == T_ECLIST))
	do { res =  (struct f_val) { .type = T_ECLIST, .val.ad =  eclist_filter(fpool, v1.val.ad, &v2, 0)  } ; fstk->vcnt++; } while (0);
      else if (v2.type != T_EC)
	runtime("Can't delete non-ec");
      else
	do { res =  (struct f_val) { .type = T_ECLIST, .val.ad =  ec_set_del(fpool, v1.val.ad, v2.val.ec)  } ; fstk->vcnt++; } while (0);
    }

    else if (v1.type == T_LCLIST)
    {
      /* v2.val is either LC or LC-set */
      if ((v2.type == T_SET) && lclist_set_type(v2.val.t) || (v2.type == T_LCLIST))
	do { res =  (struct f_val) { .type = T_LCLIST, .val.ad =  lclist_filter(fpool, v1.val.ad, &v2, 0)  } ; fstk->vcnt++; } while (0);
      else if (v2.type != T_LC)
	runtime("Can't delete non-lc");
      else
	do { res =  (struct f_val) { .type = T_LCLIST, .val.ad =  lc_set_del(fpool, v1.val.ad, v2.val.lc)  } ; fstk->vcnt++; } while (0);
    }

    else
      runtime("Can't delete in non-[e|l]clist");
  }

  
  #undef whati
#line 1432 "filter/f-inst.c"
  break;
#line 1432

#line 1432

#line 1478 "filter/f-inst.c"
 /* Constructor for FI_CLIST_FILTER */
#line 1478
  case FI_CLIST_FILTER:
#line 1478
  #define whati (&(what->i_FI_CLIST_FILTER))
#line 1478
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
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
	do { res =  (struct f_val) { .type = T_PATH, .val.ad =  as_path_filter(fpool, v1.val.ad, &v2, 1)  } ; fstk->vcnt++; } while (0);
      else
	runtime("Can't filter integer");
    }

    else if (v1.type == T_CLIST)
    {
      /* Community (or cluster) list */
      struct f_val dummy;

      if ((v2.type == T_SET) && clist_set_type(v2.val.t, &dummy) || (v2.type == T_CLIST))
	do { res =  (struct f_val) { .type = T_CLIST, .val.ad =  clist_filter(fpool, v1.val.ad, &v2, 1)  } ; fstk->vcnt++; } while (0);
      else
	runtime("Can't filter pair");
    }

    else if (v1.type == T_ECLIST)
    {
      /* v2.val is either EC or EC-set */
      if ((v2.type == T_SET) && eclist_set_type(v2.val.t) || (v2.type == T_ECLIST))
	do { res =  (struct f_val) { .type = T_ECLIST, .val.ad =  eclist_filter(fpool, v1.val.ad, &v2, 1)  } ; fstk->vcnt++; } while (0);
      else
	runtime("Can't filter ec");
    }

    else if (v1.type == T_LCLIST)
    {
      /* v2.val is either LC or LC-set */
      if ((v2.type == T_SET) && lclist_set_type(v2.val.t) || (v2.type == T_LCLIST))
	do { res =  (struct f_val) { .type = T_LCLIST, .val.ad =  lclist_filter(fpool, v1.val.ad, &v2, 1)  } ; fstk->vcnt++; } while (0);
      else
	runtime("Can't filter lc");
    }

    else
      runtime("Can't filter non-[e|l]clist");
  }

  
  #undef whati
#line 1478 "filter/f-inst.c"
  break;
#line 1478

#line 1478

#line 1508 "filter/f-inst.c"
 /* Constructor for FI_ROA_CHECK_IMPLICIT */
#line 1508
  case FI_ROA_CHECK_IMPLICIT:
#line 1508
  #define whati (&(what->i_FI_ROA_CHECK_IMPLICIT))
#line 1508
  
#line 1508
  #line 1478 "filter/f-inst.c"
 {	/* ROA Check */
    ;
    #line 1480 "filter/f-inst.c"
const struct rtable_config * rtc = whati->rtc
#line 1480
;
    struct rtable *table = rtc->table;
    do { if (!fs->rte) runtime("No route to access"); } while (0);
    ACCESS_EATTRS;
    const net_addr *net = (*fs->rte)->net->n.addr;

    /* We ignore temporary attributes, probably not a problem here */
    /* 0x02 is a value of BA_AS_PATH, we don't want to include BGP headers */
    eattr *e = ea_find(*fs->eattrs, EA_CODE(PROTOCOL_BGP, 0x02));

    if (!e || ((e->type & EAF_TYPE_MASK) != EAF_TYPE_AS_PATH))
      runtime("Missing AS_PATH attribute");

    u32 as = 0;
    as_path_get_last(e->u.ptr, &as);

    if (!table)
      runtime("Missing ROA table");

    if (table->addr_type != NET_ROA4 && table->addr_type != NET_ROA6)
      runtime("Table type must be either ROA4 or ROA6");

    if (table->addr_type != (net->type == NET_IP4 ? NET_ROA4 : NET_ROA6))
       
#line 1503 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_ENUM_ROA, .val.i = ROA_UNKNOWN } ; fstk->vcnt++; } while (0); /* Prefix and table type mismatch */
    else
       do { res =  (struct f_val) { .type = T_ENUM_ROA, .val.i =  net_roa_check(table, net, as)  } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1508 "filter/f-inst.c"
  break;
#line 1508

#line 1508

#line 1530 "filter/f-inst.c"
 /* Constructor for FI_ROA_CHECK_EXPLICIT */
#line 1530
  case FI_ROA_CHECK_EXPLICIT:
#line 1530
  #define whati (&(what->i_FI_ROA_CHECK_EXPLICIT))
#line 1530
  if (fstk->vcnt < 2) runtime("Stack underflow"); fstk->vcnt -= 2; 
#line 1530
  #line 1508 "filter/f-inst.c"
 {	/* ROA Check */
    ;
    
#line 1510 "filter/f-inst.c"
 
#line 1510 "filter/f-inst.c"
 
#line 1510
if (v1.type != (T_NET))
#line 1510
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1510
	   f_instruction_name(what->fi_code), f_type_name(T_NET), f_type_name(v1.type));
#line 1510
;
    
#line 1511 "filter/f-inst.c"
 
#line 1511 "filter/f-inst.c"
 
#line 1511
if (v2.type != (T_INT))
#line 1511
  runtime("Argument 2 of %s must be of type %s, got type %s",
#line 1511
	   f_instruction_name(what->fi_code), f_type_name(T_INT), f_type_name(v2.type));
#line 1511
;
    #line 1512 "filter/f-inst.c"
const struct rtable_config * rtc = whati->rtc
#line 1512
;
    struct rtable *table = rtc->table;

    u32 as = v2.val.i;

    if (!table)
      runtime("Missing ROA table");

    if (table->addr_type != NET_ROA4 && table->addr_type != NET_ROA6)
      runtime("Table type must be either ROA4 or ROA6");

    if (table->addr_type != (v1.val.net->type == NET_IP4 ? NET_ROA4 : NET_ROA6))
       
#line 1524 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_ENUM_ROA, .val.i = ROA_UNKNOWN } ; fstk->vcnt++; } while (0); /* Prefix and table type mismatch */
    else
       do { res =  (struct f_val) { .type = T_ENUM_ROA, .val.i =  net_roa_check(table, v1.val.net, as)  } ; fstk->vcnt++; } while (0);

  }

  
  #undef whati
#line 1530 "filter/f-inst.c"
  break;
#line 1530

#line 1530

#line 1535 "filter/f-inst.c"
 /* Constructor for FI_FORMAT */
#line 1535
  case FI_FORMAT:
#line 1535
  #define whati (&(what->i_FI_FORMAT))
#line 1535
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 1535
  #line 1530 "filter/f-inst.c"
 {	/* Format */
    
#line 1531 "filter/f-inst.c"
;
     
#line 1532 "filter/f-inst.c"
 do { res =  (struct f_val) { .type = T_STRING, .val.s = val_format_str(fpool, &v1) } ; fstk->vcnt++; } while (0);
  }

  
  #undef whati
#line 1535 "filter/f-inst.c"
  break;
#line 1535

#line 1535

#line 698 "filter/decl.m4"
 /* Constructor for FI_ASSERT */
#line 698
  case FI_ASSERT:
#line 698
  #define whati (&(what->i_FI_ASSERT))
#line 698
  if (fstk->vcnt < 1) runtime("Stack underflow"); fstk->vcnt -= 1; 
#line 698
  #line 1535 "filter/f-inst.c"
 {	/* Birdtest Assert */
    ;
    
#line 1537 "filter/f-inst.c"
 
#line 1537 "filter/f-inst.c"
 
#line 1537
if (v1.type != (T_BOOL))
#line 1537
  runtime("Argument 1 of %s must be of type %s, got type %s",
#line 1537
	   f_instruction_name(what->fi_code), f_type_name(T_BOOL), f_type_name(v1.type));
#line 1537
;

    #line 1539 "filter/f-inst.c"
const char * s = whati->s
#line 1539
;

    ASSERT(s);

    if (!bt_assert_hook)
      runtime("No bt_assert hook registered, can't assert");

    bt_assert_hook(v1.val.i, what);
  }
#line 698 "filter/decl.m4"

  #undef whati
#line 698 "filter/decl.m4"
  break;
#line 698

#line 698

#line 460 "filter/decl.m4"

