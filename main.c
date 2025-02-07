#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define ARR_LEN(arr) sizeof(arr)/sizeof(arr[0])

const char ALL_COMMAND[20][10] = {"bola", "tero_tauko", "wtf"};

#define MAX_PATH_LENGTH 1024

char *find_in_path(const char *command) {
  if (command[0] == '/') {  // ✅ Check if command is absolute path
    if (access(command, X_OK) == 0) {
      return strdup(command);
    }
    return NULL;
  }

  // path fetch
  char *path_env = getenv("PATH");
  if(path_env == NULL) {
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
    if (access(path, X_OK) == 0) { // X_OK check for executable permission bit
      free(path_copy);
      return path;
    }
    fetched_path = strtok(NULL, ":");
  }
  free(path_copy);
  return NULL;
}

void if_type(char* arg) {
  for(size_t i = 0; i < ARR_LEN(ALL_COMMAND); i++) {
    if(strcmp(arg, ALL_COMMAND[i]) == 0) {
      printf("%s is a shell builtin\n", arg);
      return;
    }
  }
  char *fetched_path = find_in_path(arg);
  if (fetched_path) {
    printf("%s is %s\n", arg, fetched_path);
  } else {
    printf("%s: not found\n", arg);
  }
}
int main() {
  char input[100];
  char *args;
  char command[100];
  
  setbuf(stdout, NULL); // Flush after every printf

  while(1) {                                           // REPL: READ-EVAL-PRINT LOOP
    printf("$ ");
    if (fgets(input, 100, stdin) == NULL) {
      break;
    }
    size_t input_length = strlen(input);

    // removing \n
    if (input[input_length - 1] == '\n') {
      input[input_length - 1] = '\0';
    }

    if(strcmp(input, "tero_tauko") == 0) {
      break;
    }

    // token generator
    char *token = strtok(input, " ");
    if(token != NULL) {
      strncpy(command, token, sizeof(command)-1);
      command[sizeof(command) - 1] = '\0';
      args = strtok(NULL, "");
    } else {
      continue;
    }
    if(strcmp(command, "bola") == 0) {
      printf("%s\n", args);
    }
    else if(strcmp(command, "wtf") == 0) {
      if_type(args);
    }
    else {
      printf("%s: command not found\n", command);
    }
  }
  return 0;
}
