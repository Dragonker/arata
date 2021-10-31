#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

#include "string.h"

size_t split_whitespace(char *str, char ***array) {
	size_t length = 1;

	for (int i = 0, ch = str[i]; ch != '\0'; i++, ch = str[i]) 
		if (isspace(ch)) length++;

	char **result = malloc(sizeof(char*) * (length + 1));

	if (result == NULL) {
		perror("Could not allocate memory.");
		exit(EXIT_FAILURE);
	}

	char *tokens = strtok(str, " ");

	for (int i = 0; i < length; i++) {
		result[i] = malloc(sizeof(char) * strlen(tokens));
		strcpy(result[i], tokens);	

		tokens = strtok(NULL, " ");
	}

	result[length] = NULL;

	*array = result;

	return length;
}
