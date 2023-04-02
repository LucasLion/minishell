#include "../include/minishell.h"

/*void	sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}*/

int	main(int argc, char **argv, char **env)
{
	extern int	rl_catch_signals;
	(void) argc;
    char    *input;
    int	    pid;
    rl_catch_signals = 1;
	while (1)
	{
		signals();
		input = readline("Minishell> ");
	    add_history(input);
        pid = fork();
        if (pid == 0)
        {
            signal(SIGQUIT, SIG_DFL);
		    if (execve(input, argv, env) == -1)
			    exit(127);
            signal(SIGQUIT, SIG_IGN);
	        exit(0);
        }
        wait(&pid);
	}	
	
}

