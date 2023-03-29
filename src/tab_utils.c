/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:45:36 by amouly            #+#    #+#             */
/*   Updated: 2023/03/29 13:30:22 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tab(char **tab)
{
    int i = 0;
      
    if (tab == NULL)
        printf("TAB NULL");
    while (tab[i])
	{
		printf("tab[%d] : %s\n", i, tab[i]);
		i++;
	}
    printf("tab[%d] : %s\n", i, tab[i]);
}

char    **copy_tab(char **tab)
{
    int     i;
    char    **ret;
    int     len;

    i = 0;
    len = ft_tablen(tab);
    // HANDLE ERROR
    ret = malloc(sizeof(char *) * (len + 1));
    if (ret == NULL)
        return (NULL);
    while (tab[i])
    {
        ret[i] = ft_strdup(tab[i]);
    // HANDLE ERROR
        if (ret[i] == NULL)
            return(NULL); // free les strings d'avant      
        i++;
    }
    ret[i] = NULL;
    return (ret);
}
