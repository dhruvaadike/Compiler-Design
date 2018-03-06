/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ENDPGM = 258,
    DECL = 259,
    ENDDECL = 260,
    T = 261,
    F = 262,
    INT = 263,
    BOOL = 264,
    NUM = 265,
    ID = 266,
    PLUS = 267,
    MUL = 268,
    ASGN = 269,
    READ = 270,
    WRITE = 271,
    MINUS = 272,
    NEWLINE = 273,
    LT = 274,
    GT = 275,
    DEQ = 276,
    ELSE = 277,
    IF = 278,
    THEN = 279,
    ENDIF = 280,
    WHILE = 281,
    DO = 282,
    EWHILE = 283
  };
#endif
/* Tokens.  */
#define ENDPGM 258
#define DECL 259
#define ENDDECL 260
#define T 261
#define F 262
#define INT 263
#define BOOL 264
#define NUM 265
#define ID 266
#define PLUS 267
#define MUL 268
#define ASGN 269
#define READ 270
#define WRITE 271
#define MINUS 272
#define NEWLINE 273
#define LT 274
#define GT 275
#define DEQ 276
#define ELSE 277
#define IF 278
#define THEN 279
#define ENDIF 280
#define WHILE 281
#define DO 282
#define EWHILE 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 19 "stage6.y" /* yacc.c:1909  */

    struct Tnode * nptr;

#line 114 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
