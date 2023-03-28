/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:39:16 by llion             #+#    #+#             */
/*   Updated: 2022/11/07 17:18:53 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*str;

	i = 0;
	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	else if (ft_strlen(s + start) > len)
		str = (char *)malloc((len + 1) * sizeof(char));
	else
		str = (char *)malloc((ft_strlen(s + start) + 1) * sizeof(char));
	if (str == 0)
		return (0);
	while (start < ft_strlen(s) && i < len && s[i + start])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
