/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mehdiCub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:23:06 by eboulhou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/30 15:10:16 by eboulhou         ###   ########.fr       */
=======
/*   Updated: 2023/10/25 15:50:46 by eboulhou         ###   ########.fr       */
>>>>>>> 6b4267c80c8df90569f31d36df8eb47b33624538
/*                                                                            */
/* ************************************************************************** */

#include "mehdiCub3d.h"
#include "cub3d.h"

void	lire_map(t_data *data, char *av)
{
	int		fd;
	int		i;
	int		j;
	char	*c;

	j = 0;
	i = 0;
	fd = open(av, O_RDONLY);
	while (1)
	{
		c = get_next_line(fd);
		i++;
		free(c);
		if (!c)
			break ;
	}
	close(fd);
	fd = open(av, O_RDONLY);
	data->mat = (char **)malloc(sizeof(char *) * (i + 1));
	while (i--)
	{
		data->mat[j] = get_next_line(fd);
		j++;
	}
	data->mat[j] = 0;
}

void	len_mapp(t_data *data)
{
	int	k;
	int	l;

	k = -1;
	l = 0;
	data->height = 0;
	data->width = 0;
	while (data->mat[++k])
	{
		if (l == 0)
		{
			while (data->mat[k][l] != '\0')
			{
				data->width++;
				l++;
			}
			data->width--;
		}
		data->height++;
	}
}

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

//function to rotate the player
void	rotate_player(t_data *pr)
{
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_LEFT))
	{
		pr->p_angle -= (M_PI / 180) * pr->rotation_angle;
	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_RIGHT))
	{
		pr->p_angle += (M_PI / 180) * pr->rotation_angle;
	}
}

//function to move the player forward and backward
//returns 1 if there is a wall, 0 if not
int	check_move(t_data *pr, float yl, float xl)
{
	int	check;

	check = 0;
	if (check_wall_at(pr, yl, xl))
		check++;
	if (check_wall_at(pr, yl, pr->ppos_x) && check_wall_at(pr, pr->ppos_y, xl))
		check ++;
	if (check == 2)
		return (1);
	return (0);
}

void	move_player_forward_backward(t_data *pr)
{
	float	tmpx;
	float	tmpy;

	tmpx = cos(pr->p_angle) * pr->p_rad;
	tmpy = sin(pr->p_angle) * pr->p_rad;
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_W)
		&& check_move(pr, (pr->ppos_y + tmpy), (pr->ppos_x + tmpx)))
	{
		pr->ppos_x += cos(pr->p_angle) * pr->p_speed;
		pr->ppos_y += sin(pr->p_angle) * pr->p_speed;
	}
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_S)
		&& check_move(pr, (pr->ppos_y - tmpy), (pr->ppos_x - tmpx)))
	{
		pr->ppos_x -= cos(pr->p_angle) * pr->p_speed;
		pr->ppos_y -= sin(pr->p_angle) * pr->p_speed;
	}
}

//function to move the player left and right
void	move_player_left_right(t_data *pr)
{
	float	tmpx;
	float	tmpy;

	tmpx = cos(pr->p_angle + M_PI_2) * pr->p_rad;
	tmpy = sin(pr->p_angle + M_PI_2) * pr->p_rad;
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_A)
		&& check_move(pr, (pr->ppos_y - tmpy), (pr->ppos_x - tmpx)))
	{
		pr->ppos_x -= cos(pr->p_angle + M_PI_2) * pr->p_speed;
		pr->ppos_y -= sin(pr->p_angle + M_PI_2) * pr->p_speed;
	}
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_D)
		&& check_move(pr, (pr->ppos_y + tmpy), roundf(pr->ppos_x + tmpx)))
	{
		pr->ppos_x += cos(pr->p_angle + M_PI_2) * pr->p_speed;
		pr->ppos_y += sin(pr->p_angle + M_PI_2) * pr->p_speed;
	}
}

void	mouvements(t_data *pr)
{
	rotate_player(pr);
	move_player_forward_backward(pr);
	move_player_left_right(pr);
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_Q)
		|| mlx_is_key_down(pr->mlx_in, MLX_KEY_ESCAPE))
		exit(0);
}

void	normalize_angle(float *angle)
{
	int	tmp;

	tmp = *angle / (2 * M_PI);
	*angle = *angle - (tmp * 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

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

<<<<<<< HEAD
int	get_color( mlx_texture_t *tex, int x, int y)
{
	uint8_t	*pixels;
	int		color;

	pixels = tex->pixels;
	color = (pixels[(y * tex->width * 4) + (4 * x) + 0] << 24);
	color += (pixels[(y * tex->width * 4) + (4 * x) + 1] << 16);
	color += (pixels[(y * tex->width * 4) + (4 * x) + 2] << 8);
=======
int get_color( mlx_texture_t *tex, int x, int y)
{
	uint8_t *pixels;
	int color;
	
	
	pixels = tex->pixels;
	color  = (pixels[(y * tex->width * 4) + (4 * x) + 0]<< 24);
	color += (pixels[(y * tex->width * 4) + (4 * x) + 1]<< 16);
	color +=(pixels[(y * tex->width * 4) + (4 * x) + 2]<< 8);
>>>>>>> 6b4267c80c8df90569f31d36df8eb47b33624538
	color += (pixels[(y * tex->width * 4) +(4 * x) + 3]);
	return (color);
}

<<<<<<< HEAD
void	draw_wall_ray(t_draw *dr, t_data *data, t_ray *ray, mlx_texture_t *tex)
{
	while (dr->i++ < dr->y_0 + ray->wall_height)
	{
		if (dr->i < data->win_h && dr->i > 0)
		{
			dr->top_dist = dr->y + (dr->strip_height / 2)
				- ((float)data->win_h / 2);
			ray->y_offset = dr->top_dist * ((float)tex->height
					/ ray->wall_height);
			ray->y_offset = abs(ray->y_offset);
			dr->color = get_color(tex, ray->x_offset, ray->y_offset);
			mlx_put_pixel(data->mlx_im, ray->i, dr->y, dr->color);
		}
		dr->y++;
	}
}

void	draw_strip(t_data *data, t_ray *ray)
{
	mlx_texture_t	*tex;
	t_draw			draw;
=======
void	draw_strip(t_data* data, t_ray *ray)
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
	while (draw.i++ < draw.y_0 + ray->wall_height)
	{
		if (draw.i < data->win_h && draw.i > 0)
		{
			draw.top_dist = draw.y + (draw.strip_height / 2) - ((float)data->win_h / 2);
			ray->y_offset = draw.top_dist * ((float)tex->height / ray->wall_height);
			ray->y_offset = abs(ray->y_offset);
			draw.color = get_color(tex, ray->x_offset, ray->y_offset);
			mlx_put_pixel(data->mlx_im, ray->i, draw.y, draw.color);
		}
		draw.y++;
	}
	while (draw.y < data->win_h)
		mlx_put_pixel(data->mlx_im, ray->i, draw.y++, data->floor_color);

	ray->x_offset = 0;
>>>>>>> 6b4267c80c8df90569f31d36df8eb47b33624538

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

//functions to count the distance between the player and the wall
void	set_distance(t_data *data, t_wall *wall)
{
	wall->vert_distance = (data->height * data->width) * data->sq_dim;
	wall->horz_distance = (data->height * data->width) * data->sq_dim;
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
		ray->dist_proj_plan = (data->win_w / 2) * tan(data->fov / 2);
		ray->wall_height = (data->sq_dim / ray->lenght) * ray->dist_proj_plan;
		ray->x_offset = ((float)data->txt->width / data->sq_dim)
			* (wall->horz_x % data->sq_dim);
		draw_strip(data, ray);
<<<<<<< HEAD
		return (1);
=======
		return 1;
>>>>>>> 6b4267c80c8df90569f31d36df8eb47b33624538
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
		ray->dist_proj_plan = (data->win_w / 2) * tan(data->fov / 2);
		ray->wall_height = (data->sq_dim / ray->lenght) * ray->dist_proj_plan;
		ray->x_offset = ((float)data->txt->width / data->sq_dim)
<<<<<<< HEAD
			* (wall->vert_y % data->sq_dim);
=======
			*( wall->vert_y % data->sq_dim);
>>>>>>> 6b4267c80c8df90569f31d36df8eb47b33624538
		draw_strip(data, ray);
		return (1);
	}
	return (0);
}

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
		normalize_angle(&data->p_angle);
		wall.horz_found_wall = false;
		wall.vert_found_wall = false;
		horizontal(data, ray.angle, &wall);
		verticall(data, ray.angle, &wall);
		set_distance(data, &wall);
		project_horz_ray(data, &wall, &ray);
		project_vert_ray(data, &wall, &ray);
		ray.i++;
		ray.angle += ray.step;
	}
}

void	draw(void *dt)
{
	t_data	*data;

	data = (t_data *) dt;
	mouvements(data);
	wall_projection(data);
}

void	vue_angle(t_data *param)
{
	int	y;
	int	x;

	x = param->ppos_x;
	y = param->ppos_y;

	// y = 0;
	// param->p_angle = 1;
	// while (param->mat[y] != NULL)
	// {
	// 	x = 0;
	// 	while (param->mat[y][x] != '\0')
	// 	{
			if (param->mat[y][x] == 'N')
				param->p_angle = M_PI_2 * 3;
			else if (param->mat[y][x] == 'E')
				param->p_angle = 0;
			else if (param->mat[y][x] == 'S')
				param->p_angle = M_PI_2;
			else if (param->mat[y][x] == 'W')
				param->p_angle = M_PI;
	// 		if (param->p_angle != 1)
	// 		{
				param->ppos_y = (y * param->sq_dim) + (param->sq_dim / 2);
				param->ppos_x = (x * param->sq_dim) + (param->sq_dim / 2);
	// 			return ;
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }
	printf("angle = %f\n", param->p_angle);
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
	data = NULL;
	exit(exit_code);
}

void	initialize_data(t_data *data, t_param *params)
{
	data->mat = params->map_mehdi;
	data->sq_dim = 100;
	data->p_speed = 4;
	data->p_rad = data->p_speed + 1;
	data->rotation_angle = 1;
	data->fov = 60 * (M_PI / 180);
	data->win_w = 1600;
	data->win_h = 800;
	data->txt_e = mlx_load_png(params->EA);
	data->txt_w = mlx_load_png(params->WE);
	data->txt_n = mlx_load_png(params->NO);
	data->txt_s = mlx_load_png(params->SO);
	if (!data->txt_e || !data->txt_w || !data->txt_n || !data->txt_s)
		free_data(data, 1);
<<<<<<< HEAD
	data->floor_color = params->rgb_F;
	data->ceiling_color = params->rgb_C;
	data->width = (params->long_line - 1) * data->sq_dim;
	data->height = (params->height_map - 1) * data->sq_dim;
=======

	data->floor_color = 0x7a776eff;
	data->ceiling_color = 0x000000ff;
	data->width =(data->width - 1) * data->sq_dim;
	data->height = (data->height - 1) * data->sq_dim;
>>>>>>> 6b4267c80c8df90569f31d36df8eb47b33624538
	data->num_rays = data->win_w;
	data->ppos_x = params->x_player;
	data->ppos_y = params->y_player;
	printf("-------------------\n");
	printf("floor = %d\n", data->floor_color);
	printf("ceiling = %d\n", data->ceiling_color);
	printf("width = %lu\n", params->long_line);
	printf("height = %d\n", params->height_map);
	printf("x = %f\n", data->ppos_x);
	printf("y = %f\n", data->ppos_y);
}

int	display(t_param *params)
{
	t_data	data;
	
	ft_bzero(&data, sizeof(t_data));
	// if (ac != 2)
	// 	return (1);
	// lire_map(&data, av[1]);
	// len_mapp(&data);
	initialize_data(&data, params);
	vue_angle(&data);
	data.mlx_in = mlx_init(data.win_w, data.win_h, "cub3D", 0);
	if (!data.mlx_in)
		free_data(&data, 1);
	data.mlx_im = mlx_new_image(data.mlx_in, data.win_w, data.win_h);
	if (!data.mlx_im)
		free_data(&data, 1);
	mlx_image_to_window(data.mlx_in, data.mlx_im, 0, 0);
	mlx_loop_hook(data.mlx_in, draw, &data);
	mlx_loop(data.mlx_in);
	return (0);
}
