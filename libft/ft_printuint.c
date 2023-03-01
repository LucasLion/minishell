/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:57:11 by llion             #+#    #+#             */
/*   Updated: 2022/12/12 14:32:46 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printuint(unsigned int n, int fd)
{
	int	i;
	int	nb;

	nb = 0;
	i = n;
	if (n > 9)
	{
		if (ft_printuint(n / 10, fd) == -1)
			return (-1);
		n = n % 10;
		nb += ft_numlen(i);
	}
	else
		nb++;
	if (ft_printchar(n + '0', fd) == -1)
		return (-1);
	return (nb);
}
