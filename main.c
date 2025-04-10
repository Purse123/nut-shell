#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARR_LEN(arr) sizeof(arr) / sizeof(arr[0])

const char ALL_COMMAND[20][10] = {"bola", "tero_tauko", "wtf"};

#define MAX_PATH_LENGTH 1024

char *find_in_path(const char *command) {
  if (command[0] == '/') {
    if (access(command, X_OK) == 0) {
      return strdup(command);
    }
    return NULL;
  }

  char *path_env = getenv("PATH");
  if (path_env == NULL) {
    printf("Path variable no set\n");
    return NULL;
  }

  char *path_copy = strdup(path_env);
  char *fetched_path = strtok(path_copy, ":");
  static char path[MAX_PATH_LENGTH];

  while (fetched_path != NULL) {
    snprintf(path, sizeof(path), "%s/%s", fetched_path, command);
    /* @access() = 0 if file assesible*/
    /* @access() = -1 if file isn't assesible*/
    if (access(path, X_OK) == 0) {
      free(path_copy);
      return path;
    }
    fetched_path = strtok(NULL, ":");
  }
  free(path_copy);
  return NULL;
}

void if_type(char *arg) {
  if (!arg || arg[0] == '\0') {
    printf("type: missing argument\n");
    return;
  }

  // Extract the first argument
  // otherwise, not work for eg: type ls -l
  char arg_copy[MAX_PATH_LENGTH];
  strncpy(arg_copy, arg, MAX_PATH_LENGTH - 1);
  arg_copy[MAX_PATH_LENGTH - 1] = '\0';

  // key-comp: handle multiple space or tab
  char *first_arg = strtok(arg_copy, " \t");

  for (size_t i = 0; i < ARR_LEN(ALL_COMMAND); i++) {
    if (strcmp(arg, ALL_COMMAND[i]) == 0) {
      printf("%s is a shell builtin\n", arg);
      return;
    }
  }

  char *fetched_path = find_in_path(arg);
  if (fetched_path) {
    printf("%s is %s\n", arg, fetched_path); // idk might remove later
  } else {
    printf("%s: command not found\n", arg);
  }
}

int main() {
  char input[100];
  char *args;
  char command[100];

  // Flush buffer
  setbuf(stdout, NULL);

  while (1) {
    printf("$ ");
    if (fgets(input, 100, stdin) == NULL) {
      break;
    }
    size_t input_length = strlen(input);

    if (input[input_length - 1] == '\n') {
      input[input_length - 1] = '\0';
    }

    if (strcmp(input, "tero_tauko") == 0) {
      break;
    }

    char *token = strtok(input, " ");
    if (token != NULL) {
      strncpy(command, token, sizeof(command) - 1);
      command[sizeof(command) - 1] = '\0';
      args = strtok(NULL, "");
    } else {
      continue;
    }
    if (strcmp(command, "bola") == 0) {
      printf("%s\n", args);
    } else if (strcmp(command, "wtf") == 0) {
      if_type(args);
    } else {
      printf("%s: command not found\n", command);
    }
  }
  return 0;
}
