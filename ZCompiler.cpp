#include <iostream>
#include <fstream>
#include <getopt.h>
#include <vector>
#include <ctype.h>
#include <string>
#include <stack>

#include "token.h"
#include "boolean.h"
#include "ifstate.h"
#include "integer.h"
#include "loperator.h"
#include "oper.h"
#include "paren.h"

using namespace std;

static int help_flag = 0;
static int length_flag = 0;

vector<token*> lexing(ifstream &in) {
  vector<token*> tokens;
  char c;

  int count = 0;
  bool skipflag = false, intflag = false;

  string number = "";

  while (in.get(c)) {

    if (skipflag) {
      if (count == 0) {
        skipflag = false;
      } else {
        count--;
        continue;
      }
    }

    if (intflag) {
      if (isdigit(c)) {
        number += c;
        continue;
      } else {
        int num = stoi(number);
        number = "";
        integer* t = new integer(num);
        tokens.push_back(t);
        intflag = false;
      }
    }

    if (isspace(c)) {
      continue;
    } else if (c == '(' || c == ')' ) {
      paren* t = new paren(c);
      tokens.push_back(t);
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      oper* t = new oper(c);
      tokens.push_back(t);
    } else if (c == '<') {
      skipflag = true;
      count = 1;
      loperator* t = new loperator("<=");
      tokens.push_back(t);
      continue;
    } else if (c == 'i') {
      skipflag = true;
      count = 1;
      ifstate* t = new ifstate();
      tokens.push_back(t);
      continue;
    } else if (c == 't') {
      skipflag = true;
      count = 3;
      boolean* t = new boolean(c);
      tokens.push_back(t);
    } else if (c == 'f') {
      skipflag = true;
      count = 4;
      boolean* t = new boolean(c);
      tokens.push_back(t);
    } else if (isdigit(c)) {
      intflag = true;
      number += c;
    } else {
      cerr << "Unexpected char: " << c;
      exit(1);
    }
  }

  return tokens;

}

void parsing(vector<token*> tokens) {
  token* root;
  token* result;
  bool rootflag = true;

  stack<token*> st;

  while (tokens.size() != 0) {
    token* cur = tokens.at(0);
    tokens.erase(tokens.begin());

    if (cur->getType().compare("paren") == 0) {
      continue;
    } else {
      if (rootflag) {
        root = cur;
        rootflag = false;
      }
      if (st.size() != 0) {
        token* top = st.top();
        st.pop();
        if (top->getType().compare("ifstate") == 0 ||
            top->getType().compare("oper") == 0 ||
            top->getType().compare("loperator") == 0) {
          if (top->needsChild()) {
            if (top->emptyChild() == NULL) {
              cout << "nulll" << endl;
            }
            token** child = top->emptyChild();
            *child = cur;
            if (top->needsChild()){
              st.push(top);
            }
          }
        }
      }
      if (cur->getType().compare("ifstate") == 0 ||
          cur->getType().compare("oper") == 0 ||
          cur->getType().compare("loperator") == 0) {
        st.push(cur);
      }
    }

  }
  result = root->eval();

  if (result->getType().compare("integer") == 0) {
    result->print();
    return;
  } else if (result->getType().compare("boolean") == 0) {
    result->print();
    return;
  } else {
    cerr << "Unexpected evaluation result";
    exit(1);
  }
}

void printTokens(vector<token*> tokens) {
  for (int i = 0; i < tokens.size(); i++) {
    tokens.at(i)->print();
  }
}

int main(int argc, char** argv) {

  // Parsing command line arguments
  int c;

  while (1) {
    static struct option long_options[] =
    {
      /* These options set a flag. */
      {"help", no_argument, &help_flag, 1},
      {"length", no_argument, &length_flag, 1},
      /* These options don’t set a flag.
      We distinguish them by their indices. */
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long (argc, argv, "", long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
    break;

    switch (c)
    {
      case 0:
      if (long_options[option_index].flag != 0) break;
      cout << "option " << long_options[option_index].name << endl;
      if (optarg) cout << " with arg " << optarg << endl;
      break;

      case '?':
      /* getopt_long already printed an error message. */
      break;

      default:
      abort ();
    }
  }

  if (help_flag) {
    cout << "Usage: my-project [flags] [args]" << endl;
    cout << "Available flags:" << endl;
    cout << "  --length     prints the lengths of each of the arguments" << endl;
    cout << "  --help       prints this help message" << endl;
    return 0;
  }

  if (optind < argc)
  {
    if (length_flag) {
      while (optind < argc) {
        cout << strlen(argv[optind++]) << endl;
      }
      return 0;
    }

    /*
    while (optind < argc) {
      cout << argv[optind++] << endl;
    }
    */

    // Start of Assignment 2

  } else {
    cerr << "Invalid argument";
    exit(1);
  }

  ifstream inFile;
  inFile.open(argv[optind]);

  if (!inFile) {
    cerr << "Unable to open file";
    exit(1);
  }

  vector<token*> tokens = lexing(inFile);
  //printTokens(tokens);

  parsing(tokens);

  //string result = parsing(tokens);
  //cout << result << endl;

  inFile.close();

  return 0;

}
