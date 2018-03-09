// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser.yy.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.yy.hpp"

// User implementation prologue.

#line 51 "parser.yy.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 29 "parser.yy" // lalr1.cc:413

#include "parser_driver.h"
#include "lang.h"

using namespace std;

#line 60 "parser.yy.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 127 "parser.yy.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (parser_driver &driver_yyarg, shared_ptr<Stms> *ret_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg),
      ret (ret_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
      switch (that.type_get ())
    {
      case 49: // AppExp
        value.move<  shared_ptr<EApp>  > (that.value);
        break;

      case 53: // BoExp
        value.move<  shared_ptr<EBool>  > (that.value);
        break;

      case 47: // FuncExp
        value.move<  shared_ptr<EFunc>  > (that.value);
        break;

      case 54: // NumExp
        value.move<  shared_ptr<ENumb>  > (that.value);
        break;

      case 55: // StringExp
        value.move<  shared_ptr<EString>  > (that.value);
        break;

      case 52: // VarExp
        value.move<  shared_ptr<EVar>  > (that.value);
        break;

      case 46: // Exp
      case 51: // Argument
        value.move<  shared_ptr<Exp>  > (that.value);
        break;

      case 40: // AssignStm
        value.move<  shared_ptr<SAssign>  > (that.value);
        break;

      case 43: // FuncStm
        value.move<  shared_ptr<SFunc>  > (that.value);
        break;

      case 44: // IfStm
        value.move<  shared_ptr<SIf>  > (that.value);
        break;

      case 42: // PrintStm
        value.move<  shared_ptr<SPrint>  > (that.value);
        break;

      case 45: // RetStm
        value.move<  shared_ptr<SReturn>  > (that.value);
        break;

      case 39: // Stm
        value.move<  shared_ptr<Stm>  > (that.value);
        break;

      case 38: // Stms
        value.move<  shared_ptr<Stms>  > (that.value);
        break;

      case 41: // PrintContent
      case 50: // Arguments
        value.move<  std::vector<shared_ptr<Exp> >  > (that.value);
        break;

      case 48: // params
        value.move<  std::vector<std::string>  > (that.value);
        break;

      case 35: // "bool"
        value.move< bool > (that.value);
        break;

      case 34: // "int"
        value.move< int > (that.value);
        break;

      case 32: // "string"
      case 33: // "identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 49: // AppExp
        value.copy<  shared_ptr<EApp>  > (that.value);
        break;

      case 53: // BoExp
        value.copy<  shared_ptr<EBool>  > (that.value);
        break;

      case 47: // FuncExp
        value.copy<  shared_ptr<EFunc>  > (that.value);
        break;

      case 54: // NumExp
        value.copy<  shared_ptr<ENumb>  > (that.value);
        break;

      case 55: // StringExp
        value.copy<  shared_ptr<EString>  > (that.value);
        break;

      case 52: // VarExp
        value.copy<  shared_ptr<EVar>  > (that.value);
        break;

      case 46: // Exp
      case 51: // Argument
        value.copy<  shared_ptr<Exp>  > (that.value);
        break;

      case 40: // AssignStm
        value.copy<  shared_ptr<SAssign>  > (that.value);
        break;

      case 43: // FuncStm
        value.copy<  shared_ptr<SFunc>  > (that.value);
        break;

      case 44: // IfStm
        value.copy<  shared_ptr<SIf>  > (that.value);
        break;

      case 42: // PrintStm
        value.copy<  shared_ptr<SPrint>  > (that.value);
        break;

      case 45: // RetStm
        value.copy<  shared_ptr<SReturn>  > (that.value);
        break;

      case 39: // Stm
        value.copy<  shared_ptr<Stm>  > (that.value);
        break;

      case 38: // Stms
        value.copy<  shared_ptr<Stms>  > (that.value);
        break;

      case 41: // PrintContent
      case 50: // Arguments
        value.copy<  std::vector<shared_ptr<Exp> >  > (that.value);
        break;

      case 48: // params
        value.copy<  std::vector<std::string>  > (that.value);
        break;

      case 35: // "bool"
        value.copy< bool > (that.value);
        break;

      case 34: // "int"
        value.copy< int > (that.value);
        break;

      case 32: // "string"
      case 33: // "identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 49: // AppExp
        yylhs.value.build<  shared_ptr<EApp>  > ();
        break;

      case 53: // BoExp
        yylhs.value.build<  shared_ptr<EBool>  > ();
        break;

      case 47: // FuncExp
        yylhs.value.build<  shared_ptr<EFunc>  > ();
        break;

      case 54: // NumExp
        yylhs.value.build<  shared_ptr<ENumb>  > ();
        break;

      case 55: // StringExp
        yylhs.value.build<  shared_ptr<EString>  > ();
        break;

      case 52: // VarExp
        yylhs.value.build<  shared_ptr<EVar>  > ();
        break;

      case 46: // Exp
      case 51: // Argument
        yylhs.value.build<  shared_ptr<Exp>  > ();
        break;

      case 40: // AssignStm
        yylhs.value.build<  shared_ptr<SAssign>  > ();
        break;

      case 43: // FuncStm
        yylhs.value.build<  shared_ptr<SFunc>  > ();
        break;

      case 44: // IfStm
        yylhs.value.build<  shared_ptr<SIf>  > ();
        break;

      case 42: // PrintStm
        yylhs.value.build<  shared_ptr<SPrint>  > ();
        break;

      case 45: // RetStm
        yylhs.value.build<  shared_ptr<SReturn>  > ();
        break;

      case 39: // Stm
        yylhs.value.build<  shared_ptr<Stm>  > ();
        break;

      case 38: // Stms
        yylhs.value.build<  shared_ptr<Stms>  > ();
        break;

      case 41: // PrintContent
      case 50: // Arguments
        yylhs.value.build<  std::vector<shared_ptr<Exp> >  > ();
        break;

      case 48: // params
        yylhs.value.build<  std::vector<std::string>  > ();
        break;

      case 35: // "bool"
        yylhs.value.build< bool > ();
        break;

      case 34: // "int"
        yylhs.value.build< int > ();
        break;

      case 32: // "string"
      case 33: // "identifier"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 113 "parser.yy" // lalr1.cc:859
    { *ret = yystack_[1].value.as<  shared_ptr<Stms>  > (); }
#line 730 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 3:
#line 114 "parser.yy" // lalr1.cc:859
    { *ret = yystack_[1].value.as<  shared_ptr<Stms>  > ();
                             (*ret)->exec();
                             exit (0);
                           }
#line 739 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 4:
#line 121 "parser.yy" // lalr1.cc:859
    {std::vector< shared_ptr<Stm> > stms = std::vector< shared_ptr<Stm> >();
                         yylhs.value.as<  shared_ptr<Stms>  > ()=make_shared<Stms>(stms);}
#line 746 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 5:
#line 123 "parser.yy" // lalr1.cc:859
    {yystack_[0].value.as<  shared_ptr<Stms>  > ()->stms.insert(yystack_[0].value.as<  shared_ptr<Stms>  > ()->stms.begin(),yystack_[1].value.as<  shared_ptr<Stm>  > ()); yylhs.value.as<  shared_ptr<Stms>  > ()=yystack_[0].value.as<  shared_ptr<Stms>  > ();}
#line 752 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 6:
#line 127 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<Stm>  > ()=yystack_[0].value.as<  shared_ptr<SIf>  > ();}
#line 758 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 7:
#line 128 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<Stm>  > ()=yystack_[0].value.as<  shared_ptr<SAssign>  > ();}
#line 764 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 8:
#line 129 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<Stm>  > ()=yystack_[0].value.as<  shared_ptr<SPrint>  > ();}
#line 770 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 9:
#line 130 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<Stm>  > ()=yystack_[0].value.as<  shared_ptr<SFunc>  > ();}
#line 776 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 10:
#line 131 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<Stm>  > ()=yystack_[0].value.as<  shared_ptr<SReturn>  > ();}
#line 782 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 11:
#line 135 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<SAssign>  > ()=make_shared<SAssign>(yystack_[3].value.as< std::string > (),yystack_[1].value.as<  shared_ptr<Exp>  > ());}
#line 788 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 12:
#line 139 "parser.yy" // lalr1.cc:859
    {std::vector<shared_ptr<Exp> > PC = std::vector<shared_ptr<Exp> >();
                                  PC.push_back(yystack_[0].value.as<  shared_ptr<EString>  > ());
                                  yylhs.value.as<  std::vector<shared_ptr<Exp> >  > ()=PC;}
#line 796 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 13:
#line 142 "parser.yy" // lalr1.cc:859
    {yystack_[2].value.as<  std::vector<shared_ptr<Exp> >  > ().push_back(yystack_[0].value.as<  shared_ptr<Exp>  > ()); yylhs.value.as<  std::vector<shared_ptr<Exp> >  > ()=yystack_[2].value.as<  std::vector<shared_ptr<Exp> >  > ();}
#line 802 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 14:
#line 143 "parser.yy" // lalr1.cc:859
    {yystack_[0].value.as<  std::vector<shared_ptr<Exp> >  > ().insert(yystack_[0].value.as<  std::vector<shared_ptr<Exp> >  > ().begin(),yystack_[2].value.as<  shared_ptr<Exp>  > ()); yylhs.value.as<  std::vector<shared_ptr<Exp> >  > ()=yystack_[0].value.as<  std::vector<shared_ptr<Exp> >  > ();}
#line 808 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 15:
#line 147 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<SPrint>  > ()=make_shared<SPrint>(yystack_[2].value.as<  std::vector<shared_ptr<Exp> >  > ());}
#line 814 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 16:
#line 148 "parser.yy" // lalr1.cc:859
    {std::vector<shared_ptr<Exp> > PC = std::vector<shared_ptr<Exp> >();
                                        PC.push_back(yystack_[2].value.as<  shared_ptr<Exp>  > ());
                                       yylhs.value.as<  shared_ptr<SPrint>  > ()=make_shared<SPrint>(PC);}
#line 822 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 17:
#line 154 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<SFunc>  > ()=make_shared<SFunc>(yystack_[1].value.as<  shared_ptr<EApp>  > ());}
#line 828 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 18:
#line 158 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<SIf>  > () = make_shared<SIf>(yystack_[4].value.as<  shared_ptr<EBool>  > (),yystack_[1].value.as<  shared_ptr<Stms>  > ()); }
#line 834 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 19:
#line 159 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<SIf>  > () = make_shared<SIf>(yystack_[8].value.as<  shared_ptr<EBool>  > (),yystack_[5].value.as<  shared_ptr<Stms>  > (),yystack_[1].value.as<  shared_ptr<Stms>  > ()); }
#line 840 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 20:
#line 160 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<SIf>  > () = make_shared<SIf>(yystack_[6].value.as<  shared_ptr<EBool>  > (),yystack_[3].value.as<  shared_ptr<Stms>  > (),yystack_[0].value.as<  shared_ptr<SIf>  > ()); }
#line 846 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 21:
#line 164 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<SReturn>  > ()=make_shared<SReturn>(yystack_[1].value.as<  shared_ptr<Exp>  > ());}
#line 852 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 22:
#line 171 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EVoid>(); }
#line 858 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 23:
#line 173 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = yystack_[0].value.as<  shared_ptr<ENumb>  > (); }
#line 864 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 24:
#line 174 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = yystack_[0].value.as<  shared_ptr<EBool>  > (); }
#line 870 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 25:
#line 175 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = yystack_[0].value.as<  shared_ptr<EVar>  > (); }
#line 876 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 26:
#line 176 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = yystack_[0].value.as<  shared_ptr<EApp>  > (); }
#line 882 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 27:
#line 177 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = yystack_[0].value.as<  shared_ptr<EFunc>  > (); }
#line 888 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 28:
#line 178 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = yystack_[0].value.as<  shared_ptr<EString>  > (); }
#line 894 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 29:
#line 179 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = yystack_[1].value.as<  shared_ptr<Exp>  > (); }
#line 900 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 30:
#line 183 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<EFunc>  > () = make_shared<EFunc>(yystack_[1].value.as<  shared_ptr<Stms>  > ());}
#line 906 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 31:
#line 184 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<EFunc>  > () = make_shared<EFunc>(yystack_[5].value.as<  std::vector<std::string>  > (), yystack_[1].value.as<  shared_ptr<Stms>  > ());}
#line 912 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 32:
#line 188 "parser.yy" // lalr1.cc:859
    {yystack_[0].value.as<  std::vector<std::string>  > ().push_back(yystack_[2].value.as< std::string > ()); yylhs.value.as<  std::vector<std::string>  > ()=yystack_[0].value.as<  std::vector<std::string>  > ();}
#line 918 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 33:
#line 189 "parser.yy" // lalr1.cc:859
    {std::vector<std::string> tmp;
                                      tmp.push_back(yystack_[0].value.as< std::string > ());
                                      yylhs.value.as<  std::vector<std::string>  > ()=tmp;}
#line 926 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 34:
#line 195 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<EApp>  > () = make_shared<EApp>(yystack_[2].value.as<  shared_ptr<EVar>  > ());}
#line 932 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 35:
#line 196 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<EApp>  > () = make_shared<EApp>(yystack_[2].value.as<  shared_ptr<EFunc>  > ());}
#line 938 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 36:
#line 197 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<EApp>  > () = make_shared<EApp>(yystack_[1].value.as<  std::vector<shared_ptr<Exp> >  > (),yystack_[3].value.as<  shared_ptr<EVar>  > ());}
#line 944 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 37:
#line 198 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<EApp>  > () = make_shared<EApp>(yystack_[1].value.as<  std::vector<shared_ptr<Exp> >  > (),yystack_[3].value.as<  shared_ptr<EFunc>  > ());}
#line 950 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 38:
#line 202 "parser.yy" // lalr1.cc:859
    {std::vector<shared_ptr<Exp> > args; args.push_back(yystack_[0].value.as<  shared_ptr<Exp>  > ()); yylhs.value.as<  std::vector<shared_ptr<Exp> >  > ()=args;}
#line 956 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 39:
#line 203 "parser.yy" // lalr1.cc:859
    {yystack_[0].value.as<  std::vector<shared_ptr<Exp> >  > ().push_back(yystack_[2].value.as<  shared_ptr<Exp>  > ()); yylhs.value.as<  std::vector<shared_ptr<Exp> >  > ()=yystack_[0].value.as<  std::vector<shared_ptr<Exp> >  > ();}
#line 962 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 40:
#line 207 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = yystack_[0].value.as<  shared_ptr<Exp>  > (); }
#line 968 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 41:
#line 211 "parser.yy" // lalr1.cc:859
    {yylhs.value.as<  shared_ptr<EVar>  > () = make_shared<EVar>(yystack_[0].value.as< std::string > ());}
#line 974 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 42:
#line 214 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[0].value.as< bool > ()); }
#line 980 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 43:
#line 215 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 986 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 44:
#line 216 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[2].value.as<  shared_ptr<Exp>  > (),Less,yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 992 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 45:
#line 217 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[2].value.as<  shared_ptr<Exp>  > (),Greater,yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 998 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 46:
#line 218 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[2].value.as<  shared_ptr<Exp>  > (),Leq,yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1004 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 47:
#line 219 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[2].value.as<  shared_ptr<Exp>  > (),Geq,yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1010 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 48:
#line 220 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[2].value.as<  shared_ptr<Exp>  > (),Equal,yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1016 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 49:
#line 221 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[2].value.as<  shared_ptr<Exp>  > (),Neq,yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1022 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 50:
#line 222 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[2].value.as<  shared_ptr<Exp>  > (),And,yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1028 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 51:
#line 223 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = make_shared<EBool>(yystack_[2].value.as<  shared_ptr<Exp>  > (),Or,yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1034 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 52:
#line 224 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EBool>  > () = yystack_[1].value.as<  shared_ptr<EBool>  > (); }
#line 1040 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 53:
#line 227 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<ENumb>  > () = make_shared<ENumb>(yystack_[0].value.as< int > ()); }
#line 1046 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 54:
#line 228 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<ENumb>  > () = make_shared<ENumb>(yystack_[2].value.as<  shared_ptr<Exp>  > (),'+',yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1052 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 55:
#line 229 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<ENumb>  > () = make_shared<ENumb>(yystack_[2].value.as<  shared_ptr<Exp>  > (),'-',yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1058 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 56:
#line 230 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<ENumb>  > () = make_shared<ENumb>(yystack_[2].value.as<  shared_ptr<Exp>  > (),'*',yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1064 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 57:
#line 231 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<ENumb>  > () = make_shared<ENumb>(yystack_[2].value.as<  shared_ptr<Exp>  > (),'/',yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 1070 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 58:
#line 232 "parser.yy" // lalr1.cc:859
    { yystack_[0].value.as<  shared_ptr<ENumb>  > ()->is_negative=true; yylhs.value.as<  shared_ptr<ENumb>  > () = yystack_[0].value.as<  shared_ptr<ENumb>  > (); }
#line 1076 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 59:
#line 233 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<ENumb>  > () = yystack_[1].value.as<  shared_ptr<ENumb>  > (); }
#line 1082 "parser.yy.cpp" // lalr1.cc:859
    break;

  case 60:
#line 239 "parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<EString>  > () = make_shared<EString>(yystack_[0].value.as< std::string > ()); }
#line 1088 "parser.yy.cpp" // lalr1.cc:859
    break;


#line 1092 "parser.yy.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -38;

  const signed char parser::yytable_ninf_ = -59;

  const short int
  parser::yypact_[] =
  {
      20,    31,   125,     1,    43,    40,    15,     6,    20,   -38,
     -38,   -38,   -38,   -38,    64,    61,    66,   125,   -38,    13,
     125,   125,   -38,   -38,   -38,   -38,   181,    64,   -38,    66,
     -38,   -38,   -38,    68,    60,    74,   125,   125,   -38,   -38,
     -38,   -38,    73,   -38,   118,    21,   144,    23,    28,   164,
      75,    76,    51,   210,    11,   -38,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,    71,    54,
      77,    80,   198,   -38,   210,    81,    78,   -38,    83,    84,
     125,    86,   125,   -38,   -38,   -38,    22,    22,   -38,   -38,
      51,    51,    51,    51,    51,    51,   244,   222,    20,   -38,
      89,    94,   -38,   -38,   125,   -38,   -38,   232,   -38,   -38,
      22,    95,    20,    20,   -38,   -38,    96,   103,   -38,    88,
       7,    20,   -38,   112,   -38
  };

  const unsigned char
  parser::yydefact_[] =
  {
       4,     0,     0,     0,     0,    41,     0,     0,     4,     7,
       8,     9,     6,    10,     0,     0,     0,     0,    22,     0,
       0,     0,    60,    41,    53,    42,     0,    27,    26,    25,
      24,    23,    28,     0,    33,     0,     0,     0,     1,     2,
       3,     5,     0,    17,     0,     0,     0,    28,    41,     0,
      24,    23,    43,     0,    23,    21,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    24,     0,    35,    40,     0,    38,    34,     0,     0,
       0,     0,     0,    29,    52,    59,    54,    55,    56,    57,
      44,    45,    46,    47,    49,    48,    50,    51,     4,    32,
       0,     0,    11,    37,     0,    36,    15,    13,    16,    14,
      54,     0,     4,     4,    39,    30,     0,     0,    31,    18,
       0,     4,    20,     0,    19
  };

  const signed char
  parser::yypgoto_[] =
  {
     -38,   -38,    -3,   -38,   -38,    42,   -38,   -38,    10,   -38,
      -1,     0,    57,     2,   -37,   -38,     4,    -6,    30,   -14
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     6,     7,     8,     9,    45,    10,    11,    12,    13,
      74,    27,    35,    28,    75,    76,    29,    30,    31,    32
  };

  const signed char
  parser::yytable_[] =
  {
      14,    26,    15,    47,    16,    41,    39,    78,    14,    40,
      15,    33,    16,    50,   121,    38,    46,    18,    49,    52,
      53,   -58,    19,    33,   -58,     1,     2,   -58,    20,     3,
      71,    79,    21,   -12,    34,    53,    72,     4,   -33,    80,
      17,   -12,    58,    59,    69,    22,    48,    24,    25,    51,
       4,    54,    36,     5,    37,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,   114,    47,    56,
      57,    58,    59,    42,    43,    44,    69,    18,    98,   107,
      68,   110,    19,    73,    70,    84,    85,    34,    20,   100,
     101,   103,    21,   105,   104,   111,   112,   106,    14,   108,
      15,   113,    16,   115,   118,    22,    23,    24,    25,   116,
     117,   119,    14,    14,    15,    15,    16,    16,   123,   120,
     124,    14,    18,    15,   109,    16,    99,    19,    77,    18,
     122,     0,     0,    20,    19,     0,     0,    21,     0,     0,
      20,     0,     0,     0,    21,     0,     0,     0,     0,     0,
      22,    23,    24,    25,    81,     0,     0,    22,    23,    24,
      25,     0,    82,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    83,     0,     0,     0,     0,     0,
       0,     0,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    55,     0,     0,     0,     0,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,   102,     0,     0,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65
  };

  const signed char
  parser::yycheck_[] =
  {
       0,     2,     0,    17,     0,     8,     0,    44,     8,     3,
       8,    10,     8,    19,     7,     0,    17,     4,    19,    20,
      21,    10,     9,    10,    13,     5,     6,    16,    15,     9,
      36,    10,    19,    10,    33,    36,    37,    30,    10,    18,
       9,    18,    20,    21,    16,    32,    33,    34,    35,    19,
      30,    21,     9,    33,    14,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,   104,    82,    18,
      19,    20,    21,     9,    13,     9,    16,     4,     7,    80,
      12,    82,     9,    10,    10,    10,    10,    33,    15,    12,
      10,    10,    19,    10,    16,    98,     7,    13,    98,    13,
      98,     7,    98,     8,     8,    32,    33,    34,    35,   112,
     113,     8,   112,   113,   112,   113,   112,   113,   121,    31,
       8,   121,     4,   121,    82,   121,    69,     9,    10,     4,
     120,    -1,    -1,    15,     9,    -1,    -1,    19,    -1,    -1,
      15,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    10,    -1,    -1,    32,    33,    34,
      35,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    13,    -1,    -1,    -1,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    13,    -1,    -1,    -1,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     5,     6,     9,    30,    33,    37,    38,    39,    40,
      42,    43,    44,    45,    47,    49,    52,     9,     4,     9,
      15,    19,    32,    33,    34,    35,    46,    47,    49,    52,
      53,    54,    55,    10,    33,    48,     9,    14,     0,     0,
       3,    38,     9,    13,     9,    41,    46,    55,    33,    46,
      53,    54,    46,    46,    54,    13,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    12,    16,
      10,    53,    46,    10,    46,    50,    51,    10,    50,    10,
      18,    10,    18,    10,    10,    10,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,     7,    48,
      12,    10,    13,    10,    16,    10,    13,    46,    13,    41,
      46,    38,     7,     7,    50,     8,    38,    38,     8,     8,
      31,     7,    44,    38,     8
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    36,    37,    37,    38,    38,    39,    39,    39,    39,
      39,    40,    41,    41,    41,    42,    42,    43,    44,    44,
      44,    45,    46,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    48,    48,    49,    49,    49,    49,    50,    50,
      51,    52,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    54,    54,    54,    54,    54,    54,    54,
      55
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     2,     0,     2,     1,     1,     1,     1,
       1,     4,     1,     3,     3,     5,     5,     2,     7,    11,
       9,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       6,     7,     3,     1,     3,     3,     4,     4,     1,     3,
       1,     1,     1,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     2,     3,
       1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"eol\"", "\"void\"", "\"print\"",
  "\"return\"", "\"{\"", "\"}\"", "\"(\"", "\")\"", "\"<-\"", "\"->\"",
  "\";\"", "\"=\"", "\"!\"", "\",\"", "\"in\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"!=\"", "\"==\"",
  "\"&&\"", "\"||\"", "IF", "ELSE", "\"string\"", "\"identifier\"",
  "\"int\"", "\"bool\"", "$accept", "prog", "Stms", "Stm", "AssignStm",
  "PrintContent", "PrintStm", "FuncStm", "IfStm", "RetStm", "Exp",
  "FuncExp", "params", "AppExp", "Arguments", "Argument", "VarExp",
  "BoExp", "NumExp", "StringExp", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   113,   113,   114,   121,   123,   127,   128,   129,   130,
     131,   135,   139,   142,   143,   147,   148,   154,   158,   159,
     160,   164,   171,   173,   174,   175,   176,   177,   178,   179,
     183,   184,   188,   189,   195,   196,   197,   198,   202,   203,
     207,   211,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   227,   228,   229,   230,   231,   232,   233,
     239
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1567 "parser.yy.cpp" // lalr1.cc:1167
#line 242 "parser.yy" // lalr1.cc:1168


// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const std::string &m) { driver.error(m); }
