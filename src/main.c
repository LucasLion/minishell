/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/04/03 11:37:41 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	extern int	rl_catch_signals;
	t_core		minishell;

	(void)argv;
	if (argc != 1)
		return (0);
	minishell.envp = copy_tab(env);
	minishell.last_status = 0;
	while (1)
	{
		if (status != 0)
		{
			minishell.last_status = status;
			status = 0;
		}
		init_core(&minishell);
		signals();
		if (minishell.input == 0)
		{
			printf("Exiting minishell...\n");
			clean_list_command(&(minishell.list_of_command));
			ft_freetab(minishell.envp);
			exit(EXIT_SUCCESS);
		}
		if ((parse_input(&minishell)))
			execute(&minishell);
		clean_list_command(&(minishell.list_of_command));
	}	
	ft_freetab(minishell.envp);
}
