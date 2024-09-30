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

#line 102 "registry.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE creglval;

int cregparse (void);

#endif /* !YY_CREG_REGISTRY_TAB_H_INCLUDED  */
