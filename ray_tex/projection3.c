/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:17:33 by eboulhou          #+#    #+#             */
/*   Updated: 2023/11/08 08:26:59 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//function to get tha direction of the ray
void	set_ray_direction(t_ray *ray, double ray_angle)
{
	ray->is_up = 1;
	ray->is_left = 1;
	if (ray_angle < M_PI_2 || ray_angle > M_PI_2 * 3)
		ray->is_left = 0;
	if (ray_angle >= 0 && ray_angle < M_PI)
		ray->is_up = 0;
}

//function to get y and x intersections of the ray with the grid
void	set_horz_intersections(t_data *data, t_ray *ray, double ray_angle)
{
	ray->y_inter = floor(data->ppos_y / data->sq_dim) * data->sq_dim;
	if (!ray->is_up)
		ray->y_inter += data->sq_dim;
	ray->x_inter = (ray->y_inter - data->ppos_y) / tan(ray_angle);
	ray->x_inter += data->ppos_x;
	ray->y_stp = data->sq_dim;
	if (ray->is_up)
		ray->y_stp *= -1;
	ray->x_stp = data->sq_dim / tan(ray_angle);
	if ((ray->is_left && ray->x_stp > 0) || (!ray->is_left && ray->x_stp < 0))
		ray->x_stp *= -1;
	ray->next_touch_x = ray->x_inter;
	ray->next_touch_y = ray->y_inter;
}

void	set_vert_intersections(t_data *data, t_ray *ray, double ray_angle)
{
	ray->x_inter = floor(data->ppos_x / data->sq_dim) * data->sq_dim;
	if (!ray->is_left)
		ray->x_inter += data->sq_dim;
	ray->y_inter = data->ppos_y + (ray->x_inter - data->ppos_x)
		* tan(ray_angle);
	ray->x_stp = data->sq_dim;
	if (ray->is_left)
		ray->x_stp *= -1;
	ray->y_stp = data->sq_dim * tan(ray_angle);
	if ((ray->is_up && ray->y_stp > 0) || (!ray->is_up && ray->y_stp < 0))
		ray->y_stp *= -1;
	ray->next_touch_x = ray->x_inter;
	ray->next_touch_y = ray->y_inter;
}
