// Alberto Maiocco
// CS4760 Project 2
// 10/6/2020
// master.c

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

#define SHMSZ 128
//key_t startSharedMem();

int main(int argc, char *argv[]) {

  int maxProc = 4;
  int maxKids = 2;
  int maxSecs = 100;
  char fileNameBuffer[128];

  if (argc <= 1) {
    perror("Master: Not enough arguments. Exiting.\n");
    exit(1);
  }

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
          exit(0);
        break;

      case 'n':
        maxProc = atoi(optarg);
        if (maxProc <= 0) {
          perror("master: maxProc <= 0. Aborting.");
          exit(1);
        }
        if (maxProc > 20) maxProc = 20;
        break;

      case 's':
        maxKids = atoi(optarg);
        if (maxKids <= 0) {
          perror("master: maxKids <= 0. Aborting.");
          exit(1);
        }
        break;

      case 't':
        maxSecs = atoi(optarg);
        if (maxSecs <= 0) {
          perror("master: maxSecs <= 0. Aborting.");
          exit(1);
        }
        break;

      case '?':
        if(isprint(optopt)) {
          fprintf(stderr, "Uknown option `-%c`.\n", optopt);
          perror("Error: Unknown option entered.");
          return 1;
        }
        else {
          fprintf (stderr, "Unkown option character `\\x%x`.\n", optopt);
          perror("Error: Unknown option character read.");
          return 1;
        }
        return 1;

      default:
        abort();

    }
  }

  int index;
  strcpy(fileNameBuffer, argv[optind]);
  for (index = optind+1; index < argc; index++) {
    strcat(fileNameBuffer, argv[index]);
  }

  printf("Max # of Processes: %d\n", maxProc);
  printf("Max # of Children: %d\n", maxKids);
  printf("Max Time Before Termination: %d\n", maxSecs);
  printf("Opening input file %s\n", fileNameBuffer);

  //File IO

  FILE *infile = fopen(fileNameBuffer, "r");
  if (infile == NULL) {
    perror("master: Error opening file. Exiting.\n");
    exit(1);
  }

  char *outfileName = "palindromeResults.txt";
  FILE *outfile = fopen(outfileName, "a+");
  if (outfile == NULL) {
    perror("master: Error opening file. Exiting.\n");
    exit(1);
  }

  //ok, the task here is to set up the shared memory and put the array in it
  //read infile into string to be put into shared memory
  char *data = 0;
  long length;
  if (infile) {
  fseek (infile, 0, SEEK_END);
  length = ftell(infile);
  fseek (infile, 0, SEEK_SET);
  data = malloc(length+1);
  if (data) {
    fread (data, 1, length, infile);
  }
  fclose (infile);
  data[length] = '\0';
  }
  int i;
  for(i=0; data[i]!='\0'; i++) {
    if(data[i]=='\n' || data[i]=='\r' ) {
      data[i] = '$';
    } else continue;
  }
  printf("%s\n", data);

  //now shared memory for reals




  return 0;
}
