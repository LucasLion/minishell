/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:14:39 by llion             #+#    #+#             */
/*   Updated: 2022/12/12 14:32:22 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printaddr(unsigned long long int p, int fd)
{
	char	nbr_display;
	char	*base;
	int		nb;

	base = "0123456789abcdef";
	nb = 0;
	if (p > 15)
	{
		nb += ft_printaddr(p / 16, fd);
		nbr_display = base[p % 16];
		p = p % 10;
	}
	else
		nbr_display = base[p];
	ft_printchar(nbr_display, fd);
	nb++;
	return (nb);
}

int	ft_printp(unsigned long long int p, int fd)
{
	int	nb;
	int	tmp;

	nb = 0;
	nb += 2;
	tmp = ft_printstr("0x", fd);
	if (tmp == -1)
		return (-1);
	tmp = ft_printaddr(p, fd);
	if (tmp == -1)
		return (-1);
	nb += tmp;
	return (nb);
}
