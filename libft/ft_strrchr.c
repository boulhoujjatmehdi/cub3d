/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:13:26 by rarraji           #+#    #+#             */
/*   Updated: 2022/10/05 22:02:29 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		cont;
	char	*i;

	cont = ft_strlen((char *)s);
	i = (char *)s + cont;
	while (i >= s)
	{
		if ((unsigned char)c == *i)
			return (i);
		i--;
	}
	return (0);
}
