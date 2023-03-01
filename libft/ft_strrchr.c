/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:28:03 by llion             #+#    #+#             */
/*   Updated: 2022/11/04 12:43:27 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = 0;
	while (*(char *)(s + i))
	{
		if (*(char *)(s + i) == (char)c)
		{
			tmp = (char *)(s + i);
		}
		i++;
	}
	if ((char)c == 0)
		return ((char *)s + ft_strlen(s));
	return (tmp);
}
