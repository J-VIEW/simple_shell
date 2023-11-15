#include "main.h"

/**
 * Prints all defined aliases.
 */
void print_aliases(void)
{
    for (int i = 0; i < num_aliases; ++i) {
        write(STDOUT_FILENO, aliases[i].name, strlen(aliases[i].name));
        write(STDOUT_FILENO, "=", 1);
        write(STDOUT_FILENO, aliases[i].value, strlen(aliases[i].value));
        write(STDOUT_FILENO, "\n", 1);
    }
}

/**
 * Finds an alias by name.
 *
 * @param name Alias name to find.
 * @return Pointer to the Alias structure if found, NULL otherwise.
 */
Alias *find_alias(char *name)
{
    for (int i = 0; i < num_aliases; ++i) {
        if (strcmp(aliases[i].name, name) == 0) {
            return &aliases[i];
        }
    }
    return NULL;
}

/**
 * Defines or updates an alias.
 *
 * @param name Alias name.
 * @param value Alias value.
 */
void define_alias(char *name, char *value)
{
    Alias *existing_alias = find_alias(name);

    if (existing_alias != NULL) {
      
        free(existing_alias->value);
        existing_alias->value = strdup(value);
    } else {
        
        if (num_aliases < MAX_ALIASES) {
            aliases[num_aliases].name = strdup(name);
            aliases[num_aliases].value = strdup(value);
            ++num_aliases;
        } else {
            write(STDOUT_FILENO, "Alias limit reached\n", 20);
        }
    }
}

