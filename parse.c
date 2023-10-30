#include "cub3d.h"

int ft_cnt_line(char *av1)
{
	int i;
	int fd;
	char *c;

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


char **read_file(t_param *var, char *av1)
{
	int fd;
	int i;
	int j;

	j = 0;
	i = 0;
	i = ft_cnt_line( av1);
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



void remplir_var(char *line, t_param *var)
{
	// printf("here\n");
	char **split;

	// printf(">%s\n", line);
	split = ft_split(line, ' ');
	// printf("-->%s\n", split[1]);
	if (line[0] == 'W')
		var->WE = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else if (line[0] == 'S')
		var->SO = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else if (line[0] == 'N')
		var->NO = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else if (line[0] == 'E')
		var->EA = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	else if (line[0] == 'F')
		var->F = ft_substr(split[1], 0, ft_strlen(split[1]));
	else
		var->C = ft_substr(split[1], 0, ft_strlen(split[1]));
	free(split);	
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
int check_line(char *s1, char *s2)
{
	int len;

	len = 0;
	if (ft_strlen2(s1) > ft_strlen2(s2))
				len = ft_strlen2(s1);
			else
				len = ft_strlen2(s2);
	return(len);			
}
int check_par(t_param *var)
{
	int		i;
	int		j;
	int		cnt;
	int		len;
	char	*tab[7] = {"NO", "EA", "SO", "WE", "F", "C"};

	i = -1;
	cnt = 0;
	while (var->map_trim[++i])
	{
		if (var->map_trim[i][0] == '\n')
			continue;
		j = -1;
		while (tab[++j])
		{
			len = check_line(tab[j], var->map_trim[i]);
			if (ft_strncmp(var->map_trim[i], tab[j], len) == 0)
			{
				cnt++;
				remplir_var(var->map_trim[i], var);
				break;
			}
		}
	}
	if(cnt == 6)
		return(0);
	return(1);	
}

void check_long_line(t_param *vars)
{
	int i;

	vars->long_line = 0;
	i = 0;
	// printf("...%d\n", i);
	while(vars->last_map[i])
	{
		if(ft_strlen(vars->last_map[i]) > vars->long_line)
			vars->long_line = ft_strlen(vars->last_map[i]) - 1;
		i++;	
	}
	printf("long line : %zu\n", vars->long_line);
}

int ft_search_player_2(t_param *vars, int y)
{
	int cnt;
	int x;
	int i;

	cnt = 0;
	i = 0;
	while(vars->map[y])
	{
		// printf("****%s\n", vars->map[y]);
		printf("vars->map[%d] :%s\n", y,vars->map[y]);
		printf("len vars->map[%d] :%zu\n", y,ft_strlen(vars->map[y]));

		vars->last_map[i] = ft_substr(vars->map[y], 0, ft_strlen(vars->map[y]));
		x = 0;
		while(vars->last_map[i][x])
		{
			if(ft_strchr("NSEW 10\n", vars->last_map[i][x]) == NULL)
					return(0);
			else if(ft_strchr("NSEW", vars->last_map[i][x]) != NULL)
    		cnt++;
			x++;
		}
		y++;
		i++;
	}
	printf("i == %d\n", y);
	vars->last_map[i] = 0;
	check_long_line(vars);
	return(cnt);
}
int ft_search_player(t_param *vars)
{
	int y;
	int cnt =0;
	int i = 0;
	int x;

	y = vars->first_line;
	printf("vars->last_line - vars->first_line : %d\n", vars->last_line - vars->first_line + 1);
	vars->last_map = (char **)malloc(sizeof(char *) * (vars->last_line - vars->first_line + 2));
	// cnt = ft_search_player_2(vars, y);
	// while(vars->map[y])
	// {
	// 	vars->last_map[i] = ft_substr(vars->map[y], 0, ft_strlen(vars->map[y]));
	// 	x = 0;
	// 	while(vars->last_map[i][x])
	// 	{
	// 		if(vars->last_map[i][x] != 'N' && vars->last_map[i][x] != 'S' && vars->last_map[i][x] != 'E' 
	// 			&& vars->last_map[i][x] != 'W' && vars->last_map[i][x] != ' ' && vars->last_map[i][x] != '1' && vars->last_map[i][x] != '0' && vars->last_map[i][x] != '\n')
	// 			{
	// 				printf("====>>%c\n", vars->last_map[i][x]);
	// 				return(0);
	// 			}
	// 		else if(vars->last_map[i][x] == 'N' || vars->last_map[i][x] == 'S' || vars->last_map[i][x] == 'E' || vars->last_map[i][x] == 'W')
	// 		{
	// 			vars->x_player = x;
	// 			printf("x player = %d\n", vars->x_player);
	// 			vars->y_player = i;
	// 			printf("y player= %d\n", vars->y_player);
	// 			cnt++;
	// 		}
	// 			x++;
	// 	}
	// 	y++;
	// 	i++;
	// }
	// vars->last_map[i] = 0;
	vars->last_line = i - 1;
	printf("last line : %d\n", vars->last_line);
	while(vars->map[y])
	{
		// printf("****%s\n", vars->map[y]);
		printf("vars->map[%d] :%s\n", y,vars->map[y]);
		printf("len vars->map[%d] :%zu\n", y,ft_strlen(vars->map[y]));

		vars->last_map[i] = ft_substr(vars->map[y], 0, ft_strlen(vars->map[y]));
		x = 0;
		while(vars->last_map[i][x])
		{
			if(ft_strchr("NSEW 10\n", vars->last_map[i][x]) == NULL)
					return(0);
			else if(ft_strchr("NSEW", vars->last_map[i][x]) != NULL)
				{
						vars->x_player = x;
						printf("x player = %d\n", vars->x_player);
						vars->y_player = i;
						printf("y player= %d\n", vars->y_player);
						cnt++;
				}
			x++;
		}
		y++;
		i++;
	}
	printf("i == %d\n", y);
	vars->last_map[i] = 0;
	check_long_line(vars);
	return(cnt);
}




int ft_cnt_param(t_param *var)
{
	int i;
	int cnt;
	int tmp = 0;

	i = -1;
	cnt = 0;
	var->first_line = 0;
	while (var->map_trim[++i])
	{
		if (ft_strchr("WSNEFC", var->map_trim[i][0]) != NULL)
			cnt++;
		else if (var->map_trim[i][0] == '1')
		{
			if(tmp == 0)
			{
				var->first_line = i;
				tmp = 1;
			}
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
		printf("first line : %d\n", var->first_line);
		printf("last line : %d\n", var->last_line);
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
	i = 0;	
	while(cheak[i])
	{
		printf("-->%s\n", cheak[i]);
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

// int ft_check_segv(int y_player, size_t x_player, t_param *vars)
// {
// 	if (y_player > vars->last_line || y_player < 0)
// 		return(0);
// 	if(ft_strlen(vars->last_map[y_player]) < x_player)
// 		return(0);	
// 	return(1);	
// }


// int	ft_valid_path(int *i, int y_player, int x_player,t_param *vars)
// {
// 	// printf("xx==%d\n", x_player);
// 	// printf("yy==%d\n", y_player);
// 	if (vars->last_map[y_player][x_player] == ' ' || vars->last_map[y_player][x_player] == '\n')
// 		(*i)++;
// 	vars->last_map[y_player][x_player] = 'X';
// 	if (ft_check_segv(y_player - 1, x_player, vars) && (vars->last_map[y_player - 1][x_player] == '0' || vars->last_map[y_player - 1][x_player] == ' ' || vars->last_map[y_player - 1][x_player] == '\n'))
// 		ft_valid_path(i, y_player - 1, x_player, vars);
// 	if (ft_check_segv(y_player + 1, x_player, vars) && (vars->last_map[y_player + 1][x_player] && (vars->last_map[y_player + 1][x_player] == '0' || vars->last_map[y_player + 1][x_player] == ' ' || vars->last_map[y_player + 1][x_player] == '\n')))
// 		ft_valid_path(i, y_player + 1, x_player, vars);
// 	if (ft_check_segv(y_player, x_player - 1, vars) && (vars->last_map[y_player][x_player - 1] == '0' || vars->last_map[y_player][x_player - 1] == ' ' || vars->last_map[y_player + 1][x_player] == '\n'))
// 		ft_valid_path(i, y_player, x_player - 1, vars);
// 	if (ft_check_segv(y_player, x_player + 1, vars) && (vars->last_map[y_player][x_player + 1] == '0' || vars->last_map[y_player][x_player + 1] == ' ' || vars->last_map[y_player + 1][x_player] == '\n'))
// 		ft_valid_path(i, y_player, x_player + 1, vars);
// 	return (*i);
// }





int space_exist(char **map, int x, int y)
{
	if(!(ft_strchr("NSWE01", map[y][x - 1])))
		return(1);
	if(!(ft_strchr("NSWE01", map[y][x + 1])))
		return(1);
	if(!(ft_strchr("NSWE01", map[y - 1][x])))
		return(1);
	if(!(ft_strchr("NSWE01", map[y + 1][x])))
		return(1);
	return(0);
}

// int ft_str(char **c)
// {
// 	int i = 0;
// 	while(c[i])
// 	{
// 		i++;
// 	}
// 	return(i);	
// }


int ft_check_space(t_param *vars)
{
    int x;
    int y;
    int check;

    y = 1;
    check = 0;
    
    while (vars->last_map && vars->last_map[y])
    {
        x = 0;
        while (vars->last_map[y][x])
        {
            if (ft_strchr("NSWE0", vars->last_map[y][x]))
            {
                check = space_exist(vars->last_map, x, y);
                if (check == 1)
                {
                    printf("ERROR soliix\n");
                    return 1;
                }
            }
            x++;
        }
        y++;
    }
    return 0;
}














void ft_ptrint_map(t_param *vars)
{
	int i;

	i = 0;
	while(vars->last_map[i])
	{
		printf("%d-->%s", i, vars->last_map[i]);
		i++;
	}
}


int check_color(t_param *vars)
{
	// char **check;
	// char **check1;
	// int i;
	// int j;

	// i = 0;
	// j = 0 ;
	
	if(vars->C[ft_strlen(vars->C)] == ',' || !ft_isdigit(vars->C[ft_strlen(vars->C) - 2])
		||vars->F[ft_strlen(vars->F)] == ',' || !ft_isdigit(vars->F[ft_strlen(vars->F) - 2]))
			{
				printf("HERE4\n");
				return(1);
			}
	// check = ft_split(vars->C, ' ');
	if(ft_isdigit(vars->C[0]) == 0)
		{
				printf("HERE3\n");
				return(1);
			}
	if(ft_strncmp(vars->C, "C" , 2) == 0) //hsb wach homa 2
		if(ft_check_is_digit(vars->C))
			{
				printf("HERE3\n");
				return(1);
			}
	// while(vars->C[i])
	// 	i++;
	// check1 = ft_split(vars->F, ' ');	
	// printf("'%s'\n", check1[0]);
	if(ft_strncmp(vars->F, "F" , 2) == 0) //hsb wach homa 2
		if(ft_check_is_digit(vars->F))
			{
				printf("HERE2 \n");
				return(1);
			}
	// while(vars->F[j])
	// 	j++;
	// if(i != 1 || j != 1)
	// {
	// 	printf("HERE1 \n");
	// 	return(1);
	// }
	return(0);
}
//--------------------------------------------------------------------------------------------------------//

int	check_first_last_line(t_param *vars)
{
	int	x;

	x = 0;
	printf("(%s)\n",vars->map[x]);
	printf("vars first line : %d\n", vars->first_line);
	while (vars->map[vars->first_line] && vars->map[vars->first_line][x])
	{
		if(ft_strchr("\n1 ", vars->map[vars->first_line][x]) == NULL)
			{
				// printf("%d--->%c\n", vars->first_line ,vars->map[vars->first_line][x]);
				printf("HERE44\n");
				return(1);
			}
		x++;	
	}
	x = 0;
	while (vars->map[vars->last_line][x])
	{
		if(ft_strchr("\n1 ", vars->map[vars->last_line][x]) == NULL)
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
	int check = 0;

	y = vars->first_line;
	while (y < vars->last_line)
	{
		if(ft_strchr("1 ", vars->map[y][0]) == NULL)
		{
			printf("HERE11\n");
			return(1);
		}
		y++;	
	}
	y = vars->first_line;
	while (y < vars->last_line)
	{
    	if(vars->map[y][0] == '\n')
      {
				if(check == 0)
				{
					vars->first_nl = 0;
					check = 1;
				}
			  y++;
        continue;
      }
			if(ft_strchr("1 ", vars->map[y][ft_strlen(vars->map[y]) - 2]) == NULL)
			{
				printf("HERE22\n");
				return(1);
			}
		y++;	
	}
		printf("first_new_line :%d\n", vars->first_nl);
	return (0);
}

void ft_change(t_param *vars)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(vars->last_map[i])
	{
			j = 0;
			while(vars->last_map[i][j])
			{
				if(ft_strchr("0WSNE", vars->last_map[i][j]) != NULL)
						vars->map_mehdi[i][j] = vars->last_map[i][j];
				j++;
			}
		// if(vars->map_mehdi[i][ft_strlen(vars->map_mehdi[i]-2)] == '\n')
		// 	vars->map_mehdi[i][ft_strlen(vars->map_mehdi[i]-2)] = '\0';
		printf("new line %d : [%s]\n", i,vars->map_mehdi[i]);
		i++;
	}
	printf("++++++++++++++++++++++++++++%d\n", i);
	vars->height_map = i;
	printf("width_map : %d\n", vars->height_map);
}

// void ft_change_map(t_param *vars)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while(vars->map_mehdi[i])
// 	{
// 		j = 0; 
// 		while(vars->map_mehdi[i][j])
// 		{
// 			ft_change(vars, i ,j);
// 			j++;
// 		}
// 		printf("new line %d : %s", i,vars->map_mehdi[i]);
// 		i++;
// 	}
// }
void map_mehdi(t_param *vars)
{
	int i;
	int dec;

	i = 0;

	while(vars->last_map[i])
		i++;
	vars->map_mehdi = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(vars->last_map[i])
	{
		vars->map_mehdi[i] = malloc(vars->long_line + 2);
		dec = vars->long_line;
		vars->map_mehdi[i][0] = '1';
		while(dec)
		{
			vars->map_mehdi[i][dec] = '1';
			dec--;
		}
		if(vars->map_mehdi[i + 1] != NULL)
			vars->map_mehdi[i][vars->long_line] = '\n';
		vars->map_mehdi[i][vars->long_line + 1] = '\0';
		printf("new line %d : %s", i,vars->map_mehdi[i]);
		i++;
	}
	vars->map_mehdi[i] = 0;
	ft_change(vars);
}


// ft_map_ry(t_param *vars)
// {
// 	int x,y;

// 	x = vars->x_player;
// 	y = vars->y_player - 1;
// 	while(vars->map[x])
// 	{
// 		while(vars->map[x][y])
// 		{
// 			if(vars->map[x][y] == ' ')

// 		}
// 	}
// 

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
void search_rgb(char *str, int rgb)
{

	char **s2;

	s2 = ft_split(str, ',');
	
	printf("S[0] = %s\n", s2[0]);
	printf("S[1] = %s\n", s2[1]);
	printf("S[2] = %s\n", ft_substr(s2[2], 0, ft_strlen(s2[2]) - 1));
	rgb = (ft_atoi(s2[0]), ft_atoi(s2[1]), ft_atoi(ft_substr(s2[2], 0, ft_strlen(s2[2]) - 1)));
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





int main(int ac, char **av)
{
	char **c;
	// int  i = 0;

	(void)ac;
	t_param param;
	ft_bzero(&param, sizeof(t_param));
	// param.tab = {"NO", "EA", "SO", "WE", "F", "C"};
	if(check_av(av[1]))
		return (0);
	c = read_file(&param, av[1]);
	// param.tab = {"NO", "EA", "SO", "WE", "F", "C"};
	if (ft_cnt_param(&param) || check_par(&param) || check_color(&param))
	{
		printf("EROOR 88 !!\n");
		// free;
		return (0);
	}
	if (check_first_last_line(&param) || check_jnob(&param) || ft_search_player(&param) != 1 || ft_check_space(&param))
	{
		printf("EROOR 99 !!\n");
		// free;
		return (0);
	}
	// ft_valid_path(&i, param.y_player, param.x_player, &param);
	// if(i != 0)
	// {
	// 	printf("EROOR Soliix !!\n");
	// 	return(0);
	// }
	ft_ptrint_map(&param);
	printf("-------------------------------------------\n");
	map_mehdi(&param);
	search_rgb(param.F, param.rgb_F);
	search_rgb(param.C, param.rgb_C);
	printf("rgb_C = %d\n", param.rgb_C);
	printf("rgb_F = %d\n", param.rgb_F);
	printf("%s\n", param.C);
	printf("%s\n", param.F);
	printf("(%s)\n", param.NO);
	printf("(%s)\n", param.EA);
	printf("(%s)\n", param.WE);
	printf("(%s)\n", param.SO);

	printf("x = %d\n", param.x_player);
	printf("y = %d\n", param.y_player);
	printf("height_map = %d\n", param.height_map);
	printf("long line : %zu\n", param.long_line);
	display(&param);
}