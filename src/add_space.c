/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:19:41 by amouly            #+#    #+#             */
/*   Updated: 2023/03/14 12:44:17 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *newly)
{
	t_list	*current_lst;

	if (*lst == 0)
		*lst = newly;
	else
	{
		current_lst = ft_lstlast((t_char *)*lst);
		current_lst->next = newly;
	}
}



int fill_list(char *line, t_char **list)
{
    int i;
    t_char *new;

    int = 0;
    while(line[i])
    {
        new = malloc(sizeof(t_char *));
        if (new == NULL)
            rertun (0);
        // cleaan la liste si il y a un souci
        new 
        i++;
    }
    
}
