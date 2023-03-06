/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/06 11:21:59 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{	
	char *line;
	(void)argc;
	(void)argv;
	(void)envp;
	
	while (1)
	{
		line = readline("Minishell > ");
		add_history(line);
		if (!(verif_line(line)))
		{
			printf("nombre de mots : %d\n", count_word_ms(line));
			split_and_print(line);
		}
	}
	return (0);
}
