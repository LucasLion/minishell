/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:41:30 by llion             #+#    #+#             */
/*   Updated: 2022/12/12 14:32:39 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str, int fd)
{
	int	nb;
	int	tmp;

	nb = 0;
	if (!str)
		str = "(null)";
	if (str)
	{
		while (*str != '\0')
		{
			tmp = write(fd, str, 1);
			if (tmp == -1)
				return (-1);
			str++;
			nb++;
		}
	}
	else
		return (nb);
	return (nb);
}
