#include "minishell.h"

char	**exec_command_test(char *command, char **argv, char **envp)
{
	char	*path;
	int		status;
	pid_t	pid;
	
	path = get_path(envp, command);
	pid = fork();
	if (pid == 0)
            execve(path, argv, envp);
	else if (pid < 0)
	{
		return (NULL);
	} 
	else
	{
		wait(&status);
		return(envp);
	}
	return (envp);
}



int main(int argc, char **argv, char **env)
{
     char *input;
     if (argc != 1)
          return (0);
     (void) argv;
     char **envp;
     
     envp = copy_tab(env);

   while (1)
   {

          t_command *list_of_command;

          list_of_command = NULL;
          input = readline("Minishell> ");
          add_history(input);
          parse_input(input, &list_of_command);
          managing_pipe(list_of_command, &envp);
         // char *cmd =  copy_string(list_of_command->command->string, envp);
         // char **arg = list_to_tab(list_of_command->command, envp);
          //exec_command_test(cmd, arg, envp);
         // exec_command(cmd, arg, &envp);
          //print_tab(envp);
          clean_list_command(&list_of_command);
   }
       
}

