#include "cmd.h"
#include "file.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ALIAS 30
#define MAX_DEST 200
#define MAX_LINE MAX_ALIAS + MAX_DEST
#define MAX_COMMAND MAX_DEST + 20
#define READ_FILE "r"
#define APPEND_FILE "a"

static int read_line(char *str, int limit);
static void check_os(char *command, char *dest);

void goto_dest(void) {
  char line[MAX_LINE + 1], alias[MAX_ALIAS], dest[MAX_DEST],
      command[MAX_COMMAND + 1];
  FILE *fp = open_file(READ_FILE);

  printf("Alias: ");
  read_line(alias, MAX_ALIAS);

  while ((fgets(line, sizeof(line), fp)) != NULL) {
    char current_alias[MAX_ALIAS], current_dest[MAX_DEST],
        command[MAX_DEST + 20];
    current_alias[0] = '\0', current_dest[0] = '\0';
    bool checking_alias = true;
    int i, j;

    for (i = 0, j = 0; i < strlen(line); i++) {
      if (line[i] == '=') {
        checking_alias = false;
        current_alias[i] = '\0';
        continue;
      }

      if (checking_alias) {
        current_alias[i] = line[i];
      } else {
        current_dest[j++] = line[i];
      }
    }

    current_dest[j] = '\0';

    if (strcmp(alias, current_alias) == 0) {
      strcpy(dest, current_dest);
      break;
    }
  }

  if (strlen(dest) != 0) {
    check_os(command, dest);
    system(command);
    fclose(fp);
    exit(EXIT_SUCCESS);
  } else {
    fprintf(stderr, "Alias %s not found\n", alias);
    fclose(fp);
    exit(EXIT_FAILURE);
  }
}

void new_dest(void) {
  char alias[MAX_ALIAS + 1];
  char dest[MAX_DEST + 1];

  printf("Title of the alias: ");
  read_line(alias, MAX_ALIAS);
  printf("Destination of the alias: ");
  read_line(dest, MAX_DEST);

  FILE *fp = open_file(APPEND_FILE);
  fprintf(fp, "%s=%s\n", alias, dest);
  fclose(fp);
}

void list_dest(void) {
  char line[MAX_LINE + 1];
  FILE *fp = open_file(READ_FILE);

  while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
  }
  fclose(fp);
}

void rm_dest(void);

static int read_line(char *str, int limit) {
  int ch, i = 0;
  while ((ch = getchar()) != '\n') {
    if (i == limit) {
      fprintf(stderr, "Input string too long\n");
      exit(EXIT_FAILURE);
    }

    if (ch == '=') {
      fprintf(stderr, "Can't include '='\n");
      exit(EXIT_FAILURE);
    }
    i++;
    *str++ = ch;
  }

  *str = '\0';
  return i;
}

static void check_os(char *command, char *dest) {
#ifdef __APPLE__
  sprintf(command,
          "osascript -e 'tell application \"Terminal\" to do script \"cd %s\"'",
          dest);
#elif __linux__
  sprintf(command, "gnome-terminal --working-directory=\"%s\"", directory);
#elif _WIN32
  sprintf(command, "start cmd.exe /K \"cd /d %s\"", directory);
#else
  printf("Opening a new terminal window is not supported on this operating "
         "system.\n");
#endif
}
