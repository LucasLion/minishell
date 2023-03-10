/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:19:41 by amouly            #+#    #+#             */
/*   Updated: 2023/03/10 15:40:17 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    init_struct_command(t_command *list_of_command)
{
    list_of_command->fd_input = 0;
	list_of_command->fd_output = 1;
    list_of_command->order = 0;
	list_of_command->pipe_after = 0;
    list_of_command->delimiter = 0;
	list_of_command->delimiters = NULL;
	list_of_command->command = NULL;
	list_of_command->options_and_args = NULL;
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

void print_list_command_from_head(t_command *list)
{
    t_command *head;
    
    head = list;
    if (head == NULL)
    {
        printf("NULL\n");
        return ;
    }
    while (head)
    {
         printf("Commande num %d\n", head->order);
         printf("fd_input : %d\n", head->fd_input);
         printf("fd_output : %d\n", head->fd_output);
         printf("Commande : %s\n", head->command);
         printf("fd_output %d\n", head->fd_output);
         printf("---Liste des ARGS ou OPTION---\n");
         print_list_string_from_head(head->options_and_args);
         if (head->delimiter)
         {
            printf("---Liste des DELIMITEURS\n");
            print_list_string_from_head(head->delimiters);
         }
        head = head->next;
    }
}

/*int fill_list_int(int nbr, t_command **list)
{
    t_command *new;

    
    new = malloc(sizeof(t_command));
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

*/
