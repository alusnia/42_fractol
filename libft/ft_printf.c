/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:10:33 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/12 09:36:50 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	rec_arg(const char *str, va_list p)
{
	if (*str == 'c')
		return (ft_putchar_fd(va_arg(p, int), 1));
	else if (*str == 's')
		return (ft_putstr_fd(va_arg(p, char *), 1));
	else if (*str == 'p')
		return (ft_putptr_fd(va_arg(p, void *), 1));
	else if (*str == 'd' || *str == 'i')
		return (ft_putnbr_fd(va_arg(p, int), 1));
	else if (*str == 'u')
		return (ft_putunbr_fd(va_arg(p, unsigned int), 1));
	else if (*str == 'x')
		return (ft_puthex_fd(va_arg(p, unsigned int), 1, 0));
	else if (*str == 'X')
		return (ft_puthex_fd(va_arg(p, unsigned int), 1, 1));
	else if (*str == 'l' && str[1] == 'f')
		return (ft_putflt_fd(va_arg(p, double), 1));
	else if (*str == 'f')
		return (ft_putflt_fd(va_arg(p, double), 1));
	else if (*str == '%')
		return (ft_putchar_fd('%', 1), 1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	p;

	count = 0;
	va_start(p, str);
	while (*str)
	{
		if (*str == '%' && str[1])
		{
			str++;
			count += rec_arg(str, p);
			if (*str == 'l' && str[1] == 'f')
				str++;
		}
		else
		{
			ft_putchar_fd(*str, 1);
			count++;
		}
		str++;
	}
	va_end(p);
	return (count);
}
