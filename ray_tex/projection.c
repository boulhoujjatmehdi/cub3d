/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:12:39 by eboulhou          #+#    #+#             */
/*   Updated: 2023/11/08 08:26:32 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_projection(t_data *data)
{
	t_wall	wall;
	t_ray	ray;

	ft_bzero(&ray, sizeof(t_ray));
	ray.step = fabs((float)data->fov / (float)data->num_rays);
	ray.angle = data->p_angle - (data->fov / 2);
	while (ray.i < data->num_rays)
	{
		normalize_angle(&ray.angle);
		ft_bzero(&wall, sizeof(t_wall));
		horizontal(data, ray.angle, &wall);
		verticall(data, ray.angle, &wall);
		set_distance(data, &wall);
		project_horz_ray(data, &wall, &ray);
		project_vert_ray(data, &wall, &ray);
		ray.i++;
		ray.angle += ray.step;
	}
}

void	horizontal(t_data *data, double ray_angle, t_wall *wall)
{
	t_ray	ray;

	ft_bzero(&ray, sizeof(t_ray));
	set_ray_direction(&ray, ray_angle);
	set_horz_intersections(data, &ray, ray_angle);
	wall->horz_x = data->ppos_x;
	wall->horz_y = data->ppos_y;
	while (ray.next_touch_x >= 0 && ray.next_touch_x <= data->width
		&& ray.next_touch_y >= 0 && ray.next_touch_y <= data->height)
	{
		ray.check_x = ray.next_touch_x;
		ray.check_y = ray.next_touch_y - ray.is_up;
		if (check_wall_at(data, ray.check_y, ray.check_x) == false)
		{
			wall->horz_found_wall = true;
			wall->horz_x = ray.next_touch_x;
			wall->horz_y = ray.next_touch_y;
			break ;
		}
		else
		{
			ray.next_touch_x += ray.x_stp ;
			ray.next_touch_y += ray.y_stp;
		}
	}
}

void	verticall(t_data *data, double ray_angle, t_wall *wall)
{
	t_ray	ray;

	ft_bzero(&ray, sizeof(t_ray));
	set_ray_direction(&ray, ray_angle);
	set_vert_intersections(data, &ray, ray_angle);
	wall->vert_x = data->ppos_x;
	wall->vert_y = data->ppos_y;
	while (ray.next_touch_x >= 0 && ray.next_touch_x <= data->width
		&& ray.next_touch_y >= 0 && ray.next_touch_y <= data->height)
	{
		ray.check_x = ray.next_touch_x - ray.is_left;
		ray.check_y = ray.next_touch_y;
		if (check_wall_at(data, ray.check_y, ray.check_x) == false)
		{
			wall->vert_found_wall = true;
			wall->vert_x = ray.next_touch_x;
			wall->vert_y = ray.next_touch_y;
			break ;
		}
		else
		{
			ray.next_touch_x += ray.x_stp;
			ray.next_touch_y += ray.y_stp;
		}
	}
}

//functions to count the distance between the player and the wall
void	set_distance(t_data *data, t_wall *wall)
{
	wall->vert_distance = INT64_MAX;
	wall->horz_distance = INT64_MAX;
	if (wall->vert_found_wall)
	{
		wall->vert_distance = sqrt((wall->vert_x - data->ppos_x)
				* (wall->vert_x - data->ppos_x) + (wall->vert_y - data->ppos_y)
				* (wall->vert_y - data->ppos_y));
	}
	if (wall->horz_found_wall)
	{
		wall->horz_distance = sqrt ((wall->horz_x - data->ppos_x)
				* (wall->horz_x - data->ppos_x) + (wall->horz_y - data->ppos_y)
				* (wall->horz_y - data->ppos_y));
	}
}
