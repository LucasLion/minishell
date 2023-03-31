/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:51:24 by amouly            #+#    #+#             */
/*   Updated: 2023/03/31 11:49:48 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_list_char(t_char **list)
{
	t_char	*next;

	next = NULL;
	if (list == NULL)
		return ;
	while (*list)
	{
		next = (*list)->next;
		free(*list);
		*list = next;
	}
}

void	clean_list_string(t_string **list)
{
	t_string	*next;

	next = NULL;
	if (list == NULL)
		return ;
	while (*list)
	{
		next = (*list)->next;
		free((*list)->string);
		free(*list);
		*list = next;
	}
}

void	clean_list_command(t_command **list)
{
	t_command	*next;

	next = NULL;
	if (list == NULL)
		return ;
	while (*list)
	{
		next = (*list)->next;
		clean_list_string(&(*list)->command);
		clean_list_string(&(*list)->input);
		clean_list_string(&(*list)->output);
		free(*list);
		*list = next;
	}
}
