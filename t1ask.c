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
		if (command == NULL)/*if command fails, eof*/
			break;
		if (*command == 0)/*if user hits ENTER*/
		{
			freearr(command);
			free(command);
			continue;
		}
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
	char *command = NULL, *token, **av;
	int i;

	printf("$ ");
	read = getline(&command, &len, stdin);
	if (strcmp(command, "exit") == 0 || strcmp(command, "env") == 0)
		enx(command);
	if (read == -1)
	{
		if (feof(stdin) != 0)/*if not EOF*/
		{
			free(command);
			return (NULL);
		}
		perror("getline");/*handles error*/
		free(command);
		exit(EXIT_SUCCESS);
	}
	command[strcspn(command, "\n")] = 0;/*remove newline*/
	token = strtok(command, "  \t");
	av = malloc(sizeof(char *) * MAX_ARGS);
	if (av == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (token != NULL)
	{
		if (i == MAX_ARGS)/*if cmd(line)args are more than allo space*/
		{
			perror("Token limit");
			free(av);
			return (NULL);
		}
		av[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	av[i] = NULL;/*null-termintes the array*/
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

	a = tofork(&av);
	if (a == NULL)
	{
		printf("COMMAND NOT FOUND\n");
		return;
	}
	else
	{
		printf("%s\n", av[0]);
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
			stok = strtok(NULL, ":");
		}
		free(cat);
		free(pen);
	}
	return (NULL);
}
/**
  *freearr - frees arr of strptr'
  *@comarr: arr of com with arg
  */
void freearr(char **comarr)
{
	int i;

	for (i = 0; comarr[i] != NULL; i++)
		free(comarr[i]);
}
