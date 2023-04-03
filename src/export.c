/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:12:49 by llion             #+#    #+#             */
/*   Updated: 2023/04/03 16:30:44 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_arg2(char *a, int *status)
{
	int	i;

	i = 0;
	while (a[i] && a[i] != '=')
	{
		if (a[i] != ' ')
			i++;
		else
		{
			*status = 1;
			return (ms_error(a, NULL, -5));
		}
	}
	if (a[i] == '=' && i == 0)
	{
		*status = 1;
		return (ms_error(a, NULL, -5));
	}
	else
		return (1);
}

int	parse_arg(char *a, int *status)
{
	int	i;

	i = 0;
	if ((a[0] >= 'a' && a[0] <= 'z') || (a[0] >= 'A' && a[0] <= 'Z')
		|| a[0] == '_')
		return (parse_arg2(a, status));
	else
	{
		*status = 1;
		return (ms_error(a, NULL, -5));
	}
}

char	**sort_tab(char **tab, int size)
{
	int		i;
	int		j;
	int		min;
	char	*tmp;
	char	**sorted_tab;

	i = 0;
	sorted_tab = copy_tab(tab);
	while (i < size - 1)
	{
		j = i + 1;
		min = i;
		while (j < size)
		{
			if (ft_strncmp(sorted_tab[j], sorted_tab[min],
					ft_strlen(sorted_tab[j])) < 0)
				min = j;
			j++;
		}
		tmp = sorted_tab[i];
		sorted_tab[i++] = sorted_tab[min];
		sorted_tab[min] = tmp;
	}
	return (sorted_tab);
}

char	*add_double_quotes(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	while (str[i] && str[i] != '=')
		ret[j++] = str[i++];
	if (str[i] == '=')
	{
		i++;
		ret[j++] = '=';
		ret[j++] = '"';
		while (str[i])
			ret[j++] = str[i++];
		ret[j] = '"';
	}
	return (ret);
}

void	display_export(char **envp)
{
	int		i;
	char	**sorted;
	char	*formatted;

	i = 0;
	sorted = sort_tab(envp, ft_tablen(envp));
	while (sorted[i])
	{
		if (sorted[i][1] == '=' && sorted[i][0] == '_')
			i++;
		else
		{
			formatted = add_double_quotes(sorted[i]);
			printf("declare -x %s\n", formatted);
			free(formatted);
			i++;
		}
	}
	ft_freetab(sorted);
}
