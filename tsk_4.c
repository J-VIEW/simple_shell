#include "main.h"

/**
 * Searches for the command in the PATH and returns the full path.
 *
 * @param command The command to search for.
 * @param path The PATH environment variable.
 * @param full_path The buffer to store the full path.
 * @return 1 if the command is found, 0 otherwise.
 */
int find_command_in_path(char *command, char *path, char *full_path) {
    char *token;
    char temp_path[MAX_PATH_SIZE];

    strcpy(temp_path, path);

    token = strtok(temp_path, ":");
    while (token != NULL) {
        snprintf(full_path, MAX_PATH_SIZE, "%s/%s", token, command);

        if (access(full_path, F_OK | X_OK) == 0) {
            return 1;  
        }

        token = strtok(NULL, ":");
    }

    return 0;  
}

/**
 * custom_env - Prints the current environment variables.
 */
void custom_env() {
    extern char **environ;  

    for (int i = 0; environ[i] != NULL; i++) {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
}

/**
 * custom_getline - Read a line of input from standard input.
 *
 * Return: A pointer to the string containing the input line.
 */
char *custom_getline(void)
{
    static char buffer[BUFFER_SIZE];  /* Static buffer for reading input */
    static size_t buffer_index = 0;   /* Index to keep track of buffer position */
    size_t i = 0;                      /* Index for storing characters in the line */
    char c;

    while (1)
    {
        if (buffer_index == 0)
        {
            ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (bytesRead <= 0)
            {
                return NULL;  /* Return NULL on EOF or error */
            }
        }

        c = buffer[buffer_index++];
        if (c == '\n' || c == '\0')
        {
            buffer[buffer_index - 1] = '\0';  /* Replace newline with null terminator */
            buffer_index = 0;                 /* Reset buffer index for the next call */
            break;
        }

        if (i == 0)
        {
            char *line = malloc(BUFFER_SIZE);  /* Initial allocation */
            if (line == NULL)
            {
                return NULL;  /* Return NULL on allocation failure */
            }

            line[i++] = c;
        }
        else if (i % BUFFER_SIZE == 0)
        {
            char *temp = realloc(line, i + BUFFER_SIZE);
            if (temp == NULL)
            {
                free(line);
                return NULL;  /* Return NULL on reallocation failure */
            }

            line = temp;
            line[i++] = c;
        }
        else
        {
            line[i++] = c;
        }
    }

    return line;
}



/**
 * custom_strtok - Breaks a string into a sequence of zero or more tokens.
 *
 * @str: The string to be parsed.
 * @delim: The delimiter characters.
 *
 * Return: A pointer to the next token or NULL if no more tokens are found.
 */
char *custom_strtok(char *str, const char *delim) {
  static char *lastToken = NULL;
  char *tokenStart;

  if (str != NULL) {
    lastToken = str;
  } else if (lastToken == NULL) {
    return NULL;
  }

  /* Skip leading delimiters */
  while (*lastToken != '\0' && strchr(delim, *lastToken) != NULL) {
    lastToken++;
  }

  /* Return NULL if no more tokens */
  if (*lastToken == '\0') {
    return NULL;
  }

  /* Save the start of the token */
  tokenStart = lastToken;

  /* Find the end of the token */
  while (*lastToken != '\0' && strchr(delim, *lastToken) == NULL) {
    lastToken++;
  }

  /* Null-terminate the token */
  if (*lastToken != '\0') {
    *lastToken = '\0';
    lastToken++;
  }

  return tokenStart;
}
