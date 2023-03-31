/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:04:32 by amouly            #+#    #+#             */
/*   Updated: 2023/03/31 13:46:33 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	put_flag(char c, int flag)
{
	if (flag == 0 && c == '"')
		return (1);
	else if (flag == 0 && c == '\'')
		return (2);
	else if (flag == 1 && c == '"')
		return (0);
	else if (flag == 2 && c == '\'')
		return (0);
	else
		return (flag);
}

int	count_word_ms(char const *str)
{
	int	i;
	int	count;
	int	flag;

	flag = 0;
	count = 0;
	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		flag = put_flag(str[i], flag);
		while (str[i] != '\0' && str[i] != ' ' && flag == 0)
			flag = put_flag(str[++i], flag);
		if ((str[i] == '\0' || str[i] == ' ') && flag == 0)
			count++;
		while (str[i] != '\0' && str[i] == ' ' && flag == 0)
			flag = put_flag(str[++i], flag);
		if (flag == 1 || flag == 2)
			i++;
	}
	return (count);
}

int	len_word(char const *str, int *pos)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while ((str[*pos] == '\0' || str[*pos] == ' '))
		(*pos)++;
	flag = put_flag(str[*pos], flag);
	while ((str[*pos] != '\0' && str[*pos] != ' ') || flag == 1 || flag == 2)
	{
		count++;
		(*pos)++;
		flag = put_flag(str[*pos], flag);
	}
	return (count);
}

void	put_word(char const *str, int *pos, char *line_tab)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((str[*pos] == '\0' || str[*pos] == ' '))
		(*pos)++;
	flag = put_flag(str[*pos], flag);
	while ((str[*pos] != '\0' && str[*pos] != ' ') || flag == 1 || flag == 2)
	{
		line_tab[i] = str[*pos];
		(*pos)++;
		i++;
		flag = put_flag(str[*pos], flag);
	}
	line_tab[i] = '\0';
}
