/* sxpph errors*/

#include "mcshell.h"

void	error_fatal(void)
{
	char *msg;

	msg = "error fatal\n";
	write(2, msg, ft_strlen(msg));
    exit(0);
}

void	error_execve(char *path)
{
	char *msg;

	msg = "error: cannot execute ";
	write(2, msg, ft_strlen(msg));
	write(2, path, ft_strlen(path));
	write(2, "\n", 1);
    //exit ?
}

void	error_cd_path(char *path)
{
	char *msg;

	msg = "error: cd: cannot change directory to ";
	write(2, msg, ft_strlen(msg));
	write(2, path, ft_strlen(path));
	write(2, "\n", 1);
}

void	error_cd_arguments(void)
{
	char *msg;

	msg = "error: cd: bad arguments\n";
	write(2, msg, ft_strlen(msg));
}