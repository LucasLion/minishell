/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/31 11:31:36 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int main(int argc, char **argv, char **env) 
{
	extern int rl_catch_signals;
	(void)argv;
	t_core	minishell;
	if (argc != 1)
        return (0);
	rl_catch_signals = 0;
	minishell.envp = copy_tab(env);
	minishell.pid = 0;
	minishell.last_status = 0;
	while (1)
	{
		signals();
		init_core(&minishell);
		if (minishell.input == 0)
		{
			printf("Exiting minishell...\n");
			exit(EXIT_SUCCESS);
		}
        if ((parse_input(&minishell)))
			execute(&minishell);
        clean_list_command(&(minishell.list_of_command));
		//system ("leaks minishell");
	}	
}
