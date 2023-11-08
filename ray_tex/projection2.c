/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:15:11 by eboulhou          #+#    #+#             */
/*   Updated: 2023/11/08 08:26:49 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_wall_ray(t_draw *dr, t_data *data, t_ray *ray, mlx_texture_t *tex)
{
	int	i_wal;

	i_wal = 0;
	while (dr->i++ < dr->y_0 + ray->wall_height)
	{
		if (dr->i < data->win_h && dr->i > 0)
		{
			ray->y_offset = i_wal * ((float)tex->height
					/ ray->wall_height);
			dr->color = get_color(tex, ray->x_offset, ray->y_offset);
			mlx_put_pixel(data->mlx_im, ray->i, dr->y, dr->color);
		}
		i_wal++;
		dr->y++;
	}
}

void	draw_strip(t_data *data, t_ray *ray)
{
	mlx_texture_t	*tex;
	t_draw			draw;

	draw.strip_height = ray->wall_height;
	tex = data->txt;
	draw.y_0 = (data->win_h / 2) - (ray->wall_height / 2);
	draw.y = 0;
	while (draw.y < draw.y_0)
		mlx_put_pixel(data->mlx_im, ray->i, draw.y++, data->ceiling_color);
	draw.y = draw.y_0;
	draw.i = draw.y_0;
	draw_wall_ray(&draw, data, ray, tex);
	while (draw.y < data->win_h)
		mlx_put_pixel(data->mlx_im, ray->i, draw.y++, data->floor_color);
	ray->x_offset = 0;
}

//function to project horizontal rays
int	project_horz_ray(t_data *data, t_wall *wall, t_ray *ray)
{
	if (wall->horz_distance < wall->vert_distance 
		|| (wall->horz_distance == wall->vert_distance && ray->test == false))
	{
		if (wall->horz_y < data->ppos_y)
		{
			wall->direction = NORTH;
			data->txt = data->txt_n;
		}
		else
		{
			wall->direction = SOUTH;
			data->txt = data->txt_s;
		}
		ray->test = false;
		ray->lenght = wall->horz_distance * cos(data->p_angle - ray->angle);
		ray->wall_height = (data->win_h / ray->lenght) * data->sq_dim;
		ray->x_offset = ((float)data->txt->width / data->sq_dim)
			* (wall->horz_x % data->sq_dim);
		draw_strip(data, ray);
		return (1);
	}
	return (0);
}

//function to project vertical rays
int	project_vert_ray(t_data *data, t_wall *wall, t_ray *ray)
{
	if (wall->horz_distance > wall->vert_distance
		|| (wall->horz_distance == wall->vert_distance && ray->test == true))
	{
		if (wall->vert_x < data->ppos_x)
		{
			wall->direction = EAST;
			data->txt = data->txt_e;
		}
		else
		{
			wall->direction = WEST;
			data->txt = data->txt_w;
		}
		ray->test = true;
		ray->lenght = wall->vert_distance * cos(data->p_angle - ray->angle);
		ray->wall_height = (data->win_h / ray->lenght) * data->sq_dim;
		ray->x_offset = ((float)data->txt->width / data->sq_dim)
			* (wall->vert_y % data->sq_dim);
		draw_strip(data, ray);
		return (1);
	}
	return (0);
}

int	get_color( mlx_texture_t *tex, int x, int y)
{
	uint8_t	*pixels;
	int		color;

	pixels = tex->pixels;
	color = (pixels[(y * tex->width * 4) + (4 * x) + 0] << 24);
	color += (pixels[(y * tex->width * 4) + (4 * x) + 1] << 16);
	color += (pixels[(y * tex->width * 4) + (4 * x) + 2] << 8);
	color += (pixels[(y * tex->width * 4) +(4 * x) + 3]);
	return (color);
}
