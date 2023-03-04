/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:12:55 by llion             #+#    #+#             */
/*   Updated: 2023/03/04 13:17:23 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(str, ' ');
	if (ft_strncmp(tab[0], "-n", 2))
	{
		print_tab(tab, 0);
		printf("\n");
	}
	else
	{
		print_tab(tab, 1);
	}
	free_tab_ms(tab);
	// TODO 
	// probleme avec la concatenation des espaces dans une string
}

