#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 100

void simsh(void);
char **get_comm(void);
void exec_comm(char **av);
char *tofork(char ***av);
void freearr(char **comarr);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
<<<<<<< HEAD

=======
char **tokspace(char *token, char **av);
>>>>>>> d057124864be4c70b25b766c4af38bde2d422fe8
extern char **environ;
void enx(char **av);

#endif
