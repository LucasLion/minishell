/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:15:25 by llion             #+#    #+#             */
/*   Updated: 2023/03/11 11:57:41 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;

	i = 0;
	if (haystack == 0 && len == 0)
		return (0);
	if (*(char *)needle == 0)
		return ((char *)haystack);
	while (haystack[i] && ft_strlen(needle) <= len - i)
	{
		if (*needle == haystack[i])
		{
			if (!(ft_strncmp(needle, &haystack[i], ft_strlen(needle))))
			{
				return ((char *)(haystack + i));
			}
		}
		i++;
	}
	return (0);
}
