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

  IF
  THEN
  ELSE
;

%token <std::string> IDENTIFIER "identifier"
%token <int> INT "int"
%token <bool> BOOL "bool"
%token <LogOps> LOP "log_op"

%type  < shared_ptr<Exp> > Exp
%type  < shared_ptr<ELet> > LetExp
%type  < shared_ptr<EApp> > AppExp
%type  < shared_ptr<EVar> > VarExp
%type  < shared_ptr<EFunc> > FuncExp
%type  < shared_ptr<ENumb> > NumExp
%type  < shared_ptr<EBool> > BoExp
%type  < shared_ptr<EIf> >  IfExp
%type  < std::vector<std::string> >  params
%type  < std::map<std::string, shared_ptr<Exp> > >  Assignments
%type  < std::pair<std::string, shared_ptr<Exp> > >  Assignment
%type  < std::vector<shared_ptr<Exp> > >  Arguments
%type  < shared_ptr<Exp> >  Argument
%parse-param {shared_ptr<Exp> *ret}

%%
%left "+" "-";
%left "*" "/";

%start prog;

prog:
    Exp "eof"             { *ret = $1; }
|   Exp "eol"             { *ret = $1;
                                      Ans answer = (*ret)->eval();
                                      if (answer.t == Int) {
                                        std::cout << answer.i << std::endl;
                                      } else if (answer.t == Bool) {
                                        std::cout << answer.b << std::endl;
                                      } else if (answer.t == Unknown) {
                                        std::cerr << "Error: Unknown Type" << std::endl;
                                      }
                                      exit (0);
                                    }
;

Exp:
     LetExp             { $$ = $1; }
|    NumExp             { $$ = $1; }
|    BoExp              { $$ = $1; }
|    VarExp             { $$ = $1; }
|    IfExp              { $$ = $1; }
|    FuncExp            { $$ = $1; }
|    "(" Exp ")"        { $$ = $2; }
;

LetExp:
    "{" Assignments "in" Exp "}"    { $$ =  make_shared<ELet>($2,$4);}
;

Assignments:
    %empty                          {std::map<std::string, shared_ptr<Exp> > context = std::map<std::string, shared_ptr<Exp> >();
                                      $$=context;}
|   Assignment Assignments          {$2.insert($1); $$=$2;}
;

Assignment:
    "identifier" "=" Exp ";"     { $$ = std::make_pair($1, $3); }
;

FuncExp :
      "(" ")" "->" "{" Exp "}"                 {$$ = make_shared<EFunc>($5);}
|     "(" params ")" "->" "{" Exp "}"          {$$ = make_shared<EFunc>($2, $6);}
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

NumExp  :   "int"                 { $$ = make_shared<ENumb>($1); }
|   VarExp                        { $$ = make_shared<ENumb>($1);}
|   AppExp                       {$$ = make_shared<ENumb>($1);}
|   LetExp                        { $$ = make_shared<ENumb>($1); }
|   NumExp "+" NumExp             { $$ = make_shared<ENumb>($1,'+',$3); }
|   NumExp "-" NumExp             { $$ = make_shared<ENumb>($1,'-',$3); }
|   NumExp "*" NumExp             { $$ = make_shared<ENumb>($1,'*',$3); }
|   NumExp "/" NumExp             { $$ = make_shared<ENumb>($1,'/',$3); }
|   "(" NumExp ")"                { $$ = $2; }
;

BoExp   :   "bool"                 { $$ = make_shared<EBool>($1); }
|   VarExp                       { $$ = make_shared<EBool>($1); }
|   AppExp                       { $$ = make_shared<EBool>($1); }
|   LetExp                        { $$ = make_shared<EBool>($1); }
|   "!" BoExp                      { $$ = make_shared<EBool>($2); }
|   NumExp LOP NumExp              { $$ = make_shared<EBool>($1,$2,$3); }
|   "(" BoExp ")"                  { $$ = $2; }
;

IfExp   :
    IF BoExp THEN Exp ELSE Exp     { $$ = make_shared<EIf>($2,$4,$6); }
|   "(" IfExp ")"             { $$ = $2; }
;

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const std::string &m) { driver.error(m); }
