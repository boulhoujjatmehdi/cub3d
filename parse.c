/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:07:58 by rarraji           #+#    #+#             */
/*   Updated: 2023/10/19 20:09:59 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **read_file(t_param *var, char *av1)
{
	int fd;
	int i;
	int j;
	char *c;

	j = 0;
	i = 0;
	fd = open(av1, O_RDONLY);
	while (1)
	{
		c = get_next_line(fd);
		i++;
		free(c);
		if (!c)
			break;
	}
	close(fd);
	fd = open(av1, O_RDONLY);
	var->map = (char **)malloc(sizeof(char *) * (i + 1));
	var->map_trim = (char **)malloc(sizeof(char *) * (i + 1));
	while (i--)
	{
		var->map[j] = get_next_line(fd);
		var->map_trim[j] = ft_strtrim(var->map[j], " ");
		j++;
	}
	var->map[j] = 0;
	return (var->map);
}

void remplir_var(char *line, t_param *var)
{
	// printf("here\n");
	if (line[0] == 'W')
		var->WE = ft_substr(line, 0, ft_strlen(line));
	else if (line[0] == 'S')
		var->SO = ft_substr(line, 0, ft_strlen(line));
	else if (line[0] == 'N')
		var->NO = ft_substr(line, 0, ft_strlen(line));
	else if (line[0] == 'E')
		var->EA = ft_substr(line, 0, ft_strlen(line));
	else if (line[0] == 'F')
		var->F = ft_substr(line, 0, ft_strlen(line));
	else
		var->C = ft_substr(line, 0, ft_strlen(line));
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

int check_par(t_param *var)
{
	int i;
	int j;
	int cnt;
	int len;
	char *tab[7] = {"NO", "EA", "SO", "WE", "F", "C"};

	i = -1;
	cnt = 0;
	while (var->map_trim[++i])
	{
		if (var->map_trim[i][0] == '\n')
			continue;
		j = 0;
		// printf("*-->%d\n", ft_strlen(tab[5]));		
		// printf("*-->%d\n", ft_strlen(tab[1]));		
		while (tab[j])
		{
			if (ft_strlen2(tab[j]) > ft_strlen2(var->map_trim[i]))
				len = ft_strlen2(tab[j]);
			else
				len = ft_strlen2(var->map_trim[i]);
			if (ft_strncmp(var->map_trim[i], tab[j], len) == 0)
			{
				// printf("-->%s\n", tab[j]);	
				cnt++;
				remplir_var(var->map_trim[i], var);
				break;
			}
			j++;
		}
	}
		if(cnt == 6)
			return(0);
		return(1);	
	
}

int ft_search_player(t_param *vars)
{
	int x;
	int y;
	int cnt;
	int i;

	y = vars->first_line;
	cnt = 0;
	i = 0;
	vars->last_map = (char **)malloc(sizeof(char *) * (vars->last_line - vars->first_line + 1));
	while(vars->map[y])
	{
		vars->last_map[i] = ft_substr(vars->map[y], 0, ft_strlen(vars->map[y]));
		x = 0;
		while(vars->last_map[i][x])
		{
			if(vars->last_map[i][x] != 'N' && vars->last_map[i][x] != 'S' && vars->last_map[i][x] != 'E' 
				&& vars->last_map[i][x] != 'W' && vars->last_map[i][x] != ' ' && vars->last_map[i][x] != '1' && vars->last_map[i][x] != '0' && vars->last_map[i][x] != '\n')
				return(0);
			else if(vars->last_map[i][x] == 'N' || vars->last_map[i][x] == 'S' || vars->last_map[i][x] == 'E' || vars->last_map[i][x] == 'W')
			{
				vars->x_player = x;
				printf("x = %d\n", vars->x_player);
				vars->y_player = i;
				printf("y = %d\n", vars->y_player);
				cnt++;
			}
				x++;
		}
		y++;
		i++;
	}
	vars->last_line = i - 1;
	return(cnt);
}




int ft_cnt_param(t_param *var)
{
	int i;
	int cnt;
	int tmp = 0;

	i = -1;
	cnt = 0;
	while (var->map_trim[++i])
	{
		if (var->map_trim[i][0] == 'W' || var->map_trim[i][0] == 'S' || var->map_trim[i][0] == 'N' || var->map_trim[i][0] == 'E' || var->map_trim[i][0] == 'F' || var->map_trim[i][0] == 'C')
			cnt++;
		else if (var->map_trim[i][0] == '1')
		{
			if(tmp == 0)
			{
				var->first_line = i;
				tmp = 1;
			}
			printf("%d\n", var->first_line);
			if (cnt < 6)
			{
				printf("HERE 2\n");	
				return (1);
			}
			var->last_line = i;
		}
		else if (var->map_trim[i][0] != '\n' && var->map_trim[i][0] != '1')
		{
			printf("HERE 3\n");	
			return (1);
		}
		else
			continue;
	}
	printf("last :%d\n", var->last_line);
	if (cnt == 6)
		return (0);
	return (1);
}

int check_string_is_digit(char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '\n')
	{
		if(ft_isdigit(str[i]) == 0)
		{
		printf("HERE8\n");
		return(1);
		}
		i++;	
	}
	return(0);
}

int check_range(char **color)
{
	int i;
	int nb;

	i = 0;
	while(color[i])
	{
		nb = ft_atoi(color[i]);
		// printf("--->%d\n", nb);
		if(nb > 255 || nb < 0)
		{
			printf("HERE7\n");
			return(1);
		}
		i++;	
	}
	return(0);
}


int ft_check_is_digit(char *color)
{
	char **cheak;
	int i;
	// printf("'%s'\n", color);
	i = 0;
	cheak = ft_split(color, ',');
	while (cheak[i])
		i++;
	if(i != 3)
		return(1);
	i = 1;	
	while(cheak[i])
	{
		if(check_string_is_digit(cheak[i]))
		{
			printf("HERE5\n");
			return(1);
		}
		i++;
	}
	if(check_range(cheak))
	{
		printf("HERE6\n");
		return(1);
	}
	return(0);
	
}

int ft_check_segv(int y_player, size_t x_player, t_param *vars)
{
	if (y_player > vars->last_line || y_player < 0)
		return(0);
	if(ft_strlen(vars->last_map[y_player]) < x_player)
		return(0);	
	return(1);	
}


int	ft_valid_path(int *i, int y_player, int x_player,t_param *vars)
{
	// printf("xx==%d\n", x_player);
	// printf("yy==%d\n", y_player);
	if (vars->last_map[y_player][x_player] == ' ' || vars->last_map[y_player][x_player] == '\n')
		(*i)++;
	vars->last_map[y_player][x_player] = 'X';
	if (ft_check_segv(y_player - 1, x_player, vars) && (vars->last_map[y_player - 1][x_player] == '0' || vars->last_map[y_player - 1][x_player] == ' ' || vars->last_map[y_player - 1][x_player] == '\n'))
		ft_valid_path(i, y_player - 1, x_player, vars);
	if (ft_check_segv(y_player + 1, x_player, vars) && (vars->last_map[y_player + 1][x_player] && (vars->last_map[y_player + 1][x_player] == '0' || vars->last_map[y_player + 1][x_player] == ' ' || vars->last_map[y_player + 1][x_player] == '\n')))
		ft_valid_path(i, y_player + 1, x_player, vars);
	if (ft_check_segv(y_player, x_player - 1, vars) && (vars->last_map[y_player][x_player - 1] == '0' || vars->last_map[y_player][x_player - 1] == ' ' || vars->last_map[y_player + 1][x_player] == '\n'))
		ft_valid_path(i, y_player, x_player - 1, vars);
	if (ft_check_segv(y_player, x_player + 1, vars) && (vars->last_map[y_player][x_player + 1] == '0' || vars->last_map[y_player][x_player + 1] == ' ' || vars->last_map[y_player + 1][x_player] == '\n'))
		ft_valid_path(i, y_player, x_player + 1, vars);
	return (*i);
}

void ft_ptrint_map(t_param *vars)
{
	int i = 0;
	// int j = 0;
	// while(vars->map_trim[i])
	// {
	// 	printf("%d-->%s", i, vars->map_trim[i]);
	// 	i++;
	// }
	// printf("\n-------------------\n");
	i = 0;
	while(vars->last_map[i])
	{
		printf("%d-->%s", i, vars->last_map[i]);
		i++;
	}
}


int check_color(t_param *vars)
{
	char **check;
	char **check1;
	int i;
	int j;

	i = 0;
	j = 0 ;
	
	if(vars->C[ft_strlen(vars->C)] == ',' || !ft_isdigit(vars->C[ft_strlen(vars->C) - 2])
		||vars->F[ft_strlen(vars->F)] == ',' || !ft_isdigit(vars->F[ft_strlen(vars->F) - 2]))
			{
				printf("HERE4\n");
				return(1);
			}
	check = ft_split(vars->C, ' ');
	if(ft_strncmp(check[0], "C" , 2) == 0) //hsb wach homa 2
		if(ft_check_is_digit(check[1]))
			{
				printf("HERE3\n");
				return(1);
			}
	while(check[i])
		i++;
	check1 = ft_split(vars->F, ' ');	
	// printf("'%s'\n", check1[0]);
	if(ft_strncmp(check1[0], "F" , 2) == 0) //hsb wach homa 2
		if(ft_check_is_digit(check1[1]))
			{
				printf("HERE2 \n");
				return(1);
			}
	while(check1[j])
		j++;
	if(i != 2 || j != 2)
	{
		printf("HERE1 \n");
		return(1);
	}
	return(0);
}
//--------------------------------------------------------------------------------------------------------//

int	check_first_last_line(t_param *vars)
{
	int	x;

	x = 0;
	while (vars->map[vars->first_line][x])
	{
		if(vars->map[vars->first_line][x] != '\n' && vars->map[vars->first_line][x] != '1' && vars->map[vars->first_line][x] != ' ')
			{
				printf("%d--->%c\n", vars->first_line ,vars->map[vars->first_line][x]);
				printf("HERE44\n");
				return(1);
			}
		x++;	
	}
	x = 0;
	while (vars->map[vars->last_line][x])
	{
		if(vars->map[vars->last_line][x] != '\n' && vars->map[vars->last_line][x] != '1' && vars->map[vars->last_line][x] != ' ')
			{
			printf("HERE33\n");
			return(1);
			}
		x++;	
	}
	return (0);
}
int check_jnob(t_param *vars)
{
	int	y;
	// int x;

	y = vars->first_line;
	while (y < vars->last_line)
	{
		if(vars->map[y][0] != '1' && vars->map[y][0] != ' ' && vars->map[y][0] != '\n')
			{
			printf("HERE11\n");
			return(1);
			}
		y++;	
	}
	y = vars->first_line;
	while (y < vars->last_line)
	{
		if(vars->map[y][ft_strlen(vars->map[y]) - 2] != '1' && vars->map[y][ft_strlen(vars->map[y]) - 2] != ' ' && vars->map[y][ft_strlen(vars->map[y]) - 2] != '\n')
			{
			printf("HERE22\n");
			return(1);
			}
		y++;	
	}
	return (0);
}


int main(int ac, char **av)
{
	char **c;
	int  i = 0;

	(void)ac;
	t_param param;
	// param.tab = {"NO", "EA", "SO", "WE", "F", "C"};
	c = read_file(&param, av[1]);
	if (ft_cnt_param(&param) || check_par(&param) || check_color(&param))
	{
		printf("EROOR 10 !!\n");
		// free;
		return (0);
	}
	if (check_first_last_line(&param) || check_jnob(&param) || ft_search_player(&param) != 1)
	{
		printf("EROOR 99 !!\n");
		// free;
		return (0);
	}
	ft_valid_path(&i, param.y_player, param.x_player, &param);
	ft_ptrint_map(&param);
	if(i != 0)
		printf("EROOR Soliix !!\n");

    
}
