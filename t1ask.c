#include "shell.h"

/**
  *main - a simple shel in Unix
  *Return: int (0 on success)
  */
int main(void)
{
	char *command, *av[2];

	while (1)
	{
		command = get_comm(av);
		if (command == NULL || strlen(command) == 0)
			continue;
		exec_comm(command, av);
	}
	return (0);
}
/**
  *get_comm - processes passed command
  *@av: passed ptr ptr
  *Return: char pointer
  */
char *get_comm(char **av)
{
	size_t len = 0;
	ssize_t read;
	char *command = NULL, *token;
	int i;

	printf("$ ");
	read = getline(&command, &len, stdin);
	if (read == -1)
	{
		if (feof(stdin) != 0)/*handles error*/
			return (NULL);
		perror("getline");
		return (NULL);
	}
	command[strcspn(command, "\n")] = 0;/*remove newline*/
	token = strtok(command, " ");
	i = 0;
	while (token != NULL)
	{
		av[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	av[i] = NULL;/*null-termintes the array*/
	return (command);
}
/**
  *exec_comm - forks and executes passed command
  *@command: pointer to passed command gotten
  *@av: passed ptr ptr
  *Return: void
  */
void exec_comm(char *command, char **av)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return;
	}
	if (child == 0)
	{
		if ((execve(command, av, environ)) == -1)
			perror("Execve");
	}
	else
	{
		if ((wait(&status)) == -1)
			perror("wait");
	}
	free(command);
}
