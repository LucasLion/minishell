/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/16 18:27:49 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	(void)envp;
	//char	**new_envp;
	char	*line;
	t_command	*list;
	int exit_status;

	list = NULL;
	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		parse_input(line, &list);
		if (ft_strncmp(line, list->command->string, 2) == 0)
			exec_command(list->command->string, argv, envp);
	}
	return (exit_status);
}
