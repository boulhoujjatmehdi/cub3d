/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:42:36 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/08 08:15:55 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	ft_search_player_2(t_param *vars, int y, int i, int cnt)
{
	int	x;

	while (vars->map[y])
	{
		vars->last_map[i] = ft_substr(vars->map[y], 0, ft_strlen(vars->map[y]));
		x = 0;
		while (vars->last_map[i][x])
		{
			if (ft_strchr("NSEW 10\n", vars->last_map[i][x]) == NULL)
				return (1);
			else if (ft_strchr("NSEW", vars->last_map[i][x]) != NULL)
			{
				vars->x_player = x;
				vars->y_player = i;
				cnt++;
			}
			x++;
		}
		y++;
		i++;
	}
	vars->last_map[i] = 0;
	vars->last_line = i - 1;
	check_long_line(vars);
	return (cnt);
}

int	ft_search_player(t_param *vars)
{
	int	y;
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	y = vars->first_line;
	vars->last_map = (char **)ft_calloc(sizeof(char *), \
		(vars->last_line - vars->first_line + 2));
	cnt = ft_search_player_2(vars, y, i, cnt);
	return (cnt);
}
