/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:59:28 by llion             #+#    #+#             */
/*   Updated: 2023/03/20 10:55:24 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tab_echo(char **tab, int i)
{
	int	counter;

	counter = 0;
	while (tab[counter])
		counter++;

	while (i < counter - 1)
		printf("%s " , tab[i++]);
	printf("%s", tab[i]);
}

void	echo(char **args)
{
	if (ft_strncmp(args[1], "-n", 2) == 0)
		print_tab_echo(args, 2);
	else
    {
		print_tab_echo(args, 1);
		printf("\n");
    }
}
