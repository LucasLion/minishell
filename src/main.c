/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/04/03 15:58:10 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



void	ctrl_d(t_core *minishell)
{
	printf("Exiting minishell...\n");
	clean_list_command(&(minishell->list_of_command));
	ft_freetab(minishell->envp);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	extern int	rl_catch_signals;
	t_core		minishell;

	(void)argv;
	if (argc != 1)
		return (0);
	minishell.envp = copy_tab(env);
	minishell.last_status = 0;
	rl_catch_signals = 0;
	signals();
	while (1)
	{
		if (globals.status != 0)
		{
			minishell.last_status = globals.status;
			globals.status = 0;
		}
		globals.catch = 1;
		init_core(&minishell);
		if (minishell.input == 0)
			ctrl_d(&minishell);
		if ((parse_input(&minishell)))
			execute(&minishell);
		clean_list_command(&(minishell.list_of_command));
	}	
	ft_freetab(minishell.envp);
}
