/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:59:44 by rarraji           #+#    #+#             */
/*   Updated: 2023/09/17 22:54:40 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <math.h>
# include "./libft/libft.h"
# include "MLX42/Include/MLX42.h"
# include "stdio.h"

typedef struct s_param
{
	char	**map_trim;
	char	**map;
	char	**last_map;
	char	**map_mehdi;
	int		first_line;
	int		last_line;
	int		x_player;
	int		y_player;
	int		first_nl;
	int		height_map;
	size_t	long_line;
}		t_param;

typedef struct s_image
{
	void		*ptr;
	void		*addr;
	int			height;
	int			width;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}		t_image;

typedef struct s_vars
{
	mlx_t		*init;
	mlx_image_t	*wind;
	float		x;
	float		y;
	int			i;
	int			j;
	char		**c;
	char		**fack_c;
	int			k;
	int			l;
	int			coin;
	int			lenk;
	int			lenl;
	int			fake_coin;
	int			les_pas;
	void		*door;
	void		*player;
	void		*hit;
	void		*bacg;
	void		*makla;
	float		angle;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

}				t_vars;

enum e_direction
{
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4
};

char	*get_next_line(int fd);

typedef struct s_check
{
	int		i;
	char	**spl;
	char	*str;
	int		check;
	int		err;
	int		tmp;
}t_check;

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

//raycasting functions****************************************************
//data
void	initialize_data(t_data *data, t_param *params);
void	free_data(t_data *data, int exit_code);
void	normalize_angle(float *angle);
void	free_mat(char **mat);
void	vue_angle(t_data *param);
// movements 
void	move_player_left_right(t_data *pr);
void	move_player_forward_backward(t_data *pr);
void	rotate_player(t_data *pr);
void	mouvements(t_data *pr);
int		check_move(t_data *pr, float yl, float xl);
//checks
int		check_wall_at(t_data *param, double k, double l);
//projection 1
void	wall_projection(t_data *data);
void	horizontal(t_data *data, double ray_angle, t_wall *wall);
void	verticall(t_data *data, double ray_angle, t_wall *wall);
void	set_distance(t_data *data, t_wall *wall);
//projection 2
void	draw_wall_ray(t_draw *dr, t_data *data, t_ray *ray, mlx_texture_t *tex);
void	draw_strip(t_data *data, t_ray *ray);
int		project_horz_ray(t_data *data, t_wall *wall, t_ray *ray);
int		project_vert_ray(t_data *data, t_wall *wall, t_ray *ray);
int		get_color( mlx_texture_t *tex, int x, int y);
//projection 3
void	set_vert_intersections(t_data *data, t_ray *ray, double ray_angle);
void	set_ray_direction(t_ray *ray, double ray_angle);
void	set_horz_intersections(t_data *data, t_ray *ray, double ray_angle);
//raycasting functions****************************************************

//|------------------------PARCING---------------------------------|

char	*get_next_line(int fd);
int		ft_strlen1(char *s);
char	*ft_strjoin1(char *s1, char *s2);
int		ft_strchr1(char *s, char c);
char	*ft_substr1(char *s, int start, int len);
int		display(t_param *vars, t_data *data);
int		space_exist(char **map, int x, int y);
int		ft_check_space(t_param *vars);
void	check_long_line(t_param *vars);
int		ft_search_player_2(t_param *vars, int y, int i, int cnt);
int		ft_search_player(t_param *vars);
int		ft_cnt_param(t_param *var);
int		ft_cnt_line(char *av1);
char	**read_file(t_param *var, char *av1);
int		ft_strlen2(char *s);
int		chec_verg(char *str);
int		ft_cnt(char **str);
int		check_first_last_line(t_param *vars);
int		check_jnob(t_param *vars);
void	ft_change(t_param *vars);
void	map_mehdi(t_param *vars);
int		create_rgb(int r, int g, int b);
void	exist_file(char *av);
int		check_av(char *av);
void	free_all_map(char **vars);
int		compare(char *s1, int *check);
void	free_matrice(char **matrice);
int		mat_lenght(char **mat);
int		myatoi(const char *str);
int		cnt_comma(char *str);
int		set_color(char *str, uint32_t *store_color);
int		set_texture(char *str, mlx_texture_t **store_texture);
int		enter_data(char **mat, t_data *data);
int		my_error(int *err, int code, char *str, char **spl);
int		check_entries(t_check *c);
#endif