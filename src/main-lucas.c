/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:55:57 by llion             #+#    #+#             */
/*   Updated: 2023/03/14 13:07:31 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	char	*line;

	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		 
	}
}
