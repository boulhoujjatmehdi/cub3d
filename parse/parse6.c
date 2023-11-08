/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:44:29 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/08 08:23:49 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mat_lenght(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
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

void	free_matrice(char **matrice)
{
	int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}

int	cnt_comma(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == ',')
			cnt++;
		i++;
	}
	if (cnt == 2)
		return (1);
	return (0);
}

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
