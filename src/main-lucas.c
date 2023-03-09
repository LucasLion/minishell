/* ************************************************************************** */ /*                                                                            */ /*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:06:00 by llion             #+#    #+#             */
/*   Updated: 2023/03/07 13:34:50 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	ft_exit()
{
	exit(0);
}

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	char	*line;
	char	***args;
	char	***envi;
	char	*test;

	while (1)
	{
		test = "LANG=YEAHSHIT USER=YOUSUCK LUCAS=gentil ANTOINE=mechant";
		line = readline("Minishell $ ");
		add_history(line);
		args = create_args_list(test);
		envi = create_env_list(envp);
		ms_export(args, envi, envp);
		free_tab3(envi);
		free_tab3(args);
	}
}
