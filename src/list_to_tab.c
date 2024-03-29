/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:45:36 by amouly            #+#    #+#             */
/*   Updated: 2023/04/04 14:05:15 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	length_list_string(t_string *list)
{
	int	i;

	i = 0;
	if (list)
	{
		i++;
		while (list->next != NULL)
		{
			list = list->next;
			i++;
		}
		return (i);
	}
	else
		return (0);
}

int	size_var(char *s_list, int *i)
{
	int	count;

	count = 0;
	while (s_list[*i] && ((s_list[*i] >= 'a' && s_list[*i] <= 'z')
			|| (s_list[*i] >= 'A' && s_list[*i] <= 'Z')
			|| (s_list[*i] >= '0' && s_list[*i] <= '9')
			|| s_list[*i] == '_'))
	{
		count++;
		(*i)++;
	}
	return (count);
}

int	count_size_env(char *string_list, int *i, char **envp, int status)
{
	int		count;
	int		debut;
	int		b;
	char	*itoa;
	int		len;

	(*i)++;
	if (string_list[*i] == '?')
	{
		itoa = ft_itoa(status);
		len = ft_strlen(itoa);
		free(itoa);
		return (len);
	}
	debut = (*i);
	count = size_var(string_list, i);
	b = 0;
	while (envp[b])
	{
		if (!ft_strncmp(envp[b], &string_list[debut], (size_t)count)
			&& envp[b][count] == '=')
			return ((int)(ft_strlen(envp[b] + count + 1)));
		b++;
	}
	return (0);
}

void	last_error(char *ret, int *j, int status)
{
	char	*err_itoa;
	int		b;

	if (g_global.status == 1)
	{
		err_itoa = ft_itoa(g_global.status);
		g_global.status = 0;
	}
	else
		err_itoa = ft_itoa(status);
	b = 0;
	while (err_itoa[b])
	{
		ret[*j] = err_itoa[b];
		(*j)++;
		b++;
	}
	free(err_itoa);
}
