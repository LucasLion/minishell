/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:04:32 by amouly            #+#    #+#             */
/*   Updated: 2023/03/04 12:09:28 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int put_flag(char c, int flag)
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


int	count_word(char const *str, char c)
{
	int	i;
	int	count;
	int flag;

	flag = 0;
	count = 0;
	i = 0;
	while (str[i] != '\0' && str[i] == c)
		i++;
	
	while (str[i] != '\0')
	{
		flag = put_flag(str[i], flag);
		while (str[i] != '\0' && str[i] != c && flag == 0)
		{
			i++;
			flag = put_flag (str[i], flag);
		}
		
		if ((str[i] == '\0' || str[i] == c )&& flag == 0)
			count++;
		while (str[i] != '\0' && str[i] == c && flag == 0 )
		{
			i++;
			flag = put_flag(str[i], flag);
		}
		if (flag == 1 || flag == 2)
			i++;
	}
	return (count);
}

int	long_mot(char const *str, char c, int flag)
{
	int	count;
	int	i;
	int	flag2;

	flag2 = 0;
	count = 0;
	i = 0;
	while ((str[i] == '\0' || str[i] == c) && flag == 0)
		return (count);
	while ((str[i] != '\0' && str[i] != c) || flag == 1 || flag == 2)
	{
		flag = put_flag(str[i], flag);
		if (flag == 1 || flag == 2)
			flag2 = 1;
		i++;
		count++;
	}
	if (flag2 == 1)
			count -= 2;
	return (count);
}

int	free_tab(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (0);
}

int	fill_tab(char **tab, char c, char const *s)
{
	int		i;
	int		pos;
	int		j;
	int 	flag;
	int		flag2;
	
	flag = 0;
	i = 0;
	pos = 0;
	while (i < count_word(s, c))
	{
		flag = put_flag(s[pos], flag);
		while (long_mot(&s[pos], c, flag) == 0)
			pos++;
		tab[i] = malloc (sizeof(char) * (long_mot(&s[pos], c, flag) + 1));
		//printf("len: %d\n", long_mot(&s[pos], c, flag));
		if (tab[i] == NULL)
			return (free_tab(tab, i));
		j = 0;
		int len = long_mot(&s[pos], c, flag);
		//while (((s[pos] != c) && s[pos] != '\0') || flag == 1 || flag == 2) 
		flag2 = 0;
		while (j < len) 
		{	
			flag = put_flag(s[pos], flag);
			if ((flag == 1 || flag == 2) && flag2 == 0)	
			{
				tab[i][j] = s[++pos];
				flag2 = 1;
			}
			else 
				tab[i][j] = s[pos];
			pos++;
			j++;
		}
		tab[i][j] = '\0';
		if (flag2 == 1)
		{
			flag = 0;
			pos++;
		}
		i++;
	}
	tab[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	if (fill_tab(tab, c, s) == 0)
		return (NULL);
	else
		return (tab);
}