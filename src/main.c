/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/04/01 17:22:09 by amouly           ###   ########.fr       */
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
	rl_catch_signals = 1;
	minishell.envp = copy_tab(env);
	minishell.last_status = 0;
	while (1)
	{
		signals();
		init_core(&minishell);
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
