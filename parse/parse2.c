/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:38:47 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/08 08:16:03 by rarraji          ###   ########.fr       */
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
