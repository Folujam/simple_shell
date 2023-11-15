#include "shell.h"

/**
  *main - a simple shel in Unix
  *Return: int (0 on success)
  */
int main(void)
{
	char **command;

	while (1)
	{
		command = get_comm();
		if (command == NULL)/*if command fails, eof, hits ENTER*/
			continue;
		exec_comm(command);
		free(command);
	}
	return (0);
}
/**
  *get_comm - processes passed command
  *Return: char pointer
  */
char **get_comm(void)
{
	size_t len = 0;
	ssize_t read;
	char *command = NULL, *token, **av, **temp;

	printf("$ ");
	read = getline(&command, &len, stdin);
	if (read == -1)
	{
		if (feof(stdin) != 0)/*if not EOF*/
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		perror("getline");/*handles error*/
		free(command);
		return (NULL);
	}
	command[strcspn(command, "\n")] = 0;/*remove newline*/
	if (command[0] == '\0')
	{
		free(command);
		return (NULL);
	}
	token = strtok(command, "  \t");
	av = malloc(sizeof(char *) * MAX_ARGS);
	if (av == NULL)
		exit(EXIT_FAILURE);
	temp = tokspace(token, av);
	if (temp == NULL)
		return (NULL);
	av = temp;
	if (strcmp(av[0], "exit") == 0 || strcmp(av[0], "env") == 0)
		enx(av);
	return (av);
}
/**
  *exec_comm - forks and executes passed command
  *@av: pointerptr to passed command gotten
  *Return: void
  */
void exec_comm(char **av)
{
	pid_t child;
	int status;
	char *a;

	if (av[0][0] == '/')
		a = strdup(av[0]);
	else
		a = tofork(&av);
	if (a == NULL)
	{
		printf("COMMAND NOT FOUND\n");
		return;
	}
	child = fork();
	if (child == -1)
	{
		perror("fork");
		return;
	}
	if (child == 0)
	{
		if ((execve(a, av, environ)) == -1)
		{
			free(a);
			perror("Execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if ((wait(&status)) == -1)
		{
			free(a);
			perror("wait");
			return;
		}
		free(a);
	}
}
/**
  *tofork - checks if command is in the path
  *@av: ptr ptr
  *Return: char ptr if found, null if not
  */
char *tofork(char ***av)
{
	char *pen, *stok, *cat;

	pen = strdup(getenv("PATH"));/*makes a copy*/
	if (pen != NULL)
	{
		stok = strtok(pen, ":");/*tokens by :*/
		cat = NULL;/*resets cat instead of free*/
		while (stok != NULL)
		{
			cat = malloc(strlen(stok) + strlen(*av[0]) + 2);
			if (cat == NULL)
				return (NULL);
			strcpy(cat, stok);
			strcat(cat, "/");
			strcat(cat, *av[0]);
			if (access(cat, F_OK) == 0)/*checks access*/
				return (cat);
			free(cat);
			stok = strtok(NULL, ":");
		}
		free(pen);
	}
	return (NULL);
}
