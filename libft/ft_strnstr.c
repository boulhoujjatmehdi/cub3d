/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:27:33 by rarraji           #+#    #+#             */
/*   Updated: 2022/10/14 17:09:08 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *ha, const char *ne, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (!ha && !len)
		return (0);
	if (ft_strlen((char *)ne) == 0 || !ne)
		return ((char *)ha);
	while (ha[i] && i < len)
	{
		n = 0;
		while (ne[n] && (ha[i + n] == ne[n]) && (i + n) < len)
		{
			n++;
		}
		if (ne[n] == '\0')
			return (((char *)ha) + i);
		i++;
	}
	return (NULL);
}
