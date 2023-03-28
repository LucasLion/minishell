/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:19:41 by amouly            #+#    #+#             */
/*   Updated: 2023/03/28 16:15:58 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    init_struct_command(t_command *list_of_command)
{
    list_of_command->redir_input = 0;
	list_of_command->redir_output = 0;
    list_of_command->order = 0;
    list_of_command->pipe_after = 0;
	list_of_command->command = NULL;
    list_of_command->input = NULL;
    list_of_command->output = NULL; 
}

int	lstadd_back_list_command(t_command **list, t_command *new)
{
	t_command      *temp;

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

int length_list_command(t_command *list, int *nb_of_pipes)
{
    int         count;
    t_command   *temp;
    
    count = 0;
    temp = list;
    // HANDLE ERROR
    if (temp == NULL)
        return (0); 
    while (temp)
    {
        count++;
        if (temp->pipe_after == 1)
            (*nb_of_pipes)++;
        temp = temp->next;
    }
    return (count);
}

