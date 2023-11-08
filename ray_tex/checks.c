/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:09:09 by eboulhou          #+#    #+#             */
/*   Updated: 2023/11/08 08:25:42 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//function to check if there is a wall at the intersection
//returns 0 if there is a wall, 1 if not
int	check_wall_at(t_data *param, double k, double l)
{
	if (param->mat[(int)(k / param->sq_dim)][(int)(l / param->sq_dim)] == '1')
	{
		return (0);
	}
	return (1);
}
