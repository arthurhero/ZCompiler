#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

enum Type {Int, Bool, Func, Unknown};
enum LogOps {Equal, Less, Greater, Leq, Geq, Neq};

struct Ans {
    int i;
    bool b;
    Type t = Unknown;
};

struct Exp {
    virtual Ans eval() = 0;
    virtual string gettype() = 0;
    std::map<std::string, shared_ptr<Exp> > context;
    static std::map<std::string, shared_ptr<Exp> > globals;
};

struct EVar : public Exp {
    std::string name;
    EVar(std::string _name);
    Ans eval();
    string gettype();
};

struct ELet : public Exp {
    shared_ptr<Exp> expression;
    ELet(std::map<std::string, shared_ptr<Exp> > _context, shared_ptr<Exp> _expression);
    Ans eval();
    string gettype();
};

struct EFunc : public Exp {
    std::vector<std::string> params;
    shared_ptr<Exp> expression;
    EFunc(shared_ptr<Exp> _expression);
    EFunc(std::vector<std::string> _params, shared_ptr<Exp> _expression);
    Ans eval();
    string gettype();
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
};

struct ENumb : public Exp {
    shared_ptr<ENumb> loperand;
    shared_ptr<ENumb> roperand;
    char oper;
    int value;
    shared_ptr<EVar> var;
    shared_ptr<EApp> app;
    shared_ptr<ELet> let;
    ENumb(int _value);
    ENumb(shared_ptr<EVar> _var);
    ENumb(shared_ptr<EApp> _app);
    ENumb(shared_ptr<ELet> _let);
    ENumb(shared_ptr<ENumb> _loperand, char _oper, shared_ptr<ENumb> _roperand);
    Ans eval();
    string gettype();
};

struct EBool : public Exp {
    shared_ptr<ENumb> loperand;
    shared_ptr<ENumb> roperand;
    shared_ptr<EBool> to_negate;
    LogOps oper;
    bool value;
    shared_ptr<EVar> var;
    shared_ptr<EApp> app;
    shared_ptr<ELet> let;
    EBool(bool _value);
    EBool(shared_ptr<EVar> _var);
    EBool(shared_ptr<EApp> _app);
    EBool(shared_ptr<ELet> _let);
    EBool(shared_ptr<EBool> _to_negate);
    EBool(shared_ptr<ENumb> _loperand, LogOps _oper, shared_ptr<ENumb> _roperand);
    Ans eval();
    std::string gettype();
};

struct EIf : public Exp {
    shared_ptr<EBool> condition;
    shared_ptr<Exp> first;
    shared_ptr<Exp> second;
    EIf(shared_ptr<EBool> _condition, shared_ptr<Exp> _first, shared_ptr<Exp> _second);
    Ans eval();
    std::string gettype();
};
