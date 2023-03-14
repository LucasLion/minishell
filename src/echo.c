/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:59:28 by llion             #+#    #+#             */
/*   Updated: 2023/03/11 13:37:16 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **tab, int i)
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
	int		i;

	i = 0;
	if (ft_strncmp(args[1], "-n", 2) == 0)
		print_tab(args, 2);
	else
    {
		print_tab(args, 1);
		printf("\n");
    }
    // verifier le resultat de strncmp
}
