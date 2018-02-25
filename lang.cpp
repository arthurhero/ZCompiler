#include <memory>
#include <iostream>

#include "lang.h"

std::map<std::string, shared_ptr<Exp> > Exp::globals = std::map<std::string, shared_ptr<Exp> >();

void forward_context(
  std::map<std::string, shared_ptr<Exp> > *src,
  std::map<std::string, shared_ptr<Exp> > *dst) {

  shared_ptr<std::map<std::string, shared_ptr<Exp> > > tmp = make_shared<std::map<std::string, shared_ptr<Exp> > >();
  tmp->insert(src->begin(), src->end());
  tmp->insert(dst->begin(), dst->end());
  std::swap(*dst, *tmp);
}

/***** EVar *******************************************************************/

EVar::EVar(std::string _name) : name(_name) { }

Ans EVar::eval() {
  //cout << "eval var" << endl;

  Ans answer;
  if (context.find(name) == context.end()){
    if (Exp::globals.find(name) == Exp::globals.end()){
      std::cerr << "Error: Undeclared Variable in EVar! " << name << std::endl;
      exit(1);
   } else {
     forward_context(&context,&((Exp::globals[name])->context));
     answer = (Exp::globals[name])->eval();
     return answer;
   }
 } else {
   forward_context(&context,&((context[name])->context));
   answer = (context[name])->eval();
   return answer;
 }
}

string EVar::gettype(){return "EVar";}

/***** ELet *******************************************************************/

ELet::ELet(std::map<std::string, shared_ptr<Exp> > _context, shared_ptr<Exp> _expression)
 : expression(_expression) {
   context = _context;
 }

Ans ELet::eval() {
  //cout << "eval let" << endl;
  Ans answer;
  forward_context(&context,&(expression->context));
  answer = expression->eval();
  return answer;
}

string ELet::gettype(){return "ELet";}

/***** EFunc *******************************************************************/

EFunc::EFunc(shared_ptr<Exp> _expression) : expression(_expression) { }

EFunc::EFunc(std::vector<std::string> _params, shared_ptr<Exp> _expression)
 : params(_params), expression(_expression) { }

Ans EFunc::eval() {
  //cout << "eval func" << endl;

  Ans answer;
  answer.t = Func;
  return answer;
}

string EFunc::gettype(){return "EFunc";}

/***** EApp *******************************************************************/

EApp::EApp(shared_ptr<EFunc> _function) : function(_function){}

EApp::EApp(std::vector<shared_ptr<Exp> > _args, shared_ptr<EFunc> _function)
 : args(_args), function(_function) {
   if (args.size() != function->params.size()) {
     std::cerr << "Error: Unmatched number of arguments: " << name << std::endl;
     exit(1);
   }
   for (int i=0; i < args.size(); i++) {
     forward_context(&context,&(args[i]->context));
     Ans tmp = args[i]->eval();
     if (tmp.t == Int) {
       context[function->params[i]] = make_shared<ENumb>(tmp.i);
     } else if (tmp.t == Bool) {
       context[function->params[i]] = make_shared<EBool>(tmp.b);
     } else {
       context[function->params[i]] = args[i];
     }
   }
 }

EApp::EApp(shared_ptr<EVar> _fname) : fname(_fname){
 name = fname->name;
}

EApp::EApp(std::vector<shared_ptr<Exp> > _args, shared_ptr<EVar> _fname)
  : args(_args), fname(_fname) {
    name = fname->name;
  }

Ans EApp::eval() {

  //cout << "eval app" << endl;
  Ans answer;

  if (fname) {
    Ans func;

    if (context.find(name) == context.end()){
      if (Exp::globals.find(name) == Exp::globals.end()){
        std::cerr << "Error: Undeclared Variable in EApp! " << name << std::endl;
        exit(1);
     } else {
       forward_context(&context,&((Exp::globals[name])->context));
       func = (Exp::globals[name])->eval();
       if (func.t != Func) {
         std::cerr << "Error: Variable not of type Func: " << name << std::endl;
         exit(1);
       }
       function = std::dynamic_pointer_cast<EFunc>(Exp::globals[name]);
     }
   } else {
     forward_context(&context,&((context[name])->context));
     func = (context[name])->eval();
     if (func.t != Func) {
       std::cerr << "Error: Variable not of type Func: " << name << std::endl;
       exit(1);
     }
     function = std::dynamic_pointer_cast<EFunc>(context[name]);
   }

   if (args.size() != function->params.size()) {
     std::cerr << "Error: Unmatched number of arguments: " << name << std::endl;
     exit(1);
   }

    for (int i=0; i < args.size(); i++) {
      forward_context(&context,&(args[i]->context));
      Ans tmp = args[i]->eval();
      if (tmp.t == Int) {
        context[function->params[i]] = make_shared<ENumb>(tmp.i);
      } else if (tmp.t == Bool) {
        context[function->params[i]] = make_shared<EBool>(tmp.b);
      } else {
        context[function->params[i]] = args[i];
      }
    }
  }

  forward_context(&context,&(function->expression->context));
  answer = function->expression->eval();
  return answer;
}

string EApp::gettype(){return "EApp";}

/***** ENumb *******************************************************************/

ENumb::ENumb(int _value) : value(_value) { }
ENumb::ENumb(shared_ptr<EVar> _var) : var(_var) { }

ENumb::ENumb(shared_ptr<EApp> _app) : app(_app){}
ENumb::ENumb(shared_ptr<ELet> _let) : let(_let){}

ENumb::ENumb(shared_ptr<ENumb> _loperand, char _oper, shared_ptr<ENumb> _roperand)
 : loperand(_loperand), roperand(_roperand), oper(_oper){ }

Ans ENumb::eval() {
  //cout << "eval numb" << endl;
  Ans answer;
  if (var) {
    forward_context(&context,&(var->context));
    Ans tmp = var->eval();
    if (tmp.t == Int) {
      answer.i = tmp.i;
    } else {
      std::cerr << "Error: Variable not of type Int: " << var->name << std::endl;
      exit(1);
    }
  } else if (app) {
    forward_context(&context,&(app->context));
    Ans tmp = app->eval();
    if (tmp.t == Int) {
      answer.i = tmp.i;
    } else {
      std::cerr << "Error: Function not of type Int: " << app->name << std::endl;
      exit(1);
    }
  } else if (let) {
    forward_context(&context,&(let->context));
    Ans tmp = let->eval();
    if (tmp.t == Int) {
      answer.i = tmp.i;
    } else {
      std::cerr << "Error: Let Exp not of type Int" << std::endl;
      exit(1);
    }
  } else if (loperand) {
    forward_context(&context,&(loperand->context));
    forward_context(&context,&(roperand->context));
    switch (oper) {
      case '+':
      answer.i = loperand->eval().i + roperand->eval().i;
      break;
      case '-':
      answer.i = loperand->eval().i - roperand->eval().i;
      break;
      case '*':
      answer.i = loperand->eval().i * roperand->eval().i;
      break;
      case '/':
      answer.i = loperand->eval().i / roperand->eval().i;
      break;
    }
  } else {
    answer.i = value;
  }
  answer.t = Int;
  //cout << answer.i << endl;

  return answer;
 }

string ENumb::gettype(){return "ENumb";}

/***** EBool ******************************************************************/

EBool::EBool(bool _value) : value(_value) { }
EBool::EBool(shared_ptr<EVar> _var) : var(_var) { }

EBool::EBool(shared_ptr<EApp> _app) : app(_app){}
EBool::EBool(shared_ptr<ELet> _let) : let(_let){}

EBool::EBool(shared_ptr<EBool> _to_negate) : to_negate(_to_negate){}

EBool::EBool(shared_ptr<ENumb> _loperand, LogOps _oper, shared_ptr<ENumb> _roperand)
 : loperand(_loperand), roperand(_roperand), oper(_oper){ }

Ans EBool::eval() {
  //cout << "eval bool" << endl;

  Ans answer;
  if (var) {
    forward_context(&context,&(var->context));
    Ans tmp = var->eval();
    if (tmp.t == Bool) {
      answer.b = tmp.b;
    } else {
      std::cerr << "Error: Variable not of type Bool: " << var->name << std::endl;
      exit(1);
    }
  } else if (app) {
    forward_context(&context,&(app->context));
    Ans tmp = app->eval();
    if (tmp.t == Bool) {
      answer.b = tmp.b;
    } else {
      std::cerr << "Error: Function not of type Bool: " << app->name << std::endl;
      exit(1);
    }
  } else if (let) {
    forward_context(&context,&(let->context));
    Ans tmp = let->eval();
    if (tmp.t == Bool) {
      answer.b = tmp.b;
    } else {
      std::cerr << "Error: Let Exp not of type Bool" << std::endl;
      exit(1);
    }
  } else if (to_negate) {
    forward_context(&context,&(to_negate->context));
    Ans tmp = to_negate->eval();
    if (tmp.t == Bool) {
      answer.b = (!tmp.b);
    } else {
      std::cerr << "Error: Bool Exp not of type Bool" << std::endl;
      exit(1);
    }
  } else if (loperand) {
    forward_context(&context,&(loperand->context));
    forward_context(&context,&(roperand->context));
    if (oper == Less) {
      if (loperand->eval().i < roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == Greater) {
      if (loperand->eval().i > roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == Leq) {
      if (loperand->eval().i <= roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == Geq) {
      if (loperand->eval().i >= roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == Equal) {
      if (loperand->eval().i == roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == Neq) {
      if (loperand->eval().i != roperand->eval().i) answer.b = true;
      else answer.b = false;
    }
  } else {
    answer.b = value;
  }
  answer.t = Bool;
  return answer;
 }

string EBool::gettype(){return "EBool";}

/***** EIf ******************************************************************/

EIf::EIf(shared_ptr<EBool> _condition, shared_ptr<Exp> _first, shared_ptr<Exp> _second)
 : condition(_condition), first(_first), second(_second){ }

Ans EIf::eval() {
  //cout << "eval if" << endl;

  Ans answer;
  forward_context(&context,&(condition->context));
  forward_context(&context,&(first->context));
  forward_context(&context,&(second->context));
  //cout << "eval cond" << endl;

  if (condition->eval().b) {
    //cout << "eval first" << endl;

    answer = first->eval();
  } else {
    //cout << "eval second" << endl;

    answer = second->eval();
  }
  return answer;
 }

string EIf::gettype(){
  return "EIf";
}
