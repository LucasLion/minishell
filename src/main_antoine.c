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
        clean_list_command(&list_of_command);

   }
       
}

