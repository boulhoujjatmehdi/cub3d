/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:04:25 by eboulhou          #+#    #+#             */
/*   Updated: 2023/11/08 08:26:24 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouvements(t_data *pr)
{
	rotate_player(pr);
	move_player_forward_backward(pr);
	move_player_left_right(pr);
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_ESCAPE))
		free_data(pr, 0);
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
