#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_PATH_SIZE 1024
#define BUFFER_SIZE 1024

#define MAX_ALIASES 10

/**
 * Structure to represent an alias.
 */
typedef struct {
  char *name;  /**< Alias name */
  char *value; /**< Alias value */
} Alias;

Alias aliases[MAX_ALIASES];
int num_aliases = 0;

/**
 * Structure to represent a variable.
 */
typedef struct {
  char *name;  /**< Variable name */
  char *value; /**< Variable value */
} Variable;

Variable variables[10]; // Assuming a maximum of 10 variables
int num_variables = 0;

void execute_command(char *command, char **arguments, char **envp);
int find_command_in_path(char *command, char *path, char *full_path);
int main(int argc, char *argv[], char *envp[]);

void custom_env();
void custom_exit();
char *custom_getline(void);

char *custom_strtok(char *str, const char *delim);
void custom_unsetenv(char **tokens);
void custom_setenv(char **tokens);

void change_directory(char **tokens);
void print_aliases(void);
Alias *find_alias(char *name);
void define_alias(char *name, char *value);



#endif

