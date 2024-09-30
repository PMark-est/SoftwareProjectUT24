/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

/* 
 *  IMS Open Corpus Workbench (CWB)
 *  Copyright (C) 1993-2006 by IMS, University of Stuttgart
 *  Copyright (C) 2007-     by the respective contributers (see file AUTHORS)
 * 
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2, or (at your option) any later
 *  version.
 * 
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 *  Public License for more details (in the file "COPYING", or available via
 *  WWW at http://www.gnu.org/copyleft/gpl.html).
 */


#include <sys/time.h>
#ifndef _WIN64
#  include <sys/resource.h>
#endif
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "../cl/globals.h"
#include "../cl/special-chars.h"
#include "../cl/attributes.h"

#include "cqp.h"
#include "options.h"
#include "ranges.h"
#include "symtab.h"
#include "treemacros.h"
#include "tree.h"
#include "eval.h"
#include "corpmanag.h"
#include "regex2dfa.h"
#include "builtins.h"
#include "groups.h"
#include "targets.h"
#include "attlist.h"
#include "concordance.h"
#include "output.h"
#include "print-modes.h"
#include "variables.h"

#include "parse_actions.h"

/* CQPserver user authentication */
#include "../CQi/auth.h"

/* macro expansion */
#include "macro.h"
 
/* ============================================================ YACC INTERFACE */

extern int yychar;

extern int yylex(void);

/** 
 * Parser error action. Emits a CQP syntax error, then turns off generate_code.
 * @see   generate_code
 * @param s                  Error message to show.
 */
void 
yyerror(const char *s)
{
  cqpmessage(Error, "CQP Syntax Error: %s\n\t%s <--", s, QueryBuffer);
  generate_code = 0;
}

void 
warn_query_lock_violation(void) 
{
  if (which_app != cqpserver)
    fprintf(stderr, "WARNING: query lock violation attempted\n");
  query_lock_violation++;       /* this is for the CQPserver */
}



/**
 * Deletes any still-pending input to the CQP parser, 
 * to the next semi-colon or end of line.
 *
 * The parser state is then ready to move on with what
 * will hopefully not be more invalid input.
 */ 
void
synchronize(void)
{
  /* function may be made into a null operation by defining this
   * constant in the make-configuration file. See the Makefile.
   */
#ifndef CQP_COMPILE_WITHOUT_SYNCHRONIZE

  /* stores enable_macros status */
  int stored_macro_status; 

  /* delete macro buffers & disable macro expansion while sync'ing */
  delete_macro_buffers(1); /* print stack trace on STDERR */
  stored_macro_status = enable_macros;
  enable_macros = 0;

  /* read and throw away characters till we have cleared away the rest 
     of the current command (which is non-actionable) to get back on track. */
  if (cqp_input_string) {
    fprintf(stderr, "Ignoring subsequent input until end of line ... \n");
    while (!(yychar <= 0))
      yychar = yylex();
  }
  else {
    fprintf(stderr, "Ignoring subsequent input until next ';'...\n");
    while (!(yychar <= 0 || yychar == ';'))
      yychar = yylex();
  }
  /* N.B. The error messages classically said "synchronizing",
     but that's programmer, not user terminology! */

  /* restore enable_macros to previous value */
  enable_macros = stored_macro_status; 

#endif /* defined CQP_COMPILE_WITHOUT_SYNCHRONIZE */
}
/* end of function synchronize() */


#define YYERROR_VERBOSE


#line 208 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    QID = 259,
    NQRID = 260,
    LABEL = 261,
    STRING = 262,
    FLAG = 263,
    TAGSTART = 264,
    TAGEND = 265,
    VARIABLE = 266,
    IPAddress = 267,
    IPSubnet = 268,
    INTEGER = 269,
    DOUBLEFLOAT = 270,
    FIELD = 271,
    FIELDLABEL = 272,
    ANCHORTAG = 273,
    ANCHORENDTAG = 274,
    SEARCH_STRATEGY = 275,
    TAB_SYM = 276,
    CAT_SYM = 277,
    DEFINE_SYM = 278,
    DIFF_SYM = 279,
    DISCARD_SYM = 280,
    EXPAND_SYM = 281,
    EXIT_SYM = 282,
    INTER_SYM = 283,
    JOIN_SYM = 284,
    SUBSET_SYM = 285,
    LEFT_SYM = 286,
    RIGHT_SYM = 287,
    SAVE_SYM = 288,
    SHOW_SYM = 289,
    CD_SYM = 290,
    TO_SYM = 291,
    WITHIN_SYM = 292,
    SET_SYM = 293,
    EXEC_SYM = 294,
    CUT_SYM = 295,
    INFO_SYM = 296,
    GROUP_SYM = 297,
    WHERE_SYM = 298,
    ESCAPE_SYM = 299,
    MEET_SYM = 300,
    UNION_SYM = 301,
    MU_SYM = 302,
    SORT_SYM = 303,
    COUNT_SYM = 304,
    ASC_SYM = 305,
    DESC_SYM = 306,
    REVERSE_SYM = 307,
    BY_SYM = 308,
    FOREACH_SYM = 309,
    ON_SYM = 310,
    YES_SYM = 311,
    OFF_SYM = 312,
    NO_SYM = 313,
    SLEEP_SYM = 314,
    REDUCE_SYM = 315,
    MAXIMAL_SYM = 316,
    WITH_SYM = 317,
    WITHOUT_SYM = 318,
    DELETE_SYM = 319,
    SIZE_SYM = 320,
    DUMP_SYM = 321,
    UNDUMP_SYM = 322,
    TABULATE_SYM = 323,
    NOT_SYM = 324,
    CONTAINS_SYM = 325,
    MATCHES_SYM = 326,
    GCDEL = 327,
    APPEND = 328,
    LEFT_APPEND = 329,
    LET = 330,
    GET = 331,
    NEQ = 332,
    IMPLIES = 333,
    RE_PAREN = 334,
    EOL_SYM = 335,
    ELLIPSIS = 336,
    MATCHALL = 337,
    LCSTART = 338,
    LCEND = 339,
    LCMATCHALL = 340,
    EXTENSION = 341,
    PLUSEQ = 342,
    MINUSEQ = 343,
    UNLOCK_SYM = 344,
    USER_SYM = 345,
    HOST_SYM = 346,
    UNDEFINED_MACRO = 347,
    MACRO_SYM = 348,
    RANDOMIZE_SYM = 349,
    FROM_SYM = 350,
    INCLUSIVE_SYM = 351,
    EXCLUSIVE_SYM = 352,
    NULL_SYM = 353
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 139 "parser.y"

  Evaltree                  evalt;
  Constrainttree            boolt;
  enum b_ops                boolo;
  int                       ival;
  double                    fval;
  int                       index;
  char                     *strval;
  CorpusList               *cl;

  struct {
    int a, b;
  } intpair;

  Context                   context;
  ActualParamList          *apl;

  enum ctxtdir              direction;

  struct Redir              redir;

  struct InputRedir         in_redir;

  struct {
    int ok;
    int ival;
    char *cval;
  }                         varval;

  struct {
    FieldType field;
    int inclusive;
  }                         base;

  struct {
    char *variableValue;
    char operator;
  }                         varsetting;

  struct {
    int mindist;
    int maxdist;
  }                         Distance;

  struct {
    FieldType anchor;
    int offset;
  }                         Anchor;

  struct {
    FieldType anchor1;
    int offset1;
    FieldType anchor2;
    int offset2;
  }                         AnchorPair;

  struct {
    char *name;
    int flags;
  }                         AttributeSpecification;

  RangeSetOp                rngsetop;

  SortClause                sortclause;

  FieldType                 field;

  SearchStrategy            search_strategy;

  TabulationItem            tabulation_item;

#line 431 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   543

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  122
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  151
/* YYNRULES -- Number of rules.  */
#define YYNRULES  358
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  546

#define YYUNDEFTOK  2
#define YYMAXUTOK   353


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   103,     2,     2,     2,   110,   102,     2,
     115,   111,   100,   101,   109,   108,     2,   118,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   120,   104,
     107,   105,   106,   114,   119,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   112,     2,   113,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   116,    99,   117,   121,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   423,   423,   423,   430,   431,   434,   434,   436,   436,
     447,   449,   449,   452,   452,   455,   455,   457,   468,   469,
     472,   478,   486,   493,   494,   494,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   523,   530,
     536,   542,   550,   559,   566,   567,   574,   579,   588,   589,
     595,   601,   602,   614,   616,   621,   623,   627,   628,   631,
     643,   650,   653,   654,   655,   656,   662,   659,   679,   682,
     683,   686,   692,   699,   707,   715,   730,   731,   732,   733,
     736,   756,   763,   764,   769,   776,   773,   796,   803,   810,
     811,   812,   815,   820,   825,   830,   831,   832,   833,   834,
     838,   839,   842,   857,   871,   872,   873,   874,   878,   879,
     882,   884,   891,   890,   898,   897,   910,   911,   916,   928,
     932,   943,   947,   959,   972,   985,   999,  1000,  1003,  1025,
    1030,  1039,  1047,  1048,  1049,  1052,  1053,  1058,  1064,  1070,
    1074,  1080,  1081,  1084,  1091,  1098,  1106,  1110,  1120,  1126,
    1129,  1136,  1142,  1154,  1164,  1165,  1169,  1170,  1179,  1193,
    1194,  1205,  1206,  1207,  1210,  1218,  1219,  1222,  1228,  1229,
    1232,  1236,  1241,  1232,  1246,  1256,  1259,  1260,  1269,  1270,
    1279,  1280,  1284,  1287,  1290,  1292,  1297,  1307,  1313,  1319,
    1325,  1328,  1331,  1337,  1343,  1349,  1352,  1360,  1370,  1386,
    1387,  1390,  1392,  1397,  1400,  1415,  1416,  1419,  1420,  1421,
    1422,  1425,  1441,  1443,  1453,  1456,  1457,  1460,  1469,  1470,
    1474,  1475,  1478,  1480,  1490,  1493,  1503,  1506,  1515,  1542,
    1545,  1547,  1553,  1551,  1559,  1562,  1563,  1566,  1576,  1585,
    1586,  1589,  1590,  1593,  1594,  1598,  1607,  1608,  1611,  1618,
    1626,  1627,  1628,  1631,  1632,  1635,  1636,  1640,  1657,  1658,
    1661,  1664,  1667,  1670,  1673,  1675,  1678,  1681,  1691,  1694,
    1696,  1700,  1701,  1704,  1705,  1707,  1708,  1710,  1711,  1714,
    1715,  1717,  1721,  1737,  1746,  1757,  1758,  1759,  1760,  1761,
    1762,  1765,  1771,  1772,  1789,  1800,  1803,  1804,  1805,  1813,
    1822,  1829,  1830,  1838,  1845,  1850,  1854,  1857,  1860,  1861,
    1876,  1877,  1878,  1879,  1880,  1884,  1884,  1886,  1887,  1888,
    1891,  1892,  1896,  1898,  1903,  1918,  1934,  1944,  1945,  1948,
    1949,  1953,  1966,  1977,  1981,  1982,  1985,  1991,  1992,  1994,
    1995,  1997,  1998,  2000,  2001,  2003,  2004,  2008,  2009
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "QID", "NQRID", "LABEL", "STRING",
  "FLAG", "TAGSTART", "TAGEND", "VARIABLE", "IPAddress", "IPSubnet",
  "INTEGER", "DOUBLEFLOAT", "FIELD", "FIELDLABEL", "ANCHORTAG",
  "ANCHORENDTAG", "SEARCH_STRATEGY", "TAB_SYM", "CAT_SYM", "DEFINE_SYM",
  "DIFF_SYM", "DISCARD_SYM", "EXPAND_SYM", "EXIT_SYM", "INTER_SYM",
  "JOIN_SYM", "SUBSET_SYM", "LEFT_SYM", "RIGHT_SYM", "SAVE_SYM",
  "SHOW_SYM", "CD_SYM", "TO_SYM", "WITHIN_SYM", "SET_SYM", "EXEC_SYM",
  "CUT_SYM", "INFO_SYM", "GROUP_SYM", "WHERE_SYM", "ESCAPE_SYM",
  "MEET_SYM", "UNION_SYM", "MU_SYM", "SORT_SYM", "COUNT_SYM", "ASC_SYM",
  "DESC_SYM", "REVERSE_SYM", "BY_SYM", "FOREACH_SYM", "ON_SYM", "YES_SYM",
  "OFF_SYM", "NO_SYM", "SLEEP_SYM", "REDUCE_SYM", "MAXIMAL_SYM",
  "WITH_SYM", "WITHOUT_SYM", "DELETE_SYM", "SIZE_SYM", "DUMP_SYM",
  "UNDUMP_SYM", "TABULATE_SYM", "NOT_SYM", "CONTAINS_SYM", "MATCHES_SYM",
  "GCDEL", "APPEND", "LEFT_APPEND", "LET", "GET", "NEQ", "IMPLIES",
  "RE_PAREN", "EOL_SYM", "ELLIPSIS", "MATCHALL", "LCSTART", "LCEND",
  "LCMATCHALL", "EXTENSION", "PLUSEQ", "MINUSEQ", "UNLOCK_SYM", "USER_SYM",
  "HOST_SYM", "UNDEFINED_MACRO", "MACRO_SYM", "RANDOMIZE_SYM", "FROM_SYM",
  "INCLUSIVE_SYM", "EXCLUSIVE_SYM", "NULL_SYM", "'|'", "'*'", "'+'", "'&'",
  "'!'", "';'", "'='", "'>'", "'<'", "'-'", "','", "'%'", "')'", "'['",
  "']'", "'?'", "'('", "'{'", "'}'", "'/'", "'@'", "':'", "'~'", "$accept",
  "line", "$@1", "command", "$@2", "$@3", "$@4", "$@5", "$@6",
  "CorpusCommand", "UnnamedCorpusCommand", "CYCommand", "$@7",
  "InteractiveCommand", "EOLCmd", "Cat", "Saving", "OptionalRedir",
  "Redir", "OptionalInputRedir", "InputRedir", "Showing",
  "AttributeSelections", "AttributeSelection", "TranslateExpr",
  "CorpusSetExpr", "SetOp", "SubsetExpr", "$@8", "Discard", "DiscArgs",
  "VarPrintCmd", "VarDefCmd", "VariableValueSpec", "OptionSetCmd", "$@9",
  "OptBase", "InclusiveExclusive", "VarValue", "InfoCmd", "GroupCmd",
  "GroupBy", "OptExpansion", "OptWithin", "TabulateCmd", "$@10", "$@11",
  "TabulationItems", "TabulationItem", "TabulationRange",
  "OptAttributeSpec", "SortCmd", "OptionalSortClause", "SortClause",
  "SortBoundaries", "SortDirection", "OptReverse", "Reduction",
  "OptPercent", "Delete", "LineRange", "SleepCmd", "SizeCmd", "DumpCmd",
  "UndumpCmd", "OptAscending", "OptWithTargetKeyword", "Query", "AQuery",
  "StandardQuery", "EmbeddedModifier", "MUQuery", "OptKeep",
  "SearchPattern", "$@12", "$@13", "$@14", "MatchSelector", "MatchOrLabel",
  "MatchendOrLabel", "OptOffset", "RegWordfExpr", "RegWordfTerm",
  "RegWordfFactor", "RegWordfPower", "Repeat", "AnchorPoint", "XMLTag",
  "RegionElement", "OptSlash", "RegexpOp", "NamedWfPattern",
  "OptTargetSign", "OptColon", "TargetNumber", "OptRefId",
  "WordformPattern", "ExtConstraint", "LookaheadConstraint",
  "OptionalFlag", "GlobalConstraint", "AlignmentConstraints", "$@15",
  "OptNot", "SearchSpace", "CutStatement", "OptNumber", "OptInteger",
  "PosInt", "OptMaxNumber", "ReStructure", "OptDirection", "Description",
  "OptionalCID", "CID", "ID_OR_NQRID", "BoolExpr", "RelExpr", "MvalOp",
  "OptionalNot", "RelLHS", "RelRHS", "RelOp", "FunctionCall",
  "FunctionArgList", "SingleArg", "LabelReference", "MUStatement",
  "MeetStatement", "MeetContext", "UnionStatement", "TABQuery",
  "TabPatterns", "TabOtherPatterns", "OptDistance", "AuthorizeCmd", "$@16",
  "OptionalGrants", "Grants", "Macro", "OptDEFINE", "ShowMacro",
  "MultiString", "RandomizeCmd", "OtherCommand", "OptFIELD", "OptON",
  "OptFROM", "OptTO", "OptELLIPSIS", "Anchor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   124,
      42,    43,    38,    33,    59,    61,    62,    60,    45,    44,
      37,    41,    91,    93,    63,    40,   123,   125,    47,    64,
      58,   126
};
# endif

#define YYPACT_NINF (-329)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-357)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      24,  -329,    78,   312,  -329,  -329,  -329,    90,  -329,   248,
     395,    97,   126,    53,  -329,    62,  -329,  -329,  -329,  -329,
     265,  -329,    98,  -329,   156,   139,  -329,   265,  -329,  -329,
    -329,   206,   212,   265,   265,    48,   295,   265,   265,   265,
    -329,   265,   265,   203,   265,   265,   286,   265,   225,   265,
     235,    50,   244,   142,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,   182,  -329,  -329,   273,  -329,  -329,   163,
      70,  -329,   243,  -329,  -329,   272,  -329,    81,    63,   287,
    -329,   266,  -329,  -329,  -329,  -329,   265,    -9,    -9,    88,
     174,   265,  -329,    -9,  -329,  -329,  -329,   317,   323,   335,
      51,  -329,   184,   327,   333,  -329,   332,  -329,    23,   296,
    -329,   319,    33,  -329,   341,    88,   300,   347,   357,  -329,
    -329,  -329,  -329,  -329,    32,   261,  -329,   265,  -329,  -329,
     349,  -329,  -329,   331,   360,  -329,  -329,    16,  -329,    16,
    -329,  -329,  -329,   336,   260,  -329,   267,  -329,  -329,   263,
     296,  -329,    39,  -329,   362,   374,  -329,  -329,  -329,  -329,
    -329,   368,   201,   253,   276,   376,  -329,  -329,  -329,   269,
    -329,  -329,  -329,  -329,  -329,   382,  -329,  -329,  -329,  -329,
    -329,    45,  -329,   333,   275,   385,   386,   379,  -329,  -329,
     350,    28,   315,   383,   384,  -329,  -329,  -329,  -329,   390,
     391,   359,   332,   316,  -329,   297,   403,  -329,   377,  -329,
     400,  -329,  -329,   301,  -329,  -329,    16,    16,   304,   -18,
    -329,   371,  -329,  -329,    77,   155,   400,  -329,    63,    63,
    -329,   350,  -329,  -329,    -2,   100,  -329,  -329,  -329,   302,
      39,     9,   320,   114,  -329,   149,  -329,  -329,  -329,  -329,
     409,  -329,  -329,   387,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,   408,  -329,  -329,  -329,   267,  -329,   411,   178,   360,
    -329,  -329,   333,    -9,   355,   322,   420,  -329,  -329,   387,
     422,  -329,   338,   101,  -329,   446,    20,   436,   337,   230,
    -329,   448,    30,   450,   453,  -329,    14,  -329,   146,  -329,
    -329,    16,  -329,    16,    16,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,   451,   239,    14,  -329,  -329,  -329,  -329,    17,
      81,  -329,   388,    63,  -329,   461,   267,  -329,  -329,  -329,
     458,  -329,   409,   -20,  -329,  -329,  -329,   346,    39,   396,
    -329,  -329,  -329,  -329,    38,  -329,  -329,    81,  -329,   455,
     356,    30,  -329,   358,   467,   258,  -329,  -329,   332,   350,
      55,  -329,  -329,  -329,  -329,  -329,  -329,   459,  -329,   465,
    -329,  -329,   332,  -329,   360,  -329,  -329,   332,   387,  -329,
    -329,   363,   364,  -329,  -329,  -329,   360,  -329,  -329,  -329,
     468,  -329,  -329,   190,  -329,  -329,   -30,   378,  -329,   360,
    -329,  -329,  -329,   333,   105,  -329,    63,   370,  -329,  -329,
     360,   479,  -329,  -329,   114,    16,  -329,   333,   110,  -329,
      -9,  -329,   447,  -329,  -329,  -329,  -329,   480,   462,  -329,
     274,   332,    -9,  -329,  -329,  -329,  -329,   473,    19,   483,
     483,  -329,   380,    14,  -329,  -329,   375,   333,  -329,   108,
    -329,   392,   393,   302,   102,   336,   381,   333,  -329,  -329,
     272,   456,  -329,    -9,  -329,  -329,   442,    20,  -329,   332,
    -329,  -329,  -329,   489,   489,   360,  -329,  -329,  -329,   389,
    -329,   486,   394,  -329,  -329,  -329,   409,   463,  -329,   397,
     487,   350,  -329,  -329,  -329,   332,   101,  -329,  -329,  -329,
    -329,  -329,  -329,   398,    52,  -329,  -329,  -329,   499,   462,
    -329,  -329,  -329,   430,  -329,  -329,   399,   412,    -9,  -329,
     490,   427,   493,  -329,  -329,   402,    64,   232,  -329,  -329,
    -329,   399,  -329,  -329,  -329,  -329
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     4,     0,     0,     1,    17,    48,     0,     3,    24,
     338,     0,     0,     0,     8,   269,   268,    75,    74,    72,
     266,    73,     0,    18,   259,   176,    23,     0,    71,    22,
     267,   266,   337,     0,   266,    61,    92,   266,   111,     0,
     346,   266,   266,     0,   266,   266,     0,     0,     0,     0,
       0,     0,   344,     0,    27,    28,    26,    29,    34,    33,
      32,    35,    36,    42,    37,    31,    30,    38,    39,    40,
      41,    43,    44,     0,    45,    46,     0,    16,    10,     0,
      24,   269,     0,   265,     7,   262,    21,     0,     0,     0,
      25,   169,   171,   180,   172,   173,     0,    55,    55,    55,
       0,    78,    80,    55,    62,    81,    64,   339,     0,     0,
      63,    66,    91,     0,     0,   110,     0,    47,   137,     0,
     158,     0,     0,   160,   348,    55,   166,   124,     0,   327,
     328,   329,   345,    12,     0,     0,     9,     0,    19,    20,
       0,   260,   261,     0,   239,   233,   235,     0,   237,     0,
     317,   230,   231,   248,     0,   308,   179,   306,   307,     0,
     137,   244,   224,    70,     0,     0,    52,    54,    51,   351,
      49,     0,     0,     0,     0,     0,    82,    79,    53,   340,
      67,    68,    65,   104,   103,   102,   105,   106,   107,   108,
      90,     0,   255,   149,   357,     0,     0,   254,   133,   136,
     250,     0,   156,     0,     0,   155,   347,   159,   161,     0,
       0,   165,     0,   352,   325,     0,     0,    14,     0,    76,
     252,   238,   232,   285,   305,   287,     0,     0,     0,     0,
     275,   278,   288,   283,     0,   324,   252,   314,     0,     0,
     178,   250,   175,   170,   250,   282,   213,   209,   210,   224,
     224,   226,   181,   193,   195,   200,   204,   203,   205,   202,
     229,    57,    56,   354,    88,    83,    89,    84,    87,    85,
      86,     0,   109,    95,    94,   179,   150,     0,   121,   239,
     253,   134,     0,    55,     0,   152,     0,   153,   154,   354,
     167,   164,    59,    55,   126,   132,   129,     0,   331,     0,
     336,     0,     0,   264,     0,   258,     0,   274,     0,   286,
     284,     0,   236,     0,     0,   281,   299,   300,   298,   297,
     296,   295,     0,     0,     0,   234,   321,   322,   323,     0,
       0,   247,   282,     0,   177,     0,   179,   218,   219,   211,
       0,   217,   229,     0,   227,   225,   222,   226,   224,   241,
     194,   197,   198,   199,     0,   196,   228,     0,   353,     0,
       0,     0,    93,     0,     0,     0,   114,   115,     0,   250,
     141,   249,   135,   148,   151,   147,   157,     0,   168,     0,
     163,    58,     0,   123,   239,   128,   355,     0,   354,   333,
     326,     0,     0,    69,    77,   263,   239,   292,   293,   294,
       0,   289,   304,     0,   302,   273,   270,   271,   272,   239,
     279,   280,   276,     0,     0,   316,     0,     0,   242,   174,
     239,     0,   201,   223,   192,     0,   182,     0,     0,   221,
      55,   341,     0,   358,   120,   116,   117,     0,   119,   349,
     144,     0,    55,    60,   127,   131,   130,     0,     0,     0,
       0,   290,     0,     0,   301,   277,     0,   257,   318,   312,
     313,   246,     0,   224,   240,   248,     0,   257,   206,    50,
     262,   121,   118,    55,   142,   143,   146,   139,   162,     0,
     332,   330,   343,   335,   334,   239,   303,   320,   256,     0,
     311,     0,     0,   245,   180,   212,   229,   185,   207,     0,
     252,   250,   113,   145,   138,     0,    55,   342,   291,   319,
     310,   309,   243,   216,     0,   183,   208,   251,     0,   119,
     140,   125,   215,     0,   186,   187,   191,    98,    55,   214,
       0,     0,     0,    96,   112,     0,     0,   101,   190,   188,
     189,   191,    99,   100,    97,   184
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
     432,  -329,  -329,  -329,  -329,  -329,  -329,   -98,  -329,  -329,
    -329,  -329,  -329,   407,  -329,   482,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,    -1,    49,  -329,  -329,  -329,    31,   137,  -329,
    -329,  -329,   361,   404,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -231,    34,  -329,  -329,  -329,  -329,  -329,  -329,
     -19,   277,   176,  -240,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -242,   179,  -329,  -328,   -83,  -252,  -329,  -269,
    -329,  -329,  -329,  -329,    60,  -235,    29,  -329,  -111,    65,
    -329,    61,   294,   251,     7,  -329,  -141,  -329,   288,   202,
    -291,   211,  -329,  -329,  -329,    83,   309,  -227,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,    89,  -329,  -329,  -329,  -329,   -99,  -250,    66,
    -114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,     9,    79,    10,    11,    12,    22,
      23,    24,    25,    53,    13,    54,    55,   166,   167,   380,
     381,    56,   110,   111,   139,    26,    27,    28,   302,    57,
     101,    58,    59,   176,    60,   361,   533,   544,   190,    61,
      62,   368,   473,   369,    63,   212,   213,   293,   294,   295,
     385,    64,   198,   199,   440,   476,   504,    65,   375,    66,
     205,    67,    68,    69,    70,   292,   211,    90,    91,    92,
      93,    94,   241,   161,   162,   349,   465,   515,   526,   541,
     531,   252,   253,   254,   255,   355,   256,   257,   258,   523,
     340,   259,   260,   346,   347,   357,   155,   151,   152,   222,
     426,   244,   461,   494,   237,   283,   304,   281,   488,   489,
      86,   143,   305,    82,    83,    30,   229,   230,   322,   323,
     231,   402,   324,   232,   403,   404,   233,   156,   157,   492,
     158,    95,   153,   235,   330,    71,   298,   390,   448,    72,
      73,    74,   483,    75,   117,   207,   441,   171,   359,   387,
     296
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     168,   170,   195,   193,   150,   178,   334,   342,   234,   336,
     370,   332,   333,   350,   421,   401,    29,   223,   224,   223,
     224,   396,   480,   344,    -5,   397,   209,   208,   398,   399,
     225,   192,   225,   401,    96,   215,  -356,   144,   282,   377,
     102,   145,   192,   113,   362,   115,   116,   202,   245,   246,
     394,   104,   192,   124,   125,   524,   127,   247,   248,   105,
     311,   194,   129,   130,   164,   273,   312,   539,   525,   313,
     144,  -350,   314,    81,   145,    16,   196,   275,     4,   348,
     540,   313,   276,   106,   314,   307,   308,    29,   144,   284,
     285,   422,   145,   400,    17,   203,   204,   165,    18,    19,
      20,   386,  -352,   163,    14,   419,   417,  -220,   177,   432,
     439,   490,   146,   249,   297,   445,    21,   197,   335,   226,
    -224,  -224,   491,   245,   246,  -224,   413,   451,     1,   345,
     481,   227,   247,   248,   438,   228,    76,   228,   447,   216,
     455,   107,   149,   274,   218,   146,   147,   427,   148,   108,
     131,   462,   108,    77,   250,   311,   109,    78,   251,   109,
      87,   164,   401,   146,   147,   137,   148,    80,   513,   315,
     406,   371,   407,   408,   164,   149,   313,   337,   154,   314,
     311,  -315,    85,   169,   350,   372,    88,   183,   249,   459,
     325,   184,  -315,   149,   165,   383,  -224,  -224,   185,  -224,
    -269,   313,    84,  -315,   314,   338,   339,   165,   264,    81,
     382,    16,   265,    97,   457,   364,   508,   120,   414,   467,
     365,   496,   458,   100,   311,    89,  -224,   468,   126,   250,
      17,   366,   367,   251,    18,    19,    20,   391,   128,   186,
     187,   188,   189,   428,   392,   313,   133,   415,   314,   351,
     352,    15,    21,    16,   437,   326,   327,   405,   132,  -315,
     266,   172,   173,   353,   267,   354,   519,   136,    81,   328,
      16,   329,    17,   446,   429,   134,    18,    19,    20,   174,
     135,   175,    99,   268,   464,   103,   140,   269,   114,    81,
     159,    16,   118,   119,    21,   121,   122,   123,   112,   453,
      16,   454,   456,   141,   142,   238,   239,   309,   224,   410,
     411,   435,   436,     5,   160,    -6,   466,    -6,    -6,    -6,
     179,    -6,    -6,    -6,   474,   475,   180,   477,   542,   543,
      -6,    -6,   469,    -6,   -11,   -11,    -6,   -11,   181,   -15,
      -6,    -6,    -6,   191,   478,   -11,   -11,   192,   194,   196,
     -11,   -13,   -11,   -11,   -11,   201,   -11,   206,    -6,    -6,
     -11,   -11,   210,  -122,   214,   217,   219,   220,   221,   261,
     240,   -11,   -11,   236,   242,   502,   -11,   -11,   -11,   -11,
     -11,   262,   263,   270,   271,   272,    -6,   277,   278,   279,
     282,   520,     6,   280,    -6,    -6,   286,    -6,    -6,   287,
     288,     7,   -11,   -11,   289,   -11,   -11,   290,   521,   291,
     300,   169,   299,   301,   303,   356,   306,    31,    32,   348,
      33,   251,   360,   358,    -6,   363,   373,    -6,    34,    35,
     534,    -6,   374,    36,   376,    37,    38,    39,   378,    40,
     315,  -282,  -282,    41,    42,   379,   316,   317,   318,   384,
     388,   393,   389,  -251,    43,    44,   395,   315,   409,    45,
      46,    47,    48,    49,   418,   420,   345,   431,   425,   430,
     434,   433,   443,   442,   449,   450,   319,   320,   321,   452,
     314,   460,   463,   471,   470,    50,    51,   479,   472,    52,
     482,   485,   487,   364,   503,   493,   507,   514,   498,   495,
     510,   517,   527,   529,   535,   511,   509,   532,   536,   537,
     506,   530,   138,    98,   516,   538,   522,   182,   528,   444,
     501,   243,   545,   200,   424,   497,   423,   343,   512,   518,
     331,   500,   499,   341,   416,   412,   486,   310,     0,   484,
       0,     0,     0,   505
};

static const yytype_int16 yycheck[] =
{
      98,    99,   116,   114,    87,   103,   241,   249,   149,   244,
     279,   238,   239,   253,   342,   306,     9,     3,     4,     3,
       4,     7,     3,    14,     0,    11,   125,   125,    14,    15,
      16,    14,    16,   324,    27,     3,    16,     7,    40,   289,
      33,    11,    14,    36,   275,    38,    39,    14,     9,    10,
     302,     3,    14,    46,    47,     3,    49,    18,    19,    11,
      78,    16,    12,    13,    73,    20,    84,     3,    16,    99,
       7,    16,   102,     3,    11,     5,    53,   191,     0,    99,
      16,    99,   193,    35,   102,   226,   227,    80,     7,    61,
     201,   111,    11,    79,    24,    62,    63,   106,    28,    29,
      30,    81,    14,    96,    14,   336,   333,     7,   101,   361,
      55,     3,    82,    74,   213,   384,    46,    94,   120,   103,
       6,     7,    14,     9,    10,    11,   109,   396,   104,   120,
     111,   115,    18,    19,   369,   121,    39,   121,   388,   107,
     409,    93,   112,    98,   137,    82,    83,   109,    85,   101,
     100,   420,   101,    27,   115,    78,   108,   104,   119,   108,
      21,    73,   453,    82,    83,    95,    85,   105,   496,    69,
     311,   282,   313,   314,    73,   112,    99,    77,   115,   102,
      78,    26,    26,    95,   424,   283,    47,     3,    74,   416,
     113,     7,    37,   112,   106,   293,    82,    83,    14,    85,
      16,    99,   104,    48,   102,   105,   106,   106,     7,     3,
     109,     5,    11,     7,   109,    37,   485,    14,   329,   109,
      42,   463,   117,    11,    78,    86,   112,   117,     3,   115,
      24,    53,    54,   119,    28,    29,    30,     7,     3,    55,
      56,    57,    58,   354,    14,    99,   104,   330,   102,   100,
     101,     3,    46,     5,   368,   100,   101,   111,    14,   104,
       7,    87,    88,   114,    11,   116,   501,   104,     3,   114,
       5,   116,    24,   387,   357,    93,    28,    29,    30,   105,
       7,   107,    31,     7,   425,    34,    43,    11,    37,     3,
       3,     5,    41,    42,    46,    44,    45,    11,     3,   109,
       5,   111,   413,    31,    32,    45,    46,     3,     4,    70,
      71,    53,    54,     1,    48,     3,   427,     5,     6,     7,
       3,     9,    10,    11,    50,    51,     3,   441,    96,    97,
      18,    19,   430,    21,    22,    23,    24,    25,     3,    27,
      28,    29,    30,    16,   442,    33,    34,    14,    16,    53,
      38,    39,    40,    41,    42,    36,    44,    16,    46,    47,
      48,    49,    62,    16,     7,   104,    17,    36,     8,     7,
     103,    59,    60,    37,   111,   473,    64,    65,    66,    67,
      68,     7,    14,     7,   115,     3,    74,   112,     3,     3,
      40,   505,    80,    14,    82,    83,    81,    85,    86,    16,
      16,    89,    90,    91,    14,    93,    94,    16,   506,    50,
       7,    95,   115,    36,    14,     6,   115,    22,    23,    99,
      25,   119,    14,    36,   112,    14,    71,   115,    33,    34,
     528,   119,   110,    38,    14,    40,    41,    42,    16,    44,
      69,    70,    71,    48,    49,   107,    75,    76,    77,     3,
      14,     3,   115,     3,    59,    60,     3,    69,     7,    64,
      65,    66,    67,    68,     3,     7,   120,   111,    72,    14,
       3,   113,     7,    14,   111,   111,   105,   106,   107,    11,
     102,   111,     3,     3,    37,    90,    91,    14,    26,    94,
       7,   111,   117,    37,    52,   103,     7,    34,   117,   106,
      14,    14,     3,    73,    14,   111,   117,    95,    81,    16,
     479,   112,    80,    31,   117,   113,   118,   110,   519,   382,
     471,   160,   541,   119,   348,   465,   347,   250,   494,   500,
     236,   470,   467,   245,   332,   324,   453,   228,    -1,   450,
      -1,    -1,    -1,   477
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   104,   123,   124,     0,     1,    80,    89,   125,   126,
     128,   129,   130,   136,    14,     3,     5,    24,    28,    29,
      30,    46,   131,   132,   133,   134,   147,   148,   149,   236,
     237,    22,    23,    25,    33,    34,    38,    40,    41,    42,
      44,    48,    49,    59,    60,    64,    65,    66,    67,    68,
      90,    91,    94,   135,   137,   138,   143,   151,   153,   154,
     156,   161,   162,   166,   173,   179,   181,   183,   184,   185,
     186,   257,   261,   262,   263,   265,    39,    27,   104,   127,
     105,     3,   235,   236,   104,    26,   232,    21,    47,    86,
     189,   190,   191,   192,   193,   253,   236,     7,   147,   235,
      11,   152,   236,   235,     3,    11,    35,    93,   101,   108,
     144,   145,     3,   236,   235,   236,   236,   266,   235,   235,
      14,   235,   235,    11,   236,   236,     3,   236,     3,    12,
      13,   100,    14,   104,    93,     7,   104,    95,   132,   146,
      43,    31,    32,   233,     7,    11,    82,    83,    85,   112,
     218,   219,   220,   254,   115,   218,   249,   250,   252,     3,
      48,   195,   196,   236,    73,   106,   139,   140,   139,    95,
     139,   269,    87,    88,   105,   107,   155,   236,   139,     3,
       3,     3,   145,     3,     7,    14,    55,    56,    57,    58,
     160,    16,    14,   230,    16,   272,    53,    94,   174,   175,
     175,    36,    14,    62,    63,   182,    16,   267,   139,   269,
      62,   188,   167,   168,     7,     3,   107,   104,   236,    17,
      36,     8,   221,     3,     4,    16,   103,   115,   121,   238,
     239,   242,   245,   248,   238,   255,    37,   226,    45,    46,
     103,   194,   111,   174,   223,     9,    10,    18,    19,    74,
     115,   119,   203,   204,   205,   206,   208,   209,   210,   213,
     214,     7,     7,    14,     7,    11,     7,    11,     7,    11,
       7,   115,     3,    20,    98,   272,   230,   112,     3,     3,
      14,   229,    40,   227,    61,   230,    81,    16,    16,    14,
      16,    50,   187,   169,   170,   171,   272,   269,   258,   115,
       7,    36,   150,    14,   228,   234,   115,   238,   238,     3,
     248,    78,    84,    99,   102,    69,    75,    76,    77,   105,
     106,   107,   240,   241,   244,   113,   100,   101,   114,   116,
     256,   234,   249,   249,   227,   120,   227,    77,   105,   106,
     212,   240,   214,   203,    14,   120,   215,   216,    99,   197,
     205,   100,   101,   114,   116,   207,     6,   217,    36,   270,
      14,   157,   194,    14,    37,    42,    53,    54,   163,   165,
     221,   230,   139,    71,   110,   180,    14,   270,    16,   107,
     141,   142,   109,   139,     3,   172,    81,   271,    14,   115,
     259,     7,    14,     3,   219,     3,     7,    11,    14,    15,
      79,   242,   243,   246,   247,   111,   238,   238,   238,     7,
      70,    71,   243,   109,   230,   218,   241,   249,     3,   194,
       7,   217,   111,   215,   204,    72,   222,   109,   230,   218,
      14,   111,   219,   113,     3,    53,    54,   272,   227,    55,
     176,   268,    14,     7,   170,   221,   272,   270,   260,   111,
     111,   221,    11,   109,   111,   221,   230,   109,   117,   249,
     111,   224,   221,     3,   238,   198,   230,   109,   117,   139,
      37,     3,    26,   164,    50,    51,   177,   272,   139,    14,
       3,   111,     7,   264,   264,   111,   247,   117,   230,   231,
       3,    14,   251,   103,   225,   106,   214,   226,   117,   231,
     233,   165,   139,    52,   178,   271,   169,     7,   221,   117,
      14,   111,   195,   217,    34,   199,   117,    14,   228,   227,
     272,   139,   118,   211,     3,    16,   200,     3,   164,    73,
     112,   202,    95,   158,   139,    14,    81,    16,   113,     3,
      16,   201,    96,    97,   159,   202
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   122,   124,   123,   123,   123,   126,   125,   127,   125,
     125,   128,   125,   129,   125,   130,   125,   125,   131,   131,
     131,   132,   133,   133,   134,   133,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   136,   137,
     137,   137,   137,   138,   139,   139,   140,   140,   141,   141,
     142,   143,   143,   143,   143,   144,   144,   145,   145,   146,
     147,   147,   148,   148,   148,   148,   150,   149,   151,   152,
     152,   153,   154,   154,   154,   154,   155,   155,   155,   155,
     156,   156,   156,   156,   156,   157,   156,   158,   158,   159,
     159,   159,   160,   160,   160,   160,   160,   160,   160,   160,
     161,   161,   162,   162,   163,   163,   163,   163,   164,   164,
     165,   165,   167,   166,   168,   166,   169,   169,   170,   171,
     171,   172,   172,   173,   173,   173,   174,   174,   175,   176,
     176,   176,   177,   177,   177,   178,   178,   179,   179,   179,
     179,   180,   180,   181,   181,   181,   182,   182,   183,   184,
     184,   185,   185,   186,   187,   187,   188,   188,   188,   189,
     189,   190,   190,   190,   191,   192,   192,   193,   194,   194,
     196,   197,   198,   195,   199,   199,   200,   200,   201,   201,
     202,   202,   203,   203,   204,   204,   205,   205,   205,   205,
     205,   206,   206,   206,   206,   206,   207,   207,   207,   208,
     208,   209,   209,   209,   210,   211,   211,   212,   212,   212,
     212,   213,   214,   214,   214,   215,   215,   216,   217,   217,
     218,   218,   219,   219,   219,   219,   220,   220,   221,   221,
     222,   222,   224,   223,   223,   225,   225,   226,   226,   227,
     227,   228,   228,   229,   229,   230,   231,   231,   232,   232,
     233,   233,   233,   234,   234,   235,   235,   236,   237,   237,
     238,   238,   238,   238,   238,   238,   239,   239,   239,   240,
     240,   241,   241,   242,   242,   242,   242,   242,   242,   243,
     243,   243,   243,   243,   243,   244,   244,   244,   244,   244,
     244,   245,   246,   246,   247,   248,   249,   249,   249,   250,
     251,   251,   251,   252,   253,   254,   255,   255,   256,   256,
     256,   256,   256,   256,   256,   258,   257,   257,   257,   257,
     259,   259,   260,   260,   261,   261,   261,   262,   262,   263,
     263,   263,   264,   264,   265,   265,   266,   267,   267,   268,
     268,   269,   269,   270,   270,   271,   271,   272,   272
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     0,     0,     3,     0,     4,
       2,     0,     3,     0,     4,     0,     2,     1,     1,     3,
       3,     2,     1,     1,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     3,
       7,     3,     3,     3,     1,     0,     2,     2,     1,     0,
       2,     1,     2,     2,     2,     2,     1,     2,     2,     4,
       3,     1,     1,     1,     1,     1,     0,     6,     2,     2,
       1,     2,     3,     4,     4,     4,     2,     2,     2,     2,
       3,     2,     1,     5,     4,     0,    11,     3,     0,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,    11,     8,     1,     1,     2,     2,     1,     0,
       2,     0,     0,     5,     0,     9,     1,     3,     2,     1,
       3,     2,     0,     3,     4,     5,     1,     0,     6,     2,
       4,     0,     1,     1,     0,     1,     0,     5,     5,     3,
       4,     1,     0,     4,     4,     3,     1,     3,     2,     3,
       2,     3,     7,     5,     1,     0,     0,     2,     3,     1,
       3,     1,     1,     1,     5,     3,     0,     4,     1,     0,
       0,     0,     0,     7,     6,     0,     1,     1,     1,     1,
       3,     0,     3,     1,     2,     1,     2,     2,     2,     2,
       1,     3,     1,     1,     1,     1,     3,     4,     5,     1,
       1,     2,     5,     1,     8,     1,     0,     1,     1,     1,
       0,     3,     2,     3,     0,     1,     0,     1,     1,     0,
       1,     1,     2,     1,     3,     1,     3,     1,     1,     0,
       2,     0,     0,     6,     0,     1,     0,     2,     0,     2,
       0,     1,     0,     1,     0,     1,     1,     0,     4,     0,
       1,     1,     0,     2,     1,     1,     0,     1,     1,     1,
       3,     3,     3,     3,     2,     1,     3,     4,     1,     2,
       2,     1,     0,     1,     2,     1,     2,     1,     1,     1,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     3,     1,     1,     1,     1,     1,     7,
       2,     1,     0,     5,     3,     2,     3,     0,     3,     5,
       4,     1,     1,     1,     0,     0,     5,     2,     2,     2,
       3,     0,     2,     0,     7,     7,     4,     1,     0,     2,
       3,     6,     2,     1,     1,     2,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
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
  switch (yyn)
    {
  case 2:
#line 423 "parser.y"
                                        { prepare_parse(); }
#line 2070 "parser.tab.c"
    break;

  case 3:
#line 424 "parser.y"
                                        {
                                          if (generate_code)
                                            addHistoryLine();
                                          resetQueryBuffer();
                                          YYACCEPT; 
                                        }
#line 2081 "parser.tab.c"
    break;

  case 4:
#line 430 "parser.y"
                                        { YYACCEPT; }
#line 2087 "parser.tab.c"
    break;

  case 5:
#line 431 "parser.y"
                                        { YYACCEPT; }
#line 2093 "parser.tab.c"
    break;

  case 6:
#line 434 "parser.y"
                                        { prepare_input(); }
#line 2099 "parser.tab.c"
    break;

  case 7:
#line 435 "parser.y"
                                        { after_CorpusCommand((yyvsp[-1].cl)); }
#line 2105 "parser.tab.c"
    break;

  case 8:
#line 436 "parser.y"
                                        { 
                                          /* unlock 'QueryLock' mode */
                                          if ((yyvsp[0].ival) == query_lock)
                                            query_lock = 0;
                                          else {
                                            fprintf(stderr, "ALERT! Query lock violation.\n");
                                            printf("\n"); /* so CQP.pm won't block -- should no longer be needed after switching to .EOL. mechanism */
                                            exit(1);
                                          }
                                        }
#line 2120 "parser.tab.c"
    break;

  case 11:
#line 449 "parser.y"
                                        { if (query_lock) {warn_query_lock_violation(); YYABORT;} }
#line 2126 "parser.tab.c"
    break;

  case 12:
#line 451 "parser.y"
                                        {  }
#line 2132 "parser.tab.c"
    break;

  case 13:
#line 452 "parser.y"
                                        { if (query_lock) {warn_query_lock_violation(); YYABORT;} }
#line 2138 "parser.tab.c"
    break;

  case 14:
#line 454 "parser.y"
                                        { do_exec((yyvsp[-1].strval)); }
#line 2144 "parser.tab.c"
    break;

  case 15:
#line 455 "parser.y"
                                        { if (query_lock) {warn_query_lock_violation(); YYABORT;} }
#line 2150 "parser.tab.c"
    break;

  case 16:
#line 456 "parser.y"
                                        { exit_cqp++; }
#line 2156 "parser.tab.c"
    break;

  case 17:
#line 457 "parser.y"
                                        { 
                                          if (yychar == YYEMPTY) 
                                            yychar = yylex(); /* so synchronize works if lookahead yychar is empty */
                                          synchronize();
                                          /* in case of syntax errors, don't save history file */
                                          resetQueryBuffer();
                                          YYABORT; /* Oli did this:   yyerrok; */
                                          /* but we don't want to continue processing a line, when part of it failed */
                                        }
#line 2170 "parser.tab.c"
    break;

  case 18:
#line 468 "parser.y"
                                        { (yyval.cl) = (yyvsp[0].cl); }
#line 2176 "parser.tab.c"
    break;

  case 19:
#line 471 "parser.y"
                                        { (yyval.cl) = in_CorpusCommand((yyvsp[-2].strval), (yyvsp[0].cl)); }
#line 2182 "parser.tab.c"
    break;

  case 20:
#line 474 "parser.y"
                                        { (yyval.cl) = in_CorpusCommand((yyvsp[-2].strval), after_CorpusSetExpr((yyvsp[0].cl))); }
#line 2188 "parser.tab.c"
    break;

  case 21:
#line 478 "parser.y"
                                        { (yyval.cl) = in_UnnamedCorpusCommand((yyvsp[-1].cl)); }
#line 2194 "parser.tab.c"
    break;

  case 22:
#line 486 "parser.y"
                                        { 
                                          if (query_lock) {
                                            warn_query_lock_violation();
                                            YYABORT;
                                          }
                                          (yyval.cl) = ActivateCorpus((yyvsp[0].cl)); 
                                        }
#line 2206 "parser.tab.c"
    break;

  case 23:
#line 493 "parser.y"
                                        { (yyval.cl) = after_CorpusSetExpr((yyvsp[0].cl)); }
#line 2212 "parser.tab.c"
    break;

  case 24:
#line 494 "parser.y"
                                        { prepare_Query(); }
#line 2218 "parser.tab.c"
    break;

  case 25:
#line 495 "parser.y"
                                        { (yyval.cl) = after_Query((yyvsp[0].cl)); }
#line 2224 "parser.tab.c"
    break;

  case 48:
#line 523 "parser.y"
                                        {
                                          /* print special code ``-::-EOL-::-'' marking end-of-command in child mode */
                                          printf("-::-EOL-::-\n"); 
                                          fflush(stdout); 
                                        }
#line 2234 "parser.tab.c"
    break;

  case 49:
#line 531 "parser.y"
                                        { 
                                          /* cat entire subcorpus */
                                          do_cat((yyvsp[-1].cl), &((yyvsp[0].redir)), 0, -1); 
                                          cl_free((yyvsp[0].redir).name); 
                                        }
#line 2244 "parser.tab.c"
    break;

  case 50:
#line 537 "parser.y"
                                        { 
                                          /* cat part of subcorpus (matches #$4 .. #$6) */
                                          do_cat((yyvsp[-5].cl), &((yyvsp[0].redir)), (yyvsp[-3].ival), (yyvsp[-1].ival)); 
                                          cl_free((yyvsp[0].redir).name); 
                                        }
#line 2254 "parser.tab.c"
    break;

  case 51:
#line 543 "parser.y"
                                        {
                                          /* cat result of a set operation on 2 subcorpora */
                                          if (generate_code) 
                                            do_cat((yyvsp[-1].cl), &((yyvsp[0].redir)), 0, -1);
                                          cl_free((yyvsp[0].redir).name);
                                          drop_temp_corpora();
                                        }
#line 2266 "parser.tab.c"
    break;

  case 52:
#line 551 "parser.y"
                                        {
                                          /* cat arbitrary string */
                                          do_catString((yyvsp[-1].strval), &((yyvsp[0].redir))); 
                                          cl_free((yyvsp[0].redir).name); 
                                          cl_free((yyvsp[-1].strval)); 
                                        }
#line 2277 "parser.tab.c"
    break;

  case 53:
#line 560 "parser.y"
                                        {
                                          do_save((yyvsp[-1].cl), &((yyvsp[0].redir))); 
                                          cl_free((yyvsp[0].redir).name); 
                                        }
#line 2286 "parser.tab.c"
    break;

  case 55:
#line 567 "parser.y"
                                        {
                                          (yyval.redir).name = NULL; /* will open STDOUT */
                                          (yyval.redir).mode = "w";
                                          (yyval.redir).stream = NULL;
                                        }
#line 2296 "parser.tab.c"
    break;

  case 56:
#line 574 "parser.y"
                                        { 
                                          (yyval.redir).name = (yyvsp[0].strval);
                                          (yyval.redir).mode = "w";
                                          (yyval.redir).stream = NULL;
                                        }
#line 2306 "parser.tab.c"
    break;

  case 57:
#line 579 "parser.y"
                                        {
                                          (yyval.redir).name = (yyvsp[0].strval);
                                          (yyval.redir).mode = "a";
                                          (yyval.redir).stream = NULL;
                                        }
#line 2316 "parser.tab.c"
    break;

  case 59:
#line 589 "parser.y"
                                        {
                                          (yyval.in_redir).name = NULL; /* will open STDIN */
                                          (yyval.in_redir).stream = NULL;
                                        }
#line 2325 "parser.tab.c"
    break;

  case 60:
#line 595 "parser.y"
                                        {
                                          (yyval.in_redir).name = (yyvsp[0].strval);
                                          (yyval.in_redir).stream = NULL;
                                        }
#line 2334 "parser.tab.c"
    break;

  case 61:
#line 601 "parser.y"
                                        { show_corpora(UNDEF); }
#line 2340 "parser.tab.c"
    break;

  case 62:
#line 602 "parser.y"
                                        {
                                          if (0 == strncasecmp((yyvsp[0].strval), "var", 3))
                                            do_PrintAllVariables();
                                          else if (strncasecmp((yyvsp[0].strval), "active", 6) == 0 || strncasecmp((yyvsp[0].strval), "current", 7) == 0) 
                                            show_corpus_active();
                                          else if (strncasecmp((yyvsp[0].strval), "sys", 3) == 0 || strncasecmp((yyvsp[0].strval), "corp", 4) == 0) 
                                            show_corpora(SYSTEM);
                                          else if (strncasecmp((yyvsp[0].strval), "sub", 3) == 0 || strcasecmp((yyvsp[0].strval), "named") == 0 || strcasecmp((yyvsp[0].strval), "queries") == 0) 
                                            show_corpora(SUB);
                                          else 
                                            cqpmessage(Error, "show what?");
                                        }
#line 2357 "parser.tab.c"
    break;

  case 64:
#line 617 "parser.y"
                                        { print_context_descriptor(&CD); }
#line 2363 "parser.tab.c"
    break;

  case 67:
#line 627 "parser.y"
                                        { do_attribute_show((yyvsp[0].strval), 1); }
#line 2369 "parser.tab.c"
    break;

  case 68:
#line 628 "parser.y"
                                        { do_attribute_show((yyvsp[0].strval), 0); }
#line 2375 "parser.tab.c"
    break;

  case 69:
#line 634 "parser.y"
                                        {
                                          if (query_lock) {
                                            warn_query_lock_violation(); 
                                            YYABORT;
                                          } 
                                          (yyval.cl) = do_translate((yyvsp[-2].cl), (yyvsp[0].strval)); 
                                        }
#line 2387 "parser.tab.c"
    break;

  case 70:
#line 643 "parser.y"
                                        { 
                                          if (query_lock) {
                                            warn_query_lock_violation(); 
                                            YYABORT;
                                          }
                                          (yyval.cl) = do_setop((yyvsp[-2].rngsetop), (yyvsp[-1].cl), (yyvsp[0].cl));
                                        }
#line 2399 "parser.tab.c"
    break;

  case 72:
#line 653 "parser.y"
                                        { (yyval.rngsetop) = RUnion; }
#line 2405 "parser.tab.c"
    break;

  case 73:
#line 654 "parser.y"
                                        { (yyval.rngsetop) = RUnion; }
#line 2411 "parser.tab.c"
    break;

  case 74:
#line 655 "parser.y"
                                        { (yyval.rngsetop) = RIntersection; }
#line 2417 "parser.tab.c"
    break;

  case 75:
#line 656 "parser.y"
                                        { (yyval.rngsetop) = RDiff; }
#line 2423 "parser.tab.c"
    break;

  case 76:
#line 662 "parser.y"
                                        { 
                                          do_start_timer();
                                          prepare_do_subset((yyvsp[-2].cl), (yyvsp[0].field));
                                          /* create environment for pattern compilation 
                                             (will be freed in prepare_input() before next command) */
                                          next_environment();
                                        }
#line 2435 "parser.tab.c"
    break;

  case 77:
#line 669 "parser.y"
                                        { 
                                          if (generate_code) {
                                            (yyval.cl) = do_subset((yyvsp[-2].field), (yyvsp[0].boolt));
                                            do_timing("Subset computed");
                                          }
                                          else 
                                            (yyval.cl) = NULL;
                                        }
#line 2448 "parser.tab.c"
    break;

  case 78:
#line 679 "parser.y"
                                        {  }
#line 2454 "parser.tab.c"
    break;

  case 79:
#line 682 "parser.y"
                                        { if ((yyvsp[0].cl)) dropcorpus((yyvsp[0].cl), NULL); }
#line 2460 "parser.tab.c"
    break;

  case 80:
#line 683 "parser.y"
                                        { if ((yyvsp[0].cl)) dropcorpus((yyvsp[0].cl), NULL); }
#line 2466 "parser.tab.c"
    break;

  case 81:
#line 686 "parser.y"
                                        {
                                          do_PrintVariableValue((yyvsp[0].strval)); 
                                          cl_free((yyvsp[0].strval));
                                        }
#line 2475 "parser.tab.c"
    break;

  case 82:
#line 694 "parser.y"
                                        {
                                          do_SetVariableValue((yyvsp[-1].strval), (yyvsp[0].varsetting).operator, (yyvsp[0].varsetting).variableValue); 
                                          cl_free((yyvsp[-1].strval));
                                          cl_free((yyvsp[0].varsetting).variableValue);
                                        }
#line 2485 "parser.tab.c"
    break;

  case 83:
#line 702 "parser.y"
                                        {
                                          do_AddSubVariables((yyvsp[-2].strval), /*add*/1, (yyvsp[0].strval));
                                          cl_free((yyvsp[-2].strval));
                                          cl_free((yyvsp[0].strval));
                                        }
#line 2495 "parser.tab.c"
    break;

  case 84:
#line 710 "parser.y"
                                        {
                                          do_AddSubVariables((yyvsp[-2].strval), /*sub*/0, (yyvsp[0].strval));
                                          cl_free((yyvsp[-2].strval));
                                          cl_free((yyvsp[0].strval));
                                        }
#line 2505 "parser.tab.c"
    break;

  case 85:
#line 718 "parser.y"
                                        {
                                          /* create first variable as empty set, then add from the second variable */
                                          char *temp = cl_strdup("");
                                          do_SetVariableValue((yyvsp[-2].strval), '=', temp);         /* cheap trick, this is :o) */
                                          cl_free(temp);
                                          do_AddSubVariables((yyvsp[-2].strval), /*add*/1, (yyvsp[0].strval));
                                          cl_free((yyvsp[-2].strval));
                                          cl_free((yyvsp[0].strval));
                                        }
#line 2519 "parser.tab.c"
    break;

  case 86:
#line 730 "parser.y"
                                        { (yyval.varsetting).variableValue = (yyvsp[0].strval); (yyval.varsetting).operator = '<'; }
#line 2525 "parser.tab.c"
    break;

  case 87:
#line 731 "parser.y"
                                        { (yyval.varsetting).variableValue = (yyvsp[0].strval); (yyval.varsetting).operator = '='; }
#line 2531 "parser.tab.c"
    break;

  case 88:
#line 732 "parser.y"
                                        { (yyval.varsetting).variableValue = (yyvsp[0].strval); (yyval.varsetting).operator = '+'; }
#line 2537 "parser.tab.c"
    break;

  case 89:
#line 733 "parser.y"
                                        { (yyval.varsetting).variableValue = (yyvsp[0].strval); (yyval.varsetting).operator = '-'; }
#line 2543 "parser.tab.c"
    break;

  case 90:
#line 736 "parser.y"
                                        {
                                          const char *msg = NULL;
                                          if ((yyvsp[0].varval).cval != NULL && (yyvsp[0].varval).ival >= 0) 
                                            msg = set_context_option_value((yyvsp[-1].strval), (yyvsp[0].varval).cval, (yyvsp[0].varval).ival);
                                          else if ((yyvsp[0].varval).cval != NULL) {
                                            /* get rid of quotes at start and end of value */
                                            /* -- removed because quotes should be stripped by lexer ({string} rule in parser.l) 
                                            if (($3.cval[0] == '"') && ($3.cval[strlen($3.cval)-1] == '"') || ($3.cval[0] == '\'') && ($3.cval[strlen($3.cval)-1] == '\'') ) {
                                              $3.cval[strlen($3.cval)-1] = '\0';
                                              $3.cval = $3.cval + 1;
                                            }
                                               -- end of removed part of action.*/
                                            msg = set_string_option_value((yyvsp[-1].strval), (yyvsp[0].varval).cval);
                                          }
                                          else
                                            msg = set_integer_option_value((yyvsp[-1].strval), (yyvsp[0].varval).ival);
                                            /* integer covers booleans too! */
                                          if (msg)
                                            cqpmessage(Warning, "Option set error:\n%s", msg);
                                        }
#line 2568 "parser.tab.c"
    break;

  case 91:
#line 756 "parser.y"
                                        {
                                          int opt;
                                          if ((opt = find_option((yyvsp[0].strval))) >= 0)
                                            print_option_value(opt);
                                          else
                                            cqpmessage(Warning, "Unknown option: ``%s''\n", (yyvsp[0].strval));
                                        }
#line 2580 "parser.tab.c"
    break;

  case 92:
#line 763 "parser.y"
                                        { print_option_values(); }
#line 2586 "parser.tab.c"
    break;

  case 93:
#line 768 "parser.y"
                                        { do_set_target((yyvsp[-3].cl), (yyvsp[-2].field), (yyvsp[-1].Anchor).anchor, (yyvsp[-1].Anchor).offset, (yyvsp[0].ival)); }
#line 2592 "parser.tab.c"
    break;

  case 94:
#line 772 "parser.y"
                                        { do_set_target((yyvsp[-2].cl), (yyvsp[-1].field), NoField, 0, 0); }
#line 2598 "parser.tab.c"
    break;

  case 95:
#line 776 "parser.y"
                                        {
                                          if (generate_code) {
                                            old_query_corpus = query_corpus;
                                            query_corpus = (yyvsp[-2].cl);  /* set query_corpus for compiling the ExtConstraint pattern */
                                            next_environment(); /* create environment for pattern compilation (will be freed in prepare_input() before next command) */
                                            do_start_timer();
                                          }
                                        }
#line 2611 "parser.tab.c"
    break;

  case 96:
#line 789 "parser.y"
                                        {
                                          do_set_complex_target((yyvsp[-9].cl), (yyvsp[-8].field), (yyvsp[-7].search_strategy), (yyvsp[-5].boolt), (yyvsp[-3].direction), (yyvsp[-2].ival), (yyvsp[-1].strval), (yyvsp[0].base).field, (yyvsp[0].base).inclusive);
                                          if (generate_code) 
                                            do_timing("``set target ...'' completed");
                                        }
#line 2621 "parser.tab.c"
    break;

  case 97:
#line 798 "parser.y"
                                        {
                                          /* from (match|keyword|target) [inclusive|exclusive] */
                                          (yyval.base).field = (yyvsp[-1].field);
                                          (yyval.base).inclusive = (yyvsp[0].ival);
                                        }
#line 2631 "parser.tab.c"
    break;

  case 98:
#line 803 "parser.y"
                                        { 
                                          (yyval.base).field = MatchField;
                                          (yyval.base).inclusive = 0;
                                        }
#line 2640 "parser.tab.c"
    break;

  case 99:
#line 810 "parser.y"
                                        { (yyval.ival) = 1; }
#line 2646 "parser.tab.c"
    break;

  case 100:
#line 811 "parser.y"
                                        { (yyval.ival) = 0; }
#line 2652 "parser.tab.c"
    break;

  case 101:
#line 812 "parser.y"
                                        { (yyval.ival) = 0; /* default is exclusive */ }
#line 2658 "parser.tab.c"
    break;

  case 102:
#line 815 "parser.y"
                                        { 
                                          (yyval.varval).ival = (yyvsp[0].ival);
                                          (yyval.varval).cval = NULL;
                                          (yyval.varval).ok = 1;
                                        }
#line 2668 "parser.tab.c"
    break;

  case 103:
#line 820 "parser.y"
                                        {
                                          (yyval.varval).ival = -1;
                                          (yyval.varval).cval = (yyvsp[0].strval);
                                          (yyval.varval).ok = 1;
                                        }
#line 2678 "parser.tab.c"
    break;

  case 104:
#line 825 "parser.y"
                                        {
                                          (yyval.varval).ival = -1;
                                          (yyval.varval).cval = (yyvsp[0].strval);
                                          (yyval.varval).ok = 1;
                                        }
#line 2688 "parser.tab.c"
    break;

  case 105:
#line 830 "parser.y"
                                        { (yyval.varval).ival =  1; (yyval.varval).cval = NULL; (yyval.varval).ok = 1; }
#line 2694 "parser.tab.c"
    break;

  case 106:
#line 831 "parser.y"
                                        { (yyval.varval).ival =  1; (yyval.varval).cval = NULL; (yyval.varval).ok = 1; }
#line 2700 "parser.tab.c"
    break;

  case 107:
#line 832 "parser.y"
                                        { (yyval.varval).ival =  0; (yyval.varval).cval = NULL; (yyval.varval).ok = 1; }
#line 2706 "parser.tab.c"
    break;

  case 108:
#line 833 "parser.y"
                                        { (yyval.varval).ival =  0; (yyval.varval).cval = NULL; (yyval.varval).ok = 1; }
#line 2712 "parser.tab.c"
    break;

  case 109:
#line 835 "parser.y"
                                        { (yyval.varval).ival = (yyvsp[-1].ival); (yyval.varval).cval = (yyvsp[0].strval);   (yyval.varval).ok = 1; }
#line 2718 "parser.tab.c"
    break;

  case 110:
#line 838 "parser.y"
                                        { do_info((yyvsp[0].cl)); }
#line 2724 "parser.tab.c"
    break;

  case 111:
#line 839 "parser.y"
                                        { do_info(current_corpus); }
#line 2730 "parser.tab.c"
    break;

  case 112:
#line 852 "parser.y"
                                        { 
                                          do_group((yyvsp[-9].cl), (yyvsp[-8].Anchor).anchor, (yyvsp[-8].Anchor).offset, (yyvsp[-7].strval), (yyvsp[-5].Anchor).anchor, (yyvsp[-5].Anchor).offset, (yyvsp[-4].strval), (yyvsp[-2].ival), (yyvsp[-1].ival), (yyvsp[-6].ival), &((yyvsp[0].redir)), (yyvsp[-3].strval)); 
                                          cl_free((yyvsp[0].redir).name);
                                          cl_free((yyvsp[-3].strval));
                                        }
#line 2740 "parser.tab.c"
    break;

  case 113:
#line 864 "parser.y"
                                        { 
                                          do_group_nosource((yyvsp[-6].cl), (yyvsp[-5].Anchor).anchor, (yyvsp[-5].Anchor).offset, (yyvsp[-4].strval), (yyvsp[-2].ival), (yyvsp[-1].ival), &((yyvsp[0].redir)), (yyvsp[-3].strval));
                                          cl_free((yyvsp[0].redir).name);
                                          cl_free((yyvsp[-3].strval));
                                        }
#line 2750 "parser.tab.c"
    break;

  case 114:
#line 871 "parser.y"
                                        { (yyval.ival) = 0; }
#line 2756 "parser.tab.c"
    break;

  case 115:
#line 872 "parser.y"
                                        { (yyval.ival) = 0; }
#line 2762 "parser.tab.c"
    break;

  case 116:
#line 873 "parser.y"
                                        { (yyval.ival) = 1; }
#line 2768 "parser.tab.c"
    break;

  case 117:
#line 874 "parser.y"
                                        { (yyval.ival) = 1; }
#line 2774 "parser.tab.c"
    break;

  case 118:
#line 878 "parser.y"
                                        { (yyval.ival) = 1; }
#line 2780 "parser.tab.c"
    break;

  case 119:
#line 879 "parser.y"
                                        { (yyval.ival) = 0; }
#line 2786 "parser.tab.c"
    break;

  case 120:
#line 883 "parser.y"
                                        { (yyval.strval) = (yyvsp[0].strval); }
#line 2792 "parser.tab.c"
    break;

  case 121:
#line 884 "parser.y"
                                        { (yyval.strval) = NULL; }
#line 2798 "parser.tab.c"
    break;

  case 122:
#line 891 "parser.y"
                                        { free_tabulation_list(); }
#line 2804 "parser.tab.c"
    break;

  case 123:
#line 893 "parser.y"
                                        { 
                                          print_tabulation((yyvsp[-3].cl), 0, INT_MAX, &((yyvsp[0].redir))); 
                                          cl_free((yyvsp[0].redir).name); 
                                        }
#line 2813 "parser.tab.c"
    break;

  case 124:
#line 898 "parser.y"
                                        { free_tabulation_list(); }
#line 2819 "parser.tab.c"
    break;

  case 125:
#line 904 "parser.y"
                                        {
                                          print_tabulation((yyvsp[-7].cl), (yyvsp[-4].ival), (yyvsp[-2].ival), &((yyvsp[0].redir))); 
                                          cl_free((yyvsp[0].redir).name); 
                                        }
#line 2828 "parser.tab.c"
    break;

  case 126:
#line 910 "parser.y"
                                        { append_tabulation_item((yyvsp[0].tabulation_item)); }
#line 2834 "parser.tab.c"
    break;

  case 127:
#line 913 "parser.y"
                                        { append_tabulation_item((yyvsp[0].tabulation_item)); }
#line 2840 "parser.tab.c"
    break;

  case 128:
#line 917 "parser.y"
                                        {
                                          (yyval.tabulation_item) = new_tabulation_item();
                                          (yyval.tabulation_item)->attribute_name = (yyvsp[0].AttributeSpecification).name;
                                          (yyval.tabulation_item)->flags   = (yyvsp[0].AttributeSpecification).flags;
                                          (yyval.tabulation_item)->anchor1 = (yyvsp[-1].AnchorPair).anchor1;
                                          (yyval.tabulation_item)->offset1 = (yyvsp[-1].AnchorPair).offset1;
                                          (yyval.tabulation_item)->anchor2 = (yyvsp[-1].AnchorPair).anchor2;
                                          (yyval.tabulation_item)->offset2 = (yyvsp[-1].AnchorPair).offset2;
                                        }
#line 2854 "parser.tab.c"
    break;

  case 129:
#line 928 "parser.y"
                                        {
                                          (yyval.AnchorPair).anchor1 = (yyval.AnchorPair).anchor2 = (yyvsp[0].Anchor).anchor; 
                                          (yyval.AnchorPair).offset1 = (yyval.AnchorPair).offset2 = (yyvsp[0].Anchor).offset; 
                                        }
#line 2863 "parser.tab.c"
    break;

  case 130:
#line 934 "parser.y"
                                        {
                                          (yyval.AnchorPair).anchor1 = (yyvsp[-2].Anchor).anchor; 
                                          (yyval.AnchorPair).offset1 = (yyvsp[-2].Anchor).offset;
                                          (yyval.AnchorPair).anchor2 = (yyvsp[0].Anchor).anchor;
                                          (yyval.AnchorPair).offset2 = (yyvsp[0].Anchor).offset;
                                        }
#line 2874 "parser.tab.c"
    break;

  case 131:
#line 943 "parser.y"
                                        { 
                                          (yyval.AttributeSpecification).name  = (yyvsp[-1].strval); 
                                          (yyval.AttributeSpecification).flags = (yyvsp[0].ival); 
                                        }
#line 2883 "parser.tab.c"
    break;

  case 132:
#line 947 "parser.y"
                                        { 
                                          (yyval.AttributeSpecification).name = NULL; 
                                          (yyval.AttributeSpecification).flags = 0; 
                                        }
#line 2892 "parser.tab.c"
    break;

  case 133:
#line 961 "parser.y"
                                        {
                                          int ok;
                                          if ((yyvsp[-1].cl) && generate_code) {
                                            do_start_timer();
                                            ok = SortSubcorpus((yyvsp[-1].cl), (yyvsp[0].sortclause), 0, NULL);
                                            FreeSortClause((yyvsp[0].sortclause));
                                            do_timing("Query result sorted");
                                            if (autoshow && ok && ((yyvsp[-1].cl)->size > 0))
                                              cat_listed_corpus((yyvsp[-1].cl), NULL, 0, -1, GlobalPrintMode);
                                          }
                                        }
#line 2908 "parser.tab.c"
    break;

  case 134:
#line 975 "parser.y"
                                        {
                                          int ok;
                                          if ((yyvsp[-2].cl) && generate_code) {
                                            do_start_timer();
                                            ok = SortSubcorpusRandomize((yyvsp[-2].cl), (yyvsp[0].ival));
                                            do_timing("Query result randomized");
                                            if (autoshow && ok && ((yyvsp[-2].cl)->size > 0))
                                              cat_listed_corpus((yyvsp[-2].cl), NULL, 0, -1, GlobalPrintMode);
                                          }
                                        }
#line 2923 "parser.tab.c"
    break;

  case 135:
#line 989 "parser.y"
                                        { 
                                          if ((yyvsp[-3].cl) && generate_code) {
                                            SortSubcorpus((yyvsp[-3].cl), (yyvsp[-2].sortclause), ((yyvsp[-1].ival) >= 1) ? (yyvsp[-1].ival) : 1, &((yyvsp[0].redir)));
                                            FreeSortClause((yyvsp[-2].sortclause));
                                            cl_free((yyvsp[0].redir).name);
                                          }
                                        }
#line 2935 "parser.tab.c"
    break;

  case 136:
#line 999 "parser.y"
                                        { (yyval.sortclause) = (yyvsp[0].sortclause); }
#line 2941 "parser.tab.c"
    break;

  case 137:
#line 1000 "parser.y"
                                        { (yyval.sortclause) = NULL; }
#line 2947 "parser.tab.c"
    break;

  case 138:
#line 1008 "parser.y"
                                        {
                                          if (generate_code) {
                                            (yyval.sortclause) = cl_malloc(sizeof(SortClauseBuffer));
                                            (yyval.sortclause)->attribute_name  = (yyvsp[-4].strval);
                                            (yyval.sortclause)->flags           = (yyvsp[-3].ival);
                                            (yyval.sortclause)->anchor1         = (yyvsp[-2].AnchorPair).anchor1;
                                            (yyval.sortclause)->offset1         = (yyvsp[-2].AnchorPair).offset1;
                                            (yyval.sortclause)->anchor2         = (yyvsp[-2].AnchorPair).anchor2;
                                            (yyval.sortclause)->offset2         = (yyvsp[-2].AnchorPair).offset2;
                                            (yyval.sortclause)->sort_ascending  = (yyvsp[-1].ival);
                                            (yyval.sortclause)->sort_reverse    = (yyvsp[0].ival);
                                          }
                                          else
                                            (yyval.sortclause) = NULL;
                                        }
#line 2967 "parser.tab.c"
    break;

  case 139:
#line 1026 "parser.y"
                                        {
                                          (yyval.AnchorPair).anchor1 = (yyval.AnchorPair).anchor2 = (yyvsp[0].Anchor).anchor; 
                                          (yyval.AnchorPair).offset1 = (yyval.AnchorPair).offset2 = (yyvsp[0].Anchor).offset; 
                                        }
#line 2976 "parser.tab.c"
    break;

  case 140:
#line 1033 "parser.y"
                                        {
                                          (yyval.AnchorPair).anchor1 = (yyvsp[-2].Anchor).anchor; 
                                          (yyval.AnchorPair).offset1 = (yyvsp[-2].Anchor).offset;
                                          (yyval.AnchorPair).anchor2 = (yyvsp[0].Anchor).anchor; 
                                          (yyval.AnchorPair).offset2 = (yyvsp[0].Anchor).offset; 
                                        }
#line 2987 "parser.tab.c"
    break;

  case 141:
#line 1039 "parser.y"
                                        { 
                                          (yyval.AnchorPair).anchor1 = MatchField;
                                          (yyval.AnchorPair).offset1 = 0;
                                          (yyval.AnchorPair).anchor2 = MatchEndField; 
                                          (yyval.AnchorPair).offset2 = 0; 
                                        }
#line 2998 "parser.tab.c"
    break;

  case 142:
#line 1047 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3004 "parser.tab.c"
    break;

  case 143:
#line 1048 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3010 "parser.tab.c"
    break;

  case 144:
#line 1049 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3016 "parser.tab.c"
    break;

  case 145:
#line 1052 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3022 "parser.tab.c"
    break;

  case 146:
#line 1053 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3028 "parser.tab.c"
    break;

  case 147:
#line 1062 "parser.y"
                                        { do_reduce((yyvsp[-3].cl), (yyvsp[-1].ival), (yyvsp[0].ival)); }
#line 3034 "parser.tab.c"
    break;

  case 148:
#line 1068 "parser.y"
                                        { apply_range_set_operation((yyvsp[-3].cl), RMaximalMatches, NULL, NULL); }
#line 3040 "parser.tab.c"
    break;

  case 149:
#line 1072 "parser.y"
                                        { do_cut((yyvsp[-1].cl), 0, (yyvsp[0].ival)-1); }
#line 3046 "parser.tab.c"
    break;

  case 150:
#line 1077 "parser.y"
                                        { do_cut((yyvsp[-2].cl), (yyvsp[-1].ival), (yyvsp[0].ival)); }
#line 3052 "parser.tab.c"
    break;

  case 151:
#line 1080 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3058 "parser.tab.c"
    break;

  case 152:
#line 1081 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3064 "parser.tab.c"
    break;

  case 153:
#line 1087 "parser.y"
                                        {
                                          if ((yyvsp[-2].cl) && generate_code)
                                            do_delete_lines((yyvsp[-2].cl), (yyvsp[0].field), SELECTED_LINES); 
                                        }
#line 3073 "parser.tab.c"
    break;

  case 154:
#line 1094 "parser.y"
                                        {
                                          if ((yyvsp[-2].cl) && generate_code)
                                            do_delete_lines((yyvsp[-2].cl), (yyvsp[0].field), UNSELECTED_LINES); 
                                        }
#line 3082 "parser.tab.c"
    break;

  case 155:
#line 1100 "parser.y"
                                        {
                                          if ((yyvsp[-1].cl) && generate_code)
                                            do_delete_lines_num((yyvsp[-1].cl), (yyvsp[0].Distance).mindist, (yyvsp[0].Distance).maxdist);
                                        }
#line 3091 "parser.tab.c"
    break;

  case 156:
#line 1106 "parser.y"
                                        { 
                                          (yyval.Distance).mindist = (yyvsp[0].ival); 
                                          (yyval.Distance).maxdist = (yyvsp[0].ival);
                                        }
#line 3100 "parser.tab.c"
    break;

  case 157:
#line 1112 "parser.y"
                                        { 
                                          (yyval.Distance).mindist = (yyvsp[-2].ival); 
                                          (yyval.Distance).maxdist = (yyvsp[0].ival); 
                                        }
#line 3109 "parser.tab.c"
    break;

  case 158:
#line 1121 "parser.y"
                                        { do_sleep((yyvsp[0].ival)); }
#line 3115 "parser.tab.c"
    break;

  case 159:
#line 1128 "parser.y"
                                        { do_size((yyvsp[-1].cl), (yyvsp[0].field)); }
#line 3121 "parser.tab.c"
    break;

  case 160:
#line 1130 "parser.y"
                                        { 
                                          do_printVariableSize((yyvsp[0].strval));
                                          cl_free((yyvsp[0].strval));
                                        }
#line 3130 "parser.tab.c"
    break;

  case 161:
#line 1138 "parser.y"
                                        {
                                          do_dump((yyvsp[-1].cl), 0, INT_MAX, &((yyvsp[0].redir))); 
                                          cl_free((yyvsp[0].redir).name); 
                                        }
#line 3139 "parser.tab.c"
    break;

  case 162:
#line 1148 "parser.y"
                                        {
                                          do_dump((yyvsp[-5].cl), (yyvsp[-3].ival), (yyvsp[-1].ival), &((yyvsp[0].redir))); 
                                          cl_free((yyvsp[0].redir).name); 
                                        }
#line 3148 "parser.tab.c"
    break;

  case 163:
#line 1158 "parser.y"
                                        {
                                          do_undump((yyvsp[-3].strval), (yyvsp[-2].ival), !(yyvsp[-1].ival), &((yyvsp[0].in_redir))); 
                                          cl_free((yyvsp[0].in_redir).name); 
                                        }
#line 3157 "parser.tab.c"
    break;

  case 164:
#line 1164 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3163 "parser.tab.c"
    break;

  case 165:
#line 1165 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3169 "parser.tab.c"
    break;

  case 166:
#line 1169 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3175 "parser.tab.c"
    break;

  case 167:
#line 1171 "parser.y"
                                        { 
                                          if ((yyvsp[0].field) == TargetField)
                                            (yyval.ival) = 1;
                                          else {
                                            yyerror("Invalid extension anchor in undump command");
                                            YYABORT;
                                          }
                                        }
#line 3188 "parser.tab.c"
    break;

  case 168:
#line 1181 "parser.y"
                                        { 
                                          if ( ((yyvsp[-1].field) == TargetField && (yyvsp[0].field) == KeywordField) || ((yyvsp[0].field) == TargetField && (yyvsp[-1].field) == KeywordField) ) 
                                            (yyval.ival) = 2;
                                          else {
                                            yyerror("Invalid extension anchor in undump command");
                                            YYABORT;
                                          }
                                        }
#line 3201 "parser.tab.c"
    break;

  case 170:
#line 1196 "parser.y"
                                        {
                                          if ((yyvsp[-2].cl) && (yyvsp[0].sortclause) && (yyvsp[-2].cl)->size > 0) {
                                            SortSubcorpus((yyvsp[-2].cl), (yyvsp[0].sortclause), 0, NULL);
                                            FreeSortClause((yyvsp[0].sortclause));
                                          }
                                          (yyval.cl) = (yyvsp[-2].cl);
                                        }
#line 3213 "parser.tab.c"
    break;

  case 174:
#line 1214 "parser.y"
                                        { (yyval.cl) = do_StandardQuery((yyvsp[-1].ival), (yyvsp[0].ival), (yyvsp[-4].strval)); }
#line 3219 "parser.tab.c"
    break;

  case 175:
#line 1218 "parser.y"
                                        { (yyval.strval) = (yyvsp[-1].strval); }
#line 3225 "parser.tab.c"
    break;

  case 176:
#line 1219 "parser.y"
                                        { (yyval.strval) = NULL; }
#line 3231 "parser.tab.c"
    break;

  case 177:
#line 1225 "parser.y"
                                        { (yyval.cl) = do_MUQuery((yyvsp[-2].evalt), (yyvsp[-1].ival), (yyvsp[0].ival)); }
#line 3237 "parser.tab.c"
    break;

  case 178:
#line 1228 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3243 "parser.tab.c"
    break;

  case 179:
#line 1229 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3249 "parser.tab.c"
    break;

  case 180:
#line 1232 "parser.y"
                                        {
                                          if (generate_code)
                                            CurEnv->match_label = label_lookup(CurEnv->labels, "match", LAB_DEFINED, 1);
                                        }
#line 3258 "parser.tab.c"
    break;

  case 181:
#line 1236 "parser.y"
                                        { 
                                          within_gc = 1; 
                                          if (generate_code)
                                            CurEnv->matchend_label = label_lookup(CurEnv->labels, "matchend", LAB_DEFINED, 1);
                                        }
#line 3268 "parser.tab.c"
    break;

  case 182:
#line 1241 "parser.y"
                                        { within_gc = 0; }
#line 3274 "parser.tab.c"
    break;

  case 183:
#line 1243 "parser.y"
                                        { do_SearchPattern((yyvsp[-5].evalt), (yyvsp[-3].boolt)); }
#line 3280 "parser.tab.c"
    break;

  case 184:
#line 1251 "parser.y"
                                        { 
                                          do_MatchSelector((yyvsp[-4].strval), (yyvsp[-3].ival), (yyvsp[-1].strval), (yyvsp[0].ival));
                                          cl_free((yyvsp[-4].strval));
                                          cl_free((yyvsp[-1].strval));
                                        }
#line 3290 "parser.tab.c"
    break;

  case 186:
#line 1259 "parser.y"
                                        { (yyval.strval) = (yyvsp[0].strval); }
#line 3296 "parser.tab.c"
    break;

  case 187:
#line 1260 "parser.y"
                                        {
                                          if ((yyvsp[0].field) != MatchField) {
                                            yyerror("expected 'match' anchor or label reference");
                                            YYERROR;
                                          }
                                          (yyval.strval) = NULL;
                                        }
#line 3308 "parser.tab.c"
    break;

  case 188:
#line 1269 "parser.y"
                                        { (yyval.strval) = (yyvsp[0].strval); }
#line 3314 "parser.tab.c"
    break;

  case 189:
#line 1270 "parser.y"
                                        {
                                          if ((yyvsp[0].field) != MatchEndField) {
                                            yyerror("expected 'matchend' anchor or label reference");
                                            YYERROR;
                                          }
                                          (yyval.strval) = NULL;
                                        }
#line 3326 "parser.tab.c"
    break;

  case 190:
#line 1279 "parser.y"
                                        { (yyval.ival) = (yyvsp[-1].ival); }
#line 3332 "parser.tab.c"
    break;

  case 191:
#line 1280 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3338 "parser.tab.c"
    break;

  case 192:
#line 1286 "parser.y"
                                        { (yyval.evalt) = reg_disj((yyvsp[-2].evalt), (yyvsp[0].evalt)); }
#line 3344 "parser.tab.c"
    break;

  case 193:
#line 1287 "parser.y"
                                        { (yyval.evalt) = (yyvsp[0].evalt); }
#line 3350 "parser.tab.c"
    break;

  case 194:
#line 1291 "parser.y"
                                        { (yyval.evalt) = reg_seq((yyvsp[-1].evalt), (yyvsp[0].evalt)); }
#line 3356 "parser.tab.c"
    break;

  case 195:
#line 1292 "parser.y"
                                        { (yyval.evalt) = (yyvsp[0].evalt); }
#line 3362 "parser.tab.c"
    break;

  case 196:
#line 1298 "parser.y"
                                        {
                                          if (generate_code) {
                                            (yyval.evalt) = (yyvsp[0].evalt);
                                            (yyval.evalt)->node.left = (yyvsp[-1].evalt);
                                            (yyval.evalt)->node.right = NULL;
                                          }
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3376 "parser.tab.c"
    break;

  case 197:
#line 1307 "parser.y"
                                        {
                                          if (generate_code)
                                            NEW_EVALNODE((yyval.evalt), re_repeat, (yyvsp[-1].evalt), NULL, 0, repeat_inf);
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3387 "parser.tab.c"
    break;

  case 198:
#line 1313 "parser.y"
                                        {
                                          if (generate_code)
                                            NEW_EVALNODE((yyval.evalt), re_repeat, (yyvsp[-1].evalt), NULL, 1, repeat_inf);
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3398 "parser.tab.c"
    break;

  case 199:
#line 1319 "parser.y"
                                        {
                                          if (generate_code)
                                            NEW_EVALNODE((yyval.evalt), re_repeat, (yyvsp[-1].evalt), NULL, 0, 1);
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3409 "parser.tab.c"
    break;

  case 200:
#line 1325 "parser.y"
                                        { (yyval.evalt) = (yyvsp[0].evalt); }
#line 3415 "parser.tab.c"
    break;

  case 201:
#line 1330 "parser.y"
                                        { (yyval.evalt) = (yyvsp[-1].evalt); }
#line 3421 "parser.tab.c"
    break;

  case 202:
#line 1331 "parser.y"
                                        {
                                          if (generate_code)
                                            NEW_EVALLEAF((yyval.evalt), (yyvsp[0].index));
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3432 "parser.tab.c"
    break;

  case 203:
#line 1337 "parser.y"
                                        {
                                          if (generate_code)
                                            NEW_EVALLEAF((yyval.evalt), (yyvsp[0].index));
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3443 "parser.tab.c"
    break;

  case 204:
#line 1343 "parser.y"
                                        {
                                          if (generate_code)
                                            NEW_EVALLEAF((yyval.evalt), (yyvsp[0].index));
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3454 "parser.tab.c"
    break;

  case 205:
#line 1349 "parser.y"
                                        { (yyval.evalt) = (yyvsp[0].evalt); }
#line 3460 "parser.tab.c"
    break;

  case 206:
#line 1354 "parser.y"
                                        { 
                                          if (generate_code)
                                            NEW_EVALNODE((yyval.evalt), re_repeat, NULL, NULL, (yyvsp[-1].ival), (yyvsp[-1].ival));
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3471 "parser.tab.c"
    break;

  case 207:
#line 1363 "parser.y"
                                        {
                                          /* new syntax for consistency with TAB queries */
                                          if (generate_code) 
                                            NEW_EVALNODE((yyval.evalt), re_repeat, NULL, NULL, 0, (yyvsp[-1].ival));
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3483 "parser.tab.c"
    break;

  case 208:
#line 1374 "parser.y"
                                        {
                                          if ((yyvsp[-1].ival) != repeat_inf && (yyvsp[-1].ival) < (yyvsp[-3].ival)) {
                                            yyerror("invalid repetition range (maximum < minimum)");
                                            YYERROR;
                                          }
                                          if (generate_code)
                                            NEW_EVALNODE((yyval.evalt), re_repeat, NULL, NULL, (yyvsp[-3].ival), (yyvsp[-1].ival));
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 3498 "parser.tab.c"
    break;

  case 209:
#line 1386 "parser.y"
                                        { (yyval.index) = do_AnchorPoint((yyvsp[0].field), 0); }
#line 3504 "parser.tab.c"
    break;

  case 210:
#line 1387 "parser.y"
                                        { (yyval.index) = do_AnchorPoint((yyvsp[0].field), 1); }
#line 3510 "parser.tab.c"
    break;

  case 211:
#line 1391 "parser.y"
                                        { (yyval.index) = do_XMLTag((yyvsp[-1].strval), 0, 0, NULL, 0); }
#line 3516 "parser.tab.c"
    break;

  case 212:
#line 1396 "parser.y"
                                        { (yyval.index) = do_XMLTag((yyvsp[-4].strval), 0, (yyvsp[-3].ival), (yyvsp[-2].strval), (yyvsp[-1].ival)); }
#line 3522 "parser.tab.c"
    break;

  case 213:
#line 1397 "parser.y"
                                        { (yyval.index) = do_XMLTag((yyvsp[0].strval), 1, 0, NULL, 0); }
#line 3528 "parser.tab.c"
    break;

  case 214:
#line 1407 "parser.y"
                                        { 
                                          (yyval.evalt) = do_RegionElement((yyvsp[-4].strval), (yyvsp[-6].ival), (yyvsp[-5].strval), (yyvsp[-3].ival), (yyvsp[-2].strval), (yyvsp[-1].ival));
                                          cl_free((yyvsp[-5].strval)); 
                                          cl_free((yyvsp[-4].strval));
                                          cl_free((yyvsp[-2].strval));
                                        }
#line 3539 "parser.tab.c"
    break;

  case 215:
#line 1415 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3545 "parser.tab.c"
    break;

  case 216:
#line 1416 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3551 "parser.tab.c"
    break;

  case 217:
#line 1419 "parser.y"
                                        { (yyval.ival) = (yyvsp[0].ival); }
#line 3557 "parser.tab.c"
    break;

  case 218:
#line 1420 "parser.y"
                                        { (yyval.ival) = OP_EQUAL | OP_NOT; }
#line 3563 "parser.tab.c"
    break;

  case 219:
#line 1421 "parser.y"
                                        { (yyval.ival) = OP_EQUAL; }
#line 3569 "parser.tab.c"
    break;

  case 220:
#line 1422 "parser.y"
                                        { (yyval.ival) = OP_EQUAL; }
#line 3575 "parser.tab.c"
    break;

  case 221:
#line 1427 "parser.y"
                                        { 
                                          (yyval.index) = do_NamedWfPattern((yyvsp[-2].ival), (yyvsp[-1].strval), (yyvsp[0].index)); 
                                          cl_free((yyvsp[-1].strval)); 
                                        }
#line 3584 "parser.tab.c"
    break;

  case 222:
#line 1442 "parser.y"
                                        { (yyval.ival) = IsTarget; }
#line 3590 "parser.tab.c"
    break;

  case 223:
#line 1445 "parser.y"
                                        {
                                          if ((yyvsp[-1].ival) == anchor_number_target)
                                            (yyval.ival) = IsTarget;
                                          else if ((yyvsp[-1].ival) == anchor_number_keyword)
                                            (yyval.ival) = IsKeyword;
                                          else
                                              (yyval.ival) = IsNotTarget; 
                                        }
#line 3603 "parser.tab.c"
    break;

  case 224:
#line 1453 "parser.y"
                                        { (yyval.ival) = IsNotTarget; }
#line 3609 "parser.tab.c"
    break;

  case 227:
#line 1460 "parser.y"
                                        {
                                          if ((yyvsp[0].ival) < 0 || (yyvsp[0].ival) > 9) {
                                            yyerror("expected number between 0 and 9");
                                            YYERROR;
                                          }
                                          (yyval.ival) = (yyvsp[0].ival);
                                        }
#line 3621 "parser.tab.c"
    break;

  case 228:
#line 1469 "parser.y"
                                        { (yyval.strval) = (yyvsp[0].strval); }
#line 3627 "parser.tab.c"
    break;

  case 229:
#line 1470 "parser.y"
                                        { (yyval.strval) = NULL; }
#line 3633 "parser.tab.c"
    break;

  case 230:
#line 1474 "parser.y"
                                        { (yyval.index) = do_WordformPattern((yyvsp[0].boolt), 0); }
#line 3639 "parser.tab.c"
    break;

  case 231:
#line 1475 "parser.y"
                                        { (yyval.index) = do_WordformPattern((yyvsp[0].boolt), 1); }
#line 3645 "parser.tab.c"
    break;

  case 232:
#line 1479 "parser.y"
                                        { (yyval.boolt) = do_StringConstraint((yyvsp[-1].strval), (yyvsp[0].ival)); }
#line 3651 "parser.tab.c"
    break;

  case 233:
#line 1480 "parser.y"
                                        {
                                          (yyval.boolt) = NULL;
                                          if (!FindVariable((yyvsp[0].strval))) {
                                            cqpmessage(Error, "%s: no such variable", (yyvsp[0].strval));
                                            generate_code = 0;
                                          }
                                          else
                                            (yyval.boolt) = do_SimpleVariableReference((yyvsp[0].strval));
                                          cl_free((yyvsp[0].strval));
                                        }
#line 3666 "parser.tab.c"
    break;

  case 234:
#line 1492 "parser.y"
                                        { (yyval.boolt) = (yyvsp[-1].boolt); }
#line 3672 "parser.tab.c"
    break;

  case 235:
#line 1493 "parser.y"
                                        {
                                          if (generate_code) {
                                            NEW_BNODE((yyval.boolt));
                                            (yyval.boolt)->constnode.type = cnode;
                                            (yyval.boolt)->constnode.val  = 1;
                                          }
                                        }
#line 3684 "parser.tab.c"
    break;

  case 236:
#line 1505 "parser.y"
                                        { (yyval.boolt) = (yyvsp[-1].boolt); }
#line 3690 "parser.tab.c"
    break;

  case 237:
#line 1506 "parser.y"
                                        {
                                          if (generate_code) {
                                            NEW_BNODE((yyval.boolt));
                                            (yyval.boolt)->constnode.type = cnode;
                                            (yyval.boolt)->constnode.val  = 1;
                                          }
                                        }
#line 3702 "parser.tab.c"
    break;

  case 238:
#line 1515 "parser.y"
                                        {
                                          /* start with no flags activated (flags = 0) */
                                          int flags = 0, i;
                                          /* process the flag string and activate the right bytes in variable "flags". */
                                          for (i = 0; (yyvsp[0].strval)[i] != '\0'; i++)
                                            switch ((yyvsp[0].strval)[i]) {
                                            case 'c':
                                              flags |= IGNORE_CASE;
                                              break;
                                            case 'd':
                                              flags |= IGNORE_DIAC;
                                              break;
                                            case 'l':
                                              flags = IGNORE_REGEX; /* literal */
                                              break;
                                            default:
                                              cqpmessage(Warning, "Unknown flag %s%c (ignored)", "%", (yyvsp[0].strval)[i]);
                                              break;
                                            }
                                          /* %l supersedes all others */
                                          if (flags & IGNORE_REGEX) {
                                            if (flags != IGNORE_REGEX) 
                                              cqpmessage(Warning, "%%c and %%d flags cannot be combined with %%l (%%c/d ignored)");
                                            flags = IGNORE_REGEX;
                                          }
                                          (yyval.ival) = flags;
                                        }
#line 3734 "parser.tab.c"
    break;

  case 239:
#line 1542 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3740 "parser.tab.c"
    break;

  case 240:
#line 1546 "parser.y"
                                        { (yyval.boolt) = (yyvsp[0].boolt); }
#line 3746 "parser.tab.c"
    break;

  case 241:
#line 1547 "parser.y"
                                        { (yyval.boolt) = NULL; }
#line 3752 "parser.tab.c"
    break;

  case 242:
#line 1553 "parser.y"
                                        { prepare_AlignmentConstraints((yyvsp[0].strval)); }
#line 3758 "parser.tab.c"
    break;

  case 243:
#line 1555 "parser.y"
                                        {
                                          if (generate_code)
                                            CurEnv->negated = (yyvsp[-1].ival);
                                        }
#line 3767 "parser.tab.c"
    break;

  case 244:
#line 1559 "parser.y"
                                        {  }
#line 3773 "parser.tab.c"
    break;

  case 245:
#line 1562 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3779 "parser.tab.c"
    break;

  case 246:
#line 1563 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3785 "parser.tab.c"
    break;

  case 247:
#line 1568 "parser.y"
                                        {
                                          if (generate_code) {
                                            CurEnv->search_context.direction = ctxtdir_leftright; /* ignored in query evaluation */
                                            CurEnv->search_context.space_type = (yyvsp[0].context).space_type;
                                            CurEnv->search_context.size = (yyvsp[0].context).size;
                                            CurEnv->search_context.attrib = (yyvsp[0].context).attrib;
                                          }
                                        }
#line 3798 "parser.tab.c"
    break;

  case 248:
#line 1576 "parser.y"
                                        {
                                          if (generate_code) {
                                            CurEnv->search_context.space_type  = word;
                                            CurEnv->search_context.size  = hard_boundary;
                                            CurEnv->search_context.attrib = NULL;
                                          }
                                        }
#line 3810 "parser.tab.c"
    break;

  case 249:
#line 1585 "parser.y"
                                        { (yyval.ival) = (yyvsp[0].ival); }
#line 3816 "parser.tab.c"
    break;

  case 250:
#line 1586 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3822 "parser.tab.c"
    break;

  case 251:
#line 1589 "parser.y"
                                        { (yyval.ival) = (yyvsp[0].ival); }
#line 3828 "parser.tab.c"
    break;

  case 252:
#line 1590 "parser.y"
                                        { (yyval.ival) = 1; }
#line 3834 "parser.tab.c"
    break;

  case 253:
#line 1593 "parser.y"
                                        { (yyval.ival) = (yyvsp[0].ival); }
#line 3840 "parser.tab.c"
    break;

  case 254:
#line 1594 "parser.y"
                                        { (yyval.ival) = 0; }
#line 3846 "parser.tab.c"
    break;

  case 255:
#line 1598 "parser.y"
                                        { 
                                          if ((yyvsp[0].ival) < 0) {
                                            yyerror("expected a non-negative integer value");
                                            YYERROR;
                                          }
                                          (yyval.ival) = (yyvsp[0].ival);
                                        }
#line 3858 "parser.tab.c"
    break;

  case 256:
#line 1607 "parser.y"
                                        { (yyval.ival) = (yyvsp[0].ival); }
#line 3864 "parser.tab.c"
    break;

  case 257:
#line 1608 "parser.y"
                                        { (yyval.ival) = repeat_inf; }
#line 3870 "parser.tab.c"
    break;

  case 258:
#line 1612 "parser.y"
                                        { 
                                          expansion.direction = (yyvsp[-2].direction);
                                          expansion.space_type = (yyvsp[0].context).space_type;
                                          expansion.size = (yyvsp[0].context).size;
                                          expansion.attrib = (yyvsp[0].context).attrib;
                                        }
#line 3881 "parser.tab.c"
    break;

  case 259:
#line 1618 "parser.y"
                                        { 
                                          expansion.direction = ctxtdir_leftright;
                                          expansion.space_type = word;
                                          expansion.size = 0;
                                          expansion.attrib = NULL;
                                        }
#line 3892 "parser.tab.c"
    break;

  case 260:
#line 1626 "parser.y"
                                        { (yyval.direction) = ctxtdir_left; }
#line 3898 "parser.tab.c"
    break;

  case 261:
#line 1627 "parser.y"
                                        { (yyval.direction) = ctxtdir_right; }
#line 3904 "parser.tab.c"
    break;

  case 262:
#line 1628 "parser.y"
                                        { (yyval.direction) = ctxtdir_leftright; }
#line 3910 "parser.tab.c"
    break;

  case 263:
#line 1631 "parser.y"
                                        { do_Description(&((yyval.context)), (yyvsp[-1].ival), (yyvsp[0].strval)); }
#line 3916 "parser.tab.c"
    break;

  case 264:
#line 1632 "parser.y"
                                        { do_Description(&((yyval.context)), (yyvsp[0].ival), NULL); }
#line 3922 "parser.tab.c"
    break;

  case 265:
#line 1635 "parser.y"
                                        { (yyval.cl) = (yyvsp[0].cl); }
#line 3928 "parser.tab.c"
    break;

  case 266:
#line 1636 "parser.y"
                                        { (yyval.cl) = findcorpus("Last", UNDEF, 0); }
#line 3934 "parser.tab.c"
    break;

  case 267:
#line 1640 "parser.y"
                                        {
                                          CorpusList *cl;
                                          cqpmessage(Message, "CID: %s", (yyvsp[0].strval));
                                          if ((cl = findcorpus((yyvsp[0].strval), UNDEF, 1)) == NULL) {
                                            cqpmessage(Error, "Corpus ``%s'' is undefined", (yyvsp[0].strval));
                                            generate_code = 0;
                                            (yyval.cl) = NULL;
                                          }
                                          else if (!access_corpus(cl)) {
                                            cqpmessage(Warning, "Corpus ``%s'' can't be accessed", (yyvsp[0].strval));
                                            (yyval.cl) = NULL;
                                          }
                                          else
                                            (yyval.cl) = cl;
                                        }
#line 3954 "parser.tab.c"
    break;

  case 268:
#line 1657 "parser.y"
                                        { (yyval.strval) = (yyvsp[0].strval); }
#line 3960 "parser.tab.c"
    break;

  case 269:
#line 1658 "parser.y"
                                        { (yyval.strval) = (yyvsp[0].strval); }
#line 3966 "parser.tab.c"
    break;

  case 270:
#line 1663 "parser.y"
                                        { (yyval.boolt) = bool_implies((yyvsp[-2].boolt), (yyvsp[0].boolt)); }
#line 3972 "parser.tab.c"
    break;

  case 271:
#line 1666 "parser.y"
                                        { (yyval.boolt) = bool_or((yyvsp[-2].boolt), (yyvsp[0].boolt)); }
#line 3978 "parser.tab.c"
    break;

  case 272:
#line 1669 "parser.y"
                                        { (yyval.boolt) = bool_and((yyvsp[-2].boolt), (yyvsp[0].boolt)); }
#line 3984 "parser.tab.c"
    break;

  case 273:
#line 1672 "parser.y"
                                        { (yyval.boolt) = (yyvsp[-1].boolt); }
#line 3990 "parser.tab.c"
    break;

  case 274:
#line 1674 "parser.y"
                                        { (yyval.boolt) = bool_not((yyvsp[0].boolt)); }
#line 3996 "parser.tab.c"
    break;

  case 275:
#line 1675 "parser.y"
                                        { (yyval.boolt) = (yyvsp[0].boolt); }
#line 4002 "parser.tab.c"
    break;

  case 276:
#line 1680 "parser.y"
                                        { (yyval.boolt) = do_RelExpr((yyvsp[-2].boolt), (yyvsp[-1].boolo), (yyvsp[0].boolt)); }
#line 4008 "parser.tab.c"
    break;

  case 277:
#line 1684 "parser.y"
                                        {
                                          /* operators for multi-valued attributes (i.e. feature-set p-attributes) */
                                          if ((yyvsp[-2].ival) & OP_NOT) 
                                            (yyval.boolt) = do_RelExpr((yyvsp[-3].boolt), cmp_neq, do_feature_set_string((yyvsp[-1].strval), (yyvsp[-2].ival), (yyvsp[0].ival)));
                                          else 
                                            (yyval.boolt) = do_RelExpr((yyvsp[-3].boolt), cmp_eq,  do_feature_set_string((yyvsp[-1].strval), (yyvsp[-2].ival), (yyvsp[0].ival)));
                                        }
#line 4020 "parser.tab.c"
    break;

  case 278:
#line 1691 "parser.y"
                                        { (yyval.boolt) = do_RelExExpr((yyvsp[0].boolt)); }
#line 4026 "parser.tab.c"
    break;

  case 279:
#line 1695 "parser.y"
                                        { (yyval.ival) = OP_CONTAINS | (yyvsp[-1].ival); }
#line 4032 "parser.tab.c"
    break;

  case 280:
#line 1697 "parser.y"
                                        { (yyval.ival) = OP_MATCHES  | (yyvsp[-1].ival); }
#line 4038 "parser.tab.c"
    break;

  case 281:
#line 1700 "parser.y"
                                        { (yyval.ival) = OP_NOT; }
#line 4044 "parser.tab.c"
    break;

  case 282:
#line 1701 "parser.y"
                                        { (yyval.ival) = 0; }
#line 4050 "parser.tab.c"
    break;

  case 283:
#line 1704 "parser.y"
                                        { (yyval.boolt) = do_LabelReference((yyvsp[0].strval), 0); }
#line 4056 "parser.tab.c"
    break;

  case 284:
#line 1706 "parser.y"
                                        { (yyval.boolt) = do_LabelReference((yyvsp[0].strval), 1); }
#line 4062 "parser.tab.c"
    break;

  case 285:
#line 1707 "parser.y"
                                        { (yyval.boolt) = do_IDReference((yyvsp[0].strval), 0); }
#line 4068 "parser.tab.c"
    break;

  case 286:
#line 1709 "parser.y"
                                        { (yyval.boolt) = do_IDReference((yyvsp[0].strval), 1); }
#line 4074 "parser.tab.c"
    break;

  case 287:
#line 1710 "parser.y"
                                        { (yyval.boolt) = do_IDReference(cl_strdup(field_type_to_name((yyvsp[0].field))), 0); }
#line 4080 "parser.tab.c"
    break;

  case 288:
#line 1711 "parser.y"
                                        { (yyval.boolt) = (yyvsp[0].boolt); }
#line 4086 "parser.tab.c"
    break;

  case 289:
#line 1714 "parser.y"
                                        { (yyval.boolt) = (yyvsp[0].boolt); }
#line 4092 "parser.tab.c"
    break;

  case 290:
#line 1716 "parser.y"
                                        { (yyval.boolt) = do_flagged_string((yyvsp[-1].strval), (yyvsp[0].ival)); }
#line 4098 "parser.tab.c"
    break;

  case 291:
#line 1720 "parser.y"
                                        { (yyval.boolt) = do_flagged_re_variable((yyvsp[-2].strval), (yyvsp[0].ival)); }
#line 4104 "parser.tab.c"
    break;

  case 292:
#line 1721 "parser.y"
                                        { 
                                          if (generate_code) {
                                            if (!FindVariable((yyvsp[0].strval))) {
                                              cqpmessage(Error, "%s: no such variable", (yyvsp[0].strval));
                                              generate_code = 0;
                                              (yyval.boolt) = NULL;
                                            }
                                            else {
                                              NEW_BNODE((yyval.boolt));
                                              (yyval.boolt)->type = var_ref;
                                              (yyval.boolt)->varref.varName = (yyvsp[0].strval);
                                            }
                                          }
                                          else
                                            (yyval.boolt) = NULL;
                                        }
#line 4125 "parser.tab.c"
    break;

  case 293:
#line 1737 "parser.y"
                                        { 
                                          if (generate_code) {
                                            NEW_BNODE((yyval.boolt));
                                            (yyval.boolt)->type = int_leaf;
                                            (yyval.boolt)->leaf.ctype.iconst = (yyvsp[0].ival);
                                          }
                                          else
                                            (yyval.boolt) = NULL;
                                        }
#line 4139 "parser.tab.c"
    break;

  case 294:
#line 1746 "parser.y"
                                        { 
                                          if (generate_code) {
                                            NEW_BNODE((yyval.boolt));
                                            (yyval.boolt)->type = float_leaf;
                                            (yyval.boolt)->leaf.ctype.fconst = (yyvsp[0].fval);
                                          }
                                          else
                                            (yyval.boolt) = NULL;
                                        }
#line 4153 "parser.tab.c"
    break;

  case 295:
#line 1757 "parser.y"
                                        { (yyval.boolo) = cmp_lt; }
#line 4159 "parser.tab.c"
    break;

  case 296:
#line 1758 "parser.y"
                                        { (yyval.boolo) = cmp_gt; }
#line 4165 "parser.tab.c"
    break;

  case 297:
#line 1759 "parser.y"
                                        { (yyval.boolo) = cmp_eq; }
#line 4171 "parser.tab.c"
    break;

  case 298:
#line 1760 "parser.y"
                                        { (yyval.boolo) = cmp_neq; }
#line 4177 "parser.tab.c"
    break;

  case 299:
#line 1761 "parser.y"
                                        { (yyval.boolo) = cmp_let; }
#line 4183 "parser.tab.c"
    break;

  case 300:
#line 1762 "parser.y"
                                        { (yyval.boolo) = cmp_get; }
#line 4189 "parser.tab.c"
    break;

  case 301:
#line 1768 "parser.y"
                                        { (yyval.boolt) = do_FunctionCall((yyvsp[-3].strval), (yyvsp[-1].apl)); }
#line 4195 "parser.tab.c"
    break;

  case 302:
#line 1771 "parser.y"
                                        { (yyval.apl) = (yyvsp[0].apl); }
#line 4201 "parser.tab.c"
    break;

  case 303:
#line 1774 "parser.y"
                                        { 
                                          ActualParamList *last;
                                          if (generate_code) {
                                            assert((yyvsp[-2].apl) != NULL);
                                            last = (yyvsp[-2].apl);
                                            while (last->next)
                                              last = last->next;
                                            last->next = (yyvsp[0].apl);
                                            (yyval.apl) = (yyvsp[-2].apl);
                                          }
                                          else
                                            (yyval.apl) = NULL;
                                        }
#line 4219 "parser.tab.c"
    break;

  case 304:
#line 1789 "parser.y"
                                        { 
                                          if (generate_code) {
                                            (yyval.apl) = (ActualParamList *)cl_malloc(sizeof(ActualParamList));
                                            (yyval.apl)->param = (yyvsp[0].boolt);
                                            (yyval.apl)->next = NULL;
                                          }
                                          else
                                            (yyval.apl) = NULL;
                                        }
#line 4233 "parser.tab.c"
    break;

  case 305:
#line 1800 "parser.y"
                                        { (yyval.strval) = (yyvsp[0].strval); }
#line 4239 "parser.tab.c"
    break;

  case 306:
#line 1803 "parser.y"
                                        { (yyval.evalt) = (yyvsp[0].evalt); }
#line 4245 "parser.tab.c"
    break;

  case 307:
#line 1804 "parser.y"
                                        { (yyval.evalt) = (yyvsp[0].evalt); }
#line 4251 "parser.tab.c"
    break;

  case 308:
#line 1805 "parser.y"
                                        { 
                                          if (generate_code)
                                            NEW_EVALLEAF((yyval.evalt), (yyvsp[0].index));
                                          else
                                            (yyval.evalt) = NULL;
                                        }
#line 4262 "parser.tab.c"
    break;

  case 309:
#line 1819 "parser.y"
                                        { (yyval.evalt) = do_MeetStatement((yyvsp[-4].evalt), (yyvsp[-2].evalt), &((yyvsp[-1].context)), 0 != (yyvsp[-3].ival)); }
#line 4268 "parser.tab.c"
    break;

  case 310:
#line 1823 "parser.y"
                                        { 
                                          (yyval.context).space_type = word;
                                          (yyval.context).size = (yyvsp[-1].ival);
                                          (yyval.context).size2 = (yyvsp[0].ival);
                                          (yyval.context).attrib = NULL;
                                        }
#line 4279 "parser.tab.c"
    break;

  case 311:
#line 1829 "parser.y"
                                        { do_StructuralContext(&((yyval.context)), (yyvsp[0].strval)); }
#line 4285 "parser.tab.c"
    break;

  case 312:
#line 1830 "parser.y"
                                        {
                                          (yyval.context).space_type = word;
                                          (yyval.context).size = 1;
                                          (yyval.context).size2 = 1;
                                          (yyval.context).attrib = NULL;
                                        }
#line 4296 "parser.tab.c"
    break;

  case 313:
#line 1842 "parser.y"
                                        { (yyval.evalt) = do_UnionStatement((yyvsp[-2].evalt), (yyvsp[-1].evalt)); }
#line 4302 "parser.tab.c"
    break;

  case 314:
#line 1847 "parser.y"
                                        { (yyval.cl) = do_TABQuery((yyvsp[-1].evalt)); }
#line 4308 "parser.tab.c"
    break;

  case 315:
#line 1851 "parser.y"
                                        { (yyval.evalt) = make_first_tabular_pattern((yyvsp[-1].index), (yyvsp[0].evalt)); }
#line 4314 "parser.tab.c"
    break;

  case 316:
#line 1856 "parser.y"
                                        { (yyval.evalt) = add_tabular_pattern((yyvsp[-2].evalt), &((yyvsp[-1].context)), (yyvsp[0].index)); }
#line 4320 "parser.tab.c"
    break;

  case 317:
#line 1857 "parser.y"
                                        { (yyval.evalt) = NULL; }
#line 4326 "parser.tab.c"
    break;

  case 318:
#line 1860 "parser.y"
                                        { do_OptDistance(&((yyval.context)), (yyvsp[-1].ival) + 1, (yyvsp[-1].ival) + 1); }
#line 4332 "parser.tab.c"
    break;

  case 319:
#line 1865 "parser.y"
                                        { 
                                          if ((yyvsp[-1].ival) == repeat_inf)
                                            do_OptDistance(&((yyval.context)), (yyvsp[-3].ival) + 1, repeat_inf);
                                          else {
                                            if ((yyvsp[-1].ival) < (yyvsp[-3].ival)) {
                                              yyerror("invalid distance range (maximum < minimum)");
                                              YYERROR;
                                            }
                                            do_OptDistance(&((yyval.context)), (yyvsp[-3].ival) + 1, (yyvsp[-1].ival) + 1);
                                          } 
                                        }
#line 4348 "parser.tab.c"
    break;

  case 320:
#line 1876 "parser.y"
                                        { do_OptDistance(&((yyval.context)), 1, (yyvsp[-1].ival) + 1); }
#line 4354 "parser.tab.c"
    break;

  case 321:
#line 1877 "parser.y"
                                        { do_OptDistance(&((yyval.context)), 1, repeat_inf); }
#line 4360 "parser.tab.c"
    break;

  case 322:
#line 1878 "parser.y"
                                        { do_OptDistance(&((yyval.context)), 2, repeat_inf); }
#line 4366 "parser.tab.c"
    break;

  case 323:
#line 1879 "parser.y"
                                        { do_OptDistance(&((yyval.context)), 1, 2); }
#line 4372 "parser.tab.c"
    break;

  case 324:
#line 1880 "parser.y"
                                        { do_OptDistance(&((yyval.context)), 1, 1); }
#line 4378 "parser.tab.c"
    break;

  case 325:
#line 1884 "parser.y"
                                        { add_user_to_list((yyvsp[-1].strval), (yyvsp[0].strval)); }
#line 4384 "parser.tab.c"
    break;

  case 327:
#line 1886 "parser.y"
                                        { add_host_to_list((yyvsp[0].strval)); }
#line 4390 "parser.tab.c"
    break;

  case 328:
#line 1887 "parser.y"
                                        { add_hosts_in_subnet_to_list((yyvsp[0].strval)); }
#line 4396 "parser.tab.c"
    break;

  case 329:
#line 1888 "parser.y"
                                        { add_host_to_list(NULL); }
#line 4402 "parser.tab.c"
    break;

  case 332:
#line 1897 "parser.y"
                                        { add_grant_to_last_user((yyvsp[0].strval)); }
#line 4408 "parser.tab.c"
    break;

  case 334:
#line 1909 "parser.y"
                                        {
                                          if (enable_macros) 
                                            define_macro((yyvsp[-4].strval), (yyvsp[-2].ival), NULL, (yyvsp[0].strval));
                                          else 
                                            cqpmessage(Error, "CQP macros not enabled.");
                                          /* don't forget to free the allocated strings */
                                          cl_free((yyvsp[0].strval));
                                          cl_free((yyvsp[-4].strval));
                                        }
#line 4422 "parser.tab.c"
    break;

  case 335:
#line 1924 "parser.y"
                                        {
                                          if (enable_macros) 
                                            define_macro((yyvsp[-4].strval), 0, (yyvsp[-2].strval), (yyvsp[0].strval));
                                          else 
                                             cqpmessage(Error, "CQP macros not enabled.");
                                          /* don't forget to free the allocated strings */
                                          cl_free((yyvsp[0].strval));  
                                          cl_free((yyvsp[-2].strval));
                                          cl_free((yyvsp[-4].strval));
                                        }
#line 4437 "parser.tab.c"
    break;

  case 336:
#line 1937 "parser.y"
                                        {
                                          load_macro_file((yyvsp[0].strval));
                                          /* don't forget to free the allocated string */
                                          cl_free((yyvsp[0].strval));  
                                        }
#line 4447 "parser.tab.c"
    break;

  case 339:
#line 1948 "parser.y"
                                        { list_macros(NULL); }
#line 4453 "parser.tab.c"
    break;

  case 340:
#line 1949 "parser.y"
                                        {
                                          list_macros((yyvsp[0].strval));
                                          cl_free((yyvsp[0].strval));
                                        }
#line 4462 "parser.tab.c"
    break;

  case 341:
#line 1958 "parser.y"
                                        {
                                          print_macro_definition((yyvsp[-3].strval), (yyvsp[-1].ival));
                                          cl_free((yyvsp[-3].strval));
                                        }
#line 4471 "parser.tab.c"
    break;

  case 342:
#line 1967 "parser.y"
                                        {
                                          int l1 = strlen((yyvsp[-1].strval)), l2 = strlen((yyvsp[0].strval));
                                          char *s = (char *)cl_malloc(l1 + l2 + 2);
                                          strcpy(s, (yyvsp[-1].strval)); s[l1] = ' ';
                                          strcpy(s+l1+1, (yyvsp[0].strval));
                                          s[l1+l2+1] = '\0';
                                          cl_free((yyvsp[-1].strval));
                                          cl_free((yyvsp[0].strval));
                                          (yyval.strval) = s;
                                        }
#line 4486 "parser.tab.c"
    break;

  case 343:
#line 1977 "parser.y"
                                        { (yyval.strval) = (yyvsp[0].strval); }
#line 4492 "parser.tab.c"
    break;

  case 344:
#line 1981 "parser.y"
                                        { cl_randomize(); }
#line 4498 "parser.tab.c"
    break;

  case 345:
#line 1982 "parser.y"
                                        { cl_set_seed((yyvsp[0].ival)); }
#line 4504 "parser.tab.c"
    break;

  case 347:
#line 1991 "parser.y"
                                        { (yyval.field) = (yyvsp[0].field); }
#line 4510 "parser.tab.c"
    break;

  case 348:
#line 1992 "parser.y"
                                        { (yyval.field) = NoField; }
#line 4516 "parser.tab.c"
    break;

  case 357:
#line 2008 "parser.y"
                                        { (yyval.Anchor).anchor = (yyvsp[0].field); (yyval.Anchor).offset = 0; }
#line 4522 "parser.tab.c"
    break;

  case 358:
#line 2009 "parser.y"
                                        { (yyval.Anchor).anchor = (yyvsp[-3].field); (yyval.Anchor).offset = (yyvsp[-1].ival); }
#line 4528 "parser.tab.c"
    break;


#line 4532 "parser.tab.c"

      default: break;
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2012 "parser.y"


