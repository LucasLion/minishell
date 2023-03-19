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
        char **tab_argv;
       char *command;
     
        list_of_command = NULL;
        input = readline("Minishell> ");
        add_history(input);
        parse_input(input, &list_of_command);
        //printf("process principal : %d\n", getpid());
        managing_pipes(list_of_command, envp);
        //print_list_command_from_head(list_of_command);

        tab_argv = list_to_tab(list_of_command->command, envp);
        command = copy_string(list_of_command->command->string, envp);
        //printf("LA commande est : %s\nET voici la liste des arguments : \n", command);
        //print_tab(tab_argv);
        //exec_command(command, tab_argv, envp);
        
        clean_list_command(&list_of_command);

   }
       
}
