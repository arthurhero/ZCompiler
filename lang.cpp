#include <memory>
#include <iostream>

#include "lang.h"

std::map<std::string, shared_ptr<Exp> > Exp::globals = std::map<std::string, shared_ptr<Exp> >();

void forward_context(
  std::map<std::string, shared_ptr<Exp> > *src,
  std::map<std::string, shared_ptr<Exp> > *dst) {

  shared_ptr<std::map<std::string, shared_ptr<Exp> > > tmp =
    make_shared<std::map<std::string, shared_ptr<Exp> > >();
  tmp->insert(dst->begin(), dst->end());
  tmp->insert(src->begin(), src->end());
  std::swap(*dst, *tmp);
}

void forward_contexts(
  std::vector<shared_ptr<std::map<std::string, shared_ptr<Exp> > > > *src,
  std::vector<shared_ptr<std::map<std::string, shared_ptr<Exp> > > > *dst) {

  shared_ptr<std::vector<shared_ptr<std::map<std::string, shared_ptr<Exp> > > > > tmp =
  make_shared<std::vector<shared_ptr<std::map<std::string, shared_ptr<Exp> > > > >();

  tmp->insert(tmp->end(), dst->begin(), dst->end());
  tmp->insert(tmp->end(), src->begin(), src->end());

  std::swap(*dst, *tmp);
}

string ans_to_string(Ans ans) {
  if (ans.t == Int) {
    return std::to_string(ans.i);
  } else if (ans.t == Bool) {
    if (ans.b) {
      return "true";
    } else {
      return "false";
    }
  } else if (ans.t == String) {
    return ans.s;
  } else if (ans.t == Void) {
    return "";
  } else if (ans.t == Func) {
    return "#function";
  } else {
    return "Not printable";
  }
}

/***** Stms *******************************************************************/

Stms::Stms(std::vector< shared_ptr<Stm> > _stms) : stms(_stms){ }

Ans Stms::exec() {
  Ans answer;
  answer.t = Void;

  //context.insert(make_pair("test",make_shared<EVoid>()));

  for (int i = 0; i < stms.size(); i++) {
    shared_ptr<Stm> stm = stms[i];
    forward_contexts(&parent_contexts, &(stm->parent_contexts));
    stm->parent_contexts.insert(stm->parent_contexts.begin(),
      std::shared_ptr<std::map<std::string, shared_ptr<Exp> > >(&context));
    Ans tmp = stm->exec();
    if (stm->gettype().compare("SReturn")==0) {
      answer = tmp;
      break;
    } else if (stm->gettype().compare("SIf")==0) {
      if (tmp.t != Void) {
        answer = tmp;
        break;
      }
    }
    cout << "end one exec" << endl;
    for (auto const& p : context) {
      cout << p.first << endl;
    }
    for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
      cout << "in parent" << endl;
      for (auto const& p : *c) {
        cout << p.first << endl;
      }
    }
  }

  return answer;
}

/***** SAssign *******************************************************************/

SAssign::SAssign(std::string _id, shared_ptr<Exp> _exp):id(_id),exp(_exp){}

Ans SAssign::exec() {
  shared_ptr<Exp> newexp;

  for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
    forward_context(&(*c),&(exp->context));
  }

  Ans tmp = exp->eval();

  if (tmp.t == Int) {
    newexp = make_shared<ENumb>(tmp.i);
  } else if (tmp.t == Bool) {
    newexp = make_shared<EBool>(tmp.b);
  } else if (tmp.t == String) {
    newexp = make_shared<EString>(tmp.s);
  } else {
    newexp = exp;
  }

  bool found = false;

  for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
    for (auto const& p : *c) {
      cout << "in assign " << p.first << endl;
    }
  }

  for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
    std::map<std::string, shared_ptr<Exp> > context = *c;
    if (context.find(id) != context.end()){
      context[id] = exp;
      found = true;
      break;
    }
  }

  if (! found) {
    shared_ptr<std::map<std::string, shared_ptr<Exp> > > context_p = parent_contexts[0];
    cout << "inserting " << id << endl;
    context_p->insert(make_pair(id,newexp));
  }

  for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
    for (auto const& p : *c) {
      cout << "in assign 2" << p.first << endl;
    }
  }

  Ans answer;
  answer.t = Void;
  return answer;
}

string SAssign::gettype() {return "SAssign";}

/***** SPrint *******************************************************************/

SPrint::SPrint(std::vector< shared_ptr<Exp> > _content):content(_content) {}

Ans SPrint::exec() {
  for (shared_ptr<Exp> exp : content) {
    cout << "start to forward in print" << endl;
    for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
      for (pair<std::string, shared_ptr<Exp> > p : *c) {
        cout << p.first << endl;
      }
      forward_context(&(*c),&(exp->context));
    }
    cout << exp->tostring();
  }

  Ans answer;
  answer.t = Void;
  return answer;
}

string SPrint::gettype() {return "SPrint";}

/***** SFunc *******************************************************************/

SFunc::SFunc(shared_ptr<EApp> _app):app(_app) {}

Ans SFunc::exec() {
  for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
    forward_context(&(*c),&(app->context));
  }
  Ans answer = app->eval();
  return answer;
}

string SFunc::gettype() {return "SFunc";}

/***** SIf *******************************************************************/

SIf::SIf(shared_ptr<EBool> _condition, shared_ptr<Stms> _first)
 : condition(_condition), first(_first){ }

SIf::SIf(shared_ptr<EBool> _condition, shared_ptr<Stms> _first, shared_ptr<Stms> _second)
 : condition(_condition), first(_first), second(_second){ }

SIf::SIf(shared_ptr<EBool> _condition, shared_ptr<Stms> _first, shared_ptr<SIf> _sec_if)
 : condition(_condition), first(_first), sec_if(_sec_if){ }

Ans SIf::exec() {
  //cout << "eval if" << endl;

  Ans answer;
  for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
    forward_context(&(*c),&(condition->context));
  }
  //cout << "eval cond" << endl;

  if (condition->eval().b) {
    //cout << "eval first" << endl;
    forward_contexts(&parent_contexts, &(first->parent_contexts));
    answer = first->exec();
  } else {
    //cout << "eval second" << endl;
    if (second) {
      forward_contexts(&parent_contexts, &(second->parent_contexts));
      answer = second->exec();
    } else if (sec_if) {
      forward_contexts(&parent_contexts, &(sec_if->parent_contexts));
      answer = sec_if->exec();
    } else {
      answer.t = Void;
    }
  }
  return answer;
 }

string SIf::gettype() {return "SIf";}


/***** SReturn *******************************************************************/

SReturn::SReturn(shared_ptr<Exp> _expression) : expression(_expression){}

Ans SReturn::exec() {
  for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
    forward_context(&(*c),&(expression->context));
  }
  Ans answer = expression->eval();
  return answer;
}

string SReturn::gettype() {return "SReturn";}

/***** EVoid *******************************************************************/

EVoid::EVoid(){ }

Ans EVoid::eval() {
  Ans answer;
  answer.t = Void;
  return answer;
}

string EVoid::gettype(){return "EVoid";}

string EVoid::tostring(){return "";}

/***** EString *******************************************************************/

EString::EString(string _str):str(_str){ }

Ans EString::eval() {
  Ans answer;
  answer.s = str;
  answer.t = String;
  return answer;
}

string EString::gettype(){return "EString";}

string EString::tostring(){return str;}


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

string EVar::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}


/***** ELet *******************************************************************/

ELet::ELet(std::vector<std::pair<std::string, shared_ptr<Exp> > > _assigns, shared_ptr<Exp> _expression)
 : expression(_expression), assigns(_assigns) {
 }

Ans ELet::eval() {
  //cout << "eval let" << endl;

  for (auto const& p : assigns) {
    forward_context(&context,&(p.second->context));
    Ans tmp = p.second->eval();
    if (tmp.t == Int) {
      context[p.first] = make_shared<ENumb>(tmp.i);
      //cout << p.first << "=" << tmp.i << endl;
    } else if (tmp.t == Bool) {
      context[p.first] = make_shared<EBool>(tmp.b);
    } else {
      context[p.first] = p.second;
    }
  }

  Ans answer;
  forward_context(&context,&(expression->context));
  answer = expression->eval();
  return answer;
}

string ELet::gettype(){return "ELet";}

string ELet::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}

/***** EFunc *******************************************************************/

EFunc::EFunc(shared_ptr<Stms> _stms): stms(_stms) { }

EFunc::EFunc(std::vector<std::string> _params, shared_ptr<Stms> _stms)
 : params(_params), stms(_stms) { }

Ans EFunc::eval() {
  //cout << "eval func" << endl;
  Ans answer;
  answer.t = Func;
  return answer;
}

string EFunc::gettype(){return "EFunc";}

string EFunc::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}

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

  for (auto const& p : context) {
    cout << "in app " << p.first << endl;
    cout << p.second->tostring() << endl;
  }

  //forward_contexts(&parent_contexts, &(function->stms->parent_contexts));
  //function->stms->parent_contexts.insert(function->stms->parent_contexts.begin(),
  //  std::shared_ptr<std::map<std::string, shared_ptr<Exp> > >(&context));
  function->stms->context.clear();
  function->stms->parent_contexts.clear();
  forward_context(&context,&(function->stms->context));
/*
  for (shared_ptr<std::map<std::string, shared_ptr<Exp> > > c : parent_contexts) {
    forward_context(&(*c),&(function->stms->context));
  }
*/
  answer = function->stms->exec();
  return answer;
}

string EApp::gettype(){return "EApp";}

string EApp::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}

/***** ENumb *******************************************************************/

ENumb::ENumb(int _value) : value(_value) { }

ENumb::ENumb(shared_ptr<Exp> _loperand, char _oper, shared_ptr<Exp> _roperand)
 : loperand(_loperand), roperand(_roperand), oper(_oper){ }

Ans ENumb::eval() {
  //cout << "eval numb" << endl;

  Ans answer;
  if (loperand) {
    forward_context(&context,&(loperand->context));
    forward_context(&context,&(roperand->context));
    Ans f = loperand->eval();
    Ans s = roperand->eval();
    if (f.t != Int || s.t != Int) {
      cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
      exit(1);
    }
    switch (oper) {
      case '+':
      answer.i = f.i + s.i;
      break;
      case '-':
      //cout << "minus" << endl;
      answer.i = f.i - s.i;
      break;
      case '*':
      answer.i = f.i * s.i;
      break;
      case '/':
      answer.i = f.i / s.i;
      break;
    }
  } else {
    //cout << "literal" << endl;

    answer.i = value;
  }
  answer.t = Int;
  //cout << answer.i << endl;
  //cout << "numb " << answer.i << endl;
  return answer;
 }

string ENumb::gettype(){return "ENumb";}

string ENumb::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}

/***** EBool ******************************************************************/

EBool::EBool(bool _value) : value(_value) { }

EBool::EBool(shared_ptr<Exp> _to_negate) : to_negate(_to_negate){}

EBool::EBool(shared_ptr<Exp> _loperand, LogOps _oper, shared_ptr<Exp> _roperand)
 : loperand(_loperand), roperand(_roperand), oper(_oper){ }

Ans EBool::eval() {
  //cout << "eval bool" << endl;

  Ans answer;
  if (to_negate) {
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
    Ans f = loperand->eval();
    Ans s = roperand->eval();

    if (oper == Less) {
      if (f.t != Int || s.t != Int) {
        cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (loperand->eval().i < roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == Greater) {
      if (f.t != Int || s.t != Int) {
        cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (loperand->eval().i > roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == Leq) {
      if (f.t != Int || s.t != Int) {
        cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (loperand->eval().i <= roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == Geq) {
      if (f.t != Int || s.t != Int) {
        cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (loperand->eval().i >= roperand->eval().i) answer.b = true;
      else answer.b = false;
    } else if (oper == And) {
      if (f.t != Bool || s.t != Bool) {
        cerr << "Expected Bool and Bool. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (loperand->eval().b && roperand->eval().b) answer.b = true;
      else answer.b = false;
    } else if (oper == Or) {
      if (f.t != Bool || s.t != Bool) {
        cerr << "Expected Bool and Bool. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (loperand->eval().b || roperand->eval().b) answer.b = true;
      else answer.b = false;
    } else if (oper == Equal) {
      if (f.t == Int || s.t == Int) {
        if (loperand->eval().i == roperand->eval().i) answer.b = true;
        else answer.b = false;
      } else if (f.t == Bool || s.t == Bool) {
        if (loperand->eval().b == roperand->eval().b) answer.b = true;
        else answer.b = false;
      } else {
        cerr << "Expected Bool/Int and Bool/Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
    } else if (oper == Neq) {
      if (f.t == Int || s.t == Int) {
        if (loperand->eval().i != roperand->eval().i) answer.b = true;
        else answer.b = false;
      } else if (f.t == Bool || s.t == Bool) {
        if (loperand->eval().b != roperand->eval().b) answer.b = true;
        else answer.b = false;
      } else {
        cerr << "Expected Bool/Int and Bool/Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
    }
  } else {
    answer.b = value;
  }
  answer.t = Bool;
  return answer;
 }

string EBool::gettype(){return "EBool";}

string EBool::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}
