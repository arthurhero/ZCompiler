%{ /* -*- C++ -*- */
  # include <cerrno>
  # include <climits>
  # include <cstdlib>
  # include <string>
  # include "lang.h"
  # include "parser_driver.h"
  # include "parser.yy.hpp"

  // Work around an incompatibility in flex (at least versions
  // 2.5.31 through 2.5.33): it generates code that does
  // not conform to C89.  See Debian bug 333231
  // <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
  # undef yywrap
  # define yywrap() 1
%}

%option noyywrap nounput batch debug noinput

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t]

%%

{blank}+    { }
[\n]+       { }

"void"      { return yy::parser::make_VOID(); }
"print"     { return yy::parser::make_PRINT(); }
"endl"     { return yy::parser::make_ENDL(); }
"return"    { return yy::parser::make_RETURN(); }

\"(\\.|[^"\\])*\"   { std::string tmp(yytext);
                       return yy::parser::make_STRING(tmp.substr(1,tmp.length()-2)); }

"{"         { return yy::parser::make_LCURL(); }
"}"         { return yy::parser::make_RCURL(); }

";"         { return yy::parser::make_SEMI(); }

"("         { return yy::parser::make_LPAREN(); }
")"         { return yy::parser::make_RPAREN(); }

"if"        { return yy::parser::make_IF(); }
"else"      { return yy::parser::make_ELSE(); }

"in"      { return yy::parser::make_IN(); }
"->"      { return yy::parser::make_RARROW(); }
"<-"      { return yy::parser::make_LARROW(); }
","       { return yy::parser::make_COMMA();  }

"<"     { return yy::parser::make_LESS(); }
">"     { return yy::parser::make_GREATER(); }
"<="     { return yy::parser::make_LEQ(); }
">="     { return yy::parser::make_GEQ(); }
"=="     { return yy::parser::make_EQUAL(); }
"!="     { return yy::parser::make_NEQ(); }
"&&"     { return yy::parser::make_AND(); }
"||"     { return yy::parser::make_OR(); }

"!"     { return yy::parser::make_EXCL(); }

"="     { return yy::parser::make_EQUAL(); }

"+"     {return yy::parser::make_PLUS(); }
"-"     {return yy::parser::make_MINUS(); }
"*"     {return yy::parser::make_STAR(); }
"/"     {return yy::parser::make_SLASH(); }

"true"|"false" {
    errno = 0;
    if (strcmp(yytext,"true")==0) {
      return yy::parser::make_BOOL(true);
    } else if (strcmp(yytext,"false")==0) {
      return yy::parser::make_BOOL(false);
    } else {
      driver.error ("unexpected boolean error");
    }
}

{int} {
    errno = 0;
    long n = strtol (yytext, NULL, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
      driver.error ("integer is out of range");
    }
    return yy::parser::make_INT(n);
}

"quit"        { return yy::parser::make_ENDLINE(); }

{id}       { return yy::parser::make_IDENTIFIER(yytext);}

<<EOF>>    { return yy::parser::make_END(); }

.          { driver.error ("invalid character"); }
%%

void parser_driver::scan_begin () {
    yy_flex_debug = trace_scanning;
    if (file.empty () || file == "-") {
      yyin = stdin;
    } else if (!(yyin = fopen (file.c_str (), "r"))) {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}

void parser_driver::scan_end () {
    fclose (yyin);
}
