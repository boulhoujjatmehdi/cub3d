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

	j = 0;
	i = 0;
	i = ft_cnt_line(av1);
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
	var->map_trim[j] = 0;
	return (var->map);
}

// void remplir_var(char *line, t_param *var)
// {
// 	// printf("here\n");
// 	if (line[0] == 'W')
// 		var->WE = ft_substr(line, 0, ft_strlen(line));
// 	else if (line[0] == 'S')
// 		var->SO = ft_substr(line, 0, ft_strlen(line));
// 	else if (line[0] == 'N')
// 		var->NO = ft_substr(line, 0, ft_strlen(line));
// 	else if (line[0] == 'E')
// 		var->EA = ft_substr(line, 0, ft_strlen(line));
// 	else if (line[0] == 'F')
// 		var->F = ft_substr(line, 0, ft_strlen(line));
// 	else
// 		var->C = ft_substr(line, 0, ft_strlen(line));
// }

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
int	check_nl(char *s)
{
	int	i;

	if (s[ft_strlen(s) - 1] == '\n') 
		i = ft_strlen2(s)-1;
	else
		i = ft_strlen(s);

		// printf("s == [%s]\n", s);


		// ft_strtrim()
	return (i);
}

int	remplir_var(char *line, t_param *var)
{
	char	**split;

	split = ft_split(line, ' ');
	// printf("--->%d\n", ft_cnt(split));
	if(ft_cnt(split) != 2)
		return(1);
	if (line[0] == 'W')
		var->WE = ft_substr(split[1], 0, check_nl(split[1]));
	else if (line[0] == 'S')
		var->SO = ft_substr(split[1], 0, check_nl(split[1]));
	else if (line[0] == 'N')
		var->NO = ft_substr(split[1], 0, check_nl(split[1]));
	else if (line[0] == 'E')
		var->EA = ft_substr(split[1], 0, check_nl(split[1]));
	else if (line[0] == 'F')
		var->F = ft_substr(line, 0, ft_strlen(line));
	else
		var->C = ft_substr(line, 0, ft_strlen(line));
	// if(line[0] != 'C' && line[0] != 'F')
		free_all_map(split);
	return(0);	
}
int	check_line(char *s1, char *s2)
{
	int	len;

	len = 0;
	if (ft_strlen2(s1) > ft_strlen2(s2))
		len = ft_strlen2(s1);
	else
		len = ft_strlen2(s2);
	return (len);			
}
int	check_par(t_param *var)
{
	int	i;
	int	j;
	int	cnt;
	int	len;
	char	*tab[7] = {"NO", "EA", "SO", "WE", "F", "C"};

	i = -1;
	cnt = 0;
	while (var->map_trim[++i])
	{
		if (var->map_trim[i][0] == '\n')
			continue ;
		j = -1;
		while (tab[++j])
		{
			len = check_line(tab[j], var->map_trim[i]);
			if (ft_strncmp(var->map_trim[i], tab[j], len) == 0)
			{
				cnt++;
				if(remplir_var(var->map_trim[i], var) == 1)
					return(1);
				break ;
			}
		}
	}
	return (cnt);	
}

void	check_long_line(t_param *vars)
{
	int	i;

	vars->long_line = 0;
	i = 0;
	while (vars->last_map[i])
	{
		if (ft_strlen(vars->last_map[i]) > vars->long_line)
			vars->long_line = ft_strlen(vars->last_map[i]);
		i++;
	}
}

int	ft_search_player_2(t_param *vars, int y)
{
	int	cnt;
	int	x;
	int	i;

	cnt = 0;
	i = 0;
	while (vars->map[y])
	{
		vars->last_map[i] = ft_substr(vars->map[y], 0, ft_strlen(vars->map[y]));
		x = 0;
		while (vars->last_map[i][x])
		{
			if (ft_strchr("NSEW 10\n", vars->last_map[i][x]) == NULL)
				return (1);
			else if (ft_strchr("NSEW", vars->last_map[i][x]) != NULL)
			{
				vars->x_player = x;
				vars->y_player = i;
				cnt++;
			}
			x++;
		}
		y++;
		i++;
	}
	vars->last_map[i] = 0;
	vars->last_line = i - 1;
	check_long_line(vars);
	return (cnt);
}

int	ft_search_player(t_param *vars)
{
	int	y;
	int	cnt;

	cnt = 0;
	y = vars->first_line;
	vars->last_map = (char **)malloc(sizeof(char *) * \
		(vars->last_line - vars->first_line + 2));
	cnt = ft_search_player_2(vars, y);
	return (cnt);
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
			cnt++;
		else if (var->map_trim[i][0] == '1')
		{
			if (tmp == 0)
			{
				var->first_line = i;
				tmp = 1;
			}
			if (cnt < 6)
				return (1);
			var->last_line = i;
		}
		else if (var->map_trim[i][0] != '\n' && var->map_trim[i][0] != '1')
			return (1);
		else
			continue ;
	}
	return (cnt);
}

int	check_string_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\n')
		return (1);
	while (str[i] && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_range(char **color)
{
	int	i;
	int	nb;

	i = 0;
	while (color[i])
	{
		nb = ft_atoi(color[i]);
		if (nb > 255 || nb < 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_is_digit(char *color)
{
	char	**check1;
	char	**check;
	int		i;

	i = 0;
	check1 = ft_split(color, ' ');
	// if(ft_cnt(check1) != 1)
	// 	return (1);
	check = ft_split(check1[1], ',');
	// if(ft_cnt(check) != 1)
	// 	return (1);
	while (check[i])
		i++;
	// printf("this is i : %d\n", i);
	if (i != 3)
		return (1);
	i = 0;
	while (check[i])
	{
		// printf("--->'%s'\n", check[i]);
		if (check_string_is_digit(check[i]))
			return (1);
		i++;
	}
	if (check_range(check))
		return (1);
	free_all_map(check);
	free_all_map(check1);
	return (0);
}


int	space_exist(char **map, int x, int y)
{
	if (!(ft_strchr("NSWE01", map[y][x - 1])))
		return (1);
	if (!(ft_strchr("NSWE01", map[y][x + 1])))
		return (1);
	if (ft_strlen(map[y - 1]) <= (size_t)x || !(ft_strchr("NSWE01", map[y - 1][x])))
		return (1);
	if (ft_strlen(map[y + 1]) <= (size_t)x || !(ft_strchr("NSWE01", map[y + 1][x])))
		return (1);
	return (0);
}

int	ft_check_space(t_param *vars)
{
	int	x;
	int	y;
	int	check;

	y = 1;
	check = 0;
	while (vars->last_map && vars->last_map[y])
	{
		x = 0;
		while (vars->last_map[y][x])
		{
			if (!ft_strchr("NSWE01 \n", vars->last_map[y][x]))
				return (1);
			if (ft_strchr("NSWE0", vars->last_map[y][x]))
			{
				check = space_exist(vars->last_map, x, y);
				if (check == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	chec_verg(char *str)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			cnt++;
		i++;
	}
	if (cnt != 2)
		return (1);
	return (0);
}


int ft_cnt(char **str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}




int ft_check_lenght(char *s1, char *s2)
{
	char **check1;
	char **check2;

	check1 = ft_split(s1, ',');
	check2 = ft_split(s2, ',');
	// printf("%d\n", ft_cnt(check1));
	// printf("%d\n", ft_cnt(check2));
	if (ft_cnt(check1) != 3 || ft_cnt(check2) != 3)
		return (1);
	return (0);	
}


int	check_color(t_param *vars)
{
	// if(ft_check_lenght(vars->C, vars->F,))
	// 	return(1);
	if (chec_verg(vars->C) == 1 || chec_verg(vars->F) == 1)
		return (1);
	if (!ft_isdigit(vars->C[ft_strlen(vars->C) - 2]) || !ft_isdigit(vars->F[ft_strlen(vars->F) - 2]))
		return (1);

	if (ft_isdigit(vars->C[2]) == 0)
	{
		return (1);
	}
	if (ft_isdigit(vars->F[2]) == 0)
		return (1);
	if (ft_strncmp(vars->C, "C" , 1) == 0)
	{
		if (ft_check_is_digit(vars->C))
			return (1);
	} //hsb wach homa 2
	if (ft_strncmp(vars->F, "F" , 1) == 0) //hsb wach homa 2
		if (ft_check_is_digit(vars->F))
			return (1);
	return (0);
}
//--------------------------------------------------------------------------------------------------------//

int	check_first_last_line(t_param *vars)
{
	int	x;

	x = 0;
	while (vars->map[vars->first_line] && vars->map[vars->first_line][x])
	{
		if (ft_strchr("\n1 ", vars->map[vars->first_line][x]) == NULL)
			return (1);
		x++;
	}
	x = 0;
	while (vars->map[vars->last_line][x])
	{
		if (ft_strchr("\n1 ", vars->map[vars->last_line][x]) == NULL)
			return (1);
		x++;
	}
	return (0);
}
int	check_jnob(t_param *vars)
{
	int	y;

	y = vars->first_line;
	while (vars->map[y])
	{
		if (ft_strchr("1 ", vars->map[y][0]) == NULL && vars->map[y][0])
			return (1);
		y++;
	}
	y = vars->first_line;
	while (y < vars->last_line)
	{
		if (ft_strchr("1 \n", vars->map[y][ft_strlen(vars->map[y]) - 2]) == NULL)
			return (1);
		y++;
	}
	return (0);
}

void	ft_change(t_param *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->last_map[i])
	{
		j = 0;
		while (vars->last_map[i][j])
		{
			if (ft_strchr("0WSNE", vars->last_map[i][j]) != NULL)
				vars->map_mehdi[i][j] = vars->last_map[i][j];
			j++;
		}
		i++;
	}
	vars->height_map = i;
}

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
void search_rgb(char *str, int *rgb)
{
	char	**s2;
	char	*tmp;

	s2 = ft_split(str, ',');
	tmp = ft_substr(s2[2], 0, ft_strlen(s2[2]) - 1);
	*rgb = create_rgb(ft_atoi(s2[0]), ft_atoi(s2[1]), ft_atoi(tmp));
	free(tmp);
	free_all_map(s2);
}

void	exist_file(char *av)
{
	int	fd;
	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		printf("file not exist !!!\n");
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
			printf("Error CUB\n");
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
	while (vars[i])
	{
		free(vars[i]);
		vars[i] = NULL;
		i++;
	}
	free(vars);
}

void printf_map(t_param *vars)
{
	int i = 0;
	while(vars->map_mehdi[i])
	{
		// printf("%d ----> %s\n", i, vars->map_mehdi[i]);
		i++;	
	}
}

////////////////////////////////////////////////////////////////////////////////

int compare(char *s1, int *check)
{
	int tmp;

	tmp = *check;
	int bol;

	bol = 1;
	if(!ft_strncmp(s1, "C", 2) && bol++)
		*check = *check | 1;
	else if(!ft_strncmp(s1, "F", 2) && bol++)
		*check = *check | 2;
	else if(!ft_strncmp(s1, "NO", 3) && bol++)
		*check = *check | 4;
	else if(!ft_strncmp(s1, "EA", 3) && bol++)
		*check = *check | 8;
	else if(!ft_strncmp(s1, "SO", 3) && bol++)
		*check = *check | 16;
	else if(!ft_strncmp(s1, "WE", 3) && bol++)
		*check = *check | 32;
	if(bol != 1)
	{
		if(tmp == *check)
			return (2);	
		return(1);
	}
	return (0);
}


//function free_matrice 
void free_matrice(char **matrice)
{
	int i = 0;
	if(!matrice)
		return ;
	while(matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}
//function mat_lenght conts the lenght of the matrice
int mat_lenght(char **mat)
{
	int i = 0;
	while(mat[i])
		i++;
	return (i);
}
int	myatoi(const char *str)
{
	int		i;
	long	ret;
	int		neg;

	i = 0;
	ret = 0;
	neg = 1;
	// if(!str)
	// 	return (-1);//todo check for null string
	if (!ft_isdigit(str[i]))
		return (-1);
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + str[i] - 48;
		if (ret > 255)
			return (-1);
		i++;
	}
	if( str[i] && !ft_isdigit(str[i]))
		return (-1);
	return (ret);
}

int set_color(char *str, uint32_t *store_color)
{
	char **tmp;

	tmp = ft_split(str, ',');
	if(mat_lenght(tmp) == 3)
	{
		if(myatoi(tmp[0]) == -1 || myatoi(tmp[1]) == -1 || myatoi(tmp[2]) == -1)
		{
			free_matrice(tmp);
			return (1);
		}
		*store_color = create_rgb(myatoi(tmp[0]), myatoi(tmp[1]), myatoi(tmp[2]));
	}
	else
	{
		free_matrice(tmp);
		return (1);	
	}

		free_matrice(tmp);
	return (0);
}


int set_texture(char *str, mlx_texture_t **store_texture)
{
	// puts("texture");
	if(!str)
		return (1);
	*store_texture = mlx_load_png(str);
	if(!*store_texture)
		return (1);
	// puts("texture");
	return (0);
}
int  enter_data(char **mat, t_data *data)
{
	// char **tmp;

	if(mat[0][0] == 'C' && set_color(mat[1], &data->ceiling_color ))
		return (1);
	else if(mat[0][0] == 'F' && set_color(mat[1], &data->floor_color))
		return (1);
	else if(mat[0][0] == 'N' && set_texture(mat[1], &data->txt_n))
		return (1);
	else if(mat[0][0] == 'E' && set_texture(mat[1], &data->txt_e))
		return (1);
	else if(mat[0][0] == 'W' && set_texture(mat[1], &data->txt_w))
		return (1);
	else if(mat[0][0] == 'S' && set_texture(mat[1], &data->txt_s))
		return (1);
	return (0);
}

int set_color_textures(t_param *param , t_data *data)
{
	int i;
	char **spl;
	int check;
	int err;
	int tmp;

	i = 0;
	err = 0;
	check = 0;
	while(param->map[i])
	{
		param->map[i][ft_strlen(param->map[i]) - 1] = '\0';
		spl = ft_split(param->map[i], ' ');
		if(spl && spl[0] && spl[0][0] == '1')
		{
			if(check != 63)
				err = 1;
			free_matrice(spl);
			break ;
		}
		if(spl && spl[0] && spl[0][0] != '\0')
		{
			tmp = compare(spl[0], &check) ;
			if(tmp == 1 && mat_lenght(spl) != 2)
			{
				err = 2;
				free_matrice(spl);
				break ;
			}
			else if(tmp == 1) 
			{
				if(enter_data(spl , data))
				{
					err = 4;
					free_matrice(spl);
					break ;
				}
			}

			if(tmp == 2)
				err = 3;
		}
		free_matrice(spl);
		i++;
	}
	return err;
}

void free_tdata(t_data *data)
{
	if(data->txt_n)
		mlx_delete_texture(data->txt_n);
	if(data->txt_e)
		mlx_delete_texture(data->txt_e);
	if(data->txt_w)
		mlx_delete_texture(data->txt_w);
	if(data->txt_s)
		mlx_delete_texture(data->txt_s);
}

void mehdi_parse(t_param *param, t_data *data)
{
	int err;

	err = set_color_textures(param, data);
	if(err)
	{
		printf("Error (%d)\n", err);
		free_tdata(data);
		ft_bzero(data, sizeof(t_data));
		system("leaks CUB3D");
		exit(1);
	}
	// else


	(void)data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main1(int ac, char **av)
{
	t_data data;


	char **c;
	t_param param;
	(void)ac;
	ft_bzero(&param, sizeof(t_param));
	ft_bzero(&data, sizeof(t_data));
	if(check_av(av[1]))
		return (0);
	c = read_file(&param, av[1]);
	
	
	mehdi_parse(&param, &data); //todo: mehdi

	if (ft_cnt_param(&param) != 6 || check_par(&param) != 6 || check_color(&param))
	{
		free_all_map(param.map_trim);
		free_all_map(param.map);
		printf("EROOR 88 !!\n");
		free(param.C);
		free(param.F);
		free(param.EA);
		free(param.NO);
		free(param.SO);
		free(param.WE);
		return (0);
	}
	if (check_first_last_line(&param) || check_jnob(&param) || ft_search_player(&param) != 1 || ft_check_space(&param))
	{
		free_all_map(param.map);
		free_all_map(param.map_trim);
		free_all_map(param.last_map);
		free(param.C);
		free(param.F);
		free(param.EA);
		free(param.NO);
		free(param.SO);
		free(param.WE);
		printf("EROOR 99 !!\n");
		// system("leaks CUB3D");
		// free;
		return (0);
	}
	// ft_valid_path(&i, param.y_player, param.x_player, &param);
	// if(i != 0)
	// {
	// 	printf("EROOR Soliix !!\n");
	// 	return(0);
	// }
	// system("leaks -p");
	// printf("-------------------------------------------\n");
	search_rgb(param.F, &param.rgb_F);
	// printf("rgb_F = %d\n", param.rgb_F);
	map_mehdi(&param);
	search_rgb(param.C, &param.rgb_C);
	// printf("rgb_C = %d\n", param.rgb_C);
	// ft_bzero(&param, sizeof(param));
	// system("leaks CUB3D");
	// exit(1);
	// printf("rgb_C = %d\n", param.rgb_C);
	// printf("rgb_F = %d\n", param.rgb_F);
	// printf("%s\n", param.C);
	// printf("%s\n", param.F);
	// printf("(%s)\n", param.NO);
	// printf("(%s)\n", param.EA);
	// printf("(%s)\n", param.WE);
	// printf("(%s)\n", param.SO);
	// printf_map(&param);
	// printf("long_line = %lu\n", param.long_line);
	// printf("height_map = %d\n", param.height_map);

	// printf("x = %d\n", param.x_player);
	// printf("y = %d\n", param.y_player);
	// printf("height_map = %d\n", param.height_map);
	free_all_map(param.map);
	free_all_map(param.map_trim);
	free_all_map(param.last_map);
	free(param.C);
	free(param.F);
	// {
	// 	ft_bzero(&param, sizeof(param));  
	// 	system("leaks CUB3D");
	// 	exit(1);
	// }

	display(&param , &data); //todo: mehdi
return 0;
}

int main(int av, char **ac)
{
	main1(av, ac);
	// system("leaks CUB3D");
	return(0);
}