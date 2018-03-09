#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

enum Type {Int, Bool, Func, String, Void, Unknown};
enum LogOps {Equal, Less, Greater, Leq, Geq, Neq, And, Or};

struct Ans {
    int i;
    bool b;
    std::string s;
    Type t = Unknown;
};

/***** Declare *******************************************************************/

struct Stm;
struct Stms;
struct SBreak;
struct SContinue;
struct SAssign;
struct SPrint;
struct SFunc;
struct subStms;
struct SIf;
struct SWhile;
struct SReturn;

struct Exp;
struct EVoid;
struct EString;
struct EVar;
struct EFunc;
struct EApp;
struct ENumb;
struct EBool;

/***** Statements *******************************************************************/

struct Stms {
    Stms(std::vector< shared_ptr<Stm> > _stms);
    Ans exec();
    std::vector<std::map<std::string, shared_ptr<Exp> > > context_list;
    std::vector< shared_ptr<Stm> > stms;
};

struct Stm {
    virtual Ans exec() = 0;
    virtual string gettype() = 0;
    std::vector<std::map<std::string, shared_ptr<Exp> > > *context_list_p;
};

struct SBreak : public Stm {
  SBreak();
  Ans exec();
  string gettype();
};

struct SContinue : public Stm {
  SContinue();
  Ans exec();
  string gettype();
};

struct SAssign : public Stm {
  std::string id;
  shared_ptr<Exp> exp;
  bool is_ref = false;
  SAssign(std::string _id, shared_ptr<Exp> _exp);
  Ans exec();
  string gettype();
};

struct SPrint : public Stm {
  std::vector< shared_ptr<Exp> > content;
  SPrint(std::vector< shared_ptr<Exp> > _content);
  Ans exec();
  string gettype();
};

struct SFunc : public Stm {
  shared_ptr<EApp> app;
  SFunc(shared_ptr<EApp> _app);
  Ans exec();
  string gettype();
};

struct subStms {
    subStms(std::vector< shared_ptr<Stm> > _stms);
    Ans exec();
    std::vector<std::map<std::string, shared_ptr<Exp> > > context_list;
    std::vector<std::map<std::string, shared_ptr<Exp> > > *context_list_p;
    bool *break_ctl_p;
    bool *continue_ctl_p;
    std::vector< shared_ptr<Stm> > stms;
};

struct SIf : public Stm {
    shared_ptr<EBool> condition;
    shared_ptr<subStms> first;
    shared_ptr<subStms> second;
    shared_ptr<SIf> sec_if;
    bool *break_ctl_p;
    bool *continue_ctl_p;
    SIf(shared_ptr<EBool> _condition, shared_ptr<subStms> _first);
    SIf(shared_ptr<EBool> _condition, shared_ptr<subStms> _first, shared_ptr<subStms> _second);
    SIf(shared_ptr<EBool> _condition, shared_ptr<subStms> _first, shared_ptr<SIf> _sec_if);
    Ans exec();
    string gettype();
};

struct SWhile : public Stm {
    shared_ptr<EBool> condition;
    shared_ptr<subStms> body;
    bool break_ctl = false;
    bool continue_ctl = false;
    SWhile(shared_ptr<EBool> _condition, shared_ptr<subStms> _body);
    Ans exec();
    string gettype();
};

struct SReturn : public Stm {
    shared_ptr<Exp> expression;
    SReturn(shared_ptr<Exp> _expression);
    Ans exec();
    string gettype();
};


/***** Expressions *******************************************************************/

struct Exp {
    virtual Ans eval() = 0;
    virtual string gettype() = 0;
    virtual string tostring() = 0;
    std::vector<std::map<std::string, shared_ptr<Exp> > > context_list;
    static std::map<std::string, shared_ptr<Exp> > refs;
};

struct EVoid : public Exp {
    EVoid();
    Ans eval();
    string gettype();
    string tostring();
};

struct EString : public Exp {
    string str;
    EString(string _str);
    Ans eval();
    string gettype();
    string tostring();
};

struct EVar : public Exp {
    std::string name;
    bool is_ref=false;
    EVar(std::string _name);
    Ans eval();
    string gettype();
    string tostring();
};

struct EFunc : public Exp {
    std::vector<std::string> params;
    shared_ptr<Stms> stms;
    EFunc(shared_ptr<Stms> _stms);
    EFunc(std::vector<std::string> _params, shared_ptr<Stms> _stms);
    Ans eval();
    string gettype();
    string tostring();
};

struct EApp : public Exp {
    std::string name = "Anonymous";
    std::vector<shared_ptr<Exp> > args;
    shared_ptr<EFunc> function;
    shared_ptr<EVar> fname;
    EApp(shared_ptr<EFunc> _function);
    EApp(shared_ptr<EVar> _fname);
    EApp(std::vector<shared_ptr<Exp> > _args, shared_ptr<EVar> _fname);
    EApp(std::vector<shared_ptr<Exp> > _args, shared_ptr<EFunc> _function);
    Ans eval();
    string gettype();
    string tostring();
};

struct ENumb : public Exp {
    shared_ptr<Exp> loperand;
    shared_ptr<Exp> roperand;
    char oper;
    int value;
    bool is_negative = false;
    ENumb(int _value);
    ENumb(shared_ptr<Exp> _loperand, char _oper, shared_ptr<Exp> _roperand);
    Ans eval();
    string gettype();
    string tostring();
};

struct EBool : public Exp {
    shared_ptr<Exp> loperand;
    shared_ptr<Exp> roperand;
    shared_ptr<Exp> to_negate;
    LogOps oper;
    bool value;
    EBool(bool _value);
    EBool(shared_ptr<Exp> _to_negate);
    EBool(shared_ptr<Exp> _loperand, LogOps _oper, shared_ptr<Exp> _roperand);
    Ans eval();
    std::string gettype();
    string tostring();
};
