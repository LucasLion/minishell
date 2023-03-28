/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:10:02 by llion             #+#    #+#             */
/*   Updated: 2022/11/10 12:16:42 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_index(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	if (len == i)
		return (0);
	return (i);
}

static int	end_index(char const *s1, char const *set)
{
	size_t		len;

	len = ft_strlen((char *)s1);
	while (len > 0 && ft_strchr(set, (char)s1[len - 1]) != 0)
		len--;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		len;
	char		*str;

	i = 0;
	if (s1 == 0 || set == 0)
		return (0);
	len = end_index(s1, set) - start_index(s1, set);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0 || s1 == 0)
		return (0);
	while (i < len)
	{
		str[i] = s1[i + start_index(s1, set)];
		i++;
	}
	str[i] = '\0';
	return (str);
}
