#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
     char *input;
     (void) argc;
     (void) argv;
     (void) envp;

   while (1)
   {
        t_command *list_of_command;
     
        list_of_command = NULL;
        input = readline("Minishell> ");
        add_history(input);
        parse_input(input, &list_of_command);
        print_list_command_from_head(list_of_command);
        
       // clean_list_command(&list_of_command);

   }
       
}
