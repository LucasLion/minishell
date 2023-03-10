#include "../include/minishell.h"

int main()
{
    char *input;

    while (1)
    {
        //char    **tab;
        input = readline("Minishell> ");
        add_history(input);
        //split_and_print(input);
        //printf("afetr formating\n");
        //tab = ft_split_ms(format_line(input));
        //print_input_after_formating(input);
        //print_input_after_formating(input);
        //printf ("-------------------\n");
        parse_input(input);
    }
}
