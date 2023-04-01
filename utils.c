/* sxpph utils */

#include "mcshell.h"

int ft_strlen(char *s)
{
	int len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	exec_to_pipe(char **argv, char **envp, int *prevpipe, int op)
{
	int i;
	int fd[2];
	int pid;

	i = 0;
	pid = 0;
	if (argv[i] && !strcmp(argv[i], "cd"))
	{
		(void)argv;
		return ;
	}
	if (pipe(fd) == -1)
		error_fatal();
	pid = fork();
	if (pid == -1)
		error_fatal();
	if (pid == 0)
	{
		if (op)
			if (close(fd[0]) == -1) // call close  to fd[0]
				error_fatal();
		if (op == PIPE)
			if (dup2(fd[1], 1) == -1) // call dup2 fot STDOUT
				error_fatal();
		if (op == PIPE)
			if (close(fd[1]) == -1) // call close  to fd[1]
				error_fatal();
		if (dup2(*prevpipe, 0) == -1) // call dup2 fot STDIN
				error_fatal();
  		if (*prevpipe != 0)
			if (close(*prevpipe) == -1) // call close  to prevpipe
				error_fatal();
		if (execve(argv[0], argv, envp) == -1) // call execve
			error_execve(argv[0]);
	}
	else
	{
		if (waitpid(pid, NULL, 0) == -1) // call waitpid
			error_fatal();
		if (op)
			if (close(fd[1]) == -1) // call close to fd[1]
				error_fatal();
		if (*prevpipe != 0)
			if (close(*prevpipe) == -1) // call close to prevpipe
				error_fatal();
		*prevpipe = fd[0];
	}
}


void	on_time_execution(char **argv, char **envp)
{
	int	i;
	int	op;
	int	start;
	int prevpipe[1];

	i = 0;
	op = 0;
	start = 1;
	*prevpipe = 0;

	while (argv[i])
	{
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";")) // start build cmd
			i++;
		if (argv[i] && !strcmp(argv[i], "|"))
			op = PIPE;
		else if (argv[i] && !strcmp(argv[i], ";"))
			op = S_COLLON;
		else
			op = 0;
		while (argv[i] && (!strcmp(argv[i], "|") || !strcmp(argv[i], ";")))  // end build cmd
			argv[i++] = NULL;
		exec_to_pipe(&argv[start], envp, prevpipe, op);// n lembro o nome q botei nessa;
		start = i;
	}
}

