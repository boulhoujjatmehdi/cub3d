/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:55:03 by rarraji           #+#    #+#             */
/*   Updated: 2022/10/13 19:27:02 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*p;

	if (!s)
		return (0);
	i = 0;
	if (start > ft_strlen((char *)s))
		return (ft_calloc(1, sizeof(char)));
	if (len > ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	p = (char *)malloc(len + 1);
	if (p == 0)
		return (NULL);
	while (s && i < (int)len)
	{
		p[i] = ((char *)s)[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
