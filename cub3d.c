/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 5023/09/19 15:34:26 by rarraji           #+#    #+#             */
/*   Updated: 5023/10/06 10:12:14 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// -----------------------------------------------//
int check_mov(t_vars *param, int k, int l)
{
	if (param->c[k][l] == '1')
		return (0);
	return (1);
}

void key_hook(t_vars *pr)
{
	if (mlx_is_key_down(pr->init, MLX_KEY_LEFT))
		pr->angle -= (M_PI / 180) * 3;
	if (mlx_is_key_down(pr->init, MLX_KEY_RIGHT))
		pr->angle += (M_PI / 180) * 3;
	if (mlx_is_key_down(pr->init, MLX_KEY_W) && check_mov(pr, (int)(pr->y - 4) / 50, (int)(pr->x) / 50))
	{
		pr->x += cosf(pr->angle);
		pr->y += sin(pr->angle);
	}
	else if (mlx_is_key_down(pr->init, MLX_KEY_S) && check_mov(pr, (int)(pr->y + 4) / 50, (int)(pr->x) / 50))
	{
		pr->x -= cosf(pr->angle);
		pr->y -= sinf(pr->angle);
	}
	else if (mlx_is_key_down(pr->init, MLX_KEY_A) && check_mov(pr, (int)(pr->y) / 50, (int)(pr->x - 4) / 50))
	{
		pr->x -= cosf(pr->angle + 90 * (M_PI / 180));
		pr->y -= sinf(pr->angle + 90 * (M_PI / 180));
	}
	else if (mlx_is_key_down(pr->init, MLX_KEY_D) && check_mov(pr, (int)(pr->y) / 50, (int)(pr->x + 4) / 50))
	{
		pr->x += cosf(pr->angle + 90 * (M_PI / 180));
		pr->y += sinf(pr->angle + 90 * (M_PI / 180));
	}
	else if (mlx_is_key_down(pr->init, MLX_KEY_Q))
		exit(1);
}

void len_mapp(t_vars *param)
{
	int k;
	int l;

	k = -1;
	l = 0;
	param->lenk = 0;
	param->lenl = 0;
	while (param->c[++k])
	{
		if (l == 0)
		{
			while (param->c[k][l] != '\0')
			{
				param->lenl++;
				l++;
			}
			param->lenl--;
		}
		param->lenk++;
	}
}

void lire_map(t_vars *param, char *av)
{
	int fd;
	int i;
	int j;
	char *c;

	j = 0;
	i = 0;
	fd = open(av, O_RDONLY);//TODO: PROTECT av
	while (1)
	{
		c = get_next_line(fd);
		i++;
		free(c);
		if (!c)
			break; //TODO: SEGV: MOVE THIS UP IT CAN CAUSE A SEGV
	}
	close(fd);
	fd = open(av, O_RDONLY);
	param->c = (char **)malloc(sizeof(char *) * (i + 1));
	while (i--)
	{
		param->c[j] = get_next_line(fd);
		j++;
	}
	param->c[j] = 0;
}

void ft_draw_pix(t_vars *param, int y, int x, int c)
{
	int i, j;
	i = 0;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			if (c == 1)
				mlx_put_pixel(param->img, x + i, y + j, 0x00FFFff);
			else
				mlx_put_pixel(param->img, x + i, y + j, 0x000000FF);
			if ((x + i) % 50 == 0 || (y + j) % 50 == 0)
			{
				mlx_put_pixel(param->img, x + i, y + j, 0x00FF00f0);
			}
			j++;
		}
		i++;
	}
}

void ft_draw_player(t_vars *param)
{
	int i, j;
	i = -4;
	while (i < 4)
	{
		j = -4;
		while (j < 4)
		{
			mlx_put_pixel(param->img, param->x + i, param->y + j, 0x00FF00ff);
			j++;
		}
		i++;
	}
	
	// DDA(param, param->x, param->y, end_x, end_y);
	float var_angle = param->angle - M_PI / 6;
	while (var_angle < param->angle +  M_PI / 6)
	{
		float end_x = param->x + (cosf(var_angle) * 50);
		float end_y = param->y + (sinf(var_angle) * 50);
		DDA(param, param->x, param->y, end_x, end_y);
		var_angle += M_PI / 360;
	}
	// for (int n = 0; n <= 0; n++) 
	// {
	// 	for (int m = 0; m <= 30; m++) 
	// 	{
	// 		DDA(param, param->x, param->y, end_x + m * 2, end_y + n);
	// 	}
  	// }
	// for (int n = -1; n < 0; n++) 
	// {
	// 	for (int m = -30; m < 0; m++) 
	// 	{
	// 		DDA(param, param->x, param->y, end_x + m * 2, end_y + n);
	// 	}
  	// }
	// DDA(param, param->x, param->y, end_x + 17, end_y + 3);
}

int print_map(t_vars *param)
{

	int x, y;

	y = 0;
	while (param->c[y] != NULL)
	{
		x = 0;
		while (param->c[y][x] != '\0')
		{
			ft_draw_pix(param, y * 50, x * 50, 0);
			if (param->c[y][x] == '1')
				ft_draw_pix(param, y * 50, x * 50, 1);
			if (param->c[y][x] == 'S' && !param->x && !param->y)
			{
				param->x = x * 50 + (50 / 2);
				param->y = y * 50 + (50 / 2);
			}
			x++;
		}
		y++;
	}
	return 0;
}

void DDA(t_vars *pr ,int X0, int Y0, int X1, int Y1)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;
  
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
    float X = X0;
    float Y = Y0;
    while (1) {
				// printf("was here %f - %f \n",(X - 4)/50, (Y - 4)/50);
			if (X < 1900 && Y < 1000)
			{
				// printf("========(%s)\n", pr->c[5]);
				if (pr->c[(int)(Y - 1)/50][(int)(X - 1)/50] == '1')
					break;
					mlx_put_pixel(pr->img, X, Y, 0x00FF0000ff);
			// sleep(2);
			}
			else 
				break;
				// if(check_mov(pr, (int)(X) / 50, (int)(Y) / 50) == 0)	
				// 	break;
        X += Xinc;
        Y += Yinc;
    }
}

void draw(void *t)
{
	t_vars *pr;

	pr = (t_vars *)t;
	print_map(pr);
	ft_draw_player(pr);
	key_hook(pr);
}

void vue_angle(t_vars *param)
{
	int y = 0;
	int x;
	while (param->c[y] != NULL)
	{
		x = 0;
		while (param->c[y][x] != '\0')
		{
			if(param->c[y][x] == 'N')
				param->angle = 0;
			else if(param->c[y][x] == 'W')
				param->angle = M_PI * 3;
			else if(param->c[y][x] == 'E')
				param->angle = M_PI_2;
			else if(param->c[y][x] == 'S')
				param->angle = M_PI_2;
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
	(void)ac;
	// t_data	img;
	t_vars mlx;

	mlx.x = 0;
	mlx.y = 0;
	lire_map(&mlx, av[1]);
	len_mapp(&mlx);
	vue_angle(&mlx);
	mlx.init = mlx_init(1900, 1000, "cub3D", 0);
	mlx.img = mlx_new_image(mlx.init, 1900, 1000);

	mlx_image_to_window(mlx.init, mlx.img, 0, 0);
	mlx_loop_hook(mlx.init, draw, &mlx);
	mlx_loop(mlx.init);
	
}


// int     init_image(t_vars *pr,t_image *img, int height, int width)
// {
//     img->ptr = mlx_new_image(pr->init, height, width);
//     if (img->ptr == NULL)
//         return (1);
//     img->height = height;
//     img->width = width;--
//     img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
//     return 0;
// }