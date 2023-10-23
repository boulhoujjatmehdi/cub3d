/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:37:00 by rarraji           #+#    #+#             */
/*   Updated: 2022/10/05 20:24:22 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen((char *)(src)));
	len_d = ft_strlen(dst);
	len_s = ft_strlen((char *)src);
	if (len_d > dstsize)
		return (len_s + dstsize);
	if (dstsize > len_d)
	{
		while ((len_d + i < (dstsize - 1)) && src[i] != '\0')
		{
			dst[len_d + i] = src[i];
			i++;
		}
		dst[len_d + i] = '\0';
	}
	return (len_d + len_s);
}
