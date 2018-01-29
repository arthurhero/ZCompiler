#include <iostream>
#include <getopt.h>

using namespace std;

static int help_flag = 0;
static int length_flag = 0;

int main(int argc, char** argv) {

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

    while (optind < argc) {
      cout << argv[optind++] << endl;
    }
  }

  return 0;

}
