// DONE: Check error when calling "ls -la --color=auto" or "cal -n 2" -- Changed `execv' with `execvp'
// TODO: Test with waitpid()

#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <ctype.h>

#include "string.h"

char *buffer;
char *PS = "(zebes@arata)^ ";

int main() {
    	buffer = malloc(sizeof(char) * BUFFER_SIZE);

        if (buffer == NULL) {
		perror("Unable to allocate buffer.");
		exit(EXIT_FAILURE);
        }

	size_t buffer_size = BUFFER_SIZE;

	size_t length;

	pid_t pid = 0;
	int status;

	char **args;

	for (;;) {
		printf("%s", PS);
		getline(&buffer, &buffer_size, stdin);

		// Remove newline at the end
		buffer[strlen(buffer) - 1] = '\0';

		if (strcmp(buffer, "exit") == 0) {
			break;
		}

		length = split_whitespace(buffer, &args);

		if (strcmp(args[0], "cd") == 0) {
			chdir(args[1]);
			continue;
		}

		pid = fork();

		// PID == 0 -- Child process
		// PID >  0 -- Parent process
		if (pid == 0) {
			execvp(args[0], args);
			// If exec fails, the following two lines will be executed
			printf("%s: %s: command not found\n", "arata", args[0]);
			exit(EXIT_FAILURE);
		} else if (pid > 0) {
			wait(&status);
		} else {
			perror("In fork(): ");
		}

		for (int i = 0; i < length; i++) {
			free(args[i]);
		}

		free(args);
	}

	free(buffer);

	return EXIT_SUCCESS;
}
