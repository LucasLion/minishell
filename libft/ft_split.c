/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:04:32 by amouly            #+#    #+#             */
/*   Updated: 2023/03/06 12:06:33 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	count_word(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0' && str[i] == c)
			i++;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] != c)
			i++;
		if (str[i] == '\0' || str[i] == c)
			count++;
		while (str[i] != '\0' && str[i] == c)
			i++;
	}
	return (count);
}

int	long_mot(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] == '\0' || str[i] == c)
		return (count);
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		count++;
	}
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

	i = 0;
	pos = 0;
	while (i < count_word(s, c))
	{
		while (long_mot(&s[pos], c) == 0)
			pos++;
		tab[i] = malloc (sizeof(char) * (long_mot(&s[pos], c) + 1));
		if (tab[i] == NULL)
			return (free_tab(tab, i));
		j = 0;
		while ((s[pos] != c) && s[pos] != '\0' )
		{	
			tab[i][j] = s[pos];
			pos++;
			j++;
		}
	tab[i][j] = '\0';
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