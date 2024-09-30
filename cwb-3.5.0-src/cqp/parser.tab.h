/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 228 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
