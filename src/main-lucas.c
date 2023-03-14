/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/14 10:53:30 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	char	*line;
	char **new;

	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		char *string = "LANG token";
		new = unset(envp, string);
	for (int i = 0; new[i]; i++)
		printf("%d: %s\n", i, new[i]);
	}
}