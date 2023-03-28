/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:59:28 by llion             #+#    #+#             */
/*   Updated: 2023/03/28 14:10:28 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO gerer le cas particulier du blackslash
// PARSING A FAIRE

int	print_tab_echo(char **tab, int i)
{
	int	counter;

	counter = 0;
	while (tab[counter])
		counter++;
	while (i < counter - 1)
	{
		if (tab[i] == NULL)
			return (ms_error("echo", NULL, errno));
		printf("%s " , tab[i++]);
	}
	printf("%s", tab[i]);
	return (0);
}

int	echo(char **argv)
{
	if (argv == NULL)
		return (ms_error("echo", NULL, errno));
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
		print_tab_echo(argv, 2);
	else if (argv[1])
	{
		print_tab_echo(argv, 1);
		printf("\n");
	}
	else
		printf("\n");
	return (0);
}
