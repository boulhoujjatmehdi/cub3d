/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:44:29 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/07 19:02:11 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	compare(char *s1, int *check)
{
	int	tmp;
	int	bol;

	tmp = *check;
	bol = 1;
	if (!ft_strncmp(s1, "C", 2) && bol++)
		*check = *check | 1;
	else if (!ft_strncmp(s1, "F", 2) && bol++)
		*check = *check | 2;
	else if (!ft_strncmp(s1, "NO", 3) && bol++)
		*check = *check | 4;
	else if (!ft_strncmp(s1, "EA", 3) && bol++)
		*check = *check | 8;
	else if (!ft_strncmp(s1, "SO", 3) && bol++)
		*check = *check | 16;
	else if (!ft_strncmp(s1, "WE", 3) && bol++)
		*check = *check | 32;
	if (bol != 1)
	{
		if (tmp == *check)
			return (2);
		return (1);
	}
	return (0);
}

//function free_matrice 
void	free_matrice(char **matrice)
{
	int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}

int	mat_lenght(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
}

int	myatoi(const char *str)
{
	int		i;
	long	ret;
	int		neg;

	i = 0;
	ret = 0;
	neg = 1;
	if (!ft_isdigit(str[i]))
		return (-1);
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + str[i] - 48;
		if (ret > 255)
			return (-1);
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-1);
	return (ret);
}

int	cnt_comma(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == ',')
			cnt++;
		i++;
	}
	if (cnt == 2)
		return (1);
	return (0);
}
