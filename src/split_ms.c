/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:04:32 by amouly            #+#    #+#             */
/*   Updated: 2023/03/10 16:22:39 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

// TOUT FONCTIONNE A TESTER //
// A TESTER AVEC input suivant
// "dasdas"Da dsad sad as"DSAdas" dasdasddsa"DAS  "DSA"" "<<" <<dsadasdas

int put_flag(char c, int flag)
{
	if (flag == 0 && c == '"')
		return(1);
	else if (flag == 0 && c == '\'')
		return(2);
	else if (flag == 1 && c == '"')
		return(0);
	else if (flag == 2 && c == '\'')
		return(0);
	else 
		return flag;
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
		flag = put_flag(str[i], flag);
		while (str[i] != '\0' && str[i] != ' ' && flag == 0)
		{
			i++;
			flag = put_flag(str[i], flag);
		}
		if ((str[i] == '\0' || str[i] == ' ' )&& flag == 0)
			count++;
		while (str[i] != '\0' && str[i] == ' ' && flag == 0)
		{
			i++;
			flag = put_flag(str[i], flag);
		}
		if (flag == 1 || flag == 2)
			i++;
	}
	return (count);
}

int	len_word(char const *str, int *pos)
{
	int count;
	int flag;
	int flag1;

	count  = 0;
	flag = 0;
	flag1 = 0;
	while ((str[*pos] == '\0' || str[*pos] == ' '))
		(*pos)++;
		
	flag = put_flag(str[*pos], flag);
	
	while ((str[*pos] != '\0' && str[*pos] != ' ') || flag == 1 || flag == 2)
	{
	//	flag1 = put_flag(str[*pos], flag);
	//	if ((flag1 == 1 && flag != 1)|| (flag1 == 2 && flag !=2) || (flag1 == 0 && flag!= 0))
	//		(*pos)++;
	//	else
	//		{
				count++;
				(*pos)++;
	//		}
	//	flag = flag1;
	
	flag = put_flag(str[*pos], flag);
	
	}
	return (count);
}

void	put_word(char const *str, int *pos, char *line_tab)
{
	int i;
	int flag;
	int flag1;

	i = 0;
	flag = 0;
	flag1 = 0;
	while ((str[*pos] == '\0' || str[*pos] == ' '))
		(*pos)++;

	flag = put_flag(str[*pos], flag);
	
	while ((str[*pos] != '\0' && str[*pos] != ' ') || flag == 1 || flag == 2)
	{
	//	flag1 = put_flag(str[*pos], flag);
	//	if ((flag1 == 1 && flag != 1)|| (flag1 == 2 && flag !=2) || (flag1 == 0 && flag!= 0))
	//		(*pos)++;
	//	else
	//		{
				line_tab[i] = str[*pos]; 
				(*pos)++;
				i++;
	//		}
	//	flag = flag1;

	flag = put_flag(str[*pos], flag);

	
	}
	line_tab[i] = '\0';
}

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
	int		i;
	int		pos;
	int		pos_word;
	int		len;
	
	int count_word = count_word_ms(s);
	i = 0;
	pos = 0;
	while (i < count_word)
	{
		pos_word = pos;
		len = len_word(s, &pos);
		tab[i] = malloc (sizeof(char) * (len + 1));
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

	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof( int*) * (count_word_ms(s) + 1));
	if (tab == NULL)
		return (NULL);
	if (fill_tab_split_ms(tab, s) == 0)
		return (NULL);
	else
		return (tab);
}

void split_and_print(char *line)
{
	char **tab;
	int i = 0;
	
	tab = ft_split_ms(line);
	while (tab[i])
	{
		printf("tab[%d] : %s\n", i, tab[i]);
		i++;
	}
	printf("tab[%d] : %s\n", i, tab[i]);
}
