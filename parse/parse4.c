/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:42:36 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/07 18:59:45 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	chec_verg(char *str)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			cnt++;
		i++;
	}
	if (cnt != 2)
		return (1);
	return (0);
}

int	ft_cnt(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_first_last_line(t_param *vars)
{
	int	x;

	x = 0;
	while (vars->map[vars->first_line] && vars->map[vars->first_line][x])
	{
		if (ft_strchr("\n1 ", vars->map[vars->first_line][x]) == NULL)
			return (1);
		x++;
	}
	x = 0;
	while (vars->map[vars->last_line][x])
	{
		if (ft_strchr("\n1 ", vars->map[vars->last_line][x]) == NULL)
			return (1);
		x++;
	}
	return (0);
}

int	check_jnob(t_param *vars)
{
	int	y;

	y = vars->first_line;
	while (vars->map[y])
	{
		if (ft_strchr("1 ", vars->map[y][0]) == NULL && vars->map[y][0])
			return (1);
		y++;
	}
	y = vars->first_line;
	while (y < vars->last_line)
	{
		if (ft_strchr("1 \n", vars->map[y][ft_strlen(vars->map[y]) - 2]) == NULL)
			return (1);
		y++;
	}
	return (0);
}

void	ft_change(t_param *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->last_map[i])
	{
		j = 0;
		while (vars->last_map[i][j])
		{
			if (ft_strchr("0WSNE", vars->last_map[i][j]) != NULL)
				vars->map_mehdi[i][j] = vars->last_map[i][j];
			j++;
		}
		i++;
	}
	vars->height_map = i;
}
