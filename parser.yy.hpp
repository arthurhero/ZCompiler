// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file parser.yy.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_PARSER_YY_HPP_INCLUDED
# define YY_YY_PARSER_YY_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 9 "parser.yy" // lalr1.cc:392

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


#line 58 "parser.yy.hpp" // lalr1.cc:392

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"

#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace yy {
#line 135 "parser.yy.hpp" // lalr1.cc:392



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // AppExp
      char dummy1[sizeof( shared_ptr<EApp> )];

      // BoExp
      char dummy2[sizeof( shared_ptr<EBool> )];

      // FuncExp
      char dummy3[sizeof( shared_ptr<EFunc> )];

      // NumExp
      char dummy4[sizeof( shared_ptr<ENumb> )];

      // StringExp
      char dummy5[sizeof( shared_ptr<EString> )];

      // VarExp
      char dummy6[sizeof( shared_ptr<EVar> )];

      // Exp
      // Argument
      char dummy7[sizeof( shared_ptr<Exp> )];

      // AssignStm
      char dummy8[sizeof( shared_ptr<SAssign> )];

      // FuncStm
      char dummy9[sizeof( shared_ptr<SFunc> )];

      // IfStm
      char dummy10[sizeof( shared_ptr<SIf> )];

      // PrintStm
      char dummy11[sizeof( shared_ptr<SPrint> )];

      // RetStm
      char dummy12[sizeof( shared_ptr<SReturn> )];

      // Stm
      char dummy13[sizeof( shared_ptr<Stm> )];

      // Stms
      char dummy14[sizeof( shared_ptr<Stms> )];

      // PrintContent
      // Arguments
      char dummy15[sizeof( std::vector<shared_ptr<Exp> > )];

      // params
      char dummy16[sizeof( std::vector<std::string> )];

      // "log_op"
      char dummy17[sizeof(LogOps)];

      // "bool"
      char dummy18[sizeof(bool)];

      // "int"
      char dummy19[sizeof(int)];

      // "string"
      // "identifier"
      char dummy20[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m);
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOK_END = 0,
        TOK_ENDLINE = 258,
        TOK_VOID = 259,
        TOK_PRINT = 260,
        TOK_ENDL = 261,
        TOK_RETURN = 262,
        TOK_LCURL = 263,
        TOK_RCURL = 264,
        TOK_LPAREN = 265,
        TOK_RPAREN = 266,
        TOK_LARROW = 267,
        TOK_RARROW = 268,
        TOK_SEMI = 269,
        TOK_EQUAL = 270,
        TOK_EXCL = 271,
        TOK_COMMA = 272,
        TOK_IN = 273,
        TOK_PLUS = 274,
        TOK_MINUS = 275,
        TOK_STAR = 276,
        TOK_SLASH = 277,
        TOK_IF = 278,
        TOK_ELSE = 279,
        TOK_STRING = 280,
        TOK_IDENTIFIER = 281,
        TOK_INT = 282,
        TOK_BOOL = 283,
        TOK_LOP = 284
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<EApp>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<EBool>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<EFunc>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<ENumb>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<EString>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<EVar>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<Exp>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<SAssign>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<SFunc>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<SIf>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<SPrint>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<SReturn>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<Stm>  v);

  basic_symbol (typename Base::kind_type t, const  shared_ptr<Stms>  v);

  basic_symbol (typename Base::kind_type t, const  std::vector<shared_ptr<Exp> >  v);

  basic_symbol (typename Base::kind_type t, const  std::vector<std::string>  v);

  basic_symbol (typename Base::kind_type t, const LogOps v);

  basic_symbol (typename Base::kind_type t, const bool v);

  basic_symbol (typename Base::kind_type t, const int v);

  basic_symbol (typename Base::kind_type t, const std::string v);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END ();

    static inline
    symbol_type
    make_ENDLINE ();

    static inline
    symbol_type
    make_VOID ();

    static inline
    symbol_type
    make_PRINT ();

    static inline
    symbol_type
    make_ENDL ();

    static inline
    symbol_type
    make_RETURN ();

    static inline
    symbol_type
    make_LCURL ();

    static inline
    symbol_type
    make_RCURL ();

    static inline
    symbol_type
    make_LPAREN ();

    static inline
    symbol_type
    make_RPAREN ();

    static inline
    symbol_type
    make_LARROW ();

    static inline
    symbol_type
    make_RARROW ();

    static inline
    symbol_type
    make_SEMI ();

    static inline
    symbol_type
    make_EQUAL ();

    static inline
    symbol_type
    make_EXCL ();

    static inline
    symbol_type
    make_COMMA ();

    static inline
    symbol_type
    make_IN ();

    static inline
    symbol_type
    make_PLUS ();

    static inline
    symbol_type
    make_MINUS ();

    static inline
    symbol_type
    make_STAR ();

    static inline
    symbol_type
    make_SLASH ();

    static inline
    symbol_type
    make_IF ();

    static inline
    symbol_type
    make_ELSE ();

    static inline
    symbol_type
    make_STRING (const std::string& v);

    static inline
    symbol_type
    make_IDENTIFIER (const std::string& v);

    static inline
    symbol_type
    make_INT (const int& v);

    static inline
    symbol_type
    make_BOOL (const bool& v);

    static inline
    symbol_type
    make_LOP (const LogOps& v);


    /// Build a parser object.
    parser (parser_driver &driver_yyarg, shared_ptr<Stms> *ret_yyarg);
    virtual ~parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const signed char yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const signed char yytable_[];

  static const unsigned char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 149,     ///< Last index in yytable_.
      yynnts_ = 20,  ///< Number of nonterminal symbols.
      yyfinal_ = 38, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 30  ///< Number of tokens.
    };


    // User arguments.
    parser_driver &driver;
    shared_ptr<Stms> *ret;
  };

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29
    };
    const unsigned int user_token_number_max_ = 284;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
      switch (other.type_get ())
    {
      case 43: // AppExp
        value.copy<  shared_ptr<EApp>  > (other.value);
        break;

      case 47: // BoExp
        value.copy<  shared_ptr<EBool>  > (other.value);
        break;

      case 41: // FuncExp
        value.copy<  shared_ptr<EFunc>  > (other.value);
        break;

      case 48: // NumExp
        value.copy<  shared_ptr<ENumb>  > (other.value);
        break;

      case 49: // StringExp
        value.copy<  shared_ptr<EString>  > (other.value);
        break;

      case 46: // VarExp
        value.copy<  shared_ptr<EVar>  > (other.value);
        break;

      case 40: // Exp
      case 45: // Argument
        value.copy<  shared_ptr<Exp>  > (other.value);
        break;

      case 34: // AssignStm
        value.copy<  shared_ptr<SAssign>  > (other.value);
        break;

      case 37: // FuncStm
        value.copy<  shared_ptr<SFunc>  > (other.value);
        break;

      case 38: // IfStm
        value.copy<  shared_ptr<SIf>  > (other.value);
        break;

      case 36: // PrintStm
        value.copy<  shared_ptr<SPrint>  > (other.value);
        break;

      case 39: // RetStm
        value.copy<  shared_ptr<SReturn>  > (other.value);
        break;

      case 33: // Stm
        value.copy<  shared_ptr<Stm>  > (other.value);
        break;

      case 32: // Stms
        value.copy<  shared_ptr<Stms>  > (other.value);
        break;

      case 35: // PrintContent
      case 44: // Arguments
        value.copy<  std::vector<shared_ptr<Exp> >  > (other.value);
        break;

      case 42: // params
        value.copy<  std::vector<std::string>  > (other.value);
        break;

      case 29: // "log_op"
        value.copy< LogOps > (other.value);
        break;

      case 28: // "bool"
        value.copy< bool > (other.value);
        break;

      case 27: // "int"
        value.copy< int > (other.value);
        break;

      case 25: // "string"
      case 26: // "identifier"
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value ()
  {
    (void) v;
      switch (this->type_get ())
    {
      case 43: // AppExp
        value.copy<  shared_ptr<EApp>  > (v);
        break;

      case 47: // BoExp
        value.copy<  shared_ptr<EBool>  > (v);
        break;

      case 41: // FuncExp
        value.copy<  shared_ptr<EFunc>  > (v);
        break;

      case 48: // NumExp
        value.copy<  shared_ptr<ENumb>  > (v);
        break;

      case 49: // StringExp
        value.copy<  shared_ptr<EString>  > (v);
        break;

      case 46: // VarExp
        value.copy<  shared_ptr<EVar>  > (v);
        break;

      case 40: // Exp
      case 45: // Argument
        value.copy<  shared_ptr<Exp>  > (v);
        break;

      case 34: // AssignStm
        value.copy<  shared_ptr<SAssign>  > (v);
        break;

      case 37: // FuncStm
        value.copy<  shared_ptr<SFunc>  > (v);
        break;

      case 38: // IfStm
        value.copy<  shared_ptr<SIf>  > (v);
        break;

      case 36: // PrintStm
        value.copy<  shared_ptr<SPrint>  > (v);
        break;

      case 39: // RetStm
        value.copy<  shared_ptr<SReturn>  > (v);
        break;

      case 33: // Stm
        value.copy<  shared_ptr<Stm>  > (v);
        break;

      case 32: // Stms
        value.copy<  shared_ptr<Stms>  > (v);
        break;

      case 35: // PrintContent
      case 44: // Arguments
        value.copy<  std::vector<shared_ptr<Exp> >  > (v);
        break;

      case 42: // params
        value.copy<  std::vector<std::string>  > (v);
        break;

      case 29: // "log_op"
        value.copy< LogOps > (v);
        break;

      case 28: // "bool"
        value.copy< bool > (v);
        break;

      case 27: // "int"
        value.copy< int > (v);
        break;

      case 25: // "string"
      case 26: // "identifier"
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<EApp>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<EBool>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<EFunc>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<ENumb>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<EString>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<EVar>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<Exp>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<SAssign>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<SFunc>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<SIf>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<SPrint>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<SReturn>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<Stm>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  shared_ptr<Stms>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  std::vector<shared_ptr<Exp> >  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const  std::vector<std::string>  v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const LogOps v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const bool v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v)
    : Base (t)
    , value (v)
  {}


  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 43: // AppExp
        value.template destroy<  shared_ptr<EApp>  > ();
        break;

      case 47: // BoExp
        value.template destroy<  shared_ptr<EBool>  > ();
        break;

      case 41: // FuncExp
        value.template destroy<  shared_ptr<EFunc>  > ();
        break;

      case 48: // NumExp
        value.template destroy<  shared_ptr<ENumb>  > ();
        break;

      case 49: // StringExp
        value.template destroy<  shared_ptr<EString>  > ();
        break;

      case 46: // VarExp
        value.template destroy<  shared_ptr<EVar>  > ();
        break;

      case 40: // Exp
      case 45: // Argument
        value.template destroy<  shared_ptr<Exp>  > ();
        break;

      case 34: // AssignStm
        value.template destroy<  shared_ptr<SAssign>  > ();
        break;

      case 37: // FuncStm
        value.template destroy<  shared_ptr<SFunc>  > ();
        break;

      case 38: // IfStm
        value.template destroy<  shared_ptr<SIf>  > ();
        break;

      case 36: // PrintStm
        value.template destroy<  shared_ptr<SPrint>  > ();
        break;

      case 39: // RetStm
        value.template destroy<  shared_ptr<SReturn>  > ();
        break;

      case 33: // Stm
        value.template destroy<  shared_ptr<Stm>  > ();
        break;

      case 32: // Stms
        value.template destroy<  shared_ptr<Stms>  > ();
        break;

      case 35: // PrintContent
      case 44: // Arguments
        value.template destroy<  std::vector<shared_ptr<Exp> >  > ();
        break;

      case 42: // params
        value.template destroy<  std::vector<std::string>  > ();
        break;

      case 29: // "log_op"
        value.template destroy< LogOps > ();
        break;

      case 28: // "bool"
        value.template destroy< bool > ();
        break;

      case 27: // "int"
        value.template destroy< int > ();
        break;

      case 25: // "string"
      case 26: // "identifier"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 43: // AppExp
        value.move<  shared_ptr<EApp>  > (s.value);
        break;

      case 47: // BoExp
        value.move<  shared_ptr<EBool>  > (s.value);
        break;

      case 41: // FuncExp
        value.move<  shared_ptr<EFunc>  > (s.value);
        break;

      case 48: // NumExp
        value.move<  shared_ptr<ENumb>  > (s.value);
        break;

      case 49: // StringExp
        value.move<  shared_ptr<EString>  > (s.value);
        break;

      case 46: // VarExp
        value.move<  shared_ptr<EVar>  > (s.value);
        break;

      case 40: // Exp
      case 45: // Argument
        value.move<  shared_ptr<Exp>  > (s.value);
        break;

      case 34: // AssignStm
        value.move<  shared_ptr<SAssign>  > (s.value);
        break;

      case 37: // FuncStm
        value.move<  shared_ptr<SFunc>  > (s.value);
        break;

      case 38: // IfStm
        value.move<  shared_ptr<SIf>  > (s.value);
        break;

      case 36: // PrintStm
        value.move<  shared_ptr<SPrint>  > (s.value);
        break;

      case 39: // RetStm
        value.move<  shared_ptr<SReturn>  > (s.value);
        break;

      case 33: // Stm
        value.move<  shared_ptr<Stm>  > (s.value);
        break;

      case 32: // Stms
        value.move<  shared_ptr<Stms>  > (s.value);
        break;

      case 35: // PrintContent
      case 44: // Arguments
        value.move<  std::vector<shared_ptr<Exp> >  > (s.value);
        break;

      case 42: // params
        value.move<  std::vector<std::string>  > (s.value);
        break;

      case 29: // "log_op"
        value.move< LogOps > (s.value);
        break;

      case 28: // "bool"
        value.move< bool > (s.value);
        break;

      case 27: // "int"
        value.move< int > (s.value);
        break;

      case 25: // "string"
      case 26: // "identifier"
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }

  inline
  parser::token_type
  parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  parser::symbol_type
  parser::make_END ()
  {
    return symbol_type (token::TOK_END);
  }

  parser::symbol_type
  parser::make_ENDLINE ()
  {
    return symbol_type (token::TOK_ENDLINE);
  }

  parser::symbol_type
  parser::make_VOID ()
  {
    return symbol_type (token::TOK_VOID);
  }

  parser::symbol_type
  parser::make_PRINT ()
  {
    return symbol_type (token::TOK_PRINT);
  }

  parser::symbol_type
  parser::make_ENDL ()
  {
    return symbol_type (token::TOK_ENDL);
  }

  parser::symbol_type
  parser::make_RETURN ()
  {
    return symbol_type (token::TOK_RETURN);
  }

  parser::symbol_type
  parser::make_LCURL ()
  {
    return symbol_type (token::TOK_LCURL);
  }

  parser::symbol_type
  parser::make_RCURL ()
  {
    return symbol_type (token::TOK_RCURL);
  }

  parser::symbol_type
  parser::make_LPAREN ()
  {
    return symbol_type (token::TOK_LPAREN);
  }

  parser::symbol_type
  parser::make_RPAREN ()
  {
    return symbol_type (token::TOK_RPAREN);
  }

  parser::symbol_type
  parser::make_LARROW ()
  {
    return symbol_type (token::TOK_LARROW);
  }

  parser::symbol_type
  parser::make_RARROW ()
  {
    return symbol_type (token::TOK_RARROW);
  }

  parser::symbol_type
  parser::make_SEMI ()
  {
    return symbol_type (token::TOK_SEMI);
  }

  parser::symbol_type
  parser::make_EQUAL ()
  {
    return symbol_type (token::TOK_EQUAL);
  }

  parser::symbol_type
  parser::make_EXCL ()
  {
    return symbol_type (token::TOK_EXCL);
  }

  parser::symbol_type
  parser::make_COMMA ()
  {
    return symbol_type (token::TOK_COMMA);
  }

  parser::symbol_type
  parser::make_IN ()
  {
    return symbol_type (token::TOK_IN);
  }

  parser::symbol_type
  parser::make_PLUS ()
  {
    return symbol_type (token::TOK_PLUS);
  }

  parser::symbol_type
  parser::make_MINUS ()
  {
    return symbol_type (token::TOK_MINUS);
  }

  parser::symbol_type
  parser::make_STAR ()
  {
    return symbol_type (token::TOK_STAR);
  }

  parser::symbol_type
  parser::make_SLASH ()
  {
    return symbol_type (token::TOK_SLASH);
  }

  parser::symbol_type
  parser::make_IF ()
  {
    return symbol_type (token::TOK_IF);
  }

  parser::symbol_type
  parser::make_ELSE ()
  {
    return symbol_type (token::TOK_ELSE);
  }

  parser::symbol_type
  parser::make_STRING (const std::string& v)
  {
    return symbol_type (token::TOK_STRING, v);
  }

  parser::symbol_type
  parser::make_IDENTIFIER (const std::string& v)
  {
    return symbol_type (token::TOK_IDENTIFIER, v);
  }

  parser::symbol_type
  parser::make_INT (const int& v)
  {
    return symbol_type (token::TOK_INT, v);
  }

  parser::symbol_type
  parser::make_BOOL (const bool& v)
  {
    return symbol_type (token::TOK_BOOL, v);
  }

  parser::symbol_type
  parser::make_LOP (const LogOps& v)
  {
    return symbol_type (token::TOK_LOP, v);
  }



} // yy
#line 1714 "parser.yy.hpp" // lalr1.cc:392




#endif // !YY_YY_PARSER_YY_HPP_INCLUDED
