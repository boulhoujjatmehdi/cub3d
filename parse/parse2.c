/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:38:47 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/07 20:49:38 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_long_line(t_param *vars)
{
	int	i;

	vars->long_line = 0;
	i = 0;
	while (vars->last_map[i])
	{
		if (ft_strlen(vars->last_map[i]) > vars->long_line)
			vars->long_line = ft_strlen(vars->last_map[i]);
		i++;
	}
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

int	ft_cnt_param(t_param *var)
{
	int	i;
	int	cnt;
	int	tmp;

	tmp = 0;
	i = -1;
	cnt = 0;
	var->first_line = 0;
	while (var->map_trim[++i])
	{
		if (ft_strchr("WSNEFC", var->map_trim[i][0]) != NULL)
			continue ;
		if (var->map_trim[i][0] == '1')
		{
			if (tmp == 0)
			{
				var->first_line = i;
				tmp = 1;
			}
			var->last_line = i;
		}
	}
	return (0);
}
