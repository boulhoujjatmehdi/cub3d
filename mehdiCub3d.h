/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mehdiCub3d.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:35:44 by eboulhou          #+#    #+#             */
/*   Updated: 2023/10/30 15:24:49 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEHDICUB3D_H
# define MEHDICUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/Include/MLX42.h"
# include "libft/libft.h"
# include "stdio.h"

enum e_direction
{
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4
};

char	*get_next_line(int fd);

typedef struct s_wall
{
	int		horz_found_wall;
	float	horz_distance;
	int		horz_x;
	int		horz_y;

	int		vert_found_wall;
	float	vert_distance;
	int		vert_x;
	int		vert_y;
	int		direction;
}	t_wall;

typedef struct s_data
{
	char			**mat;
	int				height;
	int				width;
	void			*mlx_in;
	void			*mlx_im;
	void			*mlx_wi;
	int				win_h;
	int				win_w;
	int				sq_dim;
	int				rotation_angle;
	int				p_rad;
	int				p_speed;
	float			ppos_x;
	float			ppos_y;
	float			p_angle;
	mlx_texture_t	*txt_n;
	mlx_texture_t	*txt_s;
	mlx_texture_t	*txt_e;
	mlx_texture_t	*txt_w;
	mlx_texture_t	*txt;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	float			fov;
	int				num_rays;
	float			mini_scale;
}t_data;

typedef struct s_ray
{
	float	x_inter;
	float	y_inter;
	float	x_stp;
	float	y_stp;
	int		is_up;
	int		is_left;
	float	next_touch_x;
	float	next_touch_y;
	float	check_x;
	float	check_y;
	int		i;
	int		j;
	float	angle;
	float	step;
	bool	test;
	float	lenght;
	float	dist_proj_plan;
	float	wall_height;
	int		x_offset;
	int		y_offset;
}t_ray;

typedef struct s_draw
{
	float	strip_height;
	int		y_0;
	int		y;
	int		i;
	int		y_offset;
	int		top_dist;
	int		color;
}t_draw;
#endif