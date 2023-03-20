/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:45:36 by amouly            #+#    #+#             */
/*   Updated: 2023/03/18 11:33:44 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tab(char **tab)
{
    int i = 0;
      
    if (tab == NULL)
        return ;
    while (tab[i])
	{
		printf("tab[%d] : %s\n", i, tab[i]);
		i++;
	}
    printf("tab[%d] : %s\n", i, tab[i]);
}

int len_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i])
        i++;
    return (i);
}

char    **copy_tab(char **tab)
{
    int     i;
    char    **ret;
    int     len;

    i = 0;
    len = len_tab(tab);
    ret = malloc(sizeof(char *) * (len + 1));
    if (ret == NULL)
        return (NULL);
    while (tab[i])
    {
        ret[i] = ft_strdup(tab[i]);
        if (ret[i] == NULL)
            return(NULL); // free les strings d'avant      
        i++;
    }
    ret[i] = NULL;
    return (ret);
}
