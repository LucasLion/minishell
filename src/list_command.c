/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:19:41 by amouly            #+#    #+#             */
/*   Updated: 2023/03/11 12:30:20 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    init_struct_command(t_command *list_of_command)
{
    list_of_command->redir_input = 0;
	list_of_command->redir_output = 0;
    list_of_command->order = 0;
    list_of_command->delimiter = 0;
    list_of_command->pipe_after = 0;
	list_of_command->delimiters = NULL;
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
        printf("COMMANDE OPTIONS ET ARGUMENTS : \n");
        print_list_string_from_head_command(head->command);
        if (head->redir_input == 1)
        {
            printf("LIST DES INPUT : \n");    
            print_list_string_from_head(head->input);
            
        }
        if (head->redir_output == 1)
        {
            printf("LIST DES OUTPUT : \n");
            print_list_string_from_head(head->output);
        }
        if (head->delimiter == 1)
        {
            printf("LIST DES DELIMITEURS :\n");
            print_list_string_from_head(head->delimiters);
        }
        if (head->pipe_after == 1)
            printf("---PIPE NUM %d----\n", head->order);
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
