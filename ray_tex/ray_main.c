/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:23:06 by eboulhou          #+#    #+#             */
/*   Updated: 2023/11/08 08:18:57 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "mehdiCub3d.h"
#include "../cub3d.h"

void	draw(void *dt)
{
	t_data	*data;

	data = (t_data *) dt;
	mouvements(data);
	wall_projection(data);
}

int	display(t_param *params, t_data *data)
{
	initialize_data(data, params);
	vue_angle(data);
	data->mlx_in = mlx_init(data->win_w, data->win_h, "cub3D", 0);
	if (!data->mlx_in)
		free_data(data, 1);
	data->mlx_im = mlx_new_image(data->mlx_in, data->win_w, data->win_h);
	if (!data->mlx_im)
		free_data(data, 2);
	if (mlx_image_to_window(data->mlx_in, data->mlx_im, 0, 0) == -1)
		free_data(data, 3);
	if (!mlx_loop_hook(data->mlx_in, draw, data))
		free_data(data, 4);
	mlx_loop(data->mlx_in);
	free_data(data, 0);
	return (0);
}
