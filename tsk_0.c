#include "main.h"

/**
 * Finds a variable by name.
 *
 * @param name Variable name to find.
 * @return Pointer to the Variable structure if found, NULL otherwise.
 */
Variable *find_variable(char *name)
{
    for (int i = 0; i < num_variables; ++i) {
        if (strcmp(variables[i].name, name) == 0) {
            return &variables[i];
        }
    }
    return NULL;
}

/**
 * Defines or updates a variable.
 *
 * @param name Variable name.
 * @param value Variable value.
 */
void define_variable(char *name, char *value)
{
    Variable *existing_variable = find_variable(name);

    if (existing_variable != NULL) {
        // Update existing variable
        free(existing_variable->value);
        existing_variable->value = strdup(value);
    } else {
        // Add a new variable
        if (num_variables < sizeof(variables) / sizeof(variables[0])) {
            variables[num_variables].name = strdup(name);
            variables[num_variables].value = strdup(value);
            ++num_variables;
        } else {
            printf("Variable limit reached\n");
        }
    }
}

/**
 * Expands variables in a string.
 *
 * @param input Input string.
 * @return Expanded string with variables replaced.
 */
char *expand_variables(char *input)
{
    char *result = strdup(input);
    char *token = strtok(result, " \n");

    while (token != NULL) {
        if (token[0] == '$') {
            // Handle variable replacement
            Variable *variable = find_variable(token + 1);
            if (variable != NULL) {
                token = strdup(variable->value);
            }
        }

        token = strtok(NULL, " \n");
    }

    return result;
}

