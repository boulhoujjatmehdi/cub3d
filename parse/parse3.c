/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:07:58 by rarraji           #+#    #+#             */
/*   Updated: 2023/11/07 18:58:56 by rarraji          ###   ########.fr       */
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

int	ft_strlen2(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != ' ' && s[i] != '\0')
		i++;
	return (i);
}
