/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:45:36 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/08 08:23:55 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	my_error(int *err, int code, char *str, char **spl)
{
	*err = code;
	free(str);
	free_matrice(spl);
	return (1);
}

int	check_entries(t_check *c)
{
	if (c->spl && c->spl[0] && c->spl[0][0] == '1')
	{
		if (my_error(&c->err, c->err, c->str, c->spl) && c->check != 63)
			c->err = 1;
		return (1);
	}
	return (0);
}

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

int	set_texture(char *str, mlx_texture_t **store_texture)
{
	if (!str)
		return (1);
	*store_texture = mlx_load_png(str);
	if (!*store_texture)
		return (1);
	return (0);
}
