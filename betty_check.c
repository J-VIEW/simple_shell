#include "main.h"
/**
* print_info - Prints information to the standard output
*/
void print_info(void)
{

char *str = "Let us make our own shell\n";

size_t str_len = strlen(str);
/* Allocate memory for a copy of the string */
char *n = (char *)malloc(str_len + 1);

if (n == NULL)
exit(EXIT_FAILURE);
/* copy characters source string to the allocated mem */
for (size_t i = 0; i <= str_len; i++)
{
n[i] = str[i];
}

write(1, n, str_len);

free(n);
}
