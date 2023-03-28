/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx_min.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 09:06:19 by llion             #+#    #+#             */
/*   Updated: 2022/12/12 14:33:00 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printx_min_before(unsigned int n, int fd)
{
	int		nb;
	char	nbr_display;
	char	*base;

	nb = 0;
	base = "0123456789abcdef";
	if (n > 15)
	{
		nb += ft_printx_min_before(n / 16, fd);
		if (nb == -1)
			return (-1);
		nbr_display = base[n % 16];
		n = n % 10;
	}
	else
		nbr_display = base[n];
	if (ft_printchar(nbr_display, fd) == -1)
		return (-1);
	nb++;
	return (nb);
}

int	ft_printx_min(unsigned int n, int fd)
{
	int	nb;
	int	tmp;

	nb = 0;
	tmp = ft_printx_min_before(n, fd);
	if (tmp == -1)
		return (-1);
	nb += tmp;
	return (nb);
}
