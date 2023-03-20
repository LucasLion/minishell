/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/20 11:01:23 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*line;
	t_command	*list;
	int exit_status;

	list = NULL;
	while (1)
	{
		line = readline("Minishell$ ");
		exec_command(argv, envp, list, line);
	}
	return (exit_status);
}
