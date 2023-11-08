/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:54:28 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/08 08:44:48 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_color_textures(t_param *param, t_data *data)
{
	t_check	c;

	ft_bzero(&c, sizeof(t_check));
	while (param->map[c.i])
	{
		c.str = ft_strtrim(param->map[c.i++], "\n");
		c.spl = ft_split(c.str, ' ');
		if (check_entries(&c))
			break ;
		if (c.spl && c.spl[0] && c.spl[0][0] != '\0')
		{
			c.tmp = compare(c.spl[0], &c.check);
			if (c.tmp == 1 && mat_lenght(c.spl) != 2
				&& my_error(&c.err, 2, c.str, c.spl))
				return (1);
			else if (c.tmp == 1)
				if (enter_data(c.spl, data)
					&& my_error(&c.err, 4, c.str, c.spl))
					return (1);
			if (c.tmp == 2)
				c.err = 3;
		}
		my_error(&c.err, c.err, c.str, c.spl);
	}
	return (c.err);
}

void	free_tdata(t_data *data)
{
	if (data->txt_n)
		mlx_delete_texture(data->txt_n);
	if (data->txt_e)
		mlx_delete_texture(data->txt_e);
	if (data->txt_w)
		mlx_delete_texture(data->txt_w);
	if (data->txt_s)
		mlx_delete_texture(data->txt_s);
}

int	parse_color(t_param *param, t_data *data)
{
	int	err;

	err = set_color_textures(param, data);
	if (err)
	{
		ft_putstr_fd("Error\nargs/textures error\n", 2);
		free_tdata(data);
		ft_bzero(data, sizeof(t_data));
		return (1);
	}
	return (0);
}

int	main_2(t_param *param, t_data	*data)
{
	if (parse_color(param, data))
	{
		free_matrice(param->map);
		free_matrice(param->map_trim);
		return (1);
	}
	ft_cnt_param(param);
	if (check_first_last_line(param) || check_jnob(param) || \
		ft_search_player(param) != 1 || ft_check_space(param))
	{
		free_matrice(param->map_trim);
		free_matrice(param->map);
		free_matrice(param->last_map);
		free_tdata(data);
		ft_putstr_fd("Error\nmap_error\n", 2);
		return (1);
	}
	map_mehdi(param);
	free_matrice(param->map);
	free_matrice(param->map_trim);
	free_matrice(param->last_map);
	display(param, data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_param	param;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nargs error\n", 2);
		return (1);
	}
	ft_bzero(&param, sizeof(t_param));
	ft_bzero(&data, sizeof(t_data));
	if (check_av(av[1]))
		return (0);
	if (read_file(&param, av[1]) == NULL)
	{
		free_matrice(param.map);
		free_matrice(param.map_trim);
		return (1);
	}
	if (main_2(&param, &data) == 1)
		return (1);
	return (0);
}
