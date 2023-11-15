#include "main.h"

/**
 * custom_setenv - Set or update an environment variable.
 * @tokens: An array of strings containing the command and its arguments.
 */
void custom_setenv(char **tokens) {
    if (tokens[1] == NULL || tokens[2] == NULL) {
        write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", strlen("Usage: setenv VARIABLE VALUE\n"));
        return;
    }

    if (setenv(tokens[1], tokens[2], 1) != 0) {
        perror("shell");
    }
}

/**
 * custom_unsetenv - Unset an environment variable.
 * @tokens: An array of strings containing the command and its arguments.
 */
void custom_unsetenv(char **tokens) {
    if (tokens[1] == NULL) {
        write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", strlen("Usage: unsetenv VARIABLE\n"));
        return;
    }

    if (unsetenv(tokens[1]) != 0) {
        perror("shell");
    }
}

/**
 * Changes the current directory of the process.
 *
 * @param tokens The array of strings representing the command and its arguments.
 */
void change_directory(char **tokens) {
    const char *home_dir = getenv("HOME");
    const char *prev_dir = getenv("PWD");

    if (tokens[1] == NULL) {
        /* No argument given, change to home directory */
        if (home_dir != NULL) {
            if (chdir(home_dir) != 0) {
                perror("shell");
            }
        } else {
            write(STDERR_FILENO, "cd: No home directory\n", strlen("cd: No home directory\n"));
        }
    } else if (strcmp(tokens[1], "-") == 0) {
        /* Change to the previous directory */
        if (prev_dir != NULL) {
            if (chdir(prev_dir) != 0) {
                perror("shell");
            }
        } else {
            write(STDERR_FILENO, "cd: No previous directory\n", strlen("cd: No previous directory\n"));
        }
    } else {
        /* Change to the specified directory */
        if (chdir(tokens[1]) != 0) {
            perror("shell");
        }
    }

    /* Update the PWD environment variable */
    char current_dir[1024];
    if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
        setenv("PWD", current_dir, 1);
    } else {
        perror("shell");
    }
}
