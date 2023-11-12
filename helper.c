#include "shell.h"

/**
  *enx - exits when user types, prints env var
  *@command: pointer to gotten line
  */
void enx(char *command)
{
	char **env;

	if (strcmp(command, "exit") == 0)
		exit(EXIT_SUCCESS);
	if (strcmp(command, "env") == 0)
	{
		for (env = environ; *env; ++env)
			printf("%s\n", *env);
	}
	free(command);
}
