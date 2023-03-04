/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:04:32 by amouly            #+#    #+#             */
/*   Updated: 2023/03/04 15:49:25 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

// Countword fonctionne faire a partir de cela
void put_flag(char c, int *flag)
{
	if (*flag == 0 && c == '"')
		*flag = 1;
	else if (*flag == 0 && c == '\'')
		*flag = 2;
	else if (*flag == 1 && c == '"')
		*flag = 0;
	else if (*flag == 2 && c == '\'')
		*flag = 0;
	else 
		*flag = *flag;
	
}

int	count_word_ms(char const *str)
{
	int	i;
	int	count;
	int flag;

	flag = 0;
	count = 0;
	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		put_flag(str[i], &flag);
		while (str[i] != '\0' && str[i] != ' ' && flag == 0)
		{
			i++;
			put_flag(str[i], &flag);
		}
		if ((str[i] == '\0' || str[i] == ' ' )&& flag == 0)
			count++;
		while (str[i] != '\0' && str[i] == ' ' && flag == 0)
		{
			i++;
			put_flag(str[i], &flag);
		}
		if (flag == 1 || flag == 2)
			i++;
	}
	return (count);
}

int	len_word(char const *str)
{
	int	count;
	int	i;
	int	flag;

	flag = 0;
	count = 0;
	i = 0;
	if ((str[i] == '\0' || str[i] == ' '))
		return (count);
	put_flag(str[i], &flag);
	while ((str[i] != '\0' && str[i] != ' ') || flag == 1 || flag == 2)
	{
		if (flag == 1 && str[i] == '"' )
		{
			flag = 0;
			i++;
		}
		else if (flag == 2 && str[i] == '\'' )
		{
			flag = 0;
			i++;
		}
		else 
		{
			i++;
			count++;
		}
		put_flag(str[i], &flag);
	}
	return (count);
}

/*int	free_tab(char **tab, int i)
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
*/
int	fill_tab_parse(int **tab, char const *s)
{
	int		i;
	int		pos;
	//int		j;
	
	i = 0;
	pos = 0;
	while (i < count_word_ms(s))
	{
		while (len_word(&s[pos]) == 0)
			pos++;
		/*tab[i] = malloc (sizeof(char) * (long_mot(&s[pos] c, flag) + 1));
		//printf("len: %d\n", long_mot(&s[pos], c, flag));
		if (tab[i] == NULL)
			return (free_tab(tab, i));
		j = 0;
		int len = long_mot(&s[pos], c, flag);
		//while (((s[pos] != c) && s[pos] != '\0') || flag == 1 || flag == 2) 
		while (s[pos] != '\0'&& j < len) 
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
		tab[i][j] = '\0';*/
		*tab[i] = len_word(&s[pos]);
		i++;
	}
	tab[i] = 0;
	return (1);
}

int	*ft_split_int(char const *s)
{
	int	*tab;

	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof( *int) * (count_word_ms(s) + 1));
	if (tab == NULL)
		return (NULL);
	if (fill_tab_parse(tab, s) == 0)
		return (NULL);
	else
		return (tab);
}

void split_and_print(char *line)
{
	int **tab;
	int i = 0;
	
	tab = ft_split_int(line);
	while (tab[i])
	{
		printf("tab[%d] : %d\n", i, *tab[i]);
		i++;
	}
}