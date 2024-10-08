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


/* Substitute the variable and function names.  */
#define yyparse         cregparse
#define yylex           creglex
#define yyerror         cregerror
#define yydebug         cregdebug
#define yynerrs         cregnerrs
#define yylval          creglval
#define yychar          cregchar

/* First part of user prologue.  */
#line 21 "registry.y"


#include <ctype.h>

#include "globals.h"

#include "corpus.h"
#include "attributes.h"

/*
 * note that flex/bison run with "creg" specified as their prefix. So cregerror is yyerror, etc. 
 */

extern int creglex();

Corpus *cregcorpus = NULL;
Attribute *cregattrib = NULL;

char cregestring[1024];

/* ====================================================================== */

#define cregSetAttrComponentPath(attr, cid, path) \
{ \
  if (!declare_component(attr, cid, path)) { \
    sprintf(cregestring, "Component %s with path %s declared twice" \
            " (or internal error)", cid_name(cid), path); \
    cl_free(path); \
    cregerror(cregestring); \
  } \
}

void cregerror_cleanup(char *message)
{
  fprintf(stderr, "REGISTRY ERROR (%s/%s): %s\n", cregin_path, cregin_name, message);

  if (cregattrib)
    cl_delete_attribute(cregattrib);
  cregattrib = NULL;

  if (cregcorpus != NULL)
    cl_delete_corpus(cregcorpus);
  cregcorpus = NULL;
}

#define cregerror(message) { cregerror_cleanup(message); YYERROR; }

/* ====================================================================== */


#line 128 "registry.tab.c"

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
#ifndef YY_CREG_REGISTRY_TAB_H_INCLUDED
# define YY_CREG_REGISTRY_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int cregdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NAME_SYM = 258,
    ID_SYM = 259,
    INFO_SYM = 260,
    HOME_SYM = 261,
    ATTRIBUTE_SYM = 262,
    DIR_SYM = 263,
    CORPUS_SYM = 264,
    REVCORP_SYM = 265,
    REVCIDX_SYM = 266,
    FREQS_SYM = 267,
    LEXICON_SYM = 268,
    LEXIDX_SYM = 269,
    LEXSRT_SYM = 270,
    STRUCTURE_SYM = 271,
    ALIGNED_SYM = 272,
    DYNAMIC_SYM = 273,
    DOTS_SYM = 274,
    IGNORE_SYM = 275,
    ADMIN_SYM = 276,
    ACCESS_SYM = 277,
    USER_SYM = 278,
    GROUP_SYM = 279,
    ASSERT_SYM = 280,
    HOST_SYM = 281,
    PROPERTY_SYM = 282,
    IDENTIFIER = 283,
    STRING = 284,
    NUMBER = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 98 "registry.y"

  char    *strval;
  int      ival;
  void    *args;
  void    *attr;

  IDList   idlist;

  struct {
    int status;
    char *path;
  } storage;

#line 225 "registry.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE creglval;

int cregparse (void);

#endif /* !YY_CREG_REGISTRY_TAB_H_INCLUDED  */



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
typedef yytype_int8 yy_state_t;

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
#define YYLAST   97

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

#define YYUNDEFTOK  2
#define YYMAXUTOK   285


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,     2,     2,    36,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    35,     2,
       2,    37,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   168,   168,   168,   190,   193,   199,   196,   211,   212,
     215,   216,   219,   220,   223,   225,   228,   230,   233,   235,
     238,   241,   242,   245,   245,   252,   252,   255,   259,   258,
     270,   281,   292,   323,   325,   329,   334,   339,   340,   352,
     359,   366,   367,   370,   371,   374,   375,   376,   377,   378,
     379,   380,   381,   384,   385,   388,   389,   396,   402,   405,
     408,   409,   412,   416
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME_SYM", "ID_SYM", "INFO_SYM",
  "HOME_SYM", "ATTRIBUTE_SYM", "DIR_SYM", "CORPUS_SYM", "REVCORP_SYM",
  "REVCIDX_SYM", "FREQS_SYM", "LEXICON_SYM", "LEXIDX_SYM", "LEXSRT_SYM",
  "STRUCTURE_SYM", "ALIGNED_SYM", "DYNAMIC_SYM", "DOTS_SYM", "IGNORE_SYM",
  "ADMIN_SYM", "ACCESS_SYM", "USER_SYM", "GROUP_SYM", "ASSERT_SYM",
  "HOST_SYM", "PROPERTY_SYM", "IDENTIFIER", "STRING", "NUMBER", "'{'",
  "'}'", "'('", "')'", "':'", "','", "'='", "$accept", "Registry", "$@1",
  "Declaration", "Header", "$@2", "OptInfo", "OptHome", "OptAdmin",
  "OptUserAccessClause", "OptGroupAccessClause", "OptHostAccessClause",
  "NameDecl", "IDDecl", "Attributes", "$@3", "$@4", "Attribute", "$@5",
  "StorageSpec", "AttrBody", "ArgList", "SingleArg", "OptFieldDefs",
  "FieldDefs", "FieldDef", "path", "id", "IDList", "string",
  "OptProperties", "Property", YY_NULLPTR
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
     285,   123,   125,    40,    41,    58,    44,    61
};
# endif

#define YYPACT_NINF (-78)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      65,   -78,    18,    19,   -78,    14,    24,    25,   -78,   -78,
      45,    45,    45,    45,    45,   -78,   -78,   -78,    45,    61,
     -78,   -78,   -78,    35,    35,    44,    45,    24,   -78,    35,
      73,    31,   -78,   -78,   -78,   -78,   -78,    -7,    35,   -78,
     -78,    35,   -78,    38,   -78,   -78,   -78,   -78,    40,   -78,
     -78,   -78,   -78,    58,    35,    35,    35,    35,    35,    35,
      35,    35,    49,    38,    47,    -7,    24,    45,    57,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,    -7,
     -78,   -78,   -78,    53,    64,    14,   -78,    60,    68,   -78,
     -15,   -78,    62,   -78,   -78,   -78,    -2,   -78,    67,   -78,
      26,    69,   -78,   -78,    51,    42,   -78,   -78
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     1,     0,    27,    22,    59,    20,
       0,     0,     0,     0,     0,     3,     5,    23,     0,    11,
      55,    56,    28,    34,    34,     0,     0,    27,    21,     0,
       9,    42,    31,    33,    53,    54,    30,     0,    34,    24,
      10,     0,     6,    44,    29,    35,    36,    40,     0,    37,
      39,    25,     8,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,     0,     0,    27,     0,    19,    45,
      46,    47,    48,    49,    50,    51,    52,    41,    43,     0,
      38,    26,    12,     0,    15,     0,    58,     0,    17,    32,
       0,    58,     0,    61,    18,    57,     0,    58,     7,    14,
       0,     0,    60,    16,     0,     0,    62,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -21,   -78,   -78,   -78,   -78,   -14,
     -78,   -78,   -54,   -78,    33,   -78,   -22,   -10,   -77,     0,
     -78,   -78
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    15,     6,    53,    42,    30,    68,    88,
      93,    84,     7,    19,    16,    27,    66,    17,    31,    32,
      44,    48,    49,    45,    62,    63,    33,    34,    90,    35,
      98,   102
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      22,    23,    24,    25,    26,     9,    39,    40,    28,    46,
      36,    80,    47,    20,    96,    21,    38,    94,     4,    52,
     100,    20,     5,    21,    51,    85,    20,    50,    21,    18,
      99,    10,    69,    70,    71,    72,    73,    74,    75,    76,
      11,    12,    13,     8,    14,    81,    54,    55,    56,    57,
      58,    59,    60,    61,    20,    50,    21,    82,   103,    20,
       8,    21,    43,    20,     8,    21,     1,    29,    -2,    50,
      20,   106,    21,    20,    64,    21,    65,    37,    41,    67,
      95,    77,    79,    83,    86,    89,    95,    87,   105,     0,
      95,    91,    92,    97,   101,   107,    78,   104
};

static const yytype_int8 yycheck[] =
{
      10,    11,    12,    13,    14,     5,    27,    29,    18,    31,
      24,    65,    19,    28,    91,    30,    26,    32,     0,    41,
      97,    28,     3,    30,    38,    79,    28,    37,    30,     4,
      32,     7,    54,    55,    56,    57,    58,    59,    60,    61,
      16,    17,    18,    29,    20,    66,     8,     9,    10,    11,
      12,    13,    14,    15,    28,    65,    30,    67,    32,    28,
      29,    30,    31,    28,    29,    30,     1,     6,     3,    79,
      28,    29,    30,    28,    34,    30,    36,    33,     5,    21,
      90,    32,    35,    26,    31,    85,    96,    23,    37,    -1,
     100,    31,    24,    31,    27,   105,    63,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    39,    40,     0,     3,    42,    50,    29,    67,
       7,    16,    17,    18,    20,    41,    52,    55,     4,    51,
      28,    30,    65,    65,    65,    65,    65,    53,    65,     6,
      45,    56,    57,    64,    65,    67,    57,    33,    65,    52,
      64,     5,    44,    31,    58,    61,    64,    19,    59,    60,
      65,    57,    64,    43,     8,     9,    10,    11,    12,    13,
      14,    15,    62,    63,    34,    36,    54,    21,    46,    64,
      64,    64,    64,    64,    64,    64,    64,    32,    62,    35,
      60,    52,    65,    26,    49,    60,    31,    23,    47,    67,
      66,    31,    24,    48,    32,    65,    66,    31,    68,    32,
      66,    27,    69,    32,    28,    37,    29,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    40,    39,    39,    41,    43,    42,    44,    44,
      45,    45,    46,    46,    47,    47,    48,    48,    49,    49,
      50,    51,    51,    53,    52,    54,    52,    52,    56,    55,
      55,    55,    55,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    65,    66,    66,    67,
      68,    68,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     0,    10,     2,     0,
       2,     0,     2,     0,     4,     0,     4,     0,     4,     0,
       2,     2,     0,     0,     3,     0,     6,     0,     0,     4,
       3,     3,     8,     1,     0,     1,     1,     1,     3,     1,
       1,     3,     0,     2,     0,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     2,     0,     1,
       2,     0,     4,     4
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
#line 168 "registry.y"
                                    { cregcorpus = (Corpus *)cl_malloc(sizeof(Corpus)); 
                                      cregcorpus->attributes = NULL;
                                      cregcorpus->name = NULL;
                                      cregcorpus->id = NULL;
                                      cregcorpus->path = NULL;
                                      cregcorpus->charset = latin1;  /* default charset is latin1 */
                                      cregcorpus->properties = NULL;
                                      cregcorpus->info_file = NULL;
                                      /*cregcorpus->admin = NULL; */
                                      cregcorpus->groupAccessList = NULL;
                                      cregcorpus->hostAccessList = NULL;
                                      cregcorpus->userAccessList = NULL;
                                      cregcorpus->registry_dir = NULL;
                                      cregcorpus->registry_name = NULL;
                                      cregcorpus->nr_of_loads = 1;
                                      cregcorpus->next = NULL;
                                    }
#line 1492 "registry.tab.c"
    break;

  case 3:
#line 186 "registry.y"
                                    { if (cregcorpus->attributes == NULL) {
                                        cregerror("Illegal corpus declaration -- no attributes defined"); 
                                      }
                                    }
#line 1501 "registry.tab.c"
    break;

  case 4:
#line 190 "registry.y"
                                    { cregerror_cleanup("Error parsing the main Registry structure."); YYABORT; }
#line 1507 "registry.tab.c"
    break;

  case 5:
#line 193 "registry.y"
                                    { /* nop */ }
#line 1513 "registry.tab.c"
    break;

  case 6:
#line 199 "registry.y"
                                    { cregcorpus->name      = (yyvsp[-3].strval);
                                      cregcorpus->id        = (yyvsp[-2].strval);
                                      cregcorpus->path      = (yyvsp[-1].strval);
                                      cregcorpus->info_file = (yyvsp[0].strval);
                                    }
#line 1523 "registry.tab.c"
    break;

  case 8:
#line 211 "registry.y"
                                    { (yyval.strval) = (yyvsp[0].strval); }
#line 1529 "registry.tab.c"
    break;

  case 9:
#line 212 "registry.y"
                                    { (yyval.strval) = NULL; }
#line 1535 "registry.tab.c"
    break;

  case 10:
#line 215 "registry.y"
                                    { (yyval.strval) = (yyvsp[0].strval); }
#line 1541 "registry.tab.c"
    break;

  case 11:
#line 216 "registry.y"
                                    { (yyval.strval) = NULL; }
#line 1547 "registry.tab.c"
    break;

  case 12:
#line 219 "registry.y"
                                    { /* still parses... but does nothing //cregcorpus->admin = $2; */ }
#line 1553 "registry.tab.c"
    break;

  case 13:
#line 220 "registry.y"
                                    { /* still parses... but does nothing //cregcorpus->admin = NULL;  */}
#line 1559 "registry.tab.c"
    break;

  case 14:
#line 224 "registry.y"
                                    { cregcorpus->userAccessList = (yyvsp[-1].idlist); }
#line 1565 "registry.tab.c"
    break;

  case 15:
#line 225 "registry.y"
                                    { cregcorpus->userAccessList = NULL; }
#line 1571 "registry.tab.c"
    break;

  case 16:
#line 229 "registry.y"
                                    { cregcorpus->groupAccessList = (yyvsp[-1].idlist); }
#line 1577 "registry.tab.c"
    break;

  case 17:
#line 230 "registry.y"
                                    { cregcorpus->groupAccessList = NULL; }
#line 1583 "registry.tab.c"
    break;

  case 18:
#line 234 "registry.y"
                                    { cregcorpus->hostAccessList = (yyvsp[-1].idlist); }
#line 1589 "registry.tab.c"
    break;

  case 19:
#line 235 "registry.y"
                                    { cregcorpus->hostAccessList = NULL; }
#line 1595 "registry.tab.c"
    break;

  case 20:
#line 238 "registry.y"
                                    { (yyval.strval) = (yyvsp[0].strval); }
#line 1601 "registry.tab.c"
    break;

  case 21:
#line 241 "registry.y"
                                    { (yyval.strval) = (yyvsp[0].strval); }
#line 1607 "registry.tab.c"
    break;

  case 22:
#line 242 "registry.y"
                                    { (yyval.strval) = NULL; }
#line 1613 "registry.tab.c"
    break;

  case 23:
#line 245 "registry.y"
                                    { 
                                      /* declare components which are not yet declared for local attrs. */
                                      if ((((Attribute *)(yyvsp[0].attr))->any.path == NULL) && (cregcorpus->path != NULL))
                                        ((Attribute *)(yyvsp[0].attr))->any.path = cl_strdup(cregcorpus->path);
                                      declare_default_components((Attribute *)(yyvsp[0].attr));
                                    }
#line 1624 "registry.tab.c"
    break;

  case 25:
#line 252 "registry.y"
                                               {}
#line 1630 "registry.tab.c"
    break;

  case 28:
#line 259 "registry.y"
                                    { 
                                      if ((cregattrib = setup_attribute(cregcorpus, (yyvsp[0].strval), ATT_POS, NULL)) == NULL) {
                                        sprintf(cregestring, 
                                                "Positional attribute %s declared twice -- "
                                                "semantic error", (yyvsp[0].strval));
                                        cl_free((yyvsp[0].strval));
                                        cregerror(cregestring);
                                      }
                                    }
#line 1644 "registry.tab.c"
    break;

  case 29:
#line 268 "registry.y"
                                    { (yyval.attr) = cregattrib; cregattrib = NULL; }
#line 1650 "registry.tab.c"
    break;

  case 30:
#line 271 "registry.y"
                                    { if (((yyval.attr) = setup_attribute(cregcorpus, (yyvsp[-1].strval), ATT_ALIGN, NULL)) == NULL) {
                                        sprintf(cregestring, "Alignment attribute %s declared twice -- "
                                                "semantic error", (yyvsp[-1].strval));
                                        cl_free((yyvsp[-1].strval));
                                        cl_free((yyvsp[0].storage).path);
                                        cregerror(cregestring);
                                      }

                                      ((Attribute *)(yyval.attr))->align.path = (yyvsp[0].storage).path;
                                    }
#line 1665 "registry.tab.c"
    break;

  case 31:
#line 282 "registry.y"
                                    { if (((yyval.attr) = setup_attribute(cregcorpus, (yyvsp[-1].strval), ATT_STRUC, NULL)) == NULL) {
                                        sprintf(cregestring, "Structure attribute %s declared twice -- "
                                                "semantic error", (yyvsp[-1].strval));
                                        cl_free((yyvsp[-1].strval));
                                        cl_free((yyvsp[0].storage).path);
                                        cregerror(cregestring);
                                      }

                                      ((Attribute *)(yyval.attr))->struc.path = (yyvsp[0].storage).path;
                                    }
#line 1680 "registry.tab.c"
    break;

  case 32:
#line 295 "registry.y"
                                    { if (((yyval.attr) = setup_attribute(cregcorpus, (yyvsp[-6].strval), ATT_DYN, NULL)) == NULL) {

                                        DynArg *a;

                                        sprintf(cregestring, "Dynamic attribute %s declared twice -- "
                                                "semantic error", (yyvsp[-6].strval));
                                        cl_free((yyvsp[-6].strval));
                                        cl_free((yyvsp[-1].args));
                                        cl_free((yyvsp[0].strval));

                                        while ((yyvsp[-4].args) != NULL) {
                                          a = (DynArg *)(yyvsp[-4].args);
                                          (yyvsp[-4].args) = ((DynArg *)a)->next;
                                          cl_free(a);
                                        }

                                        cregerror(cregestring);
                                      }

                                      ((Attribute *)(yyval.attr))->dyn.arglist = (yyvsp[-4].args);
                                      ((Attribute *)(yyval.attr))->dyn.res_type = ((DynArg *)(yyvsp[-1].args))->type;
                                      free((yyvsp[-1].args));
                                      ((Attribute *)(yyval.attr))->dyn.call = (yyvsp[0].strval);

                                      ((Attribute *)(yyval.attr))->dyn.path = NULL;
                                    }
#line 1711 "registry.tab.c"
    break;

  case 33:
#line 323 "registry.y"
                                    { (yyval.storage).path = (yyvsp[0].strval); 
                                    }
#line 1718 "registry.tab.c"
    break;

  case 34:
#line 325 "registry.y"
                                    { (yyval.storage).path = NULL;
                                    }
#line 1725 "registry.tab.c"
    break;

  case 35:
#line 329 "registry.y"
                                    { assert(cregattrib != NULL);
                                      if ((cregattrib->any.path == NULL) &&
                                          (cregcorpus->path != NULL))
                                        cregattrib->any.path = cl_strdup(cregcorpus->path);
                                    }
#line 1735 "registry.tab.c"
    break;

  case 36:
#line 334 "registry.y"
                                    { assert(cregattrib != NULL);
                                      cregattrib->any.path = (yyvsp[0].strval); 
                                    }
#line 1743 "registry.tab.c"
    break;

  case 37:
#line 339 "registry.y"
                                    { (yyval.args) = (yyvsp[0].args); }
#line 1749 "registry.tab.c"
    break;

  case 38:
#line 341 "registry.y"
                                    { 
                                      DynArg *last;
                                      assert((yyvsp[-2].args) != NULL);
                                      last = (yyvsp[-2].args); 
                                      while (last->next != NULL) last = (DynArg *)last->next;
                                      
                                      last->next = (yyvsp[0].args); 
                                      (yyval.args) = (yyvsp[-2].args); 
                                    }
#line 1763 "registry.tab.c"
    break;

  case 39:
#line 352 "registry.y"
                                    { (yyval.args) = (DynArg *)makearg((yyvsp[0].strval)); 
                                      if ((yyval.args) == NULL) {
                                        sprintf(cregestring, "Illegal argument type %s or "
                                                "not enough memory -- FATAL ERROR", (yyvsp[0].strval));
                                        cregerror(cregestring);
                                      }
                                    }
#line 1775 "registry.tab.c"
    break;

  case 40:
#line 359 "registry.y"
                                    { (yyval.args) = (DynArg *)makearg("VARARG"); 
                                      if ((yyval.args) == NULL)
                                        cregerror("Internal error while parsing variable "
                                                  "argument list -- FATAL ERROR");
                                    }
#line 1785 "registry.tab.c"
    break;

  case 45:
#line 374 "registry.y"
                                    { cregSetAttrComponentPath(cregattrib, CompDirectory,    (yyvsp[0].strval)); }
#line 1791 "registry.tab.c"
    break;

  case 46:
#line 375 "registry.y"
                                    { cregSetAttrComponentPath(cregattrib, CompCorpus,       (yyvsp[0].strval)); }
#line 1797 "registry.tab.c"
    break;

  case 47:
#line 376 "registry.y"
                                    { cregSetAttrComponentPath(cregattrib, CompRevCorpus,    (yyvsp[0].strval)); }
#line 1803 "registry.tab.c"
    break;

  case 48:
#line 377 "registry.y"
                                    { cregSetAttrComponentPath(cregattrib, CompRevCorpusIdx, (yyvsp[0].strval)); }
#line 1809 "registry.tab.c"
    break;

  case 49:
#line 378 "registry.y"
                                    { cregSetAttrComponentPath(cregattrib, CompCorpusFreqs,  (yyvsp[0].strval)); }
#line 1815 "registry.tab.c"
    break;

  case 50:
#line 379 "registry.y"
                                    { cregSetAttrComponentPath(cregattrib, CompLexicon,      (yyvsp[0].strval)); }
#line 1821 "registry.tab.c"
    break;

  case 51:
#line 380 "registry.y"
                                    { cregSetAttrComponentPath(cregattrib, CompLexiconIdx,   (yyvsp[0].strval)); }
#line 1827 "registry.tab.c"
    break;

  case 52:
#line 381 "registry.y"
                                    { cregSetAttrComponentPath(cregattrib, CompLexiconSrt,   (yyvsp[0].strval)); }
#line 1833 "registry.tab.c"
    break;

  case 53:
#line 384 "registry.y"
                                    { (yyval.strval) = (yyvsp[0].strval); }
#line 1839 "registry.tab.c"
    break;

  case 54:
#line 385 "registry.y"
                                    { (yyval.strval) = (yyvsp[0].strval); }
#line 1845 "registry.tab.c"
    break;

  case 55:
#line 388 "registry.y"
                                    { (yyval.strval) = (yyvsp[0].strval); }
#line 1851 "registry.tab.c"
    break;

  case 56:
#line 389 "registry.y"
                                    { char *nr;
                                      nr = (char *)cl_malloc(16);
                                      sprintf(nr, "%d", (yyvsp[0].ival));
                                      (yyval.strval) = nr;
                                    }
#line 1861 "registry.tab.c"
    break;

  case 57:
#line 396 "registry.y"
                                    { IDList n;
                                      n = (IDList)cl_malloc(sizeof(IDBuf));
                                      n->next = (yyvsp[-1].idlist);
                                      n->string = (yyvsp[0].strval);
                                      (yyval.idlist) = n;
                                    }
#line 1872 "registry.tab.c"
    break;

  case 58:
#line 402 "registry.y"
                                    { (yyval.idlist) = NULL; }
#line 1878 "registry.tab.c"
    break;

  case 59:
#line 405 "registry.y"
                                    { (yyval.strval) = (yyvsp[0].strval); }
#line 1884 "registry.tab.c"
    break;

  case 62:
#line 413 "registry.y"
                                        {
                                          add_corpus_property(cregcorpus, (yyvsp[-2].strval), (yyvsp[0].strval));
                                        }
#line 1892 "registry.tab.c"
    break;

  case 63:
#line 417 "registry.y"
                                        { /* allow IDs and numbers without quotes */
                                          add_corpus_property(cregcorpus, (yyvsp[-2].strval), (yyvsp[0].strval));
                                        }
#line 1900 "registry.tab.c"
    break;


#line 1904 "registry.tab.c"

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
#line 424 "registry.y"




