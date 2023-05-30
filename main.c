#include "cmd.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
  if (argc == 1) {
    goto_dest();
    exit(EXIT_SUCCESS);
  }

  char cmd[strlen(argv[1]) + 1];
  strcpy(cmd, argv[1]);

  if (strcmp(cmd, "new") == 0) {
    new_dest();
  } else if (strcmp(cmd, "rm") == 0) {
    printf("rm");
  } else if (strcmp(cmd, "ls") == 0) {
    list_dest();
  } else if (strcmp(cmd, "help")) {
    printf("coming soon...\n");
  }

  return 0;
}
