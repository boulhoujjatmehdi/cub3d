/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:18:21 by rarraji           #+#    #+#             */
/*   Updated: 2023/10/11 12:49:42 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	n;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
	s1++;
	n = ft_strlen(s1);
	while (n != 0 && ft_strchr(set, s1[n]))
	n--;
	str = ft_substr(s1, 0, n + 1);
	return (str);
}
