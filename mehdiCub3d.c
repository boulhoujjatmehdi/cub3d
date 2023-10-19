#include "mehdiCub3d.h"

void lire_map(t_data *data, char *av)
{
	int fd;
	int i;
	int j;
	char *c;

	j = 0;
	i = 0;
	fd = open(av, O_RDONLY);//TODO: PROTECT av 
	while (1)
	{
		c = get_next_line(fd);
		i++;
		free(c);
		if (!c)
			break; //TODO: SEGV: MOVE THIS UP IT CAN CAUSE A SEGV
	}
	close(fd);
	fd = open(av, O_RDONLY);
	data->mat = (char **)malloc(sizeof(char *) * (i + 1));
	while (i--)
	{
		data->mat[j] = get_next_line(fd);
		j++;
	}
	data->mat[j] = 0;
}
void len_mapp(t_data *data)
{
	int k;
	int l;

	k = -1;
	l = 0;
	data->height = 0;
	data->width = 0;
	while (data->mat[++k])
	{
		if (l == 0)
		{
			while (data->mat[k][l] != '\0')
			{
				data->width++;
				l++;
			}
			data->width--;
		}
		data->height++;
	}
}
void draw_line(t_data* data, float x, float y, float end_x, float end_y, uint32_t color)
{
	int steps;
	double x_i;
	double y_i;
	int i;

	x_i = end_x - x;
	y_i = end_y - y;

	steps = abs((int)x_i);
	if(fabs(x_i) < fabs(y_i))
		steps = abs((int)y_i);
	x_i = x_i/(float)steps;
	y_i = y_i/(float)steps;

	i = 0;
	while (i < abs(steps))
	{

		x += x_i;
		y += y_i;
		mlx_put_pixel(data->mlx_im, x, y, color);
		i++;
	}
}

void draw_square(t_data* data, int pos_x, int pos_y, uint32_t clr)
{
    int i;
    int j;

    i = 0;
    pos_x *= data->sq_dim ;
    pos_y *= data->sq_dim;

    while(i < data->sq_dim)
    {
        j = 0;
        while(j < data->sq_dim)
        {
            mlx_put_pixel(data->mlx_im, pos_x+j, pos_y+i, clr);
            j++;
        }
        i++;
    }
}

void draw_map(t_data *data)
{

    int i;
    int j;
    i = 0;

    while(data->mat[i])
    {
        j = 0;
        while (data->mat[i][j])
        {
            if(data->mat[i][j] == '1')
                draw_square(data, j, i, 0x00FF0000ff);
            else if(data->mat[i][j] != '\n')
                draw_square(data, j, i, 0x00ffffffff);
            j++;
        }
        i++;
    }
}

void draw_player(t_data* data)
{
        mlx_put_pixel(data->mlx_im,data->ppos_x ,data->ppos_y , 0x00000000ff);
}
int check_wall_at(t_data *param, double k, double l)
{
	// printf("x = %d , y = %d char = (%c) \n", (int)(k/param->sq_dim) , (int)(l/param->sq_dim) , param->mat[(int)(k/param->sq_dim)][(int)(l/param->sq_dim)]);
	// puts("-------------------------------------------------------------");
	// printf("x = %d , y = %d , (%.1f, %.1f)\n", (int)(k/param->sq_dim) , (int)(l/param->sq_dim), k , l);
	// puts("was here1");
	if (param->mat[(int)(k/param->sq_dim)][(int)(l/param->sq_dim)] == '1')
	{
		// puts("was here2");
		return (0);
	}
	// puts("was here3");
	return (1);
}

void mouvements(t_data *pr)
{
	float	tmpx;
	float	tmpy;
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_LEFT))
	{
		pr->p_angle -= (M_PI / 180) * pr->rotation_angle;
	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_RIGHT))
	{
		pr->p_angle += (M_PI / 180) * pr->rotation_angle;
	}
	tmpx = cos(pr->p_angle) * 7;
	tmpy = sin(pr->p_angle) * 7;

	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_W) && check_wall_at(pr, (pr->ppos_y + tmpy) , (pr->ppos_x + tmpx) ))
	{
		pr->ppos_x += cos(pr->p_angle)*1.5;
		pr->ppos_y += sin(pr->p_angle)*1.5;
		// printf("W = %f - %f\n", pr->ppos_x, pr->ppos_y);

	}
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_S) && check_wall_at(pr, (pr->ppos_y-tmpy)  , (pr->ppos_x - tmpx) ))
	{
		pr->ppos_x -= cos(pr->p_angle)*1.5;
		pr->ppos_y -= sin(pr->p_angle)*1.5;
		// printf("S = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	tmpx = cos(pr->p_angle + 90 * (M_PI / 180)) * 7;
	tmpy = sin(pr->p_angle + 90 * (M_PI / 180)) * 7;
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_A) && check_wall_at(pr, (pr->ppos_y - tmpy) , (pr->ppos_x - tmpx) ))
	{
		pr->ppos_x -= cos(pr->p_angle + 90 * (M_PI / 180));
		pr->ppos_y -= sin(pr->p_angle + 90 * (M_PI / 180));
		// printf("A = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_D) && check_wall_at(pr, (pr->ppos_y + tmpy) , roundf(pr->ppos_x + tmpx) ))
	{
		pr->ppos_x += cos(pr->p_angle + 90 * (M_PI / 180));
		pr->ppos_y += sin(pr->p_angle + 90 * (M_PI / 180));
		// printf("D = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_Q))
	{
		exit(1);
	}
}
void normalize_angle(double *angle)
{
	int tmp;
	tmp = *angle / (2 * M_PI);
	*angle = *angle - (tmp * 2 * M_PI);
	if(*angle < 0)
		*angle += 2 *M_PI;

	// printf("p_angle (%f) - tmp(%d) == tmp2(%f)\n",data->p_angle , tmp ,  data->p_angle);

}
void horizontal(t_data* data, double ray_angle, t_wall* wall)
{
	float x_inters;
	float y_inters;
	float x_steps;
	float y_steps;
	int facing_up;
	int facing_left;

	facing_up = facing_left = 1;
	if(ray_angle < M_PI_2 || ray_angle > M_PI_2 * 3)
		facing_left = 0;
	if(ray_angle >= 0 && ray_angle < M_PI)
		facing_up = 0;
	//finding y intersection 
	y_inters = floor(data->ppos_y / data->sq_dim) * data->sq_dim;
	if(!facing_up)
		y_inters += data->sq_dim;
	//finding x intersection
	x_inters = (y_inters - data->ppos_y)/ tan(ray_angle);
	x_inters += data->ppos_x;

	//calculate the increment x_step and y_step
	y_steps = data->sq_dim;
	if(facing_up)
		y_steps *= -1;

	x_steps = data->sq_dim / tan(ray_angle);
	if((facing_left && x_steps > 0)||(!facing_left && x_steps < 0))
		x_steps *= -1;

	//--------------------------
	float next_touch_x;
	float next_touch_y;
	next_touch_x = x_inters;
	next_touch_y = y_inters;
	
	wall->horz_x = data->ppos_x;
	wall->horz_y = data->ppos_y;
			wall->horz_distance = INT32_MAX;
	while(next_touch_x >= 0 && next_touch_x <= (data->width) && next_touch_y >=0 && next_touch_y <= data->height)
	{
		float check_x = next_touch_x;
		float check_y = next_touch_y + (facing_up? -1: 0);

		if(check_wall_at(data, check_y, check_x) == false)
		{
			wall->horz_found_wall = true;
			wall->horz_x = next_touch_x;
			wall->horz_y  = next_touch_y; 
			wall->horz_distance = sqrt((wall->horz_x - data->ppos_x) * (wall->horz_x - data->ppos_x)+(wall->horz_y - data->ppos_y)* (wall->horz_y - data->ppos_y));
			break;
		}
		else
		{
			next_touch_x += x_steps;
			next_touch_y += y_steps;
		}
	}
}
void verticall(t_data* data, double ray_angle, t_wall* wall)
{
	float x_inters;
	float y_inters;
	float x_steps;
	float y_steps;
	int facing_up;
	int facing_left;

	facing_up = facing_left = 1;
	if(ray_angle < M_PI_2 || ray_angle > M_PI_2 * 3)
		facing_left = 0;
	if(ray_angle >= 0 && ray_angle < M_PI)
		facing_up = 0;

	//finding y intersection 
	x_inters = floor(data->ppos_x / data->sq_dim) * data->sq_dim;
	if(!facing_left)
		x_inters += data->sq_dim;

	//finding x intersection
	y_inters =data->ppos_y + (x_inters - data->ppos_x) * tan(ray_angle);


	//calculate the increment x_step and y_step
	x_steps = data->sq_dim;
	if(facing_left)
		x_steps *= -1;

	y_steps = data->sq_dim * tan(ray_angle);
	if((facing_up && y_steps > 0)||(!facing_up && y_steps < 0))
		y_steps *= -1;

	//--------------------------




	float next_touch_x;
	float next_touch_y;
	next_touch_x = x_inters;
	next_touch_y = y_inters;
	
	wall->vert_x = data->ppos_x;
	wall->vert_y = data->ppos_y;

			wall->vert_distance = INT32_MAX;
	while(next_touch_x >= 0 && next_touch_x <= data->width && next_touch_y >=0 && next_touch_y <= data->height)
	{

		float check_x = next_touch_x + (facing_left? -1:0);
		float check_y = next_touch_y;
		if(check_wall_at(data, check_y, check_x) == false)
		{
			wall->vert_found_wall = true;
			wall->vert_x = next_touch_x;
			wall->vert_y  = next_touch_y;
			wall->vert_distance = sqrt((wall->vert_x - data->ppos_x) * (wall->vert_x - data->ppos_x)+(wall->vert_y - data->ppos_y)* (wall->vert_y - data->ppos_y));
			break;
		}
		else
		{
			next_touch_x += x_steps;
			next_touch_y += y_steps;
		}
	}
}
void draw_strip(t_data* data, int x, double wall_hight, int color)
{
	int i = 0;
	// printf("")
	int begin  = (data->win_h/2)- (wall_hight/2);
	if(begin < 0)
	{
		begin = 0;
		wall_hight = data->win_h;
	}
	while(i < data->win_h/2)
		mlx_put_pixel(data->mlx_im, x, i++, 0x00000000ff);
	while( i < data->win_h)
		mlx_put_pixel(data->mlx_im, x, i++, 0x006e7175ff);

	i = 0;
	while(i < wall_hight)
	{
		mlx_put_pixel(data->mlx_im, x, begin, color);
		begin ++;
		i++;
	}
}
void wall_projection(t_data *data)
{
	int i;
	double left_angle;
	float increase;
	t_wall wall;

	increase = fabs((float)data->fov/ (float)data->num_rays);
	left_angle = data->p_angle - (data->fov/2);
	i = 0;
	bool test;
	test = false;
	while(i < data->num_rays)
	{
		normalize_angle(&left_angle);
		normalize_angle(&data->p_angle);
		wall.horz_found_wall = wall.vert_found_wall = false;
		horizontal(data, left_angle, &wall);
		verticall(data, left_angle, &wall);
		if(wall.horz_distance < wall.vert_distance || (wall.horz_distance == wall.vert_distance && test == false))
		{
			test = false;
			double rayDistance = wall.horz_distance *cos(data->p_angle - left_angle);
			double distanceToProjPlan = (data->win_w / 2) * tan(data->fov/2);
			double wallHeight = (70 / rayDistance) * distanceToProjPlan;
			
			draw_strip(data, i, wallHeight, 0x00ff0000ff);
		}
		else if(wall.horz_distance > wall.vert_distance || (wall.horz_distance == wall.vert_distance && test == true))
		{
			test = true;
			double rayDistance = wall.vert_distance *cos(data->p_angle - left_angle);
			double distanceToProjPlan = (data->win_w / 2) * tan(data->fov/2);
			double wallHeight = (70 / rayDistance) * distanceToProjPlan;
			draw_strip(data, i, wallHeight, 0x0000ff00ff);
		}
		i++;
		left_angle += increase;
	}
}
void ray_casting(t_data *data)
{
	int i;
	double left_angle;
	float increase;
	t_wall wall;

	increase = fabs((float)data->fov/ (float)data->num_rays);
	left_angle = data->p_angle - (data->fov/2);
	i = 0;
	while(i < data->num_rays)
	{
		normalize_angle(&left_angle);
		wall.horz_found_wall = wall.vert_found_wall = false;
		horizontal(data, left_angle, &wall);
		verticall(data, left_angle, &wall);
		// if(wall.horz_found_wall && wall.vert_found_wall)
		// {
			if(wall.horz_distance < wall.vert_distance)
				draw_line(data, data->ppos_x, data->ppos_y, wall.horz_x, wall.horz_y, 0x0000ff00ff);
			else if(wall.horz_distance > wall.vert_distance)
				draw_line(data, data->ppos_x, data->ppos_y, wall.vert_x, wall.vert_y, 0x000000ffff);
			// else if()
		// }
		// else if(wall.horz_found_wall)
		// 	draw_line(data, data->ppos_x, data->ppos_y, wall.horz_x, wall.horz_y, 0x0000ff00ff);
		// else if(wall.vert_found_wall)
		// 	draw_line(data, data->ppos_x, data->ppos_y, wall.vert_x, wall.vert_y, 0x000000ffff);
		i++;
		left_angle += increase;
	}
	
}
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void render_image(t_data* data)
{
	mlx_texture_t* txtr;
	txtr = mlx_load_png("eboulhou.png");
	for (int y = 0; y < 500 ; y++)
	{
		for (int x = 0; x < 500; x++)
		{
			uint32_t color = (txtr->pixels[(y*txtr->width*4) + (x * 4)+0]<< 24) + (txtr->pixels[(y*txtr->width*4) + (x * 4)+1]<< 16) +(txtr->pixels[(y*txtr->width*4) + (x * 4)+2]<< 8) + (txtr->pixels[(y*txtr->width*4) + (x * 4)+3]);
			mlx_put_pixel(data->mlx_im, x, y, color);
		}
	}
}

void draw(void *dt)
{    
    t_data* data;

    data = (t_data*)dt; 
    // draw_map(data);
    // draw_player(data);
    mouvements(data);
	// printf("cos  = %f , sin = %f\n", cosf(data->p_angle), sinf(data->p_angle));
	
	// ray_casting(data);
	wall_projection(data);

	// render_image(data);
	// draw_line(data, data->ppos_x, data->ppos_y, (data->ppos_x+cosf(data->p_angle)*15), (data->ppos_y+sinf(data->p_angle)*15), 0x00000000ff);

}

void vue_angle(t_data *param)
{
	int y = 0;
	int x;

    param->p_angle = 1;
	while (param->mat[y] != NULL)
	{
		x = 0;
		while (param->mat[y][x] != '\0')
		{
			if(param->mat[y][x] == 'N')
				param->p_angle = M_PI_2 * 3;
			else if(param->mat[y][x] == 'E')
				param->p_angle = 0;
			else if(param->mat[y][x] == 'S')
				param->p_angle = M_PI_2;
			else if(param->mat[y][x] == 'W')
				param->p_angle = M_PI;
            if(param->p_angle != 1)
            {
                param->ppos_y = (y * param->sq_dim) + (param->sq_dim / 2);
                param->ppos_x = (x * param->sq_dim) + (param->sq_dim / 2);
                return ;
            }
			x++;
		}
		y++;
	}
}
void initialize_data(t_data* data)
{
    data->sq_dim = 50;
	data->mini_scale = 0.15;
	data->p_rad = 4;
	data->rotation_angle = 1;
	data->fov = 60*(M_PI / 180);
	data->win_w = 1900;
    data->win_h = 980;
	data->width *= data->sq_dim;
	data->height *= data->sq_dim;
	data->num_rays = data->win_w;
}

int main(int ac, char **av)
{
    t_data data;

    if(ac!= 2)
        return 1;
	lire_map(&data, av[1]);
    len_mapp(&data);
	initialize_data(&data);
    vue_angle(&data);
    data.mlx_in = mlx_init(data.win_w, data.win_h, "cub3D", 0);
	data.mlx_im = mlx_new_image(data.mlx_in, data.win_w, data.win_h);

    mlx_image_to_window(data.mlx_in, data.mlx_im, 0, 0);
    mlx_loop_hook(data.mlx_in, draw, &data);
    mlx_loop(data.mlx_in);
    return 0;

}