/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:43:35 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/07 18:59:58 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_mehdi(t_param *vars)
{
	int	i;
	int	dec;

	i = 0;
	while (vars->last_map[i])
		i++;
	vars->map_mehdi = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (vars->last_map[++i])
	{
		vars->map_mehdi[i] = malloc(vars->long_line + 2);
		dec = vars->long_line;
		vars->map_mehdi[i][0] = '1';
		while (dec)
		{
			vars->map_mehdi[i][dec] = '1';
			dec--;
		}
		if (vars->map_mehdi[i + 1] != NULL)
			vars->map_mehdi[i][vars->long_line] = '\n';
		vars->map_mehdi[i][vars->long_line + 1] = '\0';
	}
	vars->map_mehdi[i] = 0;
	ft_change(vars);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	exist_file(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nfile not exist\n");
		exit(1);
	}
}

int	check_av(char *av)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	i = 0;
	s = ".ber";
	exist_file(av);
	while (av[i])
		i++;
	i = i - 4;
	while (av[i])
	{
		if (s[j] == av[i])
		{
			j++;
			i++;
		}
		else
		{
			ft_putstr_fd("Error\n", 2);
			return (1);
		}
	}
	return (0);
}

void	free_all_map(char **vars)
{
	int	i;

	i = 0;
	if (!vars)
		return ;
	while (vars && vars[i])
	{
		free(vars[i]);
		vars[i] = NULL;
		i++;
	}
	free(vars);
}
