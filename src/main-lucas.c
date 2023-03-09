/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/09 17:07:09 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	char	*line;
	int		env_len;

	env_len = tab_len(envp);
	while (1)
	{
		line = readline("Minishell $ ");
		add_history(line);
		envp = ms_export(envp, env_len);
		for (int i = 0; envp[i]; i++)
			printf("envp[i]: %s\n", envp[i]);
	}
}
