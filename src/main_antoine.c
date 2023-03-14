#include "minishell.h"

int main()
{
    char *input;

    while (1)
    {
        input = readline("Minishell> ");
        add_history(input);
        parse_input(input);
    }
}
