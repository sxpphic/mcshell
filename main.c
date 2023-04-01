/* sxpph mcshell*/

#include "mcshell.h"

int main (int argc, char **argv, char **envp)
{
	if (argc == 1)
		return (0);
	on_time_execution(argv, envp);
	return (0);
}