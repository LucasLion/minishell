/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:26:07 by llion             #+#    #+#             */
/*   Updated: 2022/11/04 11:27:05 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;

	tmp_dst = dst;
	tmp_src = src;
	if (dst == 0 && src == 0)
		return (0);
	while (n)
	{
		*tmp_dst = *tmp_src;
		n--;
		tmp_dst++;
		tmp_src++;
	}
	return (dst);
}
