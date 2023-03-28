/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:36:49 by llion             #+#    #+#             */
/*   Updated: 2022/11/14 12:50:40 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
		{
			count++;
			i++;
		}
		else if (s[i] != c && s[i - 1] == c)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**malloc_error(char **tab, unsigned int j)
{
	unsigned int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	word_len(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != 0)
	{
		i++;
		count++;
	}
	return (count);
}

static char	*fill_tab(char *s, char c)
{
	int		i;
	char	*word;
	int		word_lenght;

	i = 0;
	word_lenght = word_len(s, c);
	word = malloc(sizeof(char) * (word_lenght + 1));
	if (word == 0)
		return (NULL);
	while (i < word_lenght)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		tab_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab_len = count_words(s, c);
	tab = malloc(sizeof(char *) * (tab_len + 1));
	if (tab == 0)
		return (0);
	while (*s)
	{
		if ((i == 0 && s[i] != c) || (*s != c && *(s - 1) == c))
		{
			tab[j] = fill_tab((char *)s, c);
			if (tab[j] == NULL)
				return (malloc_error(tab, j));
			i++;
			j++;
		}
		s++;
	}
	tab[j] = 0;
	return (tab);
}
