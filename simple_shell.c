#include "main.h"

/**
 * Executes a command.
 *
 * @param command Command to execute.
 */
void process_command(char *command) {
 
  char *expanded_command = expand_variables(command);

 
  char *tokens[20]; 
  int num_tokens = 0;
  char *token = strtok(expanded_command, " \n");
  while (token != NULL) {
    tokens[num_tokens++] = token;
    token = strtok(NULL, " \n");
  }
  tokens[num_tokens] = NULL; 

  
  pid_t child_pid = fork();
  if (child_pid == 0) {
    
    if (execvp(tokens[0], tokens) == -1) {
      perror("execvp");
      exit(EXIT_FAILURE);
    }
  } else if (child_pid > 0) {
    
    int status;
    waitpid(child_pid, &status, 0);

    free(expanded_command);
  } else {
    
    perror("fork");
  }
}

int main(void) {
  char input[100]; 

  while (1) {
    
    write(STDOUT_FILENO, "myshell> ", 9);
    fgets(input, sizeof(input), stdin);

   
    if (strstr(input, "alias") != NULL) {
      
      char *name = strtok(input, "= ");
      char *value = strtok(NULL, "= ");

      if (value == NULL) {
       
        print_aliases();
      } else {
       
        define_alias(name, value);
      }
    } else if (strstr(input, "export") != NULL) {
      
      char *name = strtok(input, "= ");
      char *value = strtok(NULL, "= ");

      if (value == NULL) {
        
        print_variables();
      } else {
       
        define_variable(name, value);
      }
    } else if (strstr(input, "exit") != NULL) {
      
      exit(EXIT_SUCCESS);
    } else {
      
      process_command(input);
    }
  }

  return 0;
}
