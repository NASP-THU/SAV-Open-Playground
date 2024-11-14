/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         cf_parse
#define yylex           cf_lex
#define yyerror         cf_error
#define yydebug         cf_debug
#define yynerrs         cf_nerrs
#define yylval          cf_lval
#define yychar          cf_char

/* First part of user prologue.  */
#line 50 "conf/gen_parser.m4"

#line 9 "conf/confbase.Y"
/* Headers from conf/confbase.Y */

#define PARSER 1

#include "nest/bird.h"
#include "conf/conf.h"
#include "lib/resource.h"
#include "lib/socket.h"
#include "lib/timer.h"
#include "lib/string.h"
#include "nest/protocol.h"
#include "nest/iface.h"
#include "nest/route.h"
#include "nest/bfd.h"
#include "nest/cli.h"
#include "filter/filter.h"

/* FIXME: Turn on YYERROR_VERBOSE and work around lots of bison bugs? */

/* Defines from conf/confbase.Y */

static void
check_u16(uint val)
{
  if (val > 0xFFFF)
    cf_error("Value %u out of range (0-65535)", val);
}

#define cf_assert(cond, ...) do { if (!(cond)) cf_error(__VA_ARGS__); } while (0)
static inline void cf_assert_symbol(const struct symbol *sym, uint class) {
  switch (class) {
    case SYM_PROTO: cf_assert(sym->class == SYM_PROTO, "Protocol name required"); break;
    case SYM_TEMPLATE: cf_assert(sym->class == SYM_TEMPLATE, "Protocol template name required"); break;
    case SYM_FUNCTION: cf_assert(sym->class == SYM_FUNCTION, "Function name required"); break;
    case SYM_FILTER: cf_assert(sym->class == SYM_FILTER, "Filter name required"); break;
    case SYM_TABLE: cf_assert(sym->class == SYM_TABLE, "Table name required"); break;
    case SYM_ATTRIBUTE: cf_assert(sym->class == SYM_ATTRIBUTE, "Custom attribute name required"); break;
    case SYM_VARIABLE: cf_assert((sym->class & ~0xff) == SYM_VARIABLE, "Variable name required"); break;
    case SYM_CONSTANT: cf_assert((sym->class & ~0xff) == SYM_CONSTANT, "Constant name required"); break;
    default: bug("This shall not happen");
  }
}

#line 9 "conf/flowspec.Y"
/* Headers from conf/flowspec.Y */

#define PARSER 1

#include "nest/bird.h"
#include "lib/flowspec.h"


/* Defines from conf/flowspec.Y */

struct flow_builder *this_flow;


#line 11 "filter/config.Y"
/* Headers from filter/config.Y */

#include "filter/f-inst.h"
#include "filter/data.h"

/* Defines from filter/config.Y */

static inline u32 pair(u32 a, u32 b) { return (a << 16) | b; }
static inline u32 pair_a(u32 p) { return p >> 16; }
static inline u32 pair_b(u32 p) { return p & 0xFFFF; }

#define f_generate_complex(fi_code, da, arg) \
  f_new_inst(FI_EA_SET, f_new_inst(fi_code, f_new_inst(FI_EA_GET, da), arg), da)

static int
f_new_var(struct sym_scope *s)
{
  /*
   * - A variable is an offset on vstack from vbase.
   * - Vbase is set on filter start / function call.
   * - Scopes contain (non-frame) block scopes inside filter/function scope
   * - Each scope knows number of vars in that scope
   * - Offset is therefore a sum of 'slots' up to filter/function scope
   * - New variables are added on top of vstk, so intermediate values cannot
   *   be there during FI_VAR_INIT. I.e. no 'var' inside 'term'.
   * - Also, each f_line must always have its scope, otherwise a variable may
   *   be defined but not initialized if relevant f_line is not executed.
   */

  int offset = s->slots++;

  while (s->block)
  {
    s = s->next;
    ASSERT(s);
    offset += s->slots;
  }

  if (offset >= 0xff)
    cf_error("Too many variables, at most 255 allowed");

  return offset;
}

/*
 * Sets and their items are during parsing handled as lists, linked
 * through left ptr. The first item in a list also contains a pointer
 * to the last item in a list (right ptr). For convenience, even items
 * are handled as one-item lists. Lists are merged by f_merge_items().
 */
static int
f_valid_set_type(int type)
{
  switch (type)
  {
  case T_INT:
  case T_PAIR:
  case T_QUAD:
  case T_ENUM:
  case T_IP:
  case T_EC:
  case T_LC:
  case T_RD:
    return 1;

  default:
    return 0;
  }
}

static inline struct f_tree *
f_new_item(struct f_val from, struct f_val to)
{
  struct f_tree *t = f_new_tree();
  t->right = t;
  t->from = from;
  t->to = to;
  return t;
}

static inline struct f_tree *
f_merge_items(struct f_tree *a, struct f_tree *b)
{
  if (!a) return b;
  a->right->left = b;
  a->right = b->right;
  b->right = NULL;
  return a;
}

static inline struct f_tree *
f_new_pair_item(int fa, int ta, int fb, int tb)
{
  check_u16(fa);
  check_u16(ta);
  check_u16(fb);
  check_u16(tb);

  if ((ta < fa) || (tb < fb))
    cf_error( "From value cannot be higher that To value in pair sets");

  struct f_tree *t = f_new_tree();
  t->right = t;
  t->from.type = t->to.type = T_PAIR;
  t->from.val.i = pair(fa, fb);
  t->to.val.i = pair(ta, tb);
  return t;
}

static inline struct f_tree *
f_new_pair_set(int fa, int ta, int fb, int tb)
{
  check_u16(fa);
  check_u16(ta);
  check_u16(fb);
  check_u16(tb);

  if ((ta < fa) || (tb < fb))
    cf_error( "From value cannot be higher that To value in pair sets");

  struct f_tree *lst = NULL;
  int i;

  for (i = fa; i <= ta; i++)
    lst = f_merge_items(lst, f_new_pair_item(i, i, fb, tb));

  return lst;
}

#define CC_ALL 0xFFFF
#define EC_ALL 0xFFFFFFFF
#define LC_ALL 0xFFFFFFFF

static struct f_tree *
f_new_ec_item(u32 kind, u32 ipv4_used, u32 key, u32 vf, u32 vt)
{
  u64 fm, to;

  if ((kind != EC_GENERIC) && (ipv4_used || (key >= 0x10000))) {
    check_u16(vf);
    if (vt == EC_ALL)
      vt = 0xFFFF;
    else
      check_u16(vt);
  }

  if (kind == EC_GENERIC) {
    fm = ec_generic(key, vf);
    to = ec_generic(key, vt);
  }
  else if (ipv4_used) {
    fm = ec_ip4(kind, key, vf);
    to = ec_ip4(kind, key, vt);
  }
  else if (key < 0x10000) {
    fm = ec_as2(kind, key, vf);
    to = ec_as2(kind, key, vt);
  }
  else {
    fm = ec_as4(kind, key, vf);
    to = ec_as4(kind, key, vt);
  }

  struct f_tree *t = f_new_tree();
  t->right = t;
  t->from.type = t->to.type = T_EC;
  t->from.val.ec = fm;
  t->to.val.ec = to;
  return t;
}

static struct f_tree *
f_new_lc_item(u32 f1, u32 t1, u32 f2, u32 t2, u32 f3, u32 t3)
{
  struct f_tree *t = f_new_tree();
  t->right = t;
  t->from.type = t->to.type = T_LC;
  t->from.val.lc = (lcomm) {f1, f2, f3};
  t->to.val.lc = (lcomm) {t1, t2, t3};
  return t;
}

static inline struct f_inst *
f_generate_empty(struct f_dynamic_attr dyn)
{
  struct f_val empty;

  switch (dyn.type & EAF_TYPE_MASK) {
    case EAF_TYPE_AS_PATH:
      empty = f_const_empty_path;
      break;
    case EAF_TYPE_INT_SET:
      empty = f_const_empty_clist;
      break;
    case EAF_TYPE_EC_SET:
      empty = f_const_empty_eclist;
      break;
    case EAF_TYPE_LC_SET:
      empty = f_const_empty_lclist;
      break;
    default:
      cf_error("Can't empty that attribute");
  }

  return f_new_inst(FI_EA_SET, f_new_inst(FI_CONSTANT, empty), dyn);
}

/*
 * Remove all new lines and doubled whitespaces
 * and convert all tabulators to spaces
 * and return a copy of string
 */
char *
assert_copy_expr(const char *start, size_t len)
{
  /* XXX: Allocates maybe a little more memory than we really finally need */
  char *str = cfg_alloc(len + 1);

  char *dst = str;
  const char *src = start - 1;
  const char *end = start + len;
  while (++src < end)
  {
    if (*src == '\n')
      continue;

    /* Skip doubled whitespaces */
    if (src != start)
    {
      const char *prev = src - 1;
      if ((*src == ' ' || *src == '\t') && (*prev == ' ' || *prev == '\t'))
	continue;
    }

    if (*src == '\t')
      *dst = ' ';
    else
      *dst = *src;

    dst++;
  }
  *dst = '\0';

  return str;
}

/*
 * assert_done - create f_instruction of bt_assert
 * @expr: expression in bt_assert()
 * @start: pointer to first char of test expression
 * @end: pointer to the last char of test expression
 */
static struct f_inst *
assert_done(struct f_inst *expr, const char *start, const char *end)
{
  return f_new_inst(FI_ASSERT, expr,
    (end >= start) ?
      assert_copy_expr(start, end - start + 1)
    : "???");
}

static struct f_inst *
assert_assign(struct f_lval *lval, struct f_inst *expr, const char *start, const char *end)
{
  struct f_inst *setter, *getter, *checker;
  switch (lval->type) {
    case F_LVAL_VARIABLE:
      setter = f_new_inst(FI_VAR_SET, expr, lval->sym);
      getter = f_new_inst(FI_VAR_GET, lval->sym);
      break;
    case F_LVAL_SA:
      setter = f_new_inst(FI_RTA_SET, expr, lval->sa);
      getter = f_new_inst(FI_RTA_GET, lval->sa);
      break;
    case F_LVAL_EA:
      setter = f_new_inst(FI_EA_SET, expr, lval->da);
      getter = f_new_inst(FI_EA_GET, lval->da);
      break;
    default:
      bug("Unknown lval type");
  }

  checker = f_new_inst(FI_EQ, expr, getter);
  setter->next = checker;

  return assert_done(setter, start, end);
}

#line 10 "nest/config.Y"
/* Headers from nest/config.Y */

#include "nest/rt-dev.h"
#include "nest/password.h"
#include "nest/cmds.h"
#include "lib/lists.h"
#include "lib/mac.h"

/* Defines from nest/config.Y */

static struct rtable_config *this_table;
static struct proto_config *this_proto;
static struct channel_config *this_channel;
static struct iface_patt *this_ipatt;
static struct iface_patt_node *this_ipn;
/* static struct roa_table_config *this_roa_table; */
static list *this_p_list;
static struct password_item *this_p_item;
static int password_id;
static struct bfd_options *this_bfd_opts;

static void
iface_patt_check(void)
{
  struct iface_patt_node *pn;

  WALK_LIST(pn, this_ipatt->ipn_list)
    if (!pn->pattern || pn->prefix.type)
      cf_error("Interface name/mask expected, not IP prefix");
}

static inline void
init_password_list(void)
{
   if (!this_p_list) {
      this_p_list = cfg_allocz(sizeof(list));
      init_list(this_p_list);
      password_id = 1;
   }
}

static inline void
init_password(const void *key, uint length, uint id)
{
   this_p_item = cfg_allocz(sizeof (struct password_item));
   this_p_item->password = key;
   this_p_item->length = length;
   this_p_item->genfrom = 0;
   this_p_item->gento = TIME_INFINITY;
   this_p_item->accfrom = 0;
   this_p_item->accto = TIME_INFINITY;
   this_p_item->id = id;
   this_p_item->alg = ALG_UNDEFINED;
   add_tail(this_p_list, &this_p_item->n);
}

static inline void
reset_passwords(void)
{
  this_p_list = NULL;
}

static inline list *
get_passwords(void)
{
  list *rv = this_p_list;
  this_p_list = NULL;
  return rv;
}

static inline void
init_bfd_opts(struct bfd_options **opts)
{
  cf_check_bfd(1);

  if (! *opts)
    *opts = bfd_new_options();
}

static inline void
open_bfd_opts(struct bfd_options **opts)
{
  init_bfd_opts(opts);
  this_bfd_opts = *opts;
}

static inline void
close_bfd_opts(void)
{
  this_bfd_opts = NULL;
}

static void
proto_postconfig(void)
{
  CALL(this_proto->protocol->postconfig, this_proto);
  this_channel = NULL;
  this_proto = NULL;
}


#define DIRECT_CFG ((struct rt_dev_config *) this_proto)

#line 8 "proto/bfd/config.Y"
/* Headers from proto/bfd/config.Y */

#include "proto/bfd/bfd.h"

/* Defines from proto/bfd/config.Y */

#define BFD_CFG ((struct bfd_config *) this_proto)
#define BFD_IFACE ((struct bfd_iface_config *) this_ipatt)
#define BFD_NEIGHBOR this_bfd_neighbor

static struct bfd_neighbor *this_bfd_neighbor;

extern struct bfd_config *bfd_cf;

#line 13 "proto/babel/config.Y"
/* Headers from proto/babel/config.Y */

#include "proto/babel/babel.h"
#include "nest/iface.h"

/* Defines from proto/babel/config.Y */

#define BABEL_CFG ((struct babel_config *) this_proto)
#define BABEL_IFACE ((struct babel_iface_config *) this_ipatt)

#line 9 "proto/bgp/config.Y"
/* Headers from proto/bgp/config.Y */

#include "proto/bgp/bgp.h"

/* Defines from proto/bgp/config.Y */

#define BGP_CFG ((struct bgp_config *) this_proto)
#define BGP_CC ((struct bgp_channel_config *) this_channel)

#line 10 "proto/mrt/config.Y"
/* Headers from proto/mrt/config.Y */

#include "proto/mrt/mrt.h"

/* Defines from proto/mrt/config.Y */

#define MRT_CFG ((struct mrt_config *) this_proto)

#line 9 "proto/ospf/config.Y"
/* Headers from proto/ospf/config.Y */

#include "proto/ospf/ospf.h"

/* Defines from proto/ospf/config.Y */

#define OSPF_CFG ((struct ospf_config *) this_proto)
#define OSPF_PATT ((struct ospf_iface_patt *) this_ipatt)

static struct ospf_area_config *this_area;
static struct nbma_node *this_nbma;
static list *this_nets;
static struct area_net_config *this_pref;
static struct ospf_stubnet_config *this_stubnet;

static inline int ospf_cfg_is_v2(void) { return OSPF_CFG->ospf2; }
static inline int ospf_cfg_is_v3(void) { return ! OSPF_CFG->ospf2; }

static void
ospf_iface_finish(void)
{
  struct ospf_iface_patt *ip = OSPF_PATT;

  if (ip->deadint == 0)
    ip->deadint = ip->deadc * ip->helloint;

  if (ip->waitint == 0)
    ip->waitint = ip->deadc * ip->helloint;

  ip->passwords = get_passwords();

  if (ospf_cfg_is_v2() && (ip->autype == OSPF_AUTH_CRYPT) && (ip->helloint < 5))
    log(L_WARN "Hello or poll interval less that 5 makes cryptographic authenication prone to replay attacks");

  if ((ip->autype == OSPF_AUTH_NONE) && (ip->passwords != NULL))
    log(L_WARN "Password option without authentication option does not make sense");

  if (ip->passwords)
  {
    struct password_item *pass;
    WALK_LIST(pass, *ip->passwords)
    {
      if (pass->alg && (ip->autype != OSPF_AUTH_CRYPT))
	cf_error("Password algorithm option requires cryptographic authentication");

      /* Set default OSPF crypto algorithms */
      if (!pass->alg && (ip->autype == OSPF_AUTH_CRYPT))
	pass->alg = ospf_cfg_is_v2() ? ALG_MD5 : ALG_HMAC_SHA256;

      if (ospf_cfg_is_v3() && ip->autype && (pass->alg < ALG_HMAC))
	cf_error("Keyed hash algorithms are not allowed, use HMAC algorithms");
    }
  }
}

static void
ospf_area_finish(void)
{
  if ((this_area->areaid == 0) && (this_area->type != OPT_E))
    cf_error("Backbone area cannot be stub/NSSA");

  if (this_area->summary && (this_area->type == OPT_E))
    cf_error("Only stub/NSSA areas can use summary propagation");

  if (this_area->default_nssa && ((this_area->type != OPT_N) || ! this_area->summary))
    cf_error("Only NSSA areas with summary propagation can use NSSA default route");

  if ((this_area->default_cost & LSA_EXT3_EBIT) && ! this_area->default_nssa)
    cf_error("Only NSSA default route can use type 2 metric");
}

static void
ospf_proto_finish(void)
{
  struct ospf_config *cf = OSPF_CFG;
  struct ospf_area_config *ac;
  struct ospf_iface_patt *ic;

  /* Define default channel */
  if (! proto_cf_main_channel(this_proto))
  {
    uint net_type = this_proto->net_type = ospf_cfg_is_v2() ? NET_IP4 : NET_IP6;
    channel_config_new(NULL, net_label[net_type], net_type, this_proto);
  }

  /* Propagate global instance ID to interfaces */
  if (cf->instance_id_set)
  {
    WALK_LIST(ac, cf->area_list)
      WALK_LIST(ic, ac->patt_list)
	if (!ic->instance_id_set)
	{ ic->instance_id = cf->instance_id; ic->instance_id_set = 1; }

    WALK_LIST(ic, cf->vlink_list)
      if (!ic->instance_id_set)
      { ic->instance_id = cf->instance_id; ic->instance_id_set = 1; }
  }

  if (ospf_cfg_is_v3())
  {
    uint ipv4 = (this_proto->net_type == NET_IP4);
    uint base = (ipv4 ? 64 : 0) + (cf->af_mc ? 32 : 0);

    /* RFC 5838 - OSPFv3-AF */
    if (cf->af_ext)
    {
      /* RFC 5838 2.1 - instance IDs based on AFs */
      WALK_LIST(ac, cf->area_list)
	WALK_LIST(ic, ac->patt_list)
	{
	  if (!ic->instance_id_set)
	    ic->instance_id = base;
	  else if (ic->instance_id >= 128)
	    log(L_WARN "Instance ID %d from unassigned/private range", ic->instance_id);
	  else if ((ic->instance_id < base) || (ic->instance_id >= (base + 32)))
	    cf_error("Instance ID %d invalid for given channel type", ic->instance_id);
	}

      /* RFC 5838 2.8 - vlinks limited to IPv6 unicast */
      if ((ipv4 || cf->af_mc) && !EMPTY_LIST(cf->vlink_list))
	cf_error("Vlinks not supported in AFs other than IPv6 unicast");
    }
    else
    {
      if (ipv4 || cf->af_mc)
	cf_error("Different channel type");
    }
  }

  if (EMPTY_LIST(cf->area_list))
    cf_error("No configured areas in OSPF");

  int areano = 0;
  int backbone = 0;
  int nssa = 0;
  WALK_LIST(ac, cf->area_list)
  {
    areano++;
    if (ac->areaid == 0)
      backbone = 1;
    if (ac->type == OPT_N)
      nssa = 1;
  }

  cf->abr = areano > 1;

  /* Route export or NSSA translation (RFC 3101 3.1) */
  cf->asbr = (proto_cf_main_channel(this_proto)->out_filter != FILTER_REJECT) || (nssa && cf->abr);

  if (cf->abr && !backbone)
  {
    struct ospf_area_config *ac = cfg_allocz(sizeof(struct ospf_area_config));
    ac->type = OPT_E; /* Backbone is non-stub */
    add_head(&cf->area_list, NODE ac);
    init_list(&ac->patt_list);
    init_list(&ac->net_list);
    init_list(&ac->enet_list);
    init_list(&ac->stubnet_list);
  }

  if (!cf->abr && !EMPTY_LIST(cf->vlink_list))
    cf_error("Vlinks cannot be used on single area router");

  if (cf->asbr && (areano == 1) && (this_area->type == 0))
    cf_error("ASBR must be in non-stub area");
}

static inline void
ospf_check_defcost(int cost)
{
  if ((cost <= 0) || (cost >= LSINFINITY))
   cf_error("Default cost must be in range 1-%u", LSINFINITY-1);
}

static inline void
ospf_check_auth(void)
{
  if (ospf_cfg_is_v3())
    cf_error("Plaintext authentication not supported in OSPFv3");
}


#line 9 "proto/perf/config.Y"
/* Headers from proto/perf/config.Y */

#include "filter/filter.h"
#include "proto/perf/perf.h"

/* Defines from proto/perf/config.Y */

#define PERF_CFG ((struct perf_config *) this_proto)

#line 9 "proto/pipe/config.Y"
/* Headers from proto/pipe/config.Y */

#include "proto/pipe/pipe.h"

/* Defines from proto/pipe/config.Y */

#define PIPE_CFG ((struct pipe_config *) this_proto)

#line 10 "proto/radv/config.Y"
/* Headers from proto/radv/config.Y */

#include "proto/radv/radv.h"

/* Defines from proto/radv/config.Y */

#define RADV_CFG ((struct radv_config *) this_proto)
#define RADV_IFACE ((struct radv_iface_config *) this_ipatt)
#define RADV_PREFIX this_radv_prefix
#define RADV_RDNSS (&this_radv_rdnss)
#define RADV_DNSSL (&this_radv_dnssl)

static struct radv_prefix_config *this_radv_prefix;
static struct radv_rdnss_config this_radv_rdnss;
static struct radv_dnssl_config this_radv_dnssl;
static list radv_dns_list;	/* Used by radv_rdnss and radv_dnssl */
static u8 radv_mult_val;	/* Used by radv_mult for second return value */


#line 12 "proto/rip/config.Y"
/* Headers from proto/rip/config.Y */

#include "proto/rip/rip.h"
#include "nest/iface.h"

/* Defines from proto/rip/config.Y */

#define RIP_CFG ((struct rip_config *) this_proto)
#define RIP_IFACE ((struct rip_iface_config *) this_ipatt)

static inline int rip_cfg_is_v2(void) { return RIP_CFG->rip2; }
static inline int rip_cfg_is_ng(void) { return ! RIP_CFG->rip2; }

static inline void
rip_check_auth(void)
{
  if (rip_cfg_is_ng())
    cf_error("Authentication not supported in RIPng");
}


#line 9 "proto/rpki/config.Y"
/* Headers from proto/rpki/config.Y */

#include "proto/rpki/rpki.h"

/* Defines from proto/rpki/config.Y */

#define RPKI_CFG ((struct rpki_config *) this_proto)
#define RPKI_TR_SSH_CFG ((struct rpki_tr_ssh_config *) RPKI_CFG->tr_config.spec)

static void
rpki_check_unused_hostname(void)
{
  if (RPKI_CFG->hostname != NULL)
    cf_error("Only one cache server per protocol allowed");
}

static void
rpki_check_unused_transport(void)
{
  if (RPKI_CFG->tr_config.spec != NULL)
    cf_error("At the most one transport per protocol allowed");
}

#line 9 "proto/static/config.Y"
/* Headers from proto/static/config.Y */

#include "proto/static/static.h"

/* Defines from proto/static/config.Y */

#define STATIC_CFG ((struct static_config *) this_proto)
static struct static_route *this_srt, *this_snh;
static struct f_inst *this_srt_cmds, *this_srt_last_cmd;

static struct static_route *
static_nexthop_new(void)
{
  struct static_route *nh = this_srt;

  if (this_snh)
  {
    /* Additional next hop */
    nh = cfg_allocz(sizeof(struct static_route));
    nh->net = this_srt->net;
    this_snh->mp_next = nh;
  }

  nh->dest = RTD_UNICAST;
  nh->mp_head = this_srt;
  return nh;
};

static void
static_route_finish(void)
{
  if (net_type_match(this_srt->net, NB_DEST) == !this_srt->dest)
    cf_error("Unexpected or missing nexthop/type");

  this_srt->cmds = f_linearize(this_srt_cmds, 0);
}

#line 9 "sysdep/linux/netlink.Y"
/* Headers from sysdep/linux/netlink.Y */

#line 9 "sysdep/unix/config.Y"
/* Headers from sysdep/unix/config.Y */

#include "sysdep/unix/unix.h"
#include <stdio.h>

/* Defines from sysdep/unix/config.Y */

static struct log_config *this_log;

#line 9 "sysdep/unix/krt.Y"
/* Headers from sysdep/unix/krt.Y */

#include "sysdep/unix/krt.h"

/* Defines from sysdep/unix/krt.Y */

#define THIS_KRT ((struct krt_config *) this_proto)
#define THIS_KIF ((struct kif_config *) this_proto)
#define KIF_IFACE ((struct kif_iface_config *) this_ipatt)

static void
kif_set_preferred(ip_addr ip)
{
  if (ipa_is_ip4(ip))
    KIF_IFACE->pref_v4 = ip;
  else if (!ipa_is_link_local(ip))
    KIF_IFACE->pref_v6 = ip;
  else
    KIF_IFACE->pref_ll = ip;
}

#line 50 "conf/gen_parser.m4"

#line 919 "obj/conf/cf-parse.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "cf-parse.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_QUIT = 3,                       /* QUIT  */
  YYSYMBOL_EXIT = 4,                       /* EXIT  */
  YYSYMBOL_HELP = 5,                       /* HELP  */
  YYSYMBOL_END = 6,                        /* END  */
  YYSYMBOL_CLI_MARKER = 7,                 /* CLI_MARKER  */
  YYSYMBOL_INVALID_TOKEN = 8,              /* INVALID_TOKEN  */
  YYSYMBOL_ELSECOL = 9,                    /* ELSECOL  */
  YYSYMBOL_DDOT = 10,                      /* DDOT  */
  YYSYMBOL_GEQ = 11,                       /* GEQ  */
  YYSYMBOL_LEQ = 12,                       /* LEQ  */
  YYSYMBOL_NEQ = 13,                       /* NEQ  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_PO = 16,                        /* PO  */
  YYSYMBOL_PC = 17,                        /* PC  */
  YYSYMBOL_NUM = 18,                       /* NUM  */
  YYSYMBOL_ENUM = 19,                      /* ENUM  */
  YYSYMBOL_IP4 = 20,                       /* IP4  */
  YYSYMBOL_IP6 = 21,                       /* IP6  */
  YYSYMBOL_VPN_RD = 22,                    /* VPN_RD  */
  YYSYMBOL_CF_SYM_KNOWN = 23,              /* CF_SYM_KNOWN  */
  YYSYMBOL_CF_SYM_UNDEFINED = 24,          /* CF_SYM_UNDEFINED  */
  YYSYMBOL_TEXT = 25,                      /* TEXT  */
  YYSYMBOL_BYTESTRING = 26,                /* BYTESTRING  */
  YYSYMBOL_PREFIX_DUMMY = 27,              /* PREFIX_DUMMY  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_29_ = 29,                       /* '<'  */
  YYSYMBOL_30_ = 30,                       /* '>'  */
  YYSYMBOL_31_ = 31,                       /* '~'  */
  YYSYMBOL_NMA = 32,                       /* NMA  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '%'  */
  YYSYMBOL_38_ = 38,                       /* '!'  */
  YYSYMBOL_39_ = 39,                       /* '.'  */
  YYSYMBOL_DEFINE = 40,                    /* DEFINE  */
  YYSYMBOL_ON = 41,                        /* ON  */
  YYSYMBOL_OFF = 42,                       /* OFF  */
  YYSYMBOL_YES = 43,                       /* YES  */
  YYSYMBOL_NO = 44,                        /* NO  */
  YYSYMBOL_S = 45,                         /* S  */
  YYSYMBOL_MS = 46,                        /* MS  */
  YYSYMBOL_US = 47,                        /* US  */
  YYSYMBOL_PORT = 48,                      /* PORT  */
  YYSYMBOL_VPN = 49,                       /* VPN  */
  YYSYMBOL_MPLS = 50,                      /* MPLS  */
  YYSYMBOL_FROM = 51,                      /* FROM  */
  YYSYMBOL_52_ = 52,                       /* ';'  */
  YYSYMBOL_53_ = 53,                       /* '('  */
  YYSYMBOL_54_ = 54,                       /* ')'  */
  YYSYMBOL_FLOW4 = 55,                     /* FLOW4  */
  YYSYMBOL_FLOW6 = 56,                     /* FLOW6  */
  YYSYMBOL_DST = 57,                       /* DST  */
  YYSYMBOL_SRC = 58,                       /* SRC  */
  YYSYMBOL_PROTO = 59,                     /* PROTO  */
  YYSYMBOL_NEXT = 60,                      /* NEXT  */
  YYSYMBOL_HEADER = 61,                    /* HEADER  */
  YYSYMBOL_DPORT = 62,                     /* DPORT  */
  YYSYMBOL_SPORT = 63,                     /* SPORT  */
  YYSYMBOL_ICMP = 64,                      /* ICMP  */
  YYSYMBOL_TYPE = 65,                      /* TYPE  */
  YYSYMBOL_CODE = 66,                      /* CODE  */
  YYSYMBOL_TCP = 67,                       /* TCP  */
  YYSYMBOL_FLAGS = 68,                     /* FLAGS  */
  YYSYMBOL_LENGTH = 69,                    /* LENGTH  */
  YYSYMBOL_DSCP = 70,                      /* DSCP  */
  YYSYMBOL_DONT_FRAGMENT = 71,             /* DONT_FRAGMENT  */
  YYSYMBOL_IS_FRAGMENT = 72,               /* IS_FRAGMENT  */
  YYSYMBOL_FIRST_FRAGMENT = 73,            /* FIRST_FRAGMENT  */
  YYSYMBOL_LAST_FRAGMENT = 74,             /* LAST_FRAGMENT  */
  YYSYMBOL_FRAGMENT = 75,                  /* FRAGMENT  */
  YYSYMBOL_LABEL = 76,                     /* LABEL  */
  YYSYMBOL_OFFSET = 77,                    /* OFFSET  */
  YYSYMBOL_78_ = 78,                       /* ','  */
  YYSYMBOL_79_ = 79,                       /* '{'  */
  YYSYMBOL_80_ = 80,                       /* '}'  */
  YYSYMBOL_FUNCTION = 81,                  /* FUNCTION  */
  YYSYMBOL_PRINT = 82,                     /* PRINT  */
  YYSYMBOL_PRINTN = 83,                    /* PRINTN  */
  YYSYMBOL_UNSET = 84,                     /* UNSET  */
  YYSYMBOL_RETURN = 85,                    /* RETURN  */
  YYSYMBOL_ACCEPT = 86,                    /* ACCEPT  */
  YYSYMBOL_REJECT = 87,                    /* REJECT  */
  YYSYMBOL_ERROR = 88,                     /* ERROR  */
  YYSYMBOL_INT = 89,                       /* INT  */
  YYSYMBOL_BOOL = 90,                      /* BOOL  */
  YYSYMBOL_IP = 91,                        /* IP  */
  YYSYMBOL_PREFIX = 92,                    /* PREFIX  */
  YYSYMBOL_RD = 93,                        /* RD  */
  YYSYMBOL_PAIR = 94,                      /* PAIR  */
  YYSYMBOL_QUAD = 95,                      /* QUAD  */
  YYSYMBOL_EC = 96,                        /* EC  */
  YYSYMBOL_LC = 97,                        /* LC  */
  YYSYMBOL_SET = 98,                       /* SET  */
  YYSYMBOL_STRING = 99,                    /* STRING  */
  YYSYMBOL_BGPMASK = 100,                  /* BGPMASK  */
  YYSYMBOL_BGPPATH = 101,                  /* BGPPATH  */
  YYSYMBOL_CLIST = 102,                    /* CLIST  */
  YYSYMBOL_ECLIST = 103,                   /* ECLIST  */
  YYSYMBOL_LCLIST = 104,                   /* LCLIST  */
  YYSYMBOL_IF = 105,                       /* IF  */
  YYSYMBOL_THEN = 106,                     /* THEN  */
  YYSYMBOL_ELSE = 107,                     /* ELSE  */
  YYSYMBOL_CASE = 108,                     /* CASE  */
  YYSYMBOL_FOR = 109,                      /* FOR  */
  YYSYMBOL_IN = 110,                       /* IN  */
  YYSYMBOL_DO = 111,                       /* DO  */
  YYSYMBOL_TRUE = 112,                     /* TRUE  */
  YYSYMBOL_FALSE = 113,                    /* FALSE  */
  YYSYMBOL_RT = 114,                       /* RT  */
  YYSYMBOL_RO = 115,                       /* RO  */
  YYSYMBOL_UNKNOWN = 116,                  /* UNKNOWN  */
  YYSYMBOL_GENERIC = 117,                  /* GENERIC  */
  YYSYMBOL_GW = 118,                       /* GW  */
  YYSYMBOL_NET = 119,                      /* NET  */
  YYSYMBOL_MASK = 120,                     /* MASK  */
  YYSYMBOL_SOURCE = 121,                   /* SOURCE  */
  YYSYMBOL_SCOPE = 122,                    /* SCOPE  */
  YYSYMBOL_DEST = 123,                     /* DEST  */
  YYSYMBOL_IFNAME = 124,                   /* IFNAME  */
  YYSYMBOL_IFINDEX = 125,                  /* IFINDEX  */
  YYSYMBOL_WEIGHT = 126,                   /* WEIGHT  */
  YYSYMBOL_GW_MPLS = 127,                  /* GW_MPLS  */
  YYSYMBOL_PREFERENCE = 128,               /* PREFERENCE  */
  YYSYMBOL_ROA_CHECK = 129,                /* ROA_CHECK  */
  YYSYMBOL_ASN = 130,                      /* ASN  */
  YYSYMBOL_IS_V4 = 131,                    /* IS_V4  */
  YYSYMBOL_IS_V6 = 132,                    /* IS_V6  */
  YYSYMBOL_LEN = 133,                      /* LEN  */
  YYSYMBOL_MAXLEN = 134,                   /* MAXLEN  */
  YYSYMBOL_DATA = 135,                     /* DATA  */
  YYSYMBOL_DATA1 = 136,                    /* DATA1  */
  YYSYMBOL_DATA2 = 137,                    /* DATA2  */
  YYSYMBOL_DEFINED = 138,                  /* DEFINED  */
  YYSYMBOL_ADD = 139,                      /* ADD  */
  YYSYMBOL_DELETE = 140,                   /* DELETE  */
  YYSYMBOL_CONTAINS = 141,                 /* CONTAINS  */
  YYSYMBOL_RESET = 142,                    /* RESET  */
  YYSYMBOL_PREPEND = 143,                  /* PREPEND  */
  YYSYMBOL_FIRST = 144,                    /* FIRST  */
  YYSYMBOL_LAST = 145,                     /* LAST  */
  YYSYMBOL_LAST_NONAGGREGATED = 146,       /* LAST_NONAGGREGATED  */
  YYSYMBOL_MATCH = 147,                    /* MATCH  */
  YYSYMBOL_MIN = 148,                      /* MIN  */
  YYSYMBOL_MAX = 149,                      /* MAX  */
  YYSYMBOL_EMPTY = 150,                    /* EMPTY  */
  YYSYMBOL_FILTER = 151,                   /* FILTER  */
  YYSYMBOL_WHERE = 152,                    /* WHERE  */
  YYSYMBOL_EVAL = 153,                     /* EVAL  */
  YYSYMBOL_ATTRIBUTE = 154,                /* ATTRIBUTE  */
  YYSYMBOL_BT_ASSERT = 155,                /* BT_ASSERT  */
  YYSYMBOL_BT_TEST_SUITE = 156,            /* BT_TEST_SUITE  */
  YYSYMBOL_BT_CHECK_ASSIGN = 157,          /* BT_CHECK_ASSIGN  */
  YYSYMBOL_BT_TEST_SAME = 158,             /* BT_TEST_SAME  */
  YYSYMBOL_FORMAT = 159,                   /* FORMAT  */
  YYSYMBOL_160_ = 160,                     /* ':'  */
  YYSYMBOL_161_ = 161,                     /* '['  */
  YYSYMBOL_162_ = 162,                     /* ']'  */
  YYSYMBOL_163_ = 163,                     /* '?'  */
  YYSYMBOL_ROUTER = 164,                   /* ROUTER  */
  YYSYMBOL_ID = 165,                       /* ID  */
  YYSYMBOL_HOSTNAME = 166,                 /* HOSTNAME  */
  YYSYMBOL_PROTOCOL = 167,                 /* PROTOCOL  */
  YYSYMBOL_TEMPLATE = 168,                 /* TEMPLATE  */
  YYSYMBOL_DISABLED = 169,                 /* DISABLED  */
  YYSYMBOL_DEBUG = 170,                    /* DEBUG  */
  YYSYMBOL_ALL = 171,                      /* ALL  */
  YYSYMBOL_DIRECT = 172,                   /* DIRECT  */
  YYSYMBOL_INTERFACE = 173,                /* INTERFACE  */
  YYSYMBOL_IMPORT = 174,                   /* IMPORT  */
  YYSYMBOL_EXPORT = 175,                   /* EXPORT  */
  YYSYMBOL_NONE = 176,                     /* NONE  */
  YYSYMBOL_VRF = 177,                      /* VRF  */
  YYSYMBOL_DEFAULT = 178,                  /* DEFAULT  */
  YYSYMBOL_TABLE = 179,                    /* TABLE  */
  YYSYMBOL_STATES = 180,                   /* STATES  */
  YYSYMBOL_ROUTES = 181,                   /* ROUTES  */
  YYSYMBOL_FILTERS = 182,                  /* FILTERS  */
  YYSYMBOL_IPV4 = 183,                     /* IPV4  */
  YYSYMBOL_IPV6 = 184,                     /* IPV6  */
  YYSYMBOL_VPN4 = 185,                     /* VPN4  */
  YYSYMBOL_VPN6 = 186,                     /* VPN6  */
  YYSYMBOL_ROA4 = 187,                     /* ROA4  */
  YYSYMBOL_ROA6 = 188,                     /* ROA6  */
  YYSYMBOL_SADR = 189,                     /* SADR  */
  YYSYMBOL_RECEIVE = 190,                  /* RECEIVE  */
  YYSYMBOL_LIMIT = 191,                    /* LIMIT  */
  YYSYMBOL_ACTION = 192,                   /* ACTION  */
  YYSYMBOL_WARN = 193,                     /* WARN  */
  YYSYMBOL_BLOCK = 194,                    /* BLOCK  */
  YYSYMBOL_RESTART = 195,                  /* RESTART  */
  YYSYMBOL_DISABLE = 196,                  /* DISABLE  */
  YYSYMBOL_KEEP = 197,                     /* KEEP  */
  YYSYMBOL_FILTERED = 198,                 /* FILTERED  */
  YYSYMBOL_RPKI = 199,                     /* RPKI  */
  YYSYMBOL_PASSWORD = 200,                 /* PASSWORD  */
  YYSYMBOL_KEY = 201,                      /* KEY  */
  YYSYMBOL_PASSIVE = 202,                  /* PASSIVE  */
  YYSYMBOL_TO = 203,                       /* TO  */
  YYSYMBOL_EVENTS = 204,                   /* EVENTS  */
  YYSYMBOL_PACKETS = 205,                  /* PACKETS  */
  YYSYMBOL_PROTOCOLS = 206,                /* PROTOCOLS  */
  YYSYMBOL_CHANNELS = 207,                 /* CHANNELS  */
  YYSYMBOL_INTERFACES = 208,               /* INTERFACES  */
  YYSYMBOL_ALGORITHM = 209,                /* ALGORITHM  */
  YYSYMBOL_KEYED = 210,                    /* KEYED  */
  YYSYMBOL_HMAC = 211,                     /* HMAC  */
  YYSYMBOL_MD5 = 212,                      /* MD5  */
  YYSYMBOL_SHA1 = 213,                     /* SHA1  */
  YYSYMBOL_SHA256 = 214,                   /* SHA256  */
  YYSYMBOL_SHA384 = 215,                   /* SHA384  */
  YYSYMBOL_SHA512 = 216,                   /* SHA512  */
  YYSYMBOL_BLAKE2S128 = 217,               /* BLAKE2S128  */
  YYSYMBOL_BLAKE2S256 = 218,               /* BLAKE2S256  */
  YYSYMBOL_BLAKE2B256 = 219,               /* BLAKE2B256  */
  YYSYMBOL_BLAKE2B512 = 220,               /* BLAKE2B512  */
  YYSYMBOL_PRIMARY = 221,                  /* PRIMARY  */
  YYSYMBOL_STATS = 222,                    /* STATS  */
  YYSYMBOL_COUNT = 223,                    /* COUNT  */
  YYSYMBOL_BY = 224,                       /* BY  */
  YYSYMBOL_COMMANDS = 225,                 /* COMMANDS  */
  YYSYMBOL_PREEXPORT = 226,                /* PREEXPORT  */
  YYSYMBOL_NOEXPORT = 227,                 /* NOEXPORT  */
  YYSYMBOL_EXPORTED = 228,                 /* EXPORTED  */
  YYSYMBOL_GENERATE = 229,                 /* GENERATE  */
  YYSYMBOL_BGP = 230,                      /* BGP  */
  YYSYMBOL_PASSWORDS = 231,                /* PASSWORDS  */
  YYSYMBOL_DESCRIPTION = 232,              /* DESCRIPTION  */
  YYSYMBOL_RELOAD = 233,                   /* RELOAD  */
  YYSYMBOL_OUT = 234,                      /* OUT  */
  YYSYMBOL_MRTDUMP = 235,                  /* MRTDUMP  */
  YYSYMBOL_MESSAGES = 236,                 /* MESSAGES  */
  YYSYMBOL_RESTRICT = 237,                 /* RESTRICT  */
  YYSYMBOL_MEMORY = 238,                   /* MEMORY  */
  YYSYMBOL_IGP_METRIC = 239,               /* IGP_METRIC  */
  YYSYMBOL_CLASS = 240,                    /* CLASS  */
  YYSYMBOL_TIMEFORMAT = 241,               /* TIMEFORMAT  */
  YYSYMBOL_ISO = 242,                      /* ISO  */
  YYSYMBOL_SHORT = 243,                    /* SHORT  */
  YYSYMBOL_LONG = 244,                     /* LONG  */
  YYSYMBOL_ROUTE = 245,                    /* ROUTE  */
  YYSYMBOL_BASE = 246,                     /* BASE  */
  YYSYMBOL_LOG = 247,                      /* LOG  */
  YYSYMBOL_GRACEFUL = 248,                 /* GRACEFUL  */
  YYSYMBOL_WAIT = 249,                     /* WAIT  */
  YYSYMBOL_FLUSH = 250,                    /* FLUSH  */
  YYSYMBOL_AS = 251,                       /* AS  */
  YYSYMBOL_IDLE = 252,                     /* IDLE  */
  YYSYMBOL_RX = 253,                       /* RX  */
  YYSYMBOL_TX = 254,                       /* TX  */
  YYSYMBOL_INTERVAL = 255,                 /* INTERVAL  */
  YYSYMBOL_MULTIPLIER = 256,               /* MULTIPLIER  */
  YYSYMBOL_CHECK = 257,                    /* CHECK  */
  YYSYMBOL_LINK = 258,                     /* LINK  */
  YYSYMBOL_SORTED = 259,                   /* SORTED  */
  YYSYMBOL_TRIE = 260,                     /* TRIE  */
  YYSYMBOL_SETTLE = 261,                   /* SETTLE  */
  YYSYMBOL_TIME = 262,                     /* TIME  */
  YYSYMBOL_GC = 263,                       /* GC  */
  YYSYMBOL_THRESHOLD = 264,                /* THRESHOLD  */
  YYSYMBOL_PERIOD = 265,                   /* PERIOD  */
  YYSYMBOL_IPV4_MC = 266,                  /* IPV4_MC  */
  YYSYMBOL_IPV4_MPLS = 267,                /* IPV4_MPLS  */
  YYSYMBOL_IPV6_MC = 268,                  /* IPV6_MC  */
  YYSYMBOL_IPV6_MPLS = 269,                /* IPV6_MPLS  */
  YYSYMBOL_IPV6_SADR = 270,                /* IPV6_SADR  */
  YYSYMBOL_VPN4_MC = 271,                  /* VPN4_MC  */
  YYSYMBOL_VPN4_MPLS = 272,                /* VPN4_MPLS  */
  YYSYMBOL_VPN6_MC = 273,                  /* VPN6_MC  */
  YYSYMBOL_VPN6_MPLS = 274,                /* VPN6_MPLS  */
  YYSYMBOL_PRI = 275,                      /* PRI  */
  YYSYMBOL_SEC = 276,                      /* SEC  */
  YYSYMBOL_SHOW = 277,                     /* SHOW  */
  YYSYMBOL_STATUS = 278,                   /* STATUS  */
  YYSYMBOL_CALL_AGENT = 279,               /* CALL_AGENT  */
  YYSYMBOL_TEST_LOG = 280,                 /* TEST_LOG  */
  YYSYMBOL_TEST_SEND = 281,                /* TEST_SEND  */
  YYSYMBOL_SUMMARY = 282,                  /* SUMMARY  */
  YYSYMBOL_SYMBOLS = 283,                  /* SYMBOLS  */
  YYSYMBOL_DUMP = 284,                     /* DUMP  */
  YYSYMBOL_RESOURCES = 285,                /* RESOURCES  */
  YYSYMBOL_SOCKETS = 286,                  /* SOCKETS  */
  YYSYMBOL_NEIGHBORS = 287,                /* NEIGHBORS  */
  YYSYMBOL_ATTRIBUTES = 288,               /* ATTRIBUTES  */
  YYSYMBOL_ECHO = 289,                     /* ECHO  */
  YYSYMBOL_ENABLE = 290,                   /* ENABLE  */
  YYSYMBOL_BABEL = 291,                    /* BABEL  */
  YYSYMBOL_METRIC = 292,                   /* METRIC  */
  YYSYMBOL_RXCOST = 293,                   /* RXCOST  */
  YYSYMBOL_HELLO = 294,                    /* HELLO  */
  YYSYMBOL_UPDATE = 295,                   /* UPDATE  */
  YYSYMBOL_WIRED = 296,                    /* WIRED  */
  YYSYMBOL_WIRELESS = 297,                 /* WIRELESS  */
  YYSYMBOL_BUFFER = 298,                   /* BUFFER  */
  YYSYMBOL_PRIORITY = 299,                 /* PRIORITY  */
  YYSYMBOL_HOP = 300,                      /* HOP  */
  YYSYMBOL_BABEL_METRIC = 301,             /* BABEL_METRIC  */
  YYSYMBOL_ENTRIES = 302,                  /* ENTRIES  */
  YYSYMBOL_RANDOMIZE = 303,                /* RANDOMIZE  */
  YYSYMBOL_MAC = 304,                      /* MAC  */
  YYSYMBOL_PERMISSIVE = 305,               /* PERMISSIVE  */
  YYSYMBOL_BFD = 306,                      /* BFD  */
  YYSYMBOL_MULTIHOP = 307,                 /* MULTIHOP  */
  YYSYMBOL_NEIGHBOR = 308,                 /* NEIGHBOR  */
  YYSYMBOL_DEV = 309,                      /* DEV  */
  YYSYMBOL_LOCAL = 310,                    /* LOCAL  */
  YYSYMBOL_AUTHENTICATION = 311,           /* AUTHENTICATION  */
  YYSYMBOL_SIMPLE = 312,                   /* SIMPLE  */
  YYSYMBOL_METICULOUS = 313,               /* METICULOUS  */
  YYSYMBOL_STRICT = 314,                   /* STRICT  */
  YYSYMBOL_BIND = 315,                     /* BIND  */
  YYSYMBOL_SESSIONS = 316,                 /* SESSIONS  */
  YYSYMBOL_HOLD = 317,                     /* HOLD  */
  YYSYMBOL_CONNECT = 318,                  /* CONNECT  */
  YYSYMBOL_RETRY = 319,                    /* RETRY  */
  YYSYMBOL_KEEPALIVE = 320,                /* KEEPALIVE  */
  YYSYMBOL_STARTUP = 321,                  /* STARTUP  */
  YYSYMBOL_VIA = 322,                      /* VIA  */
  YYSYMBOL_SELF = 323,                     /* SELF  */
  YYSYMBOL_PATH = 324,                     /* PATH  */
  YYSYMBOL_START = 325,                    /* START  */
  YYSYMBOL_DELAY = 326,                    /* DELAY  */
  YYSYMBOL_FORGET = 327,                   /* FORGET  */
  YYSYMBOL_AFTER = 328,                    /* AFTER  */
  YYSYMBOL_BGP_PATH = 329,                 /* BGP_PATH  */
  YYSYMBOL_BGP_LOCAL_PREF = 330,           /* BGP_LOCAL_PREF  */
  YYSYMBOL_BGP_MED = 331,                  /* BGP_MED  */
  YYSYMBOL_BGP_ORIGIN = 332,               /* BGP_ORIGIN  */
  YYSYMBOL_BGP_NEXT_HOP = 333,             /* BGP_NEXT_HOP  */
  YYSYMBOL_BGP_ATOMIC_AGGR = 334,          /* BGP_ATOMIC_AGGR  */
  YYSYMBOL_BGP_AGGREGATOR = 335,           /* BGP_AGGREGATOR  */
  YYSYMBOL_BGP_COMMUNITY = 336,            /* BGP_COMMUNITY  */
  YYSYMBOL_BGP_EXT_COMMUNITY = 337,        /* BGP_EXT_COMMUNITY  */
  YYSYMBOL_BGP_LARGE_COMMUNITY = 338,      /* BGP_LARGE_COMMUNITY  */
  YYSYMBOL_ADDRESS = 339,                  /* ADDRESS  */
  YYSYMBOL_RR = 340,                       /* RR  */
  YYSYMBOL_RS = 341,                       /* RS  */
  YYSYMBOL_CLIENT = 342,                   /* CLIENT  */
  YYSYMBOL_CLUSTER = 343,                  /* CLUSTER  */
  YYSYMBOL_AS4 = 344,                      /* AS4  */
  YYSYMBOL_ADVERTISE = 345,                /* ADVERTISE  */
  YYSYMBOL_CAPABILITIES = 346,             /* CAPABILITIES  */
  YYSYMBOL_PREFER = 347,                   /* PREFER  */
  YYSYMBOL_OLDER = 348,                    /* OLDER  */
  YYSYMBOL_MISSING = 349,                  /* MISSING  */
  YYSYMBOL_LLADDR = 350,                   /* LLADDR  */
  YYSYMBOL_DROP = 351,                     /* DROP  */
  YYSYMBOL_IGNORE = 352,                   /* IGNORE  */
  YYSYMBOL_REFRESH = 353,                  /* REFRESH  */
  YYSYMBOL_INTERPRET = 354,                /* INTERPRET  */
  YYSYMBOL_COMMUNITIES = 355,              /* COMMUNITIES  */
  YYSYMBOL_BGP_ORIGINATOR_ID = 356,        /* BGP_ORIGINATOR_ID  */
  YYSYMBOL_BGP_CLUSTER_LIST = 357,         /* BGP_CLUSTER_LIST  */
  YYSYMBOL_IGP = 358,                      /* IGP  */
  YYSYMBOL_GATEWAY = 359,                  /* GATEWAY  */
  YYSYMBOL_RECURSIVE = 360,                /* RECURSIVE  */
  YYSYMBOL_MED = 361,                      /* MED  */
  YYSYMBOL_TTL = 362,                      /* TTL  */
  YYSYMBOL_SECURITY = 363,                 /* SECURITY  */
  YYSYMBOL_DETERMINISTIC = 364,            /* DETERMINISTIC  */
  YYSYMBOL_SECONDARY = 365,                /* SECONDARY  */
  YYSYMBOL_ALLOW = 366,                    /* ALLOW  */
  YYSYMBOL_PATHS = 367,                    /* PATHS  */
  YYSYMBOL_AWARE = 368,                    /* AWARE  */
  YYSYMBOL_EXTENDED = 369,                 /* EXTENDED  */
  YYSYMBOL_SETKEY = 370,                   /* SETKEY  */
  YYSYMBOL_CONFEDERATION = 371,            /* CONFEDERATION  */
  YYSYMBOL_MEMBER = 372,                   /* MEMBER  */
  YYSYMBOL_MULTICAST = 373,                /* MULTICAST  */
  YYSYMBOL_LIVED = 374,                    /* LIVED  */
  YYSYMBOL_STALE = 375,                    /* STALE  */
  YYSYMBOL_IBGP = 376,                     /* IBGP  */
  YYSYMBOL_EBGP = 377,                     /* EBGP  */
  YYSYMBOL_MANDATORY = 378,                /* MANDATORY  */
  YYSYMBOL_INTERNAL = 379,                 /* INTERNAL  */
  YYSYMBOL_EXTERNAL = 380,                 /* EXTERNAL  */
  YYSYMBOL_SETS = 381,                     /* SETS  */
  YYSYMBOL_DYNAMIC = 382,                  /* DYNAMIC  */
  YYSYMBOL_RANGE = 383,                    /* RANGE  */
  YYSYMBOL_NAME = 384,                     /* NAME  */
  YYSYMBOL_DIGITS = 385,                   /* DIGITS  */
  YYSYMBOL_BGP_AIGP = 386,                 /* BGP_AIGP  */
  YYSYMBOL_AIGP = 387,                     /* AIGP  */
  YYSYMBOL_ORIGINATE = 388,                /* ORIGINATE  */
  YYSYMBOL_COST = 389,                     /* COST  */
  YYSYMBOL_ENFORCE = 390,                  /* ENFORCE  */
  YYSYMBOL_FREE = 391,                     /* FREE  */
  YYSYMBOL_VALIDATE = 392,                 /* VALIDATE  */
  YYSYMBOL_ROLE = 393,                     /* ROLE  */
  YYSYMBOL_ROLES = 394,                    /* ROLES  */
  YYSYMBOL_PEER = 395,                     /* PEER  */
  YYSYMBOL_PROVIDER = 396,                 /* PROVIDER  */
  YYSYMBOL_CUSTOMER = 397,                 /* CUSTOMER  */
  YYSYMBOL_RS_SERVER = 398,                /* RS_SERVER  */
  YYSYMBOL_RS_CLIENT = 399,                /* RS_CLIENT  */
  YYSYMBOL_REQUIRE = 400,                  /* REQUIRE  */
  YYSYMBOL_BGP_OTC = 401,                  /* BGP_OTC  */
  YYSYMBOL_GLOBAL = 402,                   /* GLOBAL  */
  YYSYMBOL_RPDP4 = 403,                    /* RPDP4  */
  YYSYMBOL_RPDP6 = 404,                    /* RPDP6  */
  YYSYMBOL_CEASE = 405,                    /* CEASE  */
  YYSYMBOL_HIT = 406,                      /* HIT  */
  YYSYMBOL_ADMINISTRATIVE = 407,           /* ADMINISTRATIVE  */
  YYSYMBOL_SHUTDOWN = 408,                 /* SHUTDOWN  */
  YYSYMBOL_CONFIGURATION = 409,            /* CONFIGURATION  */
  YYSYMBOL_CHANGE = 410,                   /* CHANGE  */
  YYSYMBOL_DECONFIGURED = 411,             /* DECONFIGURED  */
  YYSYMBOL_CONNECTION = 412,               /* CONNECTION  */
  YYSYMBOL_REJECTED = 413,                 /* REJECTED  */
  YYSYMBOL_COLLISION = 414,                /* COLLISION  */
  YYSYMBOL_OF = 415,                       /* OF  */
  YYSYMBOL_MRT = 416,                      /* MRT  */
  YYSYMBOL_FILENAME = 417,                 /* FILENAME  */
  YYSYMBOL_ALWAYS = 418,                   /* ALWAYS  */
  YYSYMBOL_OSPF = 419,                     /* OSPF  */
  YYSYMBOL_V2 = 420,                       /* V2  */
  YYSYMBOL_V3 = 421,                       /* V3  */
  YYSYMBOL_OSPF_METRIC1 = 422,             /* OSPF_METRIC1  */
  YYSYMBOL_OSPF_METRIC2 = 423,             /* OSPF_METRIC2  */
  YYSYMBOL_OSPF_TAG = 424,                 /* OSPF_TAG  */
  YYSYMBOL_OSPF_ROUTER_ID = 425,           /* OSPF_ROUTER_ID  */
  YYSYMBOL_AREA = 426,                     /* AREA  */
  YYSYMBOL_RFC1583COMPAT = 427,            /* RFC1583COMPAT  */
  YYSYMBOL_STUB = 428,                     /* STUB  */
  YYSYMBOL_TICK = 429,                     /* TICK  */
  YYSYMBOL_COST2 = 430,                    /* COST2  */
  YYSYMBOL_RETRANSMIT = 431,               /* RETRANSMIT  */
  YYSYMBOL_TRANSMIT = 432,                 /* TRANSMIT  */
  YYSYMBOL_DEAD = 433,                     /* DEAD  */
  YYSYMBOL_BROADCAST = 434,                /* BROADCAST  */
  YYSYMBOL_BCAST = 435,                    /* BCAST  */
  YYSYMBOL_NONBROADCAST = 436,             /* NONBROADCAST  */
  YYSYMBOL_NBMA = 437,                     /* NBMA  */
  YYSYMBOL_POINTOPOINT = 438,              /* POINTOPOINT  */
  YYSYMBOL_PTP = 439,                      /* PTP  */
  YYSYMBOL_POINTOMULTIPOINT = 440,         /* POINTOMULTIPOINT  */
  YYSYMBOL_PTMP = 441,                     /* PTMP  */
  YYSYMBOL_CRYPTOGRAPHIC = 442,            /* CRYPTOGRAPHIC  */
  YYSYMBOL_ELIGIBLE = 443,                 /* ELIGIBLE  */
  YYSYMBOL_POLL = 444,                     /* POLL  */
  YYSYMBOL_NETWORKS = 445,                 /* NETWORKS  */
  YYSYMBOL_HIDDEN = 446,                   /* HIDDEN  */
  YYSYMBOL_VIRTUAL = 447,                  /* VIRTUAL  */
  YYSYMBOL_ONLY = 448,                     /* ONLY  */
  YYSYMBOL_LARGE = 449,                    /* LARGE  */
  YYSYMBOL_NORMAL = 450,                   /* NORMAL  */
  YYSYMBOL_STUBNET = 451,                  /* STUBNET  */
  YYSYMBOL_TAG = 452,                      /* TAG  */
  YYSYMBOL_LSADB = 453,                    /* LSADB  */
  YYSYMBOL_ECMP = 454,                     /* ECMP  */
  YYSYMBOL_NSSA = 455,                     /* NSSA  */
  YYSYMBOL_TRANSLATOR = 456,               /* TRANSLATOR  */
  YYSYMBOL_STABILITY = 457,                /* STABILITY  */
  YYSYMBOL_LSID = 458,                     /* LSID  */
  YYSYMBOL_INSTANCE = 459,                 /* INSTANCE  */
  YYSYMBOL_REAL = 460,                     /* REAL  */
  YYSYMBOL_NETMASK = 461,                  /* NETMASK  */
  YYSYMBOL_MERGE = 462,                    /* MERGE  */
  YYSYMBOL_LSA = 463,                      /* LSA  */
  YYSYMBOL_SUPPRESSION = 464,              /* SUPPRESSION  */
  YYSYMBOL_RFC5838 = 465,                  /* RFC5838  */
  YYSYMBOL_PE = 466,                       /* PE  */
  YYSYMBOL_TOPOLOGY = 467,                 /* TOPOLOGY  */
  YYSYMBOL_STATE = 468,                    /* STATE  */
  YYSYMBOL_PERF = 469,                     /* PERF  */
  YYSYMBOL_EXP = 470,                      /* EXP  */
  YYSYMBOL_REPEAT = 471,                   /* REPEAT  */
  YYSYMBOL_MODE = 472,                     /* MODE  */
  YYSYMBOL_PIPE = 473,                     /* PIPE  */
  YYSYMBOL_RADV = 474,                     /* RADV  */
  YYSYMBOL_RA = 475,                       /* RA  */
  YYSYMBOL_SOLICITED = 476,                /* SOLICITED  */
  YYSYMBOL_UNICAST = 477,                  /* UNICAST  */
  YYSYMBOL_MANAGED = 478,                  /* MANAGED  */
  YYSYMBOL_OTHER = 479,                    /* OTHER  */
  YYSYMBOL_CONFIG = 480,                   /* CONFIG  */
  YYSYMBOL_LINGER = 481,                   /* LINGER  */
  YYSYMBOL_MTU = 482,                      /* MTU  */
  YYSYMBOL_REACHABLE = 483,                /* REACHABLE  */
  YYSYMBOL_RETRANS = 484,                  /* RETRANS  */
  YYSYMBOL_TIMER = 485,                    /* TIMER  */
  YYSYMBOL_CURRENT = 486,                  /* CURRENT  */
  YYSYMBOL_VALID = 487,                    /* VALID  */
  YYSYMBOL_PREFERRED = 488,                /* PREFERRED  */
  YYSYMBOL_MULT = 489,                     /* MULT  */
  YYSYMBOL_LIFETIME = 490,                 /* LIFETIME  */
  YYSYMBOL_SKIP = 491,                     /* SKIP  */
  YYSYMBOL_ONLINK = 492,                   /* ONLINK  */
  YYSYMBOL_AUTONOMOUS = 493,               /* AUTONOMOUS  */
  YYSYMBOL_RDNSS = 494,                    /* RDNSS  */
  YYSYMBOL_DNSSL = 495,                    /* DNSSL  */
  YYSYMBOL_NS = 496,                       /* NS  */
  YYSYMBOL_DOMAIN = 497,                   /* DOMAIN  */
  YYSYMBOL_TRIGGER = 498,                  /* TRIGGER  */
  YYSYMBOL_SENSITIVE = 499,                /* SENSITIVE  */
  YYSYMBOL_LOW = 500,                      /* LOW  */
  YYSYMBOL_MEDIUM = 501,                   /* MEDIUM  */
  YYSYMBOL_HIGH = 502,                     /* HIGH  */
  YYSYMBOL_PROPAGATE = 503,                /* PROPAGATE  */
  YYSYMBOL_RA_PREFERENCE = 504,            /* RA_PREFERENCE  */
  YYSYMBOL_RA_LIFETIME = 505,              /* RA_LIFETIME  */
  YYSYMBOL_RIP = 506,                      /* RIP  */
  YYSYMBOL_NG = 507,                       /* NG  */
  YYSYMBOL_INFINITY = 508,                 /* INFINITY  */
  YYSYMBOL_TIMEOUT = 509,                  /* TIMEOUT  */
  YYSYMBOL_GARBAGE = 510,                  /* GARBAGE  */
  YYSYMBOL_VERSION = 511,                  /* VERSION  */
  YYSYMBOL_SPLIT = 512,                    /* SPLIT  */
  YYSYMBOL_HORIZON = 513,                  /* HORIZON  */
  YYSYMBOL_POISON = 514,                   /* POISON  */
  YYSYMBOL_REVERSE = 515,                  /* REVERSE  */
  YYSYMBOL_ZERO = 516,                     /* ZERO  */
  YYSYMBOL_PLAINTEXT = 517,                /* PLAINTEXT  */
  YYSYMBOL_DEMAND = 518,                   /* DEMAND  */
  YYSYMBOL_CIRCUIT = 519,                  /* CIRCUIT  */
  YYSYMBOL_RIP_METRIC = 520,               /* RIP_METRIC  */
  YYSYMBOL_RIP_TAG = 521,                  /* RIP_TAG  */
  YYSYMBOL_REMOTE = 522,                   /* REMOTE  */
  YYSYMBOL_BIRD = 523,                     /* BIRD  */
  YYSYMBOL_PRIVATE = 524,                  /* PRIVATE  */
  YYSYMBOL_PUBLIC = 525,                   /* PUBLIC  */
  YYSYMBOL_SSH = 526,                      /* SSH  */
  YYSYMBOL_TRANSPORT = 527,                /* TRANSPORT  */
  YYSYMBOL_USER = 528,                     /* USER  */
  YYSYMBOL_EXPIRE = 529,                   /* EXPIRE  */
  YYSYMBOL_STATIC = 530,                   /* STATIC  */
  YYSYMBOL_PROHIBIT = 531,                 /* PROHIBIT  */
  YYSYMBOL_BLACKHOLE = 532,                /* BLACKHOLE  */
  YYSYMBOL_UNREACHABLE = 533,              /* UNREACHABLE  */
  YYSYMBOL_KERNEL = 534,                   /* KERNEL  */
  YYSYMBOL_NETLINK = 535,                  /* NETLINK  */
  YYSYMBOL_KRT_PREFSRC = 536,              /* KRT_PREFSRC  */
  YYSYMBOL_KRT_REALM = 537,                /* KRT_REALM  */
  YYSYMBOL_KRT_SCOPE = 538,                /* KRT_SCOPE  */
  YYSYMBOL_KRT_MTU = 539,                  /* KRT_MTU  */
  YYSYMBOL_KRT_WINDOW = 540,               /* KRT_WINDOW  */
  YYSYMBOL_KRT_RTT = 541,                  /* KRT_RTT  */
  YYSYMBOL_KRT_RTTVAR = 542,               /* KRT_RTTVAR  */
  YYSYMBOL_KRT_SSTRESH = 543,              /* KRT_SSTRESH  */
  YYSYMBOL_KRT_CWND = 544,                 /* KRT_CWND  */
  YYSYMBOL_KRT_ADVMSS = 545,               /* KRT_ADVMSS  */
  YYSYMBOL_KRT_REORDERING = 546,           /* KRT_REORDERING  */
  YYSYMBOL_KRT_HOPLIMIT = 547,             /* KRT_HOPLIMIT  */
  YYSYMBOL_KRT_INITCWND = 548,             /* KRT_INITCWND  */
  YYSYMBOL_KRT_RTO_MIN = 549,              /* KRT_RTO_MIN  */
  YYSYMBOL_KRT_INITRWND = 550,             /* KRT_INITRWND  */
  YYSYMBOL_KRT_QUICKACK = 551,             /* KRT_QUICKACK  */
  YYSYMBOL_KRT_LOCK_MTU = 552,             /* KRT_LOCK_MTU  */
  YYSYMBOL_KRT_LOCK_WINDOW = 553,          /* KRT_LOCK_WINDOW  */
  YYSYMBOL_KRT_LOCK_RTT = 554,             /* KRT_LOCK_RTT  */
  YYSYMBOL_KRT_LOCK_RTTVAR = 555,          /* KRT_LOCK_RTTVAR  */
  YYSYMBOL_KRT_LOCK_SSTRESH = 556,         /* KRT_LOCK_SSTRESH  */
  YYSYMBOL_KRT_LOCK_CWND = 557,            /* KRT_LOCK_CWND  */
  YYSYMBOL_KRT_LOCK_ADVMSS = 558,          /* KRT_LOCK_ADVMSS  */
  YYSYMBOL_KRT_LOCK_REORDERING = 559,      /* KRT_LOCK_REORDERING  */
  YYSYMBOL_KRT_LOCK_HOPLIMIT = 560,        /* KRT_LOCK_HOPLIMIT  */
  YYSYMBOL_KRT_LOCK_RTO_MIN = 561,         /* KRT_LOCK_RTO_MIN  */
  YYSYMBOL_KRT_FEATURE_ECN = 562,          /* KRT_FEATURE_ECN  */
  YYSYMBOL_KRT_FEATURE_ALLFRAG = 563,      /* KRT_FEATURE_ALLFRAG  */
  YYSYMBOL_SYSLOG = 564,                   /* SYSLOG  */
  YYSYMBOL_TRACE = 565,                    /* TRACE  */
  YYSYMBOL_INFO = 566,                     /* INFO  */
  YYSYMBOL_WARNING = 567,                  /* WARNING  */
  YYSYMBOL_AUTH = 568,                     /* AUTH  */
  YYSYMBOL_FATAL = 569,                    /* FATAL  */
  YYSYMBOL_BUG = 570,                      /* BUG  */
  YYSYMBOL_STDERR = 571,                   /* STDERR  */
  YYSYMBOL_SOFT = 572,                     /* SOFT  */
  YYSYMBOL_CONFIRM = 573,                  /* CONFIRM  */
  YYSYMBOL_UNDO = 574,                     /* UNDO  */
  YYSYMBOL_LATENCY = 575,                  /* LATENCY  */
  YYSYMBOL_WATCHDOG = 576,                 /* WATCHDOG  */
  YYSYMBOL_CONFIGURE = 577,                /* CONFIGURE  */
  YYSYMBOL_DOWN = 578,                     /* DOWN  */
  YYSYMBOL_PERSIST = 579,                  /* PERSIST  */
  YYSYMBOL_SCAN = 580,                     /* SCAN  */
  YYSYMBOL_LEARN = 581,                    /* LEARN  */
  YYSYMBOL_DEVICE = 582,                   /* DEVICE  */
  YYSYMBOL_KRT_SOURCE = 583,               /* KRT_SOURCE  */
  YYSYMBOL_KRT_METRIC = 584,               /* KRT_METRIC  */
  YYSYMBOL_YYACCEPT = 585,                 /* $accept  */
  YYSYMBOL_cli_cmd = 586,                  /* cli_cmd  */
  YYSYMBOL_cmd_QUIT = 587,                 /* cmd_QUIT  */
  YYSYMBOL_cmd_EXIT = 588,                 /* cmd_EXIT  */
  YYSYMBOL_cmd_HELP = 589,                 /* cmd_HELP  */
  YYSYMBOL_config = 590,                   /* config  */
  YYSYMBOL_conf_entries = 591,             /* conf_entries  */
  YYSYMBOL_conf = 592,                     /* conf  */
  YYSYMBOL_definition = 593,               /* definition  */
  YYSYMBOL_expr = 594,                     /* expr  */
  YYSYMBOL_expr_us = 595,                  /* expr_us  */
  YYSYMBOL_symbol = 596,                   /* symbol  */
  YYSYMBOL_bool = 597,                     /* bool  */
  YYSYMBOL_ipa = 598,                      /* ipa  */
  YYSYMBOL_ipa_scope = 599,                /* ipa_scope  */
  YYSYMBOL_pxlen4 = 600,                   /* pxlen4  */
  YYSYMBOL_net_ip4_ = 601,                 /* net_ip4_  */
  YYSYMBOL_net_ip6_ = 602,                 /* net_ip6_  */
  YYSYMBOL_net_ip6_sadr_ = 603,            /* net_ip6_sadr_  */
  YYSYMBOL_net_vpn4_ = 604,                /* net_vpn4_  */
  YYSYMBOL_net_vpn6_ = 605,                /* net_vpn6_  */
  YYSYMBOL_net_roa4_ = 606,                /* net_roa4_  */
  YYSYMBOL_net_roa6_ = 607,                /* net_roa6_  */
  YYSYMBOL_net_mpls_ = 608,                /* net_mpls_  */
  YYSYMBOL_net_ip_ = 609,                  /* net_ip_  */
  YYSYMBOL_net_vpn_ = 610,                 /* net_vpn_  */
  YYSYMBOL_net_roa_ = 611,                 /* net_roa_  */
  YYSYMBOL_net_ = 612,                     /* net_  */
  YYSYMBOL_net_ip4 = 613,                  /* net_ip4  */
  YYSYMBOL_net_ip6 = 614,                  /* net_ip6  */
  YYSYMBOL_net_ip = 615,                   /* net_ip  */
  YYSYMBOL_net_any = 616,                  /* net_any  */
  YYSYMBOL_net_or_ipa = 617,               /* net_or_ipa  */
  YYSYMBOL_label_stack_start = 618,        /* label_stack_start  */
  YYSYMBOL_label_stack = 619,              /* label_stack  */
  YYSYMBOL_time = 620,                     /* time  */
  YYSYMBOL_text = 621,                     /* text  */
  YYSYMBOL_opttext = 622,                  /* opttext  */
  YYSYMBOL_flow_num_op = 623,              /* flow_num_op  */
  YYSYMBOL_flow_logic_op = 624,            /* flow_logic_op  */
  YYSYMBOL_flow_num_type_ = 625,           /* flow_num_type_  */
  YYSYMBOL_flow_num_type = 626,            /* flow_num_type  */
  YYSYMBOL_flow_flag_type = 627,           /* flow_flag_type  */
  YYSYMBOL_flow_frag_type = 628,           /* flow_frag_type  */
  YYSYMBOL_flow_srcdst = 629,              /* flow_srcdst  */
  YYSYMBOL_flow_num_opts = 630,            /* flow_num_opts  */
  YYSYMBOL_flow_num_opt_ext_expr = 631,    /* flow_num_opt_ext_expr  */
  YYSYMBOL_flow_num_opt_ext = 632,         /* flow_num_opt_ext  */
  YYSYMBOL_flow_bmk_opts = 633,            /* flow_bmk_opts  */
  YYSYMBOL_flow_neg = 634,                 /* flow_neg  */
  YYSYMBOL_flow_frag_val = 635,            /* flow_frag_val  */
  YYSYMBOL_flow_frag_opts = 636,           /* flow_frag_opts  */
  YYSYMBOL_flow4_item = 637,               /* flow4_item  */
  YYSYMBOL_flow6_item = 638,               /* flow6_item  */
  YYSYMBOL_flow4_opts = 639,               /* flow4_opts  */
  YYSYMBOL_flow6_opts = 640,               /* flow6_opts  */
  YYSYMBOL_flow_builder_init = 641,        /* flow_builder_init  */
  YYSYMBOL_flow_builder_set_ipv4 = 642,    /* flow_builder_set_ipv4  */
  YYSYMBOL_flow_builder_set_ipv6 = 643,    /* flow_builder_set_ipv6  */
  YYSYMBOL_net_flow4_ = 644,               /* net_flow4_  */
  YYSYMBOL_net_flow6_ = 645,               /* net_flow6_  */
  YYSYMBOL_net_flow_ = 646,                /* net_flow_  */
  YYSYMBOL_filter_def = 647,               /* filter_def  */
  YYSYMBOL_648_1 = 648,                    /* $@1  */
  YYSYMBOL_filter_eval = 649,              /* filter_eval  */
  YYSYMBOL_custom_attr = 650,              /* custom_attr  */
  YYSYMBOL_bt_test_suite = 651,            /* bt_test_suite  */
  YYSYMBOL_bt_test_same = 652,             /* bt_test_same  */
  YYSYMBOL_type = 653,                     /* type  */
  YYSYMBOL_function_argsn = 654,           /* function_argsn  */
  YYSYMBOL_function_args = 655,            /* function_args  */
  YYSYMBOL_function_vars = 656,            /* function_vars  */
  YYSYMBOL_filter_body = 657,              /* filter_body  */
  YYSYMBOL_filter = 658,                   /* filter  */
  YYSYMBOL_659_2 = 659,                    /* $@2  */
  YYSYMBOL_where_filter = 660,             /* where_filter  */
  YYSYMBOL_function_body = 661,            /* function_body  */
  YYSYMBOL_function_def = 662,             /* function_def  */
  YYSYMBOL_663_3 = 663,                    /* $@3  */
  YYSYMBOL_664_4 = 664,                    /* $@4  */
  YYSYMBOL_cmds = 665,                     /* cmds  */
  YYSYMBOL_cmds_scoped = 666,              /* cmds_scoped  */
  YYSYMBOL_667_5 = 667,                    /* $@5  */
  YYSYMBOL_cmd_var = 668,                  /* cmd_var  */
  YYSYMBOL_cmd_prep = 669,                 /* cmd_prep  */
  YYSYMBOL_cmds_int = 670,                 /* cmds_int  */
  YYSYMBOL_fipa = 671,                     /* fipa  */
  YYSYMBOL_set_atom = 672,                 /* set_atom  */
  YYSYMBOL_switch_atom = 673,              /* switch_atom  */
  YYSYMBOL_cnum = 674,                     /* cnum  */
  YYSYMBOL_pair_item = 675,                /* pair_item  */
  YYSYMBOL_ec_kind = 676,                  /* ec_kind  */
  YYSYMBOL_ec_item = 677,                  /* ec_item  */
  YYSYMBOL_lc_item = 678,                  /* lc_item  */
  YYSYMBOL_set_item = 679,                 /* set_item  */
  YYSYMBOL_switch_item = 680,              /* switch_item  */
  YYSYMBOL_set_items = 681,                /* set_items  */
  YYSYMBOL_switch_items = 682,             /* switch_items  */
  YYSYMBOL_fprefix = 683,                  /* fprefix  */
  YYSYMBOL_fprefix_set = 684,              /* fprefix_set  */
  YYSYMBOL_switch_body = 685,              /* switch_body  */
  YYSYMBOL_bgp_path_expr = 686,            /* bgp_path_expr  */
  YYSYMBOL_bgp_path = 687,                 /* bgp_path  */
  YYSYMBOL_bgp_path_tail = 688,            /* bgp_path_tail  */
  YYSYMBOL_constant = 689,                 /* constant  */
  YYSYMBOL_constructor = 690,              /* constructor  */
  YYSYMBOL_var_list = 691,                 /* var_list  */
  YYSYMBOL_function_call = 692,            /* function_call  */
  YYSYMBOL_symbol_value = 693,             /* symbol_value  */
  YYSYMBOL_static_attr = 694,              /* static_attr  */
  YYSYMBOL_term = 695,                     /* term  */
  YYSYMBOL_break_command = 696,            /* break_command  */
  YYSYMBOL_print_list = 697,               /* print_list  */
  YYSYMBOL_var_init = 698,                 /* var_init  */
  YYSYMBOL_var = 699,                      /* var  */
  YYSYMBOL_for_var = 700,                  /* for_var  */
  YYSYMBOL_cmd = 701,                      /* cmd  */
  YYSYMBOL_702_6 = 702,                    /* $@6  */
  YYSYMBOL_703_7 = 703,                    /* $@7  */
  YYSYMBOL_704_8 = 704,                    /* $@8  */
  YYSYMBOL_get_cf_position = 705,          /* get_cf_position  */
  YYSYMBOL_lvalue = 706,                   /* lvalue  */
  YYSYMBOL_rtrid = 707,                    /* rtrid  */
  YYSYMBOL_idval = 708,                    /* idval  */
  YYSYMBOL_hostname_override = 709,        /* hostname_override  */
  YYSYMBOL_gr_opts = 710,                  /* gr_opts  */
  YYSYMBOL_net_type = 711,                 /* net_type  */
  YYSYMBOL_table = 712,                    /* table  */
  YYSYMBOL_table_start = 713,              /* table_start  */
  YYSYMBOL_table_sorted = 714,             /* table_sorted  */
  YYSYMBOL_table_opt = 715,                /* table_opt  */
  YYSYMBOL_table_opts = 716,               /* table_opts  */
  YYSYMBOL_table_opt_list = 717,           /* table_opt_list  */
  YYSYMBOL_proto_start = 718,              /* proto_start  */
  YYSYMBOL_proto_name = 719,               /* proto_name  */
  YYSYMBOL_proto_item = 720,               /* proto_item  */
  YYSYMBOL_channel_start = 721,            /* channel_start  */
  YYSYMBOL_channel_item_ = 722,            /* channel_item_  */
  YYSYMBOL_channel_item = 723,             /* channel_item  */
  YYSYMBOL_channel_opts = 724,             /* channel_opts  */
  YYSYMBOL_channel_opt_list = 725,         /* channel_opt_list  */
  YYSYMBOL_channel_end = 726,              /* channel_end  */
  YYSYMBOL_proto_channel = 727,            /* proto_channel  */
  YYSYMBOL_rtable = 728,                   /* rtable  */
  YYSYMBOL_imexport = 729,                 /* imexport  */
  YYSYMBOL_limit_action = 730,             /* limit_action  */
  YYSYMBOL_limit_spec = 731,               /* limit_spec  */
  YYSYMBOL_debug_default = 732,            /* debug_default  */
  YYSYMBOL_timeformat_which = 733,         /* timeformat_which  */
  YYSYMBOL_timeformat_spec = 734,          /* timeformat_spec  */
  YYSYMBOL_timeformat_base = 735,          /* timeformat_base  */
  YYSYMBOL_iface_patt_node_init = 736,     /* iface_patt_node_init  */
  YYSYMBOL_iface_patt_node_body = 737,     /* iface_patt_node_body  */
  YYSYMBOL_iface_negate = 738,             /* iface_negate  */
  YYSYMBOL_iface_patt_node = 739,          /* iface_patt_node  */
  YYSYMBOL_iface_patt_list = 740,          /* iface_patt_list  */
  YYSYMBOL_iface_patt_list_nopx = 741,     /* iface_patt_list_nopx  */
  YYSYMBOL_iface_patt_init = 742,          /* iface_patt_init  */
  YYSYMBOL_iface_patt = 743,               /* iface_patt  */
  YYSYMBOL_tos = 744,                      /* tos  */
  YYSYMBOL_proto = 745,                    /* proto  */
  YYSYMBOL_dev_proto_start = 746,          /* dev_proto_start  */
  YYSYMBOL_dev_proto = 747,                /* dev_proto  */
  YYSYMBOL_dev_iface_init = 748,           /* dev_iface_init  */
  YYSYMBOL_dev_iface_patt = 749,           /* dev_iface_patt  */
  YYSYMBOL_debug_mask = 750,               /* debug_mask  */
  YYSYMBOL_debug_list = 751,               /* debug_list  */
  YYSYMBOL_debug_flag = 752,               /* debug_flag  */
  YYSYMBOL_mrtdump_mask = 753,             /* mrtdump_mask  */
  YYSYMBOL_mrtdump_list = 754,             /* mrtdump_list  */
  YYSYMBOL_mrtdump_flag = 755,             /* mrtdump_flag  */
  YYSYMBOL_password_list = 756,            /* password_list  */
  YYSYMBOL_password_list_body = 757,       /* password_list_body  */
  YYSYMBOL_password_items = 758,           /* password_items  */
  YYSYMBOL_password_item = 759,            /* password_item  */
  YYSYMBOL_pass_key = 760,                 /* pass_key  */
  YYSYMBOL_password_item_begin = 761,      /* password_item_begin  */
  YYSYMBOL_password_item_params = 762,     /* password_item_params  */
  YYSYMBOL_password_algorithm = 763,       /* password_algorithm  */
  YYSYMBOL_password_item_end = 764,        /* password_item_end  */
  YYSYMBOL_bfd_item = 765,                 /* bfd_item  */
  YYSYMBOL_bfd_items = 766,                /* bfd_items  */
  YYSYMBOL_bfd_opts = 767,                 /* bfd_opts  */
  YYSYMBOL_cmd_SHOW_STATUS = 768,          /* cmd_SHOW_STATUS  */
  YYSYMBOL_cmd_CALL_AGENT = 769,           /* cmd_CALL_AGENT  */
  YYSYMBOL_cmd_TEST_LOG = 770,             /* cmd_TEST_LOG  */
  YYSYMBOL_cmd_TEST_SEND = 771,            /* cmd_TEST_SEND  */
  YYSYMBOL_cmd_SHOW_MEMORY = 772,          /* cmd_SHOW_MEMORY  */
  YYSYMBOL_cmd_SHOW_PROTOCOLS = 773,       /* cmd_SHOW_PROTOCOLS  */
  YYSYMBOL_cmd_SHOW_PROTOCOLS_ALL = 774,   /* cmd_SHOW_PROTOCOLS_ALL  */
  YYSYMBOL_optproto = 775,                 /* optproto  */
  YYSYMBOL_cmd_SHOW_INTERFACES = 776,      /* cmd_SHOW_INTERFACES  */
  YYSYMBOL_cmd_SHOW_INTERFACES_SUMMARY = 777, /* cmd_SHOW_INTERFACES_SUMMARY  */
  YYSYMBOL_cmd_SHOW_ROUTE = 778,           /* cmd_SHOW_ROUTE  */
  YYSYMBOL_r_args = 779,                   /* r_args  */
  YYSYMBOL_r_args_for = 780,               /* r_args_for  */
  YYSYMBOL_r_args_for_val = 781,           /* r_args_for_val  */
  YYSYMBOL_export_mode = 782,              /* export_mode  */
  YYSYMBOL_channel_sym = 783,              /* channel_sym  */
  YYSYMBOL_channel_arg = 784,              /* channel_arg  */
  YYSYMBOL_cmd_SHOW_SYMBOLS = 785,         /* cmd_SHOW_SYMBOLS  */
  YYSYMBOL_sym_args = 786,                 /* sym_args  */
  YYSYMBOL_cmd_DUMP_RESOURCES = 787,       /* cmd_DUMP_RESOURCES  */
  YYSYMBOL_cmd_DUMP_SOCKETS = 788,         /* cmd_DUMP_SOCKETS  */
  YYSYMBOL_cmd_DUMP_EVENTS = 789,          /* cmd_DUMP_EVENTS  */
  YYSYMBOL_cmd_DUMP_INTERFACES = 790,      /* cmd_DUMP_INTERFACES  */
  YYSYMBOL_cmd_DUMP_NEIGHBORS = 791,       /* cmd_DUMP_NEIGHBORS  */
  YYSYMBOL_cmd_DUMP_ATTRIBUTES = 792,      /* cmd_DUMP_ATTRIBUTES  */
  YYSYMBOL_cmd_DUMP_ROUTES = 793,          /* cmd_DUMP_ROUTES  */
  YYSYMBOL_cmd_DUMP_PROTOCOLS = 794,       /* cmd_DUMP_PROTOCOLS  */
  YYSYMBOL_cmd_DUMP_FILTER_ALL = 795,      /* cmd_DUMP_FILTER_ALL  */
  YYSYMBOL_cmd_EVAL = 796,                 /* cmd_EVAL  */
  YYSYMBOL_cmd_ECHO = 797,                 /* cmd_ECHO  */
  YYSYMBOL_echo_mask = 798,                /* echo_mask  */
  YYSYMBOL_echo_size = 799,                /* echo_size  */
  YYSYMBOL_cmd_DISABLE = 800,              /* cmd_DISABLE  */
  YYSYMBOL_cmd_ENABLE = 801,               /* cmd_ENABLE  */
  YYSYMBOL_cmd_RESTART = 802,              /* cmd_RESTART  */
  YYSYMBOL_cmd_RELOAD = 803,               /* cmd_RELOAD  */
  YYSYMBOL_cmd_RELOAD_IN = 804,            /* cmd_RELOAD_IN  */
  YYSYMBOL_cmd_RELOAD_OUT = 805,           /* cmd_RELOAD_OUT  */
  YYSYMBOL_cmd_DEBUG = 806,                /* cmd_DEBUG  */
  YYSYMBOL_debug_args = 807,               /* debug_args  */
  YYSYMBOL_cmd_MRTDUMP = 808,              /* cmd_MRTDUMP  */
  YYSYMBOL_cmd_RESTRICT = 809,             /* cmd_RESTRICT  */
  YYSYMBOL_proto_patt = 810,               /* proto_patt  */
  YYSYMBOL_proto_patt2 = 811,              /* proto_patt2  */
  YYSYMBOL_dynamic_attr = 812,             /* dynamic_attr  */
  YYSYMBOL_babel_proto_start = 813,        /* babel_proto_start  */
  YYSYMBOL_babel_proto_item = 814,         /* babel_proto_item  */
  YYSYMBOL_babel_proto_opts = 815,         /* babel_proto_opts  */
  YYSYMBOL_babel_proto = 816,              /* babel_proto  */
  YYSYMBOL_babel_iface_start = 817,        /* babel_iface_start  */
  YYSYMBOL_babel_iface_finish = 818,       /* babel_iface_finish  */
  YYSYMBOL_babel_iface_item = 819,         /* babel_iface_item  */
  YYSYMBOL_babel_iface_opts = 820,         /* babel_iface_opts  */
  YYSYMBOL_babel_iface_opt_list = 821,     /* babel_iface_opt_list  */
  YYSYMBOL_babel_iface = 822,              /* babel_iface  */
  YYSYMBOL_cmd_SHOW_BABEL_INTERFACES = 823, /* cmd_SHOW_BABEL_INTERFACES  */
  YYSYMBOL_cmd_SHOW_BABEL_NEIGHBORS = 824, /* cmd_SHOW_BABEL_NEIGHBORS  */
  YYSYMBOL_cmd_SHOW_BABEL_ENTRIES = 825,   /* cmd_SHOW_BABEL_ENTRIES  */
  YYSYMBOL_cmd_SHOW_BABEL_ROUTES = 826,    /* cmd_SHOW_BABEL_ROUTES  */
  YYSYMBOL_bfd_proto_start = 827,          /* bfd_proto_start  */
  YYSYMBOL_bfd_proto_item = 828,           /* bfd_proto_item  */
  YYSYMBOL_bfd_proto_opts = 829,           /* bfd_proto_opts  */
  YYSYMBOL_bfd_proto = 830,                /* bfd_proto  */
  YYSYMBOL_bfd_accept_item = 831,          /* bfd_accept_item  */
  YYSYMBOL_bfd_accept = 832,               /* bfd_accept  */
  YYSYMBOL_bfd_iface_start = 833,          /* bfd_iface_start  */
  YYSYMBOL_bfd_iface_finish = 834,         /* bfd_iface_finish  */
  YYSYMBOL_bfd_iface_item = 835,           /* bfd_iface_item  */
  YYSYMBOL_bfd_auth_type = 836,            /* bfd_auth_type  */
  YYSYMBOL_bfd_iface_opts = 837,           /* bfd_iface_opts  */
  YYSYMBOL_bfd_iface_opt_list = 838,       /* bfd_iface_opt_list  */
  YYSYMBOL_bfd_iface = 839,                /* bfd_iface  */
  YYSYMBOL_bfd_multihop = 840,             /* bfd_multihop  */
  YYSYMBOL_bfd_neigh_iface = 841,          /* bfd_neigh_iface  */
  YYSYMBOL_bfd_neigh_local = 842,          /* bfd_neigh_local  */
  YYSYMBOL_bfd_neigh_multihop = 843,       /* bfd_neigh_multihop  */
  YYSYMBOL_bfd_neighbor = 844,             /* bfd_neighbor  */
  YYSYMBOL_cmd_SHOW_BFD_SESSIONS = 845,    /* cmd_SHOW_BFD_SESSIONS  */
  YYSYMBOL_bgp_proto_start = 846,          /* bgp_proto_start  */
  YYSYMBOL_bgp_loc_opts = 847,             /* bgp_loc_opts  */
  YYSYMBOL_bgp_nbr_opts = 848,             /* bgp_nbr_opts  */
  YYSYMBOL_bgp_cease_mask = 849,           /* bgp_cease_mask  */
  YYSYMBOL_bgp_cease_list = 850,           /* bgp_cease_list  */
  YYSYMBOL_bgp_cease_flag = 851,           /* bgp_cease_flag  */
  YYSYMBOL_bgp_role_name = 852,            /* bgp_role_name  */
  YYSYMBOL_bgp_proto = 853,                /* bgp_proto  */
  YYSYMBOL_854_9 = 854,                    /* $@9  */
  YYSYMBOL_855_10 = 855,                   /* $@10  */
  YYSYMBOL_bgp_afi = 856,                  /* bgp_afi  */
  YYSYMBOL_bgp_channel_start = 857,        /* bgp_channel_start  */
  YYSYMBOL_bgp_nh = 858,                   /* bgp_nh  */
  YYSYMBOL_bgp_lladdr = 859,               /* bgp_lladdr  */
  YYSYMBOL_bgp_channel_item = 860,         /* bgp_channel_item  */
  YYSYMBOL_bgp_channel_opts = 861,         /* bgp_channel_opts  */
  YYSYMBOL_bgp_channel_opt_list = 862,     /* bgp_channel_opt_list  */
  YYSYMBOL_bgp_channel_end = 863,          /* bgp_channel_end  */
  YYSYMBOL_bgp_proto_channel = 864,        /* bgp_proto_channel  */
  YYSYMBOL_mrt_proto_start = 865,          /* mrt_proto_start  */
  YYSYMBOL_mrt_proto_item = 866,           /* mrt_proto_item  */
  YYSYMBOL_mrt_proto_opts = 867,           /* mrt_proto_opts  */
  YYSYMBOL_mrt_proto = 868,                /* mrt_proto  */
  YYSYMBOL_cmd_MRT_DUMP = 869,             /* cmd_MRT_DUMP  */
  YYSYMBOL_mrt_dump_args = 870,            /* mrt_dump_args  */
  YYSYMBOL_ospf_variant = 871,             /* ospf_variant  */
  YYSYMBOL_ospf_proto_start = 872,         /* ospf_proto_start  */
  YYSYMBOL_ospf_proto = 873,               /* ospf_proto  */
  YYSYMBOL_ospf_af_mc = 874,               /* ospf_af_mc  */
  YYSYMBOL_ospf_channel_start = 875,       /* ospf_channel_start  */
  YYSYMBOL_ospf_channel = 876,             /* ospf_channel  */
  YYSYMBOL_ospf_proto_item = 877,          /* ospf_proto_item  */
  YYSYMBOL_ospf_area_start = 878,          /* ospf_area_start  */
  YYSYMBOL_ospf_area = 879,                /* ospf_area  */
  YYSYMBOL_ospf_area_opts = 880,           /* ospf_area_opts  */
  YYSYMBOL_ospf_area_item = 881,           /* ospf_area_item  */
  YYSYMBOL_882_11 = 882,                   /* $@11  */
  YYSYMBOL_883_12 = 883,                   /* $@12  */
  YYSYMBOL_ospf_stubnet = 884,             /* ospf_stubnet  */
  YYSYMBOL_ospf_stubnet_start = 885,       /* ospf_stubnet_start  */
  YYSYMBOL_ospf_stubnet_opts = 886,        /* ospf_stubnet_opts  */
  YYSYMBOL_ospf_stubnet_item = 887,        /* ospf_stubnet_item  */
  YYSYMBOL_ospf_vlink = 888,               /* ospf_vlink  */
  YYSYMBOL_ospf_vlink_opts = 889,          /* ospf_vlink_opts  */
  YYSYMBOL_ospf_vlink_item = 890,          /* ospf_vlink_item  */
  YYSYMBOL_ospf_vlink_start = 891,         /* ospf_vlink_start  */
  YYSYMBOL_ospf_iface_item = 892,          /* ospf_iface_item  */
  YYSYMBOL_pref_list = 893,                /* pref_list  */
  YYSYMBOL_pref_item = 894,                /* pref_item  */
  YYSYMBOL_pref_base = 895,                /* pref_base  */
  YYSYMBOL_pref_opt = 896,                 /* pref_opt  */
  YYSYMBOL_nbma_list = 897,                /* nbma_list  */
  YYSYMBOL_nbma_eligible = 898,            /* nbma_eligible  */
  YYSYMBOL_nbma_item = 899,                /* nbma_item  */
  YYSYMBOL_ospf_iface_start = 900,         /* ospf_iface_start  */
  YYSYMBOL_ospf_instance_id = 901,         /* ospf_instance_id  */
  YYSYMBOL_ospf_iface_patt_list = 902,     /* ospf_iface_patt_list  */
  YYSYMBOL_903_13 = 903,                   /* $@13  */
  YYSYMBOL_ospf_iface_opts = 904,          /* ospf_iface_opts  */
  YYSYMBOL_ospf_iface_opt_list = 905,      /* ospf_iface_opt_list  */
  YYSYMBOL_ospf_iface = 906,               /* ospf_iface  */
  YYSYMBOL_cmd_SHOW_OSPF = 907,            /* cmd_SHOW_OSPF  */
  YYSYMBOL_cmd_SHOW_OSPF_NEIGHBORS = 908,  /* cmd_SHOW_OSPF_NEIGHBORS  */
  YYSYMBOL_cmd_SHOW_OSPF_INTERFACE = 909,  /* cmd_SHOW_OSPF_INTERFACE  */
  YYSYMBOL_cmd_SHOW_OSPF_TOPOLOGY = 910,   /* cmd_SHOW_OSPF_TOPOLOGY  */
  YYSYMBOL_cmd_SHOW_OSPF_TOPOLOGY_ALL = 911, /* cmd_SHOW_OSPF_TOPOLOGY_ALL  */
  YYSYMBOL_cmd_SHOW_OSPF_STATE = 912,      /* cmd_SHOW_OSPF_STATE  */
  YYSYMBOL_cmd_SHOW_OSPF_STATE_ALL = 913,  /* cmd_SHOW_OSPF_STATE_ALL  */
  YYSYMBOL_cmd_SHOW_OSPF_LSADB = 914,      /* cmd_SHOW_OSPF_LSADB  */
  YYSYMBOL_lsadb_args = 915,               /* lsadb_args  */
  YYSYMBOL_perf_proto_start = 916,         /* perf_proto_start  */
  YYSYMBOL_perf_proto = 917,               /* perf_proto  */
  YYSYMBOL_perf_proto_item = 918,          /* perf_proto_item  */
  YYSYMBOL_pipe_proto_start = 919,         /* pipe_proto_start  */
  YYSYMBOL_920_14 = 920,                   /* $@14  */
  YYSYMBOL_pipe_proto = 921,               /* pipe_proto  */
  YYSYMBOL_radv_proto_start = 922,         /* radv_proto_start  */
  YYSYMBOL_radv_proto_item = 923,          /* radv_proto_item  */
  YYSYMBOL_924_15 = 924,                   /* $@15  */
  YYSYMBOL_925_16 = 925,                   /* $@16  */
  YYSYMBOL_radv_proto_opts = 926,          /* radv_proto_opts  */
  YYSYMBOL_radv_proto = 927,               /* radv_proto  */
  YYSYMBOL_radv_iface_start = 928,         /* radv_iface_start  */
  YYSYMBOL_radv_iface_item = 929,          /* radv_iface_item  */
  YYSYMBOL_930_17 = 930,                   /* $@17  */
  YYSYMBOL_931_18 = 931,                   /* $@18  */
  YYSYMBOL_radv_preference = 932,          /* radv_preference  */
  YYSYMBOL_radv_iface_finish = 933,        /* radv_iface_finish  */
  YYSYMBOL_radv_iface_opts = 934,          /* radv_iface_opts  */
  YYSYMBOL_radv_iface_opt_list = 935,      /* radv_iface_opt_list  */
  YYSYMBOL_radv_iface = 936,               /* radv_iface  */
  YYSYMBOL_radv_prefix_start = 937,        /* radv_prefix_start  */
  YYSYMBOL_radv_prefix_item = 938,         /* radv_prefix_item  */
  YYSYMBOL_radv_prefix_finish = 939,       /* radv_prefix_finish  */
  YYSYMBOL_radv_prefix_opts = 940,         /* radv_prefix_opts  */
  YYSYMBOL_radv_prefix_opt_list = 941,     /* radv_prefix_opt_list  */
  YYSYMBOL_radv_prefix = 942,              /* radv_prefix  */
  YYSYMBOL_radv_rdnss_node = 943,          /* radv_rdnss_node  */
  YYSYMBOL_radv_rdnss_start = 944,         /* radv_rdnss_start  */
  YYSYMBOL_radv_rdnss_item = 945,          /* radv_rdnss_item  */
  YYSYMBOL_radv_rdnss_finish = 946,        /* radv_rdnss_finish  */
  YYSYMBOL_radv_rdnss_opts = 947,          /* radv_rdnss_opts  */
  YYSYMBOL_radv_rdnss = 948,               /* radv_rdnss  */
  YYSYMBOL_radv_dnssl_node = 949,          /* radv_dnssl_node  */
  YYSYMBOL_radv_dnssl_start = 950,         /* radv_dnssl_start  */
  YYSYMBOL_radv_dnssl_item = 951,          /* radv_dnssl_item  */
  YYSYMBOL_radv_dnssl_finish = 952,        /* radv_dnssl_finish  */
  YYSYMBOL_radv_dnssl_opts = 953,          /* radv_dnssl_opts  */
  YYSYMBOL_radv_dnssl = 954,               /* radv_dnssl  */
  YYSYMBOL_radv_mult = 955,                /* radv_mult  */
  YYSYMBOL_radv_sensitive = 956,           /* radv_sensitive  */
  YYSYMBOL_rip_variant = 957,              /* rip_variant  */
  YYSYMBOL_rip_proto_start = 958,          /* rip_proto_start  */
  YYSYMBOL_rip_proto_item = 959,           /* rip_proto_item  */
  YYSYMBOL_rip_proto_opts = 960,           /* rip_proto_opts  */
  YYSYMBOL_rip_proto = 961,                /* rip_proto  */
  YYSYMBOL_rip_iface_start = 962,          /* rip_iface_start  */
  YYSYMBOL_rip_iface_finish = 963,         /* rip_iface_finish  */
  YYSYMBOL_rip_iface_item = 964,           /* rip_iface_item  */
  YYSYMBOL_rip_auth = 965,                 /* rip_auth  */
  YYSYMBOL_rip_iface_opts = 966,           /* rip_iface_opts  */
  YYSYMBOL_rip_iface_opt_list = 967,       /* rip_iface_opt_list  */
  YYSYMBOL_rip_iface = 968,                /* rip_iface  */
  YYSYMBOL_cmd_SHOW_RIP_INTERFACES = 969,  /* cmd_SHOW_RIP_INTERFACES  */
  YYSYMBOL_cmd_SHOW_RIP_NEIGHBORS = 970,   /* cmd_SHOW_RIP_NEIGHBORS  */
  YYSYMBOL_rpki_proto_start = 971,         /* rpki_proto_start  */
  YYSYMBOL_rpki_proto = 972,               /* rpki_proto  */
  YYSYMBOL_rpki_proto_opts = 973,          /* rpki_proto_opts  */
  YYSYMBOL_rpki_proto_item = 974,          /* rpki_proto_item  */
  YYSYMBOL_rpki_keep_interval = 975,       /* rpki_keep_interval  */
  YYSYMBOL_rpki_proto_item_port = 976,     /* rpki_proto_item_port  */
  YYSYMBOL_rpki_cache_addr = 977,          /* rpki_cache_addr  */
  YYSYMBOL_rpki_transport = 978,           /* rpki_transport  */
  YYSYMBOL_rpki_transport_tcp_init = 979,  /* rpki_transport_tcp_init  */
  YYSYMBOL_rpki_transport_ssh_init = 980,  /* rpki_transport_ssh_init  */
  YYSYMBOL_rpki_transport_ssh_opts = 981,  /* rpki_transport_ssh_opts  */
  YYSYMBOL_rpki_transport_ssh_item = 982,  /* rpki_transport_ssh_item  */
  YYSYMBOL_rpki_transport_ssh_check = 983, /* rpki_transport_ssh_check  */
  YYSYMBOL_static_proto_start = 984,       /* static_proto_start  */
  YYSYMBOL_static_proto = 985,             /* static_proto  */
  YYSYMBOL_stat_nexthop = 986,             /* stat_nexthop  */
  YYSYMBOL_stat_nexthops = 987,            /* stat_nexthops  */
  YYSYMBOL_stat_route0 = 988,              /* stat_route0  */
  YYSYMBOL_stat_route = 989,               /* stat_route  */
  YYSYMBOL_stat_route_item = 990,          /* stat_route_item  */
  YYSYMBOL_stat_route_opts = 991,          /* stat_route_opts  */
  YYSYMBOL_stat_route_opt_list = 992,      /* stat_route_opt_list  */
  YYSYMBOL_cmd_SHOW_STATIC = 993,          /* cmd_SHOW_STATIC  */
  YYSYMBOL_kern_proto = 994,               /* kern_proto  */
  YYSYMBOL_kern_sys_item = 995,            /* kern_sys_item  */
  YYSYMBOL_log_begin = 996,                /* log_begin  */
  YYSYMBOL_log_config = 997,               /* log_config  */
  YYSYMBOL_syslog_name = 998,              /* syslog_name  */
  YYSYMBOL_log_limit = 999,                /* log_limit  */
  YYSYMBOL_log_file = 1000,                /* log_file  */
  YYSYMBOL_log_mask = 1001,                /* log_mask  */
  YYSYMBOL_log_mask_list = 1002,           /* log_mask_list  */
  YYSYMBOL_log_cat = 1003,                 /* log_cat  */
  YYSYMBOL_mrtdump_base = 1004,            /* mrtdump_base  */
  YYSYMBOL_debug_unix = 1005,              /* debug_unix  */
  YYSYMBOL_cmd_CONFIGURE = 1006,           /* cmd_CONFIGURE  */
  YYSYMBOL_cmd_CONFIGURE_SOFT = 1007,      /* cmd_CONFIGURE_SOFT  */
  YYSYMBOL_cmd_CONFIGURE_CONFIRM = 1008,   /* cmd_CONFIGURE_CONFIRM  */
  YYSYMBOL_cmd_CONFIGURE_UNDO = 1009,      /* cmd_CONFIGURE_UNDO  */
  YYSYMBOL_cmd_CONFIGURE_STATUS = 1010,    /* cmd_CONFIGURE_STATUS  */
  YYSYMBOL_cmd_CONFIGURE_CHECK = 1011,     /* cmd_CONFIGURE_CHECK  */
  YYSYMBOL_cmd_DOWN = 1012,                /* cmd_DOWN  */
  YYSYMBOL_cmd_GRACEFUL_RESTART = 1013,    /* cmd_GRACEFUL_RESTART  */
  YYSYMBOL_cfg_name = 1014,                /* cfg_name  */
  YYSYMBOL_cfg_timeout = 1015,             /* cfg_timeout  */
  YYSYMBOL_kern_proto_start = 1016,        /* kern_proto_start  */
  YYSYMBOL_kern_mp_limit = 1017,           /* kern_mp_limit  */
  YYSYMBOL_kern_item = 1018,               /* kern_item  */
  YYSYMBOL_kif_proto_start = 1019,         /* kif_proto_start  */
  YYSYMBOL_kif_proto = 1020,               /* kif_proto  */
  YYSYMBOL_kif_item = 1021,                /* kif_item  */
  YYSYMBOL_kif_iface_start = 1022,         /* kif_iface_start  */
  YYSYMBOL_kif_iface_item = 1023,          /* kif_iface_item  */
  YYSYMBOL_kif_iface_opts = 1024,          /* kif_iface_opts  */
  YYSYMBOL_kif_iface_opt_list = 1025,      /* kif_iface_opt_list  */
  YYSYMBOL_kif_iface = 1026                /* kif_iface  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  85
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7003

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  585
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  442
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1491
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2735

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   818


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,     2,     2,    37,     2,     2,
      53,    54,    35,    33,    78,    34,    39,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   160,    52,
      29,    28,    30,   163,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   161,     2,   162,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,     2,    80,    31,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    32,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     516,   517,   518,   519,   520,   521,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   572,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,   584
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   137,   137,   138,   141,   143,   146,   151,   154,   162,
     163,   164,   170,   171,   172,   175,   175,   180,   181,   182,
     183,   184,   185,   192,   193,   194,   201,   202,   209,   215,
     225,   238,   257,   263,   269,   277,   285,   291,   291,   292,
     292,   293,   293,   296,   297,   298,   299,   300,   301,   308,
     309,   317,   318,   326,   327,   335,   336,   344,   345,   346,
     347,   348,   358,   366,   367,   376,   384,   385,   392,   393,
      37,    38,    39,    40,    41,    42,    43,    44,    48,    49,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      65,    66,    67,    70,    71,    75,    79,    83,    84,    88,
      92,   101,   102,   106,   110,   114,   121,   122,   126,   127,
     128,   129,   133,   136,   139,   145,   149,   150,   151,   155,
     159,   165,   166,   167,   170,   172,   175,   177,   181,   188,
     189,   191,   197,   203,   203,     9,     9,    10,    10,    11,
      11,   346,   348,   348,   358,   360,   363,   364,   368,   370,
     381,   383,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   435,   436,
     445,   446,   454,   455,   461,   464,   468,   468,   478,   485,
     491,   493,   497,   493,   521,   522,   525,   525,   527,   527,
     529,   537,   538,   555,   556,   569,   570,   571,   572,   573,
     577,   585,   586,   587,   588,   592,   595,   596,   597,   598,
     599,   600,   601,   602,   603,   604,   609,   610,   611,   612,
     616,   617,   618,   622,   623,   624,   625,   626,   627,   628,
     629,   634,   635,   636,   637,   638,   642,   643,   644,   645,
     646,   650,   651,   655,   656,   660,   661,   662,   663,   671,
     672,   675,   676,   684,   694,   695,   699,   703,   704,   705,
     706,   710,   711,   712,   713,   714,   718,   719,   720,   721,
     722,   723,   724,   725,   726,   731,   732,   736,   737,   738,
     739,   744,   745,   746,   749,   768,   787,   788,   789,   790,
     791,   792,   793,   794,   795,   796,   797,   798,   802,   803,
     804,   805,   806,   807,   808,   809,   810,   811,   812,   813,
     814,   815,   816,   817,   818,   820,   821,   822,   824,   826,
     828,   829,   830,   831,   832,   833,   834,   835,   836,   837,
     838,   839,   840,   841,   842,   843,   844,   845,   855,   856,
     857,   858,   859,   860,   861,   862,   864,   865,   867,   871,
     875,   876,   877,   880,   881,   882,   891,   892,   896,   902,
     903,   907,   910,   913,   916,   922,   922,   916,   928,   940,
     944,   947,   952,   955,   966,   970,   973,   974,   978,   979,
     980,   981,   982,   983,   984,   988,   993,   994,   995,   159,
     162,   163,   167,   168,   169,   170,   180,   182,   184,   186,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     209,   211,   213,   218,   220,   224,   225,   230,   231,   232,
     233,   236,   238,   241,   243,   249,   252,   253,   257,   263,
     267,   277,   287,   289,   290,   291,   292,   293,   294,   295,
     299,   305,   310,   311,   312,   313,   314,   315,   316,   317,
     322,   323,   326,   328,   331,   333,   337,   344,   347,   350,
     351,   352,   353,   357,   358,   359,   360,   361,   365,   366,
     370,   373,   374,   375,   380,   383,   384,   385,   386,   390,
     391,   392,   393,   394,   395,   396,   397,   401,   408,   416,
     417,   421,   422,   426,   431,   432,   436,   438,   446,   450,
     451,   456,   458,   465,   466,   467,   468,   469,   473,   481,
     487,   488,   489,   493,   494,   498,   499,   500,   501,   502,
     503,   509,   510,   511,   515,   516,   520,   521,   527,   531,
     532,   535,   537,   541,   542,   545,   545,   548,   549,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   582,   590,   591,   592,   593,   594,   595,   596,
     599,   601,   605,   611,   611,   613,   613,   616,   616,   619,
     619,   622,   622,   625,   625,   628,   628,   632,   633,   636,
     636,   639,   639,   643,   643,   647,   653,   659,   665,   672,
     678,   685,   690,   695,   700,   705,   709,   713,   717,   727,
     734,   743,   747,   754,   758,   759,   760,   761,   765,   769,
     773,   787,   788,   789,   790,   793,   794,   795,   796,   801,
     802,   803,   804,   805,   806,   807,   808,   809,   810,   811,
     812,   813,   814,   815,   816,   817,   818,   819,   820,   824,
     834,   834,   838,   841,   842,   843,   844,   845,   846,   851,
     851,   853,   853,   855,   855,   857,   857,   859,   859,   861,
     861,   863,   863,   865,   865,   867,   867,   870,   870,   874,
     874,   880,   881,   882,   886,   887,   893,   893,   895,   895,
     897,   897,   899,   899,   901,   901,   903,   903,   907,   907,
     911,   912,   916,   916,   919,   919,   923,   924,   925,   929,
     930,   931,   934,    35,    37,    47,    48,    49,    50,    51,
      52,    55,    57,    61,    65,    66,    67,    68,    72,    76,
      80,    94,   114,   115,   116,   117,   118,   119,   120,   121,
     125,   126,   127,   128,   129,   130,   133,   135,   138,   140,
     144,   147,   152,   153,   154,   158,   159,   163,   164,   167,
     186,   186,    32,    34,    42,    43,    44,    45,    48,    50,
      54,    58,    74,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   152,   154,   157,   159,   164,   166,   170,   170,
     173,   173,   176,   176,   179,   179,    48,    50,    82,    84,
      85,    88,    90,    91,    92,    93,    98,    99,   103,   104,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   120,
     121,   122,   123,   124,   128,   129,   130,   131,   132,   136,
     137,   143,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   210,
     210,   211,   212,   213,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   233,   259,
     260,   261,   263,   263,   263,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   304,
     316,   318,   321,   323,   327,   334,   337,   339,   341,   343,
     345,   347,   349,   351,   353,   355,   357,   359,   361,   363,
      26,    28,    34,    35,    36,    37,    38,    39,    40,    41,
      44,    46,    50,    53,    53,    57,    58,    59,    60,    61,
      62,   211,   214,   215,   216,   219,   235,   236,   240,   241,
     245,   254,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   274,   289,   292,
     294,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   307,   308,   308,   309,   310,   311,   315,   316,   320,
     328,   330,   334,   335,   336,   340,   341,   344,   346,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     362,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     422,   424,   427,   429,   437,   439,   440,   443,   445,   449,
     450,   453,   463,   485,   487,   491,   491,   494,   496,   499,
     501,   505,   508,   509,   510,   511,   514,   514,   517,   517,
     520,   520,   525,   525,   528,   528,   533,   533,   536,   536,
     540,   540,   549,   552,   553,   554,   555,   556,   557,   558,
     559,    24,    26,    40,    41,    42,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    23,    26,    25,    40,
      41,    42,    43,    44,    46,    58,    59,    60,    61,    62,
      62,    63,    63,    64,    65,    68,    70,    74,    78,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     116,   120,   121,   122,   123,   124,   125,   125,   126,   126,
     127,   128,   132,   133,   134,   137,   175,   177,   180,   182,
     186,   189,   201,   202,   203,   204,   208,   215,   223,   225,
     228,   230,   234,   238,   248,   253,   254,   255,   259,   271,
     273,   277,   278,   282,   295,   300,   301,   302,   306,   318,
     320,   324,   325,   330,   331,   335,   336,   339,   340,    46,
      49,    50,    53,    67,    68,    69,    70,    71,    72,    75,
      77,    81,    85,   110,   140,   141,   142,   143,   144,   145,
     146,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   173,   174,   175,   176,   179,   181,   184,   186,   190,
     193,   194,   198,   198,   201,   201,    41,    43,    50,    52,
      54,    58,    59,    60,    61,    62,    63,    64,    70,    76,
      82,    86,    87,    90,    93,    97,   108,   109,   113,   120,
     130,   132,   136,   137,   138,   142,    54,    56,    63,    64,
      65,    66,    67,    75,    79,    84,    89,    92,    95,    99,
     105,   106,   109,   121,   122,   126,   131,   132,   133,   134,
     135,   136,   140,   149,   151,   154,   156,   160,   160,    23,
      26,    27,    28,    31,    32,    33,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    62,
      63,    31,    33,    35,    42,    43,    46,    48,    52,    62,
      63,    67,    68,    72,    73,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    89,    92,    93,   104,   107,   108,
     109,   110,   118,   118,   121,   121,   128,   128,   131,   131,
     134,   134,   137,   137,   140,   140,   145,   145,   150,   151,
     155,   156,   157,    41,    43,    48,    49,    52,    53,    57,
      58,    59,    60,    64,    71,    72,    83,    85,    88,    89,
      92,    93,    94,   101,   108,   111,   113,   116,   118,   122,
     125,   126
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "QUIT", "EXIT", "HELP",
  "END", "CLI_MARKER", "INVALID_TOKEN", "ELSECOL", "DDOT", "GEQ", "LEQ",
  "NEQ", "AND", "OR", "PO", "PC", "NUM", "ENUM", "IP4", "IP6", "VPN_RD",
  "CF_SYM_KNOWN", "CF_SYM_UNDEFINED", "TEXT", "BYTESTRING", "PREFIX_DUMMY",
  "'='", "'<'", "'>'", "'~'", "NMA", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'!'", "'.'", "DEFINE", "ON", "OFF", "YES", "NO", "S", "MS", "US",
  "PORT", "VPN", "MPLS", "FROM", "';'", "'('", "')'", "FLOW4", "FLOW6",
  "DST", "SRC", "PROTO", "NEXT", "HEADER", "DPORT", "SPORT", "ICMP",
  "TYPE", "CODE", "TCP", "FLAGS", "LENGTH", "DSCP", "DONT_FRAGMENT",
  "IS_FRAGMENT", "FIRST_FRAGMENT", "LAST_FRAGMENT", "FRAGMENT", "LABEL",
  "OFFSET", "','", "'{'", "'}'", "FUNCTION", "PRINT", "PRINTN", "UNSET",
  "RETURN", "ACCEPT", "REJECT", "ERROR", "INT", "BOOL", "IP", "PREFIX",
  "RD", "PAIR", "QUAD", "EC", "LC", "SET", "STRING", "BGPMASK", "BGPPATH",
  "CLIST", "ECLIST", "LCLIST", "IF", "THEN", "ELSE", "CASE", "FOR", "IN",
  "DO", "TRUE", "FALSE", "RT", "RO", "UNKNOWN", "GENERIC", "GW", "NET",
  "MASK", "SOURCE", "SCOPE", "DEST", "IFNAME", "IFINDEX", "WEIGHT",
  "GW_MPLS", "PREFERENCE", "ROA_CHECK", "ASN", "IS_V4", "IS_V6", "LEN",
  "MAXLEN", "DATA", "DATA1", "DATA2", "DEFINED", "ADD", "DELETE",
  "CONTAINS", "RESET", "PREPEND", "FIRST", "LAST", "LAST_NONAGGREGATED",
  "MATCH", "MIN", "MAX", "EMPTY", "FILTER", "WHERE", "EVAL", "ATTRIBUTE",
  "BT_ASSERT", "BT_TEST_SUITE", "BT_CHECK_ASSIGN", "BT_TEST_SAME",
  "FORMAT", "':'", "'['", "']'", "'?'", "ROUTER", "ID", "HOSTNAME",
  "PROTOCOL", "TEMPLATE", "DISABLED", "DEBUG", "ALL", "DIRECT",
  "INTERFACE", "IMPORT", "EXPORT", "NONE", "VRF", "DEFAULT", "TABLE",
  "STATES", "ROUTES", "FILTERS", "IPV4", "IPV6", "VPN4", "VPN6", "ROA4",
  "ROA6", "SADR", "RECEIVE", "LIMIT", "ACTION", "WARN", "BLOCK", "RESTART",
  "DISABLE", "KEEP", "FILTERED", "RPKI", "PASSWORD", "KEY", "PASSIVE",
  "TO", "EVENTS", "PACKETS", "PROTOCOLS", "CHANNELS", "INTERFACES",
  "ALGORITHM", "KEYED", "HMAC", "MD5", "SHA1", "SHA256", "SHA384",
  "SHA512", "BLAKE2S128", "BLAKE2S256", "BLAKE2B256", "BLAKE2B512",
  "PRIMARY", "STATS", "COUNT", "BY", "COMMANDS", "PREEXPORT", "NOEXPORT",
  "EXPORTED", "GENERATE", "BGP", "PASSWORDS", "DESCRIPTION", "RELOAD",
  "OUT", "MRTDUMP", "MESSAGES", "RESTRICT", "MEMORY", "IGP_METRIC",
  "CLASS", "TIMEFORMAT", "ISO", "SHORT", "LONG", "ROUTE", "BASE", "LOG",
  "GRACEFUL", "WAIT", "FLUSH", "AS", "IDLE", "RX", "TX", "INTERVAL",
  "MULTIPLIER", "CHECK", "LINK", "SORTED", "TRIE", "SETTLE", "TIME", "GC",
  "THRESHOLD", "PERIOD", "IPV4_MC", "IPV4_MPLS", "IPV6_MC", "IPV6_MPLS",
  "IPV6_SADR", "VPN4_MC", "VPN4_MPLS", "VPN6_MC", "VPN6_MPLS", "PRI",
  "SEC", "SHOW", "STATUS", "CALL_AGENT", "TEST_LOG", "TEST_SEND",
  "SUMMARY", "SYMBOLS", "DUMP", "RESOURCES", "SOCKETS", "NEIGHBORS",
  "ATTRIBUTES", "ECHO", "ENABLE", "BABEL", "METRIC", "RXCOST", "HELLO",
  "UPDATE", "WIRED", "WIRELESS", "BUFFER", "PRIORITY", "HOP",
  "BABEL_METRIC", "ENTRIES", "RANDOMIZE", "MAC", "PERMISSIVE", "BFD",
  "MULTIHOP", "NEIGHBOR", "DEV", "LOCAL", "AUTHENTICATION", "SIMPLE",
  "METICULOUS", "STRICT", "BIND", "SESSIONS", "HOLD", "CONNECT", "RETRY",
  "KEEPALIVE", "STARTUP", "VIA", "SELF", "PATH", "START", "DELAY",
  "FORGET", "AFTER", "BGP_PATH", "BGP_LOCAL_PREF", "BGP_MED", "BGP_ORIGIN",
  "BGP_NEXT_HOP", "BGP_ATOMIC_AGGR", "BGP_AGGREGATOR", "BGP_COMMUNITY",
  "BGP_EXT_COMMUNITY", "BGP_LARGE_COMMUNITY", "ADDRESS", "RR", "RS",
  "CLIENT", "CLUSTER", "AS4", "ADVERTISE", "CAPABILITIES", "PREFER",
  "OLDER", "MISSING", "LLADDR", "DROP", "IGNORE", "REFRESH", "INTERPRET",
  "COMMUNITIES", "BGP_ORIGINATOR_ID", "BGP_CLUSTER_LIST", "IGP", "GATEWAY",
  "RECURSIVE", "MED", "TTL", "SECURITY", "DETERMINISTIC", "SECONDARY",
  "ALLOW", "PATHS", "AWARE", "EXTENDED", "SETKEY", "CONFEDERATION",
  "MEMBER", "MULTICAST", "LIVED", "STALE", "IBGP", "EBGP", "MANDATORY",
  "INTERNAL", "EXTERNAL", "SETS", "DYNAMIC", "RANGE", "NAME", "DIGITS",
  "BGP_AIGP", "AIGP", "ORIGINATE", "COST", "ENFORCE", "FREE", "VALIDATE",
  "ROLE", "ROLES", "PEER", "PROVIDER", "CUSTOMER", "RS_SERVER",
  "RS_CLIENT", "REQUIRE", "BGP_OTC", "GLOBAL", "RPDP4", "RPDP6", "CEASE",
  "HIT", "ADMINISTRATIVE", "SHUTDOWN", "CONFIGURATION", "CHANGE",
  "DECONFIGURED", "CONNECTION", "REJECTED", "COLLISION", "OF", "MRT",
  "FILENAME", "ALWAYS", "OSPF", "V2", "V3", "OSPF_METRIC1", "OSPF_METRIC2",
  "OSPF_TAG", "OSPF_ROUTER_ID", "AREA", "RFC1583COMPAT", "STUB", "TICK",
  "COST2", "RETRANSMIT", "TRANSMIT", "DEAD", "BROADCAST", "BCAST",
  "NONBROADCAST", "NBMA", "POINTOPOINT", "PTP", "POINTOMULTIPOINT", "PTMP",
  "CRYPTOGRAPHIC", "ELIGIBLE", "POLL", "NETWORKS", "HIDDEN", "VIRTUAL",
  "ONLY", "LARGE", "NORMAL", "STUBNET", "TAG", "LSADB", "ECMP", "NSSA",
  "TRANSLATOR", "STABILITY", "LSID", "INSTANCE", "REAL", "NETMASK",
  "MERGE", "LSA", "SUPPRESSION", "RFC5838", "PE", "TOPOLOGY", "STATE",
  "PERF", "EXP", "REPEAT", "MODE", "PIPE", "RADV", "RA", "SOLICITED",
  "UNICAST", "MANAGED", "OTHER", "CONFIG", "LINGER", "MTU", "REACHABLE",
  "RETRANS", "TIMER", "CURRENT", "VALID", "PREFERRED", "MULT", "LIFETIME",
  "SKIP", "ONLINK", "AUTONOMOUS", "RDNSS", "DNSSL", "NS", "DOMAIN",
  "TRIGGER", "SENSITIVE", "LOW", "MEDIUM", "HIGH", "PROPAGATE",
  "RA_PREFERENCE", "RA_LIFETIME", "RIP", "NG", "INFINITY", "TIMEOUT",
  "GARBAGE", "VERSION", "SPLIT", "HORIZON", "POISON", "REVERSE", "ZERO",
  "PLAINTEXT", "DEMAND", "CIRCUIT", "RIP_METRIC", "RIP_TAG", "REMOTE",
  "BIRD", "PRIVATE", "PUBLIC", "SSH", "TRANSPORT", "USER", "EXPIRE",
  "STATIC", "PROHIBIT", "BLACKHOLE", "UNREACHABLE", "KERNEL", "NETLINK",
  "KRT_PREFSRC", "KRT_REALM", "KRT_SCOPE", "KRT_MTU", "KRT_WINDOW",
  "KRT_RTT", "KRT_RTTVAR", "KRT_SSTRESH", "KRT_CWND", "KRT_ADVMSS",
  "KRT_REORDERING", "KRT_HOPLIMIT", "KRT_INITCWND", "KRT_RTO_MIN",
  "KRT_INITRWND", "KRT_QUICKACK", "KRT_LOCK_MTU", "KRT_LOCK_WINDOW",
  "KRT_LOCK_RTT", "KRT_LOCK_RTTVAR", "KRT_LOCK_SSTRESH", "KRT_LOCK_CWND",
  "KRT_LOCK_ADVMSS", "KRT_LOCK_REORDERING", "KRT_LOCK_HOPLIMIT",
  "KRT_LOCK_RTO_MIN", "KRT_FEATURE_ECN", "KRT_FEATURE_ALLFRAG", "SYSLOG",
  "TRACE", "INFO", "WARNING", "AUTH", "FATAL", "BUG", "STDERR", "SOFT",
  "CONFIRM", "UNDO", "LATENCY", "WATCHDOG", "CONFIGURE", "DOWN", "PERSIST",
  "SCAN", "LEARN", "DEVICE", "KRT_SOURCE", "KRT_METRIC", "$accept",
  "cli_cmd", "cmd_QUIT", "cmd_EXIT", "cmd_HELP", "config", "conf_entries",
  "conf", "definition", "expr", "expr_us", "symbol", "bool", "ipa",
  "ipa_scope", "pxlen4", "net_ip4_", "net_ip6_", "net_ip6_sadr_",
  "net_vpn4_", "net_vpn6_", "net_roa4_", "net_roa6_", "net_mpls_",
  "net_ip_", "net_vpn_", "net_roa_", "net_", "net_ip4", "net_ip6",
  "net_ip", "net_any", "net_or_ipa", "label_stack_start", "label_stack",
  "time", "text", "opttext", "flow_num_op", "flow_logic_op",
  "flow_num_type_", "flow_num_type", "flow_flag_type", "flow_frag_type",
  "flow_srcdst", "flow_num_opts", "flow_num_opt_ext_expr",
  "flow_num_opt_ext", "flow_bmk_opts", "flow_neg", "flow_frag_val",
  "flow_frag_opts", "flow4_item", "flow6_item", "flow4_opts", "flow6_opts",
  "flow_builder_init", "flow_builder_set_ipv4", "flow_builder_set_ipv6",
  "net_flow4_", "net_flow6_", "net_flow_", "filter_def", "$@1",
  "filter_eval", "custom_attr", "bt_test_suite", "bt_test_same", "type",
  "function_argsn", "function_args", "function_vars", "filter_body",
  "filter", "$@2", "where_filter", "function_body", "function_def", "$@3",
  "$@4", "cmds", "cmds_scoped", "$@5", "cmd_var", "cmd_prep", "cmds_int",
  "fipa", "set_atom", "switch_atom", "cnum", "pair_item", "ec_kind",
  "ec_item", "lc_item", "set_item", "switch_item", "set_items",
  "switch_items", "fprefix", "fprefix_set", "switch_body", "bgp_path_expr",
  "bgp_path", "bgp_path_tail", "constant", "constructor", "var_list",
  "function_call", "symbol_value", "static_attr", "term", "break_command",
  "print_list", "var_init", "var", "for_var", "cmd", "$@6", "$@7", "$@8",
  "get_cf_position", "lvalue", "rtrid", "idval", "hostname_override",
  "gr_opts", "net_type", "table", "table_start", "table_sorted",
  "table_opt", "table_opts", "table_opt_list", "proto_start", "proto_name",
  "proto_item", "channel_start", "channel_item_", "channel_item",
  "channel_opts", "channel_opt_list", "channel_end", "proto_channel",
  "rtable", "imexport", "limit_action", "limit_spec", "debug_default",
  "timeformat_which", "timeformat_spec", "timeformat_base",
  "iface_patt_node_init", "iface_patt_node_body", "iface_negate",
  "iface_patt_node", "iface_patt_list", "iface_patt_list_nopx",
  "iface_patt_init", "iface_patt", "tos", "proto", "dev_proto_start",
  "dev_proto", "dev_iface_init", "dev_iface_patt", "debug_mask",
  "debug_list", "debug_flag", "mrtdump_mask", "mrtdump_list",
  "mrtdump_flag", "password_list", "password_list_body", "password_items",
  "password_item", "pass_key", "password_item_begin",
  "password_item_params", "password_algorithm", "password_item_end",
  "bfd_item", "bfd_items", "bfd_opts", "cmd_SHOW_STATUS", "cmd_CALL_AGENT",
  "cmd_TEST_LOG", "cmd_TEST_SEND", "cmd_SHOW_MEMORY", "cmd_SHOW_PROTOCOLS",
  "cmd_SHOW_PROTOCOLS_ALL", "optproto", "cmd_SHOW_INTERFACES",
  "cmd_SHOW_INTERFACES_SUMMARY", "cmd_SHOW_ROUTE", "r_args", "r_args_for",
  "r_args_for_val", "export_mode", "channel_sym", "channel_arg",
  "cmd_SHOW_SYMBOLS", "sym_args", "cmd_DUMP_RESOURCES", "cmd_DUMP_SOCKETS",
  "cmd_DUMP_EVENTS", "cmd_DUMP_INTERFACES", "cmd_DUMP_NEIGHBORS",
  "cmd_DUMP_ATTRIBUTES", "cmd_DUMP_ROUTES", "cmd_DUMP_PROTOCOLS",
  "cmd_DUMP_FILTER_ALL", "cmd_EVAL", "cmd_ECHO", "echo_mask", "echo_size",
  "cmd_DISABLE", "cmd_ENABLE", "cmd_RESTART", "cmd_RELOAD",
  "cmd_RELOAD_IN", "cmd_RELOAD_OUT", "cmd_DEBUG", "debug_args",
  "cmd_MRTDUMP", "cmd_RESTRICT", "proto_patt", "proto_patt2",
  "dynamic_attr", "babel_proto_start", "babel_proto_item",
  "babel_proto_opts", "babel_proto", "babel_iface_start",
  "babel_iface_finish", "babel_iface_item", "babel_iface_opts",
  "babel_iface_opt_list", "babel_iface", "cmd_SHOW_BABEL_INTERFACES",
  "cmd_SHOW_BABEL_NEIGHBORS", "cmd_SHOW_BABEL_ENTRIES",
  "cmd_SHOW_BABEL_ROUTES", "bfd_proto_start", "bfd_proto_item",
  "bfd_proto_opts", "bfd_proto", "bfd_accept_item", "bfd_accept",
  "bfd_iface_start", "bfd_iface_finish", "bfd_iface_item", "bfd_auth_type",
  "bfd_iface_opts", "bfd_iface_opt_list", "bfd_iface", "bfd_multihop",
  "bfd_neigh_iface", "bfd_neigh_local", "bfd_neigh_multihop",
  "bfd_neighbor", "cmd_SHOW_BFD_SESSIONS", "bgp_proto_start",
  "bgp_loc_opts", "bgp_nbr_opts", "bgp_cease_mask", "bgp_cease_list",
  "bgp_cease_flag", "bgp_role_name", "bgp_proto", "$@9", "$@10", "bgp_afi",
  "bgp_channel_start", "bgp_nh", "bgp_lladdr", "bgp_channel_item",
  "bgp_channel_opts", "bgp_channel_opt_list", "bgp_channel_end",
  "bgp_proto_channel", "mrt_proto_start", "mrt_proto_item",
  "mrt_proto_opts", "mrt_proto", "cmd_MRT_DUMP", "mrt_dump_args",
  "ospf_variant", "ospf_proto_start", "ospf_proto", "ospf_af_mc",
  "ospf_channel_start", "ospf_channel", "ospf_proto_item",
  "ospf_area_start", "ospf_area", "ospf_area_opts", "ospf_area_item",
  "$@11", "$@12", "ospf_stubnet", "ospf_stubnet_start",
  "ospf_stubnet_opts", "ospf_stubnet_item", "ospf_vlink",
  "ospf_vlink_opts", "ospf_vlink_item", "ospf_vlink_start",
  "ospf_iface_item", "pref_list", "pref_item", "pref_base", "pref_opt",
  "nbma_list", "nbma_eligible", "nbma_item", "ospf_iface_start",
  "ospf_instance_id", "ospf_iface_patt_list", "$@13", "ospf_iface_opts",
  "ospf_iface_opt_list", "ospf_iface", "cmd_SHOW_OSPF",
  "cmd_SHOW_OSPF_NEIGHBORS", "cmd_SHOW_OSPF_INTERFACE",
  "cmd_SHOW_OSPF_TOPOLOGY", "cmd_SHOW_OSPF_TOPOLOGY_ALL",
  "cmd_SHOW_OSPF_STATE", "cmd_SHOW_OSPF_STATE_ALL", "cmd_SHOW_OSPF_LSADB",
  "lsadb_args", "perf_proto_start", "perf_proto", "perf_proto_item",
  "pipe_proto_start", "$@14", "pipe_proto", "radv_proto_start",
  "radv_proto_item", "$@15", "$@16", "radv_proto_opts", "radv_proto",
  "radv_iface_start", "radv_iface_item", "$@17", "$@18", "radv_preference",
  "radv_iface_finish", "radv_iface_opts", "radv_iface_opt_list",
  "radv_iface", "radv_prefix_start", "radv_prefix_item",
  "radv_prefix_finish", "radv_prefix_opts", "radv_prefix_opt_list",
  "radv_prefix", "radv_rdnss_node", "radv_rdnss_start", "radv_rdnss_item",
  "radv_rdnss_finish", "radv_rdnss_opts", "radv_rdnss", "radv_dnssl_node",
  "radv_dnssl_start", "radv_dnssl_item", "radv_dnssl_finish",
  "radv_dnssl_opts", "radv_dnssl", "radv_mult", "radv_sensitive",
  "rip_variant", "rip_proto_start", "rip_proto_item", "rip_proto_opts",
  "rip_proto", "rip_iface_start", "rip_iface_finish", "rip_iface_item",
  "rip_auth", "rip_iface_opts", "rip_iface_opt_list", "rip_iface",
  "cmd_SHOW_RIP_INTERFACES", "cmd_SHOW_RIP_NEIGHBORS", "rpki_proto_start",
  "rpki_proto", "rpki_proto_opts", "rpki_proto_item", "rpki_keep_interval",
  "rpki_proto_item_port", "rpki_cache_addr", "rpki_transport",
  "rpki_transport_tcp_init", "rpki_transport_ssh_init",
  "rpki_transport_ssh_opts", "rpki_transport_ssh_item",
  "rpki_transport_ssh_check", "static_proto_start", "static_proto",
  "stat_nexthop", "stat_nexthops", "stat_route0", "stat_route",
  "stat_route_item", "stat_route_opts", "stat_route_opt_list",
  "cmd_SHOW_STATIC", "kern_proto", "kern_sys_item", "log_begin",
  "log_config", "syslog_name", "log_limit", "log_file", "log_mask",
  "log_mask_list", "log_cat", "mrtdump_base", "debug_unix",
  "cmd_CONFIGURE", "cmd_CONFIGURE_SOFT", "cmd_CONFIGURE_CONFIRM",
  "cmd_CONFIGURE_UNDO", "cmd_CONFIGURE_STATUS", "cmd_CONFIGURE_CHECK",
  "cmd_DOWN", "cmd_GRACEFUL_RESTART", "cfg_name", "cfg_timeout",
  "kern_proto_start", "kern_mp_limit", "kern_item", "kif_proto_start",
  "kif_proto", "kif_item", "kif_iface_start", "kif_iface_item",
  "kif_iface_opts", "kif_iface_opt_list", "kif_iface", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-2251)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-899)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     190,    67,   174,   892,   258,   347,   359,  4767,   224,   233,
     233,   200,   233,   410,    35,   983,   441,   528,   662,  1162,
     211,   233,   214,    21,   672, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,   777, -2251, -2251,
   -2251, -2251,   777,   777,  4767,  3569,   485,   600,   521,   227,
   -2251, -2251,  -104, -2251,   527, -2251, -2251, -2251, -2251,   208,
     552, -2251,   498,  -236, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251,   551, -2251,   477,   680, -2251,
   -2251, -2251,   818,  2160,   818, -2251,   818, -2251,   818,  6343,
     818, -2251,   818,  1579,   818,  1420,   674,  1335,   818, -2251,
     818, -2251,   818, -2251,   818,  1696,    57, -2251, -2251, -2251,
     818,   818,   -47, -2251, -2251, -2251,   903, -2251, -2251,   721,
     748,   872,   716, -2251,   668,   126,  4767,   811, -2251,  2985,
     779,   808, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251,   781,   793,   852,   870,   878,
     900,   904,  1369, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,   821,   829, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,  3749,
   -2251,   960, -2251, -2251,   555,  1000,   555, -2251,   988,   988,
     233,   233,  1013,   601, -2251,  1023,   338,   144,  1047, -2251,
    1055, -2251,   183,   794,    43,    30,  1070, -2251, -2251, -2251,
     967,  1145,  1159,  1174,  1178,  1181,  1190,  1220,  1225, -2251,
     -45, -2251,  1216,   988, -2251, -2251,  1250,  1239,  1250,  1296,
    1302,   805, -2251, -2251, -2251,  1294, -2251, -2251,  4343, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251,   691,  1305,  1325,   956, -2251, -2251,
    1300,   555,   555,  1017,  1268, -2251,   601,  1304, -2251, -2251,
   -2251, -2251,   139,  1307,     6,  1116,  1017,  1017,   777, -2251,
    1288, -2251, -2251, -2251, -2251, -2251, -2251,   491, -2251, -2251,
   -2251,   864, -2251, -2251, -2251, -2251, -2251,  1346,  1333,  1322,
   -2251,  1238,  1833,   555, -2251,   167,   227,   601,  1148, -2251,
    1355,  1339,  1368,  1375,  1352,  1354,  1359, -2251, -2251, -2251,
     312,  1106,   533,  1394,  1426,   657,    49,    66,    89,    96,
    1124,   227,  1833,  1083,  1265,  1206,   191,  1485,   762,   134,
      72,  1152,  1203,   357,  1209,  1155,  1182,  1154,   683,  1140,
    1318,  1833,  1137,  1132,  1196,  1201,  1128,  1136,   -53,  1833,
     122,  1117,  1358,  1205,  1130, -2251, -2251,  1459, -2251,  1442,
    1478,  1454,  1456,  1071, -2251,  1349,   755,  1833,  1382,  1017,
    1833,  1384,  1175,  1833,  1177, -2251,  1339, -2251,  1504,  1482,
   -2251,  1483, -2251,  1833,   919,  1539,    98,  1545,   910,  1525,
   -2251,  1529, -2251, -2251,  1017,  1102,  1290,  1560,  1401,  1360,
    1415,  1557,  1558,  1540,  1547,  1548,  1551, -2251,  1672,  1373,
    1439,  1580,  1584,    32,  1562, -2251,  1448,  1017,  1283,  1477,
    1404,  1833,  1399,  1833, -2251, -2251,  1613,  1616,  1596,  1598,
   -2251, -2251,  1421, -2251,  1635,   931, -2251,   903,   903,  4767,
    1391,   903,   903,  1679, -2251,  1688, -2251,  1694,   721,  1661,
   -2251, -2251,  4767,  1680,   249,  1684,  1675, -2251, -2251, -2251,
    1702, -2251,  1643,  2548, -2251, -2251,  1560,  4767,  4767,  4767,
    4767,  4767,  4767, -2251, -2251,  1661, -2251, -2251,  2628, -2251,
   -2251, -2251,   758, -2251,  1714, -2251, -2251, -2251, -2251,   117,
   -2251,   131,  1716,  1717, -2251,  4767,  4767,  4767,  4767,  4767,
    4767,  4767,  4767,  4767,  4767,  4767,  4767,  4767,  4767,  2036,
    2096, -2251,  1337, -2251, -2251, -2251, -2251, -2251,  1733,  1735,
    1736,  1738, -2251, -2251,   455, -2251,  1739, -2251, -2251, -2251,
     843,  1741, -2251,  1744, -2251,  2649, -2251,  1092,  1070,  1070,
    1070,  1070,  1070, -2251,  1070,  1070, -2251,   283,   311,  1747,
    1070,  1070,  1748,  1749, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251,   865, -2251, -2251,  1751,  1753,   688,  1754, -2251,   805,
   -2251, -2251,  1017,  1755,  4767,  1715, -2251, -2251,  1723,  1691,
    1701, -2251, -2251, -2251, -2251,  4767,  1728, -2251, -2251, -2251,
   -2251, -2251,  4767, -2251, -2251, -2251, -2251, -2251,  1017, -2251,
   -2251,  1730, -2251,  1017,   862, -2251,  1402, -2251,  1017,   150,
    1017,  1027, -2251, -2251, -2251, -2251, -2251, -2251, -2251,   818,
   -2251, -2251,  1760, -2251,   755, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251,  1833, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251,  1526,  1528,  1034,  1535,  1536, -2251,  1750,  1017,  1017,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,    10,  1752,
    1756,   -89,   171,  1833,  1434,  1833,  1571,  1757,  1761,  1737,
   -2251,  1765, -2251, -2251, -2251,  1303,  1782,   152,  1176,  1782,
     154,  1833,  1017,  1563,  1568,  1017,  1569,  1833,  1575,  1833,
    1655,  1833,  1833,  1772,  1833,  1833,  1833,  1833,  1833,  1833,
    1461,  1602,  1833,  1777,  1833,  1802,    81,  1606,  1833,  1833,
   -2251, -2251, -2251, -2251, -2251, -2251,  1833,   228, -2251, -2251,
    1833, -2251,  1653,  1017,  1833, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251,  1017,  1017, -2251,  1840,  1841, -2251, -2251,
   -2251, -2251, -2251, -2251,  1839,  4767, -2251, -2251,  1193,  1665,
   -2251, -2251,  1193, -2251, -2251, -2251,  1193,  1833,  1560, -2251,
   -2251, -2251, -2251, -2251, -2251,   748,   872, -2251, -2251, -2251,
    1833,  1560, -2251, -2251, -2251,  1192, -2251,  1034, -2251, -2251,
   -2251,     3,  1542, -2251,  1815,  1833, -2251,  1833,  1017,  1570,
   -2251,  1017, -2251, -2251, -2251, -2251, -2251, -2251, -2251,  1017,
   -2251,  1851, -2251, -2251, -2251,  3227, -2251, -2251,   903,   397,
   -2251, -2251, -2251, -2251,  1819,  1854,   597,  4343, -2251,  1759,
    1844, -2251, -2251,  4767, -2251,  4767, -2251, -2251,   655,  3388,
    2871,  2902,  2939,  3048,  3417,  1807,   189,  1811,  3446, -2251,
   -2251,  1880,  1593,  1651, -2251,   872, -2251,  1650,  1654,  2238,
    2238,  2238,  2475,  2475,  2238,  2238,  2238,  2238,  2238,   954,
     954,  1675,  1675, -2251, -2251, -2251, -2251, -2251,  1849, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,   938, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251,   985, -2251, -2251,  1898,
   -2251, -2251, -2251,  1578,  1672,  1839,  1883, -2251,  1729,  1731,
     387, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
    1884, -2251, -2251, -2251, -2251, -2251, -2251, -2251,   988,   988,
     988,   988,  1906,   988,   988,   104,  1070,   988,  1070,   988,
   -2251,   988,   988, -2251, -2251,   -45, -2251, -2251, -2251, -2251,
    1839,  1011,   227, -2251, -2251,  1908, -2251, -2251,  4999,  1861,
   -2251,  5268, -2251, -2251, -2251,   227,  1893, -2251,  1866,  3613,
   -2251,  3713, -2251, -2251,  1895,  1156,  1173,   227, -2251,   227,
   -2251,   -45, -2251,  1871,  1872, -2251, -2251, -2251,   553, -2251,
   -2251, -2251,  1891, -2251,  1848,  1875,  1077, -2251,  1608,  1208,
    1017,  1017,  1881,  1017,  1017, -2251,  1882,  1887,  1833,  1792,
   -2251, -2251,  1745,  1670,  1017,  1890,  1896,  1899,  1833,  1900,
    1833, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,   777,
   -2251,  1017, -2251,  1017, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251,  1902, -2251,  1017, -2251,  1017,  1903,  1904,  1017,  1017,
    1905,  1017,  1909,  1017,  1910,   755,  1911,  1912, -2251,  1916,
    1918,  1919,  1920,  1921,  1922,  1833,  1245,  1923, -2251,  1925,
   -2251,  1017,  1926,  1833,  1936,  1938,  1463, -2251,   782, -2251,
    1017, -2251, -2251, -2251,  1017, -2251, -2251, -2251,   234, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251,  4343, -2251,  1768, -2251,
    1833, -2251, -2251, -2251,  1939,   687,   486,   155,  1940,  1941,
   -2251,  1782,  1944,  1932,  1017,  1833,  1833,     3,  5343, -2251,
   -2251,  1805, -2251,  1017, -2251,  1848,  1864, -2251,   903, -2251,
   -2251,   903,  1978, -2251, -2251,  4767,  1967,  1968,  3186,  2779,
   -2251, -2251, -2251,  4767, -2251,  4767,  4767,  4767,  4767, -2251,
    3254,  4767,  3579,  4767, -2251,  1931,  4767, -2251, -2251, -2251,
    1985,  1986,  4767,  1337, -2251,   455, -2251, -2251,   721,   504,
    1217, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251,  1987,  1987, -2251, -2251,   960, -2251,  2007,  2008,
    2010,  2014, -2251,  2016,  2019, -2251, -2251,  2009,   755, -2251,
   -2251, -2251,   755,   755,   988,  2020,   988,  2022,  2023,  2024,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,  3569, -2251,
    5055,   691,  1977,  1954,  1848, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251,  1022, -2251, -2251, -2251,  1773,
    1774,  1833,  1833,   907,  1984, -2251,  2012, -2251, -2251, -2251,
     555, -2251,  1988, -2251, -2251,  1879, -2251, -2251,  1994, -2251,
   -2251, -2251, -2251,  1034,  1724, -2251,  1995,  1970,  1997, -2251,
    1998,  2018, -2251, -2251,  2029,   381, -2251,  2030,   669,  1017,
    2032, -2251, -2251, -2251,  2033, -2251,  2034,  1284,  2035,   207,
   -2251,   369, -2251, -2251, -2251,   184, -2251, -2251, -2251, -2251,
    2037,  2038, -2251,  2040, -2251,  2045, -2251,  2047, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251,  2050, -2251,  2052, -2251,
   -2251,  2053, -2251,  2054, -2251, -2251,  1788, -2251,  1693,   738,
     725,  1742,  1942,  1915,  1711,  1947,    24,  1833,  2060,  1833,
     140,  1017,  1833, -2251,  2071, -2251,  1839,  1096,  1017,   227,
    1989, -2251, -2251,  2080, -2251, -2251, -2251, -2251,   199,  1833,
   -2251,   124, -2251,  1876,  1303, -2251,    91,  2081, -2251,  1677,
   -2251,  1428, -2251, -2251, -2251, -2251,  1127, -2251, -2251, -2251,
    1127,  1958, -2251, -2251,  2089, -2251, -2251,  1833,  1017, -2251,
   -2251,  2093,  1017, -2251,  1950,  1999,  1950,  1295,     1,  1950,
   -2251, -2251,  2097, -2251, -2251, -2251, -2251,  1932, -2251, -2251,
    2117, -2251, -2251, -2251,   465, -2251, -2251,  4767,  4767,  2101,
    4767, -2251, -2251, -2251,  4767,  4767, -2251,  2104,  2105,  2108,
    2133,  4767, -2251,   550, -2251,  1017, -2251, -2251, -2251, -2251,
   -2251, -2251,  2126,  4343,  2130, -2251,  4767, -2251,  4767,  2055,
    2786,  3215,  3811,  3909,  3982,  4011,   666,   403,  4343,  2087,
     693,   651,  2090,  2158,  3446, -2251, -2251,  4040, -2251, -2251,
    2156,   721,  1661,   960, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251,  2173, -2251,  2177, -2251,
   -2251, -2251,   691, -2251,   691,  2106, -2251, -2251,  5055, -2251,
   -2251,  2136, -2251,  2172, -2251,  1929,  1935, -2251, -2251,  1017,
    1017, -2251,  1340,  1353, -2251, -2251, -2251, -2251, -2251, -2251,
    2039, -2251,   524, -2251, -2251,  2115, -2251,   119, -2251,  1833,
   -2251,  1017, -2251, -2251, -2251, -2251,  2011,  1783,  1789, -2251,
      34,  1796,   835,  1082, -2251, -2251,  2147,  2157,  2159, -2251,
   -2251, -2251, -2251,  1004,  1833, -2251,  1960,  1017,  1017,  2165,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251,   121,  1151,  1833,  1833,   -20,  1560,  1833,
     532,  1560, -2251, -2251, -2251,  1924, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,  1897, -2251, -2251,
   -2251,  1017,  1017,  1833, -2251,  2129,  1017, -2251,  2140,   755,
   -2251, -2251,  2141,  1017, -2251, -2251,  1017,  2143, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251,  2144, -2251, -2251, -2251,   784,
     490, -2251,  1833, -2251, -2251, -2251,  2048, -2251, -2251, -2251,
   -2251,  1017,  2162,  1017, -2251, -2251, -2251,  2187, -2251, -2251,
   -2251,  1017, -2251,  2117,  2218,  4767,  2161,  5055,  3317,  2186,
    2190,  6419,  5028,  2044,  2487,  2205, -2251, -2251, -2251,  4767,
    2191,  4767,  1586, -2251,    -2,  2226,  2211,  4207,  4307, -2251,
   -2251, -2251, -2251,  2185, -2251, -2251,  1199,  2179, -2251, -2251,
   -2251, -2251, -2251, -2251,  1687,  2215,  2215,   962,  2202, -2251,
    1687,  2215,  2215,  1127,  2203,  4767, -2251, -2251, -2251, -2251,
   -2251,  2222,  4767, -2251,  3848, -2251,  2223,  4767,  2250,  4173,
    4442,  2182, -2251, -2251, -2251, -2251,  1125,  2236, -2251, -2251,
   -2251,  2221,  1017,  1017, -2251, -2251,   721,  1661, -2251, -2251,
   -2251, -2251,  2206,  1833, -2251, -2251, -2251, -2251, -2251,  2115,
   -2251, -2251,   777,   227,  1976, -2251,  2235,  1885,  2003, -2251,
   -2251, -2251, -2251, -2251, -2251,   381, -2251, -2251, -2251, -2251,
    2056,  2057, -2251,  2058, -2251, -2251, -2251,   388,   388,  1034,
    1901, -2251, -2251, -2251, -2251, -2251,  2094,  2031, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251,  1833,  1833,  1848,  2213, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251,  2231, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251,  2237,  1017, -2251,  1833, -2251, -2251, -2251,  2244,
   -2251, -2251,  5185, -2251, -2251,  4767, -2251, -2251,  2260, -2251,
    5631, -2251, -2251,   691,  2207,  4767,  5900,  5214, -2251,  5245,
    2262,  2272,  2275,  2282,  2283, -2251,  1034,  2286, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251,  2329,  1017,  1324, -2251,  2264, -2251,
     745,  1017,  1775,   767, -2251, -2251, -2251, -2251,  1324,   745,
     767,  2263, -2251,  4405,  2295,  2296,   733,   435,  2297,   749,
    2299,  2300,   492,  2304,   603, -2251, -2251, -2251,  4767,  2301,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,   647, -2251, -2251,
   -2251,  1034,  2068, -2251, -2251, -2251, -2251,  1017,  1017,  1017,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,  1833,  1017, -2251,
   -2251,  1677, -2251, -2251,  1010,  1143,     0,    17,    92, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251,  2307,  2253,  1567, -2251, -2251,  4343, -2251, -2251, -2251,
   -2251, -2251, -2251,  4767,  4767,  4767, -2251,  4767, -2251, -2251,
    1017, -2251, -2251,  1017,  1466,  1017, -2251,  2215,  2215,  2325,
   -2251, -2251, -2251, -2251, -2251,  2215,  2215,  2358, -2251, -2251,
   -2251, -2251,  2342,  4767, -2251, -2251, -2251,  2343,  4767, -2251,
    4767,  2370, -2251,  4767, -2251,  4343, -2251,  1758, -2251, -2251,
   -2251,  1051, -2251, -2251,  1833,  2302,  2128,  1017,  1017,   442,
   -2251, -2251, -2251,   937,  2306,  2334, -2251,  1833, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251,  2183, -2251, -2251, -2251,   252,
   -2251, -2251,  1833,  1017,  1833,  2335, -2251,  1017,  1017,    11,
    1017,  2062,   280, -2251,  2337, -2251,  1914,  1917,  1833,  1833,
    1833,  2341,   746, -2251,     9,   -18,   944, -2251,   -31, -2251,
    5631, -2251, -2251, -2251,  2628, -2251, -2251,  2386, -2251, -2251,
   -2251, -2251,   100,  4767,  2345,  2322,  4503,  4576,  4605,  4634,
   -2251,  2264,  1017, -2251,  1017,  1017,  1017,  1775,  1775, -2251,
    2351,  2352,  2354,  2331,  2356,  2359,  2361,  1017,  2113,  1048,
   -2251,  1017,  2118,   215,  2163,  1017,  2164,  2170,   115, -2251,
    2366,  2171,  2175, -2251,  1150,  2176, -2251, -2251, -2251,  1170,
   -2251,  2210, -2251, -2251, -2251,   879, -2251, -2251, -2251,  1546,
   -2251,  1017,  2135,   238,  2169,  1965,  2355,  1017,  1017,  1833,
      25,  2013,  2072,  1017,  1833,  1017,  2119,   642,  -148,  1017,
    2318,  2017, -2251,  2394, -2251,  1017,  2395, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,  1017,  1017, -2251,
   -2251,  1017,  1017, -2251, -2251, -2251, -2251, -2251,    31,  -140,
    1973,   -34,   -38,  1974,  1975,  1833,  1972,  2193,  1979,  2166,
    2148,  2149,  2405, -2251,    58,  1034,  2408, -2251,    58,  2436,
    2410,  1017, -2251,  1833,  2167,   484,   -96,  1017,  2201,  1833,
     -33,  1034,  2109,  2209,  2347,  -154,  2212,  2214,    78,  1956,
    1963,  1961, -2251,  2423, -2251,  1959,  1955,   227,  2429, -2251,
   -2251,  4801,  1105,  1416, -2251,  4343,  2433,  4767,  2438,  2439,
    2440,  2441, -2251,  2459,  2460, -2251, -2251, -2251, -2251, -2251,
   -2251,  4767, -2251,  4767, -2251, -2251,  1210, -2251, -2251, -2251,
    1017,  1017,  1017,  1017,  1017, -2251,  1833, -2251,  1017,  1017,
   -2251,  2208, -2251,  1017,  1017,  2432,  2472,  1017, -2251, -2251,
    1184,  2504,   156,  1017,  2504,  1727,   157,  2450, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,   118,  1017,  1017,
   -2251,  1833,  2067, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
    1833,   979, -2251, -2251, -2251,  1017,  1017, -2251,  1833,  1833,
   -2251,  1017,  1833, -2251, -2251, -2251, -2251, -2251,  2041,  2041,
    2270, -2251,  1017,  2278,  2279,   641,  1017,   641,  2274,  1017,
    1017,  2061, -2251,  1833,  1017,  1017,  2346,  1833,   784,  1833,
     490, -2251, -2251,  1017, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251,  1017,  1017,  1017, -2251,  1833,  1833,
   -2251,  1017, -2251, -2251, -2251, -2251, -2251, -2251, -2251,  1165,
    1017,  1017, -2251, -2251,  1017,  1017,  1833, -2251,  1833,  1833,
    1833, -2251, -2251,  2338,  2340, -2251, -2251, -2251,  4767, -2251,
   -2251, -2251,  2435, -2251,  4901, -2251, -2251, -2251, -2251,  1017,
    1017,  2489,  2466,  1034,  1034, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,  1150, -2251, -2251,
   -2251, -2251,  2495,  2504,  2504,  2496,  2497,   916,  1681, -2251,
   -2251, -2251, -2251,  2498,  2504,  2504, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251,  1833,  1147, -2251,  2103, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251,  1833, -2251, -2251,  1017, -2251,  1017,
    1017, -2251, -2251, -2251, -2251,  2041, -2251,  1017,  2041, -2251,
    1833, -2251, -2251, -2251,  1017, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251,  2107, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251,   227,   227,  4801,  5631,
    2501, -2251, -2251, -2251,  4767, -2251, -2251, -2251,   879,  2502,
    2512,   879,   879, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251,   879,  2513,  2515, -2251, -2251, -2251,  2125,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251,  2478, -2251,   879,   879,
   -2251, -2251, -2251,   879,   879, -2251,  2517,  4767, -2251, -2251,
   -2251, -2251, -2251,  2516, -2251
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1458,     0,     3,   135,   137,   139,   573,
     575,   577,   579,   581,   583,   585,   589,   591,   593,   650,
     659,   661,   663,   665,   667,   669,   671,   673,   675,   677,
     679,   686,   688,   690,   692,   694,   696,   698,   702,   704,
     798,   800,   802,   804,   760,   983,  1126,  1128,  1130,  1132,
    1134,  1136,  1138,  1140,  1312,  1314,  1377,  1442,  1444,  1446,
    1448,  1450,  1452,  1454,  1456,     1,     2,     0,   409,     6,
     407,   408,     0,     0,     0,     0,     0,     0,     0,     0,
     426,   427,     0,   400,   401,   403,   404,   405,   406,     0,
       0,  1412,     0,     0,     5,     7,   141,   144,   146,   148,
     150,   180,   389,   396,   398,     0,   410,   413,     0,   470,
     474,   425,   428,   432,   428,   762,   428,   713,   428,   432,
     428,   970,   428,   432,   428,   432,     0,   432,   428,  1173,
     428,  1259,   428,  1316,   428,   432,   432,  1411,  1434,  1437,
     428,   428,   432,   136,   138,   140,   265,   266,   276,   193,
     194,   271,   285,   269,     0,     0,     0,     0,   286,     0,
       0,     0,   289,   267,   268,   287,   288,   290,   291,   292,
     293,   294,   295,   297,   296,     0,     0,     0,     0,     0,
       0,     0,     0,   712,   797,   957,   960,   959,   956,   958,
     961,   962,   963,   966,   968,   964,   965,   967,   969,  1122,
    1123,  1124,  1125,  1257,  1258,  1310,  1311,  1383,  1384,  1385,
    1386,  1387,  1388,  1389,  1390,  1391,  1392,  1393,  1394,  1395,
    1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,
    1406,  1407,  1408,  1409,  1410,  1490,  1491,    37,    38,    47,
      39,    40,    41,    42,    48,    43,    44,    45,   272,   133,
     134,    46,   270,   280,   316,   317,   349,   315,   318,     0,
     319,   706,   708,   707,     0,     0,     0,   706,    69,    69,
       0,     0,     0,     0,   705,     0,   710,     0,     0,   595,
       0,   652,     0,     0,   588,     0,   588,   576,   578,   580,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   682,
       0,   681,   684,    69,   985,  1459,  1458,     0,  1458,     0,
       0,  1460,  1455,    16,    15,     0,   181,   142,   145,   152,
     153,   154,   156,   155,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,     0,     0,     0,     0,    67,    66,
       0,     0,     0,     0,    22,   402,     0,     0,   476,   475,
     477,   478,     0,     0,     0,     0,     0,     0,     0,   414,
     423,   502,  1317,   807,   763,   714,   971,   992,  1152,  1167,
    1174,  1260,  1347,  1464,  1477,   995,  1262,     0,   429,     0,
     501,     0,    22,     0,   508,     0,     0,     0,     0,   440,
       0,   454,     0,     0,     0,     0,     0,   914,   915,   806,
       0,     0,     0,     0,     0,     0,   904,   905,     0,     0,
       0,     0,    22,     0,     0,     0,     0,    22,     0,   811,
     808,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,   916,   917,     0,   918,   952,
       0,     0,     0,     0,   991,     0,     0,    22,     0,     0,
      22,     0,     0,    22,   998,  1002,   454,  1003,     0,     0,
    1016,     0,  1151,    22,     0,     0,     0,     0,     0,     0,
    1156,     0,  1169,  1166,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1346,     0,     0,
       0,     0,     0,  1366,  1375,  1463,     0,     0,     0,     0,
       0,    22,     0,    22,  1469,  1470,     0,     0,     0,     0,
    1476,  1483,     0,  1480,     0,   265,   285,   265,   265,     0,
       0,   265,   265,     0,   254,     0,    29,     0,     0,     0,
      32,    33,   281,     0,     0,     0,   313,    36,   216,   217,
       0,   219,     0,     0,   128,   128,     0,     0,     0,     0,
       0,     0,     0,   195,   198,   194,   197,   200,     0,   273,
      37,    38,   245,   196,   234,   231,   232,   233,   241,     0,
     249,     0,     0,     0,   678,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   511,     0,   510,   701,   699,   700,    68,     0,     0,
       0,     0,   693,   522,     0,   521,     0,  1457,   709,   711,
     710,     0,   590,     0,   582,     0,   574,     0,   588,   588,
     588,   588,   588,   587,   588,   588,  1142,   588,   588,     0,
     588,   588,     0,     0,   672,   664,   674,   666,   660,   662,
     668,   670,  1430,  1425,  1428,  1426,  1427,  1429,  1431,  1432,
    1433,     0,  1423,   685,     0,     0,     0,     0,  1451,  1460,
    1447,  1449,  1461,     0,     0,     0,   172,   167,     0,     0,
       0,   392,   394,   395,   497,     0,     0,   397,   471,   472,
       9,    11,     0,   473,    18,    20,    19,    21,     0,    17,
    1438,     0,  1436,   479,     0,   487,  1415,  1420,  1416,     0,
       0,     0,  1441,  1440,   412,   421,   411,   993,   994,   428,
    1261,   430,     0,   503,     0,   433,   434,   488,   439,   438,
     437,   435,    22,   504,   452,   456,   505,   506,   768,   721,
     834,     0,     0,     0,     0,     0,   851,     0,     0,     0,
     908,   906,   909,   907,   910,   912,   911,   913,     0,     0,
       0,     0,    22,    22,     0,    22,     0,     0,     0,     0,
     852,     0,    23,    24,    25,     0,    26,     0,     0,    26,
       0,    22,     0,     0,     0,     0,     0,    22,     0,    22,
       0,    22,    22,     0,    22,    22,    22,    22,    22,    22,
       0,     0,    22,     0,    22,     0,     0,     0,    22,    22,
     835,   950,   954,   836,   980,   996,    22,    22,  1017,  1004,
      22,  1014,  1011,     0,    22,  1005,   999,  1000,   456,   997,
    1019,  1153,  1163,     0,     0,  1162,     0,     0,  1159,  1164,
    1165,  1155,  1154,   447,   176,     0,   461,   462,     0,     0,
     460,   442,     0,   443,   458,   441,     0,    22,     0,  1170,
    1171,  1185,  1269,  1319,  1348,     0,     0,    56,    55,  1362,
      22,     0,  1349,  1350,  1368,     0,  1367,     0,  1371,  1369,
    1370,  1360,  1363,  1373,     0,    22,  1381,    22,     0,     0,
    1471,     0,  1473,  1379,  1466,  1465,  1478,   488,  1481,     0,
    1479,     0,   257,   263,   261,     0,   193,   194,   265,     0,
     262,   264,   256,    28,    30,     0,     0,   282,   338,     0,
       0,   339,   218,     0,   298,     0,   129,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,   246,
     247,     0,     0,     0,   274,     0,   275,     0,     0,   310,
     308,   306,   303,   304,   305,   307,   309,   311,   312,   299,
     300,   301,   302,   328,   327,   321,   322,   323,     0,   326,
     320,   324,   325,   333,   334,   335,   330,   331,   332,   336,
     337,   646,   644,   645,   629,   632,   636,   639,   642,   643,
     630,   631,   633,   634,   635,   637,   638,   640,   641,   647,
     648,   649,   515,   516,   517,   519,   520,   518,     0,   513,
     691,   687,   695,   697,   526,   527,     0,   524,   703,     0,
     584,   592,   594,     0,     0,   176,     0,   605,     0,   626,
       0,   607,   606,   611,   612,   625,   627,   628,   596,   604,
       0,   651,   654,   655,   656,   657,   653,   658,    69,    69,
      69,    69,     0,    69,    69,     0,   588,    69,   588,    69,
    1127,    69,    69,  1378,   676,     0,   683,   680,   689,   984,
     176,     0,     0,   989,  1453,     0,  1462,  1443,     0,   168,
     182,     0,   143,   174,   147,     0,     0,   488,     0,     0,
     390,     0,  1439,  1435,     0,   481,   484,     0,  1419,     0,
    1418,     0,  1421,     0,     0,    12,    13,    14,     0,  1168,
     431,   436,   491,   494,   509,     0,     0,   457,   432,   432,
       0,     0,     0,     0,     0,   842,     0,     0,    22,    22,
     880,   882,     0,     0,     0,     0,     0,     0,    22,     0,
      22,   897,   896,   570,   899,   853,    54,    53,   811,     0,
     811,     0,   839,     0,   814,   815,   829,   830,   831,   832,
     833,     0,   808,     0,   837,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   879,     0,
       0,     0,     0,     0,     0,    22,     0,     0,   881,     0,
     846,     0,     0,    22,     0,     0,     0,   955,   432,  1006,
       0,  1009,  1008,  1007,     0,  1015,  1013,  1001,     0,  1160,
    1161,  1157,  1158,   175,   459,   172,   178,   469,   463,   445,
      22,   446,   444,   449,     0,   432,   432,   432,     0,     0,
    1355,    26,  1364,     0,     0,    22,    22,  1361,     0,  1353,
    1474,  1467,  1380,     0,  1472,   496,  1487,  1482,   265,   255,
     259,   265,     0,    30,   284,     0,     0,     0,     0,     0,
     124,   126,   346,     0,   314,     0,     0,     0,     0,   348,
       0,     0,     0,     0,   199,     0,     0,   235,   242,   250,
       0,     0,     0,     0,   512,     0,   523,   586,   623,   624,
       0,   620,   621,   622,   616,   614,   615,   597,   613,   598,
     603,   610,     0,     0,   599,   600,   608,   609,     0,     0,
       0,     0,   761,     0,     0,  1141,  1150,     0,     0,  1145,
    1148,  1143,     0,     0,    69,     0,    69,     0,     0,     0,
    1424,   988,   987,   986,   990,  1445,     8,   170,     0,   172,
     184,     0,     0,     0,   498,   391,   393,    10,   480,   482,
     483,   485,   486,  1414,  1417,     0,  1413,   399,   424,     0,
       0,    22,    22,     0,     0,   492,    69,   488,   507,   455,
       0,   450,     0,   770,   771,     0,   764,   765,     0,   723,
     728,   730,   730,     0,     0,   715,     0,     0,     0,   865,
       0,     0,   864,   863,     0,     0,   816,     0,    22,     0,
       0,   889,   888,   895,     0,   876,     0,     0,     0,     0,
      27,     0,   812,   813,   902,     0,   809,   810,   856,   848,
       0,     0,   869,     0,   858,     0,   844,     0,   845,   878,
     861,   883,   860,   859,   894,   862,     0,   884,     0,   886,
     847,     0,   854,     0,   857,   903,     0,   953,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,     0,    22,
      22,     0,    22,   925,     0,   982,   176,     0,     0,     0,
       0,   976,   972,     0,  1010,  1012,  1018,  1112,     0,    22,
    1032,    22,  1030,     0,     0,  1022,    22,     0,  1036,  1113,
     177,     0,   468,   448,  1172,  1187,     0,  1188,  1179,  1181,
       0,     0,  1175,  1176,     0,  1271,  1272,    22,     0,  1263,
    1264,     0,     0,  1318,  1331,     0,  1331,     0,     0,  1331,
    1321,  1322,     0,  1325,  1351,  1352,  1354,     0,    62,    63,
    1356,  1358,  1359,  1357,     0,   186,  1376,   353,   353,     0,
       0,   350,   351,   352,     0,     0,   364,     0,     0,     0,
       0,   353,  1372,     0,  1374,     0,  1475,  1382,  1485,  1489,
     258,   260,     0,   283,     0,   340,     0,   277,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,     0,
       0,     0,     0,     0,     0,    34,    35,     0,   514,   525,
       0,   617,   618,     0,   601,   602,   805,   799,   801,   803,
    1131,  1129,  1146,  1149,  1144,  1147,     0,  1133,     0,  1137,
    1313,  1315,     0,   183,     0,     0,   190,   191,   185,   188,
     189,     0,   149,     0,  1422,     0,     0,   415,   416,     0,
       0,   422,   489,     0,   493,   495,   451,   453,   488,   766,
       0,   769,   716,   488,   717,   748,   718,   752,   719,    22,
     722,     0,   871,   849,   870,   873,     0,     0,     0,   820,
       0,     0,     0,     0,   818,   874,     0,     0,     0,   890,
     875,   877,   572,     0,    22,   569,     0,     0,     0,     0,
     900,   841,   840,   838,   868,   867,   850,   866,   843,   887,
     885,   855,   901,     0,    22,    22,    22,     0,     0,    22,
       0,     0,   932,   933,   934,     0,   930,   946,   945,   947,
     935,   951,   975,   974,   973,   978,   977,     0,   981,   488,
    1035,     0,     0,    22,  1023,     0,     0,  1021,     0,     0,
    1039,  1034,  1038,     0,  1028,  1020,     0,  1046,   464,   465,
     466,   467,    52,    51,  1221,  1230,  1178,   488,  1177,     0,
       0,  1183,    22,  1186,   488,  1268,  1265,  1267,  1270,  1333,
    1332,     0,     0,     0,    25,  1335,  1334,  1323,  1338,  1339,
    1326,     0,  1320,  1365,     0,     0,     0,   184,   354,     0,
       0,     0,     0,     0,     0,     0,   385,   385,   376,     0,
       0,     0,     0,  1468,     0,     0,     0,     0,     0,    82,
      93,    94,    80,     0,    83,    84,     0,     0,    87,    88,
      92,    89,   131,    90,     0,   106,   106,     0,     0,   132,
       0,   106,   106,     0,     0,     0,   343,   344,   342,   345,
     214,     0,     0,   212,     0,   208,     0,     0,   206,     0,
       0,     0,   329,   619,  1135,  1139,     0,   356,   179,   192,
     173,     0,     0,     0,   419,   420,    59,    60,    61,    57,
      58,   490,   794,    22,   726,   724,   725,   727,   729,   748,
     746,   731,     0,     0,   755,   720,     0,     0,     0,   823,
     824,   822,   826,   825,   827,     0,   817,   892,   891,   893,
       0,     0,   568,     0,   563,   567,   571,    22,    22,     0,
       0,   940,   941,   942,   943,   944,     0,     0,   949,   936,
     922,   923,   924,   931,   948,    22,    22,  1115,  1119,  1025,
    1026,  1024,  1100,  1027,  1100,  1060,  1040,  1029,  1114,  1047,
    1228,  1227,  1218,  1234,  1233,  1241,  1180,  1243,  1244,  1251,
    1182,  1184,  1307,     0,  1328,    22,  1327,  1324,  1336,     0,
    1329,    64,     0,   361,   187,   353,   374,   375,     0,   369,
       0,   251,   360,     0,     0,     0,     0,     0,   373,     0,
       0,     0,     0,     0,     0,  1488,     0,     0,    31,   341,
     278,   279,    81,    85,    86,    91,    76,    74,    72,    71,
      73,    75,    70,    77,    99,     0,   116,   101,    97,   107,
     117,     0,     0,   118,    50,    49,   115,   125,   121,   122,
     123,   119,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   248,   169,   171,     0,     0,
     151,   417,   418,   792,   772,   767,   731,     0,   751,   753,
     754,     0,   757,   872,   821,   828,   819,     0,     0,     0,
     920,   921,   919,   928,   927,   926,   929,    22,     0,   939,
     979,  1113,  1117,  1121,     0,     0,     0,  1049,     0,  1232,
    1216,  1215,  1239,  1249,  1305,  1273,  1266,  1330,  1340,   368,
     355,     0,   362,     0,   359,   365,   385,   386,   387,   385,
     388,   371,   370,     0,     0,     0,   378,     0,  1484,  1486,
       0,    95,    79,    78,     0,     0,    78,   106,   106,     0,
     108,   109,   110,   111,   112,   106,   106,     0,   347,   229,
     213,   211,     0,     0,   209,   227,   207,     0,     0,   225,
       0,   223,   222,     0,   220,   357,   358,   773,   796,   750,
     749,     0,   535,   536,    22,     0,     0,     0,     0,     0,
     739,   528,   530,     0,   562,     0,   756,    22,   759,   564,
     565,   566,   937,   938,  1116,     0,  1033,  1103,  1101,  1104,
    1031,  1037,    22,     0,    22,     0,  1045,     0,     0,     0,
       0,     0,     0,  1059,     0,  1231,     0,     0,    22,    22,
      22,     0,     0,  1220,  1235,  1245,     0,  1309,     0,   372,
       0,   186,   201,   204,     0,   377,   203,   239,   236,   237,
     238,   243,     0,     0,     0,     0,     0,     0,     0,     0,
     100,    98,     0,   102,     0,     0,     0,     0,     0,   120,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     795,     0,     0,     0,     0,     0,     0,     0,     0,   791,
       0,     0,     0,   737,   531,     0,   732,   736,   740,     0,
     741,     0,   738,   538,   537,   539,   534,   747,   758,     0,
    1120,     0,     0,     0,     0,     0,     0,     0,     0,    22,
       0,     0,     0,     0,    22,     0,     0,     0,     0,     0,
       0,     0,  1099,     0,  1105,     0,     0,  1043,  1044,  1042,
    1041,  1053,  1050,  1056,  1057,  1058,  1051,     0,     0,  1054,
    1048,     0,     0,  1222,  1223,  1224,  1229,  1219,     0,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
    1206,  1208,     0,  1238,     0,     0,     0,  1248,     0,     0,
       0,     0,  1308,    22,     0,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1300,     0,  1345,     0,     0,     0,     0,   363,
     253,   205,     0,     0,   186,   366,     0,     0,     0,     0,
       0,     0,    96,     0,     0,   103,   114,   113,   228,   210,
     226,     0,   224,     0,   221,   774,     0,   777,   778,   776,
       0,     0,     0,     0,     0,   783,    22,   775,     0,     0,
     788,   789,   793,     0,     0,     0,     0,     0,   742,   743,
       0,     0,     0,     0,     0,     0,     0,     0,  1068,  1069,
    1070,  1071,  1072,  1073,  1074,  1075,  1065,     0,     0,     0,
    1093,    22,     0,  1107,  1062,  1080,  1098,  1087,  1088,  1089,
      22,    22,  1061,  1082,  1064,     0,     0,  1066,    22,    22,
    1063,     0,    22,  1118,  1106,  1102,  1052,  1055,  1255,  1255,
       0,  1205,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1193,    22,     0,     0,     0,    22,     0,    22,
       0,  1217,  1242,     0,  1253,  1237,  1236,  1240,  1252,  1247,
    1246,  1250,  1279,  1277,     0,     0,     0,  1293,    22,    22,
    1274,     0,  1298,  1301,  1304,  1303,  1302,  1299,  1278,    22,
       0,     0,  1275,  1276,     0,     0,    22,  1280,    22,    22,
      22,  1306,  1337,     0,     0,  1344,  1341,   202,     0,   240,
     244,   252,     0,   383,     0,   380,   381,   379,   382,     0,
       0,     0,     0,     0,     0,   781,   782,   500,   499,   784,
     785,   779,   780,   790,   733,   734,   529,   531,   735,   744,
     745,    65,     0,     0,     0,     0,     0,     0,     0,   558,
     559,   560,   561,     0,     0,     0,   562,  1091,  1090,  1092,
    1095,  1094,  1083,    22,     0,  1081,     0,  1096,  1079,  1067,
    1078,  1077,  1084,  1076,    22,  1225,  1226,     0,  1191,     0,
       0,  1212,  1213,  1214,  1201,  1255,  1202,     0,  1255,  1195,
      22,  1194,  1196,  1197,     0,  1210,  1207,  1211,  1209,  1254,
    1291,  1292,  1294,  1297,  1284,  1286,     0,  1295,  1289,  1290,
    1287,  1288,  1281,  1282,  1283,  1285,     0,     0,     0,     0,
       0,   105,   104,   215,     0,   786,   787,   532,   539,     0,
       0,   539,   539,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   539,     0,     0,   533,  1085,  1086,  1109,
    1108,  1097,  1256,  1203,  1189,  1190,  1199,  1204,  1200,  1192,
    1198,  1296,  1343,  1342,   367,   384,     0,   544,   539,   539,
     546,   545,   547,   539,   539,  1110,     0,     0,   542,   543,
     540,   541,  1111,     0,   230
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,  -102,
    -366,   -66,   518,  -436,  -751, -2251,  -155,  -163,  1530,  1531,
    1532, -2251, -2251, -2251,  -197, -2251, -2251,  -493, -2251, -1392,
    -765,  -581, -2251, -2251,  1024, -1963,  -109,  -249,   461, -1123,
   -2251,   996,   998,   999,  1001,   750,   467,   470,   753, -1292,
    -848,   754, -2251, -2251, -2251, -2251,  2025, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,   -86, -2251,
   -2251, -2251,  1362,  -985, -2251,  -595,  1240, -2251, -2251, -2251,
     801, -2068, -2251, -2251,   963, -2251,  -200,  1641,   212, -1235,
   -2019,  2426, -1985, -1955,  1644,   213,  2059, -2251,  1645, -2251,
   -2251, -2251, -2251,  -510, -2251, -2251, -2251, -1245,  -151, -1240,
      -6, -2251, -1471, -2251, -2251, -2251, -1248, -2251, -2251, -2251,
   -1669, -2251, -2251,  -457, -2251, -2251,   177, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251,   -75,  -111, -2251,  2461,  1396, -2251,
    2127,  1769,  -133,  -562,  -489, -2251,  -396, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251,  1231,  -727,  -913, -2251, -2251, -2071,
   -2251, -2251, -2251, -2251, -2251,  -279, -2251,  1316,  -112, -2251,
    1315, -1460, -2251,    36, -2123, -2251, -2251, -1033, -2251,    15,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
    -282, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,  -899,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251,   637,  1990, -1252, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,  1222,   569,
   -2251, -2251, -2251,   739, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251,  1447,    74, -2251, -2251,   726, -2251, -2251, -2251,
   -2251, -2251, -2251,   714, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,   689, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251,   554, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,   137, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,   298,   284, -2251,
   -2251, -2251, -2251,   130,   281, -2251, -2251, -2251, -2251,   132,
     287, -2250, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
    -536,   854, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251,  1762, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251,  1533,  1572, -2251,
   -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,   959,
    1969, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251, -2251,
   -2251, -2251
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    25,    26,    27,    28,     2,     3,   114,   115,   719,
     732,   398,  2072,  1954,  1170,   556,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,  2026,  1764,
    2187,   889,  1881,  1549,  1550,  2592,   360,   628,  2015,  2124,
    1833,  1834,  1835,  1836,  1837,  2016,  2017,  2018,  2020,  2021,
    2134,  2023,  1838,  1844,  1589,  1590,   946,  1280,  1281,   269,
     270,   271,   116,   696,   117,   118,   119,   120,  1634,  1358,
    1100,  1101,  1102,  1234,  1235,   870,  1103,   121,   695,  1359,
    1635,  1796,  1797,  1636,  1637,  1638,   272,   594,  2227,   956,
     595,   957,   596,   597,   598,  2231,   599,  2232,   600,   601,
    2103,   552,   273,   553,   274,   275,   936,   276,   277,   278,
    1598,  1571,  1799,  2049,  1639,  1984,  1640,  1805,  2233,  2562,
    1985,  2109,   122,   706,   123,   124,   409,   126,   127,   380,
    1384,  1128,   736,   128,   399,   410,   411,  1391,  1392,  1136,
     755,  1137,   412,   875,   871,  1512,  1239,   129,   372,   373,
     130,  1132,  1654,  1386,  1133,  1265,  1266,  1107,  1108,  2425,
     131,   132,   133,   747,   413,   624,  1028,  1029,   636,  1036,
    1037,  2170,  2171,  2435,  2172,  2173,  2174,  2447,  2603,  2286,
    1699,  1427,  1164,    29,    30,    31,    32,    33,    34,    35,
     659,    36,    37,    38,   645,  1317,  1318,  1060,  1021,   284,
      39,   647,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,   322,   684,    51,    52,    53,    54,    55,
      56,    57,   285,    58,    59,   286,   641,   280,   134,  1398,
    1138,   135,  1658,  2158,  2270,  2157,  2054,  1659,    60,    61,
      62,    63,   136,  1406,  1139,   137,  1888,  1662,  1663,  2058,
    2175,  2282,  2057,  1891,  1664,  1666,  1894,  2062,  2178,  1668,
      64,   138,   800,   797,  1417,  1683,  1684,  1181,   139,   789,
    1428,   468,   469,  2073,  1933,  1484,  1216,   832,  1217,   470,
     140,  1493,  1218,   141,    65,   686,   395,   142,   143,   847,
     486,   487,   488,   489,   490,  1228,  1507,  1748,  1745,  1751,
    1752,  2086,  2195,  1508,  2087,  2204,  1509,  2313,  2084,  2188,
    2189,  2316,  2614,  2726,  2700,  1739,  1757,  1938,  2081,  2185,
    2083,  1740,    66,    67,    68,    69,    70,    71,    72,    73,
    1075,   144,   145,   501,   146,   739,   147,   148,  1524,  1769,
    1770,  1245,   149,  1767,  2352,  2508,  2510,  2634,  2213,  2212,
    2091,  1768,  1765,  2211,  2089,  2088,  1951,  1766,  1955,  2092,
    2356,  2512,  2214,  1956,  1959,  2093,  2360,  2518,  2215,  1960,
    2515,  2625,   396,   150,  1531,  1246,   151,  1774,  2217,  2383,
    2537,  2216,  2095,  1775,    74,    75,   152,   153,  1247,  1542,
    1781,  1543,  1787,  1790,  1968,  1969,  2218,  2388,  2552,   154,
     155,   901,   902,   523,   524,  1574,  1258,   904,    76,   156,
     536,   374,   157,  1118,  1120,   729,  1123,   681,   682,   158,
     159,    77,    78,    79,    80,    81,    82,    83,    84,   331,
     693,   160,  1576,   537,   161,   162,   544,   917,  1997,  1814,
    1579,   918
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     367,   279,   593,   796,   799,   592,  1573,   626,   561,   354,
    1572,   733,   500,  1569,   948,   554,   560,   873,  1570,   838,
    1134,   335,   522,   535,   662,   888,   336,   337,   467,   358,
    1168,   359,   485,   540,   499,   922,   511,   923,   924,   591,
     629,   930,   931,   672,   521,   534,   325,   590,  1182,  2384,
    1059,   543,   559,  1253,  1762,  1597,  1599,  1601,  1602,   414,
    1320,   415,  2357,   416,  1058,   471,   653,   472,  1788,   491,
       4,     5,     6,   513,   685,   514,   710,   515,  1995,   516,
    2191,   711,   708,   709,  2228,   538,   539,  1800,   338,  2353,
    2497,  1093,   792,   793,  2495,   794,   710,  2196,  1148,   770,
    1810,   711,   361,   362,   358,  1351,   359,    88,  1573,   710,
    1335,   712,    90,    91,   711,  1569,   772,   401,  2229,   894,
    1570,   363,   402,   403,   746,   673,   541,  1336,  1771,  1254,
     405,   712,   714,   715,   716,   717,   710,   525,  1986,   774,
     710,   711,   710,  2533,   712,   711,   776,   711,  2230,   856,
     642,  2436,   888,  2390,   792,   793,  1892,   794,   710,  1152,
     564,  1327,  2528,   711,   723,   714,   715,   716,   717,  1337,
     566,   712,  2205,   573,    85,   712,  1900,   712,  2393,  2534,
     125,   714,   715,   716,   717,   406,  2492,  2323,   407,   710,
     358,  2478,   359,   712,   711,   963,  1722,     1,   820,  1291,
    1171,  2467,  1183,  1532,  1172,    88,  1184,  2593,  2604,   965,
      90,    91,   714,   715,   716,   717,   654,  2162,  2163,  2542,
       7,   401,  2460,   287,   712,   282,   402,   403,  1926,  1121,
     295,   358,  1183,   359,   405,  1533,  1703,     8,   660,  2626,
     103,   104,   105,   106,   107,   108,   710,   281,  2165,   282,
     358,   711,   359,   319,   721,  1171,   287,   821,   282,  1701,
    2394,   713,     9,    10,   163,   728,  2197,  1292,  1338,   714,
     715,   716,   717,   376,   731,   731,   565,   822,   326,   964,
    2543,   712,  2192,   939,  2421,  2422,  1153,  1131,   698,   406,
     320,  2430,   407,   966,  2527,   751,   749,   750,   710,   327,
      11,   857,    12,   711,    13,   526,   653,  2458,  2422,  1255,
     290,  2198,   734,  2479,  1496,    14,  1244,   661,  1917,   401,
     484,  1122,   779,  2324,   402,   403,  2561,  1142,  2199,  1249,
     655,   377,   405,   712,   653,  2493,   791,  2468,   103,   104,
     105,   106,   107,   108,    15,   748,    16,    17,    18,   527,
     593,    19,  1112,   164,   895,  1927,    20,    21,   825,  2594,
    2605,   638,  1339,   639,   648,   165,  1068,  1069,  1070,  1071,
    1072,   283,  1073,  1074,  2228,  1077,  1079,   841,  1081,  1082,
    1364,   724,   321,   896,  1723,  2706,  1573,   406,  2708,  2193,
     407,   649,   897,  1569,   554,   283,   554,   554,  1570,   940,
     554,   554,   863,  1173,   283,  1185,   710,  1497,  2229,  2535,
    1324,   711,  1498,  1852,   366,  1149,   294,  1171,  1270,  2431,
    2529,  1702,   771,  1614,  1615,   906,   643,  1340,  1893,   714,
     715,   716,   717,  1154,   291,  1185,   784,  2234,  2230,   773,
    2235,   712,  1901,  2498,  1918,  2143,  2194,   307,  2200,  2201,
    2202,  2031,  2499,  2325,  1076,  2423,  2496,  1853,  1173,  1251,
    1919,  1252,   775,  1319,  2436,   798,  1211,  2469,  1920,   777,
     650,   364,  2358,  1676,  1534,   963,  1241,   674,  2423,  2359,
    1242,  2596,  1078,    22,  2536,   651,  1996,  1229,  1230,  2144,
    1220,  2385,  2386,  1795,   824,  1256,   656,  2387,   324,  2354,
    1546,  1732,  2150,  2328,  2100,  2355,  1341,  1535,  1536,   640,
     657,   658,  2490,  1746,  2424,  1957,  1499,   795,   562,   528,
     675,   676,   677,   678,   679,   680,  2546,  1789,  1727,  1353,
    1342,  1174,  1175,   542,   308,   785,    88,  2459,   355,  1155,
     557,    90,    91,   925,  2022,  1573,  2151,  2513,  1753,  1978,
    2022,   888,  1569,  2525,  2422,  1610,   937,  1570,  1325,  1271,
     786,   761,  1343,   898,   899,   900,  1525,  2607,  2608,  1958,
     726,   949,   950,   951,   952,   953,   954,   727,  1811,  2206,
    2207,  1067,   958,  2208,  2209,  2210,  1174,  1175,  1741,  1812,
    1096,   529,   530,   328,   329,   330,  1221,   621,  1167,   969,
     970,   971,   972,   973,   974,   975,   976,   977,   978,   979,
     980,   981,   982,  2153,  1500,  1677,   731,  2035,  2278,  2037,
    1173,  1114,  2039,  1491,  2042,  2044,  1119,  2203,  1124,  1742,
    2679,  2680,   591,  1378,   622,  1034,   531,   532,   533,   762,
     590,  2694,  2695,   633,    23,    24,   288,   289,   292,   293,
     401,  1274,  2279,   356,  1743,   402,   403,  2154,   323,  1526,
     710,  1857,  1501,   405,  1129,   711,  1146,  1147,   309,   103,
     104,   105,   106,   107,   108,  1275,   803,  1537,   332,  1502,
     634,  1503,  1538,   804,  1539,  1504,   357,   710,  1098,  1505,
    1506,  1035,   711,   375,  1089,   712,  1884,  2269,  2314,  1109,
    1187,  1379,  1380,  1190,  2315,  1858,  1111,  1885,  1886,  1282,
     714,   715,   716,   717,   333,   334,   365,  1212,   406,   368,
    1850,   407,   712,   561,  2423,  2312,   623,  2160,  1573,  1859,
     378,   560,  2102,  1283,  2110,  1569,   379,    88,  1447,  1750,
    1570,  1225,    90,    91,  1851,  1882,  2108,  1855,  1174,  1175,
    1889,   731,   731,   502,  2280,  2281,  2382,   555,  1580,  2122,
    2126,  1581,   593,   593,  2070,  2071,  1238,  1515,   592,   562,
    1238,  1856,   635,   701,  1238,   702,  1678,   554,   703,  1516,
     710,  2122,  2126,  2526,   557,   711,  1679,  2141,  1680,   697,
    1681,   959,   960,  1682,  1344,  2161,  1346,   369,   370,   371,
     333,   334,   591,  2146,   792,   793,  1262,   794,   705,  1264,
     590,  2142,  1381,  1382,   790,   712,  1383,  1267,   563,  1328,
    1329,  1330,  1331,  2127,  1333,  1334,  2337,  2147,  1345,   567,
    1347,  1887,  1348,  1349,   576,  2244,  2245,   961,  2338,  1090,
     865,   333,   334,  2247,  2248,  2135,   577,  2162,  2163,  2164,
     764,   401,   381,   765,  1952,  1930,   402,   403,   574,  1236,
    1517,  1962,  1485,  1953,   405,  2476,   638,  1091,   639,   397,
     103,   104,   105,   106,   107,   108,   864,   865,  2165,   382,
    1313,  1623,   720,  1931,  1932,  1624,  1625,   575,  1312,   864,
     865,  1092,   558,   559,  2339,  2340,   866,  2128,    86,  2166,
    2136,   867,  2167,  2168,  1716,   578,  2128,  2136,  2251,   866,
     383,   737,   738,  2253,   867,  2254,   872,  1715,  2256,   406,
     745,   545,   407,   579,  2341,  1734,   546,   630,   631,   868,
    2441,   580,    87,  1486,   865,   869,   547,  1278,   548,  1279,
    1527,   921,    88,  1085,    89,  1086,   401,    90,    91,   545,
     780,   402,   403,   581,   546,   788,   549,   582,  2169,   405,
     358,  1487,   359,  2283,   547,  2442,   548,  1667,  1573,   813,
     602,   384,  2389,    92,   701,  1569,   702,   823,   603,   703,
    1570,   873,   558,  1354,   549,  2024,   385,   768,   769,   617,
     618,  2342,  2361,   619,  1528,   839,  1362,   710,   842,   620,
    1783,   845,   711,  1791,  2343,  1397,   625,   704,  1373,   705,
    1374,   852,  1937,   627,   406,  1361,  1303,   407,  1304,   632,
     714,   715,   716,   717,  2362,   809,   810,  1396,  1405,   637,
     558,   559,   712,  1166,   874,   710,  1352,  1686,  1407,  1408,
     711,  1410,  1411,    93,  2443,    94,    95,  1488,    96,   910,
      97,   912,  1420,   644,   792,   793,    98,   794,    99,   100,
     101,   646,   102,  1305,   550,  1306,   551,   853,   854,  1432,
     712,  1433,  1125,  1126,  1127,   103,   104,   105,   106,   107,
     108,  1436,  2444,  1437,   859,   860,  1440,  1441,  2445,  1443,
    2186,  1445,   550,   653,   551,  1626,   386,  1628,  1061,   387,
    1085,  1785,  1644,  1430,  1458,  1115,  1116,  1492,  2446,  1461,
     652,  1656,  1523,  1530,  1541,   333,   334,   554,  1494,   874,
     554,  1733,  1495,  2222,  2223,   926,   927,   109,  2683,  2684,
    2685,  2686,  2687,   110,  1522,  1529,  1540,  1653,   663,   111,
     112,  2631,  2632,  2633,  2162,  2163,  2363,   561,   559,   388,
    1762,   664,  1551,   389,   390,   560,  1928,  1389,  2558,  1934,
    1905,  1577,  1906,   558,   559,   665,  1166,   792,   793,   710,
     794,  1649,  1650,  1062,   711,  2165,  2571,  2046,  2572,  2047,
     666,  1518,  1519,   710,   667,  1520,   391,   668,   711,   296,
    1521,   297,   714,   715,   716,   717,   669,  2364,  2365,  1489,
    1490,  2366,  1369,  1370,   712,   504,   714,   715,   716,   717,
     392,   710,   792,   793,   393,   794,   711,  1250,   712,  1371,
    1372,   298,  2344,  2190,  2345,  2346,   670,  2698,   299,  2347,
    2348,   671,  2349,  2616,   683,  1237,  2367,  1611,  1612,  2368,
    2350,  2351,  1429,  1063,  1431,   688,   712,  1390,  1903,  1904,
    2369,   505,   506,   864,   865,  2370,   507,  1910,  1911,  1064,
    1065,   300,   394,   710,  2003,  2004,   301,   508,   711,  1583,
    1135,  1066,  1632,   866,   302,   325,   509,  1591,   867,  1592,
    1593,  1594,  1595,  2371,  1875,   687,   710,   689,  1399,   303,
    1604,   711,  1945,   868,  1400,  1641,  1607,  1457,   712,   869,
    1156,  1157,   690,  1159,  2271,  2272,  2372,  1167,   691,   714,
     715,   716,   717,   310,   692,   792,   793,  1688,  1784,  1186,
     359,   712,   694,   558,   559,  1192,  1166,  1194,   699,  1196,
    1197,  1914,  1199,  1200,  1201,  1202,  1203,  1204,  2122,  2123,
    1207,   591,  1209,   311,  2417,  2418,  1214,  1215,   700,   590,
    2162,  2163,   707,  1763,  1219,  1222,   722,  1763,  1223,   725,
     -68,   -68,  1226,   -68,  1692,   730,   312,   735,   313,   741,
     314,   740,   401,  1876,  1877,  2373,  1878,   402,   403,  1729,
    1736,  1401,  2438,  2439,   742,   405,  1735,   583,   584,   169,
     585,   586,   587,  2573,  2574,  1243,  2589,  2590,  2374,  2406,
    2407,   743,   304,   744,  1921,  1922,   752,   753,  1248,   583,
     584,   926,   927,   586,   587,   503,  2375,  1573,   754,  2656,
     756,  2714,   588,  1260,  1569,  1261,  1777,   757,  1786,  1570,
    1779,   758,  1693,   759,  2222,  2223,   926,   927,   760,  2716,
     406,   864,   865,   407,   588,   763,   766,   315,   316,   317,
     318,   767,   778,  2376,  2377,  2378,  2379,   781,  2380,   718,
     782,   866,  2381,   504,   783,   802,   867,   801,   113,  2224,
      88,   805,   806,  1813,   807,    90,    91,  2006,  2007,  2008,
     808,   872,   811,  2075,   812,   814,  1694,   815,   816,   305,
    1880,   818,  2733,   817,  2009,  2010,  2011,   819,  1879,   401,
     492,   826,   827,   710,   402,   403,  2051,  2052,   711,   505,
     506,   830,   405,   306,   507,  1402,  1403,  1022,  1023,  1024,
     828,   831,  1404,  1466,   829,   508,   714,   715,   716,   717,
     833,   589,  1695,   834,   509,   835,  1696,   836,   712,  1697,
    1698,  1025,  1026,  1467,   837,  1027,   840,  1874,   731,   843,
     846,  1798,  1798,   928,  1802,   844,   849,   855,  1803,  1804,
    2118,   850,   851,   858,  -898,  1798,  1866,   406,  1867,  1896,
     407,  1176,  1177,  1178,  1179,  1180,  2221,   861,  2012,  2013,
    1817,   862,  1818,   874,   401,  2222,  2223,   926,   927,   402,
     403,   504,   876,   877,   878,   731,  1915,   405,  1308,  1309,
    1310,  1311,  1468,   103,   104,   105,   106,   107,   108,   879,
     880,   583,   584,   926,   927,   586,   587,   493,   891,   881,
    2224,  1758,  1759,  1760,  1761,  2176,   882,   883,   473,    88,
     884,   890,   892,  1390,    90,    91,   893,  1469,  1470,  1939,
    1940,   903,   507,   905,  1943,  2717,  1296,  2225,  2720,  2721,
     907,  1947,   406,   508,  1948,   407,   908,   909,    88,   474,
    2722,   911,   509,    90,    91,   913,  1414,  1416,   914,   583,
     584,   926,   927,   586,   587,   915,  1424,   916,  1426,  1964,
    1763,  1966,  2025,   919,   494,  2728,  2729,   920,  1393,  1970,
    2730,  2731,   558,   885,   886,   887,   932,   935,  2006,  2007,
    2008,  2179,  2180,  2181,   588,   710,   933,  1471,   495,  1472,
     711,  1473,   934,   938,   619,  2009,  2010,  2011,   941,  1983,
     942,   943,   177,  1456,   962,  1990,  1991,   180,   181,  1992,
     510,  1463,  2014,   787,   967,   968,  1993,  1994,  2014,  1030,
     712,  1031,  1032,   401,  1033,  1038,    88,  1040,   402,   403,
    1041,    90,    91,  1080,  1083,  1084,   405,  1087,  1513,  1088,
    1094,  1097,   103,   104,   105,   106,   107,   108,  1099,  1105,
     731,   731,   401,  1552,  1553,  1104,   517,   402,   403,  1106,
    1110,  1394,  1113,  1130,  2060,   405,  1117,  1158,  1140,  1972,
    1141,   103,   104,   105,   106,   107,   108,  1143,  1144,  2012,
    2013,  2276,  1145,  1987,  1150,  1989,  2257,  1160,  1151,  1161,
     710,   406,  1474,  1162,   407,   711,  1163,  1165,  2258,  1169,
    1195,  1475,  1476,  2259,  1198,  1188,  2059,   475,  1477,  1208,
    1189,  1191,  1478,   714,   715,   716,   717,  1193,  2260,  2033,
     406,  1479,  1205,   407,  1224,   712,  2130,  2131,  2132,  2133,
    1480,   710,  1481,  1206,  1210,  1482,   711,  1213,  1231,  1232,
     401,  2096,  1233,  1240,   895,   402,   403,  1259,  1263,  1268,
    1272,  1415,  1273,   405,   714,   715,   716,   717,  1277,   103,
     104,   105,   106,   107,   108,  1290,   712,  1167,  1167,  1293,
     496,   497,   498,  2688,  2689,  2690,  2691,  2692,  1295,  1647,
    1648,  1300,  1302,  2226,  1307,  1301,  1321,  1326,  1322,  1276,
    1323,  1395,  1332,  2121,  1355,  1357,  1363,  2104,  1365,  2129,
    1368,   591,   591,  1376,  1377,  1385,  1387,  1388,   406,   590,
     590,   407,  1419,  1409,  1412,  2538,  1687,  2597,  2598,  1413,
    1418,   518,  1421,  1578,  2599,  2600,  2601,  2602,  1422,  2261,
    1548,  1423,  1425,   519,  1434,  1438,  1439,  1442,  2162,  2163,
    1511,  1444,  1446,  1448,  1449,   731,   731,   731,  1450,  1798,
    1451,  1452,  1453,  1454,  1455,  1459,  2183,  1460,  1462,  2106,
    2448,  2449,  2450,  2451,  2452,  2453,  2454,  2455,  1464,  2165,
    1465,  1514,  1544,  1545,  1547,  1724,  1575,  1726,  1728,  1582,
    1730,  1584,  1585,  1605,  1606,   476,   477,   478,   479,  1603,
    1613,  2262,  2263,  1616,  1617,  2264,  1618,  1744,  2240,  1747,
    1619,  2014,  1620,  2014,  1754,  1621,  1627,  1622,  1629,  1630,
    1631,  1642,  1643,   480,  1645,  1646,  1651,  1652,   481,  1669,
    1657,   482,  2155,  1660,   483,  1776,  1661,  1670,  1671,  1672,
    1673,  2265,  2266,  2267,   520,   605,   606,   607,   608,   609,
    1714,  1720,  2581,  2582,  2284,   731,  2277,  2584,  2585,  2268,
    1674,  2588,   610,   611,   612,   613,   614,   615,   616,   617,
     618,  1675,  1685,   619,  1689,  1690,  1691,  1700,  1713,  1704,
    1705,  2318,  1706,   983,   984,  2321,  2322,  1707,  2326,  1708,
    2329,   985,  1709,  1819,  1710,  1711,  1712,  2236,  2237,  2238,
    1719,  2239,  1820,  1821,  1822,  1823,  1717,  1824,  1825,  1826,
    1725,  1718,  1827,  1731,  1828,  1829,  1721,   986,  1737,   987,
    1830,  1831,  1738,  1755,  1749,  1832,  1756,  2675,  2676,  1772,
    2402,  1773,  2403,  2404,  2405,  1778,  1001,  1780,  1782,  1792,
    1980,  1002,  1003,  1794,  1801,  2415,   988,  1806,  1807,  2419,
    1808,  1809,  1815,  2427,  1816,  1854,   989,   990,  1860,   991,
     992,   993,   994,   995,  2658,  1763,  1861,  1863,  2699,  1864,
     996,   997,   998,  1865,   999,  1000,  1868,  1895,  1870,  2456,
    1871,  1872,  2226,  2226,  1890,  2464,  2465,  1873,  1898,  1907,
    1899,  2472,  1897,  2474,  1883,  2477,  1902,  2480,  1942,  1908,
      88,  1909,  1912,  2484,  1913,    90,    91,  1916,  2391,  1944,
    1946,  1936,  1949,  1950,  1935,  2486,  2487,  2395,  1982,  2488,
    2489,  1965,  1923,  1924,  1925,  1532,  1971,  1929,  1976,  1963,
     400,  1973,  1977,  1988,  1998,  1999,  2002,  2005,  2289,  -899,
    -899,  -899,  2514,  2019,  2027,  2032,  2514,  2034,  2038,  2522,
    2040,  1941,  2045,  2290,  2048,  2530,  -899,  -899,  -899,  -899,
    -899,   615,   616,   617,   618,  2050,  2547,   619,  2555,  1004,
    1005,  1006,  1007,  1008,  1009,  2053,  2061,  2063,  2065,  2077,
    1961,  2064,  2082,  2078,   339,   340,   341,   342,   343,   344,
     345,   346,   347,  2076,   348,   349,   350,   351,   352,   353,
    2090,  2067,  2068,  2069,  2101,  2113,  2094,  2105,  2575,  2576,
    2577,  2578,  2579,  2098,   401,  2114,   731,   731,  2115,   402,
     403,   731,   731,   404,  2116,   731,  2117,   405,  2119,  2120,
    2137,  2595,  2125,   103,   104,   105,   106,   107,   108,  2139,
    2140,  2145,  2148,  2156,  2149,  2609,  2610,  2611,  2152,  2219,
    2220,  2246,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1019,  1020,  2618,  2619,  2177,  2249,  2250,  2252,  2622,
    2255,  2274,  2275,  2162,  2163,  2285,  2287,  2320,  2327,  2330,
    2628,  2564,   406,  2336,  2635,   407,  2392,  2638,  2639,  2396,
    2397,  2055,  2642,  2643,  2331,  2408,  2409,  2332,  2410,  2411,
    2412,  2649,  2413,  2416,  2165,  2414,  2420,   408,  2432,  2428,
    2440,  2426,  2650,  2651,  2652,  2429,  2433,  2461,  2462,  2655,
    2434,  2437,  2291,  2457,  2463,  2471,  2292,  2293,   731,  2659,
    2294,  2295,  2660,  2661,  2481,  2475,  2483,  2485,  2494,  2470,
    2501,  2482,  2503,  2079,  2080,  2504,  2500,  2511,  2507,  2509,
    2517,  1957,  2521,  2531,  2505,  2524,  2506,  2671,  2672,  2548,
    2296,  2540,  2539,  2541,  2544,  2551,  2545,  2297,  2549,  2554,
    2550,  2556,  2298,  2097,  2553,  2563,   605,   606,   607,  2299,
    2565,  2566,  2567,  2568,  2300,  2569,  2570,  2301,   605,   606,
     607,   608,   609,   610,   611,   612,   613,   614,   615,   616,
     617,   618,  2586,  2583,   619,   610,   611,   612,   613,   614,
     615,   616,   617,   618,  2587,  2703,   619,  2704,  2705,  2591,
    2606,  2613,  2627,  2629,  2630,  2707,  2637,  2644,  2640,  2666,
    2624,  2667,  2710,  2673,  2674,  2302,  2669,  2678,  2681,  2682,
    2693,  2701,  2668,  2715,  2718,  2711,  2727,  2712,  2713,   605,
     606,   607,   608,   609,  2719,  2723,  1981,  2724,  2725,  2732,
    2734,  1793,  2303,  1314,  1315,  1316,   610,   611,   612,   613,
     614,   615,   616,   617,   618,  2242,  1840,   619,  1841,  1842,
    2028,  1843,  2243,  2241,  2029,  2182,  2030,  1510,  1974,  1633,
     947,  1869,   944,  1297,  2559,   572,  2560,  1298,   512,   929,
    1299,  2304,  1483,   848,  2305,  2306,  2307,  1227,  1655,  1608,
    1609,  2696,  2308,  2677,  1665,  2159,   945,  2309,  2056,  1435,
    1039,  2066,  2074,  2085,  2636,  2184,  2491,  2310,  2646,  2516,
    2520,  1967,  2648,  2311,   166,  2519,   167,   168,   169,   170,
     171,   172,     0,   173,  1375,  1042,     0,  1350,  1095,     0,
       0,   174,   175,   955,  1257,     0,   176,     0,     0,   558,
     885,   886,   887,     0,     0,     0,     0,     0,   177,   178,
       0,   179,  2273,   180,   181,     0,     0,   182,     0,     0,
       0,     0,     0,     0,     0,  2288,     0,     0,     0,   177,
       0,     0,     0,     0,   180,   181,     0,     0,     0,     0,
    2317,     0,  2319,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2333,  2334,  2335,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     183,   184,   568,   569,   570,   571,   185,   186,     0,   187,
     188,   189,   190,   191,   192,   193,   194,   195,  1043,  1044,
       0,     0,     0,     0,     0,     0,   196,   197,   198,     0,
       0,   199,     0,     0,     0,     0,     0,     0,     0,   200,
       0,     0,     0,     0,     0,     0,     0,   201,     0,   202,
     605,   606,   607,   608,   609,     0,     0,     0,     0,     0,
    1045,   865,     0,     0,     0,     0,     0,   610,   611,   612,
     613,   614,   615,   616,   617,   618,  1046,  2466,   619,     0,
    1047,     0,  2473,  1048,  1049,     0,     0,     0,  1050,     0,
       0,     0,     0,  1587,  1819,     0,     0,     0,     0,     0,
       0,     0,     0,  1820,  1821,  1822,  1823,  1051,  1824,  1825,
    1826,     0,     0,  1827,     0,  1828,  1829,  1588,     0,     0,
       0,  1830,  1831,  2502,     0,     0,  1839,   203,     0,     0,
    1052,  1053,  1054,     0,     0,  1055,  1056,  1057,     0,     0,
       0,  2523,   605,   606,   607,   608,   609,  2532,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   610,
     611,   612,   613,   614,   615,   616,   617,   618,     0,     0,
     619,     0,     0,   605,   606,   607,   608,   609,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
     610,   611,   612,   613,   614,   615,   616,   617,   618,     0,
       0,   619,     0,     0,  2580,     0,     0,     0,     0,  1285,
     605,   606,   607,   608,   609,     0,     0,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   610,   611,   612,
     613,   614,   615,   616,   617,   618,     0,     0,   619,  2612,
    1286,     0,     0,     0,   215,   216,     0,     0,  2615,  2617,
       0,     0,     0,     0,     0,     0,  2620,  2621,     0,     0,
    2623,   166,     0,   167,   168,   169,   170,   171,   172,     0,
     173,     0,     0,     0,   217,     0,     0,  1287,   174,   175,
       0,  2641,     0,   176,     0,  2645,     0,  2647,     0,   218,
       0,     0,     0,     0,     0,   177,   178,     0,   179,     0,
     180,   181,     0,     0,   182,     0,  2653,  2654,     0,     0,
     219,   220,   221,   222,     0,     0,     0,  2657,     0,   605,
     606,   607,   608,   609,  2662,     0,  2663,  2664,  2665,     0,
       0,     0,     0,     0,     0,     0,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   183,   184,   568,
     569,   570,   571,   185,   186,     0,   187,   188,   189,   190,
     191,   192,   193,   194,   195,     0,     0,     0,     0,     0,
       0,     0,     0,   196,   197,   198,  1288,     0,   199,     0,
       0,  2697,   223,   224,     0,     0,   200,     0,     0,     0,
       0,     0,  2702,     0,   201,     0,   202,     0,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,  2709,     0,
       0,     0,     0,     0,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,     0,     0,     0,     0,     0,   605,   606,   607,
     608,   609,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   255,   256,     0,   610,   611,   612,   613,   614,   615,
     616,   617,   618,     0,   203,   619,   605,   606,   607,   608,
     609,     0,     0,     0,     0,     0,     0,     0,   605,   606,
     607,   608,   609,   610,   611,   612,   613,   614,   615,   616,
     617,   618,     0,     0,   619,   610,   611,   612,   613,   614,
     615,   616,   617,   618,  1586,     0,   619,     0,     0,     0,
     166,     0,   167,   168,   169,   170,   171,   172,     0,   173,
       0,  1269,     0,     0,     0,     0,   204,   174,   175,  1596,
       0,     0,   176,  1845,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   177,   178,     0,   179,     0,   180,
     181,     0,     0,   182,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,     0,     0,     0,     0,   605,   606,
     607,   608,   609,     0,     0,     0,     0,     0,     0,     0,
       0,   215,   216,     0,     0,   610,   611,   612,   613,   614,
     615,   616,   617,   618,     0,     0,   619,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   183,   184,     0,     0,
       0,   217,   185,   186,     0,   187,   188,   189,   190,   191,
     192,   193,   194,   195,     0,     0,   218,     0,     0,     0,
       0,     0,   196,   197,   198,  1975,     0,   199,     0,   605,
     606,   607,   608,   609,     0,   200,     0,   219,   220,   221,
     222,     0,     0,   201,     0,   202,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,   605,   606,
     607,   608,   609,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1284,     0,     0,   610,   611,   612,   613,   614,
     615,   616,   617,   618,     0,     0,   619,   605,   606,   607,
     608,   609,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1289,     0,     0,   610,   611,   612,   613,   614,   615,
     616,   617,   618,     0,     0,   619,     0,     0,     0,   223,
     224,     0,     0,   203,     0,     0,     0,     0,     0,     0,
    1294,     0,     0,     0,     0,   225,   226,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,     0,
       0,     0,     0,     0,     0,   204,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   255,   256,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,     0,     0,   166,     0,   167,   168,   169,
     170,   171,   172,     0,   173,     0,     0,     0,     0,     0,
     215,   216,   174,   175,  1600,     0,     0,   176,     0,     0,
       0,     0,     0,     0,   605,   606,   607,   608,   609,   177,
     178,     0,   179,     0,   180,   181,     0,     0,   182,     0,
     217,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,     0,   218,     0,     0,   339,   340,
     341,   342,   343,   344,   345,   346,   347,  1366,   348,   349,
     350,   351,   352,   353,     0,     0,   219,   220,   221,   222,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   183,   184,     0,     0,     0,     0,   185,   186,     0,
     187,   188,   189,   190,   191,   192,   193,   194,   195,     0,
       0,     0,     0,     0,     0,     0,     0,   196,   197,   198,
       0,     0,   199,     0,   605,   606,   607,   608,   609,     0,
     200,     0,     0,     0,     0,     0,     0,     0,   201,     0,
     202,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,     0,   604,     0,     0,   223,   224,
     605,   606,   607,   608,   609,     0,     0,  1367,     0,     0,
       0,     0,     0,     0,   225,   226,     0,   610,   611,   612,
     613,   614,   615,   616,   617,   618,     0,     0,   619,     0,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   203,     0,
       0,     0,   605,   606,   607,   608,   609,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   255,   256,   610,
     611,   612,   613,   614,   615,   616,   617,   618,     0,     0,
     619,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   166,  1846,   167,   168,   169,   170,
     171,   172,     0,   173,     0,     0,     0,     0,     0,     0,
     204,   174,   175,  2036,     0,     0,   176,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   177,   178,
       0,   179,     0,   180,   181,     0,     0,   182,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,     0,     0,
     605,   606,   607,   608,   609,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,   216,   610,   611,   612,
     613,   614,   615,   616,   617,   618,     0,     0,   619,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     183,   184,     0,  1847,     0,   217,   185,   186,     0,   187,
     188,   189,   190,   191,   192,   193,   194,   195,     0,     0,
     218,     0,     0,     0,     0,     0,   196,   197,   198,     0,
       0,   199,     0,   605,   606,   607,   608,   609,     0,   200,
       0,   219,   220,   221,   222,     0,     0,   201,     0,   202,
     610,   611,   612,   613,   614,   615,   616,   617,   618,     0,
       0,   619,   605,   606,   607,   608,   609,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1848,     0,     0,   610,
     611,   612,   613,   614,   615,   616,   617,   618,     0,     0,
     619,   605,   606,   607,   608,   609,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1849,     0,     0,   610,   611,
     612,   613,   614,   615,   616,   617,   618,     0,     0,   619,
       0,     0,     0,   223,   224,     0,     0,   203,     0,     0,
       0,     0,     0,     0,  1862,     0,     0,     0,     0,   225,
     226,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,     0,     0,     0,     0,     0,     0,   204,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,     0,     0,   166,
       0,   167,   168,   169,   170,   171,   172,     0,   173,     0,
       0,     0,     0,     0,   215,   216,   174,   175,  2041,     0,
       0,   176,     0,     0,     0,     0,     0,     0,   605,   606,
     607,   608,   609,   177,   178,     0,   179,     0,   180,   181,
       0,     0,   182,     0,   217,   610,   611,   612,   613,   614,
     615,   616,   617,   618,     0,     0,   619,     0,     0,   218,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2000,     0,     0,     0,     0,     0,     0,     0,     0,
     219,   220,   221,   222,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   183,   184,     0,     0,     0,
       0,   185,   186,     0,   187,   188,   189,   190,   191,   192,
     193,   194,   195,     0,     0,     0,     0,     0,     0,     0,
       0,   196,   197,   198,     0,     0,   199,     0,   605,   606,
     607,   608,   609,     0,   200,     0,     0,     0,     0,     0,
       0,     0,   201,     0,   202,   610,   611,   612,   613,   614,
     615,   616,   617,   618,     0,     0,   619,     0,     0,     0,
       0,     0,   223,   224,   605,   606,   607,   608,   609,     0,
       0,  2001,     0,     0,     0,     0,     0,     0,   225,   226,
       0,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   203,     0,     0,     0,   605,   606,   607,   608,
     609,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   255,   256,   610,   611,   612,   613,   614,   615,   616,
     617,   618,     0,     0,   619,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,  2138,
     167,   168,   169,   170,   171,   172,     0,   173,     0,     0,
       0,     0,     0,     0,   204,   174,   175,  2043,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   177,   178,     0,   179,     0,   180,   181,     0,
       0,   182,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,     0,     0,   605,   606,   607,   608,   609,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
     216,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   183,   184,     0,  2398,     0,   217,
     185,   186,     0,   187,   188,   189,   190,   191,   192,   193,
     194,   195,     0,     0,   218,     0,     0,     0,     0,     0,
     196,   197,   198,     0,     0,   199,     0,   605,   606,   607,
     608,   609,     0,   200,     0,   219,   220,   221,   222,     0,
       0,   201,     0,   202,   610,   611,   612,   613,   614,   615,
     616,   617,   618,     0,     0,   619,   605,   606,   607,   608,
     609,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2399,     0,     0,   610,   611,   612,   613,   614,   615,   616,
     617,   618,     0,     0,   619,   605,   606,   607,   608,   609,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2400,
       0,     0,   610,   611,   612,   613,   614,   615,   616,   617,
     618,     0,     0,   619,     0,     0,     0,   223,   224,     0,
       0,   203,     0,     0,     0,     0,     0,     0,  2401,     0,
       0,     0,     0,   225,   226,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,     0,     0,
       0,     0,     0,   204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,     0,     0,   166,     0,   167,   168,   169,   170,   171,
     172,     0,   173,     0,     0,     0,     0,     0,   215,   216,
     174,   175,     0,     0,     0,   176,     0,     0,     0,     0,
       0,     0,   605,   606,   607,   608,   609,   177,   178,     0,
     179,     0,   180,   181,     0,     0,   182,     0,   217,   610,
     611,   612,   613,   614,   615,   616,   617,   618,     0,     0,
     619,     0,     0,   218,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2557,     0,     0,     0,     0,
       0,     0,     0,     0,   219,   220,   221,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   183,
     184,     0,     0,     0,     0,   185,   186,     0,   187,   188,
     189,   190,   191,   192,   193,   194,   195,     0,     0,     0,
       0,     0,     0,     0,     0,   196,   197,   198,     0,     0,
     199,     0,   605,   606,   607,   608,   609,     0,   200,     0,
       0,     0,     0,     0,     0,     0,   201,     0,   202,   610,
     611,   612,   613,   614,   615,   616,   617,   618,     0,     0,
     619,     0,     0,     0,     0,     0,   223,   224,     0,     0,
       0,     0,     0,     0,     0,  2670,     0,     0,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   203,     0,     0,     0,
     605,   606,   607,   608,   609,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   255,   256,   610,   611,   612,
     613,   614,   615,   616,   617,   618,     0,     0,   619,   605,
     606,   607,   608,   609,     0,     0,     0,     0,     0,     0,
       0,  1356,     0,     0,     0,     0,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,   204,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1554,     0,
    1979,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   178,     0,     0,     0,
       0,     0,     0,     0,   182,     0,     0,     0,     0,     0,
       0,     0,     0,   215,   216,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1555,     0,     0,  1557,  1558,  1559,
    1560,  1561,  1562,  1563,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   217,   348,   349,   350,   351,   352,   353,
    1564,     0,     0,  1565,  1566,     0,     0,     0,   218,     0,
       0,     0,     0,   185,   186,     0,   187,   188,   189,   190,
     191,   192,   193,   194,     0,     0,     0,     0,     0,   219,
     220,   221,   222,     0,     0,     0,   605,   606,   607,   608,
     609,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1567,     0,  1568,   610,   611,   612,   613,   614,   615,   616,
     617,   618,     0,     0,   619,   605,   606,   607,   608,   609,
       0,     0,     0,     0,     0,     0,     0,  2099,     0,     0,
       0,     0,   610,   611,   612,   613,   614,   615,   616,   617,
     618,     0,     0,   619,     0,     0,   605,   606,   607,   608,
     609,     0,     0,     0,     0,     0,  2111,     0,     0,     0,
       0,   223,   224,   610,   611,   612,   613,   614,   615,   616,
     617,   618,     0,     0,   619,     0,     0,   225,   226,     0,
       0,     0,     0,     0,   203,     0,     0,  2112,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1360,     0,     0,
     255,   256,     0,     0,     0,     0,   204,   339,   340,   341,
     342,   343,   344,   345,   346,   347,  1554,   348,   349,   350,
     351,   352,   353,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   178,     0,     0,     0,     0,     0,
       0,     0,   182,     0,     0,     0,     0,     0,     0,     0,
       0,   215,   216,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1555,  1556,     0,  1557,  1558,  1559,  1560,  1561,
    1562,  1563,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   217,     0,     0,     0,     0,     0,     0,  1564,     0,
       0,  1565,  1566,     0,     0,     0,   218,     0,     0,     0,
       0,   185,   186,     0,   187,   188,   189,   190,   191,   192,
     193,   194,     0,     0,     0,     0,     0,   219,   220,   221,
     222,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1567,     0,
    1568,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   223,
     224,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   225,   226,     0,     0,     0,
       0,     0,   203,     0,     0,     0,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   255,   256,
       0,     0,     0,     0,   204,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1554,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   178,     0,     0,     0,     0,     0,     0,     0,
     182,     0,     0,     0,     0,     0,     0,     0,     0,   215,
     216,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1555,     0,     0,  1557,  1558,  1559,  1560,  1561,  1562,  1563,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,     0,     0,  1564,     0,     0,  1565,
    1566,     0,     0,     0,   218,     0,     0,     0,     0,   185,
     186,     0,   187,   188,   189,   190,   191,   192,   193,   194,
       0,     0,     0,     0,     0,   219,   220,   221,   222,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1567,     0,  1568,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   223,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   225,   226,     0,     0,     0,     0,     0,
     203,     0,     0,     0,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2107,     0,     0,   255,   256,     0,     0,
       0,     0,   204,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,     0,     0,     0,     0,     0,     0,     0,   182,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,   216,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   217,   185,   186,
       0,   187,   188,   189,   190,   191,   192,   193,   194,     0,
       0,     0,   218,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   219,   220,   221,   222,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   223,   224,     0,     0,   203,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   225,   226,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,     0,     0,     0,     0,     0,
       0,   204,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   255,   256,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   215,   216,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   217,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   218,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   219,   220,   221,   222,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   417,   418,
       0,     0,     0,     0,   223,   224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     225,   226,     0,   419,     0,     0,     0,     0,     0,     0,
       0,   420,     0,     0,     0,     0,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   421,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   255,   256,     0,     0,     0,     0,     0,
       0,   422,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   401,     0,     0,
       0,     0,   402,   403,     0,   423,   424,     0,     0,     0,
     405,   425,     0,     0,     0,     0,   426,   427,   428,   429,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   430,
       0,     0,     0,   431,     0,   432,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   406,     0,     0,   407,     0,
       0,     0,     0,     0,     0,     0,     0,   433,     0,     0,
       0,   434,     0,     0,     0,     0,     0,     0,     0,     0,
     435,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   436,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   437,
     438,   439,     0,   440,     0,     0,     0,   441,   203,     0,
     442,   443,     0,   444,   445,     0,     0,   446,   447,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   448,   449,     0,     0,     0,   450,   451,
     452,     0,     0,     0,     0,     0,     0,   453,     0,     0,
       0,   454,     0,     0,   455,   456,     0,   457,     0,   458,
       0,     0,     0,   459,   460,     0,     0,     0,     0,     0,
     204,     0,     0,     0,     0,   461,     0,     0,     0,     0,
       0,     0,     0,   462,   463,     0,     0,     0,     0,     0,
       0,     0,     0,   464,     0,     0,   465,   466,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,   216,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     218,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   219,   220,   221,   222,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   223,   224,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   225,
     226,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   255,   256
};

static const yytype_int16 yycheck[] =
{
     109,     7,   202,   439,   440,   202,  1258,   286,   171,    95,
    1258,   377,   145,  1258,   576,   166,   171,   506,  1258,   476,
     747,    87,   155,   156,   306,   518,    92,    93,   139,    23,
     795,    25,   143,    80,   145,   545,   147,   547,   548,   202,
     289,   551,   552,    88,   155,   156,    25,   202,   799,    80,
     645,   162,    21,    50,    23,  1290,  1291,  1292,  1293,   134,
    1045,   136,    80,   138,   645,   140,    23,   142,    67,   144,
       3,     4,     5,   148,   323,   150,    18,   152,    80,   154,
      80,    23,   361,   362,  2103,   160,   161,  1558,    94,    80,
     128,   686,    20,    21,   128,    23,    18,    80,    88,    50,
    1571,    23,   206,   207,    23,  1090,    25,    50,  1360,    18,
       6,    53,    55,    56,    23,  1360,    50,   164,  2103,    87,
    1360,   225,   169,   170,   403,   170,   173,    23,  1520,   126,
     177,    53,    41,    42,    43,    44,    18,    80,  1807,    50,
      18,    23,    18,   176,    53,    23,    50,    23,  2103,    51,
       6,  2274,   645,  2221,    20,    21,    37,    23,    18,   248,
      34,  1060,   258,    23,    25,    41,    42,    43,    44,    65,
     176,    53,    80,   179,     0,    53,   142,    53,    78,   212,
       3,    41,    42,    43,    44,   232,   326,   176,   235,    18,
      23,   339,    25,    53,    23,    78,   172,     7,   251,    10,
      48,   176,    48,    48,    52,    50,    52,    51,    51,    78,
      55,    56,    41,    42,    43,    44,   173,   200,   201,   373,
     153,   164,  2293,    23,    53,    25,   169,   170,   248,    79,
     195,    23,    48,    25,   177,    80,    52,   170,   208,  2489,
     183,   184,   185,   186,   187,   188,    18,    23,   231,    25,
      23,    23,    25,    42,   366,    48,    23,   310,    25,    52,
     160,   363,   195,   196,     6,   374,   249,    78,   164,    41,
      42,    43,    44,   509,   376,   377,   150,   330,   257,   162,
     434,    53,   282,    34,    69,    70,   375,   744,   354,   232,
      79,   176,   235,   162,  2365,   407,   405,   406,    18,   278,
     233,   203,   235,    23,   237,   248,    23,    69,    70,   306,
     110,   294,   378,   461,    80,   248,   878,   287,   197,   164,
     143,   171,   431,   312,   169,   170,  2394,   763,   311,   891,
     287,   567,   177,    53,    23,   475,   438,   312,   183,   184,
     185,   186,   187,   188,   277,   178,   279,   280,   281,   292,
     550,   284,   718,     6,   322,   375,   289,   290,   460,   203,
     203,    23,   258,    25,   181,     6,   648,   649,   650,   651,
     652,   171,   654,   655,  2393,   657,   658,   479,   660,   661,
    1107,   242,   171,   351,   360,  2635,  1638,   232,  2638,   389,
     235,   208,   360,  1638,   545,   171,   547,   548,  1638,   150,
     551,   552,   504,   251,   171,   251,    18,   173,  2393,   442,
      23,    23,   178,    10,   206,   405,     6,    48,   928,   304,
     516,    52,   373,  1322,  1323,   527,   282,   323,   309,    41,
      42,    43,    44,   262,   234,   251,   245,  2106,  2393,   373,
    2109,    53,   408,   481,   323,    10,   446,     6,   431,   432,
     433,  1843,   490,   442,   171,   240,   490,    54,   251,   895,
     339,   897,   373,  1044,  2587,   393,   385,   442,   347,   373,
     287,   575,   490,    92,   319,    78,   872,   522,   240,   497,
     876,  2444,   171,   416,   517,   302,   488,   853,   854,    54,
     262,   522,   523,    28,   372,   492,   453,   528,   284,   490,
    1251,  1486,    10,   223,  1975,   496,   402,   352,   353,   171,
     467,   468,   481,   389,   299,    25,   282,   383,    53,   462,
     565,   566,   567,   568,   569,   570,   448,   526,   388,  1091,
     426,   379,   380,   580,     6,   344,    50,   299,    53,   368,
      36,    55,    56,   549,  1836,  1797,    54,   489,   457,  1801,
    1842,  1044,  1797,    69,    70,    51,   562,  1797,   171,   162,
     369,   249,   458,   531,   532,   533,    80,   449,   450,    79,
     564,   577,   578,   579,   580,   581,   582,   571,    28,   487,
     488,   647,   588,   491,   492,   493,   379,   380,   389,    39,
     692,   534,   535,   572,   573,   574,   368,    42,   795,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,    10,   380,   234,   718,  1852,   176,  1854,
     251,   723,  1857,  1218,  1859,  1860,   728,  2087,   730,   430,
    2593,  2594,   795,    80,    79,   180,   579,   580,   581,   327,
     795,  2604,  2605,    42,   577,   578,     9,    10,    11,    12,
     164,    54,   210,    53,   455,   169,   170,    54,    21,   173,
      18,    10,   428,   177,   739,    23,   768,   769,     6,   183,
     184,   185,   186,   187,   188,    78,   319,   522,     6,   445,
      79,   447,   527,   326,   529,   451,   165,    18,   694,   455,
     456,   236,    23,   195,     6,    53,   172,  2157,   446,   705,
     802,   148,   149,   805,   452,    54,   712,   183,   184,    54,
      41,    42,    43,    44,    23,    24,   189,   826,   232,   167,
      54,   235,    53,   886,   240,  2185,   171,    80,  1980,    78,
     179,   886,  1980,    78,  1986,  1980,   259,    50,  1195,  1504,
    1980,   843,    55,    56,    78,  1658,  1986,    54,   379,   380,
    1663,   853,   854,    79,   312,   313,  2216,    36,  1268,    14,
      15,  1271,   962,   963,   376,   377,   868,    80,   965,    53,
     872,    78,   171,    18,   876,    20,   395,   928,    23,    92,
      18,    14,    15,   299,    36,    23,   405,    54,   407,    98,
     409,    33,    34,   412,  1076,   148,  1078,   245,   246,   247,
      23,    24,   965,    54,    20,    21,   908,    23,    53,   911,
     965,    78,   259,   260,    52,    53,   263,   919,   150,  1068,
    1069,  1070,  1071,    78,  1073,  1074,    80,    78,  1077,    18,
    1079,   307,  1081,  1082,    53,  2127,  2128,    79,    92,   151,
     152,    23,    24,  2135,  2136,    78,    53,   200,   201,   202,
     317,   164,   172,   320,  1767,   323,   169,   170,    79,   865,
     173,  1774,    80,    79,   177,   223,    23,   179,    25,    51,
     183,   184,   185,   186,   187,   188,   151,   152,   231,   199,
    1043,  1338,   364,   351,   352,  1342,  1343,    79,  1043,   151,
     152,   203,    20,    21,   148,   149,   171,  2020,     6,   252,
    2023,   176,   255,   256,   179,    53,  2029,  2030,  2143,   171,
     230,   420,   421,  2148,   176,  2150,   191,   179,  2153,   232,
     402,    18,   235,    53,   178,  1487,    23,   290,   291,   191,
      51,    53,    40,   151,   152,   197,    33,   943,    35,   945,
     454,    10,    50,    78,    52,    80,   164,    55,    56,    18,
     432,   169,   170,    53,    23,   437,    53,    53,   311,   177,
      23,   179,    25,    26,    33,    86,    35,  1403,  2220,   451,
     149,   291,  2220,    81,    18,  2220,    20,   459,   149,    23,
    2220,  1470,    20,  1092,    53,    23,   306,   330,   331,    35,
      36,   245,    48,    39,   508,   477,  1105,    18,   480,    39,
    1536,   483,    23,  1539,   258,  1138,     6,    51,  1117,    53,
    1119,   493,  1739,    25,   232,  1101,    78,   235,    80,     6,
      41,    42,    43,    44,    80,   342,   343,  1138,  1139,     6,
      20,    21,    53,    23,    23,    18,    25,   368,  1140,  1141,
      23,  1143,  1144,   151,   165,   153,   154,   265,   156,   531,
     158,   533,  1154,     6,    20,    21,   164,    23,   166,   167,
     168,     6,   170,    78,   161,    80,   163,   148,   149,  1171,
      53,  1173,    45,    46,    47,   183,   184,   185,   186,   187,
     188,  1183,   203,  1185,   174,   175,  1188,  1189,   209,  1191,
      80,  1193,   161,    23,   163,  1344,   416,  1346,     6,   419,
      78,  1537,    80,  1169,  1206,   243,   244,  1218,   229,  1211,
     316,  1390,  1245,  1246,  1247,    23,    24,  1268,  1220,    23,
    1271,    25,  1224,    18,    19,    20,    21,   235,   212,   213,
     214,   215,   216,   241,  1245,  1246,  1247,  1386,   171,   247,
     248,   500,   501,   502,   200,   201,   202,  1310,    21,   469,
      23,     6,  1254,   473,   474,  1310,  1718,    80,    53,  1721,
      78,  1263,    80,    20,    21,     6,    23,    20,    21,    18,
      23,   264,   265,    81,    23,   231,  2411,    52,  2413,    54,
       6,   494,   495,    18,     6,   498,   506,     6,    23,   206,
     503,   208,    41,    42,    43,    44,     6,   253,   254,   417,
     418,   257,    46,    47,    53,   128,    41,    42,    43,    44,
     530,    18,    20,    21,   534,    23,    23,    25,    53,    46,
      47,   238,   476,    80,   478,   479,     6,    80,   245,   483,
     484,     6,   486,   254,    18,    42,   292,    20,    21,   295,
     494,   495,  1168,   151,  1170,     6,    53,   170,   413,   414,
     306,   174,   175,   151,   152,   311,   179,   253,   254,   167,
     168,   278,   582,    18,    65,    66,   283,   190,    23,  1275,
     752,   179,  1358,   171,   291,    25,   199,  1283,   176,  1285,
    1286,  1287,  1288,   339,  1650,   326,    18,   328,    80,   306,
    1296,    23,  1749,   191,    86,  1361,  1302,    52,    53,   197,
     782,   783,     6,   785,   253,   254,   362,  1504,     6,    41,
      42,    43,    44,   151,   509,    20,    21,  1419,    23,   801,
      25,    53,    28,    20,    21,   807,    23,   809,    23,   811,
     812,  1697,   814,   815,   816,   817,   818,   819,    14,    15,
     822,  1504,   824,   181,   296,   297,   828,   829,    23,  1504,
     200,   201,    52,  1516,   836,   837,    52,  1520,   840,    52,
      20,    21,   844,    23,    80,   249,   204,    79,   206,    23,
     208,   507,   164,    20,    21,   431,    23,   169,   170,  1481,
    1489,   173,   212,   213,    51,   177,  1488,    18,    19,    20,
      21,    22,    23,   183,   184,   877,   212,   213,   454,  2247,
    2248,    79,   419,   165,   253,   254,   258,    52,   890,    18,
      19,    20,    21,    22,    23,    80,   472,  2669,    79,   254,
      52,  2669,    53,   905,  2669,   907,  1528,    52,  1537,  2669,
    1532,    79,   148,    79,    18,    19,    20,    21,    79,  2674,
     232,   151,   152,   235,    53,   339,    52,   285,   286,   287,
     288,    25,   328,   509,   510,   511,   512,   374,   514,   191,
     195,   171,   518,   128,   258,   262,   176,   315,   576,    53,
      50,   262,   317,  1575,   292,    55,    56,    11,    12,    13,
     326,   191,   342,  1919,   166,   348,   202,   355,   292,   506,
    1653,   363,  2727,   292,    28,    29,    30,   361,  1653,   164,
      80,   384,   144,    18,   169,   170,  1872,  1873,    23,   174,
     175,    52,   177,   530,   179,   307,   308,   180,   181,   182,
     315,    79,   314,    60,   394,   190,    41,    42,    43,    44,
      52,   162,   248,    79,   199,    79,   252,   466,    53,   255,
     256,   204,   205,    80,   195,   208,   164,  1649,  1650,   165,
     373,  1557,  1558,   162,  1560,   380,    52,    18,  1564,  1565,
    1996,    79,    79,    18,    79,  1571,  1632,   232,  1634,  1671,
     235,   395,   396,   397,   398,   399,     9,    52,   112,   113,
    1586,    52,  1588,    23,   164,    18,    19,    20,    21,   169,
     170,   128,   191,   233,   179,  1697,  1698,   177,    20,    21,
      22,    23,   139,   183,   184,   185,   186,   187,   188,    52,
      52,    18,    19,    20,    21,    22,    23,   197,   179,    79,
      53,   193,   194,   195,   196,  2061,    79,    79,    49,    50,
      79,   258,    52,   170,    55,    56,    52,   174,   175,  1741,
    1742,    79,   179,   195,  1746,  2678,    53,    80,  2681,  2682,
     367,  1753,   232,   190,  1756,   235,   179,   253,    50,    80,
    2693,   262,   199,    55,    56,    52,  1148,  1149,    52,    18,
      19,    20,    21,    22,    23,    79,  1158,    79,  1160,  1781,
    1843,  1783,  1837,   262,   264,  2718,  2719,    52,    80,  1791,
    2723,  2724,    20,    21,    22,    23,    17,    36,    11,    12,
      13,  2067,  2068,  2069,    53,    18,    18,   244,   288,   246,
      23,   248,    18,    33,    39,    28,    29,    30,    34,  1805,
      18,    78,    50,  1205,    10,   139,   140,    55,    56,   143,
     395,  1213,  1834,   248,    18,    18,   150,   151,  1840,     6,
      53,     6,     6,   164,     6,     6,    50,     6,   169,   170,
       6,    55,    56,     6,     6,     6,   177,     6,  1240,     6,
       6,     6,   183,   184,   185,   186,   187,   188,    53,    78,
    1872,  1873,   164,  1255,  1256,    52,    80,   169,   170,    78,
      52,   173,    52,    23,  1893,   177,   384,   353,   262,  1795,
     262,   183,   184,   185,   186,   187,   188,   262,   262,   112,
     113,  2167,    52,  1809,    52,  1811,    48,   236,    52,    52,
      18,   232,   349,    52,   235,    23,    79,    52,    60,    37,
     165,   358,   359,    65,    52,   262,  1892,   248,   365,    52,
     262,   262,   369,    41,    42,    43,    44,   262,    80,  1845,
     232,   378,   381,   235,   191,    53,    71,    72,    73,    74,
     387,    18,   389,   251,    52,   392,    23,   251,    18,    18,
     164,  1963,    23,   198,   322,   169,   170,    52,   298,    18,
      51,    79,    18,   177,    41,    42,    43,    44,    34,   183,
     184,   185,   186,   187,   188,    78,    53,  2084,  2085,    78,
     470,   471,   472,   212,   213,   214,   215,   216,    18,  1381,
    1382,   251,    53,  2103,     6,   251,    23,    23,   179,   150,
     179,   303,     6,  2015,     6,    54,    23,  1983,    52,  2021,
      25,  2084,  2085,    52,    52,    34,    78,    52,   232,  2084,
    2085,   235,   262,    52,    52,  2371,  1418,   210,   211,    52,
     195,   245,    52,    79,   217,   218,   219,   220,    52,   191,
      18,    52,    52,   257,    52,    52,    52,    52,   200,   201,
     192,    52,    52,    52,    52,  2067,  2068,  2069,    52,  1975,
      52,    52,    52,    52,    52,    52,  2078,    52,    52,  1985,
     434,   435,   436,   437,   438,   439,   440,   441,    52,   231,
      52,    52,    52,    52,    50,  1477,   191,  1479,  1480,    21,
    1482,    34,    34,    18,    18,   426,   427,   428,   429,    78,
      23,   253,   254,     6,     6,   257,     6,  1499,  2120,  1501,
       6,  2123,     6,  2125,  1506,     6,     6,    18,     6,     6,
       6,    54,    78,   454,   261,   261,    52,    25,   459,   315,
      52,   462,  2048,   164,   465,  1527,    52,    52,    78,    52,
      52,   293,   294,   295,   358,    11,    12,    13,    14,    15,
     367,   350,  2428,  2429,  2173,  2167,  2168,  2433,  2434,   311,
      52,  2437,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    52,    52,    39,    52,    52,    52,    52,   300,    52,
      52,  2193,    52,    57,    58,  2197,  2198,    52,  2200,    52,
    2202,    65,    52,    48,    52,    52,    52,  2113,  2114,  2115,
     195,  2117,    57,    58,    59,    60,   374,    62,    63,    64,
      60,   179,    67,    52,    69,    70,   179,    91,   139,    93,
      75,    76,    52,    52,   258,    80,   459,  2573,  2574,   181,
    2242,    52,  2244,  2245,  2246,    52,    50,   197,   149,    52,
     106,    55,    56,    36,    53,  2257,   120,    53,    53,  2261,
      52,    28,    36,  2265,    34,    78,   130,   131,    78,   133,
     134,   135,   136,   137,  2540,  2338,    18,    21,  2614,     6,
     144,   145,   146,     6,   148,   149,    80,  1669,    52,  2291,
      18,   262,  2392,  2393,    79,  2297,  2298,   262,   415,    52,
     411,  2303,   191,  2305,   165,  2307,   410,  2309,    79,    52,
      50,    52,  1694,  2315,   254,    55,    56,    52,  2224,    79,
      79,   324,    79,    79,   300,  2327,  2328,  2233,    23,  2331,
    2332,    69,  1714,  1715,  1716,    48,    18,  1719,    52,   191,
      80,    80,    52,    52,    18,    34,    61,    68,    65,    11,
      12,    13,  2354,    38,    52,    52,  2358,    35,    35,  2361,
      10,  1743,    80,    80,    28,  2367,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    54,  2378,    39,  2387,   183,
     184,   185,   186,   187,   188,    79,   310,    52,   285,   195,
    1772,   406,    79,   262,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   402,    99,   100,   101,   102,   103,   104,
      79,   255,   255,   255,    54,    53,    79,   110,  2420,  2421,
    2422,  2423,  2424,    79,   164,    53,  2428,  2429,    53,   169,
     170,  2433,  2434,   173,    52,  2437,    53,   177,    52,    10,
      77,  2443,    78,   183,   184,   185,   186,   187,   188,    54,
      54,    54,    53,    52,    54,  2457,  2458,  2459,    54,    52,
     107,    36,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,  2475,  2476,   307,    18,    35,    35,  2481,
      10,    79,   254,   200,   201,    79,    52,    52,   326,    52,
    2492,  2397,   232,    52,  2496,   235,    10,  2499,  2500,    54,
      78,  1883,  2504,  2505,   490,    54,    54,   490,    54,    78,
      54,  2513,    53,   300,   231,    54,   298,   257,    52,   255,
     210,   258,  2524,  2525,  2526,   255,   255,   258,   463,  2531,
     255,   255,   249,   298,    79,   363,   253,   254,  2540,  2541,
     257,   258,  2544,  2545,   126,   326,    52,    52,   475,   436,
     475,   434,   480,  1935,  1936,   262,   482,    52,   310,   310,
      52,    25,    52,   262,   485,   298,   300,  2569,  2570,   513,
     287,   262,   363,   126,   262,    52,   262,   294,   515,   524,
     519,    52,   299,  1965,   525,    52,    11,    12,    13,   306,
      52,    52,    52,    52,   311,    36,    36,   314,    11,    12,
      13,    14,    15,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    80,   305,    39,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    52,  2627,    39,  2629,  2630,    25,
      80,   464,   262,   255,   255,  2637,   262,   191,   477,   201,
     499,   201,  2644,    54,    78,   362,   111,    52,    52,    52,
      52,   448,  2558,    52,    52,   448,    78,  2666,  2667,    11,
      12,    13,    14,    15,    52,    52,    79,    52,   443,    52,
      54,  1547,   389,  1043,  1043,  1043,    28,    29,    30,    31,
      32,    33,    34,    35,    36,  2124,  1590,    39,  1590,  1590,
    1840,  1590,  2125,  2123,  1841,  2077,  1842,  1235,  1797,  1359,
     575,  1638,    54,   962,  2392,   179,  2393,   963,   147,   550,
     965,   428,  1216,   486,   431,   432,   433,   848,  1387,  1303,
    1305,  2606,   439,  2587,  1402,  2056,    78,   444,  1889,  1182,
     640,  1905,  1918,  1944,  2497,  2081,  2338,   454,  2508,  2355,
    2359,  1787,  2510,   460,    16,  2358,    18,    19,    20,    21,
      22,    23,    -1,    25,  1121,     6,    -1,  1085,   689,    -1,
      -1,    33,    34,    35,   902,    -1,    38,    -1,    -1,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    53,  2164,    55,    56,    -1,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2177,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,
    2192,    -1,  2194,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2208,  2209,  2210,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,   113,   114,   115,   116,   117,   118,   119,    -1,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   109,   110,
      -1,    -1,    -1,    -1,    -1,    -1,   138,   139,   140,    -1,
      -1,   143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   159,    -1,   161,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
     151,   152,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,   167,  2299,    39,    -1,
     171,    -1,  2304,   174,   175,    -1,    -1,    -1,   179,    -1,
      -1,    -1,    -1,    54,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,   198,    62,    63,
      64,    -1,    -1,    67,    -1,    69,    70,    78,    -1,    -1,
      -1,    75,    76,  2345,    -1,    -1,    80,   239,    -1,    -1,
     221,   222,   223,    -1,    -1,   226,   227,   228,    -1,    -1,
      -1,  2363,    11,    12,    13,    14,    15,  2369,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   301,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,  2426,    -1,    -1,    -1,    -1,    78,
      11,    12,    13,    14,    15,    -1,    -1,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,  2461,
      78,    -1,    -1,    -1,   356,   357,    -1,    -1,  2470,  2471,
      -1,    -1,    -1,    -1,    -1,    -1,  2478,  2479,    -1,    -1,
    2482,    16,    -1,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    -1,   386,    -1,    -1,    78,    33,    34,
      -1,  2503,    -1,    38,    -1,  2507,    -1,  2509,    -1,   401,
      -1,    -1,    -1,    -1,    -1,    50,    51,    -1,    53,    -1,
      55,    56,    -1,    -1,    59,    -1,  2528,  2529,    -1,    -1,
     422,   423,   424,   425,    -1,    -1,    -1,  2539,    -1,    11,
      12,    13,    14,    15,  2546,    -1,  2548,  2549,  2550,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,
     115,   116,   117,   118,   119,    -1,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   138,   139,   140,    78,    -1,   143,    -1,
      -1,  2613,   504,   505,    -1,    -1,   151,    -1,    -1,    -1,
      -1,    -1,  2624,    -1,   159,    -1,   161,    -1,   520,   521,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2640,    -1,
      -1,    -1,    -1,    -1,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,    -1,    -1,    -1,    -1,    -1,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   583,   584,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,   239,    39,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,    12,
      13,    14,    15,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    78,    -1,    39,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    -1,    25,
      -1,    54,    -1,    -1,    -1,    -1,   301,    33,    34,    35,
      -1,    -1,    38,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    -1,    53,    -1,    55,
      56,    -1,    -1,    59,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,    -1,    -1,    -1,    -1,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   356,   357,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   112,   113,    -1,    -1,
      -1,   386,   118,   119,    -1,   121,   122,   123,   124,   125,
     126,   127,   128,   129,    -1,    -1,   401,    -1,    -1,    -1,
      -1,    -1,   138,   139,   140,    78,    -1,   143,    -1,    11,
      12,    13,    14,    15,    -1,   151,    -1,   422,   423,   424,
     425,    -1,    -1,   159,    -1,   161,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,   504,
     505,    -1,    -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,   520,   521,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,    -1,
      -1,    -1,    -1,    -1,    -1,   301,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   583,   584,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,    -1,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,
     356,   357,    33,    34,    35,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    11,    12,    13,    14,    15,    50,
      51,    -1,    53,    -1,    55,    56,    -1,    -1,    59,    -1,
     386,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,   401,    -1,    -1,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    54,    99,   100,
     101,   102,   103,   104,    -1,    -1,   422,   423,   424,   425,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   112,   113,    -1,    -1,    -1,    -1,   118,   119,    -1,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,   139,   140,
      -1,    -1,   143,    -1,    11,    12,    13,    14,    15,    -1,
     151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   159,    -1,
     161,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,     6,    -1,    -1,   504,   505,
      11,    12,    13,    14,    15,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,   520,   521,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   239,    -1,
      -1,    -1,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   583,   584,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    54,    18,    19,    20,    21,
      22,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
     301,    33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    53,    -1,    55,    56,    -1,    -1,    59,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,    -1,    -1,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   356,   357,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,   113,    -1,    54,    -1,   386,   118,   119,    -1,   121,
     122,   123,   124,   125,   126,   127,   128,   129,    -1,    -1,
     401,    -1,    -1,    -1,    -1,    -1,   138,   139,   140,    -1,
      -1,   143,    -1,    11,    12,    13,    14,    15,    -1,   151,
      -1,   422,   423,   424,   425,    -1,    -1,   159,    -1,   161,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,   504,   505,    -1,    -1,   239,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,   520,
     521,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,    -1,    -1,    -1,    -1,    -1,    -1,   301,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   583,   584,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    -1,    25,    -1,
      -1,    -1,    -1,    -1,   356,   357,    33,    34,    35,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    11,    12,
      13,    14,    15,    50,    51,    -1,    53,    -1,    55,    56,
      -1,    -1,    59,    -1,   386,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,   401,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     422,   423,   424,   425,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,   113,    -1,    -1,    -1,
      -1,   118,   119,    -1,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   138,   139,   140,    -1,    -1,   143,    -1,    11,    12,
      13,    14,    15,    -1,   151,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   159,    -1,   161,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,   504,   505,    11,    12,    13,    14,    15,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,   520,   521,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,   239,    -1,    -1,    -1,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   583,   584,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    54,
      18,    19,    20,    21,    22,    23,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,   301,    33,    34,    35,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    -1,    53,    -1,    55,    56,    -1,
      -1,    59,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,    -1,    -1,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,
     357,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   112,   113,    -1,    54,    -1,   386,
     118,   119,    -1,   121,   122,   123,   124,   125,   126,   127,
     128,   129,    -1,    -1,   401,    -1,    -1,    -1,    -1,    -1,
     138,   139,   140,    -1,    -1,   143,    -1,    11,    12,    13,
      14,    15,    -1,   151,    -1,   422,   423,   424,   425,    -1,
      -1,   159,    -1,   161,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,   504,   505,    -1,
      -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,   520,   521,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,    -1,    -1,    -1,
      -1,    -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   583,   584,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    -1,    -1,    -1,   356,   357,
      33,    34,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    11,    12,    13,    14,    15,    50,    51,    -1,
      53,    -1,    55,    56,    -1,    -1,    59,    -1,   386,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,   401,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   422,   423,   424,   425,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
     113,    -1,    -1,    -1,    -1,   118,   119,    -1,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   138,   139,   140,    -1,    -1,
     143,    -1,    11,    12,    13,    14,    15,    -1,   151,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   159,    -1,   161,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,   504,   505,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,   520,   521,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   239,    -1,    -1,    -1,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   583,   584,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,   301,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   356,   357,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   386,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,   108,   109,    -1,    -1,    -1,   401,    -1,
      -1,    -1,    -1,   118,   119,    -1,   121,   122,   123,   124,
     125,   126,   127,   128,    -1,    -1,    -1,    -1,    -1,   422,
     423,   424,   425,    -1,    -1,    -1,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     155,    -1,   157,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,   504,   505,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,   520,   521,    -1,
      -1,    -1,    -1,    -1,   239,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,
     583,   584,    -1,    -1,    -1,    -1,   301,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    23,    99,   100,   101,
     102,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   356,   357,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    -1,    82,    83,    84,    85,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   386,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,   108,   109,    -1,    -1,    -1,   401,    -1,    -1,    -1,
      -1,   118,   119,    -1,   121,   122,   123,   124,   125,   126,
     127,   128,    -1,    -1,    -1,    -1,    -1,   422,   423,   424,
     425,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
     157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   504,
     505,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   520,   521,    -1,    -1,    -1,
      -1,    -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   583,   584,
      -1,    -1,    -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,
     357,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    82,    83,    84,    85,    86,    87,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,
      -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,   108,
     109,    -1,    -1,    -1,   401,    -1,    -1,    -1,    -1,   118,
     119,    -1,   121,   122,   123,   124,   125,   126,   127,   128,
      -1,    -1,    -1,    -1,    -1,   422,   423,   424,   425,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,   157,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   504,   505,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   520,   521,    -1,    -1,    -1,    -1,    -1,
     239,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,   583,   584,    -1,    -1,
      -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,   357,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,   118,   119,
      -1,   121,   122,   123,   124,   125,   126,   127,   128,    -1,
      -1,    -1,   401,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   422,   423,   424,   425,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   504,   505,    -1,    -1,   239,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   520,   521,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,    -1,    -1,    -1,    -1,    -1,
      -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   583,   584,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   356,   357,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   386,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   401,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   422,   423,   424,   425,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,   504,   505,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     520,   521,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   583,   584,    -1,    -1,    -1,    -1,    -1,
      -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   164,    -1,    -1,
      -1,    -1,   169,   170,    -1,   172,   173,    -1,    -1,    -1,
     177,   178,    -1,    -1,    -1,    -1,   183,   184,   185,   186,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,
      -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,    -1,    -1,
      -1,   248,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     257,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   290,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,
     307,   308,    -1,   310,    -1,    -1,    -1,   314,   239,    -1,
     317,   318,    -1,   320,   321,    -1,    -1,   324,   325,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   340,   341,    -1,    -1,    -1,   345,   346,
     347,    -1,    -1,    -1,    -1,    -1,    -1,   354,    -1,    -1,
      -1,   358,    -1,    -1,   361,   362,    -1,   364,    -1,   366,
      -1,    -1,    -1,   370,   371,    -1,    -1,    -1,    -1,    -1,
     301,    -1,    -1,    -1,    -1,   382,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   390,   391,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   400,    -1,    -1,   403,   404,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   356,   357,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   386,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     401,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   422,   423,   424,   425,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   504,   505,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   520,
     521,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   583,   584
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     7,   590,   591,     3,     4,     5,   153,   170,   195,
     196,   233,   235,   237,   248,   277,   279,   280,   281,   284,
     289,   290,   416,   577,   578,   586,   587,   588,   589,   768,
     769,   770,   771,   772,   773,   774,   776,   777,   778,   785,
     787,   788,   789,   790,   791,   792,   793,   794,   795,   796,
     797,   800,   801,   802,   803,   804,   805,   806,   808,   809,
     823,   824,   825,   826,   845,   869,   907,   908,   909,   910,
     911,   912,   913,   914,   969,   970,   993,  1006,  1007,  1008,
    1009,  1010,  1011,  1012,  1013,     0,     6,    40,    50,    52,
      55,    56,    81,   151,   153,   154,   156,   158,   164,   166,
     167,   168,   170,   183,   184,   185,   186,   187,   188,   235,
     241,   247,   248,   576,   592,   593,   647,   649,   650,   651,
     652,   662,   707,   709,   710,   711,   712,   713,   718,   732,
     735,   745,   746,   747,   813,   816,   827,   830,   846,   853,
     865,   868,   872,   873,   916,   917,   919,   921,   922,   927,
     958,   961,   971,   972,   984,   985,   994,   997,  1004,  1005,
    1016,  1019,  1020,     6,     6,     6,    16,    18,    19,    20,
      21,    22,    23,    25,    33,    34,    38,    50,    51,    53,
      55,    56,    59,   112,   113,   118,   119,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   138,   139,   140,   143,
     151,   159,   161,   239,   301,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   356,   357,   386,   401,   422,
     423,   424,   425,   504,   505,   520,   521,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,   583,   584,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   644,
     645,   646,   671,   687,   689,   690,   692,   693,   694,   695,
     812,    23,    25,   171,   784,   807,   810,    23,   810,   810,
     110,   234,   810,   810,     6,   195,   206,   208,   238,   245,
     278,   283,   291,   306,   419,   506,   530,     6,     6,     6,
     151,   181,   204,   206,   208,   285,   286,   287,   288,    42,
      79,   171,   798,   810,   284,    25,   257,   278,   572,   573,
     574,  1014,     6,    23,    24,   596,   596,   596,   695,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    99,   100,
     101,   102,   103,   104,   653,    53,    53,   165,    23,    25,
     621,   206,   207,   225,   575,   189,   206,   621,   167,   245,
     246,   247,   733,   734,   996,   195,   509,   567,   179,   259,
     714,   172,   199,   230,   291,   306,   416,   419,   469,   473,
     474,   506,   530,   534,   582,   871,   957,    51,   596,   719,
      80,   164,   169,   170,   173,   177,   232,   235,   257,   711,
     720,   721,   727,   749,   719,   719,   719,    55,    56,    80,
      88,   121,   148,   172,   173,   178,   183,   184,   185,   186,
     196,   200,   202,   244,   248,   257,   290,   306,   307,   308,
     310,   314,   317,   318,   320,   321,   324,   325,   340,   341,
     345,   346,   347,   354,   358,   361,   362,   364,   366,   370,
     371,   382,   390,   391,   400,   403,   404,   720,   856,   857,
     864,   719,   719,    49,    80,   248,   426,   427,   428,   429,
     454,   459,   462,   465,   711,   720,   875,   876,   877,   878,
     879,   719,    80,   197,   264,   288,   470,   471,   472,   720,
     727,   918,    79,    80,   128,   174,   175,   179,   190,   199,
     395,   720,   722,   719,   719,   719,   719,    80,   245,   257,
     358,   720,   727,   988,   989,    80,   248,   292,   462,   534,
     535,   579,   580,   581,   720,   727,   995,  1018,   719,   719,
      80,   173,   580,   720,  1021,    18,    23,    33,    35,    53,
     161,   163,   686,   688,   693,    36,   600,    36,    20,    21,
     601,   602,    53,   150,    34,   150,   695,    18,   114,   115,
     116,   117,   676,   695,    79,    79,    53,    53,    53,    53,
      53,    53,    53,    18,    19,    21,    22,    23,    53,   162,
     601,   602,   609,   671,   672,   675,   677,   678,   679,   681,
     683,   684,   149,   149,     6,    11,    12,    13,    14,    15,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    39,
      39,    42,    79,   171,   750,     6,   750,    25,   622,   622,
     810,   810,     6,    42,    79,   171,   753,     6,    23,    25,
     171,   811,     6,   282,     6,   779,     6,   786,   181,   208,
     287,   302,   316,    23,   173,   287,   453,   467,   468,   775,
     208,   287,   775,   171,     6,     6,     6,     6,     6,     6,
       6,     6,    88,   170,   522,   565,   566,   567,   568,   569,
     570,  1002,  1003,    18,   799,   622,   870,  1014,     6,  1014,
       6,     6,   509,  1015,    28,   663,   648,    98,   596,    23,
      23,    18,    20,    23,    51,    53,   708,    52,   750,   750,
      18,    23,    53,   594,    41,    42,    43,    44,   191,   594,
     597,   753,    52,    25,   242,    52,   564,   571,   621,  1000,
     249,   594,   595,   595,   596,    79,   717,   420,   421,   920,
     507,    23,    51,    79,   165,   597,   750,   748,   178,   621,
     621,   753,   258,    52,    79,   725,    52,    52,    79,    79,
      79,   249,   327,   339,   317,   320,    52,    25,   330,   331,
      50,   373,    50,   373,    50,   373,    50,   373,   328,   621,
     597,   374,   195,   258,   245,   344,   369,   248,   597,   854,
      52,   594,    20,    21,    23,   383,   598,   848,   393,   598,
     847,   315,   262,   319,   326,   262,   317,   292,   326,   342,
     343,   342,   166,   597,   348,   355,   292,   292,   363,   361,
     251,   310,   330,   597,   372,   594,   384,   144,   315,   394,
      52,    79,   862,    52,    79,    79,   466,   195,   708,   597,
     164,   594,   597,   165,   380,   597,   373,   874,   725,    52,
      79,    79,   597,   148,   149,    18,    51,   203,    18,   174,
     175,    52,    52,   594,   151,   152,   171,   176,   191,   197,
     660,   729,   191,   729,    23,   728,   191,   233,   179,    52,
      52,    79,    79,    79,    79,    21,    22,    23,   612,   616,
     258,   179,    52,    52,    87,   322,   351,   360,   531,   532,
     533,   986,   987,    79,   992,   195,   594,   367,   179,   253,
     597,   262,   597,    52,    52,    79,    79,  1022,  1026,   262,
      52,    10,   688,   688,   688,   695,    20,    21,   162,   681,
     688,   688,    17,    18,    18,    36,   691,   695,    33,    34,
     150,    34,    18,    78,    54,    78,   641,   641,   728,   695,
     695,   695,   695,   695,   695,    35,   674,   676,   695,    33,
      34,    79,    10,    78,   162,    78,   162,    18,    18,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,    57,    58,    65,    91,    93,   120,   130,
     131,   133,   134,   135,   136,   137,   144,   145,   146,   148,
     149,    50,    55,    56,   183,   184,   185,   186,   187,   188,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   783,   180,   181,   182,   204,   205,   208,   751,   752,
       6,     6,     6,     6,   180,   236,   754,   755,     6,   811,
       6,     6,     6,   109,   110,   151,   167,   171,   174,   175,
     179,   198,   221,   222,   223,   226,   227,   228,   616,   660,
     782,     6,    81,   151,   167,   168,   179,   596,   775,   775,
     775,   775,   775,   775,   775,   915,   171,   775,   171,   775,
       6,   775,   775,     6,     6,    78,    80,     6,     6,     6,
     151,   179,   203,   660,     6,  1015,   594,     6,   695,    53,
     655,   656,   657,   661,    52,    78,    78,   742,   743,   695,
      52,   695,   595,    52,   594,   243,   244,   384,   998,   594,
     999,    79,   171,  1001,   594,    45,    46,    47,   716,   719,
      23,   708,   736,   739,   740,   597,   724,   726,   815,   829,
     262,   262,   598,   262,   262,    52,   594,   594,    88,   405,
      52,    52,   248,   375,   262,   368,   597,   597,   353,   597,
     236,    52,    52,    79,   767,    52,    23,   609,   615,    37,
     599,    48,    52,   251,   379,   380,   395,   396,   397,   398,
     399,   852,   599,    48,    52,   251,   597,   594,   262,   262,
     594,   262,   597,   262,   597,   165,   597,   597,    52,   597,
     597,   597,   597,   597,   597,   381,   251,   597,    52,   597,
      52,   385,   621,   251,   597,   597,   861,   863,   867,   597,
     262,   368,   597,   597,   191,   594,   597,   726,   880,   595,
     595,    18,    18,    23,   658,   659,   695,    42,   594,   731,
     198,   731,   731,   597,   728,   926,   960,   973,   597,   728,
      25,   598,   598,    50,   126,   306,   492,   986,   991,    52,
     597,   597,   594,   298,   594,   740,   741,   594,    18,    54,
     688,   162,    51,    18,    54,    78,   150,    34,   695,   695,
     642,   643,    54,    78,    54,    78,    78,    78,    78,    54,
      78,    10,    78,    78,    54,    18,    53,   672,   679,   683,
     251,   251,    53,    78,    80,    78,    80,     6,    20,    21,
      22,    23,   601,   602,   603,   604,   605,   780,   781,   616,
     658,    23,   179,   179,    23,   171,    23,   784,   622,   622,
     622,   622,     6,   622,   622,     6,    23,    65,   164,   258,
     323,   402,   426,   458,   775,   622,   775,   622,   622,   622,
    1003,   658,    25,   728,   621,     6,    52,    54,   654,   664,
      79,   653,   621,    23,   740,    52,    54,    54,    25,    46,
      47,    46,    47,   621,   621,  1002,    52,    52,    80,   148,
     149,   259,   260,   263,   715,    34,   738,    78,    52,    80,
     170,   722,   723,    80,   173,   303,   720,   727,   814,    80,
      86,   173,   307,   308,   314,   720,   828,   594,   594,    52,
     594,   594,    52,    52,   597,    79,   597,   849,   195,   262,
     594,    52,    52,    52,   597,    52,   597,   766,   855,   848,
     596,   848,   594,   594,    52,   847,   594,   594,    52,    52,
     594,   594,    52,   594,    52,   594,    52,   708,    52,    52,
      52,    52,    52,    52,    52,    52,   597,    52,   594,    52,
      52,   594,    52,   597,    52,    52,    60,    80,   139,   174,
     175,   244,   246,   248,   349,   358,   359,   365,   369,   378,
     387,   389,   392,   723,   860,    80,   151,   179,   265,   417,
     418,   660,   720,   866,   594,   594,    80,   173,   178,   282,
     380,   428,   445,   447,   451,   455,   456,   881,   888,   891,
     657,   192,   730,   597,    52,    80,    92,   173,   494,   495,
     498,   503,   720,   727,   923,    80,   173,   454,   508,   720,
     727,   959,    48,    80,   319,   352,   353,   522,   527,   529,
     720,   727,   974,   976,    52,    52,   599,    50,    18,   618,
     619,   594,   597,   597,    23,    79,    80,    82,    83,    84,
      85,    86,    87,    88,   105,   108,   109,   155,   157,   692,
     694,   696,   701,   812,   990,   191,  1017,   594,    79,  1025,
     688,   688,    21,   695,    34,    34,    78,    54,    78,   639,
     640,   695,   695,   695,   695,   695,    35,   674,   695,   674,
      35,   674,   674,    78,   695,    18,    18,   695,   752,   755,
      51,    20,    21,    23,   784,   784,     6,     6,     6,     6,
       6,     6,    18,   708,   708,   708,   622,     6,   622,     6,
       6,     6,   653,   661,   653,   665,   668,   669,   670,   699,
     701,   596,    54,    78,    80,   261,   261,   597,   597,   264,
     265,    52,    25,   622,   737,   739,   750,    52,   817,   822,
     164,    52,   832,   833,   839,   833,   840,   598,   844,   315,
      52,    78,    52,    52,    52,    52,    92,   234,   395,   405,
     407,   409,   412,   850,   851,    52,   368,   597,   594,    52,
      52,    52,    80,   148,   202,   248,   252,   255,   256,   765,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,   300,   367,   179,   179,   374,   179,   195,
     350,   179,   172,   360,   597,    60,   597,   388,   597,   594,
     597,    52,   658,    25,   728,   594,   621,   139,    52,   900,
     906,   389,   430,   455,   597,   883,   389,   597,   882,   258,
     615,   884,   885,   457,   597,    52,   459,   901,   193,   194,
     195,   196,    23,   602,   614,   937,   942,   928,   936,   924,
     925,   614,   181,    52,   962,   968,   597,   594,    52,   594,
     197,   975,   149,   975,    23,   598,   621,   977,    67,   526,
     978,   975,    52,   619,    36,    28,   666,   667,   695,   697,
     697,    53,   695,   695,   695,   702,    53,    53,    52,    28,
     697,    28,    39,   594,  1024,    36,    34,   695,   695,    48,
      57,    58,    59,    60,    62,    63,    64,    67,    69,    70,
      75,    76,    80,   625,   626,   627,   628,   629,   637,    80,
     626,   627,   628,   629,   638,    78,    54,    54,    54,    54,
      54,    78,    10,    54,    78,    54,    78,    10,    54,    78,
      78,    18,    54,    21,     6,     6,   596,   596,    80,   669,
      52,    18,   262,   262,   594,   595,    20,    21,    23,   601,
     602,   617,   741,   165,   172,   183,   184,   307,   831,   741,
      79,   838,    37,   309,   841,   597,   594,   191,   415,   411,
     142,   408,   410,   413,   414,    78,    80,    52,    52,    52,
     253,   254,   597,   254,   595,   594,    52,   197,   323,   339,
     347,   253,   254,   597,   597,   597,   248,   375,   728,   597,
     323,   351,   352,   859,   728,   300,   324,   740,   902,   594,
     594,   597,    79,   594,    79,   708,    79,   594,   594,    79,
      79,   941,   741,    79,   598,   943,   948,    25,    79,   949,
     954,   597,   741,   191,   594,    69,   594,   976,   979,   980,
     594,    18,   695,    80,   665,    78,    52,    52,   812,    52,
     106,    79,    23,   653,   700,   705,   705,   695,    52,   695,
     139,   140,   143,   150,   151,    80,   488,  1023,    18,    34,
      54,    54,    61,    65,    66,    68,    11,    12,    13,    28,
      29,    30,   112,   113,   594,   623,   630,   631,   632,    38,
     633,   634,   634,   636,    23,   601,   613,    52,   630,   633,
     636,   614,    52,   695,    35,   674,    35,   674,    35,   674,
      10,    35,   674,    35,   674,    80,    52,    54,    28,   698,
      54,   595,   595,    79,   821,   597,   838,   837,   834,   596,
     621,   310,   842,    52,   406,   285,   851,   255,   255,   255,
     376,   377,   597,   858,   858,   598,   402,   195,   262,   597,
     597,   903,    79,   905,   893,   893,   886,   889,   940,   939,
      79,   935,   944,   950,    79,   967,   594,   597,    79,    52,
     697,    54,   701,   685,   596,   110,   695,    23,   694,   706,
     812,    52,    52,    53,    53,    53,    52,    53,   598,    52,
      10,   594,    14,    15,   624,    78,    15,    78,   624,   594,
      71,    72,    73,    74,   635,    78,   624,    77,    54,    54,
      54,    54,    78,    10,    54,    54,    54,    78,    53,    54,
      10,    54,    54,    10,    54,   695,    52,   820,   818,   834,
      80,   148,   200,   201,   202,   231,   252,   255,   256,   311,
     756,   757,   759,   760,   761,   835,   598,   307,   843,   595,
     595,   595,   597,   594,   901,   904,    80,   615,   894,   895,
      80,    80,   282,   389,   446,   887,    80,   249,   294,   311,
     431,   432,   433,   756,   890,    80,   487,   488,   491,   492,
     493,   938,   934,   933,   947,   953,   966,   963,   981,    52,
     107,     9,    18,    19,    53,    80,   671,   673,   675,   677,
     678,   680,   682,   703,   705,   705,   695,   695,   695,   695,
     594,   632,   623,   631,   634,   634,    36,   634,   634,    18,
      35,   674,    35,   674,   674,    10,   674,    48,    60,    65,
      80,   191,   253,   254,   257,   293,   294,   295,   311,   756,
     819,   253,   254,   597,    79,   254,   595,   594,   176,   210,
     312,   313,   836,    26,   621,    79,   764,    52,   597,    65,
      80,   249,   253,   254,   257,   258,   287,   294,   299,   306,
     311,   314,   362,   389,   428,   431,   432,   433,   439,   444,
     454,   460,   756,   892,   446,   452,   896,   597,   594,   597,
      52,   594,   594,   176,   312,   442,   594,   326,   223,   594,
      52,   490,   490,   597,   597,   597,    52,    80,    92,   148,
     149,   178,   245,   258,   476,   478,   479,   483,   484,   486,
     494,   495,   929,    80,   490,   496,   945,    80,   490,   497,
     951,    48,    80,   202,   253,   254,   257,   292,   295,   306,
     311,   339,   362,   431,   454,   472,   509,   510,   511,   512,
     514,   518,   756,   964,    80,   522,   523,   528,   982,   701,
     666,   695,    10,    78,   160,   695,    54,    78,    54,    54,
      54,    54,   594,   594,   594,   594,   635,   635,    54,    54,
      54,    78,    54,    53,    54,   594,   300,   296,   297,   594,
     298,    69,    70,   240,   299,   744,   258,   594,   255,   255,
     176,   304,    52,   255,   255,   758,   759,   255,   212,   213,
     210,    51,    86,   165,   203,   209,   229,   762,   434,   435,
     436,   437,   438,   439,   440,   441,   594,   298,    69,   299,
     744,   258,   463,    79,   594,   594,   597,   176,   312,   442,
     436,   363,   594,   597,   594,   326,   223,   594,   339,   461,
     594,   126,   434,    52,   594,    52,   594,   594,   594,   594,
     481,   942,   326,   475,   475,   128,   490,   128,   481,   490,
     482,   475,   597,   480,   262,   485,   300,   310,   930,   310,
     931,    52,   946,   489,   594,   955,   943,    52,   952,   955,
     949,    52,   594,   597,   298,    69,   299,   744,   258,   516,
     594,   262,   597,   176,   212,   442,   517,   965,   598,   363,
     262,   126,   373,   434,   262,   262,   448,   594,   513,   515,
     519,    52,   983,   525,   524,   621,    52,    54,    53,   673,
     680,   666,   704,    52,   695,    52,    52,    52,    52,    36,
      36,   674,   674,   183,   184,   594,   594,   594,   594,   594,
     597,   595,   595,   305,   595,   595,    80,    52,   595,   212,
     213,    25,   620,    51,   203,   594,   620,   210,   211,   217,
     218,   219,   220,   763,    51,   203,    80,   449,   450,   594,
     594,   594,   597,   464,   897,   597,   254,   597,   594,   594,
     597,   597,   594,   597,   499,   956,   956,   262,   594,   255,
     255,   500,   501,   502,   932,   594,   932,   262,   594,   594,
     477,   597,   594,   594,   191,   597,   948,   597,   954,   594,
     594,   594,   594,   597,   597,   594,   254,   597,   595,   594,
     594,   594,   597,   597,   597,   597,   201,   201,   695,   111,
      54,   594,   594,    54,    78,   598,   598,   758,    52,   620,
     620,    52,    52,   212,   213,   214,   215,   216,   212,   213,
     214,   215,   216,    52,   620,   620,   764,   597,    80,   598,
     899,   448,   597,   594,   594,   594,   956,   594,   956,   597,
     594,   448,   621,   621,   701,    52,   674,   762,    52,    52,
     762,   762,   762,    52,    52,   443,   898,    78,   762,   762,
     762,   762,    52,   674,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   585,   590,   590,   591,   591,   592,   592,   593,   594,
     594,   594,   595,   595,   595,   596,   596,   597,   597,   597,
     597,   597,   597,   598,   598,   598,   599,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   609,   610,
     610,   611,   611,   612,   612,   612,   612,   612,   612,   613,
     613,   614,   614,   615,   615,   616,   616,   617,   617,   617,
     617,   617,   618,   619,   619,   620,   621,   621,   622,   622,
     623,   623,   623,   623,   623,   623,   623,   623,   624,   624,
     625,   625,   625,   625,   625,   625,   625,   625,   625,   625,
     626,   627,   628,   629,   629,   630,   630,   630,   630,   631,
     631,   632,   632,   633,   633,   633,   634,   634,   635,   635,
     635,   635,   636,   636,   636,   637,   637,   637,   637,   638,
     638,   638,   638,   638,   639,   639,   640,   640,   641,   642,
     643,   644,   645,   646,   646,   586,   587,   586,   588,   586,
     589,   592,   648,   647,   592,   649,   592,   650,   592,   651,
     592,   652,   653,   653,   653,   653,   653,   653,   653,   653,
     653,   653,   653,   653,   653,   653,   653,   653,   654,   654,
     655,   655,   656,   656,   657,   658,   659,   658,   660,   661,
     592,   663,   664,   662,   665,   665,   667,   666,   668,   668,
     669,   670,   670,   671,   671,   672,   672,   672,   672,   672,
     672,   673,   673,   673,   673,   674,   675,   675,   675,   675,
     675,   675,   675,   675,   675,   675,   676,   676,   676,   676,
     677,   677,   677,   678,   678,   678,   678,   678,   678,   678,
     678,   679,   679,   679,   679,   679,   680,   680,   680,   680,
     680,   681,   681,   682,   682,   683,   683,   683,   683,   684,
     684,   685,   685,   685,   686,   686,   687,   688,   688,   688,
     688,   688,   688,   688,   688,   688,   689,   689,   689,   689,
     689,   689,   689,   689,   689,   689,   689,   690,   690,   690,
     690,   691,   691,   691,   692,   693,   694,   694,   694,   694,
     694,   694,   694,   694,   694,   694,   694,   694,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     696,   696,   696,   697,   697,   697,   698,   698,   699,   700,
     700,   701,   701,   701,   702,   703,   704,   701,   701,   701,
     701,   701,   701,   701,   701,   701,   701,   701,   701,   701,
     701,   701,   701,   701,   701,   705,   706,   706,   706,   592,
     707,   707,   708,   708,   708,   708,   592,   709,   592,   710,
     711,   711,   711,   711,   711,   711,   711,   711,   711,   711,
     592,   712,   713,   714,   714,   715,   715,   715,   715,   715,
     715,   716,   716,   717,   717,   592,   718,   718,   719,   719,
     719,   719,   720,   720,   720,   720,   720,   720,   720,   720,
     721,   722,   722,   722,   722,   722,   722,   722,   722,   722,
     723,   723,   724,   724,   725,   725,   726,   727,   728,   729,
     729,   729,   729,   730,   730,   730,   730,   730,   731,   731,
     592,   732,   732,   732,   592,   733,   733,   733,   733,   734,
     734,   734,   734,   734,   734,   734,   734,   735,   736,   737,
     737,   738,   738,   739,   740,   740,   741,   742,   743,   744,
     744,   745,   746,   747,   747,   747,   747,   747,   748,   749,
     750,   750,   750,   751,   751,   752,   752,   752,   752,   752,
     752,   753,   753,   753,   754,   754,   755,   755,   756,   757,
     757,   758,   758,   759,   759,   760,   760,   761,   761,   762,
     762,   762,   762,   762,   762,   762,   762,   762,   763,   763,
     763,   763,   763,   763,   763,   763,   763,   763,   763,   763,
     763,   763,   764,   765,   765,   765,   765,   765,   765,   765,
     766,   766,   767,   586,   768,   586,   769,   586,   770,   586,
     771,   586,   772,   586,   773,   586,   774,   775,   775,   586,
     776,   586,   777,   586,   778,   779,   779,   779,   779,   779,
     779,   779,   779,   779,   779,   779,   779,   779,   779,   779,
     779,   779,   779,   780,   780,   780,   780,   780,   780,   780,
     780,   781,   781,   781,   781,   782,   782,   782,   782,   783,
     783,   783,   783,   783,   783,   783,   783,   783,   783,   783,
     783,   783,   783,   783,   783,   783,   783,   783,   783,   784,
     586,   785,   786,   786,   786,   786,   786,   786,   786,   586,
     787,   586,   788,   586,   789,   586,   790,   586,   791,   586,
     792,   586,   793,   586,   794,   586,   795,   586,   796,   586,
     797,   798,   798,   798,   799,   799,   586,   800,   586,   801,
     586,   802,   586,   803,   586,   804,   586,   805,   586,   806,
     807,   807,   586,   808,   586,   809,   810,   810,   810,   811,
     811,   811,   812,   745,   827,   828,   828,   828,   828,   828,
     828,   829,   829,   830,   831,   831,   831,   831,   832,   832,
     833,   834,   835,   835,   835,   835,   835,   835,   835,   835,
     836,   836,   836,   836,   836,   836,   837,   837,   838,   838,
     839,   840,   841,   841,   841,   842,   842,   843,   843,   844,
     586,   845,   745,   813,   814,   814,   814,   814,   815,   815,
     816,   817,   818,   819,   819,   819,   819,   819,   819,   819,
     819,   819,   819,   819,   819,   819,   819,   819,   819,   819,
     819,   819,   820,   820,   821,   821,   822,   812,   586,   823,
     586,   824,   586,   825,   586,   826,   745,   846,   847,   847,
     847,   848,   848,   848,   848,   848,   849,   849,   850,   850,
     851,   851,   851,   851,   851,   851,   851,   851,   851,   852,
     852,   852,   852,   852,   853,   853,   853,   853,   853,   853,
     853,   853,   853,   853,   853,   853,   853,   853,   853,   853,
     853,   853,   853,   853,   853,   853,   853,   853,   853,   853,
     853,   853,   853,   853,   853,   853,   853,   853,   853,   853,
     853,   853,   853,   853,   853,   853,   853,   853,   853,   853,
     853,   853,   853,   853,   853,   853,   853,   853,   853,   853,
     853,   853,   853,   853,   853,   853,   853,   853,   854,   855,
     853,   853,   853,   853,   856,   856,   856,   856,   856,   856,
     856,   856,   856,   856,   856,   856,   856,   856,   857,   858,
     858,   858,   859,   859,   859,   860,   860,   860,   860,   860,
     860,   860,   860,   860,   860,   860,   860,   860,   860,   860,
     860,   860,   860,   860,   860,   860,   860,   860,   860,   860,
     861,   861,   862,   862,   863,   864,   812,   812,   812,   812,
     812,   812,   812,   812,   812,   812,   812,   812,   812,   812,
     745,   865,   866,   866,   866,   866,   866,   866,   866,   866,
     867,   867,   868,   586,   869,   870,   870,   870,   870,   870,
     870,   745,   871,   871,   871,   872,   873,   873,   874,   874,
     875,   876,   877,   877,   877,   877,   877,   877,   877,   877,
     877,   877,   877,   877,   877,   877,   877,   878,   879,   880,
     880,   881,   881,   881,   881,   881,   881,   881,   881,   881,
     882,   881,   883,   881,   881,   881,   881,   884,   884,   885,
     886,   886,   887,   887,   887,   888,   888,   889,   889,   890,
     890,   890,   890,   890,   890,   890,   890,   890,   890,   890,
     891,   892,   892,   892,   892,   892,   892,   892,   892,   892,
     892,   892,   892,   892,   892,   892,   892,   892,   892,   892,
     892,   892,   892,   892,   892,   892,   892,   892,   892,   892,
     892,   892,   892,   892,   892,   892,   892,   892,   892,   892,
     893,   893,   894,   895,   896,   896,   896,   897,   897,   898,
     898,   899,   900,   901,   901,   903,   902,   904,   904,   905,
     905,   906,   812,   812,   812,   812,   586,   907,   586,   908,
     586,   909,   586,   910,   586,   911,   586,   912,   586,   913,
     586,   914,   915,   915,   915,   915,   915,   915,   915,   915,
     915,   745,   916,   917,   917,   917,   918,   918,   918,   918,
     918,   918,   918,   918,   918,   918,   745,   920,   919,   921,
     921,   921,   921,   745,   922,   923,   923,   923,   923,   924,
     923,   925,   923,   923,   923,   926,   926,   927,   928,   929,
     929,   929,   929,   929,   929,   929,   929,   929,   929,   929,
     929,   929,   929,   929,   929,   929,   930,   929,   931,   929,
     929,   929,   932,   932,   932,   933,   934,   934,   935,   935,
     936,   937,   938,   938,   938,   938,   938,   939,   940,   940,
     941,   941,   942,   943,   944,   945,   945,   945,   946,   947,
     947,   948,   948,   949,   950,   951,   951,   951,   952,   953,
     953,   954,   954,   955,   955,   956,   956,   812,   812,   745,
     957,   957,   958,   959,   959,   959,   959,   959,   959,   960,
     960,   961,   962,   963,   964,   964,   964,   964,   964,   964,
     964,   964,   964,   964,   964,   964,   964,   964,   964,   964,
     964,   964,   964,   964,   964,   964,   964,   964,   964,   964,
     964,   965,   965,   965,   965,   966,   966,   967,   967,   968,
     812,   812,   586,   969,   586,   970,   745,   971,   972,   973,
     973,   974,   974,   974,   974,   974,   974,   974,   974,   974,
     974,   975,   975,   976,   977,   977,   978,   978,   979,   980,
     981,   981,   982,   982,   982,   983,   745,   984,   985,   985,
     985,   985,   985,   985,   986,   986,   986,   986,   986,   986,
     987,   987,   988,   989,   989,   989,   989,   989,   989,   989,
     989,   989,   990,   991,   991,   992,   992,   586,   993,   994,
     995,   995,   995,   812,   812,   812,   812,   812,   812,   812,
     812,   812,   812,   812,   812,   812,   812,   812,   812,   812,
     812,   812,   812,   812,   812,   812,   812,   812,   812,   812,
     812,   592,   996,   997,   998,   998,   999,   999,  1000,  1000,
    1000,  1001,  1001,  1002,  1002,  1003,  1003,  1003,  1003,  1003,
    1003,  1003,  1003,  1003,   592,  1004,  1004,   592,  1005,  1005,
    1005,  1005,   586,  1006,   586,  1007,   586,  1008,   586,  1009,
     586,  1010,   586,  1011,   586,  1012,   586,  1013,  1014,  1014,
    1015,  1015,  1015,   745,  1016,   994,   994,  1017,  1017,  1018,
    1018,  1018,  1018,  1018,  1018,  1018,   745,  1019,  1020,  1020,
    1021,  1021,  1021,  1022,  1023,  1024,  1024,  1025,  1025,  1026,
     812,   812
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     1,     1,     5,     1,
       3,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     0,     2,     2,     2,
       3,     7,     2,     2,     5,     5,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     4,     1,     3,     1,
       3,     1,     3,     4,     6,     6,     0,     1,     1,     1,
       1,     1,     2,     4,     4,     2,     2,     2,     2,     2,
       4,     2,     2,     2,     0,     3,     0,     3,     0,     0,
       0,     6,     6,     1,     1,     1,     2,     1,     2,     1,
       2,     1,     0,     4,     1,     2,     1,     4,     1,     6,
       1,     8,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     4,
       2,     5,     0,     4,     1,     1,     0,     2,     2,     4,
       1,     0,     0,     6,     0,     1,     0,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     3,     1,     1,     1,     5,     7,     5,     7,
       9,     7,     5,     7,     5,    11,     1,     1,     2,     1,
       7,     9,     7,     7,     9,     7,     9,     7,     9,     7,
      15,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     1,     2,     2,     6,     1,
       3,     0,     4,     3,     1,     3,     3,     2,     4,     3,
       4,     2,     2,     2,     2,     0,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     1,     5,     7,     7,
       1,     0,     1,     3,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     4,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     6,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     7,     6,     6,     6,     6,     4,     8,     4,     1,
       1,     1,     1,     0,     1,     3,     0,     2,     4,     2,
       1,     3,     4,     6,     0,     0,     0,     9,     4,     3,
       4,     4,     5,     3,     3,     3,     2,     5,     4,     7,
       7,     7,     7,     7,     9,     0,     1,     1,     1,     1,
       4,     5,     1,     3,     1,     1,     1,     3,     1,     5,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     0,     1,     2,     2,     4,     4,     3,
       3,     0,     3,     0,     3,     1,     1,     1,     0,     1,
       2,     3,     0,     2,     2,     2,     3,     2,     2,     2,
       1,     2,     2,     2,     3,     3,     3,     2,     4,     3,
       1,     2,     0,     3,     0,     3,     0,     3,     1,     2,
       1,     1,     1,     0,     2,     2,     2,     2,     2,     1,
       1,     3,     3,     3,     1,     1,     1,     1,     1,     2,
       4,     3,     4,     4,     3,     4,     4,     3,     0,     1,
       2,     0,     1,     3,     1,     3,     1,     0,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     5,     0,     3,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     1,     1,     4,
       1,     0,     3,     5,     2,     1,     1,     2,     2,     0,
       5,     5,     5,     5,     4,     4,     4,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     0,     2,     4,     4,     4,     2,     2,     1,
       0,     3,     3,     1,     3,     1,     2,     1,     2,     1,
       2,     1,     3,     1,     4,     1,     5,     1,     0,     1,
       3,     1,     4,     1,     4,     0,     2,     3,     3,     3,
       3,     4,     4,     3,     2,     2,     2,     2,     3,     3,
       3,     2,     2,     1,     1,     1,     1,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     4,     0,     2,     2,     2,     2,     2,     2,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     4,     1,     3,     1,
       4,     1,     1,     3,     0,     1,     1,     4,     1,     4,
       1,     4,     1,     3,     1,     4,     1,     4,     1,     3,
       2,     2,     1,     4,     1,     2,     1,     1,     1,     1,
       0,     1,     1,     1,     2,     1,     2,     2,     2,     2,
       3,     0,     3,     5,     1,     1,     1,     1,     0,     2,
       0,     0,     2,     4,     4,     4,     2,     2,     2,     1,
       1,     1,     2,     2,     3,     3,     0,     3,     0,     3,
       4,     3,     0,     2,     2,     0,     2,     0,     2,     4,
       1,     5,     1,     2,     1,     1,     2,     4,     0,     3,
       5,     0,     0,     0,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     2,     3,     3,     4,     4,     2,     2,
       3,     1,     0,     3,     0,     3,     4,     1,     1,     6,
       1,     6,     1,     6,     1,     6,     2,     2,     0,     3,
       3,     0,     3,     3,     2,     2,     1,     3,     1,     3,
       1,     3,     2,     2,     2,     2,     2,     2,     3,     1,
       1,     1,     1,     1,     3,     3,     3,     4,     6,     4,
       6,     6,     4,     6,     5,     5,     4,     5,     5,     6,
       6,     3,     3,     4,     5,     6,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     6,     6,     6,     5,
       6,     6,     8,     6,     6,     6,     5,     6,     5,     4,
       4,     4,     4,     5,     5,     6,     5,     6,     5,     5,
       6,     7,     7,     7,     5,     5,     4,     4,     0,     0,
       6,     6,     5,     5,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     4,
       2,     3,     2,     2,     2,     2,     3,     5,     5,     4,
       3,     3,     3,     3,     3,     2,     2,     2,     3,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     2,     2,     1,     2,     2,     4,
       0,     3,     5,     1,     4,     0,     3,     3,     3,     2,
       3,     2,     1,     2,     2,     2,     3,     3,     0,     1,
       2,     3,     1,     1,     2,     2,     3,     3,     3,     3,
       4,     2,     4,     3,     2,     3,     1,     2,     4,     0,
       3,     2,     1,     2,     3,     3,     3,     3,     2,     3,
       0,     5,     0,     5,     2,     2,     1,     4,     1,     1,
       0,     3,     2,     2,     2,     5,     2,     0,     3,     0,
       2,     2,     3,     2,     2,     3,     2,     2,     2,     1,
       3,     2,     2,     2,     2,     2,     2,     3,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       2,     3,     2,     3,     3,     4,     4,     2,     2,     2,
       3,     3,     3,     2,     3,     3,     3,     4,     2,     1,
       0,     2,     3,     1,     0,     1,     2,     0,     2,     0,
       1,     3,     0,     0,     2,     0,     3,     0,     3,     0,
       3,     3,     1,     1,     1,     1,     1,     4,     1,     6,
       1,     6,     1,     6,     1,     7,     1,     6,     1,     7,
       1,     5,     0,     2,     3,     2,     3,     3,     2,     3,
       2,     2,     2,     3,     3,     3,     1,     3,     3,     2,
       3,     3,     2,     2,     2,     2,     2,     0,     4,     2,
       3,     3,     5,     1,     2,     1,     1,     2,     2,     0,
       3,     0,     3,     2,     3,     0,     3,     5,     0,     4,
       4,     3,     4,     2,     3,     3,     3,     3,     4,     4,
       4,     3,     3,     4,     4,     2,     0,     3,     0,     3,
       3,     3,     1,     1,     1,     0,     0,     3,     0,     3,
       4,     1,     2,     2,     2,     4,     4,     0,     0,     3,
       0,     3,     3,     1,     0,     0,     2,     2,     0,     0,
       3,     1,     5,     1,     0,     0,     2,     2,     0,     0,
       3,     1,     5,     1,     2,     0,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     2,     4,     2,     2,     0,
       3,     5,     0,     0,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     4,     3,     2,     2,
       1,     1,     1,     1,     1,     0,     3,     0,     3,     4,
       1,     1,     1,     6,     1,     6,     1,     2,     5,     0,
       3,     1,     1,     2,     3,     1,     2,     3,     3,     3,
       4,     0,     1,     2,     1,     1,     2,     6,     0,     0,
       0,     3,     4,     4,     2,     0,     2,     2,     3,     3,
       3,     5,     5,     4,     3,     2,     3,     3,     3,     3,
       1,     2,     2,     2,     3,     5,     1,     2,     2,     2,
       2,     2,     1,     0,     2,     0,     3,     1,     4,     3,
       3,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     5,     2,     0,     0,     2,     2,     2,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     1,     3,     4,
       3,     3,     1,     4,     1,     5,     1,     3,     1,     3,
       1,     3,     1,     4,     1,     2,     1,     3,     0,     1,
       0,     1,     2,     2,     2,     3,     3,     0,     2,     1,
       1,     2,     3,     2,     3,     4,     2,     2,     3,     3,
       1,     2,     3,     0,     2,     0,     3,     0,     3,     3,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          YYNOMEM;                                                      \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      YY_LAC_ESTABLISH;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* config: conf_entries END  */
#line 137 "conf/confbase.Y"
                         { return 0; }
#line 6433 "obj/conf/cf-parse.tab.c"
    break;

  case 3: /* config: CLI_MARKER cli_cmd  */
#line 138 "conf/confbase.Y"
                      { return 0; }
#line 6439 "obj/conf/cf-parse.tab.c"
    break;

  case 8: /* definition: DEFINE symbol '=' term ';'  */
#line 154 "conf/confbase.Y"
                              {
     struct f_val *val = cfg_allocz(sizeof(struct f_val));
     if (f_eval(f_linearize((yyvsp[-1].x), 1), cfg_mem, val) > F_RETURN) cf_error("Runtime error");
     cf_define_symbol((yyvsp[-3].s), SYM_CONSTANT | val->type, val, val);
   }
#line 6449 "obj/conf/cf-parse.tab.c"
    break;

  case 10: /* expr: '(' term ')'  */
#line 163 "conf/confbase.Y"
                { (yyval.i) = f_eval_int(f_linearize((yyvsp[-1].x), 1)); }
#line 6455 "obj/conf/cf-parse.tab.c"
    break;

  case 11: /* expr: CF_SYM_KNOWN  */
#line 164 "conf/confbase.Y"
                {
     if ((yyvsp[0].s)->class != (SYM_CONSTANT | T_INT)) cf_error("Number constant expected");
     (yyval.i) = SYM_VAL((yyvsp[0].s)).i; }
#line 6463 "obj/conf/cf-parse.tab.c"
    break;

  case 12: /* expr_us: expr S  */
#line 170 "conf/confbase.Y"
           { (yyval.time) = (yyvsp[-1].i) S_; }
#line 6469 "obj/conf/cf-parse.tab.c"
    break;

  case 13: /* expr_us: expr MS  */
#line 171 "conf/confbase.Y"
           { (yyval.time) = (yyvsp[-1].i) MS_; }
#line 6475 "obj/conf/cf-parse.tab.c"
    break;

  case 14: /* expr_us: expr US  */
#line 172 "conf/confbase.Y"
           { (yyval.time) = (yyvsp[-1].i) US_; }
#line 6481 "obj/conf/cf-parse.tab.c"
    break;

  case 17: /* bool: expr  */
#line 180 "conf/confbase.Y"
        { (yyval.i) = !!(yyvsp[0].i); }
#line 6487 "obj/conf/cf-parse.tab.c"
    break;

  case 18: /* bool: ON  */
#line 181 "conf/confbase.Y"
      { (yyval.i) = 1; }
#line 6493 "obj/conf/cf-parse.tab.c"
    break;

  case 19: /* bool: YES  */
#line 182 "conf/confbase.Y"
       { (yyval.i) = 1; }
#line 6499 "obj/conf/cf-parse.tab.c"
    break;

  case 20: /* bool: OFF  */
#line 183 "conf/confbase.Y"
       { (yyval.i) = 0; }
#line 6505 "obj/conf/cf-parse.tab.c"
    break;

  case 21: /* bool: NO  */
#line 184 "conf/confbase.Y"
      { (yyval.i) = 0; }
#line 6511 "obj/conf/cf-parse.tab.c"
    break;

  case 22: /* bool: %empty  */
#line 185 "conf/confbase.Y"
                                 { (yyval.i) = 1; }
#line 6517 "obj/conf/cf-parse.tab.c"
    break;

  case 23: /* ipa: IP4  */
#line 192 "conf/confbase.Y"
       { (yyval.a) = ipa_from_ip4((yyvsp[0].ip4)); }
#line 6523 "obj/conf/cf-parse.tab.c"
    break;

  case 24: /* ipa: IP6  */
#line 193 "conf/confbase.Y"
       { (yyval.a) = ipa_from_ip6((yyvsp[0].ip6)); }
#line 6529 "obj/conf/cf-parse.tab.c"
    break;

  case 25: /* ipa: CF_SYM_KNOWN  */
#line 194 "conf/confbase.Y"
                {
     if ((yyvsp[0].s)->class != (SYM_CONSTANT | T_IP)) cf_error("IP address constant expected");
     (yyval.a) = SYM_VAL((yyvsp[0].s)).ip;
   }
#line 6538 "obj/conf/cf-parse.tab.c"
    break;

  case 26: /* ipa_scope: %empty  */
#line 201 "conf/confbase.Y"
               { (yyval.iface) = NULL; }
#line 6544 "obj/conf/cf-parse.tab.c"
    break;

  case 27: /* ipa_scope: '%' symbol  */
#line 202 "conf/confbase.Y"
              { (yyval.iface) = if_get_by_name((yyvsp[0].s)->name); }
#line 6550 "obj/conf/cf-parse.tab.c"
    break;

  case 28: /* pxlen4: '/' NUM  */
#line 209 "conf/confbase.Y"
           {
     if ((yyvsp[0].i) > IP4_MAX_PREFIX_LENGTH) cf_error("Invalid prefix length %u", (yyvsp[0].i));
     (yyval.i) = (yyvsp[0].i);
   }
#line 6559 "obj/conf/cf-parse.tab.c"
    break;

  case 29: /* net_ip4_: IP4 pxlen4  */
#line 216 "conf/confbase.Y"
{
  net_fill_ip4(&((yyval.net)), (yyvsp[-1].ip4), (yyvsp[0].i));

  net_addr_ip4 *n = (void *) &((yyval.net));
  if (!net_validate_ip4(n))
    cf_error("Invalid IPv4 prefix %I4/%d, maybe you wanted %I4/%d",
	     n->prefix, n->pxlen, ip4_and(n->prefix, ip4_mkmask(n->pxlen)), n->pxlen);
}
#line 6572 "obj/conf/cf-parse.tab.c"
    break;

  case 30: /* net_ip6_: IP6 '/' NUM  */
#line 226 "conf/confbase.Y"
{
  if ((yyvsp[0].i) > IP6_MAX_PREFIX_LENGTH)
    cf_error("Invalid prefix length %u", (yyvsp[0].i));

  net_fill_ip6(&((yyval.net)), (yyvsp[-2].ip6), (yyvsp[0].i));

  net_addr_ip6 *n = (void *) &((yyval.net));
  if (!net_validate_ip6(n))
    cf_error("Invalid IPv6 prefix %I6/%d, maybe you wanted %I6/%d",
	     n->prefix, n->pxlen, ip6_and(n->prefix, ip6_mkmask(n->pxlen)), n->pxlen);
}
#line 6588 "obj/conf/cf-parse.tab.c"
    break;

  case 31: /* net_ip6_sadr_: IP6 '/' NUM FROM IP6 '/' NUM  */
#line 239 "conf/confbase.Y"
{
  if ((yyvsp[-4].i) > IP6_MAX_PREFIX_LENGTH)
    cf_error("Invalid prefix length %u", (yyvsp[-4].i));

  if ((yyvsp[0].i) > IP6_MAX_PREFIX_LENGTH)
    cf_error("Invalid prefix length %u", (yyvsp[0].i));

  (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_ip6_sadr));
  net_fill_ip6_sadr((yyval.net_ptr), (yyvsp[-6].ip6), (yyvsp[-4].i), (yyvsp[-2].ip6), (yyvsp[0].i));

  net_addr_ip6_sadr *n = (void *) (yyval.net_ptr);
  if (!net_validate_ip6_sadr(n))
    cf_error("Invalid SADR IPv6 prefix %I6/%d from %I6/%d, maybe you wanted %I6/%d from %I6/%d",
	     n->dst_prefix, n->dst_pxlen, n->src_prefix, n->src_pxlen,
	     ip6_and(n->dst_prefix, ip6_mkmask(n->dst_pxlen)), n->dst_pxlen,
	     ip6_and(n->src_prefix, ip6_mkmask(n->src_pxlen)), n->src_pxlen);
}
#line 6610 "obj/conf/cf-parse.tab.c"
    break;

  case 32: /* net_vpn4_: VPN_RD net_ip4_  */
#line 258 "conf/confbase.Y"
{
  (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_vpn4));
  net_fill_vpn4((yyval.net_ptr), net4_prefix(&(yyvsp[0].net)), net4_pxlen(&(yyvsp[0].net)), (yyvsp[-1].i64));
}
#line 6619 "obj/conf/cf-parse.tab.c"
    break;

  case 33: /* net_vpn6_: VPN_RD net_ip6_  */
#line 264 "conf/confbase.Y"
{
  (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_vpn6));
  net_fill_vpn6((yyval.net_ptr), net6_prefix(&(yyvsp[0].net)), net6_pxlen(&(yyvsp[0].net)), (yyvsp[-1].i64));
}
#line 6628 "obj/conf/cf-parse.tab.c"
    break;

  case 34: /* net_roa4_: net_ip4_ MAX NUM AS NUM  */
#line 270 "conf/confbase.Y"
{
  (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_roa4));
  net_fill_roa4((yyval.net_ptr), net4_prefix(&(yyvsp[-4].net)), net4_pxlen(&(yyvsp[-4].net)), (yyvsp[-2].i), (yyvsp[0].i));
  if ((yyvsp[-2].i) < net4_pxlen(&(yyvsp[-4].net)) || (yyvsp[-2].i) > IP4_MAX_PREFIX_LENGTH)
    cf_error("Invalid max prefix length %u", (yyvsp[-2].i));
}
#line 6639 "obj/conf/cf-parse.tab.c"
    break;

  case 35: /* net_roa6_: net_ip6_ MAX NUM AS NUM  */
#line 278 "conf/confbase.Y"
{
  (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_roa6));
  net_fill_roa6((yyval.net_ptr), net6_prefix(&(yyvsp[-4].net)), net6_pxlen(&(yyvsp[-4].net)), (yyvsp[-2].i), (yyvsp[0].i));
  if ((yyvsp[-2].i) < net6_pxlen(&(yyvsp[-4].net)) || (yyvsp[-2].i) > IP6_MAX_PREFIX_LENGTH)
    cf_error("Invalid max prefix length %u", (yyvsp[-2].i));
}
#line 6650 "obj/conf/cf-parse.tab.c"
    break;

  case 36: /* net_mpls_: MPLS NUM  */
#line 286 "conf/confbase.Y"
{
  (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_roa6));
  net_fill_mpls((yyval.net_ptr), (yyvsp[0].i));
}
#line 6659 "obj/conf/cf-parse.tab.c"
    break;

  case 43: /* net_: net_ip_  */
#line 296 "conf/confbase.Y"
           { (yyval.net_ptr) = cfg_alloc((yyvsp[0].net).length); net_copy((yyval.net_ptr), &((yyvsp[0].net))); }
#line 6665 "obj/conf/cf-parse.tab.c"
    break;

  case 50: /* net_ip4: CF_SYM_KNOWN  */
#line 309 "conf/confbase.Y"
                {
     if (((yyvsp[0].s)->class != (SYM_CONSTANT | T_NET)) || (SYM_VAL((yyvsp[0].s)).net->type != NET_IP4))
       cf_error("IPv4 network constant expected");
     (yyval.net) = * SYM_VAL((yyvsp[0].s)).net;
   }
#line 6675 "obj/conf/cf-parse.tab.c"
    break;

  case 52: /* net_ip6: CF_SYM_KNOWN  */
#line 318 "conf/confbase.Y"
                {
     if (((yyvsp[0].s)->class != (SYM_CONSTANT | T_NET)) || (SYM_VAL((yyvsp[0].s)).net->type != NET_IP6))
       cf_error("IPv6 network constant expected");
     (yyval.net) = * SYM_VAL((yyvsp[0].s)).net;
   }
#line 6685 "obj/conf/cf-parse.tab.c"
    break;

  case 54: /* net_ip: CF_SYM_KNOWN  */
#line 327 "conf/confbase.Y"
                {
     if (((yyvsp[0].s)->class != (SYM_CONSTANT | T_NET)) || !net_is_ip(SYM_VAL((yyvsp[0].s)).net))
       cf_error("IP network constant expected");
     (yyval.net) = * SYM_VAL((yyvsp[0].s)).net;
   }
#line 6695 "obj/conf/cf-parse.tab.c"
    break;

  case 56: /* net_any: CF_SYM_KNOWN  */
#line 336 "conf/confbase.Y"
                {
     if ((yyvsp[0].s)->class != (SYM_CONSTANT | T_NET))
       cf_error("Network constant expected");
     (yyval.net_ptr) = (net_addr *) SYM_VAL((yyvsp[0].s)).net; /* Avoid const warning */
   }
#line 6705 "obj/conf/cf-parse.tab.c"
    break;

  case 59: /* net_or_ipa: IP4  */
#line 346 "conf/confbase.Y"
       { net_fill_ip4(&((yyval.net)), (yyvsp[0].ip4), IP4_MAX_PREFIX_LENGTH); }
#line 6711 "obj/conf/cf-parse.tab.c"
    break;

  case 60: /* net_or_ipa: IP6  */
#line 347 "conf/confbase.Y"
       { net_fill_ip6(&((yyval.net)), (yyvsp[0].ip6), IP6_MAX_PREFIX_LENGTH); }
#line 6717 "obj/conf/cf-parse.tab.c"
    break;

  case 61: /* net_or_ipa: CF_SYM_KNOWN  */
#line 348 "conf/confbase.Y"
                {
     if ((yyvsp[0].s)->class == (SYM_CONSTANT | T_IP))
       net_fill_ip_host(&((yyval.net)), SYM_VAL((yyvsp[0].s)).ip);
     else if (((yyvsp[0].s)->class == (SYM_CONSTANT | T_NET)) && net_is_ip(SYM_VAL((yyvsp[0].s)).net))
       (yyval.net) = * SYM_VAL((yyvsp[0].s)).net;
     else
       cf_error("IP address or network constant expected");
   }
#line 6730 "obj/conf/cf-parse.tab.c"
    break;

  case 62: /* label_stack_start: NUM  */
#line 359 "conf/confbase.Y"
{
  (yyval.mls) = cfg_allocz(sizeof(mpls_label_stack));
  (yyval.mls)->len = 1;
  (yyval.mls)->stack[0] = (yyvsp[0].i);
}
#line 6740 "obj/conf/cf-parse.tab.c"
    break;

  case 64: /* label_stack: label_stack '/' NUM  */
#line 367 "conf/confbase.Y"
                        {
    if ((yyvsp[-2].mls)->len >= MPLS_MAX_LABEL_STACK)
      cf_error("Too many labels in stack");
    (yyvsp[-2].mls)->stack[(yyvsp[-2].mls)->len++] = (yyvsp[0].i);
    (yyval.mls) = (yyvsp[-2].mls);
  }
#line 6751 "obj/conf/cf-parse.tab.c"
    break;

  case 65: /* time: TEXT  */
#line 376 "conf/confbase.Y"
        {
     (yyval.time) = tm_parse_time((yyvsp[0].t));
     if (!(yyval.time))
       cf_error("Invalid date/time");
   }
#line 6761 "obj/conf/cf-parse.tab.c"
    break;

  case 67: /* text: CF_SYM_KNOWN  */
#line 385 "conf/confbase.Y"
                {
     if ((yyvsp[0].s)->class != (SYM_CONSTANT | T_STRING)) cf_error("String constant expected");
     (yyval.t) = SYM_VAL((yyvsp[0].s)).s;
   }
#line 6770 "obj/conf/cf-parse.tab.c"
    break;

  case 69: /* opttext: %empty  */
#line 393 "conf/confbase.Y"
               { (yyval.t) = NULL; }
#line 6776 "obj/conf/cf-parse.tab.c"
    break;

  case 70: /* flow_num_op: TRUE  */
#line 37 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_TRUE; }
#line 6782 "obj/conf/cf-parse.tab.c"
    break;

  case 71: /* flow_num_op: '='  */
#line 38 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_EQ;  }
#line 6788 "obj/conf/cf-parse.tab.c"
    break;

  case 72: /* flow_num_op: NEQ  */
#line 39 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_NEQ; }
#line 6794 "obj/conf/cf-parse.tab.c"
    break;

  case 73: /* flow_num_op: '<'  */
#line 40 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_LT;  }
#line 6800 "obj/conf/cf-parse.tab.c"
    break;

  case 74: /* flow_num_op: LEQ  */
#line 41 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_LEQ; }
#line 6806 "obj/conf/cf-parse.tab.c"
    break;

  case 75: /* flow_num_op: '>'  */
#line 42 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_GT;  }
#line 6812 "obj/conf/cf-parse.tab.c"
    break;

  case 76: /* flow_num_op: GEQ  */
#line 43 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_GEQ; }
#line 6818 "obj/conf/cf-parse.tab.c"
    break;

  case 77: /* flow_num_op: FALSE  */
#line 44 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_FALSE; }
#line 6824 "obj/conf/cf-parse.tab.c"
    break;

  case 78: /* flow_logic_op: OR  */
#line 48 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_OR; }
#line 6830 "obj/conf/cf-parse.tab.c"
    break;

  case 79: /* flow_logic_op: AND  */
#line 49 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_OP_AND; }
#line 6836 "obj/conf/cf-parse.tab.c"
    break;

  case 80: /* flow_num_type_: PROTO  */
#line 53 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_IP_PROTOCOL; }
#line 6842 "obj/conf/cf-parse.tab.c"
    break;

  case 81: /* flow_num_type_: NEXT HEADER  */
#line 54 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_NEXT_HEADER; }
#line 6848 "obj/conf/cf-parse.tab.c"
    break;

  case 82: /* flow_num_type_: PORT  */
#line 55 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_PORT; }
#line 6854 "obj/conf/cf-parse.tab.c"
    break;

  case 83: /* flow_num_type_: DPORT  */
#line 56 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_DST_PORT; }
#line 6860 "obj/conf/cf-parse.tab.c"
    break;

  case 84: /* flow_num_type_: SPORT  */
#line 57 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_SRC_PORT; }
#line 6866 "obj/conf/cf-parse.tab.c"
    break;

  case 85: /* flow_num_type_: ICMP TYPE  */
#line 58 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_ICMP_TYPE; }
#line 6872 "obj/conf/cf-parse.tab.c"
    break;

  case 86: /* flow_num_type_: ICMP CODE  */
#line 59 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_ICMP_CODE; }
#line 6878 "obj/conf/cf-parse.tab.c"
    break;

  case 87: /* flow_num_type_: LENGTH  */
#line 60 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_PACKET_LENGTH; }
#line 6884 "obj/conf/cf-parse.tab.c"
    break;

  case 88: /* flow_num_type_: DSCP  */
#line 61 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_DSCP; }
#line 6890 "obj/conf/cf-parse.tab.c"
    break;

  case 89: /* flow_num_type_: LABEL  */
#line 62 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_LABEL; }
#line 6896 "obj/conf/cf-parse.tab.c"
    break;

  case 90: /* flow_num_type: flow_num_type_  */
#line 65 "conf/flowspec.Y"
                             { flow_builder_set_type(this_flow, (yyvsp[0].i32)); }
#line 6902 "obj/conf/cf-parse.tab.c"
    break;

  case 91: /* flow_flag_type: TCP FLAGS  */
#line 66 "conf/flowspec.Y"
                             { flow_builder_set_type(this_flow, FLOW_TYPE_TCP_FLAGS); }
#line 6908 "obj/conf/cf-parse.tab.c"
    break;

  case 92: /* flow_frag_type: FRAGMENT  */
#line 67 "conf/flowspec.Y"
                             { flow_builder_set_type(this_flow, FLOW_TYPE_FRAGMENT); }
#line 6914 "obj/conf/cf-parse.tab.c"
    break;

  case 93: /* flow_srcdst: DST  */
#line 70 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_DST_PREFIX; }
#line 6920 "obj/conf/cf-parse.tab.c"
    break;

  case 94: /* flow_srcdst: SRC  */
#line 71 "conf/flowspec.Y"
                { (yyval.i32) = FLOW_TYPE_SRC_PREFIX; }
#line 6926 "obj/conf/cf-parse.tab.c"
    break;

  case 95: /* flow_num_opts: flow_num_op expr  */
#line 75 "conf/flowspec.Y"
                    {
     flow_check_cf_value_length(this_flow, (yyvsp[0].i));
     flow_builder_add_op_val(this_flow, (yyvsp[-1].i32), (yyvsp[0].i));
   }
#line 6935 "obj/conf/cf-parse.tab.c"
    break;

  case 96: /* flow_num_opts: flow_num_opts flow_logic_op flow_num_op expr  */
#line 79 "conf/flowspec.Y"
                                                {
     flow_check_cf_value_length(this_flow, (yyvsp[0].i));
     flow_builder_add_op_val(this_flow, (yyvsp[-2].i32) | (yyvsp[-1].i32), (yyvsp[0].i));
   }
#line 6944 "obj/conf/cf-parse.tab.c"
    break;

  case 99: /* flow_num_opt_ext_expr: expr  */
#line 88 "conf/flowspec.Y"
        {
     flow_check_cf_value_length(this_flow, (yyvsp[0].i));
     flow_builder_add_op_val(this_flow, FLOW_OP_EQ, (yyvsp[0].i));
   }
#line 6953 "obj/conf/cf-parse.tab.c"
    break;

  case 100: /* flow_num_opt_ext_expr: expr DDOT expr  */
#line 92 "conf/flowspec.Y"
                  {
     flow_check_cf_value_length(this_flow, (yyvsp[-2].i));
     flow_check_cf_value_length(this_flow, (yyvsp[0].i));
     flow_builder_add_op_val(this_flow, FLOW_OP_GEQ, (yyvsp[-2].i));
     flow_builder_add_op_val(this_flow, FLOW_OP_AND | FLOW_OP_LEQ, (yyvsp[0].i));
   }
#line 6964 "obj/conf/cf-parse.tab.c"
    break;

  case 103: /* flow_bmk_opts: flow_neg expr '/' expr  */
#line 106 "conf/flowspec.Y"
                          {
     flow_check_cf_bmk_values(this_flow, (yyvsp[-3].i32), (yyvsp[-2].i), (yyvsp[0].i));
     flow_builder_add_val_mask(this_flow, (yyvsp[-3].i32), (yyvsp[-2].i), (yyvsp[0].i));
   }
#line 6973 "obj/conf/cf-parse.tab.c"
    break;

  case 104: /* flow_bmk_opts: flow_bmk_opts flow_logic_op flow_neg expr '/' expr  */
#line 110 "conf/flowspec.Y"
                                                      {
     flow_check_cf_bmk_values(this_flow, (yyvsp[-3].i32), (yyvsp[-2].i), (yyvsp[0].i));
     flow_builder_add_val_mask(this_flow, (yyvsp[-4].i32) | (yyvsp[-3].i32), (yyvsp[-2].i), (yyvsp[0].i));
   }
#line 6982 "obj/conf/cf-parse.tab.c"
    break;

  case 105: /* flow_bmk_opts: flow_bmk_opts ',' flow_neg expr '/' expr  */
#line 114 "conf/flowspec.Y"
                                            {
     flow_check_cf_bmk_values(this_flow, (yyvsp[-3].i32), (yyvsp[-2].i), (yyvsp[0].i));
     flow_builder_add_val_mask(this_flow, 0x40 | (yyvsp[-3].i32), (yyvsp[-2].i), (yyvsp[0].i)); /* AND */
   }
#line 6991 "obj/conf/cf-parse.tab.c"
    break;

  case 106: /* flow_neg: %empty  */
#line 121 "conf/flowspec.Y"
                { (yyval.i32) = 0x00; }
#line 6997 "obj/conf/cf-parse.tab.c"
    break;

  case 107: /* flow_neg: '!'  */
#line 122 "conf/flowspec.Y"
                { (yyval.i32) = 0x02; }
#line 7003 "obj/conf/cf-parse.tab.c"
    break;

  case 108: /* flow_frag_val: DONT_FRAGMENT  */
#line 126 "conf/flowspec.Y"
                  { (yyval.i32) = 1; }
#line 7009 "obj/conf/cf-parse.tab.c"
    break;

  case 109: /* flow_frag_val: IS_FRAGMENT  */
#line 127 "conf/flowspec.Y"
                  { (yyval.i32) = 2; }
#line 7015 "obj/conf/cf-parse.tab.c"
    break;

  case 110: /* flow_frag_val: FIRST_FRAGMENT  */
#line 128 "conf/flowspec.Y"
                  { (yyval.i32) = 4; }
#line 7021 "obj/conf/cf-parse.tab.c"
    break;

  case 111: /* flow_frag_val: LAST_FRAGMENT  */
#line 129 "conf/flowspec.Y"
                  { (yyval.i32) = 8; }
#line 7027 "obj/conf/cf-parse.tab.c"
    break;

  case 112: /* flow_frag_opts: flow_neg flow_frag_val  */
#line 133 "conf/flowspec.Y"
                          {
     flow_builder_add_val_mask(this_flow, 0, ((yyvsp[-1].i32) ? 0 : (yyvsp[0].i32)), (yyvsp[0].i32));
   }
#line 7035 "obj/conf/cf-parse.tab.c"
    break;

  case 113: /* flow_frag_opts: flow_frag_opts flow_logic_op flow_neg flow_frag_val  */
#line 136 "conf/flowspec.Y"
                                                       {
     flow_builder_add_val_mask(this_flow, (yyvsp[-2].i32), ((yyvsp[-1].i32) ? 0 : (yyvsp[0].i32)), (yyvsp[0].i32));
   }
#line 7043 "obj/conf/cf-parse.tab.c"
    break;

  case 114: /* flow_frag_opts: flow_frag_opts ',' flow_neg flow_frag_val  */
#line 139 "conf/flowspec.Y"
                                             {
     flow_builder_add_val_mask(this_flow, 0x40, ((yyvsp[-1].i32) ? 0 : (yyvsp[0].i32)), (yyvsp[0].i32)); /* AND */
   }
#line 7051 "obj/conf/cf-parse.tab.c"
    break;

  case 115: /* flow4_item: flow_srcdst net_ip4  */
#line 145 "conf/flowspec.Y"
                       {
     flow_builder_set_type(this_flow, (yyvsp[-1].i32));
     flow_builder4_add_pfx(this_flow, (net_addr_ip4 *) &((yyvsp[0].net)));
   }
#line 7060 "obj/conf/cf-parse.tab.c"
    break;

  case 119: /* flow6_item: flow_srcdst net_ip6  */
#line 155 "conf/flowspec.Y"
                       {
     flow_builder_set_type(this_flow, (yyvsp[-1].i32));
     flow_builder6_add_pfx(this_flow, (net_addr_ip6 *) &((yyvsp[0].net)), 0);
   }
#line 7069 "obj/conf/cf-parse.tab.c"
    break;

  case 120: /* flow6_item: flow_srcdst net_ip6 OFFSET NUM  */
#line 159 "conf/flowspec.Y"
                                  {
     if ((yyvsp[0].i) > (yyvsp[-2].net).pxlen)
       cf_error("Prefix offset is higher than prefix length");
     flow_builder_set_type(this_flow, (yyvsp[-3].i32));
     flow_builder6_add_pfx(this_flow, (net_addr_ip6 *) &((yyvsp[-2].net)), (yyvsp[0].i));
   }
#line 7080 "obj/conf/cf-parse.tab.c"
    break;

  case 128: /* flow_builder_init: %empty  */
#line 181 "conf/flowspec.Y"
{
  if (this_flow == NULL)
    this_flow = flow_builder_init(config_pool);	  /* FIXME: This should be allocated from tmp in future */
  else
    flow_builder_clear(this_flow);
}
#line 7091 "obj/conf/cf-parse.tab.c"
    break;

  case 129: /* flow_builder_set_ipv4: %empty  */
#line 188 "conf/flowspec.Y"
                       { this_flow->ipv6 = 0; }
#line 7097 "obj/conf/cf-parse.tab.c"
    break;

  case 130: /* flow_builder_set_ipv6: %empty  */
#line 189 "conf/flowspec.Y"
                       { this_flow->ipv6 = 1; }
#line 7103 "obj/conf/cf-parse.tab.c"
    break;

  case 131: /* net_flow4_: FLOW4 '{' flow_builder_init flow_builder_set_ipv4 flow4_opts '}'  */
#line 192 "conf/flowspec.Y"
{
  (yyval.net_ptr) = (net_addr *) flow_builder4_finalize(this_flow, cfg_mem);
  flow4_validate_cf((net_addr_flow4 *) (yyval.net_ptr));
}
#line 7112 "obj/conf/cf-parse.tab.c"
    break;

  case 132: /* net_flow6_: FLOW6 '{' flow_builder_init flow_builder_set_ipv6 flow6_opts '}'  */
#line 198 "conf/flowspec.Y"
{
  (yyval.net_ptr) = (net_addr *) flow_builder6_finalize(this_flow, cfg_mem);
  flow6_validate_cf((net_addr_flow6 *) (yyval.net_ptr));
}
#line 7121 "obj/conf/cf-parse.tab.c"
    break;

  case 142: /* $@1: %empty  */
#line 348 "filter/config.Y"
                 { (yyvsp[0].s) = cf_define_symbol((yyvsp[0].s), SYM_FILTER, filter, NULL); cf_push_scope( (yyvsp[0].s) ); }
#line 7127 "obj/conf/cf-parse.tab.c"
    break;

  case 143: /* filter_def: FILTER symbol $@1 filter_body  */
#line 349 "filter/config.Y"
                 {
     struct filter *f = cfg_alloc(sizeof(struct filter));
     *f = (struct filter) { .sym = (yyvsp[-2].s), .root = (yyvsp[0].fl) };
     (yyvsp[-2].s)->filter = f;

     cf_pop_scope();
   }
#line 7139 "obj/conf/cf-parse.tab.c"
    break;

  case 145: /* filter_eval: EVAL term  */
#line 360 "filter/config.Y"
             { f_eval_int(f_linearize((yyvsp[0].x), 1)); }
#line 7145 "obj/conf/cf-parse.tab.c"
    break;

  case 147: /* custom_attr: ATTRIBUTE type symbol ';'  */
#line 364 "filter/config.Y"
                                       {
  cf_define_symbol((yyvsp[-1].s), SYM_ATTRIBUTE, attribute, ca_lookup(new_config->pool, (yyvsp[-1].s)->name, (yyvsp[-2].i))->fda);
}
#line 7153 "obj/conf/cf-parse.tab.c"
    break;

  case 149: /* bt_test_suite: BT_TEST_SUITE '(' CF_SYM_KNOWN ',' text ')'  */
#line 370 "filter/config.Y"
                                             {
  cf_assert_symbol((yyvsp[-3].s), SYM_FUNCTION);
  struct f_bt_test_suite *t = cfg_allocz(sizeof(struct f_bt_test_suite));
  t->fn = (yyvsp[-3].s)->function;
  t->fn_name = (yyvsp[-3].s)->name;
  t->dsc = (yyvsp[-1].t);

  add_tail(&new_config->tests, &t->n);
 }
#line 7167 "obj/conf/cf-parse.tab.c"
    break;

  case 151: /* bt_test_same: BT_TEST_SAME '(' CF_SYM_KNOWN ',' CF_SYM_KNOWN ',' NUM ')'  */
#line 383 "filter/config.Y"
                                                            {
  cf_assert_symbol((yyvsp[-5].s), SYM_FUNCTION);
  cf_assert_symbol((yyvsp[-3].s), SYM_FUNCTION);
  struct f_bt_test_suite *t = cfg_allocz(sizeof(struct f_bt_test_suite));
  t->fn = (yyvsp[-5].s)->function;
  t->cmp = (yyvsp[-3].s)->function;
  t->result = (yyvsp[-1].i);
  t->fn_name = (yyvsp[-5].s)->name;
  t->dsc = (yyvsp[-3].s)->name;
  add_tail(&new_config->tests, &t->n);
 }
#line 7183 "obj/conf/cf-parse.tab.c"
    break;

  case 152: /* type: INT  */
#line 397 "filter/config.Y"
       { (yyval.i) = T_INT; }
#line 7189 "obj/conf/cf-parse.tab.c"
    break;

  case 153: /* type: BOOL  */
#line 398 "filter/config.Y"
        { (yyval.i) = T_BOOL; }
#line 7195 "obj/conf/cf-parse.tab.c"
    break;

  case 154: /* type: IP  */
#line 399 "filter/config.Y"
      { (yyval.i) = T_IP; }
#line 7201 "obj/conf/cf-parse.tab.c"
    break;

  case 155: /* type: RD  */
#line 400 "filter/config.Y"
      { (yyval.i) = T_RD; }
#line 7207 "obj/conf/cf-parse.tab.c"
    break;

  case 156: /* type: PREFIX  */
#line 401 "filter/config.Y"
          { (yyval.i) = T_NET; }
#line 7213 "obj/conf/cf-parse.tab.c"
    break;

  case 157: /* type: PAIR  */
#line 402 "filter/config.Y"
        { (yyval.i) = T_PAIR; }
#line 7219 "obj/conf/cf-parse.tab.c"
    break;

  case 158: /* type: QUAD  */
#line 403 "filter/config.Y"
        { (yyval.i) = T_QUAD; }
#line 7225 "obj/conf/cf-parse.tab.c"
    break;

  case 159: /* type: EC  */
#line 404 "filter/config.Y"
      { (yyval.i) = T_EC; }
#line 7231 "obj/conf/cf-parse.tab.c"
    break;

  case 160: /* type: LC  */
#line 405 "filter/config.Y"
      { (yyval.i) = T_LC; }
#line 7237 "obj/conf/cf-parse.tab.c"
    break;

  case 161: /* type: STRING  */
#line 406 "filter/config.Y"
          { (yyval.i) = T_STRING; }
#line 7243 "obj/conf/cf-parse.tab.c"
    break;

  case 162: /* type: BGPMASK  */
#line 407 "filter/config.Y"
           { (yyval.i) = T_PATH_MASK; }
#line 7249 "obj/conf/cf-parse.tab.c"
    break;

  case 163: /* type: BGPPATH  */
#line 408 "filter/config.Y"
           { (yyval.i) = T_PATH; }
#line 7255 "obj/conf/cf-parse.tab.c"
    break;

  case 164: /* type: CLIST  */
#line 409 "filter/config.Y"
         { (yyval.i) = T_CLIST; }
#line 7261 "obj/conf/cf-parse.tab.c"
    break;

  case 165: /* type: ECLIST  */
#line 410 "filter/config.Y"
          { (yyval.i) = T_ECLIST; }
#line 7267 "obj/conf/cf-parse.tab.c"
    break;

  case 166: /* type: LCLIST  */
#line 411 "filter/config.Y"
          { (yyval.i) = T_LCLIST; }
#line 7273 "obj/conf/cf-parse.tab.c"
    break;

  case 167: /* type: type SET  */
#line 412 "filter/config.Y"
            {
	switch ((yyvsp[-1].i)) {
	  case T_INT:
	  case T_PAIR:
	  case T_QUAD:
	  case T_EC:
	  case T_LC:
	  case T_RD:
	  case T_IP:
	       (yyval.i) = T_SET;
	       break;

	  case T_NET:
	       (yyval.i) = T_PREFIX_SET;
	    break;

	  default:
		cf_error( "You can't create sets of this type." );
	}
   }
#line 7298 "obj/conf/cf-parse.tab.c"
    break;

  case 168: /* function_argsn: %empty  */
#line 435 "filter/config.Y"
               { (yyval.fa) = NULL; }
#line 7304 "obj/conf/cf-parse.tab.c"
    break;

  case 169: /* function_argsn: function_argsn type symbol ';'  */
#line 436 "filter/config.Y"
                                  {
     if ((yyvsp[-1].s)->scope->slots >= 0xfe) cf_error("Too many declarations, at most 255 allowed");
     (yyval.fa) = cfg_alloc(sizeof(struct f_arg));
     (yyval.fa)->arg = cf_define_symbol((yyvsp[-1].s), SYM_VARIABLE | (yyvsp[-2].i), offset, sym_->scope->slots++);
     (yyval.fa)->next = (yyvsp[-3].fa);
   }
#line 7315 "obj/conf/cf-parse.tab.c"
    break;

  case 170: /* function_args: '(' ')'  */
#line 445 "filter/config.Y"
           { (yyval.fa) = NULL; }
#line 7321 "obj/conf/cf-parse.tab.c"
    break;

  case 171: /* function_args: '(' function_argsn type symbol ')'  */
#line 446 "filter/config.Y"
                                      {
     (yyval.fa) = cfg_alloc(sizeof(struct f_arg));
     (yyval.fa)->arg = cf_define_symbol((yyvsp[-1].s), SYM_VARIABLE | (yyvsp[-2].i), offset, sym_->scope->slots++);
     (yyval.fa)->next = (yyvsp[-3].fa);
   }
#line 7331 "obj/conf/cf-parse.tab.c"
    break;

  case 172: /* function_vars: %empty  */
#line 454 "filter/config.Y"
               { (yyval.i) = 0; }
#line 7337 "obj/conf/cf-parse.tab.c"
    break;

  case 173: /* function_vars: function_vars type symbol ';'  */
#line 455 "filter/config.Y"
                                 {
     cf_define_symbol((yyvsp[-1].s), SYM_VARIABLE | (yyvsp[-2].i), offset, f_new_var(sym_->scope));
     (yyval.i) = (yyvsp[-3].i) + 1;
   }
#line 7346 "obj/conf/cf-parse.tab.c"
    break;

  case 175: /* filter: CF_SYM_KNOWN  */
#line 464 "filter/config.Y"
                {
     cf_assert_symbol((yyvsp[0].s), SYM_FILTER);
     (yyval.f) = (yyvsp[0].s)->filter;
   }
#line 7355 "obj/conf/cf-parse.tab.c"
    break;

  case 176: /* $@2: %empty  */
#line 468 "filter/config.Y"
   { cf_push_scope(NULL); }
#line 7361 "obj/conf/cf-parse.tab.c"
    break;

  case 177: /* filter: $@2 filter_body  */
#line 468 "filter/config.Y"
                                        {
     struct filter *f = cfg_alloc(sizeof(struct filter));
     *f = (struct filter) { .root = (yyvsp[0].fl) };
     (yyval.f) = f;

     cf_pop_scope();
   }
#line 7373 "obj/conf/cf-parse.tab.c"
    break;

  case 178: /* where_filter: WHERE term  */
#line 478 "filter/config.Y"
              {
     /* Construct 'IF term THEN { ACCEPT; } ELSE { REJECT; }' */
     (yyval.f) = f_new_where((yyvsp[0].x));
   }
#line 7382 "obj/conf/cf-parse.tab.c"
    break;

  case 179: /* function_body: function_vars '{' cmds '}'  */
#line 485 "filter/config.Y"
                              {
     (yyval.fl) = f_linearize((yyvsp[-1].x), 0);
     (yyval.fl)->vars = (yyvsp[-3].i);
   }
#line 7391 "obj/conf/cf-parse.tab.c"
    break;

  case 181: /* $@3: %empty  */
#line 493 "filter/config.Y"
                   {
     DBG( "Beginning of function %s\n", (yyvsp[0].s)->name );
     (yyvsp[0].s) = cf_define_symbol((yyvsp[0].s), SYM_FUNCTION, function, NULL);
     cf_push_scope((yyvsp[0].s));
   }
#line 7401 "obj/conf/cf-parse.tab.c"
    break;

  case 182: /* $@4: %empty  */
#line 497 "filter/config.Y"
                   {
     /* Make dummy f_line for storing function prototype */
     struct f_line *dummy = cfg_allocz(sizeof(struct f_line));
     (yyvsp[-2].s)->function = dummy;

     /* Revert the args */
     while ((yyvsp[0].fa)) {
       struct f_arg *tmp = (yyvsp[0].fa);
       (yyvsp[0].fa) = (yyvsp[0].fa)->next;

       tmp->next = dummy->arg_list;
       dummy->arg_list = tmp;
       dummy->args++;
     }
   }
#line 7421 "obj/conf/cf-parse.tab.c"
    break;

  case 183: /* function_def: FUNCTION symbol $@3 function_args $@4 function_body  */
#line 511 "filter/config.Y"
                   {
     (yyvsp[0].fl)->args = (yyvsp[-4].s)->function->args;
     (yyvsp[0].fl)->arg_list = (yyvsp[-4].s)->function->arg_list;
     (yyvsp[-4].s)->function = (yyvsp[0].fl);
     cf_pop_scope();
   }
#line 7432 "obj/conf/cf-parse.tab.c"
    break;

  case 184: /* cmds: %empty  */
#line 521 "filter/config.Y"
                  { (yyval.x) = NULL; }
#line 7438 "obj/conf/cf-parse.tab.c"
    break;

  case 185: /* cmds: cmds_int  */
#line 522 "filter/config.Y"
            { (yyval.x) = (yyvsp[0].xp).begin; }
#line 7444 "obj/conf/cf-parse.tab.c"
    break;

  case 186: /* $@5: %empty  */
#line 525 "filter/config.Y"
             { cf_push_soft_scope(); }
#line 7450 "obj/conf/cf-parse.tab.c"
    break;

  case 187: /* cmds_scoped: $@5 cmds  */
#line 525 "filter/config.Y"
                                            { cf_pop_soft_scope(); (yyval.x) = (yyvsp[0].x); }
#line 7456 "obj/conf/cf-parse.tab.c"
    break;

  case 190: /* cmd_prep: cmd_var  */
#line 529 "filter/config.Y"
                  {
  (yyval.xp).begin = (yyval.xp).end = (yyvsp[0].x);
  if ((yyvsp[0].x))
    while ((yyval.xp).end->next)
      (yyval.xp).end = (yyval.xp).end->next;
}
#line 7467 "obj/conf/cf-parse.tab.c"
    break;

  case 192: /* cmds_int: cmds_int cmd_prep  */
#line 538 "filter/config.Y"
                     {
  if (!(yyvsp[-1].xp).begin)
    (yyval.xp) = (yyvsp[0].xp);
  else if (!(yyvsp[0].xp).begin)
    (yyval.xp) = (yyvsp[-1].xp);
  else {
    (yyval.xp).begin = (yyvsp[-1].xp).begin;
    (yyval.xp).end = (yyvsp[0].xp).end;
    (yyvsp[-1].xp).end->next = (yyvsp[0].xp).begin;
  }
 }
#line 7483 "obj/conf/cf-parse.tab.c"
    break;

  case 193: /* fipa: IP4  */
#line 555 "filter/config.Y"
                          { (yyval.v).type = T_IP; (yyval.v).val.ip = ipa_from_ip4((yyvsp[0].ip4)); }
#line 7489 "obj/conf/cf-parse.tab.c"
    break;

  case 194: /* fipa: IP6  */
#line 556 "filter/config.Y"
                          { (yyval.v).type = T_IP; (yyval.v).val.ip = ipa_from_ip6((yyvsp[0].ip6)); }
#line 7495 "obj/conf/cf-parse.tab.c"
    break;

  case 195: /* set_atom: NUM  */
#line 569 "filter/config.Y"
          { (yyval.v).type = T_INT; (yyval.v).val.i = (yyvsp[0].i); }
#line 7501 "obj/conf/cf-parse.tab.c"
    break;

  case 196: /* set_atom: fipa  */
#line 570 "filter/config.Y"
          { (yyval.v) = (yyvsp[0].v); }
#line 7507 "obj/conf/cf-parse.tab.c"
    break;

  case 197: /* set_atom: VPN_RD  */
#line 571 "filter/config.Y"
          { (yyval.v).type = T_RD; (yyval.v).val.ec = (yyvsp[0].i64); }
#line 7513 "obj/conf/cf-parse.tab.c"
    break;

  case 198: /* set_atom: ENUM  */
#line 572 "filter/config.Y"
          { (yyval.v).type = pair_a((yyvsp[0].i)); (yyval.v).val.i = pair_b((yyvsp[0].i)); }
#line 7519 "obj/conf/cf-parse.tab.c"
    break;

  case 199: /* set_atom: '(' term ')'  */
#line 573 "filter/config.Y"
                {
     if (f_eval(f_linearize((yyvsp[-1].x), 1), cfg_mem, &((yyval.v))) > F_RETURN) cf_error("Runtime error");
     if (!f_valid_set_type((yyval.v).type)) cf_error("Set-incompatible type");
   }
#line 7528 "obj/conf/cf-parse.tab.c"
    break;

  case 200: /* set_atom: CF_SYM_KNOWN  */
#line 577 "filter/config.Y"
                {
     cf_assert_symbol((yyvsp[0].s), SYM_CONSTANT);
     if (!f_valid_set_type(SYM_TYPE((yyvsp[0].s)))) cf_error("%s: set-incompatible type", (yyvsp[0].s)->name);
     (yyval.v) = *(yyvsp[0].s)->val;
   }
#line 7538 "obj/conf/cf-parse.tab.c"
    break;

  case 201: /* switch_atom: NUM  */
#line 585 "filter/config.Y"
         { (yyval.v).type = T_INT; (yyval.v).val.i = (yyvsp[0].i); }
#line 7544 "obj/conf/cf-parse.tab.c"
    break;

  case 202: /* switch_atom: '(' term ')'  */
#line 586 "filter/config.Y"
                { (yyval.v).type = T_INT; (yyval.v).val.i = f_eval_int(f_linearize((yyvsp[-1].x), 1)); }
#line 7550 "obj/conf/cf-parse.tab.c"
    break;

  case 203: /* switch_atom: fipa  */
#line 587 "filter/config.Y"
         { (yyval.v) = (yyvsp[0].v); }
#line 7556 "obj/conf/cf-parse.tab.c"
    break;

  case 204: /* switch_atom: ENUM  */
#line 588 "filter/config.Y"
         { (yyval.v).type = pair_a((yyvsp[0].i)); (yyval.v).val.i = pair_b((yyvsp[0].i)); }
#line 7562 "obj/conf/cf-parse.tab.c"
    break;

  case 205: /* cnum: term  */
#line 592 "filter/config.Y"
        { (yyval.i32) = f_eval_int(f_linearize((yyvsp[0].x), 1)); }
#line 7568 "obj/conf/cf-parse.tab.c"
    break;

  case 206: /* pair_item: '(' cnum ',' cnum ')'  */
#line 595 "filter/config.Y"
                                        { (yyval.e) = f_new_pair_item((yyvsp[-3].i32), (yyvsp[-3].i32), (yyvsp[-1].i32), (yyvsp[-1].i32)); }
#line 7574 "obj/conf/cf-parse.tab.c"
    break;

  case 207: /* pair_item: '(' cnum ',' cnum DDOT cnum ')'  */
#line 596 "filter/config.Y"
                                        { (yyval.e) = f_new_pair_item((yyvsp[-5].i32), (yyvsp[-5].i32), (yyvsp[-3].i32), (yyvsp[-1].i32)); }
#line 7580 "obj/conf/cf-parse.tab.c"
    break;

  case 208: /* pair_item: '(' cnum ',' '*' ')'  */
#line 597 "filter/config.Y"
                                        { (yyval.e) = f_new_pair_item((yyvsp[-3].i32), (yyvsp[-3].i32), 0, CC_ALL); }
#line 7586 "obj/conf/cf-parse.tab.c"
    break;

  case 209: /* pair_item: '(' cnum DDOT cnum ',' cnum ')'  */
#line 598 "filter/config.Y"
                                        { (yyval.e) = f_new_pair_set((yyvsp[-5].i32), (yyvsp[-3].i32), (yyvsp[-1].i32), (yyvsp[-1].i32)); }
#line 7592 "obj/conf/cf-parse.tab.c"
    break;

  case 210: /* pair_item: '(' cnum DDOT cnum ',' cnum DDOT cnum ')'  */
#line 599 "filter/config.Y"
                                             { (yyval.e) = f_new_pair_set((yyvsp[-7].i32), (yyvsp[-5].i32), (yyvsp[-3].i32), (yyvsp[-1].i32)); }
#line 7598 "obj/conf/cf-parse.tab.c"
    break;

  case 211: /* pair_item: '(' cnum DDOT cnum ',' '*' ')'  */
#line 600 "filter/config.Y"
                                        { (yyval.e) = f_new_pair_item((yyvsp[-5].i32), (yyvsp[-3].i32), 0, CC_ALL); }
#line 7604 "obj/conf/cf-parse.tab.c"
    break;

  case 212: /* pair_item: '(' '*' ',' cnum ')'  */
#line 601 "filter/config.Y"
                                        { (yyval.e) = f_new_pair_set(0, CC_ALL, (yyvsp[-1].i32), (yyvsp[-1].i32)); }
#line 7610 "obj/conf/cf-parse.tab.c"
    break;

  case 213: /* pair_item: '(' '*' ',' cnum DDOT cnum ')'  */
#line 602 "filter/config.Y"
                                        { (yyval.e) = f_new_pair_set(0, CC_ALL, (yyvsp[-3].i32), (yyvsp[-1].i32)); }
#line 7616 "obj/conf/cf-parse.tab.c"
    break;

  case 214: /* pair_item: '(' '*' ',' '*' ')'  */
#line 603 "filter/config.Y"
                                        { (yyval.e) = f_new_pair_item(0, CC_ALL, 0, CC_ALL); }
#line 7622 "obj/conf/cf-parse.tab.c"
    break;

  case 215: /* pair_item: '(' cnum ',' cnum ')' DDOT '(' cnum ',' cnum ')'  */
#line 605 "filter/config.Y"
   { (yyval.e) = f_new_pair_item((yyvsp[-9].i32), (yyvsp[-3].i32), (yyvsp[-7].i32), (yyvsp[-1].i32)); }
#line 7628 "obj/conf/cf-parse.tab.c"
    break;

  case 216: /* ec_kind: RT  */
#line 609 "filter/config.Y"
      { (yyval.ecs) = EC_RT; }
#line 7634 "obj/conf/cf-parse.tab.c"
    break;

  case 217: /* ec_kind: RO  */
#line 610 "filter/config.Y"
      { (yyval.ecs) = EC_RO; }
#line 7640 "obj/conf/cf-parse.tab.c"
    break;

  case 218: /* ec_kind: UNKNOWN NUM  */
#line 611 "filter/config.Y"
               { (yyval.ecs) = (yyvsp[0].i); }
#line 7646 "obj/conf/cf-parse.tab.c"
    break;

  case 219: /* ec_kind: GENERIC  */
#line 612 "filter/config.Y"
           { (yyval.ecs) = EC_GENERIC; }
#line 7652 "obj/conf/cf-parse.tab.c"
    break;

  case 220: /* ec_item: '(' ec_kind ',' cnum ',' cnum ')'  */
#line 616 "filter/config.Y"
                                                { (yyval.e) = f_new_ec_item((yyvsp[-5].ecs), 0, (yyvsp[-3].i32), (yyvsp[-1].i32), (yyvsp[-1].i32)); }
#line 7658 "obj/conf/cf-parse.tab.c"
    break;

  case 221: /* ec_item: '(' ec_kind ',' cnum ',' cnum DDOT cnum ')'  */
#line 617 "filter/config.Y"
                                                { (yyval.e) = f_new_ec_item((yyvsp[-7].ecs), 0, (yyvsp[-5].i32), (yyvsp[-3].i32), (yyvsp[-1].i32)); }
#line 7664 "obj/conf/cf-parse.tab.c"
    break;

  case 222: /* ec_item: '(' ec_kind ',' cnum ',' '*' ')'  */
#line 618 "filter/config.Y"
                                                { (yyval.e) = f_new_ec_item((yyvsp[-5].ecs), 0, (yyvsp[-3].i32), 0, EC_ALL); }
#line 7670 "obj/conf/cf-parse.tab.c"
    break;

  case 223: /* lc_item: '(' cnum ',' cnum ',' cnum ')'  */
#line 622 "filter/config.Y"
                                            { (yyval.e) = f_new_lc_item((yyvsp[-5].i32), (yyvsp[-5].i32), (yyvsp[-3].i32), (yyvsp[-3].i32), (yyvsp[-1].i32), (yyvsp[-1].i32)); }
#line 7676 "obj/conf/cf-parse.tab.c"
    break;

  case 224: /* lc_item: '(' cnum ',' cnum ',' cnum DDOT cnum ')'  */
#line 623 "filter/config.Y"
                                            { (yyval.e) = f_new_lc_item((yyvsp[-7].i32), (yyvsp[-7].i32), (yyvsp[-5].i32), (yyvsp[-5].i32), (yyvsp[-3].i32), (yyvsp[-1].i32)); }
#line 7682 "obj/conf/cf-parse.tab.c"
    break;

  case 225: /* lc_item: '(' cnum ',' cnum ',' '*' ')'  */
#line 624 "filter/config.Y"
                                            { (yyval.e) = f_new_lc_item((yyvsp[-5].i32), (yyvsp[-5].i32), (yyvsp[-3].i32), (yyvsp[-3].i32), 0, LC_ALL); }
#line 7688 "obj/conf/cf-parse.tab.c"
    break;

  case 226: /* lc_item: '(' cnum ',' cnum DDOT cnum ',' '*' ')'  */
#line 625 "filter/config.Y"
                                            { (yyval.e) = f_new_lc_item((yyvsp[-7].i32), (yyvsp[-7].i32), (yyvsp[-5].i32), (yyvsp[-3].i32), 0, LC_ALL); }
#line 7694 "obj/conf/cf-parse.tab.c"
    break;

  case 227: /* lc_item: '(' cnum ',' '*' ',' '*' ')'  */
#line 626 "filter/config.Y"
                                            { (yyval.e) = f_new_lc_item((yyvsp[-5].i32), (yyvsp[-5].i32), 0, LC_ALL, 0, LC_ALL); }
#line 7700 "obj/conf/cf-parse.tab.c"
    break;

  case 228: /* lc_item: '(' cnum DDOT cnum ',' '*' ',' '*' ')'  */
#line 627 "filter/config.Y"
                                            { (yyval.e) = f_new_lc_item((yyvsp[-7].i32), (yyvsp[-5].i32), 0, LC_ALL, 0, LC_ALL); }
#line 7706 "obj/conf/cf-parse.tab.c"
    break;

  case 229: /* lc_item: '(' '*' ',' '*' ',' '*' ')'  */
#line 628 "filter/config.Y"
                                            { (yyval.e) = f_new_lc_item(0, LC_ALL, 0, LC_ALL, 0, LC_ALL); }
#line 7712 "obj/conf/cf-parse.tab.c"
    break;

  case 230: /* lc_item: '(' cnum ',' cnum ',' cnum ')' DDOT '(' cnum ',' cnum ',' cnum ')'  */
#line 630 "filter/config.Y"
   { (yyval.e) = f_new_lc_item((yyvsp[-13].i32), (yyvsp[-5].i32), (yyvsp[-11].i32), (yyvsp[-3].i32), (yyvsp[-9].i32), (yyvsp[-1].i32)); }
#line 7718 "obj/conf/cf-parse.tab.c"
    break;

  case 234: /* set_item: set_atom  */
#line 637 "filter/config.Y"
            { (yyval.e) = f_new_item((yyvsp[0].v), (yyvsp[0].v)); }
#line 7724 "obj/conf/cf-parse.tab.c"
    break;

  case 235: /* set_item: set_atom DDOT set_atom  */
#line 638 "filter/config.Y"
                          { (yyval.e) = f_new_item((yyvsp[-2].v), (yyvsp[0].v)); }
#line 7730 "obj/conf/cf-parse.tab.c"
    break;

  case 239: /* switch_item: switch_atom  */
#line 645 "filter/config.Y"
               { (yyval.e) = f_new_item((yyvsp[0].v), (yyvsp[0].v)); }
#line 7736 "obj/conf/cf-parse.tab.c"
    break;

  case 240: /* switch_item: switch_atom DDOT switch_atom  */
#line 646 "filter/config.Y"
                                { (yyval.e) = f_new_item((yyvsp[-2].v), (yyvsp[0].v)); }
#line 7742 "obj/conf/cf-parse.tab.c"
    break;

  case 242: /* set_items: set_items ',' set_item  */
#line 651 "filter/config.Y"
                          { (yyval.e) = f_merge_items((yyvsp[-2].e), (yyvsp[0].e)); }
#line 7748 "obj/conf/cf-parse.tab.c"
    break;

  case 244: /* switch_items: switch_items ',' switch_item  */
#line 656 "filter/config.Y"
                                { (yyval.e) = f_merge_items((yyvsp[-2].e), (yyvsp[0].e)); }
#line 7754 "obj/conf/cf-parse.tab.c"
    break;

  case 245: /* fprefix: net_ip_  */
#line 660 "filter/config.Y"
                { (yyval.px).net = (yyvsp[0].net); (yyval.px).lo = (yyvsp[0].net).pxlen; (yyval.px).hi = (yyvsp[0].net).pxlen; }
#line 7760 "obj/conf/cf-parse.tab.c"
    break;

  case 246: /* fprefix: net_ip_ '+'  */
#line 661 "filter/config.Y"
                { (yyval.px).net = (yyvsp[-1].net); (yyval.px).lo = (yyvsp[-1].net).pxlen; (yyval.px).hi = net_max_prefix_length[(yyvsp[-1].net).type]; }
#line 7766 "obj/conf/cf-parse.tab.c"
    break;

  case 247: /* fprefix: net_ip_ '-'  */
#line 662 "filter/config.Y"
                { (yyval.px).net = (yyvsp[-1].net); (yyval.px).lo = 0; (yyval.px).hi = (yyvsp[-1].net).pxlen; }
#line 7772 "obj/conf/cf-parse.tab.c"
    break;

  case 248: /* fprefix: net_ip_ '{' NUM ',' NUM '}'  */
#line 663 "filter/config.Y"
                               {
     (yyval.px).net = (yyvsp[-5].net); (yyval.px).lo = (yyvsp[-3].i); (yyval.px).hi = (yyvsp[-1].i);
     if (((yyvsp[-3].i) > (yyvsp[-1].i)) || ((yyvsp[-1].i) > net_max_prefix_length[(yyvsp[-5].net).type]))
       cf_error("Invalid prefix pattern range: {%u, %u}", (yyvsp[-3].i), (yyvsp[-1].i));
   }
#line 7782 "obj/conf/cf-parse.tab.c"
    break;

  case 249: /* fprefix_set: fprefix  */
#line 671 "filter/config.Y"
           { (yyval.trie) = f_new_trie(cfg_mem, 0); trie_add_prefix((yyval.trie), &((yyvsp[0].px).net), (yyvsp[0].px).lo, (yyvsp[0].px).hi); }
#line 7788 "obj/conf/cf-parse.tab.c"
    break;

  case 250: /* fprefix_set: fprefix_set ',' fprefix  */
#line 672 "filter/config.Y"
                           { (yyval.trie) = (yyvsp[-2].trie); if (!trie_add_prefix((yyval.trie), &((yyvsp[0].px).net), (yyvsp[0].px).lo, (yyvsp[0].px).hi)) cf_error("Mixed IPv4/IPv6 prefixes in prefix set"); }
#line 7794 "obj/conf/cf-parse.tab.c"
    break;

  case 251: /* switch_body: %empty  */
#line 675 "filter/config.Y"
                         { (yyval.e) = NULL; }
#line 7800 "obj/conf/cf-parse.tab.c"
    break;

  case 252: /* switch_body: switch_body switch_items ':' cmds_scoped  */
#line 676 "filter/config.Y"
                                             {
     /* Fill data fields */
     struct f_tree *t;
     struct f_line *line = f_linearize((yyvsp[0].x), 0);
     for (t = (yyvsp[-2].e); t; t = t->left)
       t->data = line;
     (yyval.e) = f_merge_items((yyvsp[-3].e), (yyvsp[-2].e));
   }
#line 7813 "obj/conf/cf-parse.tab.c"
    break;

  case 253: /* switch_body: switch_body ELSECOL cmds_scoped  */
#line 684 "filter/config.Y"
                                   {
     struct f_tree *t = f_new_tree();
     t->from.type = t->to.type = T_VOID;
     t->right = t;
     t->data = f_linearize((yyvsp[0].x), 0);
     (yyval.e) = f_merge_items((yyvsp[-2].e), t);
 }
#line 7825 "obj/conf/cf-parse.tab.c"
    break;

  case 254: /* bgp_path_expr: symbol_value  */
#line 694 "filter/config.Y"
                { (yyval.x) = (yyvsp[0].x); }
#line 7831 "obj/conf/cf-parse.tab.c"
    break;

  case 255: /* bgp_path_expr: '(' term ')'  */
#line 695 "filter/config.Y"
                { (yyval.x) = (yyvsp[-1].x); }
#line 7837 "obj/conf/cf-parse.tab.c"
    break;

  case 256: /* bgp_path: PO bgp_path_tail PC  */
#line 699 "filter/config.Y"
                         { (yyval.x) = (yyvsp[-1].x); }
#line 7843 "obj/conf/cf-parse.tab.c"
    break;

  case 257: /* bgp_path_tail: NUM bgp_path_tail  */
#line 703 "filter/config.Y"
                                { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_PATH_MASK_ITEM, .val.pmi = { .asn = (yyvsp[-1].i), .kind = PM_ASN, }, }); (yyval.x)->next = (yyvsp[0].x);  }
#line 7849 "obj/conf/cf-parse.tab.c"
    break;

  case 258: /* bgp_path_tail: NUM DDOT NUM bgp_path_tail  */
#line 704 "filter/config.Y"
                                { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_PATH_MASK_ITEM, .val.pmi = { .from = (yyvsp[-3].i), .to = (yyvsp[-1].i), .kind = PM_ASN_RANGE }, }); (yyval.x)->next = (yyvsp[0].x); }
#line 7855 "obj/conf/cf-parse.tab.c"
    break;

  case 259: /* bgp_path_tail: '[' ']' bgp_path_tail  */
#line 705 "filter/config.Y"
                         { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_PATH_MASK_ITEM, .val.pmi = { .set = NULL, .kind = PM_ASN_SET }, }); (yyval.x)->next = (yyvsp[0].x); }
#line 7861 "obj/conf/cf-parse.tab.c"
    break;

  case 260: /* bgp_path_tail: '[' set_items ']' bgp_path_tail  */
#line 706 "filter/config.Y"
                                   {
   if ((yyvsp[-2].e)->from.type != T_INT) cf_error("Only integer sets allowed in path mask");
   (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_PATH_MASK_ITEM, .val.pmi = { .set = build_tree((yyvsp[-2].e)), .kind = PM_ASN_SET }, }); (yyval.x)->next = (yyvsp[0].x);
 }
#line 7870 "obj/conf/cf-parse.tab.c"
    break;

  case 261: /* bgp_path_tail: '*' bgp_path_tail  */
#line 710 "filter/config.Y"
                                { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_PATH_MASK_ITEM, .val.pmi = { .kind = PM_ASTERISK }, }); (yyval.x)->next = (yyvsp[0].x); }
#line 7876 "obj/conf/cf-parse.tab.c"
    break;

  case 262: /* bgp_path_tail: '?' bgp_path_tail  */
#line 711 "filter/config.Y"
                                { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_PATH_MASK_ITEM, .val.pmi = { .kind = PM_QUESTION }, }); (yyval.x)->next = (yyvsp[0].x); }
#line 7882 "obj/conf/cf-parse.tab.c"
    break;

  case 263: /* bgp_path_tail: '+' bgp_path_tail  */
#line 712 "filter/config.Y"
                                { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_PATH_MASK_ITEM, .val.pmi = { .kind = PM_LOOP }, }); (yyval.x)->next = (yyvsp[0].x); }
#line 7888 "obj/conf/cf-parse.tab.c"
    break;

  case 264: /* bgp_path_tail: bgp_path_expr bgp_path_tail  */
#line 713 "filter/config.Y"
                                { (yyval.x) = (yyvsp[-1].x); (yyval.x)->next = (yyvsp[0].x); }
#line 7894 "obj/conf/cf-parse.tab.c"
    break;

  case 265: /* bgp_path_tail: %empty  */
#line 714 "filter/config.Y"
                                { (yyval.x) = NULL; }
#line 7900 "obj/conf/cf-parse.tab.c"
    break;

  case 266: /* constant: NUM  */
#line 718 "filter/config.Y"
          { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_INT, .val.i = (yyvsp[0].i), }); }
#line 7906 "obj/conf/cf-parse.tab.c"
    break;

  case 267: /* constant: TRUE  */
#line 719 "filter/config.Y"
          { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_BOOL, .val.i = 1, }); }
#line 7912 "obj/conf/cf-parse.tab.c"
    break;

  case 268: /* constant: FALSE  */
#line 720 "filter/config.Y"
          { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_BOOL, .val.i = 0, }); }
#line 7918 "obj/conf/cf-parse.tab.c"
    break;

  case 269: /* constant: TEXT  */
#line 721 "filter/config.Y"
          { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_STRING, .val.s = (yyvsp[0].t), }); }
#line 7924 "obj/conf/cf-parse.tab.c"
    break;

  case 270: /* constant: fipa  */
#line 722 "filter/config.Y"
          { (yyval.x) = f_new_inst(FI_CONSTANT, (yyvsp[0].v)); }
#line 7930 "obj/conf/cf-parse.tab.c"
    break;

  case 271: /* constant: VPN_RD  */
#line 723 "filter/config.Y"
          { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_RD, .val.ec = (yyvsp[0].i64), }); }
#line 7936 "obj/conf/cf-parse.tab.c"
    break;

  case 272: /* constant: net_  */
#line 724 "filter/config.Y"
          { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_NET, .val.net = (yyvsp[0].net_ptr), }); }
#line 7942 "obj/conf/cf-parse.tab.c"
    break;

  case 273: /* constant: '[' ']'  */
#line 725 "filter/config.Y"
           { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_SET, .val.t = NULL, }); }
#line 7948 "obj/conf/cf-parse.tab.c"
    break;

  case 274: /* constant: '[' set_items ']'  */
#line 726 "filter/config.Y"
                     {
     DBG( "We've got a set here..." );
     (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_SET, .val.t = build_tree((yyvsp[-1].e)), });
     DBG( "ook\n" );
 }
#line 7958 "obj/conf/cf-parse.tab.c"
    break;

  case 275: /* constant: '[' fprefix_set ']'  */
#line 731 "filter/config.Y"
                       { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = T_PREFIX_SET, .val.ti = (yyvsp[-1].trie), }); }
#line 7964 "obj/conf/cf-parse.tab.c"
    break;

  case 276: /* constant: ENUM  */
#line 732 "filter/config.Y"
          { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { .type = (yyvsp[0].i) >> 16, .val.i = (yyvsp[0].i) & 0xffff, }); }
#line 7970 "obj/conf/cf-parse.tab.c"
    break;

  case 277: /* constructor: '(' term ',' term ')'  */
#line 736 "filter/config.Y"
                         { (yyval.x) = f_new_inst(FI_PAIR_CONSTRUCT, (yyvsp[-3].x), (yyvsp[-1].x)); }
#line 7976 "obj/conf/cf-parse.tab.c"
    break;

  case 278: /* constructor: '(' ec_kind ',' term ',' term ')'  */
#line 737 "filter/config.Y"
                                     { (yyval.x) = f_new_inst(FI_EC_CONSTRUCT, (yyvsp[-3].x), (yyvsp[-1].x), (yyvsp[-5].ecs)); }
#line 7982 "obj/conf/cf-parse.tab.c"
    break;

  case 279: /* constructor: '(' term ',' term ',' term ')'  */
#line 738 "filter/config.Y"
                                  { (yyval.x) = f_new_inst(FI_LC_CONSTRUCT, (yyvsp[-5].x), (yyvsp[-3].x), (yyvsp[-1].x)); }
#line 7988 "obj/conf/cf-parse.tab.c"
    break;

  case 280: /* constructor: bgp_path  */
#line 739 "filter/config.Y"
            { (yyval.x) = f_new_inst(FI_PATHMASK_CONSTRUCT, (yyvsp[0].x)); }
#line 7994 "obj/conf/cf-parse.tab.c"
    break;

  case 281: /* var_list: %empty  */
#line 744 "filter/config.Y"
                      { (yyval.x) = NULL; }
#line 8000 "obj/conf/cf-parse.tab.c"
    break;

  case 282: /* var_list: term  */
#line 745 "filter/config.Y"
        { (yyval.x) = (yyvsp[0].x); }
#line 8006 "obj/conf/cf-parse.tab.c"
    break;

  case 283: /* var_list: var_list ',' term  */
#line 746 "filter/config.Y"
                     { (yyval.x) = (yyvsp[0].x); (yyval.x)->next = (yyvsp[-2].x); }
#line 8012 "obj/conf/cf-parse.tab.c"
    break;

  case 284: /* function_call: CF_SYM_KNOWN '(' var_list ')'  */
#line 750 "filter/config.Y"
   {
     if ((yyvsp[-3].s)->class != SYM_FUNCTION)
       cf_error("You can't call something which is not a function. Really.");

     /* Revert the var_list */
     struct f_inst *args = NULL;
     while ((yyvsp[-1].x)) {
       struct f_inst *tmp = (yyvsp[-1].x);
       (yyvsp[-1].x) = (yyvsp[-1].x)->next;

       tmp->next = args;
       args = tmp;
     }

     (yyval.x) = f_new_inst(FI_CALL, args, (yyvsp[-3].s));
   }
#line 8033 "obj/conf/cf-parse.tab.c"
    break;

  case 285: /* symbol_value: CF_SYM_KNOWN  */
#line 769 "filter/config.Y"
  {
    switch ((yyvsp[0].s)->class) {
      case SYM_CONSTANT_RANGE:
	(yyval.x) = f_new_inst(FI_CONSTANT, *((yyvsp[0].s)->val));
	break;
      case SYM_VARIABLE_RANGE:
	(yyval.x) = f_new_inst(FI_VAR_GET, (yyvsp[0].s));
	break;
      case SYM_ATTRIBUTE:
	(yyval.x) = f_new_inst(FI_EA_GET, *(yyvsp[0].s)->attribute);
	break;
      default:
	cf_error("Can't get value of symbol %s", (yyvsp[0].s)->name);
    }
  }
#line 8053 "obj/conf/cf-parse.tab.c"
    break;

  case 286: /* static_attr: FROM  */
#line 787 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_IP,         SA_FROM,	0); }
#line 8059 "obj/conf/cf-parse.tab.c"
    break;

  case 287: /* static_attr: GW  */
#line 788 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_IP,         SA_GW,	0); }
#line 8065 "obj/conf/cf-parse.tab.c"
    break;

  case 288: /* static_attr: NET  */
#line 789 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_NET,	  SA_NET,	1); }
#line 8071 "obj/conf/cf-parse.tab.c"
    break;

  case 289: /* static_attr: PROTO  */
#line 790 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_STRING,     SA_PROTO,	1); }
#line 8077 "obj/conf/cf-parse.tab.c"
    break;

  case 290: /* static_attr: SOURCE  */
#line 791 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_ENUM_RTS,   SA_SOURCE,	1); }
#line 8083 "obj/conf/cf-parse.tab.c"
    break;

  case 291: /* static_attr: SCOPE  */
#line 792 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_ENUM_SCOPE, SA_SCOPE,	0); }
#line 8089 "obj/conf/cf-parse.tab.c"
    break;

  case 292: /* static_attr: DEST  */
#line 793 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_ENUM_RTD,   SA_DEST,	0); }
#line 8095 "obj/conf/cf-parse.tab.c"
    break;

  case 293: /* static_attr: IFNAME  */
#line 794 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_STRING,     SA_IFNAME,	0); }
#line 8101 "obj/conf/cf-parse.tab.c"
    break;

  case 294: /* static_attr: IFINDEX  */
#line 795 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_INT,        SA_IFINDEX,	1); }
#line 8107 "obj/conf/cf-parse.tab.c"
    break;

  case 295: /* static_attr: WEIGHT  */
#line 796 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_INT,        SA_WEIGHT,	0); }
#line 8113 "obj/conf/cf-parse.tab.c"
    break;

  case 296: /* static_attr: PREFERENCE  */
#line 797 "filter/config.Y"
              { (yyval.fsa) = f_new_static_attr(T_INT,	  SA_PREF,	0); }
#line 8119 "obj/conf/cf-parse.tab.c"
    break;

  case 297: /* static_attr: GW_MPLS  */
#line 798 "filter/config.Y"
           { (yyval.fsa) = f_new_static_attr(T_INT,        SA_GW_MPLS,	0); }
#line 8125 "obj/conf/cf-parse.tab.c"
    break;

  case 298: /* term: '(' term ')'  */
#line 802 "filter/config.Y"
                        { (yyval.x) = (yyvsp[-1].x); }
#line 8131 "obj/conf/cf-parse.tab.c"
    break;

  case 299: /* term: term '+' term  */
#line 803 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_ADD, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8137 "obj/conf/cf-parse.tab.c"
    break;

  case 300: /* term: term '-' term  */
#line 804 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_SUBTRACT, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8143 "obj/conf/cf-parse.tab.c"
    break;

  case 301: /* term: term '*' term  */
#line 805 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_MULTIPLY, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8149 "obj/conf/cf-parse.tab.c"
    break;

  case 302: /* term: term '/' term  */
#line 806 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_DIVIDE, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8155 "obj/conf/cf-parse.tab.c"
    break;

  case 303: /* term: term AND term  */
#line 807 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_AND, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8161 "obj/conf/cf-parse.tab.c"
    break;

  case 304: /* term: term OR term  */
#line 808 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_OR, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8167 "obj/conf/cf-parse.tab.c"
    break;

  case 305: /* term: term '=' term  */
#line 809 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_EQ, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8173 "obj/conf/cf-parse.tab.c"
    break;

  case 306: /* term: term NEQ term  */
#line 810 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_NEQ, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8179 "obj/conf/cf-parse.tab.c"
    break;

  case 307: /* term: term '<' term  */
#line 811 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_LT, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8185 "obj/conf/cf-parse.tab.c"
    break;

  case 308: /* term: term LEQ term  */
#line 812 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_LTE, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8191 "obj/conf/cf-parse.tab.c"
    break;

  case 309: /* term: term '>' term  */
#line 813 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_LT, (yyvsp[0].x), (yyvsp[-2].x)); }
#line 8197 "obj/conf/cf-parse.tab.c"
    break;

  case 310: /* term: term GEQ term  */
#line 814 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_LTE, (yyvsp[0].x), (yyvsp[-2].x)); }
#line 8203 "obj/conf/cf-parse.tab.c"
    break;

  case 311: /* term: term '~' term  */
#line 815 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_MATCH, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8209 "obj/conf/cf-parse.tab.c"
    break;

  case 312: /* term: term NMA term  */
#line 816 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_NOT_MATCH, (yyvsp[-2].x), (yyvsp[0].x)); }
#line 8215 "obj/conf/cf-parse.tab.c"
    break;

  case 313: /* term: '!' term  */
#line 817 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_NOT, (yyvsp[0].x)); }
#line 8221 "obj/conf/cf-parse.tab.c"
    break;

  case 314: /* term: DEFINED '(' term ')'  */
#line 818 "filter/config.Y"
                        { (yyval.x) = f_new_inst(FI_DEFINED, (yyvsp[-1].x)); }
#line 8227 "obj/conf/cf-parse.tab.c"
    break;

  case 315: /* term: symbol_value  */
#line 820 "filter/config.Y"
                  { (yyval.x) = (yyvsp[0].x); }
#line 8233 "obj/conf/cf-parse.tab.c"
    break;

  case 316: /* term: constant  */
#line 821 "filter/config.Y"
            { (yyval.x) = (yyvsp[0].x); }
#line 8239 "obj/conf/cf-parse.tab.c"
    break;

  case 317: /* term: constructor  */
#line 822 "filter/config.Y"
               { (yyval.x) = (yyvsp[0].x); }
#line 8245 "obj/conf/cf-parse.tab.c"
    break;

  case 318: /* term: static_attr  */
#line 824 "filter/config.Y"
               { (yyval.x) = f_new_inst(FI_RTA_GET, (yyvsp[0].fsa)); }
#line 8251 "obj/conf/cf-parse.tab.c"
    break;

  case 319: /* term: dynamic_attr  */
#line 826 "filter/config.Y"
                { (yyval.x) = f_new_inst(FI_EA_GET, (yyvsp[0].fda)); }
#line 8257 "obj/conf/cf-parse.tab.c"
    break;

  case 320: /* term: term '.' IS_V4  */
#line 828 "filter/config.Y"
                  { (yyval.x) = f_new_inst(FI_IS_V4, (yyvsp[-2].x)); }
#line 8263 "obj/conf/cf-parse.tab.c"
    break;

  case 321: /* term: term '.' TYPE  */
#line 829 "filter/config.Y"
                 { (yyval.x) = f_new_inst(FI_TYPE, (yyvsp[-2].x)); }
#line 8269 "obj/conf/cf-parse.tab.c"
    break;

  case 322: /* term: term '.' IP  */
#line 830 "filter/config.Y"
               { (yyval.x) = f_new_inst(FI_IP, (yyvsp[-2].x)); }
#line 8275 "obj/conf/cf-parse.tab.c"
    break;

  case 323: /* term: term '.' RD  */
#line 831 "filter/config.Y"
               { (yyval.x) = f_new_inst(FI_ROUTE_DISTINGUISHER, (yyvsp[-2].x)); }
#line 8281 "obj/conf/cf-parse.tab.c"
    break;

  case 324: /* term: term '.' LEN  */
#line 832 "filter/config.Y"
                { (yyval.x) = f_new_inst(FI_LENGTH, (yyvsp[-2].x)); }
#line 8287 "obj/conf/cf-parse.tab.c"
    break;

  case 325: /* term: term '.' MAXLEN  */
#line 833 "filter/config.Y"
                   { (yyval.x) = f_new_inst(FI_ROA_MAXLEN, (yyvsp[-2].x)); }
#line 8293 "obj/conf/cf-parse.tab.c"
    break;

  case 326: /* term: term '.' ASN  */
#line 834 "filter/config.Y"
                { (yyval.x) = f_new_inst(FI_ASN, (yyvsp[-2].x)); }
#line 8299 "obj/conf/cf-parse.tab.c"
    break;

  case 327: /* term: term '.' SRC  */
#line 835 "filter/config.Y"
                { (yyval.x) = f_new_inst(FI_NET_SRC, (yyvsp[-2].x)); }
#line 8305 "obj/conf/cf-parse.tab.c"
    break;

  case 328: /* term: term '.' DST  */
#line 836 "filter/config.Y"
                { (yyval.x) = f_new_inst(FI_NET_DST, (yyvsp[-2].x)); }
#line 8311 "obj/conf/cf-parse.tab.c"
    break;

  case 329: /* term: term '.' MASK '(' term ')'  */
#line 837 "filter/config.Y"
                              { (yyval.x) = f_new_inst(FI_IP_MASK, (yyvsp[-5].x), (yyvsp[-1].x)); }
#line 8317 "obj/conf/cf-parse.tab.c"
    break;

  case 330: /* term: term '.' FIRST  */
#line 838 "filter/config.Y"
                  { (yyval.x) = f_new_inst(FI_AS_PATH_FIRST, (yyvsp[-2].x)); }
#line 8323 "obj/conf/cf-parse.tab.c"
    break;

  case 331: /* term: term '.' LAST  */
#line 839 "filter/config.Y"
                  { (yyval.x) = f_new_inst(FI_AS_PATH_LAST, (yyvsp[-2].x)); }
#line 8329 "obj/conf/cf-parse.tab.c"
    break;

  case 332: /* term: term '.' LAST_NONAGGREGATED  */
#line 840 "filter/config.Y"
                                { (yyval.x) = f_new_inst(FI_AS_PATH_LAST_NAG, (yyvsp[-2].x)); }
#line 8335 "obj/conf/cf-parse.tab.c"
    break;

  case 333: /* term: term '.' DATA  */
#line 841 "filter/config.Y"
                 { (yyval.x) = f_new_inst(FI_PAIR_DATA, (yyvsp[-2].x)); }
#line 8341 "obj/conf/cf-parse.tab.c"
    break;

  case 334: /* term: term '.' DATA1  */
#line 842 "filter/config.Y"
                  { (yyval.x) = f_new_inst(FI_LC_DATA1, (yyvsp[-2].x)); }
#line 8347 "obj/conf/cf-parse.tab.c"
    break;

  case 335: /* term: term '.' DATA2  */
#line 843 "filter/config.Y"
                  { (yyval.x) = f_new_inst(FI_LC_DATA2, (yyvsp[-2].x)); }
#line 8353 "obj/conf/cf-parse.tab.c"
    break;

  case 336: /* term: term '.' MIN  */
#line 844 "filter/config.Y"
                 { (yyval.x) = f_new_inst(FI_MIN, (yyvsp[-2].x)); }
#line 8359 "obj/conf/cf-parse.tab.c"
    break;

  case 337: /* term: term '.' MAX  */
#line 845 "filter/config.Y"
                 { (yyval.x) = f_new_inst(FI_MAX, (yyvsp[-2].x)); }
#line 8365 "obj/conf/cf-parse.tab.c"
    break;

  case 338: /* term: '+' EMPTY '+'  */
#line 855 "filter/config.Y"
                 { (yyval.x) = f_new_inst(FI_CONSTANT, f_const_empty_path); }
#line 8371 "obj/conf/cf-parse.tab.c"
    break;

  case 339: /* term: '-' EMPTY '-'  */
#line 856 "filter/config.Y"
                 { (yyval.x) = f_new_inst(FI_CONSTANT, f_const_empty_clist); }
#line 8377 "obj/conf/cf-parse.tab.c"
    break;

  case 340: /* term: '-' '-' EMPTY '-' '-'  */
#line 857 "filter/config.Y"
                         { (yyval.x) = f_new_inst(FI_CONSTANT, f_const_empty_eclist); }
#line 8383 "obj/conf/cf-parse.tab.c"
    break;

  case 341: /* term: '-' '-' '-' EMPTY '-' '-' '-'  */
#line 858 "filter/config.Y"
                                 { (yyval.x) = f_new_inst(FI_CONSTANT, f_const_empty_lclist); }
#line 8389 "obj/conf/cf-parse.tab.c"
    break;

  case 342: /* term: PREPEND '(' term ',' term ')'  */
#line 859 "filter/config.Y"
                                 { (yyval.x) = f_new_inst(FI_PATH_PREPEND, (yyvsp[-3].x), (yyvsp[-1].x)); }
#line 8395 "obj/conf/cf-parse.tab.c"
    break;

  case 343: /* term: ADD '(' term ',' term ')'  */
#line 860 "filter/config.Y"
                             { (yyval.x) = f_new_inst(FI_CLIST_ADD, (yyvsp[-3].x), (yyvsp[-1].x)); }
#line 8401 "obj/conf/cf-parse.tab.c"
    break;

  case 344: /* term: DELETE '(' term ',' term ')'  */
#line 861 "filter/config.Y"
                                { (yyval.x) = f_new_inst(FI_CLIST_DEL, (yyvsp[-3].x), (yyvsp[-1].x)); }
#line 8407 "obj/conf/cf-parse.tab.c"
    break;

  case 345: /* term: FILTER '(' term ',' term ')'  */
#line 862 "filter/config.Y"
                                { (yyval.x) = f_new_inst(FI_CLIST_FILTER, (yyvsp[-3].x), (yyvsp[-1].x)); }
#line 8413 "obj/conf/cf-parse.tab.c"
    break;

  case 346: /* term: ROA_CHECK '(' rtable ')'  */
#line 864 "filter/config.Y"
                            { (yyval.x) = f_new_inst(FI_ROA_CHECK_IMPLICIT, (yyvsp[-1].r)); }
#line 8419 "obj/conf/cf-parse.tab.c"
    break;

  case 347: /* term: ROA_CHECK '(' rtable ',' term ',' term ')'  */
#line 865 "filter/config.Y"
                                              { (yyval.x) = f_new_inst(FI_ROA_CHECK_EXPLICIT, (yyvsp[-3].x), (yyvsp[-1].x), (yyvsp[-5].r)); }
#line 8425 "obj/conf/cf-parse.tab.c"
    break;

  case 348: /* term: FORMAT '(' term ')'  */
#line 867 "filter/config.Y"
                       {  (yyval.x) = f_new_inst(FI_FORMAT, (yyvsp[-1].x)); }
#line 8431 "obj/conf/cf-parse.tab.c"
    break;

  case 350: /* break_command: ACCEPT  */
#line 875 "filter/config.Y"
          { (yyval.fret) = F_ACCEPT; }
#line 8437 "obj/conf/cf-parse.tab.c"
    break;

  case 351: /* break_command: REJECT  */
#line 876 "filter/config.Y"
          { (yyval.fret) = F_REJECT; }
#line 8443 "obj/conf/cf-parse.tab.c"
    break;

  case 352: /* break_command: ERROR  */
#line 877 "filter/config.Y"
         { (yyval.fret) = F_ERROR; }
#line 8449 "obj/conf/cf-parse.tab.c"
    break;

  case 353: /* print_list: %empty  */
#line 880 "filter/config.Y"
                        { (yyval.x) = NULL; }
#line 8455 "obj/conf/cf-parse.tab.c"
    break;

  case 354: /* print_list: term  */
#line 881 "filter/config.Y"
        { (yyval.x) = (yyvsp[0].x); }
#line 8461 "obj/conf/cf-parse.tab.c"
    break;

  case 355: /* print_list: term ',' print_list  */
#line 882 "filter/config.Y"
                       {
     ASSERT((yyvsp[-2].x));
     ASSERT((yyvsp[-2].x)->next == NULL);
     (yyvsp[-2].x)->next = (yyvsp[0].x);
     (yyval.x) = (yyvsp[-2].x);
   }
#line 8472 "obj/conf/cf-parse.tab.c"
    break;

  case 356: /* var_init: %empty  */
#line 891 "filter/config.Y"
               { (yyval.x) = f_new_inst(FI_CONSTANT, (struct f_val) { }); }
#line 8478 "obj/conf/cf-parse.tab.c"
    break;

  case 357: /* var_init: '=' term  */
#line 892 "filter/config.Y"
            { (yyval.x) = (yyvsp[0].x); }
#line 8484 "obj/conf/cf-parse.tab.c"
    break;

  case 358: /* var: type symbol var_init ';'  */
#line 896 "filter/config.Y"
                            {
     struct symbol *sym = cf_define_symbol((yyvsp[-2].s), SYM_VARIABLE | (yyvsp[-3].i), offset, f_new_var(sym_->scope));
     (yyval.x) = f_new_inst(FI_VAR_INIT, (yyvsp[-1].x), sym);
   }
#line 8493 "obj/conf/cf-parse.tab.c"
    break;

  case 359: /* for_var: type symbol  */
#line 902 "filter/config.Y"
               { (yyval.s) = cf_define_symbol((yyvsp[0].s), SYM_VARIABLE | (yyvsp[-1].i), offset, f_new_var(sym_->scope)); }
#line 8499 "obj/conf/cf-parse.tab.c"
    break;

  case 360: /* for_var: CF_SYM_KNOWN  */
#line 903 "filter/config.Y"
                { (yyval.s) = (yyvsp[0].s); cf_assert_symbol((yyvsp[0].s), SYM_VARIABLE); }
#line 8505 "obj/conf/cf-parse.tab.c"
    break;

  case 361: /* cmd: '{' cmds_scoped '}'  */
#line 907 "filter/config.Y"
                       {
     (yyval.x) = (yyvsp[-1].x);
   }
#line 8513 "obj/conf/cf-parse.tab.c"
    break;

  case 362: /* cmd: IF term THEN cmd  */
#line 910 "filter/config.Y"
                    {
     (yyval.x) = f_new_inst(FI_CONDITION, (yyvsp[-2].x), (yyvsp[0].x), NULL);
   }
#line 8521 "obj/conf/cf-parse.tab.c"
    break;

  case 363: /* cmd: IF term THEN cmd ELSE cmd  */
#line 913 "filter/config.Y"
                             {
     (yyval.x) = f_new_inst(FI_CONDITION, (yyvsp[-4].x), (yyvsp[-2].x), (yyvsp[0].x));
   }
#line 8529 "obj/conf/cf-parse.tab.c"
    break;

  case 364: /* $@6: %empty  */
#line 916 "filter/config.Y"
       {
     /* Reserve space for walk data on stack */
     cf_push_block_scope();
     conf_this_scope->slots += 2;
   }
#line 8539 "obj/conf/cf-parse.tab.c"
    break;

  case 365: /* $@7: %empty  */
#line 922 "filter/config.Y"
   { conf_this_scope->active = 0; }
#line 8545 "obj/conf/cf-parse.tab.c"
    break;

  case 366: /* $@8: %empty  */
#line 922 "filter/config.Y"
                                         { conf_this_scope->active = 1; }
#line 8551 "obj/conf/cf-parse.tab.c"
    break;

  case 367: /* cmd: FOR $@6 for_var IN $@7 term $@8 DO cmd  */
#line 923 "filter/config.Y"
          {
     cf_pop_block_scope();
     (yyval.x) = f_new_inst(FI_FOR_INIT, (yyvsp[-3].x), (yyvsp[-6].s));
     (yyval.x)->next = f_new_inst(FI_FOR_NEXT, (yyvsp[-6].s), (yyvsp[0].x));
   }
#line 8561 "obj/conf/cf-parse.tab.c"
    break;

  case 368: /* cmd: CF_SYM_KNOWN '=' term ';'  */
#line 928 "filter/config.Y"
                             {
     switch ((yyvsp[-3].s)->class) {
       case SYM_VARIABLE_RANGE:
	 (yyval.x) = f_new_inst(FI_VAR_SET, (yyvsp[-1].x), (yyvsp[-3].s));
	 break;
       case SYM_ATTRIBUTE:
	 (yyval.x) = f_new_inst(FI_EA_SET, (yyvsp[-1].x), *(yyvsp[-3].s)->attribute);
	 break;
       default:
	 cf_error("Can't assign to symbol %s", (yyvsp[-3].s)->name);
     }
   }
#line 8578 "obj/conf/cf-parse.tab.c"
    break;

  case 369: /* cmd: RETURN term ';'  */
#line 940 "filter/config.Y"
                   {
     DBG( "Ook, we'll return the value\n" );
     (yyval.x) = f_new_inst(FI_RETURN, (yyvsp[-1].x));
   }
#line 8587 "obj/conf/cf-parse.tab.c"
    break;

  case 370: /* cmd: dynamic_attr '=' term ';'  */
#line 944 "filter/config.Y"
                             {
     (yyval.x) = f_new_inst(FI_EA_SET, (yyvsp[-1].x), (yyvsp[-3].fda));
   }
#line 8595 "obj/conf/cf-parse.tab.c"
    break;

  case 371: /* cmd: static_attr '=' term ';'  */
#line 947 "filter/config.Y"
                            {
     if ((yyvsp[-3].fsa).readonly)
       cf_error( "This static attribute is read-only.");
     (yyval.x) = f_new_inst(FI_RTA_SET, (yyvsp[-1].x), (yyvsp[-3].fsa));
   }
#line 8605 "obj/conf/cf-parse.tab.c"
    break;

  case 372: /* cmd: UNSET '(' dynamic_attr ')' ';'  */
#line 952 "filter/config.Y"
                                  {
     (yyval.x) = f_new_inst(FI_EA_UNSET, (yyvsp[-2].fda));
   }
#line 8613 "obj/conf/cf-parse.tab.c"
    break;

  case 373: /* cmd: break_command print_list ';'  */
#line 955 "filter/config.Y"
                                {
    struct f_inst *breaker = f_new_inst(FI_DIE, (yyvsp[-2].fret));
    if ((yyvsp[-1].x)) {
      struct f_inst *printer = f_new_inst(FI_PRINT, (yyvsp[-1].x));
      struct f_inst *flusher = f_new_inst(FI_FLUSH);
      printer->next = flusher;
      flusher->next = breaker;
      (yyval.x) = printer;
    } else
      (yyval.x) = breaker;
   }
#line 8629 "obj/conf/cf-parse.tab.c"
    break;

  case 374: /* cmd: PRINT print_list ';'  */
#line 966 "filter/config.Y"
                        {
    (yyval.x) = f_new_inst(FI_PRINT, (yyvsp[-1].x));
    (yyval.x)->next = f_new_inst(FI_FLUSH);
   }
#line 8638 "obj/conf/cf-parse.tab.c"
    break;

  case 375: /* cmd: PRINTN print_list ';'  */
#line 970 "filter/config.Y"
                         {
    (yyval.x) = f_new_inst(FI_PRINT, (yyvsp[-1].x));
   }
#line 8646 "obj/conf/cf-parse.tab.c"
    break;

  case 376: /* cmd: function_call ';'  */
#line 973 "filter/config.Y"
                     { (yyval.x) = f_new_inst(FI_DROP_RESULT, (yyvsp[-1].x)); }
#line 8652 "obj/conf/cf-parse.tab.c"
    break;

  case 377: /* cmd: CASE term '{' switch_body '}'  */
#line 974 "filter/config.Y"
                                 {
      (yyval.x) = f_new_inst(FI_SWITCH, (yyvsp[-3].x), build_tree((yyvsp[-1].e)));
   }
#line 8660 "obj/conf/cf-parse.tab.c"
    break;

  case 378: /* cmd: dynamic_attr '.' EMPTY ';'  */
#line 978 "filter/config.Y"
                              { (yyval.x) = f_generate_empty((yyvsp[-3].fda)); }
#line 8666 "obj/conf/cf-parse.tab.c"
    break;

  case 379: /* cmd: dynamic_attr '.' PREPEND '(' term ')' ';'  */
#line 979 "filter/config.Y"
                                               { (yyval.x) = f_generate_complex( FI_PATH_PREPEND, (yyvsp[-6].fda), (yyvsp[-2].x) ); }
#line 8672 "obj/conf/cf-parse.tab.c"
    break;

  case 380: /* cmd: dynamic_attr '.' ADD '(' term ')' ';'  */
#line 980 "filter/config.Y"
                                               { (yyval.x) = f_generate_complex( FI_CLIST_ADD, (yyvsp[-6].fda), (yyvsp[-2].x) ); }
#line 8678 "obj/conf/cf-parse.tab.c"
    break;

  case 381: /* cmd: dynamic_attr '.' DELETE '(' term ')' ';'  */
#line 981 "filter/config.Y"
                                               { (yyval.x) = f_generate_complex( FI_CLIST_DEL, (yyvsp[-6].fda), (yyvsp[-2].x) ); }
#line 8684 "obj/conf/cf-parse.tab.c"
    break;

  case 382: /* cmd: dynamic_attr '.' FILTER '(' term ')' ';'  */
#line 982 "filter/config.Y"
                                               { (yyval.x) = f_generate_complex( FI_CLIST_FILTER, (yyvsp[-6].fda), (yyvsp[-2].x) ); }
#line 8690 "obj/conf/cf-parse.tab.c"
    break;

  case 383: /* cmd: BT_ASSERT '(' get_cf_position term get_cf_position ')' ';'  */
#line 983 "filter/config.Y"
                                                              { (yyval.x) = assert_done((yyvsp[-3].x), (yyvsp[-4].t) + 1, (yyvsp[-2].t) - 1); }
#line 8696 "obj/conf/cf-parse.tab.c"
    break;

  case 384: /* cmd: BT_CHECK_ASSIGN '(' get_cf_position lvalue get_cf_position ',' term ')' ';'  */
#line 984 "filter/config.Y"
                                                                               { (yyval.x) = assert_assign(&(yyvsp[-5].flv), (yyvsp[-2].x), (yyvsp[-6].t) + 1, (yyvsp[-4].t) - 1); }
#line 8702 "obj/conf/cf-parse.tab.c"
    break;

  case 385: /* get_cf_position: %empty  */
#line 988 "filter/config.Y"
{
  (yyval.t) = cf_text;
}
#line 8710 "obj/conf/cf-parse.tab.c"
    break;

  case 386: /* lvalue: CF_SYM_KNOWN  */
#line 993 "filter/config.Y"
                { cf_assert_symbol((yyvsp[0].s), SYM_VARIABLE); (yyval.flv) = (struct f_lval) { .type = F_LVAL_VARIABLE, .sym = (yyvsp[0].s) }; }
#line 8716 "obj/conf/cf-parse.tab.c"
    break;

  case 387: /* lvalue: static_attr  */
#line 994 "filter/config.Y"
               { (yyval.flv) = (struct f_lval) { .type = F_LVAL_SA, .sa = (yyvsp[0].fsa) }; }
#line 8722 "obj/conf/cf-parse.tab.c"
    break;

  case 388: /* lvalue: dynamic_attr  */
#line 995 "filter/config.Y"
                { (yyval.flv) = (struct f_lval) { .type = F_LVAL_EA, .da = (yyvsp[0].fda) }; }
#line 8728 "obj/conf/cf-parse.tab.c"
    break;

  case 390: /* rtrid: ROUTER ID idval ';'  */
#line 162 "nest/config.Y"
                       { new_config->router_id = (yyvsp[-1].i32); }
#line 8734 "obj/conf/cf-parse.tab.c"
    break;

  case 391: /* rtrid: ROUTER ID FROM iface_patt ';'  */
#line 163 "nest/config.Y"
                                 { new_config->router_id_from = this_ipatt; }
#line 8740 "obj/conf/cf-parse.tab.c"
    break;

  case 392: /* idval: NUM  */
#line 167 "nest/config.Y"
       { (yyval.i32) = (yyvsp[0].i); }
#line 8746 "obj/conf/cf-parse.tab.c"
    break;

  case 393: /* idval: '(' term ')'  */
#line 168 "nest/config.Y"
                { (yyval.i32) = f_eval_int(f_linearize((yyvsp[-1].x), 1)); }
#line 8752 "obj/conf/cf-parse.tab.c"
    break;

  case 394: /* idval: IP4  */
#line 169 "nest/config.Y"
       { (yyval.i32) = ip4_to_u32((yyvsp[0].ip4)); }
#line 8758 "obj/conf/cf-parse.tab.c"
    break;

  case 395: /* idval: CF_SYM_KNOWN  */
#line 170 "nest/config.Y"
                {
     if ((yyvsp[0].s)->class == (SYM_CONSTANT | T_INT) || (yyvsp[0].s)->class == (SYM_CONSTANT | T_QUAD))
       (yyval.i32) = SYM_VAL((yyvsp[0].s)).i;
     else if (((yyvsp[0].s)->class == (SYM_CONSTANT | T_IP)) && ipa_is_ip4(SYM_VAL((yyvsp[0].s)).ip))
       (yyval.i32) = ipa_to_u32(SYM_VAL((yyvsp[0].s)).ip);
     else
       cf_error("Number or IPv4 address constant expected");
   }
#line 8771 "obj/conf/cf-parse.tab.c"
    break;

  case 397: /* hostname_override: HOSTNAME text ';'  */
#line 182 "nest/config.Y"
                                     { new_config->hostname = (yyvsp[-1].t); }
#line 8777 "obj/conf/cf-parse.tab.c"
    break;

  case 399: /* gr_opts: GRACEFUL RESTART WAIT expr ';'  */
#line 186 "nest/config.Y"
                                        { new_config->gr_wait = (yyvsp[-1].i); }
#line 8783 "obj/conf/cf-parse.tab.c"
    break;

  case 400: /* net_type: IPV4  */
#line 192 "nest/config.Y"
        { (yyval.i) = NET_IP4; }
#line 8789 "obj/conf/cf-parse.tab.c"
    break;

  case 401: /* net_type: IPV6  */
#line 193 "nest/config.Y"
        { (yyval.i) = NET_IP6; }
#line 8795 "obj/conf/cf-parse.tab.c"
    break;

  case 402: /* net_type: IPV6 SADR  */
#line 194 "nest/config.Y"
             { (yyval.i) = NET_IP6_SADR; }
#line 8801 "obj/conf/cf-parse.tab.c"
    break;

  case 403: /* net_type: VPN4  */
#line 195 "nest/config.Y"
        { (yyval.i) = NET_VPN4; }
#line 8807 "obj/conf/cf-parse.tab.c"
    break;

  case 404: /* net_type: VPN6  */
#line 196 "nest/config.Y"
        { (yyval.i) = NET_VPN6; }
#line 8813 "obj/conf/cf-parse.tab.c"
    break;

  case 405: /* net_type: ROA4  */
#line 197 "nest/config.Y"
        { (yyval.i) = NET_ROA4; }
#line 8819 "obj/conf/cf-parse.tab.c"
    break;

  case 406: /* net_type: ROA6  */
#line 198 "nest/config.Y"
        { (yyval.i) = NET_ROA6; }
#line 8825 "obj/conf/cf-parse.tab.c"
    break;

  case 407: /* net_type: FLOW4  */
#line 199 "nest/config.Y"
        { (yyval.i) = NET_FLOW4; }
#line 8831 "obj/conf/cf-parse.tab.c"
    break;

  case 408: /* net_type: FLOW6  */
#line 200 "nest/config.Y"
        { (yyval.i) = NET_FLOW6; }
#line 8837 "obj/conf/cf-parse.tab.c"
    break;

  case 409: /* net_type: MPLS  */
#line 201 "nest/config.Y"
        { (yyval.i) = NET_MPLS; }
#line 8843 "obj/conf/cf-parse.tab.c"
    break;

  case 412: /* table_start: net_type TABLE symbol  */
#line 213 "nest/config.Y"
                                   {
   this_table = rt_new_table((yyvsp[0].s), (yyvsp[-2].i));
   }
#line 8851 "obj/conf/cf-parse.tab.c"
    break;

  case 414: /* table_sorted: SORTED  */
#line 220 "nest/config.Y"
          { this_table->sorted = 1; }
#line 8857 "obj/conf/cf-parse.tab.c"
    break;

  case 415: /* table_opt: SORTED bool  */
#line 224 "nest/config.Y"
               { this_table->sorted = (yyvsp[0].i); }
#line 8863 "obj/conf/cf-parse.tab.c"
    break;

  case 416: /* table_opt: TRIE bool  */
#line 225 "nest/config.Y"
             {
     if (!net_val_match(this_table->addr_type, NB_IP | NB_VPN | NB_ROA | NB_IP6_SADR))
       cf_error("Trie option not supported for %s table", net_label[this_table->addr_type]);
     this_table->trie_used = (yyvsp[0].i);
   }
#line 8873 "obj/conf/cf-parse.tab.c"
    break;

  case 417: /* table_opt: MIN SETTLE TIME expr_us  */
#line 230 "nest/config.Y"
                           { this_table->min_settle_time = (yyvsp[0].time); }
#line 8879 "obj/conf/cf-parse.tab.c"
    break;

  case 418: /* table_opt: MAX SETTLE TIME expr_us  */
#line 231 "nest/config.Y"
                           { this_table->max_settle_time = (yyvsp[0].time); }
#line 8885 "obj/conf/cf-parse.tab.c"
    break;

  case 419: /* table_opt: GC THRESHOLD expr  */
#line 232 "nest/config.Y"
                     { this_table->gc_threshold = (yyvsp[0].i); }
#line 8891 "obj/conf/cf-parse.tab.c"
    break;

  case 420: /* table_opt: GC PERIOD expr_us  */
#line 233 "nest/config.Y"
                     { this_table->gc_period = (uint) (yyvsp[0].time); if ((yyvsp[0].time) > 3600 S_) cf_error("GC period must be at most 3600 s"); }
#line 8897 "obj/conf/cf-parse.tab.c"
    break;

  case 425: /* conf: proto  */
#line 249 "nest/config.Y"
            { proto_postconfig(); }
#line 8903 "obj/conf/cf-parse.tab.c"
    break;

  case 426: /* proto_start: PROTOCOL  */
#line 252 "nest/config.Y"
            { (yyval.i) = SYM_PROTO; }
#line 8909 "obj/conf/cf-parse.tab.c"
    break;

  case 427: /* proto_start: TEMPLATE  */
#line 253 "nest/config.Y"
            { (yyval.i) = SYM_TEMPLATE; }
#line 8915 "obj/conf/cf-parse.tab.c"
    break;

  case 428: /* proto_name: %empty  */
#line 257 "nest/config.Y"
               {
     struct symbol *s = cf_default_name(this_proto->protocol->template, &this_proto->protocol->name_counter);
     s->class = this_proto->class;
     s->proto = this_proto;
     this_proto->name = s->name;
     }
#line 8926 "obj/conf/cf-parse.tab.c"
    break;

  case 429: /* proto_name: symbol  */
#line 263 "nest/config.Y"
          {
     cf_define_symbol((yyvsp[0].s), this_proto->class, proto, this_proto);
     this_proto->name = (yyvsp[0].s)->name;
   }
#line 8935 "obj/conf/cf-parse.tab.c"
    break;

  case 430: /* proto_name: FROM CF_SYM_KNOWN  */
#line 267 "nest/config.Y"
                     {
     if (((yyvsp[0].s)->class != SYM_TEMPLATE) && ((yyvsp[0].s)->class != SYM_PROTO)) cf_error("Template or protocol name expected");

     struct symbol *s = cf_default_name(this_proto->protocol->template, &this_proto->protocol->name_counter);
     s->class = this_proto->class;
     s->proto = this_proto;
     this_proto->name = s->name;

     proto_copy_config(this_proto, (yyvsp[0].s)->proto);
   }
#line 8950 "obj/conf/cf-parse.tab.c"
    break;

  case 431: /* proto_name: symbol FROM CF_SYM_KNOWN  */
#line 277 "nest/config.Y"
                            {
     if (((yyvsp[0].s)->class != SYM_TEMPLATE) && ((yyvsp[0].s)->class != SYM_PROTO)) cf_error("Template or protocol name expected");

     cf_define_symbol((yyvsp[-2].s), this_proto->class, proto, this_proto);
     this_proto->name = (yyvsp[-2].s)->name;

     proto_copy_config(this_proto, (yyvsp[0].s)->proto);
   }
#line 8963 "obj/conf/cf-parse.tab.c"
    break;

  case 433: /* proto_item: DISABLED bool  */
#line 289 "nest/config.Y"
                 { this_proto->disabled = (yyvsp[0].i); }
#line 8969 "obj/conf/cf-parse.tab.c"
    break;

  case 434: /* proto_item: DEBUG debug_mask  */
#line 290 "nest/config.Y"
                    { this_proto->debug = (yyvsp[0].i); }
#line 8975 "obj/conf/cf-parse.tab.c"
    break;

  case 435: /* proto_item: MRTDUMP mrtdump_mask  */
#line 291 "nest/config.Y"
                        { this_proto->mrtdump = (yyvsp[0].i); }
#line 8981 "obj/conf/cf-parse.tab.c"
    break;

  case 436: /* proto_item: ROUTER ID idval  */
#line 292 "nest/config.Y"
                   { this_proto->router_id = (yyvsp[0].i32); }
#line 8987 "obj/conf/cf-parse.tab.c"
    break;

  case 437: /* proto_item: DESCRIPTION text  */
#line 293 "nest/config.Y"
                    { this_proto->dsc = (yyvsp[0].t); }
#line 8993 "obj/conf/cf-parse.tab.c"
    break;

  case 438: /* proto_item: VRF text  */
#line 294 "nest/config.Y"
            { this_proto->vrf = if_get_by_name((yyvsp[0].t)); this_proto->vrf_set = 1; }
#line 8999 "obj/conf/cf-parse.tab.c"
    break;

  case 439: /* proto_item: VRF DEFAULT  */
#line 295 "nest/config.Y"
               { this_proto->vrf = NULL; this_proto->vrf_set = 1; }
#line 9005 "obj/conf/cf-parse.tab.c"
    break;

  case 440: /* channel_start: net_type  */
#line 300 "nest/config.Y"
{
  (yyval.cc) = this_channel = channel_config_get(NULL, net_label[(yyvsp[0].i)], (yyvsp[0].i), this_proto);
}
#line 9013 "obj/conf/cf-parse.tab.c"
    break;

  case 441: /* channel_item_: TABLE rtable  */
#line 305 "nest/config.Y"
                {
     if (this_channel->net_type && ((yyvsp[0].r)->addr_type != this_channel->net_type))
       cf_error("Incompatible table type");
     this_channel->table = (yyvsp[0].r);
   }
#line 9023 "obj/conf/cf-parse.tab.c"
    break;

  case 442: /* channel_item_: IMPORT imexport  */
#line 310 "nest/config.Y"
                   { this_channel->in_filter = (yyvsp[0].f); }
#line 9029 "obj/conf/cf-parse.tab.c"
    break;

  case 443: /* channel_item_: EXPORT imexport  */
#line 311 "nest/config.Y"
                   { this_channel->out_filter = (yyvsp[0].f); }
#line 9035 "obj/conf/cf-parse.tab.c"
    break;

  case 444: /* channel_item_: RECEIVE LIMIT limit_spec  */
#line 312 "nest/config.Y"
                            { this_channel->rx_limit = (yyvsp[0].cl); }
#line 9041 "obj/conf/cf-parse.tab.c"
    break;

  case 445: /* channel_item_: IMPORT LIMIT limit_spec  */
#line 313 "nest/config.Y"
                           { this_channel->in_limit = (yyvsp[0].cl); }
#line 9047 "obj/conf/cf-parse.tab.c"
    break;

  case 446: /* channel_item_: EXPORT LIMIT limit_spec  */
#line 314 "nest/config.Y"
                           { this_channel->out_limit = (yyvsp[0].cl); }
#line 9053 "obj/conf/cf-parse.tab.c"
    break;

  case 447: /* channel_item_: PREFERENCE expr  */
#line 315 "nest/config.Y"
                   { this_channel->preference = (yyvsp[0].i); check_u16((yyvsp[0].i)); }
#line 9059 "obj/conf/cf-parse.tab.c"
    break;

  case 448: /* channel_item_: IMPORT KEEP FILTERED bool  */
#line 316 "nest/config.Y"
                             { this_channel->in_keep_filtered = (yyvsp[0].i); }
#line 9065 "obj/conf/cf-parse.tab.c"
    break;

  case 449: /* channel_item_: RPKI RELOAD bool  */
#line 317 "nest/config.Y"
                    { this_channel->rpki_reload = (yyvsp[0].i); }
#line 9071 "obj/conf/cf-parse.tab.c"
    break;

  case 451: /* channel_item: DEBUG debug_mask  */
#line 323 "nest/config.Y"
                    { this_channel->debug = (yyvsp[0].i); }
#line 9077 "obj/conf/cf-parse.tab.c"
    break;

  case 456: /* channel_end: %empty  */
#line 337 "nest/config.Y"
{
  if (!this_channel->table)
    cf_error("Routing table not specified");

  this_channel = NULL;
}
#line 9088 "obj/conf/cf-parse.tab.c"
    break;

  case 458: /* rtable: CF_SYM_KNOWN  */
#line 347 "nest/config.Y"
                     { cf_assert_symbol((yyvsp[0].s), SYM_TABLE); (yyval.r) = (yyvsp[0].s)->table; }
#line 9094 "obj/conf/cf-parse.tab.c"
    break;

  case 459: /* imexport: FILTER filter  */
#line 350 "nest/config.Y"
                 { (yyval.f) = (yyvsp[0].f); }
#line 9100 "obj/conf/cf-parse.tab.c"
    break;

  case 461: /* imexport: ALL  */
#line 352 "nest/config.Y"
       { (yyval.f) = FILTER_ACCEPT; }
#line 9106 "obj/conf/cf-parse.tab.c"
    break;

  case 462: /* imexport: NONE  */
#line 353 "nest/config.Y"
        { (yyval.f) = FILTER_REJECT; }
#line 9112 "obj/conf/cf-parse.tab.c"
    break;

  case 463: /* limit_action: %empty  */
#line 357 "nest/config.Y"
                 { (yyval.i) = PLA_DISABLE; }
#line 9118 "obj/conf/cf-parse.tab.c"
    break;

  case 464: /* limit_action: ACTION WARN  */
#line 358 "nest/config.Y"
               { (yyval.i) = PLA_WARN; }
#line 9124 "obj/conf/cf-parse.tab.c"
    break;

  case 465: /* limit_action: ACTION BLOCK  */
#line 359 "nest/config.Y"
                { (yyval.i) = PLA_BLOCK; }
#line 9130 "obj/conf/cf-parse.tab.c"
    break;

  case 466: /* limit_action: ACTION RESTART  */
#line 360 "nest/config.Y"
                  { (yyval.i) = PLA_RESTART; }
#line 9136 "obj/conf/cf-parse.tab.c"
    break;

  case 467: /* limit_action: ACTION DISABLE  */
#line 361 "nest/config.Y"
                  { (yyval.i) = PLA_DISABLE; }
#line 9142 "obj/conf/cf-parse.tab.c"
    break;

  case 468: /* limit_spec: expr limit_action  */
#line 365 "nest/config.Y"
                     { (yyval.cl) = (struct channel_limit){ .limit = (yyvsp[-1].i), (yyval.cl).action = (yyvsp[0].i) }; }
#line 9148 "obj/conf/cf-parse.tab.c"
    break;

  case 469: /* limit_spec: OFF  */
#line 366 "nest/config.Y"
       { (yyval.cl) = (struct channel_limit){}; }
#line 9154 "obj/conf/cf-parse.tab.c"
    break;

  case 471: /* debug_default: DEBUG PROTOCOLS debug_mask  */
#line 373 "nest/config.Y"
                              { new_config->proto_default_debug = (yyvsp[0].i); }
#line 9160 "obj/conf/cf-parse.tab.c"
    break;

  case 472: /* debug_default: DEBUG CHANNELS debug_mask  */
#line 374 "nest/config.Y"
                             { new_config->channel_default_debug = (yyvsp[0].i); }
#line 9166 "obj/conf/cf-parse.tab.c"
    break;

  case 473: /* debug_default: DEBUG COMMANDS expr  */
#line 375 "nest/config.Y"
                       { new_config->cli_debug = (yyvsp[0].i); }
#line 9172 "obj/conf/cf-parse.tab.c"
    break;

  case 475: /* timeformat_which: ROUTE  */
#line 383 "nest/config.Y"
         { (yyval.tf) = &new_config->tf_route; }
#line 9178 "obj/conf/cf-parse.tab.c"
    break;

  case 476: /* timeformat_which: PROTOCOL  */
#line 384 "nest/config.Y"
            { (yyval.tf) = &new_config->tf_proto; }
#line 9184 "obj/conf/cf-parse.tab.c"
    break;

  case 477: /* timeformat_which: BASE  */
#line 385 "nest/config.Y"
        { (yyval.tf) = &new_config->tf_base; }
#line 9190 "obj/conf/cf-parse.tab.c"
    break;

  case 478: /* timeformat_which: LOG  */
#line 386 "nest/config.Y"
       { (yyval.tf) = &new_config->tf_log; }
#line 9196 "obj/conf/cf-parse.tab.c"
    break;

  case 479: /* timeformat_spec: timeformat_which TEXT  */
#line 390 "nest/config.Y"
                         { *(yyvsp[-1].tf) = (struct timeformat){(yyvsp[0].t), NULL, 0}; }
#line 9202 "obj/conf/cf-parse.tab.c"
    break;

  case 480: /* timeformat_spec: timeformat_which TEXT expr TEXT  */
#line 391 "nest/config.Y"
                                   { *(yyvsp[-3].tf) = (struct timeformat){(yyvsp[-2].t), (yyvsp[0].t), (s64) (yyvsp[-1].i) S_}; }
#line 9208 "obj/conf/cf-parse.tab.c"
    break;

  case 481: /* timeformat_spec: timeformat_which ISO SHORT  */
#line 392 "nest/config.Y"
                                 { *(yyvsp[-2].tf) = TM_ISO_SHORT_S; }
#line 9214 "obj/conf/cf-parse.tab.c"
    break;

  case 482: /* timeformat_spec: timeformat_which ISO SHORT MS  */
#line 393 "nest/config.Y"
                                 { *(yyvsp[-3].tf) = TM_ISO_SHORT_MS; }
#line 9220 "obj/conf/cf-parse.tab.c"
    break;

  case 483: /* timeformat_spec: timeformat_which ISO SHORT US  */
#line 394 "nest/config.Y"
                                 { *(yyvsp[-3].tf) = TM_ISO_SHORT_US; }
#line 9226 "obj/conf/cf-parse.tab.c"
    break;

  case 484: /* timeformat_spec: timeformat_which ISO LONG  */
#line 395 "nest/config.Y"
                                { *(yyvsp[-2].tf) = TM_ISO_LONG_S; }
#line 9232 "obj/conf/cf-parse.tab.c"
    break;

  case 485: /* timeformat_spec: timeformat_which ISO LONG MS  */
#line 396 "nest/config.Y"
                                { *(yyvsp[-3].tf) = TM_ISO_LONG_MS; }
#line 9238 "obj/conf/cf-parse.tab.c"
    break;

  case 486: /* timeformat_spec: timeformat_which ISO LONG US  */
#line 397 "nest/config.Y"
                                { *(yyvsp[-3].tf) = TM_ISO_LONG_US; }
#line 9244 "obj/conf/cf-parse.tab.c"
    break;

  case 488: /* iface_patt_node_init: %empty  */
#line 408 "nest/config.Y"
               {
     struct iface_patt_node *ipn = cfg_allocz(sizeof(struct iface_patt_node));
     add_tail(&this_ipatt->ipn_list, NODE ipn);
     this_ipn = ipn;
   }
#line 9254 "obj/conf/cf-parse.tab.c"
    break;

  case 489: /* iface_patt_node_body: TEXT  */
#line 416 "nest/config.Y"
        { this_ipn->pattern = (yyvsp[0].t); /* this_ipn->prefix stays zero */ }
#line 9260 "obj/conf/cf-parse.tab.c"
    break;

  case 490: /* iface_patt_node_body: opttext net_or_ipa  */
#line 417 "nest/config.Y"
                      { this_ipn->pattern = (yyvsp[-1].t); this_ipn->prefix = (yyvsp[0].net); }
#line 9266 "obj/conf/cf-parse.tab.c"
    break;

  case 491: /* iface_negate: %empty  */
#line 421 "nest/config.Y"
       { this_ipn->positive = 1; }
#line 9272 "obj/conf/cf-parse.tab.c"
    break;

  case 492: /* iface_negate: '-'  */
#line 422 "nest/config.Y"
       { this_ipn->positive = 0; }
#line 9278 "obj/conf/cf-parse.tab.c"
    break;

  case 496: /* iface_patt_list_nopx: iface_patt_list  */
#line 436 "nest/config.Y"
                                      { iface_patt_check(); }
#line 9284 "obj/conf/cf-parse.tab.c"
    break;

  case 497: /* iface_patt_init: %empty  */
#line 438 "nest/config.Y"
                 {
   /* Generic this_ipatt init */
   this_ipatt = cfg_allocz(sizeof(struct iface_patt));
   init_list(&this_ipatt->ipn_list);
 }
#line 9294 "obj/conf/cf-parse.tab.c"
    break;

  case 499: /* tos: CLASS expr  */
#line 450 "nest/config.Y"
              { (yyval.i) = (yyvsp[0].i) & 0xfc;        if ((yyvsp[0].i) > 255) cf_error("TX class must be in range 0-255"); }
#line 9300 "obj/conf/cf-parse.tab.c"
    break;

  case 500: /* tos: DSCP expr  */
#line 451 "nest/config.Y"
              { (yyval.i) = ((yyvsp[0].i) & 0x3f) << 2; if ((yyvsp[0].i) > 63)  cf_error("TX DSCP must be in range 0-63"); }
#line 9306 "obj/conf/cf-parse.tab.c"
    break;

  case 502: /* dev_proto_start: proto_start DIRECT  */
#line 458 "nest/config.Y"
                                    {
     this_proto = proto_config_new(&proto_device, (yyvsp[-1].i));
     init_list(&DIRECT_CFG->iface_list);
   }
#line 9315 "obj/conf/cf-parse.tab.c"
    break;

  case 507: /* dev_proto: dev_proto CHECK LINK bool ';'  */
#line 469 "nest/config.Y"
                                 { DIRECT_CFG->check_link = (yyvsp[-1].i); }
#line 9321 "obj/conf/cf-parse.tab.c"
    break;

  case 508: /* dev_iface_init: %empty  */
#line 473 "nest/config.Y"
               {
     this_ipatt = cfg_allocz(sizeof(struct iface_patt));
     add_tail(&DIRECT_CFG->iface_list, NODE this_ipatt);
     init_list(&this_ipatt->ipn_list);
   }
#line 9331 "obj/conf/cf-parse.tab.c"
    break;

  case 510: /* debug_mask: ALL  */
#line 487 "nest/config.Y"
       { (yyval.i) = ~0; }
#line 9337 "obj/conf/cf-parse.tab.c"
    break;

  case 511: /* debug_mask: OFF  */
#line 488 "nest/config.Y"
       { (yyval.i) = 0; }
#line 9343 "obj/conf/cf-parse.tab.c"
    break;

  case 512: /* debug_mask: '{' debug_list '}'  */
#line 489 "nest/config.Y"
                      { (yyval.i) = (yyvsp[-1].i); }
#line 9349 "obj/conf/cf-parse.tab.c"
    break;

  case 514: /* debug_list: debug_list ',' debug_flag  */
#line 494 "nest/config.Y"
                             { (yyval.i) = (yyvsp[-2].i) | (yyvsp[0].i); }
#line 9355 "obj/conf/cf-parse.tab.c"
    break;

  case 515: /* debug_flag: STATES  */
#line 498 "nest/config.Y"
                { (yyval.i) = D_STATES; }
#line 9361 "obj/conf/cf-parse.tab.c"
    break;

  case 516: /* debug_flag: ROUTES  */
#line 499 "nest/config.Y"
                { (yyval.i) = D_ROUTES; }
#line 9367 "obj/conf/cf-parse.tab.c"
    break;

  case 517: /* debug_flag: FILTERS  */
#line 500 "nest/config.Y"
                { (yyval.i) = D_FILTERS; }
#line 9373 "obj/conf/cf-parse.tab.c"
    break;

  case 518: /* debug_flag: INTERFACES  */
#line 501 "nest/config.Y"
                { (yyval.i) = D_IFACES; }
#line 9379 "obj/conf/cf-parse.tab.c"
    break;

  case 519: /* debug_flag: EVENTS  */
#line 502 "nest/config.Y"
                { (yyval.i) = D_EVENTS; }
#line 9385 "obj/conf/cf-parse.tab.c"
    break;

  case 520: /* debug_flag: PACKETS  */
#line 503 "nest/config.Y"
                { (yyval.i) = D_PACKETS; }
#line 9391 "obj/conf/cf-parse.tab.c"
    break;

  case 521: /* mrtdump_mask: ALL  */
#line 509 "nest/config.Y"
       { (yyval.i) = ~0; }
#line 9397 "obj/conf/cf-parse.tab.c"
    break;

  case 522: /* mrtdump_mask: OFF  */
#line 510 "nest/config.Y"
       { (yyval.i) = 0; }
#line 9403 "obj/conf/cf-parse.tab.c"
    break;

  case 523: /* mrtdump_mask: '{' mrtdump_list '}'  */
#line 511 "nest/config.Y"
                        { (yyval.i) = (yyvsp[-1].i); }
#line 9409 "obj/conf/cf-parse.tab.c"
    break;

  case 525: /* mrtdump_list: mrtdump_list ',' mrtdump_flag  */
#line 516 "nest/config.Y"
                                 { (yyval.i) = (yyvsp[-2].i) | (yyvsp[0].i); }
#line 9415 "obj/conf/cf-parse.tab.c"
    break;

  case 526: /* mrtdump_flag: STATES  */
#line 520 "nest/config.Y"
                { (yyval.i) = MD_STATES; }
#line 9421 "obj/conf/cf-parse.tab.c"
    break;

  case 527: /* mrtdump_flag: MESSAGES  */
#line 521 "nest/config.Y"
                { (yyval.i) = MD_MESSAGES; }
#line 9427 "obj/conf/cf-parse.tab.c"
    break;

  case 537: /* password_item_begin: pass_key text  */
#line 548 "nest/config.Y"
                  { init_password_list(); init_password((yyvsp[0].t), strlen((yyvsp[0].t)), password_id++); }
#line 9433 "obj/conf/cf-parse.tab.c"
    break;

  case 538: /* password_item_begin: pass_key BYTESTRING  */
#line 549 "nest/config.Y"
                        { init_password_list(); init_password((yyvsp[0].bs)->data, (yyvsp[0].bs)->length, password_id++); }
#line 9439 "obj/conf/cf-parse.tab.c"
    break;

  case 539: /* password_item_params: %empty  */
#line 553 "nest/config.Y"
               { }
#line 9445 "obj/conf/cf-parse.tab.c"
    break;

  case 540: /* password_item_params: GENERATE FROM time ';' password_item_params  */
#line 554 "nest/config.Y"
                                               { this_p_item->genfrom = (yyvsp[-2].time); }
#line 9451 "obj/conf/cf-parse.tab.c"
    break;

  case 541: /* password_item_params: GENERATE TO time ';' password_item_params  */
#line 555 "nest/config.Y"
                                             { this_p_item->gento = (yyvsp[-2].time); }
#line 9457 "obj/conf/cf-parse.tab.c"
    break;

  case 542: /* password_item_params: ACCEPT FROM time ';' password_item_params  */
#line 556 "nest/config.Y"
                                             { this_p_item->accfrom = (yyvsp[-2].time); }
#line 9463 "obj/conf/cf-parse.tab.c"
    break;

  case 543: /* password_item_params: ACCEPT TO time ';' password_item_params  */
#line 557 "nest/config.Y"
                                           { this_p_item->accto = (yyvsp[-2].time); }
#line 9469 "obj/conf/cf-parse.tab.c"
    break;

  case 544: /* password_item_params: FROM time ';' password_item_params  */
#line 558 "nest/config.Y"
                                      { this_p_item->genfrom = this_p_item->accfrom = (yyvsp[-2].time); }
#line 9475 "obj/conf/cf-parse.tab.c"
    break;

  case 545: /* password_item_params: TO time ';' password_item_params  */
#line 559 "nest/config.Y"
                                    { this_p_item->gento = this_p_item->accto = (yyvsp[-2].time); }
#line 9481 "obj/conf/cf-parse.tab.c"
    break;

  case 546: /* password_item_params: ID expr ';' password_item_params  */
#line 560 "nest/config.Y"
                                    { this_p_item->id = (yyvsp[-2].i); if ((yyvsp[-2].i) > 255) cf_error("Password ID must be in range 0-255"); }
#line 9487 "obj/conf/cf-parse.tab.c"
    break;

  case 547: /* password_item_params: ALGORITHM password_algorithm ';' password_item_params  */
#line 561 "nest/config.Y"
                                                         { this_p_item->alg = (yyvsp[-2].i); }
#line 9493 "obj/conf/cf-parse.tab.c"
    break;

  case 548: /* password_algorithm: KEYED MD5  */
#line 565 "nest/config.Y"
                { (yyval.i) = ALG_MD5; }
#line 9499 "obj/conf/cf-parse.tab.c"
    break;

  case 549: /* password_algorithm: KEYED SHA1  */
#line 566 "nest/config.Y"
                { (yyval.i) = ALG_SHA1; }
#line 9505 "obj/conf/cf-parse.tab.c"
    break;

  case 550: /* password_algorithm: KEYED SHA256  */
#line 567 "nest/config.Y"
                { (yyval.i) = ALG_SHA256; }
#line 9511 "obj/conf/cf-parse.tab.c"
    break;

  case 551: /* password_algorithm: KEYED SHA384  */
#line 568 "nest/config.Y"
                { (yyval.i) = ALG_SHA384; }
#line 9517 "obj/conf/cf-parse.tab.c"
    break;

  case 552: /* password_algorithm: KEYED SHA512  */
#line 569 "nest/config.Y"
                { (yyval.i) = ALG_SHA512; }
#line 9523 "obj/conf/cf-parse.tab.c"
    break;

  case 553: /* password_algorithm: HMAC MD5  */
#line 570 "nest/config.Y"
                { (yyval.i) = ALG_HMAC_MD5; }
#line 9529 "obj/conf/cf-parse.tab.c"
    break;

  case 554: /* password_algorithm: HMAC SHA1  */
#line 571 "nest/config.Y"
                { (yyval.i) = ALG_HMAC_SHA1; }
#line 9535 "obj/conf/cf-parse.tab.c"
    break;

  case 555: /* password_algorithm: HMAC SHA256  */
#line 572 "nest/config.Y"
                { (yyval.i) = ALG_HMAC_SHA256; }
#line 9541 "obj/conf/cf-parse.tab.c"
    break;

  case 556: /* password_algorithm: HMAC SHA384  */
#line 573 "nest/config.Y"
                { (yyval.i) = ALG_HMAC_SHA384; }
#line 9547 "obj/conf/cf-parse.tab.c"
    break;

  case 557: /* password_algorithm: HMAC SHA512  */
#line 574 "nest/config.Y"
                { (yyval.i) = ALG_HMAC_SHA512; }
#line 9553 "obj/conf/cf-parse.tab.c"
    break;

  case 558: /* password_algorithm: BLAKE2S128  */
#line 575 "nest/config.Y"
                { (yyval.i) = ALG_BLAKE2S_128; }
#line 9559 "obj/conf/cf-parse.tab.c"
    break;

  case 559: /* password_algorithm: BLAKE2S256  */
#line 576 "nest/config.Y"
                { (yyval.i) = ALG_BLAKE2S_256; }
#line 9565 "obj/conf/cf-parse.tab.c"
    break;

  case 560: /* password_algorithm: BLAKE2B256  */
#line 577 "nest/config.Y"
                { (yyval.i) = ALG_BLAKE2B_256; }
#line 9571 "obj/conf/cf-parse.tab.c"
    break;

  case 561: /* password_algorithm: BLAKE2B512  */
#line 578 "nest/config.Y"
                { (yyval.i) = ALG_BLAKE2B_512; }
#line 9577 "obj/conf/cf-parse.tab.c"
    break;

  case 562: /* password_item_end: %empty  */
#line 582 "nest/config.Y"
{
  password_validate_length(this_p_item);
}
#line 9585 "obj/conf/cf-parse.tab.c"
    break;

  case 563: /* bfd_item: INTERVAL expr_us  */
#line 590 "nest/config.Y"
                    { this_bfd_opts->min_rx_int = this_bfd_opts->min_tx_int = (yyvsp[0].time); }
#line 9591 "obj/conf/cf-parse.tab.c"
    break;

  case 564: /* bfd_item: MIN RX INTERVAL expr_us  */
#line 591 "nest/config.Y"
                           { this_bfd_opts->min_rx_int = (yyvsp[0].time); }
#line 9597 "obj/conf/cf-parse.tab.c"
    break;

  case 565: /* bfd_item: MIN TX INTERVAL expr_us  */
#line 592 "nest/config.Y"
                           { this_bfd_opts->min_tx_int = (yyvsp[0].time); }
#line 9603 "obj/conf/cf-parse.tab.c"
    break;

  case 566: /* bfd_item: IDLE TX INTERVAL expr_us  */
#line 593 "nest/config.Y"
                            { this_bfd_opts->idle_tx_int = (yyvsp[0].time); }
#line 9609 "obj/conf/cf-parse.tab.c"
    break;

  case 567: /* bfd_item: MULTIPLIER expr  */
#line 594 "nest/config.Y"
                   { this_bfd_opts->multiplier = (yyvsp[0].i); }
#line 9615 "obj/conf/cf-parse.tab.c"
    break;

  case 568: /* bfd_item: PASSIVE bool  */
#line 595 "nest/config.Y"
                { this_bfd_opts->passive = (yyvsp[0].i); this_bfd_opts->passive_set = 1; }
#line 9621 "obj/conf/cf-parse.tab.c"
    break;

  case 569: /* bfd_item: GRACEFUL  */
#line 596 "nest/config.Y"
            { this_bfd_opts->mode = BGP_BFD_GRACEFUL; }
#line 9627 "obj/conf/cf-parse.tab.c"
    break;

  case 574: /* cmd_SHOW_STATUS: SHOW STATUS END  */
#line 612 "nest/config.Y"
{ cmd_show_status(); }
#line 9633 "obj/conf/cf-parse.tab.c"
    break;

  case 576: /* cmd_CALL_AGENT: CALL_AGENT END  */
#line 614 "nest/config.Y"
{ call_agent(); }
#line 9639 "obj/conf/cf-parse.tab.c"
    break;

  case 578: /* cmd_TEST_LOG: TEST_LOG END  */
#line 617 "nest/config.Y"
{ test_log(); }
#line 9645 "obj/conf/cf-parse.tab.c"
    break;

  case 580: /* cmd_TEST_SEND: TEST_SEND END  */
#line 620 "nest/config.Y"
{ test_send(); }
#line 9651 "obj/conf/cf-parse.tab.c"
    break;

  case 582: /* cmd_SHOW_MEMORY: SHOW MEMORY END  */
#line 623 "nest/config.Y"
{ cmd_show_memory(); }
#line 9657 "obj/conf/cf-parse.tab.c"
    break;

  case 584: /* cmd_SHOW_PROTOCOLS: SHOW PROTOCOLS proto_patt2 END  */
#line 626 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-1].ps), proto_cmd_show, 0, 0); }
#line 9663 "obj/conf/cf-parse.tab.c"
    break;

  case 586: /* cmd_SHOW_PROTOCOLS_ALL: SHOW PROTOCOLS ALL proto_patt2 END  */
#line 629 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-1].ps), proto_cmd_show, 0, 1); }
#line 9669 "obj/conf/cf-parse.tab.c"
    break;

  case 587: /* optproto: CF_SYM_KNOWN  */
#line 632 "nest/config.Y"
                { cf_assert_symbol((yyvsp[0].s), SYM_PROTO); (yyval.s) = (yyvsp[0].s); }
#line 9675 "obj/conf/cf-parse.tab.c"
    break;

  case 588: /* optproto: %empty  */
#line 633 "nest/config.Y"
               { (yyval.s) = NULL; }
#line 9681 "obj/conf/cf-parse.tab.c"
    break;

  case 590: /* cmd_SHOW_INTERFACES: SHOW INTERFACES END  */
#line 637 "nest/config.Y"
{ if_show(); }
#line 9687 "obj/conf/cf-parse.tab.c"
    break;

  case 592: /* cmd_SHOW_INTERFACES_SUMMARY: SHOW INTERFACES SUMMARY END  */
#line 640 "nest/config.Y"
{ if_show_summary(); }
#line 9693 "obj/conf/cf-parse.tab.c"
    break;

  case 594: /* cmd_SHOW_ROUTE: SHOW ROUTE r_args END  */
#line 644 "nest/config.Y"
{ rt_show((yyvsp[-1].ra)); }
#line 9699 "obj/conf/cf-parse.tab.c"
    break;

  case 595: /* r_args: %empty  */
#line 647 "nest/config.Y"
               {
     (yyval.ra) = cfg_allocz(sizeof(struct rt_show_data));
     init_list(&((yyval.ra)->tables));
     (yyval.ra)->filter = FILTER_ACCEPT;
     (yyval.ra)->running_on_config = new_config->fallback;
   }
#line 9710 "obj/conf/cf-parse.tab.c"
    break;

  case 596: /* r_args: r_args net_any  */
#line 653 "nest/config.Y"
                  {
     (yyval.ra) = (yyvsp[-1].ra);
     if ((yyval.ra)->addr) cf_error("Only one prefix expected");
     (yyval.ra)->addr = (yyvsp[0].net_ptr);
     (yyval.ra)->addr_mode = RSD_ADDR_EQUAL;
   }
#line 9721 "obj/conf/cf-parse.tab.c"
    break;

  case 597: /* r_args: r_args FOR r_args_for  */
#line 659 "nest/config.Y"
                         {
     (yyval.ra) = (yyvsp[-2].ra);
     if ((yyval.ra)->addr) cf_error("Only one prefix expected");
     (yyval.ra)->addr = (yyvsp[0].net_ptr);
     (yyval.ra)->addr_mode = RSD_ADDR_FOR;
   }
#line 9732 "obj/conf/cf-parse.tab.c"
    break;

  case 598: /* r_args: r_args IN net_any  */
#line 665 "nest/config.Y"
                     {
     (yyval.ra) = (yyvsp[-2].ra);
     if ((yyval.ra)->addr) cf_error("Only one prefix expected");
     if (!net_type_match((yyvsp[0].net_ptr), NB_IP)) cf_error("Only IP networks accepted for 'in' argument");
     (yyval.ra)->addr = (yyvsp[0].net_ptr);
     (yyval.ra)->addr_mode = RSD_ADDR_IN;
   }
#line 9744 "obj/conf/cf-parse.tab.c"
    break;

  case 599: /* r_args: r_args TABLE CF_SYM_KNOWN  */
#line 672 "nest/config.Y"
                            {
     cf_assert_symbol((yyvsp[0].s), SYM_TABLE);
     (yyval.ra) = (yyvsp[-2].ra);
     rt_show_add_table((yyval.ra), (yyvsp[0].s)->table->table);
     (yyval.ra)->tables_defined_by = RSD_TDB_DIRECT;
   }
#line 9755 "obj/conf/cf-parse.tab.c"
    break;

  case 600: /* r_args: r_args TABLE ALL  */
#line 678 "nest/config.Y"
                    {
     struct rtable_config *t;
     (yyval.ra) = (yyvsp[-2].ra);
     WALK_LIST(t, config->tables)
       rt_show_add_table((yyval.ra), t->table);
     (yyval.ra)->tables_defined_by = RSD_TDB_ALL;
   }
#line 9767 "obj/conf/cf-parse.tab.c"
    break;

  case 601: /* r_args: r_args IMPORT TABLE channel_arg  */
#line 685 "nest/config.Y"
                                   {
     if (!(yyvsp[0].c)->in_table) cf_error("No import table in channel %s.%s", (yyvsp[0].c)->proto->name, (yyvsp[0].c)->name);
     rt_show_add_table((yyval.ra), (yyvsp[0].c)->in_table);
     (yyval.ra)->tables_defined_by = RSD_TDB_DIRECT;
   }
#line 9777 "obj/conf/cf-parse.tab.c"
    break;

  case 602: /* r_args: r_args EXPORT TABLE channel_arg  */
#line 690 "nest/config.Y"
                                   {
     if (!(yyvsp[0].c)->out_table) cf_error("No export table in channel %s.%s", (yyvsp[0].c)->proto->name, (yyvsp[0].c)->name);
     rt_show_add_table((yyval.ra), (yyvsp[0].c)->out_table);
     (yyval.ra)->tables_defined_by = RSD_TDB_DIRECT;
   }
#line 9787 "obj/conf/cf-parse.tab.c"
    break;

  case 603: /* r_args: r_args FILTER filter  */
#line 695 "nest/config.Y"
                        {
     (yyval.ra) = (yyvsp[-2].ra);
     if ((yyval.ra)->filter != FILTER_ACCEPT) cf_error("Filter specified twice");
     (yyval.ra)->filter = (yyvsp[0].f);
   }
#line 9797 "obj/conf/cf-parse.tab.c"
    break;

  case 604: /* r_args: r_args where_filter  */
#line 700 "nest/config.Y"
                       {
     (yyval.ra) = (yyvsp[-1].ra);
     if ((yyval.ra)->filter != FILTER_ACCEPT) cf_error("Filter specified twice");
     (yyval.ra)->filter = (yyvsp[0].f);
   }
#line 9807 "obj/conf/cf-parse.tab.c"
    break;

  case 605: /* r_args: r_args ALL  */
#line 705 "nest/config.Y"
              {
     (yyval.ra) = (yyvsp[-1].ra);
     (yyval.ra)->verbose = 1;
   }
#line 9816 "obj/conf/cf-parse.tab.c"
    break;

  case 606: /* r_args: r_args PRIMARY  */
#line 709 "nest/config.Y"
                  {
     (yyval.ra) = (yyvsp[-1].ra);
     (yyval.ra)->primary_only = 1;
   }
#line 9825 "obj/conf/cf-parse.tab.c"
    break;

  case 607: /* r_args: r_args FILTERED  */
#line 713 "nest/config.Y"
                   {
     (yyval.ra) = (yyvsp[-1].ra);
     (yyval.ra)->filtered = 1;
   }
#line 9834 "obj/conf/cf-parse.tab.c"
    break;

  case 608: /* r_args: r_args export_mode CF_SYM_KNOWN  */
#line 717 "nest/config.Y"
                                   {
     cf_assert_symbol((yyvsp[0].s), SYM_PROTO);
     struct proto_config *c = (struct proto_config *) (yyvsp[0].s)->proto;
     (yyval.ra) = (yyvsp[-2].ra);
     if ((yyval.ra)->export_mode) cf_error("Export specified twice");
     if (!c->proto) cf_error("%s is not a protocol", (yyvsp[0].s)->name);
     (yyval.ra)->export_mode = (yyvsp[-1].i);
     (yyval.ra)->export_protocol = c->proto;
     (yyval.ra)->tables_defined_by = RSD_TDB_INDIRECT;
   }
#line 9849 "obj/conf/cf-parse.tab.c"
    break;

  case 609: /* r_args: r_args export_mode channel_arg  */
#line 727 "nest/config.Y"
                                  {
     (yyval.ra) = (yyvsp[-2].ra);
     if ((yyval.ra)->export_mode) cf_error("Export specified twice");
     (yyval.ra)->export_mode = (yyvsp[-1].i);
     (yyval.ra)->export_channel = (yyvsp[0].c);
     (yyval.ra)->tables_defined_by = RSD_TDB_INDIRECT;
   }
#line 9861 "obj/conf/cf-parse.tab.c"
    break;

  case 610: /* r_args: r_args PROTOCOL CF_SYM_KNOWN  */
#line 734 "nest/config.Y"
                                {
     cf_assert_symbol((yyvsp[0].s), SYM_PROTO);
     struct proto_config *c = (struct proto_config *) (yyvsp[0].s)->proto;
     (yyval.ra) = (yyvsp[-2].ra);
     if ((yyval.ra)->show_protocol) cf_error("Protocol specified twice");
     if (!c->proto) cf_error("%s is not a protocol", (yyvsp[0].s)->name);
     (yyval.ra)->show_protocol = c->proto;
     (yyval.ra)->tables_defined_by = RSD_TDB_INDIRECT;
   }
#line 9875 "obj/conf/cf-parse.tab.c"
    break;

  case 611: /* r_args: r_args STATS  */
#line 743 "nest/config.Y"
                {
     (yyval.ra) = (yyvsp[-1].ra);
     (yyval.ra)->stats = 1;
   }
#line 9884 "obj/conf/cf-parse.tab.c"
    break;

  case 612: /* r_args: r_args COUNT  */
#line 747 "nest/config.Y"
                {
     (yyval.ra) = (yyvsp[-1].ra);
     (yyval.ra)->stats = 2;
   }
#line 9893 "obj/conf/cf-parse.tab.c"
    break;

  case 613: /* r_args_for: r_args_for_val  */
#line 754 "nest/config.Y"
                 {
    (yyval.net_ptr) = cfg_alloc((yyvsp[0].net).length);
    net_copy((yyval.net_ptr), &(yyvsp[0].net));
  }
#line 9902 "obj/conf/cf-parse.tab.c"
    break;

  case 617: /* r_args_for: VPN_RD IP4  */
#line 761 "nest/config.Y"
              {
    (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_vpn4));
    net_fill_vpn4((yyval.net_ptr), (yyvsp[0].ip4), IP4_MAX_PREFIX_LENGTH, (yyvsp[-1].i64));
  }
#line 9911 "obj/conf/cf-parse.tab.c"
    break;

  case 618: /* r_args_for: VPN_RD IP6  */
#line 765 "nest/config.Y"
              {
    (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_vpn6));
    net_fill_vpn6((yyval.net_ptr), (yyvsp[0].ip6), IP6_MAX_PREFIX_LENGTH, (yyvsp[-1].i64));
  }
#line 9920 "obj/conf/cf-parse.tab.c"
    break;

  case 619: /* r_args_for: IP6 FROM IP6  */
#line 769 "nest/config.Y"
                {
    (yyval.net_ptr) = cfg_alloc(sizeof(net_addr_ip6_sadr));
    net_fill_ip6_sadr((yyval.net_ptr), (yyvsp[-2].ip6), IP6_MAX_PREFIX_LENGTH, (yyvsp[0].ip6), IP6_MAX_PREFIX_LENGTH);
  }
#line 9929 "obj/conf/cf-parse.tab.c"
    break;

  case 620: /* r_args_for: CF_SYM_KNOWN  */
#line 773 "nest/config.Y"
                {
     if ((yyvsp[0].s)->class == (SYM_CONSTANT | T_IP))
     {
       (yyval.net_ptr) = cfg_alloc(ipa_is_ip4(SYM_VAL((yyvsp[0].s)).ip) ? sizeof(net_addr_ip4) : sizeof(net_addr_ip6));
       net_fill_ip_host((yyval.net_ptr), SYM_VAL((yyvsp[0].s)).ip);
     }
     else if (((yyvsp[0].s)->class == (SYM_CONSTANT | T_NET)) && net_type_match(SYM_VAL((yyvsp[0].s)).net, NB_IP | NB_VPN))
       (yyval.net_ptr) = (net_addr *) SYM_VAL((yyvsp[0].s)).net; /* Avoid const warning */
     else
       cf_error("IP address or network constant expected");
   }
#line 9945 "obj/conf/cf-parse.tab.c"
    break;

  case 623: /* r_args_for_val: IP4  */
#line 789 "nest/config.Y"
       { net_fill_ip4(&((yyval.net)), (yyvsp[0].ip4), IP4_MAX_PREFIX_LENGTH); }
#line 9951 "obj/conf/cf-parse.tab.c"
    break;

  case 624: /* r_args_for_val: IP6  */
#line 790 "nest/config.Y"
       { net_fill_ip6(&((yyval.net)), (yyvsp[0].ip6), IP6_MAX_PREFIX_LENGTH); }
#line 9957 "obj/conf/cf-parse.tab.c"
    break;

  case 625: /* export_mode: PREEXPORT  */
#line 793 "nest/config.Y"
                { (yyval.i) = RSEM_PREEXPORT; }
#line 9963 "obj/conf/cf-parse.tab.c"
    break;

  case 626: /* export_mode: EXPORT  */
#line 794 "nest/config.Y"
                { (yyval.i) = RSEM_EXPORT; }
#line 9969 "obj/conf/cf-parse.tab.c"
    break;

  case 627: /* export_mode: NOEXPORT  */
#line 795 "nest/config.Y"
                { (yyval.i) = RSEM_NOEXPORT; }
#line 9975 "obj/conf/cf-parse.tab.c"
    break;

  case 628: /* export_mode: EXPORTED  */
#line 796 "nest/config.Y"
                { (yyval.i) = RSEM_EXPORTED; }
#line 9981 "obj/conf/cf-parse.tab.c"
    break;

  case 629: /* channel_sym: IPV4  */
#line 801 "nest/config.Y"
                { (yyval.t) = "ipv4"; }
#line 9987 "obj/conf/cf-parse.tab.c"
    break;

  case 630: /* channel_sym: IPV4_MC  */
#line 802 "nest/config.Y"
                { (yyval.t) = "ipv4-mc"; }
#line 9993 "obj/conf/cf-parse.tab.c"
    break;

  case 631: /* channel_sym: IPV4_MPLS  */
#line 803 "nest/config.Y"
                { (yyval.t) = "ipv4-mpls"; }
#line 9999 "obj/conf/cf-parse.tab.c"
    break;

  case 632: /* channel_sym: IPV6  */
#line 804 "nest/config.Y"
                { (yyval.t) = "ipv6"; }
#line 10005 "obj/conf/cf-parse.tab.c"
    break;

  case 633: /* channel_sym: IPV6_MC  */
#line 805 "nest/config.Y"
                { (yyval.t) = "ipv6-mc"; }
#line 10011 "obj/conf/cf-parse.tab.c"
    break;

  case 634: /* channel_sym: IPV6_MPLS  */
#line 806 "nest/config.Y"
                { (yyval.t) = "ipv6-mpls"; }
#line 10017 "obj/conf/cf-parse.tab.c"
    break;

  case 635: /* channel_sym: IPV6_SADR  */
#line 807 "nest/config.Y"
                { (yyval.t) = "ipv6-sadr"; }
#line 10023 "obj/conf/cf-parse.tab.c"
    break;

  case 636: /* channel_sym: VPN4  */
#line 808 "nest/config.Y"
                { (yyval.t) = "vpn4"; }
#line 10029 "obj/conf/cf-parse.tab.c"
    break;

  case 637: /* channel_sym: VPN4_MC  */
#line 809 "nest/config.Y"
                { (yyval.t) = "vpn4-mc"; }
#line 10035 "obj/conf/cf-parse.tab.c"
    break;

  case 638: /* channel_sym: VPN4_MPLS  */
#line 810 "nest/config.Y"
                { (yyval.t) = "vpn4-mpls"; }
#line 10041 "obj/conf/cf-parse.tab.c"
    break;

  case 639: /* channel_sym: VPN6  */
#line 811 "nest/config.Y"
                { (yyval.t) = "vpn6"; }
#line 10047 "obj/conf/cf-parse.tab.c"
    break;

  case 640: /* channel_sym: VPN6_MC  */
#line 812 "nest/config.Y"
                { (yyval.t) = "vpn6-mc"; }
#line 10053 "obj/conf/cf-parse.tab.c"
    break;

  case 641: /* channel_sym: VPN6_MPLS  */
#line 813 "nest/config.Y"
                { (yyval.t) = "vpn6-mpls"; }
#line 10059 "obj/conf/cf-parse.tab.c"
    break;

  case 642: /* channel_sym: ROA4  */
#line 814 "nest/config.Y"
                { (yyval.t) = "roa4"; }
#line 10065 "obj/conf/cf-parse.tab.c"
    break;

  case 643: /* channel_sym: ROA6  */
#line 815 "nest/config.Y"
                { (yyval.t) = "roa6"; }
#line 10071 "obj/conf/cf-parse.tab.c"
    break;

  case 644: /* channel_sym: FLOW4  */
#line 816 "nest/config.Y"
                { (yyval.t) = "flow4"; }
#line 10077 "obj/conf/cf-parse.tab.c"
    break;

  case 645: /* channel_sym: FLOW6  */
#line 817 "nest/config.Y"
                { (yyval.t) = "flow6"; }
#line 10083 "obj/conf/cf-parse.tab.c"
    break;

  case 646: /* channel_sym: MPLS  */
#line 818 "nest/config.Y"
                { (yyval.t) = "mpls"; }
#line 10089 "obj/conf/cf-parse.tab.c"
    break;

  case 647: /* channel_sym: PRI  */
#line 819 "nest/config.Y"
                { (yyval.t) = "pri"; }
#line 10095 "obj/conf/cf-parse.tab.c"
    break;

  case 648: /* channel_sym: SEC  */
#line 820 "nest/config.Y"
                { (yyval.t) = "sec"; }
#line 10101 "obj/conf/cf-parse.tab.c"
    break;

  case 649: /* channel_arg: CF_SYM_KNOWN '.' channel_sym  */
#line 824 "nest/config.Y"
                                {
     cf_assert_symbol((yyvsp[-2].s), SYM_PROTO);
     struct proto *p =  (yyvsp[-2].s)->proto->proto;
     if (!p) cf_error("%s is not a protocol", (yyvsp[-2].s)->name);
     (yyval.c) = proto_find_channel_by_name(p, (yyvsp[0].t));
     if (!(yyval.c)) cf_error("Channel %s.%s not found", (yyvsp[-2].s)->name, (yyvsp[0].t));
   }
#line 10113 "obj/conf/cf-parse.tab.c"
    break;

  case 651: /* cmd_SHOW_SYMBOLS: SHOW SYMBOLS sym_args END  */
#line 835 "nest/config.Y"
{ cmd_show_symbols((yyvsp[-1].sd)); }
#line 10119 "obj/conf/cf-parse.tab.c"
    break;

  case 652: /* sym_args: %empty  */
#line 838 "nest/config.Y"
               {
     (yyval.sd) = cfg_allocz(sizeof(struct sym_show_data));
   }
#line 10127 "obj/conf/cf-parse.tab.c"
    break;

  case 653: /* sym_args: sym_args TABLE  */
#line 841 "nest/config.Y"
                  { (yyval.sd) = (yyvsp[-1].sd); (yyval.sd)->type = SYM_TABLE; }
#line 10133 "obj/conf/cf-parse.tab.c"
    break;

  case 654: /* sym_args: sym_args FUNCTION  */
#line 842 "nest/config.Y"
                     { (yyval.sd) = (yyvsp[-1].sd); (yyval.sd)->type = SYM_FUNCTION; }
#line 10139 "obj/conf/cf-parse.tab.c"
    break;

  case 655: /* sym_args: sym_args FILTER  */
#line 843 "nest/config.Y"
                   { (yyval.sd) = (yyvsp[-1].sd); (yyval.sd)->type = SYM_FILTER; }
#line 10145 "obj/conf/cf-parse.tab.c"
    break;

  case 656: /* sym_args: sym_args PROTOCOL  */
#line 844 "nest/config.Y"
                     { (yyval.sd) = (yyvsp[-1].sd); (yyval.sd)->type = SYM_PROTO; }
#line 10151 "obj/conf/cf-parse.tab.c"
    break;

  case 657: /* sym_args: sym_args TEMPLATE  */
#line 845 "nest/config.Y"
                     { (yyval.sd) = (yyvsp[-1].sd); (yyval.sd)->type = SYM_TEMPLATE; }
#line 10157 "obj/conf/cf-parse.tab.c"
    break;

  case 658: /* sym_args: sym_args symbol  */
#line 846 "nest/config.Y"
                   { (yyval.sd) = (yyvsp[-1].sd); (yyval.sd)->sym = (yyvsp[0].s); }
#line 10163 "obj/conf/cf-parse.tab.c"
    break;

  case 660: /* cmd_DUMP_RESOURCES: DUMP RESOURCES END  */
#line 852 "nest/config.Y"
{ rdump(&root_pool); cli_msg(0, ""); }
#line 10169 "obj/conf/cf-parse.tab.c"
    break;

  case 662: /* cmd_DUMP_SOCKETS: DUMP SOCKETS END  */
#line 854 "nest/config.Y"
{ sk_dump_all(); cli_msg(0, ""); }
#line 10175 "obj/conf/cf-parse.tab.c"
    break;

  case 664: /* cmd_DUMP_EVENTS: DUMP EVENTS END  */
#line 856 "nest/config.Y"
{ io_log_dump(); cli_msg(0, ""); }
#line 10181 "obj/conf/cf-parse.tab.c"
    break;

  case 666: /* cmd_DUMP_INTERFACES: DUMP INTERFACES END  */
#line 858 "nest/config.Y"
{ if_dump_all(); cli_msg(0, ""); }
#line 10187 "obj/conf/cf-parse.tab.c"
    break;

  case 668: /* cmd_DUMP_NEIGHBORS: DUMP NEIGHBORS END  */
#line 860 "nest/config.Y"
{ neigh_dump_all(); cli_msg(0, ""); }
#line 10193 "obj/conf/cf-parse.tab.c"
    break;

  case 670: /* cmd_DUMP_ATTRIBUTES: DUMP ATTRIBUTES END  */
#line 862 "nest/config.Y"
{ rta_dump_all(); cli_msg(0, ""); }
#line 10199 "obj/conf/cf-parse.tab.c"
    break;

  case 672: /* cmd_DUMP_ROUTES: DUMP ROUTES END  */
#line 864 "nest/config.Y"
{ rt_dump_all(); cli_msg(0, ""); }
#line 10205 "obj/conf/cf-parse.tab.c"
    break;

  case 674: /* cmd_DUMP_PROTOCOLS: DUMP PROTOCOLS END  */
#line 866 "nest/config.Y"
{ protos_dump_all(); cli_msg(0, ""); }
#line 10211 "obj/conf/cf-parse.tab.c"
    break;

  case 676: /* cmd_DUMP_FILTER_ALL: DUMP FILTER ALL END  */
#line 868 "nest/config.Y"
{ filters_dump_all(); cli_msg(0, ""); }
#line 10217 "obj/conf/cf-parse.tab.c"
    break;

  case 678: /* cmd_EVAL: EVAL term END  */
#line 871 "nest/config.Y"
{ cmd_eval(f_linearize((yyvsp[-1].x), 1)); }
#line 10223 "obj/conf/cf-parse.tab.c"
    break;

  case 680: /* cmd_ECHO: ECHO echo_mask echo_size END  */
#line 874 "nest/config.Y"
                                       {
  cli_set_log_echo(this_cli, (yyvsp[-2].i), (yyvsp[-1].i));
  cli_msg(0, "");
}
#line 10232 "obj/conf/cf-parse.tab.c"
    break;

  case 681: /* echo_mask: ALL  */
#line 880 "nest/config.Y"
       { (yyval.i) = ~0; }
#line 10238 "obj/conf/cf-parse.tab.c"
    break;

  case 682: /* echo_mask: OFF  */
#line 881 "nest/config.Y"
       { (yyval.i) = 0; }
#line 10244 "obj/conf/cf-parse.tab.c"
    break;

  case 683: /* echo_mask: '{' log_mask_list '}'  */
#line 882 "nest/config.Y"
                         { (yyval.i) = (yyvsp[-1].i); }
#line 10250 "obj/conf/cf-parse.tab.c"
    break;

  case 684: /* echo_size: %empty  */
#line 886 "nest/config.Y"
               { (yyval.i) = 4096; }
#line 10256 "obj/conf/cf-parse.tab.c"
    break;

  case 685: /* echo_size: NUM  */
#line 887 "nest/config.Y"
       {
     if ((yyvsp[0].i) < 256 || (yyvsp[0].i) > 65536) cf_error("Invalid log buffer size");
     (yyval.i) = (yyvsp[0].i);
   }
#line 10265 "obj/conf/cf-parse.tab.c"
    break;

  case 687: /* cmd_DISABLE: DISABLE proto_patt opttext END  */
#line 894 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-2].ps), proto_cmd_disable, 1, (uintptr_t) (yyvsp[-1].t)); }
#line 10271 "obj/conf/cf-parse.tab.c"
    break;

  case 689: /* cmd_ENABLE: ENABLE proto_patt opttext END  */
#line 896 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-2].ps), proto_cmd_enable, 1, (uintptr_t) (yyvsp[-1].t)); }
#line 10277 "obj/conf/cf-parse.tab.c"
    break;

  case 691: /* cmd_RESTART: RESTART proto_patt opttext END  */
#line 898 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-2].ps), proto_cmd_restart, 1, (uintptr_t) (yyvsp[-1].t)); }
#line 10283 "obj/conf/cf-parse.tab.c"
    break;

  case 693: /* cmd_RELOAD: RELOAD proto_patt END  */
#line 900 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-1].ps), proto_cmd_reload, 1, CMD_RELOAD); }
#line 10289 "obj/conf/cf-parse.tab.c"
    break;

  case 695: /* cmd_RELOAD_IN: RELOAD IN proto_patt END  */
#line 902 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-1].ps), proto_cmd_reload, 1, CMD_RELOAD_IN); }
#line 10295 "obj/conf/cf-parse.tab.c"
    break;

  case 697: /* cmd_RELOAD_OUT: RELOAD OUT proto_patt END  */
#line 904 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-1].ps), proto_cmd_reload, 1, CMD_RELOAD_OUT); }
#line 10301 "obj/conf/cf-parse.tab.c"
    break;

  case 699: /* cmd_DEBUG: DEBUG debug_args END  */
#line 908 "nest/config.Y"
{ /* Done in debug_args */  }
#line 10307 "obj/conf/cf-parse.tab.c"
    break;

  case 700: /* debug_args: proto_patt debug_mask  */
#line 911 "nest/config.Y"
                         { proto_apply_cmd((yyvsp[-1].ps), proto_cmd_debug, 1, (yyvsp[0].i));  }
#line 10313 "obj/conf/cf-parse.tab.c"
    break;

  case 701: /* debug_args: channel_arg debug_mask  */
#line 912 "nest/config.Y"
                          { channel_cmd_debug((yyvsp[-1].c), (yyvsp[0].i)); }
#line 10319 "obj/conf/cf-parse.tab.c"
    break;

  case 703: /* cmd_MRTDUMP: MRTDUMP proto_patt mrtdump_mask END  */
#line 917 "nest/config.Y"
{ proto_apply_cmd((yyvsp[-2].ps), proto_cmd_mrtdump, 1, (yyvsp[-1].i)); }
#line 10325 "obj/conf/cf-parse.tab.c"
    break;

  case 705: /* cmd_RESTRICT: RESTRICT END  */
#line 920 "nest/config.Y"
{ this_cli->restricted = 1; cli_msg(16, "Access restricted"); }
#line 10331 "obj/conf/cf-parse.tab.c"
    break;

  case 706: /* proto_patt: CF_SYM_KNOWN  */
#line 923 "nest/config.Y"
                { cf_assert_symbol((yyvsp[0].s), SYM_PROTO); (yyval.ps).ptr = (yyvsp[0].s); (yyval.ps).patt = 0; }
#line 10337 "obj/conf/cf-parse.tab.c"
    break;

  case 707: /* proto_patt: ALL  */
#line 924 "nest/config.Y"
        { (yyval.ps).ptr = NULL; (yyval.ps).patt = 1; }
#line 10343 "obj/conf/cf-parse.tab.c"
    break;

  case 708: /* proto_patt: TEXT  */
#line 925 "nest/config.Y"
        { (yyval.ps).ptr = (yyvsp[0].t); (yyval.ps).patt = 1; }
#line 10349 "obj/conf/cf-parse.tab.c"
    break;

  case 709: /* proto_patt2: CF_SYM_KNOWN  */
#line 929 "nest/config.Y"
                { cf_assert_symbol((yyvsp[0].s), SYM_PROTO); (yyval.ps).ptr = (yyvsp[0].s); (yyval.ps).patt = 0; }
#line 10355 "obj/conf/cf-parse.tab.c"
    break;

  case 710: /* proto_patt2: %empty  */
#line 930 "nest/config.Y"
        { (yyval.ps).ptr = NULL; (yyval.ps).patt = 1; }
#line 10361 "obj/conf/cf-parse.tab.c"
    break;

  case 711: /* proto_patt2: TEXT  */
#line 931 "nest/config.Y"
        { (yyval.ps).ptr = (yyvsp[0].t); (yyval.ps).patt = 1; }
#line 10367 "obj/conf/cf-parse.tab.c"
    break;

  case 712: /* dynamic_attr: IGP_METRIC  */
#line 934 "nest/config.Y"
                         { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_GEN_IGP_METRIC); }
#line 10373 "obj/conf/cf-parse.tab.c"
    break;

  case 714: /* bfd_proto_start: proto_start BFD  */
#line 38 "proto/bfd/config.Y"
{
  this_proto = proto_config_new(&proto_bfd, (yyvsp[-1].i));
  init_list(&BFD_CFG->patt_list);
  init_list(&BFD_CFG->neigh_list);
  BFD_CFG->accept_ipv4 = BFD_CFG->accept_ipv6 = 1;
  BFD_CFG->accept_direct = BFD_CFG->accept_multihop = 1;
}
#line 10385 "obj/conf/cf-parse.tab.c"
    break;

  case 720: /* bfd_proto_item: STRICT BIND bool  */
#line 52 "proto/bfd/config.Y"
                    { BFD_CFG->strict_bind = (yyvsp[0].i); }
#line 10391 "obj/conf/cf-parse.tab.c"
    break;

  case 724: /* bfd_accept_item: IPV4  */
#line 65 "proto/bfd/config.Y"
                        { BFD_CFG->accept_ipv4 = 1;  BFD_CFG->accept_ipv6 = 0; }
#line 10397 "obj/conf/cf-parse.tab.c"
    break;

  case 725: /* bfd_accept_item: IPV6  */
#line 66 "proto/bfd/config.Y"
                        { BFD_CFG->accept_ipv4 = 0;  BFD_CFG->accept_ipv6 = 1; }
#line 10403 "obj/conf/cf-parse.tab.c"
    break;

  case 726: /* bfd_accept_item: DIRECT  */
#line 67 "proto/bfd/config.Y"
                        { BFD_CFG->accept_direct = 1;  BFD_CFG->accept_multihop = 0; }
#line 10409 "obj/conf/cf-parse.tab.c"
    break;

  case 727: /* bfd_accept_item: MULTIHOP  */
#line 68 "proto/bfd/config.Y"
                        { BFD_CFG->accept_direct = 0;  BFD_CFG->accept_multihop = 1; }
#line 10415 "obj/conf/cf-parse.tab.c"
    break;

  case 728: /* bfd_accept: %empty  */
#line 72 "proto/bfd/config.Y"
   {
     BFD_CFG->accept_ipv4 = BFD_CFG->accept_ipv6 = 1;
     BFD_CFG->accept_direct = BFD_CFG->accept_multihop = 1;
   }
#line 10424 "obj/conf/cf-parse.tab.c"
    break;

  case 730: /* bfd_iface_start: %empty  */
#line 80 "proto/bfd/config.Y"
{
  this_ipatt = cfg_allocz(sizeof(struct bfd_iface_config));
  add_tail(&BFD_CFG->patt_list, NODE this_ipatt);
  init_list(&this_ipatt->ipn_list);

  BFD_IFACE->min_rx_int = BFD_DEFAULT_MIN_RX_INT;
  BFD_IFACE->min_tx_int = BFD_DEFAULT_MIN_TX_INT;
  BFD_IFACE->idle_tx_int = BFD_DEFAULT_IDLE_TX_INT;
  BFD_IFACE->multiplier = BFD_DEFAULT_MULTIPLIER;

  reset_passwords();
}
#line 10441 "obj/conf/cf-parse.tab.c"
    break;

  case 731: /* bfd_iface_finish: %empty  */
#line 94 "proto/bfd/config.Y"
{
  BFD_IFACE->passwords = get_passwords();

  if (!BFD_IFACE->auth_type != !BFD_IFACE->passwords)
    log(L_WARN "Authentication and password options should be used together");

  if (BFD_IFACE->passwords)
  {
    struct password_item *pass;
    WALK_LIST(pass, *BFD_IFACE->passwords)
    {
      if (pass->alg)
        cf_error("Password algorithm option not available in BFD protocol");

      pass->alg = bfd_auth_type_to_hash_alg[BFD_IFACE->auth_type];
    }
  }
}
#line 10464 "obj/conf/cf-parse.tab.c"
    break;

  case 732: /* bfd_iface_item: INTERVAL expr_us  */
#line 114 "proto/bfd/config.Y"
                    { BFD_IFACE->min_rx_int = BFD_IFACE->min_tx_int = (yyvsp[0].time); }
#line 10470 "obj/conf/cf-parse.tab.c"
    break;

  case 733: /* bfd_iface_item: MIN RX INTERVAL expr_us  */
#line 115 "proto/bfd/config.Y"
                           { BFD_IFACE->min_rx_int = (yyvsp[0].time); }
#line 10476 "obj/conf/cf-parse.tab.c"
    break;

  case 734: /* bfd_iface_item: MIN TX INTERVAL expr_us  */
#line 116 "proto/bfd/config.Y"
                           { BFD_IFACE->min_tx_int = (yyvsp[0].time); }
#line 10482 "obj/conf/cf-parse.tab.c"
    break;

  case 735: /* bfd_iface_item: IDLE TX INTERVAL expr_us  */
#line 117 "proto/bfd/config.Y"
                            { BFD_IFACE->idle_tx_int = (yyvsp[0].time); }
#line 10488 "obj/conf/cf-parse.tab.c"
    break;

  case 736: /* bfd_iface_item: MULTIPLIER expr  */
#line 118 "proto/bfd/config.Y"
                   { BFD_IFACE->multiplier = (yyvsp[0].i); }
#line 10494 "obj/conf/cf-parse.tab.c"
    break;

  case 737: /* bfd_iface_item: PASSIVE bool  */
#line 119 "proto/bfd/config.Y"
                { BFD_IFACE->passive = (yyvsp[0].i); }
#line 10500 "obj/conf/cf-parse.tab.c"
    break;

  case 738: /* bfd_iface_item: AUTHENTICATION bfd_auth_type  */
#line 120 "proto/bfd/config.Y"
                                { BFD_IFACE->auth_type = (yyvsp[0].i); }
#line 10506 "obj/conf/cf-parse.tab.c"
    break;

  case 739: /* bfd_iface_item: password_list  */
#line 121 "proto/bfd/config.Y"
                 {}
#line 10512 "obj/conf/cf-parse.tab.c"
    break;

  case 740: /* bfd_auth_type: NONE  */
#line 125 "proto/bfd/config.Y"
                         { (yyval.i) = BFD_AUTH_NONE; }
#line 10518 "obj/conf/cf-parse.tab.c"
    break;

  case 741: /* bfd_auth_type: SIMPLE  */
#line 126 "proto/bfd/config.Y"
                         { (yyval.i) = BFD_AUTH_SIMPLE; }
#line 10524 "obj/conf/cf-parse.tab.c"
    break;

  case 742: /* bfd_auth_type: KEYED MD5  */
#line 127 "proto/bfd/config.Y"
                         { (yyval.i) = BFD_AUTH_KEYED_MD5; }
#line 10530 "obj/conf/cf-parse.tab.c"
    break;

  case 743: /* bfd_auth_type: KEYED SHA1  */
#line 128 "proto/bfd/config.Y"
                         { (yyval.i) = BFD_AUTH_KEYED_SHA1; }
#line 10536 "obj/conf/cf-parse.tab.c"
    break;

  case 744: /* bfd_auth_type: METICULOUS KEYED MD5  */
#line 129 "proto/bfd/config.Y"
                         { (yyval.i) = BFD_AUTH_METICULOUS_KEYED_MD5; }
#line 10542 "obj/conf/cf-parse.tab.c"
    break;

  case 745: /* bfd_auth_type: METICULOUS KEYED SHA1  */
#line 130 "proto/bfd/config.Y"
                         { (yyval.i) = BFD_AUTH_METICULOUS_KEYED_SHA1; }
#line 10548 "obj/conf/cf-parse.tab.c"
    break;

  case 751: /* bfd_multihop: bfd_iface_start bfd_iface_opt_list bfd_iface_finish  */
#line 148 "proto/bfd/config.Y"
{ BFD_CFG->multihop = BFD_IFACE; }
#line 10554 "obj/conf/cf-parse.tab.c"
    break;

  case 752: /* bfd_neigh_iface: %empty  */
#line 152 "proto/bfd/config.Y"
               { (yyval.iface) = NULL; }
#line 10560 "obj/conf/cf-parse.tab.c"
    break;

  case 753: /* bfd_neigh_iface: '%' symbol  */
#line 153 "proto/bfd/config.Y"
              { (yyval.iface) = if_get_by_name((yyvsp[0].s)->name); }
#line 10566 "obj/conf/cf-parse.tab.c"
    break;

  case 754: /* bfd_neigh_iface: DEV text  */
#line 154 "proto/bfd/config.Y"
            { (yyval.iface) = if_get_by_name((yyvsp[0].t)); }
#line 10572 "obj/conf/cf-parse.tab.c"
    break;

  case 755: /* bfd_neigh_local: %empty  */
#line 158 "proto/bfd/config.Y"
               { (yyval.a) = IPA_NONE; }
#line 10578 "obj/conf/cf-parse.tab.c"
    break;

  case 756: /* bfd_neigh_local: LOCAL ipa  */
#line 159 "proto/bfd/config.Y"
             { (yyval.a) = (yyvsp[0].a); }
#line 10584 "obj/conf/cf-parse.tab.c"
    break;

  case 757: /* bfd_neigh_multihop: %empty  */
#line 163 "proto/bfd/config.Y"
               { (yyval.i) = 0; }
#line 10590 "obj/conf/cf-parse.tab.c"
    break;

  case 758: /* bfd_neigh_multihop: MULTIHOP bool  */
#line 164 "proto/bfd/config.Y"
                 { (yyval.i) = (yyvsp[0].i); }
#line 10596 "obj/conf/cf-parse.tab.c"
    break;

  case 759: /* bfd_neighbor: ipa bfd_neigh_iface bfd_neigh_local bfd_neigh_multihop  */
#line 168 "proto/bfd/config.Y"
{
  this_bfd_neighbor = cfg_allocz(sizeof(struct bfd_neighbor));
  add_tail(&BFD_CFG->neigh_list, NODE this_bfd_neighbor);

  BFD_NEIGHBOR->addr = (yyvsp[-3].a);
  BFD_NEIGHBOR->local = (yyvsp[-1].a);
  BFD_NEIGHBOR->iface = (yyvsp[-2].iface);
  BFD_NEIGHBOR->multihop = (yyvsp[0].i);

  if ((yyvsp[0].i) && (yyvsp[-2].iface))
    cf_error("Neighbor cannot set both interface and multihop");

  if ((yyvsp[0].i) && ipa_zero((yyvsp[-1].a)))
    cf_error("Multihop neighbor requires specified local address");
}
#line 10616 "obj/conf/cf-parse.tab.c"
    break;

  case 761: /* cmd_SHOW_BFD_SESSIONS: SHOW BFD SESSIONS optproto END  */
#line 187 "proto/bfd/config.Y"
{ PROTO_WALK_CMD((yyvsp[-1].s), &proto_bfd, p) bfd_show_sessions(p); }
#line 10622 "obj/conf/cf-parse.tab.c"
    break;

  case 763: /* babel_proto_start: proto_start BABEL  */
#line 35 "proto/babel/config.Y"
{
  this_proto = proto_config_new(&proto_babel, (yyvsp[-1].i));
  init_list(&BABEL_CFG->iface_list);
  BABEL_CFG->hold_time = 1 S_;
}
#line 10632 "obj/conf/cf-parse.tab.c"
    break;

  case 767: /* babel_proto_item: RANDOMIZE ROUTER ID bool  */
#line 45 "proto/babel/config.Y"
                            { BABEL_CFG->randomize_router_id = (yyvsp[0].i); }
#line 10638 "obj/conf/cf-parse.tab.c"
    break;

  case 771: /* babel_iface_start: %empty  */
#line 58 "proto/babel/config.Y"
{
  this_ipatt = cfg_allocz(sizeof(struct babel_iface_config));
  add_tail(&BABEL_CFG->iface_list, NODE this_ipatt);
  init_list(&this_ipatt->ipn_list);
  reset_passwords();

  BABEL_IFACE->port = BABEL_PORT;
  BABEL_IFACE->type = BABEL_IFACE_TYPE_WIRED;
  BABEL_IFACE->limit = BABEL_HELLO_LIMIT;
  BABEL_IFACE->tx_tos = IP_PREC_INTERNET_CONTROL;
  BABEL_IFACE->tx_priority = sk_priority_control;
  BABEL_IFACE->check_link = 1;
}
#line 10656 "obj/conf/cf-parse.tab.c"
    break;

  case 772: /* babel_iface_finish: %empty  */
#line 74 "proto/babel/config.Y"
{
  if (BABEL_IFACE->type == BABEL_IFACE_TYPE_WIRELESS)
  {
    if (!BABEL_IFACE->hello_interval)
      BABEL_IFACE->hello_interval = BABEL_HELLO_INTERVAL_WIRELESS;
    if (!BABEL_IFACE->rxcost)
      BABEL_IFACE->rxcost = BABEL_RXCOST_WIRELESS;
  }
  else
  {
    if (!BABEL_IFACE->hello_interval)
      BABEL_IFACE->hello_interval = BABEL_HELLO_INTERVAL_WIRED;
    if (!BABEL_IFACE->rxcost)
      BABEL_IFACE->rxcost = BABEL_RXCOST_WIRED;
  }

  /* Make sure we do not overflow the 16-bit centisec fields */
  if (!BABEL_IFACE->update_interval)
    BABEL_IFACE->update_interval = MIN_(BABEL_IFACE->hello_interval*BABEL_UPDATE_INTERVAL_FACTOR, BABEL_MAX_INTERVAL);
  BABEL_IFACE->ihu_interval = MIN_(BABEL_IFACE->hello_interval*BABEL_IHU_INTERVAL_FACTOR, BABEL_MAX_INTERVAL);

  BABEL_CFG->hold_time = MAX_(BABEL_CFG->hold_time, BABEL_IFACE->update_interval*BABEL_HOLD_TIME_FACTOR);

  BABEL_IFACE->passwords = get_passwords();

  if (!BABEL_IFACE->auth_type != !BABEL_IFACE->passwords)
    cf_error("Authentication and password options should be used together");

  if (BABEL_IFACE->passwords)
  {
    struct password_item *pass;
    uint len = 0, i = 0;

    WALK_LIST(pass, *BABEL_IFACE->passwords)
    {
      /* Set default crypto algorithm (HMAC-SHA256) */
      if (!pass->alg)
	pass->alg = ALG_HMAC_SHA256;

      if (!((pass->alg & ALG_HMAC) ||
	    (pass->alg == ALG_BLAKE2S_128) ||
	    (pass->alg == ALG_BLAKE2S_256) ||
	    (pass->alg == ALG_BLAKE2B_256) ||
	    (pass->alg == ALG_BLAKE2B_512)))
	cf_error("Only HMAC and Blake2 algorithms are supported");

      len += mac_type_length(pass->alg);
      i++;
    }

    BABEL_IFACE->mac_num_keys = i;
    BABEL_IFACE->mac_total_len = len;
  }

}
#line 10716 "obj/conf/cf-parse.tab.c"
    break;

  case 774: /* babel_iface_item: PORT expr  */
#line 132 "proto/babel/config.Y"
             { BABEL_IFACE->port = (yyvsp[0].i); if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>65535)) cf_error("Invalid port number"); }
#line 10722 "obj/conf/cf-parse.tab.c"
    break;

  case 775: /* babel_iface_item: RXCOST expr  */
#line 133 "proto/babel/config.Y"
               { BABEL_IFACE->rxcost = (yyvsp[0].i); if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>65535)) cf_error("Invalid rxcost"); }
#line 10728 "obj/conf/cf-parse.tab.c"
    break;

  case 776: /* babel_iface_item: LIMIT expr  */
#line 134 "proto/babel/config.Y"
              { BABEL_IFACE->limit = (yyvsp[0].i); if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>16)) cf_error("Limit must be in range 1-16"); }
#line 10734 "obj/conf/cf-parse.tab.c"
    break;

  case 777: /* babel_iface_item: TYPE WIRED  */
#line 135 "proto/babel/config.Y"
              { BABEL_IFACE->type = BABEL_IFACE_TYPE_WIRED; }
#line 10740 "obj/conf/cf-parse.tab.c"
    break;

  case 778: /* babel_iface_item: TYPE WIRELESS  */
#line 136 "proto/babel/config.Y"
                 { BABEL_IFACE->type = BABEL_IFACE_TYPE_WIRELESS; }
#line 10746 "obj/conf/cf-parse.tab.c"
    break;

  case 779: /* babel_iface_item: HELLO INTERVAL expr_us  */
#line 137 "proto/babel/config.Y"
                          { BABEL_IFACE->hello_interval = (yyvsp[0].time); if (((yyvsp[0].time)<BABEL_MIN_INTERVAL) || ((yyvsp[0].time)>BABEL_MAX_INTERVAL)) cf_error("Hello interval must be in range 10 ms - 655 s"); }
#line 10752 "obj/conf/cf-parse.tab.c"
    break;

  case 780: /* babel_iface_item: UPDATE INTERVAL expr_us  */
#line 138 "proto/babel/config.Y"
                           { BABEL_IFACE->update_interval = (yyvsp[0].time); if (((yyvsp[0].time)<BABEL_MIN_INTERVAL) || ((yyvsp[0].time)>BABEL_MAX_INTERVAL)) cf_error("Update interval must be in range 10 ms - 655 s"); }
#line 10758 "obj/conf/cf-parse.tab.c"
    break;

  case 781: /* babel_iface_item: RX BUFFER expr  */
#line 139 "proto/babel/config.Y"
                  { BABEL_IFACE->rx_buffer = (yyvsp[0].i); if (((yyvsp[0].i)<256) || ((yyvsp[0].i)>65535)) cf_error("RX buffer must be in range 256-65535"); }
#line 10764 "obj/conf/cf-parse.tab.c"
    break;

  case 782: /* babel_iface_item: TX LENGTH expr  */
#line 140 "proto/babel/config.Y"
                  { BABEL_IFACE->tx_length = (yyvsp[0].i); if (((yyvsp[0].i)<256) || ((yyvsp[0].i)>65535)) cf_error("TX length must be in range 256-65535"); }
#line 10770 "obj/conf/cf-parse.tab.c"
    break;

  case 783: /* babel_iface_item: TX tos  */
#line 141 "proto/babel/config.Y"
          { BABEL_IFACE->tx_tos = (yyvsp[0].i); }
#line 10776 "obj/conf/cf-parse.tab.c"
    break;

  case 784: /* babel_iface_item: TX PRIORITY expr  */
#line 142 "proto/babel/config.Y"
                    { BABEL_IFACE->tx_priority = (yyvsp[0].i); }
#line 10782 "obj/conf/cf-parse.tab.c"
    break;

  case 785: /* babel_iface_item: CHECK LINK bool  */
#line 143 "proto/babel/config.Y"
                   { BABEL_IFACE->check_link = (yyvsp[0].i); }
#line 10788 "obj/conf/cf-parse.tab.c"
    break;

  case 786: /* babel_iface_item: NEXT HOP IPV4 ipa  */
#line 144 "proto/babel/config.Y"
                     { BABEL_IFACE->next_hop_ip4 = (yyvsp[0].a); if (!ipa_is_ip4((yyvsp[0].a))) cf_error("Must be an IPv4 address"); }
#line 10794 "obj/conf/cf-parse.tab.c"
    break;

  case 787: /* babel_iface_item: NEXT HOP IPV6 ipa  */
#line 145 "proto/babel/config.Y"
                     { BABEL_IFACE->next_hop_ip6 = (yyvsp[0].a); if (!ipa_is_ip6((yyvsp[0].a))) cf_error("Must be an IPv6 address"); }
#line 10800 "obj/conf/cf-parse.tab.c"
    break;

  case 788: /* babel_iface_item: AUTHENTICATION NONE  */
#line 146 "proto/babel/config.Y"
                       { BABEL_IFACE->auth_type = BABEL_AUTH_NONE; }
#line 10806 "obj/conf/cf-parse.tab.c"
    break;

  case 789: /* babel_iface_item: AUTHENTICATION MAC  */
#line 147 "proto/babel/config.Y"
                      { BABEL_IFACE->auth_type = BABEL_AUTH_MAC; BABEL_IFACE->auth_permissive = 0; }
#line 10812 "obj/conf/cf-parse.tab.c"
    break;

  case 790: /* babel_iface_item: AUTHENTICATION MAC PERMISSIVE  */
#line 148 "proto/babel/config.Y"
                                 { BABEL_IFACE->auth_type = BABEL_AUTH_MAC; BABEL_IFACE->auth_permissive = 1; }
#line 10818 "obj/conf/cf-parse.tab.c"
    break;

  case 797: /* dynamic_attr: BABEL_METRIC  */
#line 166 "proto/babel/config.Y"
                           { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_BABEL_METRIC); }
#line 10824 "obj/conf/cf-parse.tab.c"
    break;

  case 799: /* cmd_SHOW_BABEL_INTERFACES: SHOW BABEL INTERFACES optproto opttext END  */
#line 171 "proto/babel/config.Y"
{ PROTO_WALK_CMD((yyvsp[-2].s), &proto_babel, p) babel_show_interfaces(p, (yyvsp[-1].t)); }
#line 10830 "obj/conf/cf-parse.tab.c"
    break;

  case 801: /* cmd_SHOW_BABEL_NEIGHBORS: SHOW BABEL NEIGHBORS optproto opttext END  */
#line 174 "proto/babel/config.Y"
{ PROTO_WALK_CMD((yyvsp[-2].s), &proto_babel, p) babel_show_neighbors(p, (yyvsp[-1].t)); }
#line 10836 "obj/conf/cf-parse.tab.c"
    break;

  case 803: /* cmd_SHOW_BABEL_ENTRIES: SHOW BABEL ENTRIES optproto opttext END  */
#line 177 "proto/babel/config.Y"
{ PROTO_WALK_CMD((yyvsp[-2].s), &proto_babel, p) babel_show_entries(p); }
#line 10842 "obj/conf/cf-parse.tab.c"
    break;

  case 805: /* cmd_SHOW_BABEL_ROUTES: SHOW BABEL ROUTES optproto opttext END  */
#line 180 "proto/babel/config.Y"
{ PROTO_WALK_CMD((yyvsp[-2].s), &proto_babel, p)  babel_show_routes(p); }
#line 10848 "obj/conf/cf-parse.tab.c"
    break;

  case 807: /* bgp_proto_start: proto_start BGP  */
#line 50 "proto/bgp/config.Y"
                                 {
     this_proto = proto_config_new(&proto_bgp, (yyvsp[-1].i));
     BGP_CFG->local_port = BGP_PORT;
     BGP_CFG->remote_port = BGP_PORT;
     BGP_CFG->multihop = -1;	/* undefined */
     BGP_CFG->hold_time = 240;
     BGP_CFG->initial_hold_time = 240;
     BGP_CFG->compare_path_lengths = 1;
     BGP_CFG->igp_metric = 1;
     BGP_CFG->connect_delay_time = 5;
     BGP_CFG->connect_retry_time = 120;
     BGP_CFG->error_amnesia_time = 300;
     BGP_CFG->error_delay_time_min = 60;
     BGP_CFG->error_delay_time_max = 300;
     BGP_CFG->enable_refresh = 1;
     BGP_CFG->enable_as4 = 1;
     BGP_CFG->enable_hostname = 0;
     BGP_CFG->capabilities = 2;
     BGP_CFG->interpret_communities = 1;
     BGP_CFG->allow_as_sets = 1;
     BGP_CFG->default_local_pref = 100;
     BGP_CFG->gr_mode = BGP_GR_AWARE;
     BGP_CFG->gr_time = 120;
     BGP_CFG->llgr_mode = -1;
     BGP_CFG->llgr_time = 3600;
     BGP_CFG->setkey = 1;
     BGP_CFG->local_role = BGP_ROLE_UNDEFINED;
     BGP_CFG->dynamic_name = "dynbgp";
     BGP_CFG->check_link = -1;
   }
#line 10883 "obj/conf/cf-parse.tab.c"
    break;

  case 809: /* bgp_loc_opts: bgp_loc_opts PORT expr  */
#line 84 "proto/bgp/config.Y"
                          { BGP_CFG->local_port = (yyvsp[0].i); if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>65535)) cf_error("Invalid port number"); }
#line 10889 "obj/conf/cf-parse.tab.c"
    break;

  case 810: /* bgp_loc_opts: bgp_loc_opts AS expr  */
#line 85 "proto/bgp/config.Y"
                        { BGP_CFG->local_as = (yyvsp[0].i); }
#line 10895 "obj/conf/cf-parse.tab.c"
    break;

  case 812: /* bgp_nbr_opts: bgp_nbr_opts PORT expr  */
#line 90 "proto/bgp/config.Y"
                          { BGP_CFG->remote_port = (yyvsp[0].i); if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>65535)) cf_error("Invalid port number"); }
#line 10901 "obj/conf/cf-parse.tab.c"
    break;

  case 813: /* bgp_nbr_opts: bgp_nbr_opts AS expr  */
#line 91 "proto/bgp/config.Y"
                        { BGP_CFG->remote_as = (yyvsp[0].i); }
#line 10907 "obj/conf/cf-parse.tab.c"
    break;

  case 814: /* bgp_nbr_opts: bgp_nbr_opts INTERNAL  */
#line 92 "proto/bgp/config.Y"
                         { BGP_CFG->peer_type = BGP_PT_INTERNAL; }
#line 10913 "obj/conf/cf-parse.tab.c"
    break;

  case 815: /* bgp_nbr_opts: bgp_nbr_opts EXTERNAL  */
#line 93 "proto/bgp/config.Y"
                         { BGP_CFG->peer_type = BGP_PT_EXTERNAL; }
#line 10919 "obj/conf/cf-parse.tab.c"
    break;

  case 816: /* bgp_cease_mask: bool  */
#line 98 "proto/bgp/config.Y"
        { (yyval.i) = (yyvsp[0].i) ? ~(1 << 7) : 0; }
#line 10925 "obj/conf/cf-parse.tab.c"
    break;

  case 817: /* bgp_cease_mask: '{' bgp_cease_list '}'  */
#line 99 "proto/bgp/config.Y"
                          { (yyval.i) = (yyvsp[-1].i); }
#line 10931 "obj/conf/cf-parse.tab.c"
    break;

  case 819: /* bgp_cease_list: bgp_cease_list ',' bgp_cease_flag  */
#line 104 "proto/bgp/config.Y"
                                     { (yyval.i) = (yyvsp[-2].i) | (yyvsp[0].i); }
#line 10937 "obj/conf/cf-parse.tab.c"
    break;

  case 820: /* bgp_cease_flag: CEASE  */
#line 108 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 0; }
#line 10943 "obj/conf/cf-parse.tab.c"
    break;

  case 821: /* bgp_cease_flag: PREFIX LIMIT HIT  */
#line 109 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 1; }
#line 10949 "obj/conf/cf-parse.tab.c"
    break;

  case 822: /* bgp_cease_flag: ADMINISTRATIVE SHUTDOWN  */
#line 110 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 2; }
#line 10955 "obj/conf/cf-parse.tab.c"
    break;

  case 823: /* bgp_cease_flag: PEER DECONFIGURED  */
#line 111 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 3; }
#line 10961 "obj/conf/cf-parse.tab.c"
    break;

  case 824: /* bgp_cease_flag: ADMINISTRATIVE RESET  */
#line 112 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 4; }
#line 10967 "obj/conf/cf-parse.tab.c"
    break;

  case 825: /* bgp_cease_flag: CONNECTION REJECTED  */
#line 113 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 5; }
#line 10973 "obj/conf/cf-parse.tab.c"
    break;

  case 826: /* bgp_cease_flag: CONFIGURATION CHANGE  */
#line 114 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 6; }
#line 10979 "obj/conf/cf-parse.tab.c"
    break;

  case 827: /* bgp_cease_flag: CONNECTION COLLISION  */
#line 115 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 7; }
#line 10985 "obj/conf/cf-parse.tab.c"
    break;

  case 828: /* bgp_cease_flag: OUT OF RESOURCES  */
#line 116 "proto/bgp/config.Y"
                                { (yyval.i) = 1 << 8; }
#line 10991 "obj/conf/cf-parse.tab.c"
    break;

  case 829: /* bgp_role_name: PEER  */
#line 120 "proto/bgp/config.Y"
             { (yyval.i) = BGP_ROLE_PEER; }
#line 10997 "obj/conf/cf-parse.tab.c"
    break;

  case 830: /* bgp_role_name: PROVIDER  */
#line 121 "proto/bgp/config.Y"
             { (yyval.i) = BGP_ROLE_PROVIDER; }
#line 11003 "obj/conf/cf-parse.tab.c"
    break;

  case 831: /* bgp_role_name: CUSTOMER  */
#line 122 "proto/bgp/config.Y"
             { (yyval.i) = BGP_ROLE_CUSTOMER; }
#line 11009 "obj/conf/cf-parse.tab.c"
    break;

  case 832: /* bgp_role_name: RS_SERVER  */
#line 123 "proto/bgp/config.Y"
             { (yyval.i) = BGP_ROLE_RS_SERVER; }
#line 11015 "obj/conf/cf-parse.tab.c"
    break;

  case 833: /* bgp_role_name: RS_CLIENT  */
#line 124 "proto/bgp/config.Y"
             { (yyval.i) = BGP_ROLE_RS_CLIENT; }
#line 11021 "obj/conf/cf-parse.tab.c"
    break;

  case 838: /* bgp_proto: bgp_proto LOCAL ipa ipa_scope bgp_loc_opts ';'  */
#line 132 "proto/bgp/config.Y"
                                                  {
     BGP_CFG->local_ip = (yyvsp[-3].a);
     if ((yyvsp[-2].iface)) BGP_CFG->iface = (yyvsp[-2].iface);
   }
#line 11030 "obj/conf/cf-parse.tab.c"
    break;

  case 840: /* bgp_proto: bgp_proto NEIGHBOR ipa ipa_scope bgp_nbr_opts ';'  */
#line 137 "proto/bgp/config.Y"
                                                     {
     if (ipa_nonzero(BGP_CFG->remote_ip) || BGP_CFG->remote_range)
       cf_error("Only one neighbor per BGP instance is allowed");
     BGP_CFG->remote_ip = (yyvsp[-3].a);
     if ((yyvsp[-2].iface)) BGP_CFG->iface = (yyvsp[-2].iface);
   }
#line 11041 "obj/conf/cf-parse.tab.c"
    break;

  case 841: /* bgp_proto: bgp_proto NEIGHBOR RANGE net_ip bgp_nbr_opts ';'  */
#line 143 "proto/bgp/config.Y"
                                                    {
     if (ipa_nonzero(BGP_CFG->remote_ip) || BGP_CFG->remote_range)
       cf_error("Only one neighbor per BGP instance is allowed");
     net_addr *n = cfg_alloc((yyvsp[-2].net).length);
     net_copy(n, &((yyvsp[-2].net)));
     BGP_CFG->remote_range = n;
   }
#line 11053 "obj/conf/cf-parse.tab.c"
    break;

  case 842: /* bgp_proto: bgp_proto INTERFACE TEXT ';'  */
#line 150 "proto/bgp/config.Y"
                                { BGP_CFG->iface = if_get_by_name((yyvsp[-1].t)); }
#line 11059 "obj/conf/cf-parse.tab.c"
    break;

  case 843: /* bgp_proto: bgp_proto RR CLUSTER ID idval ';'  */
#line 151 "proto/bgp/config.Y"
                                     { BGP_CFG->rr_cluster_id = (yyvsp[-1].i32); }
#line 11065 "obj/conf/cf-parse.tab.c"
    break;

  case 844: /* bgp_proto: bgp_proto RR CLIENT bool ';'  */
#line 152 "proto/bgp/config.Y"
                                { BGP_CFG->rr_client = (yyvsp[-1].i); }
#line 11071 "obj/conf/cf-parse.tab.c"
    break;

  case 845: /* bgp_proto: bgp_proto RS CLIENT bool ';'  */
#line 153 "proto/bgp/config.Y"
                                { BGP_CFG->rs_client = (yyvsp[-1].i); }
#line 11077 "obj/conf/cf-parse.tab.c"
    break;

  case 846: /* bgp_proto: bgp_proto CONFEDERATION expr ';'  */
#line 154 "proto/bgp/config.Y"
                                    { BGP_CFG->confederation = (yyvsp[-1].i); }
#line 11083 "obj/conf/cf-parse.tab.c"
    break;

  case 847: /* bgp_proto: bgp_proto CONFEDERATION MEMBER bool ';'  */
#line 155 "proto/bgp/config.Y"
                                           { BGP_CFG->confederation_member = (yyvsp[-1].i); }
#line 11089 "obj/conf/cf-parse.tab.c"
    break;

  case 848: /* bgp_proto: bgp_proto HOLD TIME expr ';'  */
#line 156 "proto/bgp/config.Y"
                                { BGP_CFG->hold_time = (yyvsp[-1].i); if (((yyvsp[-1].i) && (yyvsp[-1].i)<3) || ((yyvsp[-1].i)>65535)) cf_error("Hold time must be in range 3-65535 or zero"); }
#line 11095 "obj/conf/cf-parse.tab.c"
    break;

  case 849: /* bgp_proto: bgp_proto MIN HOLD TIME expr ';'  */
#line 157 "proto/bgp/config.Y"
                                    { BGP_CFG->min_hold_time = (yyvsp[-1].i); }
#line 11101 "obj/conf/cf-parse.tab.c"
    break;

  case 850: /* bgp_proto: bgp_proto STARTUP HOLD TIME expr ';'  */
#line 158 "proto/bgp/config.Y"
                                        { BGP_CFG->initial_hold_time = (yyvsp[-1].i); }
#line 11107 "obj/conf/cf-parse.tab.c"
    break;

  case 851: /* bgp_proto: bgp_proto DIRECT ';'  */
#line 159 "proto/bgp/config.Y"
                        { BGP_CFG->multihop = 0; }
#line 11113 "obj/conf/cf-parse.tab.c"
    break;

  case 852: /* bgp_proto: bgp_proto MULTIHOP ';'  */
#line 160 "proto/bgp/config.Y"
                          { BGP_CFG->multihop = 64; }
#line 11119 "obj/conf/cf-parse.tab.c"
    break;

  case 853: /* bgp_proto: bgp_proto MULTIHOP expr ';'  */
#line 161 "proto/bgp/config.Y"
                               { BGP_CFG->multihop = (yyvsp[-1].i); if (((yyvsp[-1].i)<1) || ((yyvsp[-1].i)>255)) cf_error("Multihop must be in range 1-255"); }
#line 11125 "obj/conf/cf-parse.tab.c"
    break;

  case 854: /* bgp_proto: bgp_proto DYNAMIC NAME text ';'  */
#line 162 "proto/bgp/config.Y"
                                   {
     if (strchr((yyvsp[-1].t), '%')) cf_error("Forbidden character '%%' in dynamic name");
     if (strlen((yyvsp[-1].t)) > (SYM_MAX_LEN - 16)) cf_error("Dynamic name too long");
     BGP_CFG->dynamic_name = (yyvsp[-1].t);
   }
#line 11135 "obj/conf/cf-parse.tab.c"
    break;

  case 855: /* bgp_proto: bgp_proto DYNAMIC NAME DIGITS expr ';'  */
#line 167 "proto/bgp/config.Y"
                                          { BGP_CFG->dynamic_name_digits = (yyvsp[-1].i); if ((yyvsp[-1].i)>10) cf_error("Dynamic name digits must be at most 10"); }
#line 11141 "obj/conf/cf-parse.tab.c"
    break;

  case 856: /* bgp_proto: bgp_proto STRICT BIND bool ';'  */
#line 168 "proto/bgp/config.Y"
                                  { BGP_CFG->strict_bind = (yyvsp[-1].i); }
#line 11147 "obj/conf/cf-parse.tab.c"
    break;

  case 857: /* bgp_proto: bgp_proto FREE BIND bool ';'  */
#line 169 "proto/bgp/config.Y"
                                { BGP_CFG->free_bind = (yyvsp[-1].i); }
#line 11153 "obj/conf/cf-parse.tab.c"
    break;

  case 858: /* bgp_proto: bgp_proto PATH METRIC bool ';'  */
#line 170 "proto/bgp/config.Y"
                                  { BGP_CFG->compare_path_lengths = (yyvsp[-1].i); }
#line 11159 "obj/conf/cf-parse.tab.c"
    break;

  case 859: /* bgp_proto: bgp_proto MED METRIC bool ';'  */
#line 171 "proto/bgp/config.Y"
                                 { BGP_CFG->med_metric = (yyvsp[-1].i); }
#line 11165 "obj/conf/cf-parse.tab.c"
    break;

  case 860: /* bgp_proto: bgp_proto IGP METRIC bool ';'  */
#line 172 "proto/bgp/config.Y"
                                 { BGP_CFG->igp_metric = (yyvsp[-1].i); }
#line 11171 "obj/conf/cf-parse.tab.c"
    break;

  case 861: /* bgp_proto: bgp_proto PREFER OLDER bool ';'  */
#line 173 "proto/bgp/config.Y"
                                   { BGP_CFG->prefer_older = (yyvsp[-1].i); }
#line 11177 "obj/conf/cf-parse.tab.c"
    break;

  case 862: /* bgp_proto: bgp_proto DETERMINISTIC MED bool ';'  */
#line 174 "proto/bgp/config.Y"
                                        { BGP_CFG->deterministic_med = (yyvsp[-1].i); }
#line 11183 "obj/conf/cf-parse.tab.c"
    break;

  case 863: /* bgp_proto: bgp_proto DEFAULT BGP_MED expr ';'  */
#line 175 "proto/bgp/config.Y"
                                      { BGP_CFG->default_med = (yyvsp[-1].i); }
#line 11189 "obj/conf/cf-parse.tab.c"
    break;

  case 864: /* bgp_proto: bgp_proto DEFAULT BGP_LOCAL_PREF expr ';'  */
#line 176 "proto/bgp/config.Y"
                                             { BGP_CFG->default_local_pref = (yyvsp[-1].i); }
#line 11195 "obj/conf/cf-parse.tab.c"
    break;

  case 865: /* bgp_proto: bgp_proto SOURCE ADDRESS ipa ';'  */
#line 177 "proto/bgp/config.Y"
                                    { BGP_CFG->local_ip = (yyvsp[-1].a); }
#line 11201 "obj/conf/cf-parse.tab.c"
    break;

  case 866: /* bgp_proto: bgp_proto START DELAY TIME expr ';'  */
#line 178 "proto/bgp/config.Y"
                                       { BGP_CFG->connect_delay_time = (yyvsp[-1].i); log(L_WARN "%s: Start delay time option is deprecated, use connect delay time", this_proto->name); }
#line 11207 "obj/conf/cf-parse.tab.c"
    break;

  case 867: /* bgp_proto: bgp_proto CONNECT DELAY TIME expr ';'  */
#line 179 "proto/bgp/config.Y"
                                         { BGP_CFG->connect_delay_time = (yyvsp[-1].i); }
#line 11213 "obj/conf/cf-parse.tab.c"
    break;

  case 868: /* bgp_proto: bgp_proto CONNECT RETRY TIME expr ';'  */
#line 180 "proto/bgp/config.Y"
                                         { BGP_CFG->connect_retry_time = (yyvsp[-1].i); }
#line 11219 "obj/conf/cf-parse.tab.c"
    break;

  case 869: /* bgp_proto: bgp_proto KEEPALIVE TIME expr ';'  */
#line 181 "proto/bgp/config.Y"
                                     { BGP_CFG->keepalive_time = (yyvsp[-1].i); if (((yyvsp[-1].i)<1) || ((yyvsp[-1].i)>65535)) cf_error("Keepalive time must be in range 1-65535"); }
#line 11225 "obj/conf/cf-parse.tab.c"
    break;

  case 870: /* bgp_proto: bgp_proto MIN KEEPALIVE TIME expr ';'  */
#line 182 "proto/bgp/config.Y"
                                         { BGP_CFG->min_keepalive_time = (yyvsp[-1].i); }
#line 11231 "obj/conf/cf-parse.tab.c"
    break;

  case 871: /* bgp_proto: bgp_proto ERROR FORGET TIME expr ';'  */
#line 183 "proto/bgp/config.Y"
                                        { BGP_CFG->error_amnesia_time = (yyvsp[-1].i); }
#line 11237 "obj/conf/cf-parse.tab.c"
    break;

  case 872: /* bgp_proto: bgp_proto ERROR WAIT TIME expr ',' expr ';'  */
#line 184 "proto/bgp/config.Y"
                                               { BGP_CFG->error_delay_time_min = (yyvsp[-3].i); BGP_CFG->error_delay_time_max = (yyvsp[-1].i); }
#line 11243 "obj/conf/cf-parse.tab.c"
    break;

  case 873: /* bgp_proto: bgp_proto DISABLE AFTER ERROR bool ';'  */
#line 185 "proto/bgp/config.Y"
                                          { BGP_CFG->disable_after_error = (yyvsp[-1].i); }
#line 11249 "obj/conf/cf-parse.tab.c"
    break;

  case 874: /* bgp_proto: bgp_proto DISABLE AFTER CEASE bgp_cease_mask ';'  */
#line 186 "proto/bgp/config.Y"
                                                    { BGP_CFG->disable_after_cease = (yyvsp[-1].i); }
#line 11255 "obj/conf/cf-parse.tab.c"
    break;

  case 875: /* bgp_proto: bgp_proto ENABLE ROUTE REFRESH bool ';'  */
#line 187 "proto/bgp/config.Y"
                                           { BGP_CFG->enable_refresh = (yyvsp[-1].i); }
#line 11261 "obj/conf/cf-parse.tab.c"
    break;

  case 876: /* bgp_proto: bgp_proto ENABLE AS4 bool ';'  */
#line 188 "proto/bgp/config.Y"
                                 { BGP_CFG->enable_as4 = (yyvsp[-1].i); }
#line 11267 "obj/conf/cf-parse.tab.c"
    break;

  case 877: /* bgp_proto: bgp_proto ENABLE EXTENDED MESSAGES bool ';'  */
#line 189 "proto/bgp/config.Y"
                                               { BGP_CFG->enable_extended_messages = (yyvsp[-1].i); }
#line 11273 "obj/conf/cf-parse.tab.c"
    break;

  case 878: /* bgp_proto: bgp_proto ADVERTISE HOSTNAME bool ';'  */
#line 190 "proto/bgp/config.Y"
                                         { BGP_CFG->enable_hostname = (yyvsp[-1].i); }
#line 11279 "obj/conf/cf-parse.tab.c"
    break;

  case 879: /* bgp_proto: bgp_proto CAPABILITIES bool ';'  */
#line 191 "proto/bgp/config.Y"
                                   { BGP_CFG->capabilities = (yyvsp[-1].i); }
#line 11285 "obj/conf/cf-parse.tab.c"
    break;

  case 880: /* bgp_proto: bgp_proto PASSWORD text ';'  */
#line 192 "proto/bgp/config.Y"
                               { BGP_CFG->password = (yyvsp[-1].t); }
#line 11291 "obj/conf/cf-parse.tab.c"
    break;

  case 881: /* bgp_proto: bgp_proto SETKEY bool ';'  */
#line 193 "proto/bgp/config.Y"
                             { BGP_CFG->setkey = (yyvsp[-1].i); }
#line 11297 "obj/conf/cf-parse.tab.c"
    break;

  case 882: /* bgp_proto: bgp_proto PASSIVE bool ';'  */
#line 194 "proto/bgp/config.Y"
                              { BGP_CFG->passive = (yyvsp[-1].i); }
#line 11303 "obj/conf/cf-parse.tab.c"
    break;

  case 883: /* bgp_proto: bgp_proto INTERPRET COMMUNITIES bool ';'  */
#line 195 "proto/bgp/config.Y"
                                            { BGP_CFG->interpret_communities = (yyvsp[-1].i); }
#line 11309 "obj/conf/cf-parse.tab.c"
    break;

  case 884: /* bgp_proto: bgp_proto ALLOW LOCAL AS ';'  */
#line 196 "proto/bgp/config.Y"
                                { BGP_CFG->allow_local_as = -1; }
#line 11315 "obj/conf/cf-parse.tab.c"
    break;

  case 885: /* bgp_proto: bgp_proto ALLOW LOCAL AS expr ';'  */
#line 197 "proto/bgp/config.Y"
                                     { BGP_CFG->allow_local_as = (yyvsp[-1].i); }
#line 11321 "obj/conf/cf-parse.tab.c"
    break;

  case 886: /* bgp_proto: bgp_proto ALLOW BGP_LOCAL_PREF bool ';'  */
#line 198 "proto/bgp/config.Y"
                                           { BGP_CFG->allow_local_pref = (yyvsp[-1].i); }
#line 11327 "obj/conf/cf-parse.tab.c"
    break;

  case 887: /* bgp_proto: bgp_proto ALLOW AS SETS bool ';'  */
#line 199 "proto/bgp/config.Y"
                                    { BGP_CFG->allow_as_sets = (yyvsp[-1].i); }
#line 11333 "obj/conf/cf-parse.tab.c"
    break;

  case 888: /* bgp_proto: bgp_proto GRACEFUL RESTART bool ';'  */
#line 200 "proto/bgp/config.Y"
                                       { BGP_CFG->gr_mode = (yyvsp[-1].i); }
#line 11339 "obj/conf/cf-parse.tab.c"
    break;

  case 889: /* bgp_proto: bgp_proto GRACEFUL RESTART AWARE ';'  */
#line 201 "proto/bgp/config.Y"
                                        { BGP_CFG->gr_mode = BGP_GR_AWARE; }
#line 11345 "obj/conf/cf-parse.tab.c"
    break;

  case 890: /* bgp_proto: bgp_proto GRACEFUL RESTART TIME expr ';'  */
#line 202 "proto/bgp/config.Y"
                                            { BGP_CFG->gr_time = (yyvsp[-1].i); }
#line 11351 "obj/conf/cf-parse.tab.c"
    break;

  case 891: /* bgp_proto: bgp_proto LONG LIVED GRACEFUL RESTART bool ';'  */
#line 203 "proto/bgp/config.Y"
                                                  { BGP_CFG->llgr_mode = (yyvsp[-1].i); }
#line 11357 "obj/conf/cf-parse.tab.c"
    break;

  case 892: /* bgp_proto: bgp_proto LONG LIVED GRACEFUL RESTART AWARE ';'  */
#line 204 "proto/bgp/config.Y"
                                                   { BGP_CFG->llgr_mode = BGP_LLGR_AWARE; }
#line 11363 "obj/conf/cf-parse.tab.c"
    break;

  case 893: /* bgp_proto: bgp_proto LONG LIVED STALE TIME expr ';'  */
#line 205 "proto/bgp/config.Y"
                                            { BGP_CFG->llgr_time = (yyvsp[-1].i); }
#line 11369 "obj/conf/cf-parse.tab.c"
    break;

  case 894: /* bgp_proto: bgp_proto TTL SECURITY bool ';'  */
#line 206 "proto/bgp/config.Y"
                                   { BGP_CFG->ttl_security = (yyvsp[-1].i); }
#line 11375 "obj/conf/cf-parse.tab.c"
    break;

  case 895: /* bgp_proto: bgp_proto CHECK LINK bool ';'  */
#line 207 "proto/bgp/config.Y"
                                 { BGP_CFG->check_link = (yyvsp[-1].i); }
#line 11381 "obj/conf/cf-parse.tab.c"
    break;

  case 896: /* bgp_proto: bgp_proto BFD bool ';'  */
#line 208 "proto/bgp/config.Y"
                          { if ((yyvsp[-1].i)) init_bfd_opts(&BGP_CFG->bfd); else BGP_CFG->bfd = NULL; }
#line 11387 "obj/conf/cf-parse.tab.c"
    break;

  case 897: /* bgp_proto: bgp_proto BFD GRACEFUL ';'  */
#line 209 "proto/bgp/config.Y"
                              { init_bfd_opts(&BGP_CFG->bfd); BGP_CFG->bfd->mode = BGP_BFD_GRACEFUL; }
#line 11393 "obj/conf/cf-parse.tab.c"
    break;

  case 898: /* $@9: %empty  */
#line 210 "proto/bgp/config.Y"
                 { open_bfd_opts(&BGP_CFG->bfd); }
#line 11399 "obj/conf/cf-parse.tab.c"
    break;

  case 899: /* $@10: %empty  */
#line 210 "proto/bgp/config.Y"
                                                            { close_bfd_opts(); }
#line 11405 "obj/conf/cf-parse.tab.c"
    break;

  case 901: /* bgp_proto: bgp_proto ENFORCE FIRST AS bool ';'  */
#line 211 "proto/bgp/config.Y"
                                       { BGP_CFG->enforce_first_as = (yyvsp[-1].i); }
#line 11411 "obj/conf/cf-parse.tab.c"
    break;

  case 902: /* bgp_proto: bgp_proto LOCAL ROLE bgp_role_name ';'  */
#line 212 "proto/bgp/config.Y"
                                          { BGP_CFG->local_role = (yyvsp[-1].i); }
#line 11417 "obj/conf/cf-parse.tab.c"
    break;

  case 903: /* bgp_proto: bgp_proto REQUIRE ROLES bool ';'  */
#line 213 "proto/bgp/config.Y"
                                    { BGP_CFG->require_roles = (yyvsp[-1].i); }
#line 11423 "obj/conf/cf-parse.tab.c"
    break;

  case 904: /* bgp_afi: IPV4  */
#line 217 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_IPV4; }
#line 11429 "obj/conf/cf-parse.tab.c"
    break;

  case 905: /* bgp_afi: IPV6  */
#line 218 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_IPV6; }
#line 11435 "obj/conf/cf-parse.tab.c"
    break;

  case 906: /* bgp_afi: IPV4 MULTICAST  */
#line 219 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_IPV4_MC; }
#line 11441 "obj/conf/cf-parse.tab.c"
    break;

  case 907: /* bgp_afi: IPV6 MULTICAST  */
#line 220 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_IPV6_MC; }
#line 11447 "obj/conf/cf-parse.tab.c"
    break;

  case 908: /* bgp_afi: IPV4 MPLS  */
#line 221 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_IPV4_MPLS; }
#line 11453 "obj/conf/cf-parse.tab.c"
    break;

  case 909: /* bgp_afi: IPV6 MPLS  */
#line 222 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_IPV6_MPLS; }
#line 11459 "obj/conf/cf-parse.tab.c"
    break;

  case 910: /* bgp_afi: VPN4 MPLS  */
#line 223 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_VPN4_MPLS; }
#line 11465 "obj/conf/cf-parse.tab.c"
    break;

  case 911: /* bgp_afi: VPN6 MPLS  */
#line 224 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_VPN6_MPLS; }
#line 11471 "obj/conf/cf-parse.tab.c"
    break;

  case 912: /* bgp_afi: VPN4 MULTICAST  */
#line 225 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_VPN4_MC; }
#line 11477 "obj/conf/cf-parse.tab.c"
    break;

  case 913: /* bgp_afi: VPN6 MULTICAST  */
#line 226 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_VPN6_MC; }
#line 11483 "obj/conf/cf-parse.tab.c"
    break;

  case 914: /* bgp_afi: FLOW4  */
#line 227 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_FLOW4; }
#line 11489 "obj/conf/cf-parse.tab.c"
    break;

  case 915: /* bgp_afi: FLOW6  */
#line 228 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_FLOW6; }
#line 11495 "obj/conf/cf-parse.tab.c"
    break;

  case 916: /* bgp_afi: RPDP4  */
#line 229 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_RPDP4; }
#line 11501 "obj/conf/cf-parse.tab.c"
    break;

  case 917: /* bgp_afi: RPDP6  */
#line 230 "proto/bgp/config.Y"
                        { (yyval.i32) = BGP_AF_RPDP6; }
#line 11507 "obj/conf/cf-parse.tab.c"
    break;

  case 918: /* bgp_channel_start: bgp_afi  */
#line 234 "proto/bgp/config.Y"
{
  const struct bgp_af_desc *desc = bgp_get_af_desc((yyvsp[0].i32));

  if (!desc)
    cf_error("Unknown AFI/SAFI");

  this_channel = channel_config_get(&channel_bgp, desc->name, desc->net, this_proto);

  /* New channel */
  if (!BGP_CC->desc)
  {
    BGP_CC->c.in_filter = FILTER_UNDEF;
    BGP_CC->c.out_filter = FILTER_UNDEF;
    BGP_CC->c.ra_mode = RA_UNDEF;
    BGP_CC->afi = (yyvsp[0].i32);
    BGP_CC->desc = desc;
    BGP_CC->next_hop_keep = 0xff; /* undefined */
    BGP_CC->gr_able = 0xff;	/* undefined */
    BGP_CC->llgr_able = 0xff;	/* undefined */
    BGP_CC->llgr_time = ~0U;	/* undefined */
    BGP_CC->aigp = 0xff;	/* undefined */
  }
}
#line 11535 "obj/conf/cf-parse.tab.c"
    break;

  case 919: /* bgp_nh: bool  */
#line 259 "proto/bgp/config.Y"
        { (yyval.i) = (yyvsp[0].i); }
#line 11541 "obj/conf/cf-parse.tab.c"
    break;

  case 920: /* bgp_nh: IBGP  */
#line 260 "proto/bgp/config.Y"
        { (yyval.i) = NH_IBGP; }
#line 11547 "obj/conf/cf-parse.tab.c"
    break;

  case 921: /* bgp_nh: EBGP  */
#line 261 "proto/bgp/config.Y"
        { (yyval.i) = NH_EBGP; }
#line 11553 "obj/conf/cf-parse.tab.c"
    break;

  case 926: /* bgp_channel_item: NEXT HOP ADDRESS ipa  */
#line 267 "proto/bgp/config.Y"
                        { BGP_CC->next_hop_addr = (yyvsp[0].a); }
#line 11559 "obj/conf/cf-parse.tab.c"
    break;

  case 927: /* bgp_channel_item: NEXT HOP SELF bgp_nh  */
#line 268 "proto/bgp/config.Y"
                        { BGP_CC->next_hop_self = (yyvsp[0].i); }
#line 11565 "obj/conf/cf-parse.tab.c"
    break;

  case 928: /* bgp_channel_item: NEXT HOP KEEP bgp_nh  */
#line 269 "proto/bgp/config.Y"
                        { BGP_CC->next_hop_keep = (yyvsp[0].i); }
#line 11571 "obj/conf/cf-parse.tab.c"
    break;

  case 929: /* bgp_channel_item: NEXT HOP PREFER GLOBAL  */
#line 270 "proto/bgp/config.Y"
                          { BGP_CC->next_hop_prefer = NHP_GLOBAL; }
#line 11577 "obj/conf/cf-parse.tab.c"
    break;

  case 930: /* bgp_channel_item: MANDATORY bool  */
#line 271 "proto/bgp/config.Y"
                  { BGP_CC->mandatory = (yyvsp[0].i); }
#line 11583 "obj/conf/cf-parse.tab.c"
    break;

  case 931: /* bgp_channel_item: MISSING LLADDR bgp_lladdr  */
#line 272 "proto/bgp/config.Y"
                             { log(L_WARN "%s.%s: Missing lladdr option is deprecated and ignored, remove it", this_proto->name, this_channel->name); }
#line 11589 "obj/conf/cf-parse.tab.c"
    break;

  case 932: /* bgp_channel_item: GATEWAY DIRECT  */
#line 273 "proto/bgp/config.Y"
                  { BGP_CC->gw_mode = GW_DIRECT; }
#line 11595 "obj/conf/cf-parse.tab.c"
    break;

  case 933: /* bgp_channel_item: GATEWAY RECURSIVE  */
#line 274 "proto/bgp/config.Y"
                     { BGP_CC->gw_mode = GW_RECURSIVE; }
#line 11601 "obj/conf/cf-parse.tab.c"
    break;

  case 934: /* bgp_channel_item: SECONDARY bool  */
#line 275 "proto/bgp/config.Y"
                  { BGP_CC->secondary = (yyvsp[0].i); }
#line 11607 "obj/conf/cf-parse.tab.c"
    break;

  case 935: /* bgp_channel_item: VALIDATE bool  */
#line 276 "proto/bgp/config.Y"
                 {
    BGP_CC->validate = (yyvsp[0].i);
    if (BGP_SAFI(BGP_CC->afi) != BGP_SAFI_FLOW)
      cf_error("Validate option limited to flowspec channels");
   }
#line 11617 "obj/conf/cf-parse.tab.c"
    break;

  case 936: /* bgp_channel_item: GRACEFUL RESTART bool  */
#line 281 "proto/bgp/config.Y"
                         { BGP_CC->gr_able = (yyvsp[0].i); }
#line 11623 "obj/conf/cf-parse.tab.c"
    break;

  case 937: /* bgp_channel_item: LONG LIVED GRACEFUL RESTART bool  */
#line 282 "proto/bgp/config.Y"
                                    { BGP_CC->llgr_able = (yyvsp[0].i); }
#line 11629 "obj/conf/cf-parse.tab.c"
    break;

  case 938: /* bgp_channel_item: LONG LIVED STALE TIME expr  */
#line 283 "proto/bgp/config.Y"
                              { BGP_CC->llgr_time = (yyvsp[0].i); }
#line 11635 "obj/conf/cf-parse.tab.c"
    break;

  case 939: /* bgp_channel_item: EXTENDED NEXT HOP bool  */
#line 284 "proto/bgp/config.Y"
                          { BGP_CC->ext_next_hop = (yyvsp[0].i); }
#line 11641 "obj/conf/cf-parse.tab.c"
    break;

  case 940: /* bgp_channel_item: ADD PATHS RX  */
#line 285 "proto/bgp/config.Y"
                { BGP_CC->add_path = BGP_ADD_PATH_RX; }
#line 11647 "obj/conf/cf-parse.tab.c"
    break;

  case 941: /* bgp_channel_item: ADD PATHS TX  */
#line 286 "proto/bgp/config.Y"
                { BGP_CC->add_path = BGP_ADD_PATH_TX; }
#line 11653 "obj/conf/cf-parse.tab.c"
    break;

  case 942: /* bgp_channel_item: ADD PATHS bool  */
#line 287 "proto/bgp/config.Y"
                  { BGP_CC->add_path = (yyvsp[0].i) ? BGP_ADD_PATH_FULL : 0; }
#line 11659 "obj/conf/cf-parse.tab.c"
    break;

  case 943: /* bgp_channel_item: IMPORT TABLE bool  */
#line 288 "proto/bgp/config.Y"
                     { BGP_CC->import_table = (yyvsp[0].i); }
#line 11665 "obj/conf/cf-parse.tab.c"
    break;

  case 944: /* bgp_channel_item: EXPORT TABLE bool  */
#line 289 "proto/bgp/config.Y"
                     { BGP_CC->export_table = (yyvsp[0].i); }
#line 11671 "obj/conf/cf-parse.tab.c"
    break;

  case 945: /* bgp_channel_item: AIGP bool  */
#line 290 "proto/bgp/config.Y"
             { BGP_CC->aigp = (yyvsp[0].i); BGP_CC->aigp_originate = 0; }
#line 11677 "obj/conf/cf-parse.tab.c"
    break;

  case 946: /* bgp_channel_item: AIGP ORIGINATE  */
#line 291 "proto/bgp/config.Y"
                  { BGP_CC->aigp = 1; BGP_CC->aigp_originate = 1; }
#line 11683 "obj/conf/cf-parse.tab.c"
    break;

  case 947: /* bgp_channel_item: COST expr  */
#line 292 "proto/bgp/config.Y"
             { BGP_CC->cost = (yyvsp[0].i); if ((yyvsp[0].i) < 1) cf_error("Cost must be positive"); }
#line 11689 "obj/conf/cf-parse.tab.c"
    break;

  case 948: /* bgp_channel_item: IGP TABLE rtable  */
#line 293 "proto/bgp/config.Y"
                    {
    if (BGP_CC->desc->no_igp)
      cf_error("IGP table not allowed here");

    if ((yyvsp[0].r)->addr_type == NET_IP4)
      BGP_CC->igp_table_ip4 = (yyvsp[0].r);
    else if ((yyvsp[0].r)->addr_type == NET_IP6)
      BGP_CC->igp_table_ip6 = (yyvsp[0].r);
    else
      cf_error("Mismatched IGP table type");
   }
#line 11705 "obj/conf/cf-parse.tab.c"
    break;

  case 949: /* bgp_channel_item: BASE TABLE rtable  */
#line 304 "proto/bgp/config.Y"
                     {
    if (BGP_SAFI(BGP_CC->afi) != BGP_SAFI_FLOW)
      cf_error("Base table option limited to flowspec channels");

    if (((BGP_CC->afi == BGP_AF_FLOW4) && ((yyvsp[0].r)->addr_type == NET_IP4)) ||
        ((BGP_CC->afi == BGP_AF_FLOW6) && ((yyvsp[0].r)->addr_type == NET_IP6)))
      BGP_CC->base_table = (yyvsp[0].r);
    else
      cf_error("Mismatched base table type");
   }
#line 11720 "obj/conf/cf-parse.tab.c"
    break;

  case 954: /* bgp_channel_end: %empty  */
#line 327 "proto/bgp/config.Y"
{
  if (!this_channel->table)
    cf_error("Routing table not specified");

  this_channel = NULL;
}
#line 11731 "obj/conf/cf-parse.tab.c"
    break;

  case 956: /* dynamic_attr: BGP_ORIGIN  */
#line 338 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_ENUM_BGP_ORIGIN, EA_CODE(PROTOCOL_BGP, BA_ORIGIN)); }
#line 11737 "obj/conf/cf-parse.tab.c"
    break;

  case 957: /* dynamic_attr: BGP_PATH  */
#line 340 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_AS_PATH, T_PATH, EA_CODE(PROTOCOL_BGP, BA_AS_PATH)); }
#line 11743 "obj/conf/cf-parse.tab.c"
    break;

  case 958: /* dynamic_attr: BGP_NEXT_HOP  */
#line 342 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_IP_ADDRESS, T_IP, EA_CODE(PROTOCOL_BGP, BA_NEXT_HOP)); }
#line 11749 "obj/conf/cf-parse.tab.c"
    break;

  case 959: /* dynamic_attr: BGP_MED  */
#line 344 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_CODE(PROTOCOL_BGP, BA_MULTI_EXIT_DISC)); }
#line 11755 "obj/conf/cf-parse.tab.c"
    break;

  case 960: /* dynamic_attr: BGP_LOCAL_PREF  */
#line 346 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_CODE(PROTOCOL_BGP, BA_LOCAL_PREF)); }
#line 11761 "obj/conf/cf-parse.tab.c"
    break;

  case 961: /* dynamic_attr: BGP_ATOMIC_AGGR  */
#line 348 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_OPAQUE, T_ENUM_EMPTY, EA_CODE(PROTOCOL_BGP, BA_ATOMIC_AGGR)); }
#line 11767 "obj/conf/cf-parse.tab.c"
    break;

  case 962: /* dynamic_attr: BGP_AGGREGATOR  */
#line 350 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_OPAQUE, T_ENUM_EMPTY, EA_CODE(PROTOCOL_BGP, BA_AGGREGATOR)); }
#line 11773 "obj/conf/cf-parse.tab.c"
    break;

  case 963: /* dynamic_attr: BGP_COMMUNITY  */
#line 352 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT_SET, T_CLIST, EA_CODE(PROTOCOL_BGP, BA_COMMUNITY)); }
#line 11779 "obj/conf/cf-parse.tab.c"
    break;

  case 964: /* dynamic_attr: BGP_ORIGINATOR_ID  */
#line 354 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_ROUTER_ID, T_QUAD, EA_CODE(PROTOCOL_BGP, BA_ORIGINATOR_ID)); }
#line 11785 "obj/conf/cf-parse.tab.c"
    break;

  case 965: /* dynamic_attr: BGP_CLUSTER_LIST  */
#line 356 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT_SET, T_CLIST, EA_CODE(PROTOCOL_BGP, BA_CLUSTER_LIST)); }
#line 11791 "obj/conf/cf-parse.tab.c"
    break;

  case 966: /* dynamic_attr: BGP_EXT_COMMUNITY  */
#line 358 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_EC_SET, T_ECLIST, EA_CODE(PROTOCOL_BGP, BA_EXT_COMMUNITY)); }
#line 11797 "obj/conf/cf-parse.tab.c"
    break;

  case 967: /* dynamic_attr: BGP_AIGP  */
#line 360 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_OPAQUE, T_ENUM_EMPTY, EA_CODE(PROTOCOL_BGP, BA_AIGP)); }
#line 11803 "obj/conf/cf-parse.tab.c"
    break;

  case 968: /* dynamic_attr: BGP_LARGE_COMMUNITY  */
#line 362 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_LC_SET, T_LCLIST, EA_CODE(PROTOCOL_BGP, BA_LARGE_COMMUNITY)); }
#line 11809 "obj/conf/cf-parse.tab.c"
    break;

  case 969: /* dynamic_attr: BGP_OTC  */
#line 364 "proto/bgp/config.Y"
        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_CODE(PROTOCOL_BGP, BA_ONLY_TO_CUSTOMER)); }
#line 11815 "obj/conf/cf-parse.tab.c"
    break;

  case 971: /* mrt_proto_start: proto_start MRT  */
#line 29 "proto/mrt/config.Y"
{
  this_proto = proto_config_new(&proto_mrt, (yyvsp[-1].i));
}
#line 11823 "obj/conf/cf-parse.tab.c"
    break;

  case 973: /* mrt_proto_item: TABLE rtable  */
#line 35 "proto/mrt/config.Y"
                        { MRT_CFG->table_cf = (yyvsp[0].r); }
#line 11829 "obj/conf/cf-parse.tab.c"
    break;

  case 974: /* mrt_proto_item: TABLE TEXT  */
#line 36 "proto/mrt/config.Y"
                        { MRT_CFG->table_expr = (yyvsp[0].t); }
#line 11835 "obj/conf/cf-parse.tab.c"
    break;

  case 975: /* mrt_proto_item: FILTER filter  */
#line 37 "proto/mrt/config.Y"
                        { MRT_CFG->filter = (yyvsp[0].f); }
#line 11841 "obj/conf/cf-parse.tab.c"
    break;

  case 976: /* mrt_proto_item: where_filter  */
#line 38 "proto/mrt/config.Y"
                        { MRT_CFG->filter = (yyvsp[0].f); }
#line 11847 "obj/conf/cf-parse.tab.c"
    break;

  case 977: /* mrt_proto_item: FILENAME text  */
#line 39 "proto/mrt/config.Y"
                        { MRT_CFG->filename = (yyvsp[0].t); }
#line 11853 "obj/conf/cf-parse.tab.c"
    break;

  case 978: /* mrt_proto_item: PERIOD expr  */
#line 40 "proto/mrt/config.Y"
                        { MRT_CFG->period = (yyvsp[0].i); }
#line 11859 "obj/conf/cf-parse.tab.c"
    break;

  case 979: /* mrt_proto_item: ALWAYS ADD PATH bool  */
#line 41 "proto/mrt/config.Y"
                        { MRT_CFG->always_add_path = (yyvsp[0].i); }
#line 11865 "obj/conf/cf-parse.tab.c"
    break;

  case 982: /* mrt_proto: mrt_proto_start proto_name '{' mrt_proto_opts '}'  */
#line 50 "proto/mrt/config.Y"
                                                     { mrt_check_config(this_proto); }
#line 11871 "obj/conf/cf-parse.tab.c"
    break;

  case 984: /* cmd_MRT_DUMP: MRT DUMP mrt_dump_args END  */
#line 54 "proto/mrt/config.Y"
{ mrt_dump_cmd((yyvsp[-1].md)); }
#line 11877 "obj/conf/cf-parse.tab.c"
    break;

  case 985: /* mrt_dump_args: %empty  */
#line 57 "proto/mrt/config.Y"
               { (yyval.md) = cfg_allocz(sizeof(struct mrt_dump_data)); }
#line 11883 "obj/conf/cf-parse.tab.c"
    break;

  case 986: /* mrt_dump_args: mrt_dump_args TABLE rtable  */
#line 58 "proto/mrt/config.Y"
                                { (yyval.md) = (yyvsp[-2].md); (yyval.md)->table_ptr = (yyvsp[0].r)->table; }
#line 11889 "obj/conf/cf-parse.tab.c"
    break;

  case 987: /* mrt_dump_args: mrt_dump_args TABLE TEXT  */
#line 59 "proto/mrt/config.Y"
                                { (yyval.md) = (yyvsp[-2].md); (yyval.md)->table_expr = (yyvsp[0].t); }
#line 11895 "obj/conf/cf-parse.tab.c"
    break;

  case 988: /* mrt_dump_args: mrt_dump_args FILTER filter  */
#line 60 "proto/mrt/config.Y"
                                { (yyval.md) = (yyvsp[-2].md); (yyval.md)->filter = (yyvsp[0].f); }
#line 11901 "obj/conf/cf-parse.tab.c"
    break;

  case 989: /* mrt_dump_args: mrt_dump_args where_filter  */
#line 61 "proto/mrt/config.Y"
                                { (yyval.md) = (yyvsp[-1].md); (yyval.md)->filter = (yyvsp[0].f); }
#line 11907 "obj/conf/cf-parse.tab.c"
    break;

  case 990: /* mrt_dump_args: mrt_dump_args TO text  */
#line 62 "proto/mrt/config.Y"
                                { (yyval.md) = (yyvsp[-2].md); (yyval.md)->filename = (yyvsp[0].t); }
#line 11913 "obj/conf/cf-parse.tab.c"
    break;

  case 991: /* proto: ospf_proto '}'  */
#line 211 "proto/ospf/config.Y"
                      { ospf_proto_finish(); }
#line 11919 "obj/conf/cf-parse.tab.c"
    break;

  case 992: /* ospf_variant: OSPF  */
#line 214 "proto/ospf/config.Y"
           { (yyval.i) = 1; }
#line 11925 "obj/conf/cf-parse.tab.c"
    break;

  case 993: /* ospf_variant: OSPF V2  */
#line 215 "proto/ospf/config.Y"
           { (yyval.i) = 1; }
#line 11931 "obj/conf/cf-parse.tab.c"
    break;

  case 994: /* ospf_variant: OSPF V3  */
#line 216 "proto/ospf/config.Y"
           { (yyval.i) = 0; }
#line 11937 "obj/conf/cf-parse.tab.c"
    break;

  case 995: /* ospf_proto_start: proto_start ospf_variant  */
#line 220 "proto/ospf/config.Y"
{
  this_proto = proto_config_new(&proto_ospf, (yyvsp[-1].i));
  this_proto->net_type = (yyvsp[0].i) ? NET_IP4 : 0;

  init_list(&OSPF_CFG->area_list);
  init_list(&OSPF_CFG->vlink_list);
  OSPF_CFG->ecmp = rt_default_ecmp;
  OSPF_CFG->tick = OSPF_DEFAULT_TICK;
  OSPF_CFG->ospf2 = (yyvsp[0].i);
  OSPF_CFG->af_ext = !(yyvsp[0].i);
  OSPF_CFG->gr_mode = OSPF_GR_AWARE;
  OSPF_CFG->gr_time = OSPF_DEFAULT_GR_TIME;
}
#line 11955 "obj/conf/cf-parse.tab.c"
    break;

  case 998: /* ospf_af_mc: %empty  */
#line 240 "proto/ospf/config.Y"
             { (yyval.i) = 0; }
#line 11961 "obj/conf/cf-parse.tab.c"
    break;

  case 999: /* ospf_af_mc: MULTICAST  */
#line 241 "proto/ospf/config.Y"
             { (yyval.i) = 1; }
#line 11967 "obj/conf/cf-parse.tab.c"
    break;

  case 1000: /* ospf_channel_start: net_type ospf_af_mc  */
#line 246 "proto/ospf/config.Y"
{
  /* TODO: change name for multicast channels */
  (yyval.cc) = this_channel = channel_config_get(NULL, net_label[(yyvsp[-1].i)], (yyvsp[-1].i), this_proto);

  /* Save the multicast flag */
  OSPF_CFG->af_mc = (yyvsp[0].i);
}
#line 11979 "obj/conf/cf-parse.tab.c"
    break;

  case 1003: /* ospf_proto_item: ospf_channel  */
#line 258 "proto/ospf/config.Y"
                { this_proto->net_type = (yyvsp[0].cc)->net_type; }
#line 11985 "obj/conf/cf-parse.tab.c"
    break;

  case 1004: /* ospf_proto_item: RFC1583COMPAT bool  */
#line 259 "proto/ospf/config.Y"
                      { OSPF_CFG->rfc1583 = (yyvsp[0].i); }
#line 11991 "obj/conf/cf-parse.tab.c"
    break;

  case 1005: /* ospf_proto_item: RFC5838 bool  */
#line 260 "proto/ospf/config.Y"
                { OSPF_CFG->af_ext = (yyvsp[0].i); if (!ospf_cfg_is_v3()) cf_error("RFC5838 option requires OSPFv3"); }
#line 11997 "obj/conf/cf-parse.tab.c"
    break;

  case 1006: /* ospf_proto_item: VPN PE bool  */
#line 261 "proto/ospf/config.Y"
               { OSPF_CFG->vpn_pe = (yyvsp[0].i); }
#line 12003 "obj/conf/cf-parse.tab.c"
    break;

  case 1007: /* ospf_proto_item: STUB ROUTER bool  */
#line 262 "proto/ospf/config.Y"
                    { OSPF_CFG->stub_router = (yyvsp[0].i); }
#line 12009 "obj/conf/cf-parse.tab.c"
    break;

  case 1008: /* ospf_proto_item: GRACEFUL RESTART bool  */
#line 263 "proto/ospf/config.Y"
                         { OSPF_CFG->gr_mode = (yyvsp[0].i); }
#line 12015 "obj/conf/cf-parse.tab.c"
    break;

  case 1009: /* ospf_proto_item: GRACEFUL RESTART AWARE  */
#line 264 "proto/ospf/config.Y"
                          { OSPF_CFG->gr_mode = OSPF_GR_AWARE; }
#line 12021 "obj/conf/cf-parse.tab.c"
    break;

  case 1010: /* ospf_proto_item: GRACEFUL RESTART TIME expr  */
#line 265 "proto/ospf/config.Y"
                              { OSPF_CFG->gr_time = (yyvsp[0].i); if (((yyvsp[0].i) < 1) || ((yyvsp[0].i) > 1800)) cf_error("Graceful restart time must be in range 1-1800"); }
#line 12027 "obj/conf/cf-parse.tab.c"
    break;

  case 1011: /* ospf_proto_item: ECMP bool  */
#line 266 "proto/ospf/config.Y"
             { OSPF_CFG->ecmp = (yyvsp[0].i) ? OSPF_DEFAULT_ECMP_LIMIT : 0; }
#line 12033 "obj/conf/cf-parse.tab.c"
    break;

  case 1012: /* ospf_proto_item: ECMP bool LIMIT expr  */
#line 267 "proto/ospf/config.Y"
                        { OSPF_CFG->ecmp = (yyvsp[-2].i) ? (yyvsp[0].i) : 0; }
#line 12039 "obj/conf/cf-parse.tab.c"
    break;

  case 1013: /* ospf_proto_item: MERGE EXTERNAL bool  */
#line 268 "proto/ospf/config.Y"
                       { OSPF_CFG->merge_external = (yyvsp[0].i); }
#line 12045 "obj/conf/cf-parse.tab.c"
    break;

  case 1014: /* ospf_proto_item: TICK expr  */
#line 269 "proto/ospf/config.Y"
             { OSPF_CFG->tick = (yyvsp[0].i); if((yyvsp[0].i) <= 0) cf_error("Tick must be greater than zero"); }
#line 12051 "obj/conf/cf-parse.tab.c"
    break;

  case 1015: /* ospf_proto_item: INSTANCE ID expr  */
#line 270 "proto/ospf/config.Y"
                    { OSPF_CFG->instance_id = (yyvsp[0].i); OSPF_CFG->instance_id_set = 1; if ((yyvsp[0].i) > 255) cf_error("Instance ID must be in range 0-255"); }
#line 12057 "obj/conf/cf-parse.tab.c"
    break;

  case 1017: /* ospf_area_start: AREA idval  */
#line 274 "proto/ospf/config.Y"
                            {
  this_area = cfg_allocz(sizeof(struct ospf_area_config));
  add_tail(&OSPF_CFG->area_list, NODE this_area);
  this_area->areaid = (yyvsp[0].i32);
  this_area->default_cost = OSPF_DEFAULT_STUB_COST;
  this_area->type = OPT_E;
  this_area->transint = OSPF_DEFAULT_TRANSINT;

  init_list(&this_area->patt_list);
  init_list(&this_area->net_list);
  init_list(&this_area->enet_list);
  init_list(&this_area->stubnet_list);
 }
#line 12075 "obj/conf/cf-parse.tab.c"
    break;

  case 1018: /* ospf_area: ospf_area_start '{' ospf_area_opts '}'  */
#line 289 "proto/ospf/config.Y"
                                                  { ospf_area_finish(); }
#line 12081 "obj/conf/cf-parse.tab.c"
    break;

  case 1021: /* ospf_area_item: STUB bool  */
#line 298 "proto/ospf/config.Y"
             { this_area->type = (yyvsp[0].i) ? 0 : OPT_E; /* We should remove the option */ }
#line 12087 "obj/conf/cf-parse.tab.c"
    break;

  case 1022: /* ospf_area_item: NSSA  */
#line 299 "proto/ospf/config.Y"
        { this_area->type = OPT_N; }
#line 12093 "obj/conf/cf-parse.tab.c"
    break;

  case 1023: /* ospf_area_item: SUMMARY bool  */
#line 300 "proto/ospf/config.Y"
                { this_area->summary = (yyvsp[0].i); }
#line 12099 "obj/conf/cf-parse.tab.c"
    break;

  case 1024: /* ospf_area_item: DEFAULT NSSA bool  */
#line 301 "proto/ospf/config.Y"
                     { this_area->default_nssa = (yyvsp[0].i); }
#line 12105 "obj/conf/cf-parse.tab.c"
    break;

  case 1025: /* ospf_area_item: DEFAULT COST expr  */
#line 302 "proto/ospf/config.Y"
                     { this_area->default_cost = (yyvsp[0].i); ospf_check_defcost((yyvsp[0].i)); }
#line 12111 "obj/conf/cf-parse.tab.c"
    break;

  case 1026: /* ospf_area_item: DEFAULT COST2 expr  */
#line 303 "proto/ospf/config.Y"
                      { this_area->default_cost = (yyvsp[0].i) | LSA_EXT3_EBIT; ospf_check_defcost((yyvsp[0].i)); }
#line 12117 "obj/conf/cf-parse.tab.c"
    break;

  case 1027: /* ospf_area_item: STUB COST expr  */
#line 304 "proto/ospf/config.Y"
                  { this_area->default_cost = (yyvsp[0].i); ospf_check_defcost((yyvsp[0].i)); }
#line 12123 "obj/conf/cf-parse.tab.c"
    break;

  case 1028: /* ospf_area_item: TRANSLATOR bool  */
#line 305 "proto/ospf/config.Y"
                   { this_area->translator = (yyvsp[0].i); }
#line 12129 "obj/conf/cf-parse.tab.c"
    break;

  case 1029: /* ospf_area_item: TRANSLATOR STABILITY expr  */
#line 306 "proto/ospf/config.Y"
                             { this_area->transint = (yyvsp[0].i); }
#line 12135 "obj/conf/cf-parse.tab.c"
    break;

  case 1030: /* $@11: %empty  */
#line 307 "proto/ospf/config.Y"
            { this_nets = &this_area->net_list; }
#line 12141 "obj/conf/cf-parse.tab.c"
    break;

  case 1032: /* $@12: %empty  */
#line 308 "proto/ospf/config.Y"
            { this_nets = &this_area->enet_list; }
#line 12147 "obj/conf/cf-parse.tab.c"
    break;

  case 1039: /* ospf_stubnet_start: net_ip  */
#line 320 "proto/ospf/config.Y"
          {
     this_stubnet = cfg_allocz(sizeof(struct ospf_stubnet_config));
     add_tail(&this_area->stubnet_list, NODE this_stubnet);
     this_stubnet->prefix = (yyvsp[0].net);
     this_stubnet->cost = COST_D;
   }
#line 12158 "obj/conf/cf-parse.tab.c"
    break;

  case 1042: /* ospf_stubnet_item: HIDDEN bool  */
#line 334 "proto/ospf/config.Y"
               { this_stubnet->hidden = (yyvsp[0].i); }
#line 12164 "obj/conf/cf-parse.tab.c"
    break;

  case 1043: /* ospf_stubnet_item: SUMMARY bool  */
#line 335 "proto/ospf/config.Y"
                { this_stubnet->summary = (yyvsp[0].i); }
#line 12170 "obj/conf/cf-parse.tab.c"
    break;

  case 1044: /* ospf_stubnet_item: COST expr  */
#line 336 "proto/ospf/config.Y"
             { this_stubnet->cost = (yyvsp[0].i); }
#line 12176 "obj/conf/cf-parse.tab.c"
    break;

  case 1045: /* ospf_vlink: ospf_vlink_start ospf_instance_id '{' ospf_vlink_opts '}'  */
#line 340 "proto/ospf/config.Y"
                                                             { ospf_iface_finish(); }
#line 12182 "obj/conf/cf-parse.tab.c"
    break;

  case 1046: /* ospf_vlink: ospf_vlink_start ospf_instance_id  */
#line 341 "proto/ospf/config.Y"
                                     { ospf_iface_finish(); }
#line 12188 "obj/conf/cf-parse.tab.c"
    break;

  case 1050: /* ospf_vlink_item: HELLO expr  */
#line 350 "proto/ospf/config.Y"
              { OSPF_PATT->helloint = (yyvsp[0].i) ; if (((yyvsp[0].i)<=0) || ((yyvsp[0].i)>65535)) cf_error("Hello interval must be in range 1-65535"); }
#line 12194 "obj/conf/cf-parse.tab.c"
    break;

  case 1051: /* ospf_vlink_item: RETRANSMIT expr  */
#line 351 "proto/ospf/config.Y"
                   { OSPF_PATT->rxmtint = (yyvsp[0].i) ; if ((yyvsp[0].i)<=1) cf_error("Retransmit int must be greater than one"); }
#line 12200 "obj/conf/cf-parse.tab.c"
    break;

  case 1052: /* ospf_vlink_item: TRANSMIT DELAY expr  */
#line 352 "proto/ospf/config.Y"
                       { OSPF_PATT->inftransdelay = (yyvsp[0].i) ; if (((yyvsp[0].i)<=0) || ((yyvsp[0].i)>65535)) cf_error("Transmit delay must be in range 1-65535"); }
#line 12206 "obj/conf/cf-parse.tab.c"
    break;

  case 1053: /* ospf_vlink_item: WAIT expr  */
#line 353 "proto/ospf/config.Y"
             { OSPF_PATT->waitint = (yyvsp[0].i) ; if ((yyvsp[0].i)<=1) cf_error("Wait interval must be greater than one"); }
#line 12212 "obj/conf/cf-parse.tab.c"
    break;

  case 1054: /* ospf_vlink_item: DEAD expr  */
#line 354 "proto/ospf/config.Y"
             { OSPF_PATT->deadint = (yyvsp[0].i) ; if ((yyvsp[0].i)<=1) cf_error("Dead interval must be greater than one"); }
#line 12218 "obj/conf/cf-parse.tab.c"
    break;

  case 1055: /* ospf_vlink_item: DEAD COUNT expr  */
#line 355 "proto/ospf/config.Y"
                   { OSPF_PATT->deadc = (yyvsp[0].i) ; if ((yyvsp[0].i)<=1) cf_error("Dead count must be greater than one"); }
#line 12224 "obj/conf/cf-parse.tab.c"
    break;

  case 1056: /* ospf_vlink_item: AUTHENTICATION NONE  */
#line 356 "proto/ospf/config.Y"
                       { OSPF_PATT->autype = OSPF_AUTH_NONE;  }
#line 12230 "obj/conf/cf-parse.tab.c"
    break;

  case 1057: /* ospf_vlink_item: AUTHENTICATION SIMPLE  */
#line 357 "proto/ospf/config.Y"
                         { OSPF_PATT->autype = OSPF_AUTH_SIMPLE; ospf_check_auth(); }
#line 12236 "obj/conf/cf-parse.tab.c"
    break;

  case 1058: /* ospf_vlink_item: AUTHENTICATION CRYPTOGRAPHIC  */
#line 358 "proto/ospf/config.Y"
                                { OSPF_PATT->autype = OSPF_AUTH_CRYPT; }
#line 12242 "obj/conf/cf-parse.tab.c"
    break;

  case 1060: /* ospf_vlink_start: VIRTUAL LINK idval  */
#line 363 "proto/ospf/config.Y"
 {
  if (this_area->areaid == 0) cf_error("Virtual link cannot be in backbone");
  this_ipatt = cfg_allocz(sizeof(struct ospf_iface_patt));
  add_tail(&OSPF_CFG->vlink_list, NODE this_ipatt);
  init_list(&this_ipatt->ipn_list);
  OSPF_PATT->voa = this_area->areaid;
  OSPF_PATT->vid = (yyvsp[0].i32);
  OSPF_PATT->helloint = HELLOINT_D;
  OSPF_PATT->rxmtint = RXMTINT_D;
  OSPF_PATT->inftransdelay = INFTRANSDELAY_D;
  OSPF_PATT->deadc = DEADC_D;
  OSPF_PATT->type = OSPF_IT_VLINK;
  init_list(&OSPF_PATT->nbma_list);
  reset_passwords();
 }
#line 12262 "obj/conf/cf-parse.tab.c"
    break;

  case 1061: /* ospf_iface_item: COST expr  */
#line 381 "proto/ospf/config.Y"
             { OSPF_PATT->cost = (yyvsp[0].i) ; if (((yyvsp[0].i)<=0) || ((yyvsp[0].i)>65535)) cf_error("Cost must be in range 1-65535"); }
#line 12268 "obj/conf/cf-parse.tab.c"
    break;

  case 1062: /* ospf_iface_item: HELLO expr  */
#line 382 "proto/ospf/config.Y"
              { OSPF_PATT->helloint = (yyvsp[0].i) ; if (((yyvsp[0].i)<=0) || ((yyvsp[0].i)>65535)) cf_error("Hello interval must be in range 1-65535"); }
#line 12274 "obj/conf/cf-parse.tab.c"
    break;

  case 1063: /* ospf_iface_item: POLL expr  */
#line 383 "proto/ospf/config.Y"
             { OSPF_PATT->pollint = (yyvsp[0].i) ; if ((yyvsp[0].i)<=0) cf_error("Poll int must be greater than zero"); }
#line 12280 "obj/conf/cf-parse.tab.c"
    break;

  case 1064: /* ospf_iface_item: RETRANSMIT expr  */
#line 384 "proto/ospf/config.Y"
                   { OSPF_PATT->rxmtint = (yyvsp[0].i) ; if ((yyvsp[0].i)<=1) cf_error("Retransmit int must be greater than one"); }
#line 12286 "obj/conf/cf-parse.tab.c"
    break;

  case 1065: /* ospf_iface_item: WAIT expr  */
#line 385 "proto/ospf/config.Y"
             { OSPF_PATT->waitint = (yyvsp[0].i) ; if ((yyvsp[0].i)<=1) cf_error("Wait interval must be greater than one"); }
#line 12292 "obj/conf/cf-parse.tab.c"
    break;

  case 1066: /* ospf_iface_item: DEAD expr  */
#line 386 "proto/ospf/config.Y"
             { OSPF_PATT->deadint = (yyvsp[0].i) ; if ((yyvsp[0].i)<=1) cf_error("Dead interval must be greater than one"); }
#line 12298 "obj/conf/cf-parse.tab.c"
    break;

  case 1067: /* ospf_iface_item: DEAD COUNT expr  */
#line 387 "proto/ospf/config.Y"
                   { OSPF_PATT->deadc = (yyvsp[0].i) ; if ((yyvsp[0].i)<=1) cf_error("Dead count must be greater than one"); }
#line 12304 "obj/conf/cf-parse.tab.c"
    break;

  case 1068: /* ospf_iface_item: TYPE BROADCAST  */
#line 388 "proto/ospf/config.Y"
                  { OSPF_PATT->type = OSPF_IT_BCAST ; }
#line 12310 "obj/conf/cf-parse.tab.c"
    break;

  case 1069: /* ospf_iface_item: TYPE BCAST  */
#line 389 "proto/ospf/config.Y"
              { OSPF_PATT->type = OSPF_IT_BCAST ; }
#line 12316 "obj/conf/cf-parse.tab.c"
    break;

  case 1070: /* ospf_iface_item: TYPE NONBROADCAST  */
#line 390 "proto/ospf/config.Y"
                     { OSPF_PATT->type = OSPF_IT_NBMA ; }
#line 12322 "obj/conf/cf-parse.tab.c"
    break;

  case 1071: /* ospf_iface_item: TYPE NBMA  */
#line 391 "proto/ospf/config.Y"
             { OSPF_PATT->type = OSPF_IT_NBMA ; }
#line 12328 "obj/conf/cf-parse.tab.c"
    break;

  case 1072: /* ospf_iface_item: TYPE POINTOPOINT  */
#line 392 "proto/ospf/config.Y"
                    { OSPF_PATT->type = OSPF_IT_PTP ; }
#line 12334 "obj/conf/cf-parse.tab.c"
    break;

  case 1073: /* ospf_iface_item: TYPE PTP  */
#line 393 "proto/ospf/config.Y"
            { OSPF_PATT->type = OSPF_IT_PTP ; }
#line 12340 "obj/conf/cf-parse.tab.c"
    break;

  case 1074: /* ospf_iface_item: TYPE POINTOMULTIPOINT  */
#line 394 "proto/ospf/config.Y"
                         { OSPF_PATT->type = OSPF_IT_PTMP ; }
#line 12346 "obj/conf/cf-parse.tab.c"
    break;

  case 1075: /* ospf_iface_item: TYPE PTMP  */
#line 395 "proto/ospf/config.Y"
             { OSPF_PATT->type = OSPF_IT_PTMP ; }
#line 12352 "obj/conf/cf-parse.tab.c"
    break;

  case 1076: /* ospf_iface_item: REAL BROADCAST bool  */
#line 396 "proto/ospf/config.Y"
                       { OSPF_PATT->real_bcast = (yyvsp[0].i); if (!ospf_cfg_is_v2()) cf_error("Real broadcast option requires OSPFv2"); }
#line 12358 "obj/conf/cf-parse.tab.c"
    break;

  case 1077: /* ospf_iface_item: PTP NETMASK bool  */
#line 397 "proto/ospf/config.Y"
                    { OSPF_PATT->ptp_netmask = (yyvsp[0].i); if (!ospf_cfg_is_v2()) cf_error("PtP netmask option requires OSPFv2"); }
#line 12364 "obj/conf/cf-parse.tab.c"
    break;

  case 1078: /* ospf_iface_item: PTP ADDRESS bool  */
#line 398 "proto/ospf/config.Y"
                    { OSPF_PATT->ptp_address = (yyvsp[0].i); if (!ospf_cfg_is_v2()) cf_error("PtP address option requires OSPFv2"); }
#line 12370 "obj/conf/cf-parse.tab.c"
    break;

  case 1079: /* ospf_iface_item: TRANSMIT DELAY expr  */
#line 399 "proto/ospf/config.Y"
                       { OSPF_PATT->inftransdelay = (yyvsp[0].i) ; if (((yyvsp[0].i)<=0) || ((yyvsp[0].i)>65535)) cf_error("Transmit delay must be in range 1-65535"); }
#line 12376 "obj/conf/cf-parse.tab.c"
    break;

  case 1080: /* ospf_iface_item: PRIORITY expr  */
#line 400 "proto/ospf/config.Y"
                 { OSPF_PATT->priority = (yyvsp[0].i) ; if ((yyvsp[0].i)>255) cf_error("Priority must be in range 0-255"); }
#line 12382 "obj/conf/cf-parse.tab.c"
    break;

  case 1081: /* ospf_iface_item: STRICT NONBROADCAST bool  */
#line 401 "proto/ospf/config.Y"
                            { OSPF_PATT->strictnbma = (yyvsp[0].i) ; }
#line 12388 "obj/conf/cf-parse.tab.c"
    break;

  case 1082: /* ospf_iface_item: STUB bool  */
#line 402 "proto/ospf/config.Y"
             { OSPF_PATT->stub = (yyvsp[0].i) ; }
#line 12394 "obj/conf/cf-parse.tab.c"
    break;

  case 1083: /* ospf_iface_item: CHECK LINK bool  */
#line 403 "proto/ospf/config.Y"
                   { OSPF_PATT->check_link = (yyvsp[0].i); }
#line 12400 "obj/conf/cf-parse.tab.c"
    break;

  case 1084: /* ospf_iface_item: ECMP WEIGHT expr  */
#line 404 "proto/ospf/config.Y"
                    { OSPF_PATT->ecmp_weight = (yyvsp[0].i) - 1; if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>256)) cf_error("ECMP weight must be in range 1-256"); }
#line 12406 "obj/conf/cf-parse.tab.c"
    break;

  case 1085: /* ospf_iface_item: LINK LSA SUPPRESSION bool  */
#line 405 "proto/ospf/config.Y"
                             { OSPF_PATT->link_lsa_suppression = (yyvsp[0].i); if (!ospf_cfg_is_v3()) cf_error("Link LSA suppression option requires OSPFv3"); }
#line 12412 "obj/conf/cf-parse.tab.c"
    break;

  case 1087: /* ospf_iface_item: AUTHENTICATION NONE  */
#line 407 "proto/ospf/config.Y"
                       { OSPF_PATT->autype = OSPF_AUTH_NONE; }
#line 12418 "obj/conf/cf-parse.tab.c"
    break;

  case 1088: /* ospf_iface_item: AUTHENTICATION SIMPLE  */
#line 408 "proto/ospf/config.Y"
                         { OSPF_PATT->autype = OSPF_AUTH_SIMPLE; ospf_check_auth(); }
#line 12424 "obj/conf/cf-parse.tab.c"
    break;

  case 1089: /* ospf_iface_item: AUTHENTICATION CRYPTOGRAPHIC  */
#line 409 "proto/ospf/config.Y"
                                { OSPF_PATT->autype = OSPF_AUTH_CRYPT; }
#line 12430 "obj/conf/cf-parse.tab.c"
    break;

  case 1090: /* ospf_iface_item: RX BUFFER NORMAL  */
#line 410 "proto/ospf/config.Y"
                    { OSPF_PATT->rx_buffer = 0; }
#line 12436 "obj/conf/cf-parse.tab.c"
    break;

  case 1091: /* ospf_iface_item: RX BUFFER LARGE  */
#line 411 "proto/ospf/config.Y"
                   { OSPF_PATT->rx_buffer = OSPF_MAX_PKT_SIZE; }
#line 12442 "obj/conf/cf-parse.tab.c"
    break;

  case 1092: /* ospf_iface_item: RX BUFFER expr  */
#line 412 "proto/ospf/config.Y"
                  { OSPF_PATT->rx_buffer = (yyvsp[0].i); if (((yyvsp[0].i) < OSPF_MIN_PKT_SIZE) || ((yyvsp[0].i) > OSPF_MAX_PKT_SIZE)) cf_error("Buffer size must be in range 256-65535"); }
#line 12448 "obj/conf/cf-parse.tab.c"
    break;

  case 1093: /* ospf_iface_item: TX tos  */
#line 413 "proto/ospf/config.Y"
          { OSPF_PATT->tx_tos = (yyvsp[0].i); }
#line 12454 "obj/conf/cf-parse.tab.c"
    break;

  case 1094: /* ospf_iface_item: TX PRIORITY expr  */
#line 414 "proto/ospf/config.Y"
                    { OSPF_PATT->tx_priority = (yyvsp[0].i); }
#line 12460 "obj/conf/cf-parse.tab.c"
    break;

  case 1095: /* ospf_iface_item: TX LENGTH expr  */
#line 415 "proto/ospf/config.Y"
                  { OSPF_PATT->tx_length = (yyvsp[0].i); if (((yyvsp[0].i) < OSPF_MIN_PKT_SIZE) || ((yyvsp[0].i) > OSPF_MAX_PKT_SIZE)) cf_error("TX length must be in range 256-65535"); }
#line 12466 "obj/conf/cf-parse.tab.c"
    break;

  case 1096: /* ospf_iface_item: TTL SECURITY bool  */
#line 416 "proto/ospf/config.Y"
                     { OSPF_PATT->ttl_security = (yyvsp[0].i); }
#line 12472 "obj/conf/cf-parse.tab.c"
    break;

  case 1097: /* ospf_iface_item: TTL SECURITY TX ONLY  */
#line 417 "proto/ospf/config.Y"
                        { OSPF_PATT->ttl_security = 2; }
#line 12478 "obj/conf/cf-parse.tab.c"
    break;

  case 1098: /* ospf_iface_item: BFD bool  */
#line 418 "proto/ospf/config.Y"
            { OSPF_PATT->bfd = (yyvsp[0].i); cf_check_bfd((yyvsp[0].i)); }
#line 12484 "obj/conf/cf-parse.tab.c"
    break;

  case 1103: /* pref_base: net_ip  */
#line 430 "proto/ospf/config.Y"
 {
   this_pref = cfg_allocz(sizeof(struct area_net_config));
   add_tail(this_nets, NODE this_pref);
   this_pref->prefix = (yyvsp[0].net);
 }
#line 12494 "obj/conf/cf-parse.tab.c"
    break;

  case 1105: /* pref_opt: HIDDEN  */
#line 439 "proto/ospf/config.Y"
          { this_pref->hidden = 1; }
#line 12500 "obj/conf/cf-parse.tab.c"
    break;

  case 1106: /* pref_opt: TAG expr  */
#line 440 "proto/ospf/config.Y"
            { this_pref->tag = (yyvsp[0].i); }
#line 12506 "obj/conf/cf-parse.tab.c"
    break;

  case 1109: /* nbma_eligible: %empty  */
#line 449 "proto/ospf/config.Y"
             { (yyval.i) = 0; }
#line 12512 "obj/conf/cf-parse.tab.c"
    break;

  case 1110: /* nbma_eligible: ELIGIBLE  */
#line 450 "proto/ospf/config.Y"
            { (yyval.i) = 1; }
#line 12518 "obj/conf/cf-parse.tab.c"
    break;

  case 1111: /* nbma_item: ipa nbma_eligible ';'  */
#line 454 "proto/ospf/config.Y"
 {
   this_nbma = cfg_allocz(sizeof(struct nbma_node));
   add_tail(&OSPF_PATT->nbma_list, NODE this_nbma);
   this_nbma->ip=(yyvsp[-2].a);
   this_nbma->eligible=(yyvsp[-1].i);
 }
#line 12529 "obj/conf/cf-parse.tab.c"
    break;

  case 1112: /* ospf_iface_start: %empty  */
#line 463 "proto/ospf/config.Y"
 {
  this_ipatt = cfg_allocz(sizeof(struct ospf_iface_patt));
  add_tail(&this_area->patt_list, NODE this_ipatt);
  init_list(&this_ipatt->ipn_list);
  OSPF_PATT->cost = COST_D;
  OSPF_PATT->helloint = HELLOINT_D;
  OSPF_PATT->pollint = POLLINT_D;
  OSPF_PATT->rxmtint = RXMTINT_D;
  OSPF_PATT->inftransdelay = INFTRANSDELAY_D;
  OSPF_PATT->priority = PRIORITY_D;
  OSPF_PATT->deadc = DEADC_D;
  OSPF_PATT->type = OSPF_IT_UNDEF;
  init_list(&OSPF_PATT->nbma_list);
  OSPF_PATT->check_link = 1;
  OSPF_PATT->ptp_netmask = 2; /* not specified */
  OSPF_PATT->ptp_address = 2; /* not specified */
  OSPF_PATT->tx_tos = IP_PREC_INTERNET_CONTROL;
  OSPF_PATT->tx_priority = sk_priority_control;
  reset_passwords();
 }
#line 12554 "obj/conf/cf-parse.tab.c"
    break;

  case 1114: /* ospf_instance_id: INSTANCE expr  */
#line 487 "proto/ospf/config.Y"
                 { OSPF_PATT->instance_id = (yyvsp[0].i); OSPF_PATT->instance_id_set = 1; if ((yyvsp[0].i) > 255) cf_error("Instance ID must be in range 0-255"); }
#line 12560 "obj/conf/cf-parse.tab.c"
    break;

  case 1115: /* $@13: %empty  */
#line 491 "proto/ospf/config.Y"
                   { if (ospf_cfg_is_v3()) iface_patt_check(); }
#line 12566 "obj/conf/cf-parse.tab.c"
    break;

  case 1121: /* ospf_iface: ospf_iface_start ospf_iface_patt_list ospf_iface_opt_list  */
#line 505 "proto/ospf/config.Y"
                                                            { ospf_iface_finish(); }
#line 12572 "obj/conf/cf-parse.tab.c"
    break;

  case 1122: /* dynamic_attr: OSPF_METRIC1  */
#line 508 "proto/ospf/config.Y"
                           { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_OSPF_METRIC1); }
#line 12578 "obj/conf/cf-parse.tab.c"
    break;

  case 1123: /* dynamic_attr: OSPF_METRIC2  */
#line 509 "proto/ospf/config.Y"
                           { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_OSPF_METRIC2); }
#line 12584 "obj/conf/cf-parse.tab.c"
    break;

  case 1124: /* dynamic_attr: OSPF_TAG  */
#line 510 "proto/ospf/config.Y"
                       { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_OSPF_TAG); }
#line 12590 "obj/conf/cf-parse.tab.c"
    break;

  case 1125: /* dynamic_attr: OSPF_ROUTER_ID  */
#line 511 "proto/ospf/config.Y"
                             { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_ROUTER_ID, T_QUAD, EA_OSPF_ROUTER_ID); }
#line 12596 "obj/conf/cf-parse.tab.c"
    break;

  case 1127: /* cmd_SHOW_OSPF: SHOW OSPF optproto END  */
#line 515 "proto/ospf/config.Y"
{ PROTO_WALK_CMD((yyvsp[-1].s), &proto_ospf, p) ospf_sh(p); }
#line 12602 "obj/conf/cf-parse.tab.c"
    break;

  case 1129: /* cmd_SHOW_OSPF_NEIGHBORS: SHOW OSPF NEIGHBORS optproto opttext END  */
#line 518 "proto/ospf/config.Y"
{ PROTO_WALK_CMD((yyvsp[-2].s), &proto_ospf, p) ospf_sh_neigh(p, (yyvsp[-1].t)); }
#line 12608 "obj/conf/cf-parse.tab.c"
    break;

  case 1131: /* cmd_SHOW_OSPF_INTERFACE: SHOW OSPF INTERFACE optproto opttext END  */
#line 521 "proto/ospf/config.Y"
{ PROTO_WALK_CMD((yyvsp[-2].s), &proto_ospf, p) ospf_sh_iface(p, (yyvsp[-1].t)); }
#line 12614 "obj/conf/cf-parse.tab.c"
    break;

  case 1133: /* cmd_SHOW_OSPF_TOPOLOGY: SHOW OSPF TOPOLOGY optproto opttext END  */
#line 526 "proto/ospf/config.Y"
{ ospf_sh_state(proto_get_named((yyvsp[-2].s), &proto_ospf), 0, 1); }
#line 12620 "obj/conf/cf-parse.tab.c"
    break;

  case 1135: /* cmd_SHOW_OSPF_TOPOLOGY_ALL: SHOW OSPF TOPOLOGY ALL optproto opttext END  */
#line 529 "proto/ospf/config.Y"
{ ospf_sh_state(proto_get_named((yyvsp[-2].s), &proto_ospf), 0, 0); }
#line 12626 "obj/conf/cf-parse.tab.c"
    break;

  case 1137: /* cmd_SHOW_OSPF_STATE: SHOW OSPF STATE optproto opttext END  */
#line 534 "proto/ospf/config.Y"
{ ospf_sh_state(proto_get_named((yyvsp[-2].s), &proto_ospf), 1, 1); }
#line 12632 "obj/conf/cf-parse.tab.c"
    break;

  case 1139: /* cmd_SHOW_OSPF_STATE_ALL: SHOW OSPF STATE ALL optproto opttext END  */
#line 537 "proto/ospf/config.Y"
{ ospf_sh_state(proto_get_named((yyvsp[-2].s), &proto_ospf), 1, 0); }
#line 12638 "obj/conf/cf-parse.tab.c"
    break;

  case 1141: /* cmd_SHOW_OSPF_LSADB: SHOW OSPF LSADB lsadb_args END  */
#line 541 "proto/ospf/config.Y"
{
  if (!(yyvsp[-1].ld)->proto)
    (yyvsp[-1].ld)->proto = (struct ospf_proto *) proto_get_named(NULL, &proto_ospf);

  ospf_sh_lsadb((yyvsp[-1].ld));
}
#line 12649 "obj/conf/cf-parse.tab.c"
    break;

  case 1142: /* lsadb_args: %empty  */
#line 549 "proto/ospf/config.Y"
               {
     (yyval.ld) = cfg_allocz(sizeof(struct lsadb_show_data));
   }
#line 12657 "obj/conf/cf-parse.tab.c"
    break;

  case 1143: /* lsadb_args: lsadb_args GLOBAL  */
#line 552 "proto/ospf/config.Y"
                     { (yyval.ld) = (yyvsp[-1].ld); (yyval.ld)->scope = LSA_SCOPE_AS; }
#line 12663 "obj/conf/cf-parse.tab.c"
    break;

  case 1144: /* lsadb_args: lsadb_args AREA idval  */
#line 553 "proto/ospf/config.Y"
                         { (yyval.ld) = (yyvsp[-2].ld); (yyval.ld)->scope = LSA_SCOPE_AREA; (yyval.ld)->area = (yyvsp[0].i32); }
#line 12669 "obj/conf/cf-parse.tab.c"
    break;

  case 1145: /* lsadb_args: lsadb_args LINK  */
#line 554 "proto/ospf/config.Y"
                   { (yyval.ld) = (yyvsp[-1].ld); (yyval.ld)->scope = 1; /* hack, 0 is no filter */ }
#line 12675 "obj/conf/cf-parse.tab.c"
    break;

  case 1146: /* lsadb_args: lsadb_args TYPE NUM  */
#line 555 "proto/ospf/config.Y"
                       { (yyval.ld) = (yyvsp[-2].ld); (yyval.ld)->type = (yyvsp[0].i); }
#line 12681 "obj/conf/cf-parse.tab.c"
    break;

  case 1147: /* lsadb_args: lsadb_args LSID idval  */
#line 556 "proto/ospf/config.Y"
                         { (yyval.ld) = (yyvsp[-2].ld); (yyval.ld)->lsid = (yyvsp[0].i32); }
#line 12687 "obj/conf/cf-parse.tab.c"
    break;

  case 1148: /* lsadb_args: lsadb_args SELF  */
#line 557 "proto/ospf/config.Y"
                   { (yyval.ld) = (yyvsp[-1].ld); (yyval.ld)->router = SH_ROUTER_SELF; }
#line 12693 "obj/conf/cf-parse.tab.c"
    break;

  case 1149: /* lsadb_args: lsadb_args ROUTER idval  */
#line 558 "proto/ospf/config.Y"
                           { (yyval.ld) = (yyvsp[-2].ld); (yyval.ld)->router = (yyvsp[0].i32); }
#line 12699 "obj/conf/cf-parse.tab.c"
    break;

  case 1150: /* lsadb_args: lsadb_args CF_SYM_KNOWN  */
#line 559 "proto/ospf/config.Y"
                           { cf_assert_symbol((yyvsp[0].s), SYM_PROTO); (yyval.ld) = (yyvsp[-1].ld); (yyval.ld)->proto = (struct ospf_proto *) proto_get_named((yyvsp[0].s), &proto_ospf); }
#line 12705 "obj/conf/cf-parse.tab.c"
    break;

  case 1152: /* perf_proto_start: proto_start PERF  */
#line 27 "proto/perf/config.Y"
{
  this_proto = proto_config_new(&proto_perf, (yyvsp[-1].i));
  PERF_CFG->from = 10;
  PERF_CFG->to = 20;
  PERF_CFG->repeat = 4;
  PERF_CFG->threshold_max = 500 MS_;
  PERF_CFG->threshold_min = 1 MS_;
  PERF_CFG->attrs_per_rte = 0;
  PERF_CFG->keep = 0;
  PERF_CFG->mode = PERF_MODE_IMPORT;
}
#line 12721 "obj/conf/cf-parse.tab.c"
    break;

  case 1156: /* perf_proto_item: proto_channel  */
#line 46 "proto/perf/config.Y"
                 { this_proto->net_type = (yyvsp[0].cc)->net_type; }
#line 12727 "obj/conf/cf-parse.tab.c"
    break;

  case 1157: /* perf_proto_item: EXP FROM NUM  */
#line 47 "proto/perf/config.Y"
                { PERF_CFG->from = (yyvsp[0].i); }
#line 12733 "obj/conf/cf-parse.tab.c"
    break;

  case 1158: /* perf_proto_item: EXP TO NUM  */
#line 48 "proto/perf/config.Y"
              { PERF_CFG->to = (yyvsp[0].i); }
#line 12739 "obj/conf/cf-parse.tab.c"
    break;

  case 1159: /* perf_proto_item: REPEAT NUM  */
#line 49 "proto/perf/config.Y"
              { PERF_CFG->repeat = (yyvsp[0].i); }
#line 12745 "obj/conf/cf-parse.tab.c"
    break;

  case 1160: /* perf_proto_item: THRESHOLD MIN expr_us  */
#line 50 "proto/perf/config.Y"
                         { PERF_CFG->threshold_min = (yyvsp[0].time); }
#line 12751 "obj/conf/cf-parse.tab.c"
    break;

  case 1161: /* perf_proto_item: THRESHOLD MAX expr_us  */
#line 51 "proto/perf/config.Y"
                         { PERF_CFG->threshold_max = (yyvsp[0].time); }
#line 12757 "obj/conf/cf-parse.tab.c"
    break;

  case 1162: /* perf_proto_item: ATTRIBUTES NUM  */
#line 52 "proto/perf/config.Y"
                  { PERF_CFG->attrs_per_rte = (yyvsp[0].i); }
#line 12763 "obj/conf/cf-parse.tab.c"
    break;

  case 1163: /* perf_proto_item: KEEP bool  */
#line 53 "proto/perf/config.Y"
             { PERF_CFG->keep = (yyvsp[0].i); }
#line 12769 "obj/conf/cf-parse.tab.c"
    break;

  case 1164: /* perf_proto_item: MODE IMPORT  */
#line 54 "proto/perf/config.Y"
               { PERF_CFG->mode = PERF_MODE_IMPORT; }
#line 12775 "obj/conf/cf-parse.tab.c"
    break;

  case 1165: /* perf_proto_item: MODE EXPORT  */
#line 55 "proto/perf/config.Y"
               { PERF_CFG->mode = PERF_MODE_EXPORT; }
#line 12781 "obj/conf/cf-parse.tab.c"
    break;

  case 1166: /* proto: pipe_proto '}'  */
#line 23 "proto/pipe/config.Y"
                      { this_channel = NULL; }
#line 12787 "obj/conf/cf-parse.tab.c"
    break;

  case 1167: /* $@14: %empty  */
#line 26 "proto/pipe/config.Y"
{
  this_proto = proto_config_new(&proto_pipe, (yyvsp[-1].i));
}
#line 12795 "obj/conf/cf-parse.tab.c"
    break;

  case 1168: /* pipe_proto_start: proto_start PIPE $@14 proto_name  */
#line 30 "proto/pipe/config.Y"
{
  this_channel = proto_cf_main_channel(this_proto);
  if (!this_channel) {
    this_channel = channel_config_new(NULL, NULL, 0, this_proto);
    this_channel->in_filter = FILTER_ACCEPT;
    this_channel->out_filter = FILTER_ACCEPT;
  }
}
#line 12808 "obj/conf/cf-parse.tab.c"
    break;

  case 1172: /* pipe_proto: pipe_proto PEER TABLE rtable ';'  */
#line 43 "proto/pipe/config.Y"
                                    { PIPE_CFG->peer = (yyvsp[-1].r); }
#line 12814 "obj/conf/cf-parse.tab.c"
    break;

  case 1174: /* radv_proto_start: proto_start RADV  */
#line 47 "proto/radv/config.Y"
{
  this_proto = proto_config_new(&proto_radv, (yyvsp[-1].i));
  this_proto->net_type = NET_IP6;

  init_list(&RADV_CFG->patt_list);
  init_list(&RADV_CFG->pref_list);
  init_list(&RADV_CFG->rdnss_list);
  init_list(&RADV_CFG->dnssl_list);
}
#line 12828 "obj/conf/cf-parse.tab.c"
    break;

  case 1178: /* radv_proto_item: PREFIX radv_prefix  */
#line 61 "proto/radv/config.Y"
                      { add_tail(&RADV_CFG->pref_list, NODE this_radv_prefix); }
#line 12834 "obj/conf/cf-parse.tab.c"
    break;

  case 1179: /* $@15: %empty  */
#line 62 "proto/radv/config.Y"
         { init_list(&radv_dns_list); }
#line 12840 "obj/conf/cf-parse.tab.c"
    break;

  case 1180: /* radv_proto_item: RDNSS $@15 radv_rdnss  */
#line 62 "proto/radv/config.Y"
                                                   { add_tail_list(&RADV_CFG->rdnss_list, &radv_dns_list); }
#line 12846 "obj/conf/cf-parse.tab.c"
    break;

  case 1181: /* $@16: %empty  */
#line 63 "proto/radv/config.Y"
         { init_list(&radv_dns_list); }
#line 12852 "obj/conf/cf-parse.tab.c"
    break;

  case 1182: /* radv_proto_item: DNSSL $@16 radv_dnssl  */
#line 63 "proto/radv/config.Y"
                                                   { add_tail_list(&RADV_CFG->dnssl_list, &radv_dns_list); }
#line 12858 "obj/conf/cf-parse.tab.c"
    break;

  case 1183: /* radv_proto_item: TRIGGER net_ip6  */
#line 64 "proto/radv/config.Y"
                   { RADV_CFG->trigger = (yyvsp[0].net); }
#line 12864 "obj/conf/cf-parse.tab.c"
    break;

  case 1184: /* radv_proto_item: PROPAGATE ROUTES bool  */
#line 65 "proto/radv/config.Y"
                         { RADV_CFG->propagate_routes = (yyvsp[0].i); }
#line 12870 "obj/conf/cf-parse.tab.c"
    break;

  case 1188: /* radv_iface_start: %empty  */
#line 78 "proto/radv/config.Y"
{
  this_ipatt = cfg_allocz(sizeof(struct radv_iface_config));
  add_tail(&RADV_CFG->patt_list, NODE this_ipatt);
  init_list(&this_ipatt->ipn_list);
  init_list(&RADV_IFACE->pref_list);
  init_list(&RADV_IFACE->rdnss_list);
  init_list(&RADV_IFACE->dnssl_list);

  RADV_IFACE->min_ra_int = (u32) -1; /* undefined */
  RADV_IFACE->max_ra_int = DEFAULT_MAX_RA_INT;
  RADV_IFACE->min_delay = DEFAULT_MIN_DELAY;
  RADV_IFACE->prefix_linger_time = (u32) -1;
  RADV_IFACE->route_linger_time = (u32) -1;
  RADV_IFACE->current_hop_limit = DEFAULT_CURRENT_HOP_LIMIT;
  RADV_IFACE->default_lifetime = (u32) -1;
  RADV_IFACE->default_lifetime_sensitive = 1;
  RADV_IFACE->default_preference = RA_PREF_MEDIUM;
  RADV_IFACE->route_lifetime = (u32) -1;
  RADV_IFACE->route_lifetime_sensitive = 0;
  RADV_IFACE->route_preference = RA_PREF_MEDIUM;
}
#line 12896 "obj/conf/cf-parse.tab.c"
    break;

  case 1189: /* radv_iface_item: MIN RA INTERVAL expr  */
#line 101 "proto/radv/config.Y"
                        { RADV_IFACE->min_ra_int = (yyvsp[0].i); if ((yyvsp[0].i) < 3) cf_error("Min RA interval must be at least 3"); }
#line 12902 "obj/conf/cf-parse.tab.c"
    break;

  case 1190: /* radv_iface_item: MAX RA INTERVAL expr  */
#line 102 "proto/radv/config.Y"
                        { RADV_IFACE->max_ra_int = (yyvsp[0].i); if (((yyvsp[0].i) < 4) || ((yyvsp[0].i) > 1800)) cf_error("Max RA interval must be in range 4-1800"); }
#line 12908 "obj/conf/cf-parse.tab.c"
    break;

  case 1191: /* radv_iface_item: MIN DELAY expr  */
#line 103 "proto/radv/config.Y"
                  { RADV_IFACE->min_delay = (yyvsp[0].i); if ((yyvsp[0].i) <= 0) cf_error("Min delay must be positive"); }
#line 12914 "obj/conf/cf-parse.tab.c"
    break;

  case 1192: /* radv_iface_item: SOLICITED RA UNICAST bool  */
#line 104 "proto/radv/config.Y"
                             { RADV_IFACE->solicited_ra_unicast = (yyvsp[0].i); }
#line 12920 "obj/conf/cf-parse.tab.c"
    break;

  case 1193: /* radv_iface_item: MANAGED bool  */
#line 105 "proto/radv/config.Y"
                { RADV_IFACE->managed = (yyvsp[0].i); }
#line 12926 "obj/conf/cf-parse.tab.c"
    break;

  case 1194: /* radv_iface_item: OTHER CONFIG bool  */
#line 106 "proto/radv/config.Y"
                     { RADV_IFACE->other_config = (yyvsp[0].i); }
#line 12932 "obj/conf/cf-parse.tab.c"
    break;

  case 1195: /* radv_iface_item: LINK MTU expr  */
#line 107 "proto/radv/config.Y"
                 { RADV_IFACE->link_mtu = (yyvsp[0].i); }
#line 12938 "obj/conf/cf-parse.tab.c"
    break;

  case 1196: /* radv_iface_item: REACHABLE TIME expr  */
#line 108 "proto/radv/config.Y"
                       { RADV_IFACE->reachable_time = (yyvsp[0].i); if ((yyvsp[0].i) > 3600000) cf_error("Reachable time must be in range 0-3600000"); }
#line 12944 "obj/conf/cf-parse.tab.c"
    break;

  case 1197: /* radv_iface_item: RETRANS TIMER expr  */
#line 109 "proto/radv/config.Y"
                      { RADV_IFACE->retrans_timer = (yyvsp[0].i); }
#line 12950 "obj/conf/cf-parse.tab.c"
    break;

  case 1198: /* radv_iface_item: CURRENT HOP LIMIT expr  */
#line 110 "proto/radv/config.Y"
                          { RADV_IFACE->current_hop_limit = (yyvsp[0].i); if ((yyvsp[0].i) > 255) cf_error("Current hop limit must be in range 0-255"); }
#line 12956 "obj/conf/cf-parse.tab.c"
    break;

  case 1199: /* radv_iface_item: DEFAULT LIFETIME expr radv_sensitive  */
#line 111 "proto/radv/config.Y"
                                        {
     RADV_IFACE->default_lifetime = (yyvsp[-1].i);
     if ((yyvsp[-1].i) > 9000)  cf_error("Default lifetime must be in range 0-9000");
     if ((yyvsp[0].i) != (uint) -1) RADV_IFACE->default_lifetime_sensitive = (yyvsp[0].i);
   }
#line 12966 "obj/conf/cf-parse.tab.c"
    break;

  case 1200: /* radv_iface_item: ROUTE LIFETIME expr radv_sensitive  */
#line 116 "proto/radv/config.Y"
                                      {
     RADV_IFACE->route_lifetime = (yyvsp[-1].i);
     if ((yyvsp[0].i) != (uint) -1) RADV_IFACE->route_lifetime_sensitive = (yyvsp[0].i);
   }
#line 12975 "obj/conf/cf-parse.tab.c"
    break;

  case 1201: /* radv_iface_item: DEFAULT PREFERENCE radv_preference  */
#line 120 "proto/radv/config.Y"
                                      { RADV_IFACE->default_preference = (yyvsp[0].i); }
#line 12981 "obj/conf/cf-parse.tab.c"
    break;

  case 1202: /* radv_iface_item: ROUTE PREFERENCE radv_preference  */
#line 121 "proto/radv/config.Y"
                                    { RADV_IFACE->route_preference = (yyvsp[0].i); }
#line 12987 "obj/conf/cf-parse.tab.c"
    break;

  case 1203: /* radv_iface_item: PREFIX LINGER TIME expr  */
#line 122 "proto/radv/config.Y"
                           { RADV_IFACE->prefix_linger_time = (yyvsp[0].i); }
#line 12993 "obj/conf/cf-parse.tab.c"
    break;

  case 1204: /* radv_iface_item: ROUTE LINGER TIME expr  */
#line 123 "proto/radv/config.Y"
                          { RADV_IFACE->route_linger_time = (yyvsp[0].i); }
#line 12999 "obj/conf/cf-parse.tab.c"
    break;

  case 1205: /* radv_iface_item: PREFIX radv_prefix  */
#line 124 "proto/radv/config.Y"
                      { add_tail(&RADV_IFACE->pref_list, NODE this_radv_prefix); }
#line 13005 "obj/conf/cf-parse.tab.c"
    break;

  case 1206: /* $@17: %empty  */
#line 125 "proto/radv/config.Y"
         { init_list(&radv_dns_list); }
#line 13011 "obj/conf/cf-parse.tab.c"
    break;

  case 1207: /* radv_iface_item: RDNSS $@17 radv_rdnss  */
#line 125 "proto/radv/config.Y"
                                                   { add_tail_list(&RADV_IFACE->rdnss_list, &radv_dns_list); }
#line 13017 "obj/conf/cf-parse.tab.c"
    break;

  case 1208: /* $@18: %empty  */
#line 126 "proto/radv/config.Y"
         { init_list(&radv_dns_list); }
#line 13023 "obj/conf/cf-parse.tab.c"
    break;

  case 1209: /* radv_iface_item: DNSSL $@18 radv_dnssl  */
#line 126 "proto/radv/config.Y"
                                                   { add_tail_list(&RADV_IFACE->dnssl_list, &radv_dns_list); }
#line 13029 "obj/conf/cf-parse.tab.c"
    break;

  case 1210: /* radv_iface_item: RDNSS LOCAL bool  */
#line 127 "proto/radv/config.Y"
                    { RADV_IFACE->rdnss_local = (yyvsp[0].i); }
#line 13035 "obj/conf/cf-parse.tab.c"
    break;

  case 1211: /* radv_iface_item: DNSSL LOCAL bool  */
#line 128 "proto/radv/config.Y"
                    { RADV_IFACE->dnssl_local = (yyvsp[0].i); }
#line 13041 "obj/conf/cf-parse.tab.c"
    break;

  case 1212: /* radv_preference: LOW  */
#line 132 "proto/radv/config.Y"
       { (yyval.i) = RA_PREF_LOW; }
#line 13047 "obj/conf/cf-parse.tab.c"
    break;

  case 1213: /* radv_preference: MEDIUM  */
#line 133 "proto/radv/config.Y"
          { (yyval.i) = RA_PREF_MEDIUM; }
#line 13053 "obj/conf/cf-parse.tab.c"
    break;

  case 1214: /* radv_preference: HIGH  */
#line 134 "proto/radv/config.Y"
        { (yyval.i) = RA_PREF_HIGH; }
#line 13059 "obj/conf/cf-parse.tab.c"
    break;

  case 1215: /* radv_iface_finish: %empty  */
#line 137 "proto/radv/config.Y"
{
  struct radv_iface_config *ic = RADV_IFACE;

  if (ic->min_ra_int == (u32) -1)
    ic->min_ra_int = MAX_(ic->max_ra_int / 3, 3);

  if (ic->default_lifetime == (u32) -1)
    ic->default_lifetime = 3 * ic->max_ra_int;

  if (ic->route_lifetime == (u32) -1)
    ic->route_lifetime = 3 * ic->max_ra_int;

  if (ic->prefix_linger_time == (u32) -1)
    ic->prefix_linger_time = 3 * ic->max_ra_int;

  if (ic->route_linger_time == (u32) -1)
    ic->route_linger_time = 3 * ic->max_ra_int;

  if ((ic->min_ra_int > 3) &&
      (ic->min_ra_int > (ic->max_ra_int * 3 / 4)))
    cf_error("Min RA interval must be at most 3/4 * Max RA interval");

  if ((ic->default_lifetime > 0) && (ic->default_lifetime < ic->max_ra_int))
    cf_error("Default lifetime must be either 0 or at least Max RA interval");

  if ((ic->route_lifetime > 0) && (ic->route_lifetime < ic->max_ra_int))
    cf_error("Route lifetime must be either 0 or at least Max RA interval");

  if ((ic->prefix_linger_time > 0) && (ic->prefix_linger_time < ic->max_ra_int))
    cf_error("Prefix linger time must be either 0 or at least Max RA interval");

  if ((ic->route_linger_time > 0) && (ic->route_linger_time < ic->max_ra_int))
    cf_error("Route linger time must be either 0 or at least Max RA interval");

  RADV_CFG->max_linger_time = MAX_(RADV_CFG->max_linger_time, ic->route_linger_time);
}
#line 13100 "obj/conf/cf-parse.tab.c"
    break;

  case 1221: /* radv_prefix_start: net_ip6  */
#line 190 "proto/radv/config.Y"
{
  this_radv_prefix = cfg_allocz(sizeof(struct radv_prefix_config));
  RADV_PREFIX->prefix = *(net_addr_ip6 *) &((yyvsp[0].net));

  RADV_PREFIX->onlink = 1;
  RADV_PREFIX->autonomous = 1;
  RADV_PREFIX->valid_lifetime = DEFAULT_VALID_LIFETIME;
  RADV_PREFIX->preferred_lifetime = DEFAULT_PREFERRED_LIFETIME;
}
#line 13114 "obj/conf/cf-parse.tab.c"
    break;

  case 1222: /* radv_prefix_item: SKIP bool  */
#line 201 "proto/radv/config.Y"
             { RADV_PREFIX->skip = (yyvsp[0].i); }
#line 13120 "obj/conf/cf-parse.tab.c"
    break;

  case 1223: /* radv_prefix_item: ONLINK bool  */
#line 202 "proto/radv/config.Y"
               { RADV_PREFIX->onlink = (yyvsp[0].i); }
#line 13126 "obj/conf/cf-parse.tab.c"
    break;

  case 1224: /* radv_prefix_item: AUTONOMOUS bool  */
#line 203 "proto/radv/config.Y"
                   { RADV_PREFIX->autonomous = (yyvsp[0].i); }
#line 13132 "obj/conf/cf-parse.tab.c"
    break;

  case 1225: /* radv_prefix_item: VALID LIFETIME expr radv_sensitive  */
#line 204 "proto/radv/config.Y"
                                      {
     RADV_PREFIX->valid_lifetime = (yyvsp[-1].i);
     if ((yyvsp[0].i) != (uint) -1) RADV_PREFIX->valid_lifetime_sensitive = (yyvsp[0].i);
   }
#line 13141 "obj/conf/cf-parse.tab.c"
    break;

  case 1226: /* radv_prefix_item: PREFERRED LIFETIME expr radv_sensitive  */
#line 208 "proto/radv/config.Y"
                                          {
     RADV_PREFIX->preferred_lifetime = (yyvsp[-1].i);
     if ((yyvsp[0].i) != (uint) -1) RADV_PREFIX->preferred_lifetime_sensitive = (yyvsp[0].i);
   }
#line 13150 "obj/conf/cf-parse.tab.c"
    break;

  case 1227: /* radv_prefix_finish: %empty  */
#line 215 "proto/radv/config.Y"
{
  if (RADV_PREFIX->preferred_lifetime > RADV_PREFIX->valid_lifetime)
    cf_error("Preferred lifetime must be at most Valid lifetime");

  if (RADV_PREFIX->valid_lifetime_sensitive > RADV_PREFIX->preferred_lifetime_sensitive)
    cf_error("Valid lifetime sensitive requires that Preferred lifetime is sensitive too");
}
#line 13162 "obj/conf/cf-parse.tab.c"
    break;

  case 1233: /* radv_rdnss_node: ipa  */
#line 239 "proto/radv/config.Y"
{
  struct radv_rdnss_config *cf = cfg_allocz(sizeof(struct radv_rdnss_config));
  add_tail(&radv_dns_list, NODE cf);

  cf->server = (yyvsp[0].a);
  cf->lifetime_mult = DEFAULT_DNS_LIFETIME_MULT;
}
#line 13174 "obj/conf/cf-parse.tab.c"
    break;

  case 1234: /* radv_rdnss_start: %empty  */
#line 248 "proto/radv/config.Y"
{
  RADV_RDNSS->lifetime = 0;
  RADV_RDNSS->lifetime_mult = DEFAULT_DNS_LIFETIME_MULT;
}
#line 13183 "obj/conf/cf-parse.tab.c"
    break;

  case 1237: /* radv_rdnss_item: LIFETIME radv_mult  */
#line 255 "proto/radv/config.Y"
                      { RADV_RDNSS->lifetime = (yyvsp[0].i); RADV_RDNSS->lifetime_mult = radv_mult_val; }
#line 13189 "obj/conf/cf-parse.tab.c"
    break;

  case 1238: /* radv_rdnss_finish: %empty  */
#line 259 "proto/radv/config.Y"
{
  if (EMPTY_LIST(radv_dns_list))
    cf_error("No nameserver in RDNSS section");

  struct radv_rdnss_config *cf;
  WALK_LIST(cf, radv_dns_list)
  {
    cf->lifetime = RADV_RDNSS->lifetime;
    cf->lifetime_mult = RADV_RDNSS->lifetime_mult;
  }
}
#line 13205 "obj/conf/cf-parse.tab.c"
    break;

  case 1243: /* radv_dnssl_node: TEXT  */
#line 283 "proto/radv/config.Y"
{
  struct radv_dnssl_config *cf = cfg_allocz(sizeof(struct radv_dnssl_config));
  add_tail(&radv_dns_list, NODE cf);

  cf->domain = (yyvsp[0].t);
  cf->lifetime_mult = DEFAULT_DNS_LIFETIME_MULT;

  if (radv_process_domain(cf) < 0)
    cf_error("Invalid domain dame");
}
#line 13220 "obj/conf/cf-parse.tab.c"
    break;

  case 1244: /* radv_dnssl_start: %empty  */
#line 295 "proto/radv/config.Y"
{
  RADV_DNSSL->lifetime = 0;
  RADV_DNSSL->lifetime_mult = DEFAULT_DNS_LIFETIME_MULT;
}
#line 13229 "obj/conf/cf-parse.tab.c"
    break;

  case 1247: /* radv_dnssl_item: LIFETIME radv_mult  */
#line 302 "proto/radv/config.Y"
                      { RADV_DNSSL->lifetime = (yyvsp[0].i); RADV_DNSSL->lifetime_mult = radv_mult_val; }
#line 13235 "obj/conf/cf-parse.tab.c"
    break;

  case 1248: /* radv_dnssl_finish: %empty  */
#line 306 "proto/radv/config.Y"
{
  if (EMPTY_LIST(radv_dns_list))
    cf_error("No domain in DNSSL section");

  struct radv_dnssl_config *cf;
  WALK_LIST(cf, radv_dns_list)
  {
    cf->lifetime = RADV_DNSSL->lifetime;
    cf->lifetime_mult = RADV_DNSSL->lifetime_mult;
  }
}
#line 13251 "obj/conf/cf-parse.tab.c"
    break;

  case 1253: /* radv_mult: expr  */
#line 330 "proto/radv/config.Y"
        { (yyval.i) = (yyvsp[0].i); radv_mult_val = 0; }
#line 13257 "obj/conf/cf-parse.tab.c"
    break;

  case 1254: /* radv_mult: MULT expr  */
#line 331 "proto/radv/config.Y"
             { (yyval.i) = 0; radv_mult_val = (yyvsp[0].i); if (((yyvsp[0].i) < 1) || ((yyvsp[0].i) > 254)) cf_error("Multiplier must be in range 1-254"); }
#line 13263 "obj/conf/cf-parse.tab.c"
    break;

  case 1255: /* radv_sensitive: %empty  */
#line 335 "proto/radv/config.Y"
               { (yyval.i) = (uint) -1; }
#line 13269 "obj/conf/cf-parse.tab.c"
    break;

  case 1256: /* radv_sensitive: SENSITIVE bool  */
#line 336 "proto/radv/config.Y"
                  { (yyval.i) = (yyvsp[0].i); }
#line 13275 "obj/conf/cf-parse.tab.c"
    break;

  case 1257: /* dynamic_attr: RA_PREFERENCE  */
#line 339 "proto/radv/config.Y"
                            { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_ENUM_RA_PREFERENCE, EA_RA_PREFERENCE); }
#line 13281 "obj/conf/cf-parse.tab.c"
    break;

  case 1258: /* dynamic_attr: RA_LIFETIME  */
#line 340 "proto/radv/config.Y"
                          { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_RA_LIFETIME); }
#line 13287 "obj/conf/cf-parse.tab.c"
    break;

  case 1260: /* rip_variant: RIP  */
#line 49 "proto/rip/config.Y"
          { (yyval.i) = 1; }
#line 13293 "obj/conf/cf-parse.tab.c"
    break;

  case 1261: /* rip_variant: RIP NG  */
#line 50 "proto/rip/config.Y"
          { (yyval.i) = 0; }
#line 13299 "obj/conf/cf-parse.tab.c"
    break;

  case 1262: /* rip_proto_start: proto_start rip_variant  */
#line 54 "proto/rip/config.Y"
{
  this_proto = proto_config_new(&proto_rip, (yyvsp[-1].i));
  this_proto->net_type = (yyvsp[0].i) ? NET_IP4 : NET_IP6;

  init_list(&RIP_CFG->patt_list);
  RIP_CFG->rip2 = (yyvsp[0].i);
  RIP_CFG->ecmp = rt_default_ecmp;
  RIP_CFG->infinity = RIP_DEFAULT_INFINITY;
  RIP_CFG->min_timeout_time = 60 S_;
  RIP_CFG->max_garbage_time = 60 S_;
}
#line 13315 "obj/conf/cf-parse.tab.c"
    break;

  case 1265: /* rip_proto_item: ECMP bool  */
#line 69 "proto/rip/config.Y"
                        { RIP_CFG->ecmp = (yyvsp[0].i) ? RIP_DEFAULT_ECMP_LIMIT : 0; }
#line 13321 "obj/conf/cf-parse.tab.c"
    break;

  case 1266: /* rip_proto_item: ECMP bool LIMIT expr  */
#line 70 "proto/rip/config.Y"
                        { RIP_CFG->ecmp = (yyvsp[-2].i) ? (yyvsp[0].i) : 0; }
#line 13327 "obj/conf/cf-parse.tab.c"
    break;

  case 1267: /* rip_proto_item: INFINITY expr  */
#line 71 "proto/rip/config.Y"
                        { RIP_CFG->infinity = (yyvsp[0].i); }
#line 13333 "obj/conf/cf-parse.tab.c"
    break;

  case 1272: /* rip_iface_start: %empty  */
#line 85 "proto/rip/config.Y"
{
  this_ipatt = cfg_allocz(sizeof(struct rip_iface_config));
  add_tail(&RIP_CFG->patt_list, NODE this_ipatt);
  init_list(&this_ipatt->ipn_list);
  reset_passwords();

  RIP_IFACE->metric = 1;
  RIP_IFACE->port = rip_cfg_is_v2() ? RIP_PORT : RIP_NG_PORT;
  RIP_IFACE->version = rip_cfg_is_v2() ? RIP_V2 : RIP_V1;
  RIP_IFACE->split_horizon = 1;
  RIP_IFACE->poison_reverse = 1;
  RIP_IFACE->check_zero = 1;
  RIP_IFACE->check_link = 1;
  RIP_IFACE->ttl_security = rip_cfg_is_v2() ? 0 : 1;
  RIP_IFACE->rx_buffer = rip_cfg_is_v2() ? RIP_MAX_PKT_LENGTH : 0;
  RIP_IFACE->tx_length = rip_cfg_is_v2() ? RIP_MAX_PKT_LENGTH : 0;
  RIP_IFACE->tx_tos = IP_PREC_INTERNET_CONTROL;
  RIP_IFACE->tx_priority = sk_priority_control;
  RIP_IFACE->update_time = RIP_DEFAULT_UPDATE_TIME;
  RIP_IFACE->timeout_time = RIP_DEFAULT_TIMEOUT_TIME;
  RIP_IFACE->garbage_time = RIP_DEFAULT_GARBAGE_TIME;
  RIP_IFACE->rxmt_time = RIP_DEFAULT_RXMT_TIME;
}
#line 13361 "obj/conf/cf-parse.tab.c"
    break;

  case 1273: /* rip_iface_finish: %empty  */
#line 110 "proto/rip/config.Y"
{
  /* Default mode is broadcast for RIPv1, multicast for RIPv2 and RIPng */
  if (!RIP_IFACE->mode)
    RIP_IFACE->mode = (rip_cfg_is_v2() && (RIP_IFACE->version == RIP_V1)) ?
      RIP_IM_BROADCAST : RIP_IM_MULTICAST;

  RIP_IFACE->passwords = get_passwords();

  if (!RIP_IFACE->auth_type != !RIP_IFACE->passwords)
    log(L_WARN "Authentication and password options should be used together");

  if (RIP_IFACE->passwords)
  {
    struct password_item *pass;
    WALK_LIST(pass, *RIP_IFACE->passwords)
    {
      if (pass->alg && (RIP_IFACE->auth_type != RIP_AUTH_CRYPTO))
	cf_error("Password algorithm option requires cryptographic authentication");

      /* Set default crypto algorithm (MD5) */
      if (!pass->alg && (RIP_IFACE->auth_type == RIP_AUTH_CRYPTO))
	pass->alg = ALG_MD5;
    }
  }

  RIP_CFG->min_timeout_time = MIN_(RIP_CFG->min_timeout_time, RIP_IFACE->timeout_time);
  RIP_CFG->max_garbage_time = MAX_(RIP_CFG->max_garbage_time, RIP_IFACE->garbage_time);
}
#line 13394 "obj/conf/cf-parse.tab.c"
    break;

  case 1274: /* rip_iface_item: METRIC expr  */
#line 140 "proto/rip/config.Y"
                        { RIP_IFACE->metric = (yyvsp[0].i); if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>255)) cf_error("Metric must be in range 1-255"); }
#line 13400 "obj/conf/cf-parse.tab.c"
    break;

  case 1275: /* rip_iface_item: MODE MULTICAST  */
#line 141 "proto/rip/config.Y"
                        { RIP_IFACE->mode = RIP_IM_MULTICAST; }
#line 13406 "obj/conf/cf-parse.tab.c"
    break;

  case 1276: /* rip_iface_item: MODE BROADCAST  */
#line 142 "proto/rip/config.Y"
                        { RIP_IFACE->mode = RIP_IM_BROADCAST; if (rip_cfg_is_ng()) cf_error("Broadcast not supported in RIPng"); }
#line 13412 "obj/conf/cf-parse.tab.c"
    break;

  case 1277: /* rip_iface_item: PASSIVE bool  */
#line 143 "proto/rip/config.Y"
                        { RIP_IFACE->passive = (yyvsp[0].i); }
#line 13418 "obj/conf/cf-parse.tab.c"
    break;

  case 1278: /* rip_iface_item: ADDRESS ipa  */
#line 144 "proto/rip/config.Y"
                        { RIP_IFACE->address = (yyvsp[0].a); if (ipa_is_ip4((yyvsp[0].a)) != rip_cfg_is_v2()) cf_error("IP address version mismatch"); }
#line 13424 "obj/conf/cf-parse.tab.c"
    break;

  case 1279: /* rip_iface_item: PORT expr  */
#line 145 "proto/rip/config.Y"
                        { RIP_IFACE->port = (yyvsp[0].i); if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>65535)) cf_error("Invalid port number"); }
#line 13430 "obj/conf/cf-parse.tab.c"
    break;

  case 1280: /* rip_iface_item: VERSION expr  */
#line 146 "proto/rip/config.Y"
                        { RIP_IFACE->version = (yyvsp[0].i);
			  if (rip_cfg_is_ng()) cf_error("Version not supported in RIPng");
			  if (((yyvsp[0].i) != RIP_V1) && ((yyvsp[0].i) != RIP_V2)) cf_error("Unsupported version");
			}
#line 13439 "obj/conf/cf-parse.tab.c"
    break;

  case 1281: /* rip_iface_item: VERSION ONLY bool  */
#line 150 "proto/rip/config.Y"
                        { RIP_IFACE->version_only = (yyvsp[0].i); }
#line 13445 "obj/conf/cf-parse.tab.c"
    break;

  case 1282: /* rip_iface_item: SPLIT HORIZON bool  */
#line 151 "proto/rip/config.Y"
                        { RIP_IFACE->split_horizon = (yyvsp[0].i); }
#line 13451 "obj/conf/cf-parse.tab.c"
    break;

  case 1283: /* rip_iface_item: POISON REVERSE bool  */
#line 152 "proto/rip/config.Y"
                        { RIP_IFACE->poison_reverse = (yyvsp[0].i); }
#line 13457 "obj/conf/cf-parse.tab.c"
    break;

  case 1284: /* rip_iface_item: CHECK ZERO bool  */
#line 153 "proto/rip/config.Y"
                        { RIP_IFACE->check_zero = (yyvsp[0].i); }
#line 13463 "obj/conf/cf-parse.tab.c"
    break;

  case 1285: /* rip_iface_item: DEMAND CIRCUIT bool  */
#line 154 "proto/rip/config.Y"
                        { RIP_IFACE->demand_circuit = (yyvsp[0].i); }
#line 13469 "obj/conf/cf-parse.tab.c"
    break;

  case 1286: /* rip_iface_item: UPDATE TIME expr  */
#line 155 "proto/rip/config.Y"
                        { RIP_IFACE->update_time = (yyvsp[0].i) S_; if ((yyvsp[0].i)<=0) cf_error("Update time must be positive"); }
#line 13475 "obj/conf/cf-parse.tab.c"
    break;

  case 1287: /* rip_iface_item: TIMEOUT TIME expr  */
#line 156 "proto/rip/config.Y"
                        { RIP_IFACE->timeout_time = (yyvsp[0].i) S_; if ((yyvsp[0].i)<=0) cf_error("Timeout time must be positive"); }
#line 13481 "obj/conf/cf-parse.tab.c"
    break;

  case 1288: /* rip_iface_item: GARBAGE TIME expr  */
#line 157 "proto/rip/config.Y"
                        { RIP_IFACE->garbage_time = (yyvsp[0].i) S_; if ((yyvsp[0].i)<=0) cf_error("Garbage time must be positive"); }
#line 13487 "obj/conf/cf-parse.tab.c"
    break;

  case 1289: /* rip_iface_item: RETRANSMIT TIME expr_us  */
#line 158 "proto/rip/config.Y"
                           { RIP_IFACE->rxmt_time = (yyvsp[0].time); if ((yyvsp[0].time)<=0) cf_error("Retransmit time must be positive"); }
#line 13493 "obj/conf/cf-parse.tab.c"
    break;

  case 1290: /* rip_iface_item: ECMP WEIGHT expr  */
#line 159 "proto/rip/config.Y"
                        { RIP_IFACE->ecmp_weight = (yyvsp[0].i) - 1; if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>256)) cf_error("ECMP weight must be in range 1-256"); }
#line 13499 "obj/conf/cf-parse.tab.c"
    break;

  case 1291: /* rip_iface_item: RX BUFFER expr  */
#line 160 "proto/rip/config.Y"
                        { RIP_IFACE->rx_buffer = (yyvsp[0].i); if (((yyvsp[0].i)<256) || ((yyvsp[0].i)>65535)) cf_error("RX length must be in range 256-65535"); }
#line 13505 "obj/conf/cf-parse.tab.c"
    break;

  case 1292: /* rip_iface_item: TX LENGTH expr  */
#line 161 "proto/rip/config.Y"
                        { RIP_IFACE->tx_length = (yyvsp[0].i); if (((yyvsp[0].i)<256) || ((yyvsp[0].i)>65535)) cf_error("TX length must be in range 256-65535"); }
#line 13511 "obj/conf/cf-parse.tab.c"
    break;

  case 1293: /* rip_iface_item: TX tos  */
#line 162 "proto/rip/config.Y"
                        { RIP_IFACE->tx_tos = (yyvsp[0].i); }
#line 13517 "obj/conf/cf-parse.tab.c"
    break;

  case 1294: /* rip_iface_item: TX PRIORITY expr  */
#line 163 "proto/rip/config.Y"
                        { RIP_IFACE->tx_priority = (yyvsp[0].i); }
#line 13523 "obj/conf/cf-parse.tab.c"
    break;

  case 1295: /* rip_iface_item: TTL SECURITY bool  */
#line 164 "proto/rip/config.Y"
                        { RIP_IFACE->ttl_security = (yyvsp[0].i); }
#line 13529 "obj/conf/cf-parse.tab.c"
    break;

  case 1296: /* rip_iface_item: TTL SECURITY TX ONLY  */
#line 165 "proto/rip/config.Y"
                        { RIP_IFACE->ttl_security = 2; }
#line 13535 "obj/conf/cf-parse.tab.c"
    break;

  case 1297: /* rip_iface_item: CHECK LINK bool  */
#line 166 "proto/rip/config.Y"
                        { RIP_IFACE->check_link = (yyvsp[0].i); }
#line 13541 "obj/conf/cf-parse.tab.c"
    break;

  case 1298: /* rip_iface_item: BFD bool  */
#line 167 "proto/rip/config.Y"
                        { RIP_IFACE->bfd = (yyvsp[0].i); cf_check_bfd((yyvsp[0].i)); }
#line 13547 "obj/conf/cf-parse.tab.c"
    break;

  case 1299: /* rip_iface_item: AUTHENTICATION rip_auth  */
#line 168 "proto/rip/config.Y"
                           { RIP_IFACE->auth_type = (yyvsp[0].i); if ((yyvsp[0].i)) rip_check_auth(); }
#line 13553 "obj/conf/cf-parse.tab.c"
    break;

  case 1300: /* rip_iface_item: password_list  */
#line 169 "proto/rip/config.Y"
                        { rip_check_auth(); }
#line 13559 "obj/conf/cf-parse.tab.c"
    break;

  case 1301: /* rip_auth: NONE  */
#line 173 "proto/rip/config.Y"
                        { (yyval.i) = RIP_AUTH_NONE; }
#line 13565 "obj/conf/cf-parse.tab.c"
    break;

  case 1302: /* rip_auth: PLAINTEXT  */
#line 174 "proto/rip/config.Y"
                        { (yyval.i) = RIP_AUTH_PLAIN; }
#line 13571 "obj/conf/cf-parse.tab.c"
    break;

  case 1303: /* rip_auth: CRYPTOGRAPHIC  */
#line 175 "proto/rip/config.Y"
                        { (yyval.i) = RIP_AUTH_CRYPTO; }
#line 13577 "obj/conf/cf-parse.tab.c"
    break;

  case 1304: /* rip_auth: MD5  */
#line 176 "proto/rip/config.Y"
                        { (yyval.i) = RIP_AUTH_CRYPTO; }
#line 13583 "obj/conf/cf-parse.tab.c"
    break;

  case 1310: /* dynamic_attr: RIP_METRIC  */
#line 193 "proto/rip/config.Y"
                         { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_RIP_METRIC); }
#line 13589 "obj/conf/cf-parse.tab.c"
    break;

  case 1311: /* dynamic_attr: RIP_TAG  */
#line 194 "proto/rip/config.Y"
                      { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_RIP_TAG); }
#line 13595 "obj/conf/cf-parse.tab.c"
    break;

  case 1313: /* cmd_SHOW_RIP_INTERFACES: SHOW RIP INTERFACES optproto opttext END  */
#line 199 "proto/rip/config.Y"
{ PROTO_WALK_CMD((yyvsp[-2].s), &proto_rip, p) rip_show_interfaces(p, (yyvsp[-1].t)); }
#line 13601 "obj/conf/cf-parse.tab.c"
    break;

  case 1315: /* cmd_SHOW_RIP_NEIGHBORS: SHOW RIP NEIGHBORS optproto opttext END  */
#line 202 "proto/rip/config.Y"
{ PROTO_WALK_CMD((yyvsp[-2].s), &proto_rip, p) rip_show_neighbors(p, (yyvsp[-1].t)); }
#line 13607 "obj/conf/cf-parse.tab.c"
    break;

  case 1317: /* rpki_proto_start: proto_start RPKI  */
#line 43 "proto/rpki/config.Y"
                                   {
  this_proto = proto_config_new(&proto_rpki, (yyvsp[-1].i));
  RPKI_CFG->retry_interval = RPKI_RETRY_INTERVAL;
  RPKI_CFG->refresh_interval = RPKI_REFRESH_INTERVAL;
  RPKI_CFG->expire_interval = RPKI_EXPIRE_INTERVAL;
}
#line 13618 "obj/conf/cf-parse.tab.c"
    break;

  case 1318: /* rpki_proto: rpki_proto_start proto_name '{' rpki_proto_opts '}'  */
#line 50 "proto/rpki/config.Y"
                                                                { rpki_check_config(RPKI_CFG); }
#line 13624 "obj/conf/cf-parse.tab.c"
    break;

  case 1327: /* rpki_proto_item: REFRESH rpki_keep_interval expr  */
#line 64 "proto/rpki/config.Y"
                                   {
     if (rpki_check_refresh_interval((yyvsp[0].i)))
       cf_error(rpki_check_refresh_interval((yyvsp[0].i)));
     RPKI_CFG->refresh_interval = (yyvsp[0].i);
     RPKI_CFG->keep_refresh_interval = (yyvsp[-1].i);
   }
#line 13635 "obj/conf/cf-parse.tab.c"
    break;

  case 1328: /* rpki_proto_item: RETRY rpki_keep_interval expr  */
#line 70 "proto/rpki/config.Y"
                                 {
     if (rpki_check_retry_interval((yyvsp[0].i)))
       cf_error(rpki_check_retry_interval((yyvsp[0].i)));
     RPKI_CFG->retry_interval = (yyvsp[0].i);
     RPKI_CFG->keep_retry_interval = (yyvsp[-1].i);
   }
#line 13646 "obj/conf/cf-parse.tab.c"
    break;

  case 1329: /* rpki_proto_item: EXPIRE rpki_keep_interval expr  */
#line 76 "proto/rpki/config.Y"
                                  {
     if (rpki_check_expire_interval((yyvsp[0].i)))
       cf_error(rpki_check_expire_interval((yyvsp[0].i)));
     RPKI_CFG->expire_interval = (yyvsp[0].i);
     RPKI_CFG->keep_expire_interval = (yyvsp[-1].i);
   }
#line 13657 "obj/conf/cf-parse.tab.c"
    break;

  case 1330: /* rpki_proto_item: IGNORE MAX LENGTH bool  */
#line 82 "proto/rpki/config.Y"
                          { RPKI_CFG->ignore_max_length = (yyvsp[0].i); }
#line 13663 "obj/conf/cf-parse.tab.c"
    break;

  case 1331: /* rpki_keep_interval: %empty  */
#line 86 "proto/rpki/config.Y"
             { (yyval.i) = 0; }
#line 13669 "obj/conf/cf-parse.tab.c"
    break;

  case 1332: /* rpki_keep_interval: KEEP  */
#line 87 "proto/rpki/config.Y"
        { (yyval.i) = 1; }
#line 13675 "obj/conf/cf-parse.tab.c"
    break;

  case 1333: /* rpki_proto_item_port: PORT expr  */
#line 90 "proto/rpki/config.Y"
                                { check_u16((yyvsp[0].i)); RPKI_CFG->port = (yyvsp[0].i); }
#line 13681 "obj/conf/cf-parse.tab.c"
    break;

  case 1334: /* rpki_cache_addr: text  */
#line 93 "proto/rpki/config.Y"
        {
     rpki_check_unused_hostname();
     RPKI_CFG->hostname = (yyvsp[0].t);
   }
#line 13690 "obj/conf/cf-parse.tab.c"
    break;

  case 1335: /* rpki_cache_addr: ipa  */
#line 97 "proto/rpki/config.Y"
       {
     rpki_check_unused_hostname();
     RPKI_CFG->ip = (yyvsp[0].a);
     /* Ensure hostname is filled */
     char *hostname = cfg_allocz(INET6_ADDRSTRLEN + 1);
     bsnprintf(hostname, INET6_ADDRSTRLEN+1, "%I", RPKI_CFG->ip);
     RPKI_CFG->hostname = hostname;
   }
#line 13703 "obj/conf/cf-parse.tab.c"
    break;

  case 1338: /* rpki_transport_tcp_init: %empty  */
#line 113 "proto/rpki/config.Y"
{
  rpki_check_unused_transport();
  RPKI_CFG->tr_config.spec = cfg_allocz(sizeof(struct rpki_tr_tcp_config));
  RPKI_CFG->tr_config.type = RPKI_TR_TCP;
}
#line 13713 "obj/conf/cf-parse.tab.c"
    break;

  case 1339: /* rpki_transport_ssh_init: %empty  */
#line 120 "proto/rpki/config.Y"
{
#if HAVE_LIBSSH
  rpki_check_unused_transport();
  RPKI_CFG->tr_config.spec = cfg_allocz(sizeof(struct rpki_tr_ssh_config));
  RPKI_CFG->tr_config.type = RPKI_TR_SSH;
#else
  cf_error("This build doesn't support SSH");
#endif
}
#line 13727 "obj/conf/cf-parse.tab.c"
    break;

  case 1342: /* rpki_transport_ssh_item: BIRD PRIVATE KEY text  */
#line 136 "proto/rpki/config.Y"
                          { RPKI_TR_SSH_CFG->bird_private_key = (yyvsp[0].t); }
#line 13733 "obj/conf/cf-parse.tab.c"
    break;

  case 1343: /* rpki_transport_ssh_item: REMOTE PUBLIC KEY text  */
#line 137 "proto/rpki/config.Y"
                          { RPKI_TR_SSH_CFG->cache_public_key = (yyvsp[0].t); }
#line 13739 "obj/conf/cf-parse.tab.c"
    break;

  case 1344: /* rpki_transport_ssh_item: USER text  */
#line 138 "proto/rpki/config.Y"
                          { RPKI_TR_SSH_CFG->user = (yyvsp[0].t); }
#line 13745 "obj/conf/cf-parse.tab.c"
    break;

  case 1345: /* rpki_transport_ssh_check: %empty  */
#line 142 "proto/rpki/config.Y"
{
  if (RPKI_TR_SSH_CFG->user == NULL)
    cf_error("User must be set");
}
#line 13754 "obj/conf/cf-parse.tab.c"
    break;

  case 1347: /* static_proto_start: proto_start STATIC  */
#line 57 "proto/static/config.Y"
{
  this_proto = proto_config_new(&proto_static, (yyvsp[-1].i));
  init_list(&STATIC_CFG->routes);
}
#line 13763 "obj/conf/cf-parse.tab.c"
    break;

  case 1350: /* static_proto: static_proto proto_channel ';'  */
#line 65 "proto/static/config.Y"
                                  { this_proto->net_type = (yyvsp[-1].cc)->net_type; }
#line 13769 "obj/conf/cf-parse.tab.c"
    break;

  case 1351: /* static_proto: static_proto CHECK LINK bool ';'  */
#line 66 "proto/static/config.Y"
                                    { STATIC_CFG->check_link = (yyvsp[-1].i); }
#line 13775 "obj/conf/cf-parse.tab.c"
    break;

  case 1352: /* static_proto: static_proto IGP TABLE rtable ';'  */
#line 67 "proto/static/config.Y"
                                     {
    if ((yyvsp[-1].r)->addr_type == NET_IP4)
      STATIC_CFG->igp_table_ip4 = (yyvsp[-1].r);
    else if ((yyvsp[-1].r)->addr_type == NET_IP6)
      STATIC_CFG->igp_table_ip6 = (yyvsp[-1].r);
    else
      cf_error("Incompatible IGP table type");
   }
#line 13788 "obj/conf/cf-parse.tab.c"
    break;

  case 1353: /* static_proto: static_proto stat_route stat_route_opt_list ';'  */
#line 75 "proto/static/config.Y"
                                                   { static_route_finish(); }
#line 13794 "obj/conf/cf-parse.tab.c"
    break;

  case 1354: /* stat_nexthop: VIA ipa ipa_scope  */
#line 79 "proto/static/config.Y"
                      {
      this_snh = static_nexthop_new();
      this_snh->via = (yyvsp[-1].a);
      this_snh->iface = (yyvsp[0].iface);
    }
#line 13804 "obj/conf/cf-parse.tab.c"
    break;

  case 1355: /* stat_nexthop: VIA TEXT  */
#line 84 "proto/static/config.Y"
             {
      this_snh = static_nexthop_new();
      this_snh->via = IPA_NONE;
      this_snh->iface = if_get_by_name((yyvsp[0].t));
    }
#line 13814 "obj/conf/cf-parse.tab.c"
    break;

  case 1356: /* stat_nexthop: stat_nexthop MPLS label_stack  */
#line 89 "proto/static/config.Y"
                                  {
    this_snh->mls = (yyvsp[0].mls);
  }
#line 13822 "obj/conf/cf-parse.tab.c"
    break;

  case 1357: /* stat_nexthop: stat_nexthop ONLINK bool  */
#line 92 "proto/static/config.Y"
                             {
    this_snh->onlink = (yyvsp[0].i);
  }
#line 13830 "obj/conf/cf-parse.tab.c"
    break;

  case 1358: /* stat_nexthop: stat_nexthop WEIGHT expr  */
#line 95 "proto/static/config.Y"
                             {
    this_snh->weight = (yyvsp[0].i) - 1;
    if (((yyvsp[0].i)<1) || ((yyvsp[0].i)>256)) cf_error("Weight must be in range 1-256");
  }
#line 13839 "obj/conf/cf-parse.tab.c"
    break;

  case 1359: /* stat_nexthop: stat_nexthop BFD bool  */
#line 99 "proto/static/config.Y"
                          {
    this_snh->use_bfd = (yyvsp[0].i); cf_check_bfd((yyvsp[0].i));
  }
#line 13847 "obj/conf/cf-parse.tab.c"
    break;

  case 1362: /* stat_route0: ROUTE net_any  */
#line 109 "proto/static/config.Y"
                           {
     this_srt = cfg_allocz(sizeof(struct static_route));
     add_tail(&STATIC_CFG->routes, &this_srt->n);
     this_srt->net = (yyvsp[0].net_ptr);
     this_srt_cmds = NULL;
     this_srt_last_cmd = NULL;
     this_srt->mp_next = NULL;
     this_snh = NULL;
  }
#line 13861 "obj/conf/cf-parse.tab.c"
    break;

  case 1364: /* stat_route: stat_route0 RECURSIVE ipa  */
#line 122 "proto/static/config.Y"
                             {
      this_srt->dest = RTDX_RECURSIVE;
      this_srt->via = (yyvsp[0].a);
   }
#line 13870 "obj/conf/cf-parse.tab.c"
    break;

  case 1365: /* stat_route: stat_route0 RECURSIVE ipa MPLS label_stack  */
#line 126 "proto/static/config.Y"
                                              {
      this_srt->dest = RTDX_RECURSIVE;
      this_srt->via = (yyvsp[-2].a);
      this_srt->mls = (yyvsp[0].mls);
   }
#line 13880 "obj/conf/cf-parse.tab.c"
    break;

  case 1366: /* stat_route: stat_route0  */
#line 131 "proto/static/config.Y"
                                { this_srt->dest = RTD_NONE; }
#line 13886 "obj/conf/cf-parse.tab.c"
    break;

  case 1367: /* stat_route: stat_route0 DROP  */
#line 132 "proto/static/config.Y"
                                { this_srt->dest = RTD_BLACKHOLE; }
#line 13892 "obj/conf/cf-parse.tab.c"
    break;

  case 1368: /* stat_route: stat_route0 REJECT  */
#line 133 "proto/static/config.Y"
                                { this_srt->dest = RTD_UNREACHABLE; }
#line 13898 "obj/conf/cf-parse.tab.c"
    break;

  case 1369: /* stat_route: stat_route0 BLACKHOLE  */
#line 134 "proto/static/config.Y"
                                { this_srt->dest = RTD_BLACKHOLE; }
#line 13904 "obj/conf/cf-parse.tab.c"
    break;

  case 1370: /* stat_route: stat_route0 UNREACHABLE  */
#line 135 "proto/static/config.Y"
                                { this_srt->dest = RTD_UNREACHABLE; }
#line 13910 "obj/conf/cf-parse.tab.c"
    break;

  case 1371: /* stat_route: stat_route0 PROHIBIT  */
#line 136 "proto/static/config.Y"
                                { this_srt->dest = RTD_PROHIBIT; }
#line 13916 "obj/conf/cf-parse.tab.c"
    break;

  case 1372: /* stat_route_item: cmd  */
#line 140 "proto/static/config.Y"
       {
     if (this_srt_last_cmd)
       this_srt_last_cmd->next = (yyvsp[0].x);
     else
       this_srt_cmds = (yyvsp[0].x);
     this_srt_last_cmd = (yyvsp[0].x);
   }
#line 13928 "obj/conf/cf-parse.tab.c"
    break;

  case 1378: /* cmd_SHOW_STATIC: SHOW STATIC optproto END  */
#line 161 "proto/static/config.Y"
{ PROTO_WALK_CMD((yyvsp[-1].s), &proto_static, p) static_show(p); }
#line 13934 "obj/conf/cf-parse.tab.c"
    break;

  case 1380: /* kern_sys_item: KERNEL TABLE expr  */
#line 26 "sysdep/linux/netlink.Y"
                     { THIS_KRT->sys.table_id = (yyvsp[0].i); }
#line 13940 "obj/conf/cf-parse.tab.c"
    break;

  case 1381: /* kern_sys_item: METRIC expr  */
#line 27 "sysdep/linux/netlink.Y"
               { THIS_KRT->sys.metric = (yyvsp[0].i); }
#line 13946 "obj/conf/cf-parse.tab.c"
    break;

  case 1382: /* kern_sys_item: NETLINK RX BUFFER expr  */
#line 28 "sysdep/linux/netlink.Y"
                          { THIS_KRT->sys.netlink_rx_buffer = (yyvsp[0].i); }
#line 13952 "obj/conf/cf-parse.tab.c"
    break;

  case 1383: /* dynamic_attr: KRT_PREFSRC  */
#line 31 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_IP_ADDRESS, T_IP, EA_KRT_PREFSRC); }
#line 13958 "obj/conf/cf-parse.tab.c"
    break;

  case 1384: /* dynamic_attr: KRT_REALM  */
#line 32 "sysdep/linux/netlink.Y"
                        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_REALM); }
#line 13964 "obj/conf/cf-parse.tab.c"
    break;

  case 1385: /* dynamic_attr: KRT_SCOPE  */
#line 33 "sysdep/linux/netlink.Y"
                        { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_SCOPE); }
#line 13970 "obj/conf/cf-parse.tab.c"
    break;

  case 1386: /* dynamic_attr: KRT_MTU  */
#line 35 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_MTU); }
#line 13976 "obj/conf/cf-parse.tab.c"
    break;

  case 1387: /* dynamic_attr: KRT_WINDOW  */
#line 36 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_WINDOW); }
#line 13982 "obj/conf/cf-parse.tab.c"
    break;

  case 1388: /* dynamic_attr: KRT_RTT  */
#line 37 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_RTT); }
#line 13988 "obj/conf/cf-parse.tab.c"
    break;

  case 1389: /* dynamic_attr: KRT_RTTVAR  */
#line 38 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_RTTVAR); }
#line 13994 "obj/conf/cf-parse.tab.c"
    break;

  case 1390: /* dynamic_attr: KRT_SSTRESH  */
#line 39 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_SSTRESH); }
#line 14000 "obj/conf/cf-parse.tab.c"
    break;

  case 1391: /* dynamic_attr: KRT_CWND  */
#line 40 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_CWND); }
#line 14006 "obj/conf/cf-parse.tab.c"
    break;

  case 1392: /* dynamic_attr: KRT_ADVMSS  */
#line 41 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_ADVMSS); }
#line 14012 "obj/conf/cf-parse.tab.c"
    break;

  case 1393: /* dynamic_attr: KRT_REORDERING  */
#line 42 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_REORDERING); }
#line 14018 "obj/conf/cf-parse.tab.c"
    break;

  case 1394: /* dynamic_attr: KRT_HOPLIMIT  */
#line 43 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_HOPLIMIT); }
#line 14024 "obj/conf/cf-parse.tab.c"
    break;

  case 1395: /* dynamic_attr: KRT_INITCWND  */
#line 44 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_INITCWND); }
#line 14030 "obj/conf/cf-parse.tab.c"
    break;

  case 1396: /* dynamic_attr: KRT_RTO_MIN  */
#line 45 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_RTO_MIN); }
#line 14036 "obj/conf/cf-parse.tab.c"
    break;

  case 1397: /* dynamic_attr: KRT_INITRWND  */
#line 46 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_INITRWND); }
#line 14042 "obj/conf/cf-parse.tab.c"
    break;

  case 1398: /* dynamic_attr: KRT_QUICKACK  */
#line 47 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_QUICKACK); }
#line 14048 "obj/conf/cf-parse.tab.c"
    break;

  case 1399: /* dynamic_attr: KRT_LOCK_MTU  */
#line 51 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(2, T_BOOL, EA_KRT_LOCK); }
#line 14054 "obj/conf/cf-parse.tab.c"
    break;

  case 1400: /* dynamic_attr: KRT_LOCK_WINDOW  */
#line 52 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(3, T_BOOL, EA_KRT_LOCK); }
#line 14060 "obj/conf/cf-parse.tab.c"
    break;

  case 1401: /* dynamic_attr: KRT_LOCK_RTT  */
#line 53 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(4, T_BOOL, EA_KRT_LOCK); }
#line 14066 "obj/conf/cf-parse.tab.c"
    break;

  case 1402: /* dynamic_attr: KRT_LOCK_RTTVAR  */
#line 54 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(5, T_BOOL, EA_KRT_LOCK); }
#line 14072 "obj/conf/cf-parse.tab.c"
    break;

  case 1403: /* dynamic_attr: KRT_LOCK_SSTRESH  */
#line 55 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(6, T_BOOL, EA_KRT_LOCK); }
#line 14078 "obj/conf/cf-parse.tab.c"
    break;

  case 1404: /* dynamic_attr: KRT_LOCK_CWND  */
#line 56 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(7, T_BOOL, EA_KRT_LOCK); }
#line 14084 "obj/conf/cf-parse.tab.c"
    break;

  case 1405: /* dynamic_attr: KRT_LOCK_ADVMSS  */
#line 57 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(8, T_BOOL, EA_KRT_LOCK); }
#line 14090 "obj/conf/cf-parse.tab.c"
    break;

  case 1406: /* dynamic_attr: KRT_LOCK_REORDERING  */
#line 58 "sysdep/linux/netlink.Y"
                                  { (yyval.fda) = f_new_dynamic_attr_bit(9, T_BOOL, EA_KRT_LOCK); }
#line 14096 "obj/conf/cf-parse.tab.c"
    break;

  case 1407: /* dynamic_attr: KRT_LOCK_HOPLIMIT  */
#line 59 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(10, T_BOOL, EA_KRT_LOCK); }
#line 14102 "obj/conf/cf-parse.tab.c"
    break;

  case 1408: /* dynamic_attr: KRT_LOCK_RTO_MIN  */
#line 60 "sysdep/linux/netlink.Y"
                               { (yyval.fda) = f_new_dynamic_attr_bit(13, T_BOOL, EA_KRT_LOCK); }
#line 14108 "obj/conf/cf-parse.tab.c"
    break;

  case 1409: /* dynamic_attr: KRT_FEATURE_ECN  */
#line 62 "sysdep/linux/netlink.Y"
                                { (yyval.fda) = f_new_dynamic_attr_bit(0, T_BOOL, EA_KRT_FEATURES); }
#line 14114 "obj/conf/cf-parse.tab.c"
    break;

  case 1410: /* dynamic_attr: KRT_FEATURE_ALLFRAG  */
#line 63 "sysdep/linux/netlink.Y"
                                  { (yyval.fda) = f_new_dynamic_attr(3, T_BOOL, EA_KRT_FEATURES); }
#line 14120 "obj/conf/cf-parse.tab.c"
    break;

  case 1412: /* log_begin: %empty  */
#line 33 "sysdep/unix/config.Y"
           { this_log = cfg_allocz(sizeof(struct log_config)); }
#line 14126 "obj/conf/cf-parse.tab.c"
    break;

  case 1413: /* log_config: LOG log_begin log_file log_mask ';'  */
#line 35 "sysdep/unix/config.Y"
                                                {
    this_log->mask = (yyvsp[-1].i);
    add_tail(&new_config->logfiles, &this_log->n);
  }
#line 14135 "obj/conf/cf-parse.tab.c"
    break;

  case 1414: /* syslog_name: NAME text  */
#line 42 "sysdep/unix/config.Y"
             { (yyval.t) = (yyvsp[0].t); }
#line 14141 "obj/conf/cf-parse.tab.c"
    break;

  case 1415: /* syslog_name: %empty  */
#line 43 "sysdep/unix/config.Y"
   { (yyval.t) = bird_name; }
#line 14147 "obj/conf/cf-parse.tab.c"
    break;

  case 1417: /* log_limit: expr text  */
#line 48 "sysdep/unix/config.Y"
             { this_log->limit = (yyvsp[-1].i); this_log->backup = (yyvsp[0].t); }
#line 14153 "obj/conf/cf-parse.tab.c"
    break;

  case 1418: /* log_file: text log_limit  */
#line 52 "sysdep/unix/config.Y"
                  {
     if (!parse_and_exit)
     {
       this_log->rf = rf_open(new_config->pool, (yyvsp[-1].t), "a");
       if (!this_log->rf) cf_error("Unable to open log file '%s': %m", (yyvsp[-1].t));
       this_log->fh = rf_file(this_log->rf);
     }
     this_log->pos = -1;
     this_log->filename = (yyvsp[-1].t);
   }
#line 14168 "obj/conf/cf-parse.tab.c"
    break;

  case 1419: /* log_file: SYSLOG syslog_name  */
#line 62 "sysdep/unix/config.Y"
                      { this_log->fh = NULL; new_config->syslog_name = (yyvsp[0].t); }
#line 14174 "obj/conf/cf-parse.tab.c"
    break;

  case 1420: /* log_file: STDERR  */
#line 63 "sysdep/unix/config.Y"
          { this_log->fh = stderr; }
#line 14180 "obj/conf/cf-parse.tab.c"
    break;

  case 1421: /* log_mask: ALL  */
#line 67 "sysdep/unix/config.Y"
       { (yyval.i) = ~0; }
#line 14186 "obj/conf/cf-parse.tab.c"
    break;

  case 1422: /* log_mask: '{' log_mask_list '}'  */
#line 68 "sysdep/unix/config.Y"
                         { (yyval.i) = (yyvsp[-1].i); }
#line 14192 "obj/conf/cf-parse.tab.c"
    break;

  case 1423: /* log_mask_list: log_cat  */
#line 72 "sysdep/unix/config.Y"
           { (yyval.i) = 1 << (yyvsp[0].i); }
#line 14198 "obj/conf/cf-parse.tab.c"
    break;

  case 1424: /* log_mask_list: log_mask_list ',' log_cat  */
#line 73 "sysdep/unix/config.Y"
                             { (yyval.i) = (yyvsp[-2].i) | (1 << (yyvsp[0].i)); }
#line 14204 "obj/conf/cf-parse.tab.c"
    break;

  case 1425: /* log_cat: DEBUG  */
#line 77 "sysdep/unix/config.Y"
         { (yyval.i) = L_DEBUG[0]; }
#line 14210 "obj/conf/cf-parse.tab.c"
    break;

  case 1426: /* log_cat: TRACE  */
#line 78 "sysdep/unix/config.Y"
         { (yyval.i) = L_TRACE[0]; }
#line 14216 "obj/conf/cf-parse.tab.c"
    break;

  case 1427: /* log_cat: INFO  */
#line 79 "sysdep/unix/config.Y"
        { (yyval.i) = L_INFO[0]; }
#line 14222 "obj/conf/cf-parse.tab.c"
    break;

  case 1428: /* log_cat: REMOTE  */
#line 80 "sysdep/unix/config.Y"
          { (yyval.i) = L_REMOTE[0]; }
#line 14228 "obj/conf/cf-parse.tab.c"
    break;

  case 1429: /* log_cat: WARNING  */
#line 81 "sysdep/unix/config.Y"
           { (yyval.i) = L_WARN[0]; }
#line 14234 "obj/conf/cf-parse.tab.c"
    break;

  case 1430: /* log_cat: ERROR  */
#line 82 "sysdep/unix/config.Y"
         { (yyval.i) = L_ERR[0]; }
#line 14240 "obj/conf/cf-parse.tab.c"
    break;

  case 1431: /* log_cat: AUTH  */
#line 83 "sysdep/unix/config.Y"
        { (yyval.i) = L_AUTH[0]; }
#line 14246 "obj/conf/cf-parse.tab.c"
    break;

  case 1432: /* log_cat: FATAL  */
#line 84 "sysdep/unix/config.Y"
         { (yyval.i) = L_FATAL[0]; }
#line 14252 "obj/conf/cf-parse.tab.c"
    break;

  case 1433: /* log_cat: BUG  */
#line 85 "sysdep/unix/config.Y"
       { (yyval.i) = L_BUG[0]; }
#line 14258 "obj/conf/cf-parse.tab.c"
    break;

  case 1435: /* mrtdump_base: MRTDUMP PROTOCOLS mrtdump_mask ';'  */
#line 92 "sysdep/unix/config.Y"
                                      { new_config->proto_default_mrtdump = (yyvsp[-1].i); }
#line 14264 "obj/conf/cf-parse.tab.c"
    break;

  case 1436: /* mrtdump_base: MRTDUMP text ';'  */
#line 93 "sysdep/unix/config.Y"
                    {
     if (!parse_and_exit)
     {
       struct rfile *f = rf_open(new_config->pool, (yyvsp[-1].t), "a");
       if (!f) cf_error("Unable to open MRTDump file '%s': %m", (yyvsp[-1].t));
       new_config->mrtdump_file = rf_fileno(f);
     }
   }
#line 14277 "obj/conf/cf-parse.tab.c"
    break;

  case 1438: /* debug_unix: DEBUG LATENCY bool  */
#line 107 "sysdep/unix/config.Y"
                      { new_config->latency_debug = (yyvsp[0].i); }
#line 14283 "obj/conf/cf-parse.tab.c"
    break;

  case 1439: /* debug_unix: DEBUG LATENCY LIMIT expr_us  */
#line 108 "sysdep/unix/config.Y"
                               { new_config->latency_limit = (yyvsp[0].time); }
#line 14289 "obj/conf/cf-parse.tab.c"
    break;

  case 1440: /* debug_unix: WATCHDOG WARNING expr_us  */
#line 109 "sysdep/unix/config.Y"
                            { new_config->watchdog_warning = (yyvsp[0].time); }
#line 14295 "obj/conf/cf-parse.tab.c"
    break;

  case 1441: /* debug_unix: WATCHDOG TIMEOUT expr_us  */
#line 110 "sysdep/unix/config.Y"
                            { new_config->watchdog_timeout = ((yyvsp[0].time) + 999999) TO_S; }
#line 14301 "obj/conf/cf-parse.tab.c"
    break;

  case 1443: /* cmd_CONFIGURE: CONFIGURE cfg_name cfg_timeout END  */
#line 119 "sysdep/unix/config.Y"
{ cmd_reconfig((yyvsp[-2].t), RECONFIG_HARD, (yyvsp[-1].i)); }
#line 14307 "obj/conf/cf-parse.tab.c"
    break;

  case 1445: /* cmd_CONFIGURE_SOFT: CONFIGURE SOFT cfg_name cfg_timeout END  */
#line 122 "sysdep/unix/config.Y"
{ cmd_reconfig((yyvsp[-2].t), RECONFIG_SOFT, (yyvsp[-1].i)); }
#line 14313 "obj/conf/cf-parse.tab.c"
    break;

  case 1447: /* cmd_CONFIGURE_CONFIRM: CONFIGURE CONFIRM END  */
#line 129 "sysdep/unix/config.Y"
{ cmd_reconfig_confirm(); }
#line 14319 "obj/conf/cf-parse.tab.c"
    break;

  case 1449: /* cmd_CONFIGURE_UNDO: CONFIGURE UNDO END  */
#line 132 "sysdep/unix/config.Y"
{ cmd_reconfig_undo(); }
#line 14325 "obj/conf/cf-parse.tab.c"
    break;

  case 1451: /* cmd_CONFIGURE_STATUS: CONFIGURE STATUS END  */
#line 135 "sysdep/unix/config.Y"
{ cmd_reconfig_status(); }
#line 14331 "obj/conf/cf-parse.tab.c"
    break;

  case 1453: /* cmd_CONFIGURE_CHECK: CONFIGURE CHECK cfg_name END  */
#line 138 "sysdep/unix/config.Y"
{ cmd_check_config((yyvsp[-1].t)); }
#line 14337 "obj/conf/cf-parse.tab.c"
    break;

  case 1455: /* cmd_DOWN: DOWN END  */
#line 141 "sysdep/unix/config.Y"
{ cmd_shutdown(); }
#line 14343 "obj/conf/cf-parse.tab.c"
    break;

  case 1457: /* cmd_GRACEFUL_RESTART: GRACEFUL RESTART END  */
#line 146 "sysdep/unix/config.Y"
{ cmd_graceful_restart(); }
#line 14349 "obj/conf/cf-parse.tab.c"
    break;

  case 1458: /* cfg_name: %empty  */
#line 150 "sysdep/unix/config.Y"
               { (yyval.t) = NULL; }
#line 14355 "obj/conf/cf-parse.tab.c"
    break;

  case 1460: /* cfg_timeout: %empty  */
#line 155 "sysdep/unix/config.Y"
               { (yyval.i) = 0; }
#line 14361 "obj/conf/cf-parse.tab.c"
    break;

  case 1461: /* cfg_timeout: TIMEOUT  */
#line 156 "sysdep/unix/config.Y"
           { (yyval.i) = UNIX_DEFAULT_CONFIGURE_TIMEOUT; }
#line 14367 "obj/conf/cf-parse.tab.c"
    break;

  case 1462: /* cfg_timeout: TIMEOUT expr  */
#line 157 "sysdep/unix/config.Y"
                { (yyval.i) = (yyvsp[0].i); }
#line 14373 "obj/conf/cf-parse.tab.c"
    break;

  case 1464: /* kern_proto_start: proto_start KERNEL  */
#line 43 "sysdep/unix/krt.Y"
                                     {
     this_proto = krt_init_config((yyvsp[-1].i));
}
#line 14381 "obj/conf/cf-parse.tab.c"
    break;

  case 1467: /* kern_mp_limit: %empty  */
#line 52 "sysdep/unix/krt.Y"
               { (yyval.i) = KRT_DEFAULT_ECMP_LIMIT; }
#line 14387 "obj/conf/cf-parse.tab.c"
    break;

  case 1468: /* kern_mp_limit: LIMIT expr  */
#line 53 "sysdep/unix/krt.Y"
               { (yyval.i) = (yyvsp[0].i); if (((yyvsp[0].i) <= 0) || ((yyvsp[0].i) > 255)) cf_error("Merge paths limit must be in range 1-255"); }
#line 14393 "obj/conf/cf-parse.tab.c"
    break;

  case 1470: /* kern_item: proto_channel  */
#line 58 "sysdep/unix/krt.Y"
                 { this_proto->net_type = (yyvsp[0].cc)->net_type; }
#line 14399 "obj/conf/cf-parse.tab.c"
    break;

  case 1471: /* kern_item: PERSIST bool  */
#line 59 "sysdep/unix/krt.Y"
                { THIS_KRT->persist = (yyvsp[0].i); }
#line 14405 "obj/conf/cf-parse.tab.c"
    break;

  case 1472: /* kern_item: SCAN TIME expr  */
#line 60 "sysdep/unix/krt.Y"
                  {
      /* Scan time of 0 means scan on startup only */
      THIS_KRT->scan_time = (yyvsp[0].i) S_;
   }
#line 14414 "obj/conf/cf-parse.tab.c"
    break;

  case 1473: /* kern_item: LEARN bool  */
#line 64 "sysdep/unix/krt.Y"
              {
      THIS_KRT->learn = (yyvsp[0].i);
#ifndef KRT_ALLOW_LEARN
      if ((yyvsp[0].i))
	cf_error("Learning of kernel routes not supported on this platform");
#endif
   }
#line 14426 "obj/conf/cf-parse.tab.c"
    break;

  case 1474: /* kern_item: GRACEFUL RESTART bool  */
#line 71 "sysdep/unix/krt.Y"
                         { THIS_KRT->graceful_restart = (yyvsp[0].i); }
#line 14432 "obj/conf/cf-parse.tab.c"
    break;

  case 1475: /* kern_item: MERGE PATHS bool kern_mp_limit  */
#line 72 "sysdep/unix/krt.Y"
                                  {
      THIS_KRT->merge_paths = (yyvsp[-1].i) ? (yyvsp[0].i) : 0;
#ifndef KRT_ALLOW_MERGE_PATHS
      if ((yyvsp[-1].i))
	cf_error("Path merging not supported on this platform");
#endif
   }
#line 14444 "obj/conf/cf-parse.tab.c"
    break;

  case 1477: /* kif_proto_start: proto_start DEVICE  */
#line 85 "sysdep/unix/krt.Y"
                                    { this_proto = kif_init_config((yyvsp[-1].i)); }
#line 14450 "obj/conf/cf-parse.tab.c"
    break;

  case 1482: /* kif_item: SCAN TIME expr  */
#line 94 "sysdep/unix/krt.Y"
                  {
      /* Scan time of 0 means scan on startup only */
      THIS_KIF->scan_time = (yyvsp[0].i) S_;
   }
#line 14459 "obj/conf/cf-parse.tab.c"
    break;

  case 1483: /* kif_iface_start: %empty  */
#line 101 "sysdep/unix/krt.Y"
{
  this_ipatt = cfg_allocz(sizeof(struct kif_iface_config));
  add_tail(&THIS_KIF->iface_list, NODE this_ipatt);
  init_list(&this_ipatt->ipn_list);
}
#line 14469 "obj/conf/cf-parse.tab.c"
    break;

  case 1484: /* kif_iface_item: PREFERRED ipa  */
#line 108 "sysdep/unix/krt.Y"
                 { kif_set_preferred((yyvsp[0].a)); }
#line 14475 "obj/conf/cf-parse.tab.c"
    break;

  case 1490: /* dynamic_attr: KRT_SOURCE  */
#line 125 "sysdep/unix/krt.Y"
                         { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_SOURCE); }
#line 14481 "obj/conf/cf-parse.tab.c"
    break;

  case 1491: /* dynamic_attr: KRT_METRIC  */
#line 126 "sysdep/unix/krt.Y"
                         { (yyval.fda) = f_new_dynamic_attr(EAF_TYPE_INT, T_INT, EA_KRT_METRIC); }
#line 14487 "obj/conf/cf-parse.tab.c"
    break;


#line 14491 "obj/conf/cf-parse.tab.c"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 50 "conf/gen_parser.m4"

#line 397 "conf/confbase.Y"
/* C Code from conf/confbase.Y */

#line 206 "conf/flowspec.Y"
/* C Code from conf/flowspec.Y */

#line 937 "nest/config.Y"
/* C Code from nest/config.Y */

#line 189 "proto/bfd/config.Y"
/* C Code from proto/bfd/config.Y */

#line 182 "proto/babel/config.Y"
/* C Code from proto/babel/config.Y */

#line 370 "proto/bgp/config.Y"
/* C Code from proto/bgp/config.Y */

#line 66 "proto/mrt/config.Y"
/* C Code from proto/mrt/config.Y */

#line 562 "proto/ospf/config.Y"
/* C Code from proto/ospf/config.Y */

#line 59 "proto/perf/config.Y"
/* C Code from proto/perf/config.Y */

#line 46 "proto/pipe/config.Y"
/* C Code from proto/pipe/config.Y */

#line 342 "proto/radv/config.Y"
/* C Code from proto/radv/config.Y */

#line 205 "proto/rip/config.Y"
/* C Code from proto/rip/config.Y */

#line 147 "proto/rpki/config.Y"
/* C Code from proto/rpki/config.Y */

#line 163 "proto/static/config.Y"
/* C Code from proto/static/config.Y */

#line 66 "sysdep/linux/netlink.Y"
/* C Code from sysdep/linux/netlink.Y */

#line 160 "sysdep/unix/config.Y"
/* C Code from sysdep/unix/config.Y */

#line 128 "sysdep/unix/krt.Y"
/* C Code from sysdep/unix/krt.Y */

