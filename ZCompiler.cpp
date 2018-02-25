#include <iostream>
#include <getopt.h>
#include "lang.h"
#include "parser_driver.h"

static int help_flag = 0;
static int lex_flag = 0;
static int parse_flag = 0;

void start(const std::string filename) {
  parser_driver driver (filename, lex_flag, parse_flag);
  shared_ptr<Exp> prog = driver.parse();
  Ans answer = prog->eval();
  if (answer.t == Int) {
    std::cout << answer.i << std::endl;
  } else if (answer.t == Bool) {
    std::cout << answer.b << std::endl;
  } else if (answer.t == Func) {
    std::cout << "A Function" << std::endl;
  } else if (answer.t == Unknown) {
    std::cerr << "Error: Unknown Type" << std::endl;
  }
}

int main(int argc, char *argv[]) {

  // Parsing command line arguments
  int c;

  while (1) {
    static struct option long_options[] =
    {
      /* These options set a flag. */
      {"help", no_argument, &help_flag, 1},
      {"lex", no_argument, &lex_flag, 1},
      {"parse", no_argument, &parse_flag, 1},
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
    cout << "  --help       prints this help message" << endl;
    cout << "  --lex        prints small steps when scanning" << endl;
    cout << "  --parse        prints small steps when parsing" << endl;
    return 0;
  }

  if (optind < argc)
  {
    start(argv[optind]);
  } else {
    start("-");
  }
}
