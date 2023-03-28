/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:19:00 by llion             #+#    #+#             */
/*   Updated: 2022/12/12 14:32:06 by llion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	parse(const char *str, va_list args, int *nb)
{
	int	count;

	count = *nb;
	if (*str == 'd' || *str == 'i')
		*nb += ft_printnbr(va_arg(args, int), 1);
	else if (*str == 'c')
		*nb += ft_printchar(va_arg(args, int), 1);
	else if (*str == 's')
		*nb += ft_printstr(va_arg(args, char *), 1);
	else if (*str == 'u')
		*nb += ft_printuint(va_arg(args, unsigned int), 1);
	else if (*str == 'x')
		*nb += ft_printx_min(va_arg(args, unsigned int), 1);
	else if (*str == 'X')
		*nb += ft_printx(va_arg(args, unsigned int), 1);
	else if (*str == 'p')
		*nb += ft_printp(va_arg(args, unsigned long long int), 1);
	else if (*str == '%')
		*nb += ft_printpct(1);
	if (*nb < count)
		return (-1);
	return (*nb);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		tmp;

	len = 0;
	va_start(args, str);
	while (*str != 0)
	{
		if (*(str) == '%')
		{
			str++;
			if (parse(str, args, &len) < 0)
				return (-1);
		}
		else
		{
			tmp = write(1, str, 1);
			if (tmp == -1)
				return (-1);
			len++;
		}
		str++;
	}
	va_end(args);
	return (len);
}
