/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:52:32 by llion             #+#    #+#             */
/*   Updated: 2022/11/04 11:44:58 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == 0 && src == 0)
		return (0);
	if (dst > src)
	{
		while (len-- > 0)
			*(char *)(dst + len) = *(char *)(src + len);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
