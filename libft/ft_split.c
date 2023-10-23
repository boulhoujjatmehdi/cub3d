/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:37:28 by rarraji           #+#    #+#             */
/*   Updated: 2022/10/13 18:43:25 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_word(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

static char	*allocation(char const *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!word)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		word;
	int		i;

	i = 0;
	if (!s)
		return (0);
	word = ft_word(s, c);
	tab = (char **)ft_calloc(sizeof(char *), (word + 1));
	if (!tab)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
			tab[i] = allocation(s, c);
		while (*s && *s != c)
			s++;
		i++;
	}
	return (tab);
}
