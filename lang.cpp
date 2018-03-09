#include <memory>
#include <iostream>

#include "lang.h"

std::map<std::string, shared_ptr<Exp> > Exp::globals = std::map<std::string, shared_ptr<Exp> >();

string unescape(const string& s) {
  string res;
  string::const_iterator it = s.begin();
  while (it != s.end()) {
    char c = *it++;
    if (c == '\\' && it != s.end())
    {
      switch (*it++) {
      case '\\': c = '\\'; break;
      case 'n': c = '\n'; break;
      case 't': c = '\t'; break;
      case '"': c = '"'; break;
      case '\'': c = '\''; break;
      case 'b': c = '\b'; break;
      // all other escapes
      default:
        // invalid escape sequence - skip it. alternatively you can copy it as is, throw an exception...
        continue;
      }
    }
    res += c;
  }
  return res;
}

void forward_context(
  std::vector<std::map<std::string, shared_ptr<Exp> > > *src,
  std::vector<std::map<std::string, shared_ptr<Exp> > > *dst) {

  std::map<std::string, shared_ptr<Exp> > tmp =
    std::map<std::string, shared_ptr<Exp> >();
  tmp.insert((*src)[0].begin(), (*src)[0].end());
  dst->insert(dst->begin(),tmp);
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

Stms::Stms(std::vector< shared_ptr<Stm> > _stms) : stms(_stms){
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

Ans Stms::exec() {

  Ans answer;
  answer.t = Void;

  for (int i = 0; i < stms.size(); i++) {
    shared_ptr<Stm> stm = stms[i];

    stm->context_list_p = &context_list;
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
  }
  context_list.erase(context_list.begin());

  return answer;
}

/***** SAssign *******************************************************************/

SAssign::SAssign(std::string _id, shared_ptr<Exp> _exp):id(_id),exp(_exp){}

Ans SAssign::exec() {
  shared_ptr<Exp> newexp;

  forward_context(context_list_p,&(exp->context_list));

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

  (*context_list_p)[0][id]=newexp;

  Ans answer;
  answer.t = Void;
  return answer;
}

string SAssign::gettype() {return "SAssign";}

/***** SPrint *******************************************************************/

SPrint::SPrint(std::vector< shared_ptr<Exp> > _content):content(_content) {}

Ans SPrint::exec() {
  for (shared_ptr<Exp> exp : content) {
    forward_context(context_list_p,&(exp->context_list));
    printf("%s",exp->tostring().c_str());
  }

  Ans answer;
  answer.t = Void;
  return answer;
}

string SPrint::gettype() {return "SPrint";}

/***** SFunc *******************************************************************/

SFunc::SFunc(shared_ptr<EApp> _app):app(_app) {}

Ans SFunc::exec() {
  forward_context(context_list_p,&(app->context_list));
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

  Ans answer;
  forward_context(context_list_p,&(condition->context_list));

  if (condition->eval().b) {
    forward_context(context_list_p,&(first->context_list));
    answer = first->exec();
  } else {
    if (second) {
      forward_context(context_list_p,&(second->context_list));
      answer = second->exec();
    } else if (sec_if) {
      sec_if->context_list_p=context_list_p;
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
  forward_context(context_list_p,&(expression->context_list));
  Ans answer = expression->eval();
  return answer;
}

string SReturn::gettype() {return "SReturn";}

/***** EVoid *******************************************************************/

EVoid::EVoid(){
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

Ans EVoid::eval() {
  Ans answer;
  answer.t = Void;
  return answer;
}

string EVoid::gettype(){return "EVoid";}

string EVoid::tostring(){return "";}

/***** EString *******************************************************************/

EString::EString(string _str){
  str = unescape(_str);
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

Ans EString::eval() {
  Ans answer;
  answer.s = str;
  answer.t = String;
  return answer;
}

string EString::gettype(){return "EString";}

string EString::tostring(){return str;}


/***** EVar *******************************************************************/

EVar::EVar(std::string _name) : name(_name) {
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

Ans EVar::eval() {
  Ans answer;

  if (context_list[0].find(name) == context_list[0].end()){
   std::cerr << "Error: Undeclared Variable in EVar! " << name << std::endl;
   exit(1);
 } else {
   forward_context(&context_list,&((context_list[0][name])->context_list));
   answer = (context_list[0][name])->eval();
 }
 context_list.erase(context_list.begin());
 return answer;
}

string EVar::gettype(){return "EVar";}

string EVar::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}

/***** EFunc *******************************************************************/

EFunc::EFunc(shared_ptr<Stms> _stms): stms(_stms) {
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

EFunc::EFunc(std::vector<std::string> _params, shared_ptr<Stms> _stms)
 : params(_params), stms(_stms) {
   std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
   context_list.insert(context_list.begin(), first);
 }

Ans EFunc::eval() {
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

EApp::EApp(shared_ptr<EFunc> _function) : function(_function){
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

EApp::EApp(std::vector<shared_ptr<Exp> > _args, shared_ptr<EFunc> _function)
 : args(_args), function(_function) {
   std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
   context_list.insert(context_list.begin(), first);
   if (args.size() != function->params.size()) {
     std::cerr << "Error: Unmatched number of arguments: " << name << std::endl;
     exit(1);
   }
 }


EApp::EApp(shared_ptr<EVar> _fname) : fname(_fname){
 name = fname->name;
 std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
 context_list.insert(context_list.begin(), first);
}

EApp::EApp(std::vector<shared_ptr<Exp> > _args, shared_ptr<EVar> _fname)
  : args(_args), fname(_fname) {
    name = fname->name;
    std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
    context_list.insert(context_list.begin(), first);
  }

Ans EApp::eval() {

  Ans answer;
  std::map<std::string, shared_ptr<Exp> > *context_p = &(context_list[0]);

  if (fname) {
    Ans func;

    if (context_p->find(name) == context_p->end()){
     std::cerr << "Error: Undeclared Variable in EApp! " << name << std::endl;
     exit(1);
   } else {
     //forward_context(&context,&((context[name])->context));
     forward_context(&context_list,&((*context_p)[name]->context_list));
     func = ((*context_p)[name])->eval();
     if (func.t != Func) {
       std::cerr << "Error: Variable not of type Func: " << name << std::endl;
       exit(1);
     }
     function = std::dynamic_pointer_cast<EFunc>((*context_p)[name]);
   }

 }

   if (args.size() != function->params.size()) {
     std::cerr << "Error: Unmatched number of arguments: " << name << std::endl;
     exit(1);
   }

    for (int i=0; i < args.size(); i++) {
      forward_context(&context_list,&(args[i]->context_list));

      Ans tmp = args[i]->eval();
      if (tmp.t == Int) {
        (*context_p)[function->params[i]] = make_shared<ENumb>(tmp.i);
      } else if (tmp.t == Bool) {
        (*context_p)[function->params[i]] = make_shared<EBool>(tmp.b);
      } else {
        (*context_p)[function->params[i]] = args[i];
      }
    }

  forward_context(&context_list,&(function->stms->context_list));
  answer = function->stms->exec();

  context_list.erase(context_list.begin());
  return answer;
}

string EApp::gettype(){return "EApp";}

string EApp::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}

/***** ENumb *******************************************************************/

ENumb::ENumb(int _value) : value(_value) {
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

ENumb::ENumb(shared_ptr<Exp> _loperand, char _oper, shared_ptr<Exp> _roperand)
 : loperand(_loperand), roperand(_roperand), oper(_oper){
   std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
   context_list.insert(context_list.begin(), first);
 }

Ans ENumb::eval() {
  Ans answer;
  if (loperand) {
    forward_context(&context_list,&(loperand->context_list));
    forward_context(&context_list,&(roperand->context_list));

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
    answer.i = value;
  }
  answer.t = Int;
  if (is_negative) {
    answer.i = (-1)*(answer.i);
  }
  context_list.erase(context_list.begin());
  return answer;
 }

string ENumb::gettype(){return "ENumb";}

string ENumb::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}

/***** EBool ******************************************************************/

EBool::EBool(bool _value) : value(_value) {
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

EBool::EBool(shared_ptr<Exp> _to_negate) : to_negate(_to_negate){
  std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
  context_list.insert(context_list.begin(), first);
}

EBool::EBool(shared_ptr<Exp> _loperand, LogOps _oper, shared_ptr<Exp> _roperand)
 : loperand(_loperand), roperand(_roperand), oper(_oper){
   std::map<std::string, shared_ptr<Exp> > first = std::map<std::string, shared_ptr<Exp> >();
   context_list.insert(context_list.begin(), first);
 }

Ans EBool::eval() {
  Ans answer;
  if (to_negate) {
    forward_context(&context_list,&(to_negate->context_list));

    Ans tmp = to_negate->eval();
    if (tmp.t == Bool) {
      answer.b = (!tmp.b);
    } else {
      std::cerr << "Error: Bool Exp not of type Bool" << std::endl;
      exit(1);
    }
  } else if (loperand) {
    forward_context(&context_list,&(loperand->context_list));
    forward_context(&context_list,&(roperand->context_list));

    Ans f = loperand->eval();
    Ans s = roperand->eval();

    if (oper == Less) {
      if (f.t != Int || s.t != Int) {
        cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (f.i < s.i) answer.b = true;
      else answer.b = false;
    } else if (oper == Greater) {
      if (f.t != Int || s.t != Int) {
        cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (f.i > s.i) answer.b = true;
      else answer.b = false;
    } else if (oper == Leq) {
      if (f.t != Int || s.t != Int) {
        cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (f.i <= s.i) answer.b = true;
      else answer.b = false;
    } else if (oper == Geq) {
      if (f.t != Int || s.t != Int) {
        cerr << "Expected Int and Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (f.i >= s.i) answer.b = true;
      else answer.b = false;
    } else if (oper == And) {
      if (f.t != Bool || s.t != Bool) {
        cerr << "Expected Bool and Bool. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (f.b && s.b) answer.b = true;
      else answer.b = false;
    } else if (oper == Or) {
      if (f.t != Bool || s.t != Bool) {
        cerr << "Expected Bool and Bool. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
      if (f.b || s.b) answer.b = true;
      else answer.b = false;
    } else if (oper == Equal) {
      if (f.t == Int || s.t == Int) {
        if (f.i == s.i) answer.b = true;
        else answer.b = false;
      } else if (f.t == Bool || s.t == Bool) {
        if (f.b == s.b) answer.b = true;
        else answer.b = false;
      } else {
        cerr << "Expected Bool/Int and Bool/Int. Given " << f.t << " and " << s.t << endl;
        exit(1);
      }
    } else if (oper == Neq) {
      if (f.t == Int || s.t == Int) {
        if (f.i != s.i) answer.b = true;
        else answer.b = false;
      } else if (f.t == Bool || s.t == Bool) {
        if (f.b != s.b) answer.b = true;
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

  context_list.erase(context_list.begin());
  return answer;
 }

string EBool::gettype(){return "EBool";}

string EBool::tostring(){
  Ans answer = this->eval();
  return ans_to_string(answer);
}
