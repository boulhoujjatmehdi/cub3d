/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 07:56:39 by eboulhou          #+#    #+#             */
/*   Updated: 2023/11/08 08:26:13 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_data(t_data *data, t_param *params)
{
	data->mat = params->map_mehdi;
	data->sq_dim = 100;
	data->p_speed = 4;
	data->p_rad = data->p_speed * 2;
	data->rotation_angle = 1;
	data->fov = 60 * (M_PI / 180);
	data->win_w = 1600;
	data->win_h = 800;
	if (!data->txt_e || !data->txt_w || !data->txt_n || !data->txt_s)
		free_data(data, 5);
	data->width = (params->long_line - 2) * data->sq_dim;
	data->height = (params->height_map - 1) * data->sq_dim;
	data->num_rays = data->win_w;
	data->ppos_x = params->x_player;
	data->ppos_y = params->y_player;
}

void	normalize_angle(float *angle)
{
	int	tmp;

	tmp = *angle / (2 * M_PI);
	*angle = *angle - (tmp * 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	if (mat == NULL)
		return ;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
}

void	free_data(t_data *data, int exit_code)
{
	int	i;

	i = 0;
	if (data->mat == NULL)
		return ;
	while (data->mat[i])
	{
		free(data->mat[i]);
		i++;
	}
	free(data->mat);
	if (data->txt_n)
		mlx_delete_texture(data->txt_n);
	if (data->txt_s)
		mlx_delete_texture(data->txt_s);
	if (data->txt_e)
		mlx_delete_texture(data->txt_e);
	if (data->txt_w)
		mlx_delete_texture(data->txt_w);
	if (data->mlx_im)
		mlx_delete_image(data->mlx_in, data->mlx_im);
	if (exit_code)
		ft_putstr_fd("Error\n", 2);
	exit(exit_code);
}

void	vue_angle(t_data *param)
{
	int	y;
	int	x;

	x = param->ppos_x;
	y = param->ppos_y;
	if (param->mat[y][x] == 'N')
		param->p_angle = M_PI_2 * 3;
	else if (param->mat[y][x] == 'E')
		param->p_angle = 0;
	else if (param->mat[y][x] == 'S')
		param->p_angle = M_PI_2;
	else if (param->mat[y][x] == 'W')
		param->p_angle = M_PI;
	param->ppos_y = (y * param->sq_dim) + (param->sq_dim / 2);
	param->ppos_x = (x * param->sq_dim) + (param->sq_dim / 2);
}
