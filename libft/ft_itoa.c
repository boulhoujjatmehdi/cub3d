/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:28:40 by rarraji           #+#    #+#             */
/*   Updated: 2022/10/13 18:49:35 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	int_count(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = nb * -1;
	}
	if (nb == 0)
		count++;
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	n1;
	int		count;
	char	*str;

	n1 = n;
	count = int_count(n1);
	str = (char *)ft_calloc(sizeof(char), (count + 1));
	if (str == 0)
		return (0);
	count--;
	if (n1 < 0)
	{
		str[0] = '-';
		n1 = n1 * -1;
	}
	if (n1 == 0)
		str[0] = '0';
	while (n1 > 0)
	{
		str[count] = (n1 % 10) + 48;
		n1 = n1 / 10;
		count--;
	}
	return (str);
}
