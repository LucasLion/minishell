#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
     char *input;
     (void) argc;
     (void) argv;
    // (void) envp;

   while (1)
   {
        t_command *list_of_command;
        char **tab_argv;
     
        list_of_command = NULL;
        input = readline("Minishell> ");
        add_history(input);
        parse_input(input, &list_of_command);
        //print_list_command_from_head(list_of_command);
        tab_argv = list_to_tab_argv(list_of_command->command, envp);
        print_tab(tab_argv);
        
       // clean_list_command(&list_of_command);

   }
       
}
