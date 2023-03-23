#include "minishell.h"

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
          managing_pipe(list_of_command, envp);
          //char *cmd =  copy_string(list_of_command->command->string, envp);
          //char **arg = list_to_tab(list_of_command->command, envp);
          //exec_command(cmd, arg, &envp);
          print_tab(envp);
          clean_list_command(&list_of_command);
     
   }
       
}

