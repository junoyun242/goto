#include "file.h"
#include <stdio.h>
#include <stdlib.h>

FILE *open_file(char *mode) {
  char *filename = "./goto.config";
  FILE *fp = fopen(filename, mode);
  if (fp == NULL) {
    fp = fopen(filename, "a");
    if (fp == NULL) {
      fprintf(stderr, "Can't open the config file\n");
      exit(EXIT_FAILURE);
    }

    fp = fopen(filename, mode);
  }

  return fp;
}
