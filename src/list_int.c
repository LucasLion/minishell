/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:19:41 by amouly            #+#    #+#             */
/*   Updated: 2023/03/08 17:13:56 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lstadd_back_list_int(t_number **list, t_number *new)
{
	t_number      *temp;

	if (list == NULL && new == NULL)
		return (0);
	if ((*list) == NULL)
	{
		(*list) = new;
        new->previous = NULL;
		new->next = NULL;
	}
	else
	{
		temp = (*list);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
        new->previous = temp;
	}
	return (1);
}



int fill_list_int(int nbr, t_number **list)
{
    t_number *new;

    
    new = malloc(sizeof(t_number));
    if (new == NULL)
        return (0);
    // cleaan la liste si il y a un souci
    new->nbr = nbr;
    new->next = NULL;
    if (!lstadd_back_list_int(list, new ))
            return (0);
    // cleaan la liste si il y a un souci
    return (1);
}

void print_list_int_from_head(t_number *list)
{
    t_number *head;
    
    head = list;
    if (head == NULL)
    {
        printf("NULL\n");
        return ;
    }
    while (head)
    {
        printf("index : %d\n", head->nbr);
        head = head->next;
    }
}

void print_list_int_from_bottom(t_number *list)
{
    t_number *head;
    
    head = list;
    if (head == NULL)
    {
        printf("\n");
        return ;
    }
    while (head->next)
        head = head->next;
    while (head)
    {
        printf("index : %d\n", head->nbr);
        head = head->previous;
    }
}


