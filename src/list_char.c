/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:19:41 by amouly            #+#    #+#             */
/*   Updated: 2023/03/30 17:40:43 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lstadd_back_ms(t_char **list, t_char *new)
{
	t_char	*temp;

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

int	fill_list(char *line, t_char **list)
{
	int		i;
	t_char	*new;

	i = 0;
	while (line && line[i])
	{
		new = malloc(sizeof(t_char));
		if (new == NULL)
			return (0);
		new->character = line[i];
		new->next = NULL;
		if (!lstadd_back_ms(list, new))
			return (0);
		i++;
	}
	return (1);
}

int	insert_space_node(t_char *previous, t_char *next)
{
	t_char	*node_space;

	node_space = malloc(sizeof(t_char));
	if (node_space == NULL)
		return (0);
	node_space->character = ' ';
	node_space->previous = previous;
	if (previous != NULL)
		previous->next = node_space;
	node_space->next = next;
	if (next != NULL)
		next->previous = node_space;
	return (1);
}

int	insert_two_spaces(t_char *node)
{
	if (!insert_space_node(node->previous, node))
		return (0);
	if (!insert_space_node(node, node->next))
		return (0);
	return (1);
}
