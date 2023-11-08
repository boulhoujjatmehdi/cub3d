/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:07:58 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/08 08:17:27 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_cnt_line(char *av1)
{
	int		i;
	int		fd;
	char	*c;

	i = 0;
	fd = open(av1, O_RDONLY);
	while (1)
	{
		c = get_next_line(fd);
		i++;
		free(c);
		if (!c)
			break ;
	}
	close(fd);
	return (i);
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

char	**read_file(t_param *var, char *av1)
{
	int	fd;
	int	i;
	int	j;

	j = -1;
	i = 0;
	i = ft_cnt_line(av1);
	fd = open(av1, O_RDONLY);
	var->map = (char **)malloc(sizeof(char *) * (i + 1));
	var->map_trim = (char **)malloc(sizeof(char *) * (i + 1));
	while (i--)
	{
		var->map[++j] = get_next_line(fd);
		var->map_trim[j] = ft_strtrim(var->map[j], " ");
	}
	var->map[j] = 0;
	var->map_trim[j] = 0;
	if (var->map[0] == NULL)
	{
		close(fd);
		ft_putstr_fd("Error\n.ber file error", 2);
		return (NULL);
	}
	close(fd);
	return (var->map);
}

int	ft_cnt_param(t_param *var)
{
	int	i;
	int	cnt;
	int	tmp;

	tmp = 0;
	i = -1;
	cnt = 0;
	var->first_line = 0;
	while (var->map_trim[++i])
	{
		if (ft_strchr("WSNEFC", var->map_trim[i][0]) != NULL)
			continue ;
		if (var->map_trim[i][0] == '1')
		{
			if (tmp == 0)
			{
				var->first_line = i;
				tmp = 1;
			}
			var->last_line = i;
		}
	}
	return (0);
}
