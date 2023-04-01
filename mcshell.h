/* sxpph header */

#ifndef MCSHELL_H
# define MCSHELL_H

# define PIPE 1
# define S_COLLON 2

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

int     ft_strlen(char *s);
void	error_fatal(void);
void	error_execve(char *path);
void	error_cd_path(char *path);
void	error_cd_arguments(void);
void	on_time_execution(char **argv, char **envp);
void	exec_to_pipe(char **argv, char **envp, int *prevpipe, int op);



#endif