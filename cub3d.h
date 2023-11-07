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

#ifndef SO_LONG_H
# define SO_LONG_H

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


#include"stdio.h"

typedef struct s_param
{
		char **tab;
		char **map_trim;
		char **map;
		char **last_map;
		char **map_mehdi;
		int rgb_F;
		int rgb_C;
		char *NO;
		char *SO;
		char *WE;
		char *EA;
		char *F;
		char *C;
		int		first_line;
		int		last_line;
		int		x_player;
		int		y_player;
		int 	first_nl;
		int		height_map;
		// char *tab[7];
		size_t long_line;
}		t_param;

typedef struct s_image
{
		void		*ptr;
		void    	*addr;
		int			height;
		int     	width;
		int			bits_per_pixel;
		int     	line_length;
		int     	endian;
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
	//lenk->height_of_map
	int			lenk;
	//lenk->width_of_map
	int			lenl;
	int			fake_coin;
	int			les_pas;
	void		*door;
	void		*player;
	void		*hit;
	void		*bacg;
	void		*makla;
	float		angle;
	/// ////////
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

}				t_vars;


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

typedef struct s_check
{
	int i;
	char **spl;
	char *str;
	int check;
	int err;
	int tmp;
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

int		ft_printf(const char *str, ...);
int		ft_putchar(int c);
int		ft_putnbr(int n);
int		ft_putstr(char *s);
char	*get_next_line(int fd);
// int		ft_strlen(char *s);
// char	*ft_strjoin(char *s1, char *s2);
char	*read_line(int fd, char *str);
char	*p1_line(char *str);
char	*last_line(char *str);
int		ft_strchr1(char *s, char c);
// char	*ft_strchr1(char *s, int c);
// char	*ft_substr(char *s, int start, int len);
// void	print_map(t_data	img, t_vars *param);
void 	key_hook(t_vars *pr); 
int		ft_check_par(t_vars *param);
// void len_mapp(t_data *data);
// int		check_jnob(t_vars *param);
int		check_len(t_vars *param);
void	ft_fack_map(t_vars *param, char *av);
void	check_path(t_vars *param);
void	ft_cntcoin(t_vars *param);
// int		ft_path(int *i, int k, int l, t_vars *param);
// int		check_mov(t_vars *param, int k, int l, int keycode);
int		ft_destroy(t_vars *param);
void	check_exect_player_exit(char c, int cnt, t_vars *param);
void	ft_chrp(t_vars *param);
int		check_av(char *av);
// void lire_map(t_data *data, char *av);
int		ft_defpar(char c, t_vars *param);
void	ft_put(t_vars *param, void *img);
void	ft_init(t_vars *pr);
// void	free_all_map(t_vars *param);







int DDA(t_vars *pr ,int X0, int Y0, int X1, int Y1);
int	print_map(t_vars *param);
void ft_draw_player(t_vars *param);
int	check_mov(t_vars *param, int k, int l);
void draw_3d(int dst, int x , t_vars *param);
// void ft_draw_pix(t_data	img, t_vars *param, int c);
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int remplir_var(char *line ,t_param *var);
int	ft_strlen1(char *s);
char	*ft_strjoin1(char *s1, char *s2);
int	ft_strchr1(char *s, char c);
char	*ft_substr1(char *s, int start, int len);
int	check_first_last_line(t_param *vars);
int check_jnob(t_param *vars);
int ft_search_player(t_param *vars);
int	ft_valid_path(int *i, int y_player, int x_player,t_param *vars);


int display(t_param *vars, t_data *data);
void    free_all_map(char **vars);
int ft_cnt(char **str);


#endif