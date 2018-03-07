#pragma once

#include <string>
#include <map>
#include <memory>
#include "lang.h"
#include "parser.yy.hpp"

#define YY_DECL yy::parser::symbol_type yylex (parser_driver &driver)

YY_DECL;

class parser_driver {
public:
    parser_driver(const std::string &f, bool lex, bool parse);
    virtual ~parser_driver();

    std::string file;
    int result;

    bool trace_scanning;
    bool trace_parsing;

    shared_ptr<Stms> parse();

    void error(const std::string &m);

    // NOTE: Implemented in scanner.l
    void scan_begin();
    void scan_end();
};
