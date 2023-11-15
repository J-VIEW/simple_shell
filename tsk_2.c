#include "main.h"

/**
 * Exits the shell.
 */
void custom_exit() {
    write(STDOUT_FILENO, "Exiting shell...\n", 18);
    exit(0);
}

/**
 * custom_exit - Exits the shell with a specified status.
 *
 * @status: The exit status.
 *
 * Return: This function does not return.
 */
void custom_exit(char **tokens) {
  int status;

  if (tokens[1] == NULL) {
    /* No argument given, use the default status of 0 */
    status = 0;
  } else {
    /* Convert the argument to an integer */
    status = atoi(tokens[1]);
  }

  exit(status);
}

