/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/20 14:46:44 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		input = readline("Minishell$ ");
        add_history(input);
        parse_input(input, &list_of_command);
		tab_argv = list_to_tab(list_of_command->command, envp);
        command = copy_string(list_of_command->command->string, envp);
		envp = exec_command(command, tab_argv, envp);
	}	
	return (exit_status);
}
