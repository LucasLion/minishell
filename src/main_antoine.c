#include "minishell.h"

int main()
{
    char *input;

   while (1)
   {
        t_command *list_of_command;

        list_of_command = NULL;
        input = readline("Minishell> ");
        add_history(input);
        parse_input_loc(input, list_of_command);
        
        clean_list_command(&list_of_command);

   }
       
}
