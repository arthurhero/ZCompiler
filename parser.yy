%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines
%define parser_class_name {parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#ifndef YY_NULLPTR
  #define YY_NULLPTR nullptr
#endif
#include <string>
#include <memory>
#include <vector>
#include <map>
#include "lang.h"
class parser_driver;
using namespace std;

}

// The parsing context
%param { parser_driver &driver }

%define parse.trace
%define parse.error verbose

%code {
#include "parser_driver.h"
#include "lang.h"

using namespace std;
}

%define api.token.prefix {TOK_}
%token
  END     0   "eof"
  ENDLINE     "eol"
  VOID        "void"
  PRINT       "print"
  ENDL        "endl"
  RETURN      "return"
  LCURL       "{"
  RCURL       "}"
  LPAREN      "("
  RPAREN      ")"
  LARROW      "<-"
  RARROW      "->"
  SEMI        ";"
  EQUAL       "="
  EXCL        "!"
  COMMA       ","

  IN          "in"

  PLUS    "+"
  MINUS   "-"
  STAR    "*"
  SLASH   "/"

  LESS    "<"
  GREATER ">"
  LEQ     "<="
  GEQ     ">="
  NEQ     "!="
  LEQUAL  "=="
  AND     "&&"
  OR      "||"

  IF
  ELSE
;

%token <std::string> STRING "string"
%token <std::string> IDENTIFIER "identifier"
%token <int> INT "int"
%token <bool> BOOL "bool"

%type  < shared_ptr<Stm> > Stm
%type  < shared_ptr<Stms> > Stms

%type  < shared_ptr<SAssign> > AssignStm
%type  < shared_ptr<SPrint> > PrintStm
%type  < std::vector<shared_ptr<Exp> > > PrintContent
%type  < shared_ptr<SFunc> > FuncStm
%type  < shared_ptr<SIf> >  IfStm
%type  < shared_ptr<SReturn> >  RetStm

%type  < shared_ptr<Exp> > Exp
%type  < shared_ptr<EApp> > AppExp
%type  < shared_ptr<EVar> > VarExp
%type  < shared_ptr<EFunc> > FuncExp
%type  < shared_ptr<ENumb> > NumExp
%type  < shared_ptr<EBool> > BoExp
%type  < shared_ptr<EString> > StringExp
%type  < std::vector<std::string> >  params
%type  < std::vector<shared_ptr<Exp> > >  Arguments
%type  < shared_ptr<Exp> >  Argument

%parse-param {shared_ptr<Stms> *ret}

%%
%left "||";
%left "&&";
%left "<" ">" "<=" ">=" "==" "!=";
%left "!";
%left "+" "-";
%left "*" "/";

%start prog;

prog:
    Stms "eof"             { *ret = $1; }
|   Stms "eol"             { *ret = $1;
                             (*ret)->exec();
                             exit (0);
                           }
;

Stms:
     %empty             {std::vector< shared_ptr<Stm> > stms = std::vector< shared_ptr<Stm> >();
                         $$=make_shared<Stms>(stms);}
|    Stm Stms           {$2->stms.insert($2->stms.begin(),$1); $$=$2;}
;

Stm:
     IfStm              {$$=$1;}
|    AssignStm          {$$=$1;}
|    PrintStm           {$$=$1;}
|    FuncStm            {$$=$1;}
|    RetStm             {$$=$1;}
;

AssignStm:
     "identifier" "=" Exp ";"       {$$=make_shared<SAssign>($1,$3);}
;

PrintContent:
     StringExp                   {std::vector<shared_ptr<Exp> > PC = std::vector<shared_ptr<Exp> >();
                                  PC.push_back($1);
                                  $$=PC;}
|    PrintContent "+" Exp        {$1.push_back($3); $$=$1;}
|    Exp "+" PrintContent        {$3.push_back($1); $$=$3;}
;

PrintStm:
     "print" "(" PrintContent ")" ";" {$$=make_shared<SPrint>($3);}
|    "print" "(" Exp ")" ";"          {std::vector<shared_ptr<Exp> > PC = std::vector<shared_ptr<Exp> >();
                                        PC.push_back($3);
                                       $$=make_shared<SPrint>(PC);}
;

FuncStm:
     AppExp ";"                       {$$=make_shared<SFunc>($1);}
;

IfStm   :
   IF "(" BoExp ")" "{" Stms "}"                      { $$ = make_shared<SIf>($3,$6); }
|  IF "(" BoExp ")" "{" Stms "}" ELSE "{" Stms "}"     { $$ = make_shared<SIf>($3,$6,$10); }
|  IF "(" BoExp ")" "{" Stms "}" ELSE IfStm    { $$ = make_shared<SIf>($3,$6,$9); }
;

RetStm:
     "return" Exp  ";"                {$$=make_shared<SReturn>($2);}
;


//////////////////////////////////////////////////

Exp:
     "void"             { $$ = make_shared<EVoid>(); }
//|    LetExp             { $$ = $1; }
|    NumExp             { $$ = $1; }
|    BoExp              { $$ = $1; }
|    VarExp             { $$ = $1; }
|    AppExp             { $$ = $1; }
|    FuncExp            { $$ = $1; }
|    StringExp          { $$ = $1; }
|    "(" Exp ")"        { $$ = $2; }
;

FuncExp :
      "(" ")" "->" "{" Stms "}"                 {$$ = make_shared<EFunc>($5);}
|     "(" params ")" "->" "{" Stms "}"          {$$ = make_shared<EFunc>($2, $6);}
;

params :
     "identifier" "," params       {$3.push_back($1); $$=$3;}
|    "identifier"                  {std::vector<std::string> tmp;
                                      tmp.push_back($1);
                                      $$=tmp;}
;

AppExp :
      VarExp "(" ")"                        {$$ = make_shared<EApp>($1);}
|     FuncExp "(" ")"                       {$$ = make_shared<EApp>($1);}
|     VarExp "(" Arguments ")"              {$$ = make_shared<EApp>($3,$1);}
|     FuncExp "(" Arguments ")"             {$$ = make_shared<EApp>($3,$1);}
;

Arguments:
    Argument                         {std::vector<shared_ptr<Exp> > args; args.push_back($1); $$=args;}
|   Argument "," Arguments           {$3.push_back($1); $$=$3;}
;

Argument:
    Exp                         { $$ = $1; }
;

VarExp:
    "identifier"                 {$$ = make_shared<EVar>($1);}
;

BoExp   :   "bool"               { $$ = make_shared<EBool>($1); }
|   "!" Exp                      { $$ = make_shared<EBool>($2); }
|   Exp "<" Exp                  { $$ = make_shared<EBool>($1,Less,$3); }
|   Exp ">" Exp                  { $$ = make_shared<EBool>($1,Greater,$3); }
|   Exp "<=" Exp                  { $$ = make_shared<EBool>($1,Leq,$3); }
|   Exp ">=" Exp                  { $$ = make_shared<EBool>($1,Geq,$3); }
|   Exp "==" Exp                  { $$ = make_shared<EBool>($1,Equal,$3); }
|   Exp "!=" Exp                  { $$ = make_shared<EBool>($1,Neq,$3); }
|   Exp "&&" Exp                  { $$ = make_shared<EBool>($1,And,$3); }
|   Exp "||" Exp                  { $$ = make_shared<EBool>($1,Or,$3); }
|   "(" BoExp ")"                { $$ = $2; }
;

NumExp  :   "int"                 { $$ = make_shared<ENumb>($1); }
|   Exp "+" Exp             { $$ = make_shared<ENumb>($1,'+',$3); }
|   Exp "-" Exp             { $$ = make_shared<ENumb>($1,'-',$3); }
|   Exp "*" Exp             { $$ = make_shared<ENumb>($1,'*',$3); }
|   Exp "/" Exp             { $$ = make_shared<ENumb>($1,'/',$3); }
|   "(" NumExp ")"                { $$ = $2; }
;



StringExp:
    "string"                      { $$ = make_shared<EString>($1); }
|   "endl"                        { $$ = make_shared<EString>("\n"); }
;

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const std::string &m) { driver.error(m); }
