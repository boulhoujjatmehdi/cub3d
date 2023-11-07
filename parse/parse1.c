/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:38:52 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/07 18:58:26 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	space_exist(char **map, int x, int y)
{
	if (!(ft_strchr("NSWE01", map[y][x - 1])))
		return (1);
	if (!(ft_strchr("NSWE01", map[y][x + 1])))
		return (1);
	if (ft_strlen(map[y - 1]) <= (size_t)x || \
		!(ft_strchr("NSWE01", map[y - 1][x])))
		return (1);
	if (ft_strlen(map[y + 1]) <= (size_t)x || \
		!(ft_strchr("NSWE01", map[y + 1][x])))
		return (1);
	return (0);
}

int	ft_check_space(t_param *vars)
{
	int	x;
	int	y;
	int	check;

	y = 1;
	check = 0;
	while (vars->last_map && vars->last_map[y])
	{
		x = 0;
		while (vars->last_map[y][x])
		{
			if (!ft_strchr("NSWE01 \n", vars->last_map[y][x]))
				return (1);
			if (ft_strchr("NSWE0", vars->last_map[y][x]))
			{
				check = space_exist(vars->last_map, x, y);
				if (check == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
