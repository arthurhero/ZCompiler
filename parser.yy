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
  RETURN      "return"
  LCURL       "{"
  RCURL       "}"
  LPAREN      "("
  RPAREN      ")"
  LBRACKET    "["
  RBRACKET    "]"
  LARROW      "<-"
  RARROW      "->"
  SEMI        ";"
  EQUAL       "="
  EXCL        "!"
  AMPER       "&"
  COMMA       ","
  DOT         "."

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
  WHILE
  BREAK     "break"
  CONTINUE  "continue"
  GET       "get"
  REMOVE    "remove"
  INSERT    "insert"
  LENGTH    "length"
;

%token <std::string> STRING "string"
%token <std::string> IDENTIFIER "identifier"
%token <int> INT "int"
%token <bool> BOOL "bool"

%type  < shared_ptr<Stm> > Stm
%type  < shared_ptr<Stms> > Stms

%type  < shared_ptr<SList> > ListStm
%type  < shared_ptr<SAssign> > AssignStm
%type  < shared_ptr<SPrint> > PrintStm
%type  < std::vector<shared_ptr<Exp> > > PrintContent
%type  < shared_ptr<SFunc> > FuncStm

%type  < shared_ptr<SBreak> >  BreakStm
%type  < shared_ptr<SContinue> >  ContinueStm
%type  < shared_ptr<subStms> > subStms
%type  < shared_ptr<SIf> >  IfStm
%type  < shared_ptr<SWhile> >  WhileStm

%type  < shared_ptr<SReturn> >  RetStm

%type  < shared_ptr<Exp> > Exp
%type  < shared_ptr<EList> > ListExp
%type  < shared_ptr<EListOp> > ListOpExp
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
|    WhileStm           {$$=$1;}
|    ListStm            {$$=$1;}
|    BreakStm           {$$=$1;}
|    ContinueStm        {$$=$1;}
|    AssignStm          {$$=$1;}
|    PrintStm           {$$=$1;}
|    FuncStm            {$$=$1;}
|    RetStm             {$$=$1;}
;

ListStm:
     ListOpExp ";"        {$$=make_shared<SList>($1);}
;

AssignStm:
     "identifier" "=" Exp ";"       {$$=make_shared<SAssign>($1,$3);}
|    "*""identifier" "=" Exp ";"       {$$=make_shared<SAssign>($2,$4);$$->is_ref=true;}
;

PrintContent:
     StringExp                   {std::vector<shared_ptr<Exp> > PC = std::vector<shared_ptr<Exp> >();
                                  PC.push_back($1);
                                  $$=PC;}
|    PrintContent "+" Exp        {$1.push_back($3); $$=$1;}
|    Exp "+" PrintContent        {$3.insert($3.begin(),$1); $$=$3;}
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

BreakStm:
    "break" ";"                 {$$=make_shared<SBreak>();}
;

ContinueStm:
    "continue" ";"                 {$$=make_shared<SContinue>();}
;

subStms:
   Stms                            {$$=make_shared<subStms>($1->stms);}
;

IfStm   :
   IF "(" BoExp ")" "{" subStms "}"               { $$ = make_shared<SIf>($3,$6); }
|  IF "(" BoExp ")" "{" subStms "}" ELSE "{" subStms "}"     { $$ = make_shared<SIf>($3,$6,$10); }
|  IF "(" BoExp ")" "{" subStms "}" ELSE IfStm    { $$ = make_shared<SIf>($3,$6,$9); }
;

WhileStm:
   WHILE "(" BoExp ")" "{" subStms "}"            { $$ = make_shared<SWhile>($3,$6); }
;

RetStm:
     "return" Exp  ";"                {$$=make_shared<SReturn>($2);}
;


//////////////////////////////////////////////////

Exp:
     "void"             { $$ = make_shared<EVoid>(); }
|    NumExp             { $$ = $1; }
|    ListExp            { $$ = $1; }
|    ListOpExp          { $$ = $1; }
|    BoExp              { $$ = $1; }
|    VarExp             { $$ = $1; }
|    AppExp             { $$ = $1; }
|    FuncExp            { $$ = $1; }
|    StringExp          { $$ = $1; }
|    "(" Exp ")"        { $$ = $2; }
;

Arguments:
    Argument                         {std::vector<shared_ptr<Exp> > args; args.push_back($1); $$=args;}
|   Arguments "," Argument           {$1.push_back($3); $$=$1;}
;

Argument:
    Exp                         { $$ = $1; }
;

ListExp:
     "[" "]"                          {$$ = make_shared<EList>();}
|    "[" Arguments "]"                {$$ = make_shared<EList>($2);}
;

ListOpExp:
     "identifier" "." "get" "(" Exp ")"            {$$=make_shared<EListOp>(Get,$1,$5);}
|    "identifier" "." "remove" "(" Exp ")"        {$$=make_shared<EListOp>(Remove,$1,$5);}
|    "identifier" "." "insert" "(" Exp "," Exp ")"   {$$=make_shared<EListOp>(Insert,$1,$5,$7);}
|    "identifier" "." "length" "("")"              {$$=make_shared<EListOp>(Length,$1);}
;

FuncExp :
      "(" ")" "->" "{" Stms "}"                 {$$ = make_shared<EFunc>($5);}
|     "(" params ")" "->" "{" Stms "}"          {$$ = make_shared<EFunc>($2, $6);}
;

params :
     params "," "identifier"       {$1.push_back($3); $$=$1;}
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

VarExp:
    "identifier"                 {$$ = make_shared<EVar>($1);}
|   "*""identifier"              {$$ = make_shared<EVar>($2);$$->is_ref=true;}
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
|   "-" NumExp              { $2->is_negative=true; $$ = $2; }
|   "(" NumExp ")"                { $$ = $2; }
;



StringExp:
    "string"                      { $$ = make_shared<EString>($1); }
;

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const std::string &m) { driver.error(m); }
