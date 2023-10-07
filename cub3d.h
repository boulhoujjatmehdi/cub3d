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
# include "MLX42/Include/MLX42.h"


#include"stdio.h"



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

// typedef struct	s_data {
// }				t_data;

int		ft_printf(const char *str, ...);
int		ft_putchar(int c);
int		ft_putnbr(int n);
int		ft_putstr(char *s);
char	*get_next_line(int fd);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*read_line(int fd, char *str);
char	*p1_line(char *str);
char	*last_line(char *str);
int		ft_strchr(char *s, char c);
char	*ft_substr(char *s, int start, int len);
// void	print_map(t_data	img, t_vars *param);
void key_hook(t_vars *pr); 
int		ft_check_par(t_vars *param);
void	len_mapp(t_vars *param);
int		check_jnob(t_vars *param);
int		check_len(t_vars *param);
void	ft_fack_map(t_vars *param, char *av);
void	check_path(t_vars *param);
void	ft_cntcoin(t_vars *param);
int		ft_path(int *i, int k, int l, t_vars *param);
// int		check_mov(t_vars *param, int k, int l, int keycode);
int		ft_destroy(t_vars *param);
void	check_exect_player_exit(char c, int cnt, t_vars *param);
void	ft_chrp(t_vars *param);
int		check_av(char *av);
void	lire_map(t_vars *param, char *av);
int		ft_defpar(char c, t_vars *param);
void	ft_put(t_vars *param, void *img);
void	ft_init(t_vars *pr);
void	free_all_map(t_vars *param);







void DDA(t_vars *pr ,int X0, int Y0, int X1, int Y1);
int	print_map(t_vars *param);
void ft_draw_player(t_vars *param);
int	check_mov(t_vars *param, int k, int l);
// void ft_draw_pix(t_data	img, t_vars *param, int c);
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif