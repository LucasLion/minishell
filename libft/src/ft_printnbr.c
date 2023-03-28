/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:34:14 by llion             #+#    #+#             */
/*   Updated: 2022/12/12 14:32:14 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_len(int n, int nb)
{
	if (n >= 0)
		nb += ft_numlen(n);
	else
		nb += ft_numlen(n * -1);
	return (nb);
}

int	ft_printnbr_before(int n, int fd)
{
	unsigned int	nbr;
	int				nb;

	nb = 0;
	if (n < 0)
	{
		nb += ft_printchar('-', fd);
		if (nb == -1)
			return (-1);
		nbr = n * -1;
	}
	else
		nbr = n;
	if (nbr > 9)
	{
		if (ft_printnbr_before(nbr / 10, fd) == -1)
			return (-1);
		nbr = nbr % 10;
		nb = calc_len(n, nb);
	}
	else
		nb++;
	if (ft_printchar(nbr + '0', fd) == -1)
		return (-1);
	return (nb);
}

int	ft_printnbr(int n, int fd)
{
	int	tmp;

	tmp = ft_printnbr_before(n, fd);
	if (tmp == -1)
		return (-1);
	return (tmp);
}
