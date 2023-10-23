/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:13:26 by rarraji           #+#    #+#             */
/*   Updated: 2023/10/11 13:11:14 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	// if (c == '\0')
	// 	return ((char *)s + ft_strlen(s));
	if (s[i] == '\0')
		return (NULL);
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)(s + i));
}
