/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:24:41 by rarraji           #+#    #+#             */
/*   Updated: 2023/09/18 09:28:56 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

// -------------------------------//

int	ft_putnbr(int n)
{
	int		cont;

	cont = 0;
	if (n > 9)
	{
		cont += ft_putnbr(n / 10);
		cont += ft_putnbr(n % 10);
	}
	else
	{
		cont += ft_putchar(n + 48);
	}
	return (cont);
}
// -------------------------------//

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}
// -------------------------------//

int	ft_check(va_list list, char c)
{
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(list, int)));
	else if (c == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(list, char *)));
	return (0);
}
// -------------------------------//

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		cont;

	va_start(list, str);
	cont = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			cont += ft_check(list, *str);
		}
		else
			cont += ft_putchar(*str);
		str++;
	}
	va_end (list);
	return (cont);
}
