/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:45:36 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/07 19:06:06 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_color(char *str, uint32_t *store_color)
{
	char	**tmp;

	tmp = ft_split(str, ',');
	if (mat_lenght(tmp) == 3 && cnt_comma(str))
	{
		if (myatoi(tmp[0]) == -1 || myatoi(tmp[1]) == -1 || \
			myatoi(tmp[2]) == -1)
		{
			free_matrice(tmp);
			return (1);
		}
		*store_color = create_rgb(myatoi(tmp[0]), myatoi(tmp[1]), \
		myatoi(tmp[2]));
	}
	else
	{
		free_matrice(tmp);
		return (1);
	}
	free_matrice(tmp);
	return (0);
}

int	set_texture(char *str, mlx_texture_t **store_texture)
{
	if (!str)
		return (1);
	*store_texture = mlx_load_png(str);
	if (!*store_texture)
		return (1);
	return (0);
}

int	enter_data(char **mat, t_data *data)
{
	if (mat[0][0] == 'C' && set_color(mat[1], &data->ceiling_color))
		return (1);
	else if (mat[0][0] == 'F' && set_color(mat[1], &data->floor_color))
		return (1);
	else if (mat[0][0] == 'N' && set_texture(mat[1], &data->txt_n))
		return (1);
	else if (mat[0][0] == 'E' && set_texture(mat[1], &data->txt_e))
		return (1);
	else if (mat[0][0] == 'W' && set_texture(mat[1], &data->txt_w))
		return (1);
	else if (mat[0][0] == 'S' && set_texture(mat[1], &data->txt_s))
		return (1);
	return (0);
}

int	my_error(int *err, int code, char *str, char **spl)
{
	*err = code;
	free(str);
	free_matrice(spl);
	return (1);
}

int	check_entries(t_check *c)
{
	if (c->spl && c->spl[0] && c->spl[0][0] == '1')
	{
		if (my_error(&c->err, c->err, c->str, c->spl) && c->check != 63)
			c->err = 1;
		return (1);
	}
	return (0);
}
