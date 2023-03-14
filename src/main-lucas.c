/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/14 14:00:22 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	**new_envp;
	char	*line;

	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		new_envp = unset(envp, line);
		for (int i = 0; new_envp[i]; i++)
			printf("%d: %s\n", i, new_envp[i]);
	}
}
