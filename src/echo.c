/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:59:28 by llion             #+#    #+#             */
/*   Updated: 2023/03/24 11:28:44 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO gerer le cas particulier du blackslash

void	print_tab_echo(char **tab, int i, int fd_out)
{
	int	counter;

	counter = 0;
	while (tab[counter])
		counter++;

	while (i < counter - 1)
	{
		write(fd_out, tab[i], ft_strlen(tab[i]));
		i++;
	}
		//printf("%s " , tab[i++]);
	write(fd_out, tab[i], ft_strlen(tab[i]));
	//printf("%s", tab[i]);
}

void	echo(char **argv, int fd_out)
{
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
		print_tab_echo(argv, 2, fd_out);
	else if (argv[1])
	{
		print_tab_echo(argv, 1, fd_out);
		printf("\n");
	}
	else
		printf("\n");
}
