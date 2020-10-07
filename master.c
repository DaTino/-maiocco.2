// Alberto Maiocco
// CS4760 Project 2
// 10/6/2020
// master.c

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char **argv) {

  int maxProc;
  int maxKids;
  int maxSecs;
  char infile[128];

  //the wonderful getopt wurld.
  int optionIndex;
  while ((optionIndex = getopt(argc, argv, "hn:s:t:")) != -1) {
    switch (optionIndex) {
      case 'h':
          printf("Welcome to the Valid Argument Usage Dimension\n");
          printf("- = - = - \n");
          printf("-h       : Display correct command line argument Usage\n");
          printf("-n <int> : Indicate the maximum total of child processes master will create. (Default 4)\n");
          printf("-s <int> : Indicate the number of children allowed to exist in the system at the same time. (Default 2)\n");
          printf("-t <int> : The time in seconds after which the process will terminate, even if it has not finished. (Default 100)\n");
          printf("The last argument is an input file containing strings to be tested.\n");
        break;

      case 'n':
        if (optarg == NULL) maxProc = 4;
        else maxProc = atoi(optarg);
        if (maxProc <= 0) {
          perror("master: maxProc <= 0. Aborting.");
          exit(-1);
        }
        if (maxProc > 20) maxProc = 20;
        break;

      case 's':
        if (optarg == NULL) maxKids = 2;
        else maxKids = atoi(optarg);
        if (maxKids <= 0) {
          perror("master: maxKids <= 0. Aborting.");
          exit(-1);
        }
        break;

      case 't':
        if (optarg == NULL) maxSecs = 100;
        else maxSecs = atoi(optarg);
        if (maxSecs <= 0) {
          perror("master: maxSecs <= 0. Aborting.");
          exit(-1);
        }
        break;

      case '?':
        if (optind == argc) {
          strcpy(infile, argv[optind-1]);
        }
        if(isprint(optopt)) {
          fprintf(stderr, "Uknown option `-%c`.\n", optopt);
          perror("Error: Unknown option entered.");
          return -1;
        }
        else {
          fprintf (stderr, "Unkown option character `\\x%x`.\n", optopt);
          perror("Error: Unknown option character read.");
          return -1;
        }

      default:
        abort();

    }
  }
  printf("Max # of Processes: %d\n", maxProc);
  printf("Max # of Children: %d\n", maxKids);
  printf("Max Time Before Termination: %d\n s", maxKids);
  printf("%s\n", infile);

  return 0;
}
