/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:25:17 by llion             #+#    #+#             */
/*   Updated: 2023/03/04 13:50:37 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		quotes_verif(char *str)
{
	int	i;
	int	flag1;
	int	flag2;

	i = 0;
	flag1 = 0;
	flag2 = 0;
	while (str[i])
	{
		if (str[i] == '"' && flag1 == 0 && flag2 == 0)
			flag1 = 1;
		else if (str[i] == '\'' && flag1 == 0 && flag2 == 0)
			flag2 = 1;
		else if (str[i] == '"' && flag1 == 1 && flag2 == 0)
			flag1 = 0;
		else if (str[i] == '\'' && flag1 == 0 && flag2 == 1)
			flag2 = 0;
		i++;
	}
	if (flag1 == 1 || flag2 == 1)
		return (1);
	else
		return (0);
}

int verif_line(char *line)
{
    if (quotes_verif(line))
    {
        printf("Error. Close quote please\n");
        return (1);
    }
    else
        return (0);
}