#pragma once
#include <string>

using namespace std;

class token {
public:
  virtual void print()=0;
  virtual token* eval()=0;
  virtual string getType()=0;
  virtual bool needsChild() {
    return false;
  }
  virtual token** emptyChild() {
    return NULL;
  }
};
