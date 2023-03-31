/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ms2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:04:32 by amouly            #+#    #+#             */
/*   Updated: 2023/03/31 13:46:50 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_tab_ms_split(char **tab, int i)
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

int	fill_tab_split_ms(char **tab, char const *s)
{
	int	i;
	int	pos;
	int	pos_word;
	int	len;
	int	count_word;

	i = 0;
	pos = 0;
	count_word = count_word_ms(s);
	while (i < count_word)
	{
		pos_word = pos;
		len = len_word(s, &pos);
		tab[i] = malloc(sizeof(char) * (len + 1));
		if (tab[i] == NULL)
			return (free_tab_ms_split(tab, i));
		put_word(s, &pos_word, tab[i]);
		i++;
	}
	tab[i] = 0;
	return (1);
}

char	**ft_split_ms(char const *s)
{
	char	**tab;
	int		i;
	int		b;

	i = 0;
	b = 0;
	while (s && s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			b = 1;
		i++;
	}
	if (s == NULL || b == 0)
		return (NULL);
	tab = malloc(sizeof(int *) * (count_word_ms(s) + 1));
	if (tab == NULL)
		return (NULL);
	if (fill_tab_split_ms(tab, s) == 0)
		return (NULL);
	else
	{
		free((void *)s);
		return (tab);
	}
}

void	split_and_print(char *line)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split_ms(line);
	while (tab[i])
	{
		printf("tab[%d] : %s\n", i, tab[i]);
		i++;
	}
	printf("tab[%d] : %s\n", i, tab[i]);
}
