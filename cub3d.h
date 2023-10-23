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
		char **fack_map;
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
	//c->map
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



// --------------------------------------------//
typedef struct s_wall
{
    float horz_found_wall;
    float horz_distance;
    int horz_x;
    int horz_y;

    float vert_found_wall;
    float vert_distance;
    int vert_x;
    int vert_y;
} t_wall;

typedef struct s_data
{
    char    **mat;
    int     height;
    int     width;
    void*   mlx_in;
    void*   mlx_im;
    void*   mlx_wi;

    //window: height
    int     win_h;
    //window: width
    int     win_w;
    //square dimentions
    int     sq_dim;
    //player rotation angle
    int     rotation_angle;
    //player radius
    int     p_rad;;
    //player position x
    float   ppos_x;
    //player position y
    float   ppos_y;
    //player view angle
    double  p_angle;


    //raycasting
    //field of view
    float   fov;
    //number of rays
    int     num_rays;
    //minimap scale
    float   mini_scale;

}t_data;

// --------------------------------------------//

// typedef struct	s_data {
// }				t_data;

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
void key_hook(t_vars *pr); 
int		ft_check_par(t_vars *param);
void len_mapp(t_data *data);
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
void lire_map(t_data *data, char *av);
int		ft_defpar(char c, t_vars *param);
void	ft_put(t_vars *param, void *img);
void	ft_init(t_vars *pr);
void	free_all_map(t_vars *param);







int DDA(t_vars *pr ,int X0, int Y0, int X1, int Y1);
int	print_map(t_vars *param);
void ft_draw_player(t_vars *param);
int	check_mov(t_vars *param, int k, int l);
void draw_3d(int dst, int x , t_vars *param);
// void ft_draw_pix(t_data	img, t_vars *param, int c);
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);








void remplir_var(char *line ,t_param *var);
int	ft_strlen1(char *s);
char	*ft_strjoin1(char *s1, char *s2);
int	ft_strchr1(char *s, char c);
char	*ft_substr1(char *s, int start, int len);
int	check_first_last_line(t_param *vars);
int check_jnob(t_param *vars);
int ft_search_player(t_param *vars);
int	ft_valid_path(int *i, int y_player, int x_player,t_param *vars);


#endif