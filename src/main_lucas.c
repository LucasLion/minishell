/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/24 11:33:28 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define R "\033[0;31m"
#define G "\033[0;32m"
#define Y "\033[0;33m"
#define B "\033[0;34m"
#define P "\033[0;35m"
#define C "\033[0;36m"
#define N "\033[0m"

int main(int argc, char **argv, char **env) 
{
	(void)argc;
	(void)argv;
	char		*input;
	t_command	*list_of_command;
	int			exit_status;
	char		**envp;
	char		**tab_argv;
	char		*command;

	envp = copy_tab(env);
	while (1)
	{
		list_of_command = NULL;
		input = readline(C"M"G"i"Y"n"B"i"P"s"C"h"R"e"G"l"Y"l"B" $ " N);
        add_history(input);
        parse_input(input, &list_of_command);
		tab_argv = list_to_tab(list_of_command->command, envp);
        command = copy_string(list_of_command->command->string, envp);
		exec_command(command, tab_argv, &envp);
	}	
	return (exit_status);
}
