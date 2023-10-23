/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:13:26 by rarraji           #+#    #+#             */
/*   Updated: 2022/10/05 19:39:27 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	char	*a;
	char	*b;
	size_t	i;

	a = (char *)d;
	b = (char *)s;
	i = 0;
	if (a == NULL && b == NULL)
		return (0);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (d);
}
