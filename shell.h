#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void simsh(void);
char *get_comm(char **av);
void exec_comm(char *command, char **av);

extern char **environ;

#endif
