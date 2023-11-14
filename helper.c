#include "shell.h"

/**
  *enx - exits when user types, prints env var
  *@av: pointer to gotten line
  */
void enx(char **av)
{
	int status;
	char **env;

	if (strcmp(av[0], "exit") == 0)
	{
		if (av[1] != NULL)
		{
			status = atoi(av[1]);
			exit(status);
		}
		exit(EXIT_SUCCESS);
	}
	if (strcmp(av[0], "env") == 0)
	{
		for (env = environ; *env; ++env)
			printf("%s\n", *env);
	}
}
/**
  *tokspace - assigns each token a space
  *@av: ptr to empty space for token
  *@token: token from splits
  *Return:ptr to token ptr
  */
char **tokspace(char *token, char **av)
{
	int i;

	i = 0;
	while (token != NULL)
	{
		if (i == MAX_ARGS)/*if cmd(line)args are more than allo space*/
		{
			perror("Token limit");
			free(av);
			return (NULL);
		}
		av[i] = strdup(token);
		if (av[i] == NULL)
		{
			free(av);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " ");
	}
	av[i] = NULL;/*null-termintes the array*/
	return (av);
}
