/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:48:55 by rarraji           #+#    #+#             */
/*   Updated: 2023/10/11 20:04:36 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen1(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
// -----------------------------------------------//

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	s = (char *)malloc(ft_strlen1(s1) + ft_strlen1(s2) + 1);
	if (!s)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
			s[i] = s1[i];
			i++;
	}
	while (s2[j] != '\0')
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[i] = '\0';
	free(s1);
	return (s);
}
// -----------------------------------------------//

int	ft_strchr1(char *s, char c)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}
// -----------------------------------------------//

char	*ft_substr1(char *s, int start, int len)
{
	char	*p;
	int		i;

	if (!s)
		return (0);
	i = 0;
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (s && i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
