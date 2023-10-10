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
void draw_line(t_data* data, float x, float y, float end_x, float end_y)
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
		mlx_put_pixel(data->mlx_im, x, y, 0x00000000ff);
		i++;
	}
}

void draw_square(t_data* data, int pos_x, int pos_y, uint32_t clr)
{
    int i;
    int j;

    i = 0;
    pos_x *= data->sq_dim;
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
	printf("x = %d , y = %d \n", (int)(k/50) , (int)(l/50));
	if (param->mat[(int)(k/50)][(int)(l/50)] == '1')
	{
		return (0);
	}
	return (1);
}

void key_hook(t_data *pr)
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
	tmpx = cosf(pr->p_angle);
	tmpy = sinf(pr->p_angle);

	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_W) && check_wall_at(pr, (pr->ppos_y + tmpy) , (pr->ppos_x + tmpx) ))
	{
		pr->ppos_x += cosf(pr->p_angle);
		pr->ppos_y += sinf(pr->p_angle);
		// printf("W = %f - %f\n", pr->ppos_x, pr->ppos_y);

	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_S) && check_wall_at(pr, (pr->ppos_y-tmpy)  , (pr->ppos_x - tmpx) ))
	{
		pr->ppos_x -= cosf(pr->p_angle);
		pr->ppos_y -= sinf(pr->p_angle);
		// printf("S = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	tmpx = cosf(pr->p_angle + 90 * (M_PI / 180));
	tmpy = sinf(pr->p_angle + 90 * (M_PI / 180));
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_A) && check_wall_at(pr, (pr->ppos_y - tmpy) , (pr->ppos_x - tmpx) ))
	{
		pr->ppos_x -= cosf(pr->p_angle + 90 * (M_PI / 180));
		pr->ppos_y -= sinf(pr->p_angle + 90 * (M_PI / 180));
		// printf("A = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_D) && check_wall_at(pr, (pr->ppos_y + tmpy) , roundf(pr->ppos_x + tmpx) ))
	{
		pr->ppos_x += cosf(pr->p_angle + 90 * (M_PI / 180));
		pr->ppos_y += sinf(pr->p_angle + 90 * (M_PI / 180));
		// printf("D = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_Q))
		exit(1);
}
void normalize_angle(t_data* data)
{
	int tmp;
	tmp = data->p_angle / (2 * M_PI);
	data->p_angle = data->p_angle - (tmp * 2 * M_PI);
	if(data->p_angle < 0)
		data->p_angle += 2 *M_PI;

	// printf("p_angle (%f) - tmp(%d) == tmp2(%f)\n",data->p_angle , tmp ,  data->p_angle);

}
void horizontal(t_data* data, double ray_angle)
{
	//TODO: GET THE FIRST INTERSECTION BY (X AND Y)
	//TODO: GET THE YSTEP AND XSTEP IN HORIZONTAL STEPS
	(void)data;
	int x_inters;
	int y_inters;
	int x_steps;
	int y_steps;
	int facing_up;
	int facing_left;

	facing_up = facing_left = 1;
	if(ray_angle < M_PI_2 || ray_angle > M_PI_2 * 3)
		facing_left = 0;
	if(ray_angle >= 0 && ray_angle < M_PI)
		facing_up = 0;
	y_inters = floor(data->ppos_y / data->sq_dim) * data->sq_dim;
	if(!facing_up)
		y_inters += data->sq_dim;
	x_inters = (data->ppos_y - y_inters)/ tanf(ray_angle);
	// if(facing_up)
	// 	x_inters *= -1;
	// else
	// 	y_inters += data->sq_dim;
	x_inters += data->ppos_x;

	y_steps = data->sq_dim;
	if(facing_up)
	{
		y_steps *= -1;
	}


	x_steps = data->sq_dim / tan(ray_angle);
	if((facing_left && x_steps > 0)||(!facing_left && x_steps < 0))
		x_steps *= -1;

	int next_touch_x;
	int next_touch_y;

	int wallhitx;
	int wallhity;
	int foundwall;

	next_touch_x = x_inters;
	next_touch_y = y_inters;
	
	if(facing_up)
		next_touch_y --;
	wallhity = wallhitx = 0;
	while(next_touch_x >= 0 && next_touch_x <= data->win_w && next_touch_y >=0 && next_touch_y <= data->win_h)
	{
		printf("x = (%d) y = (%d) w = (%d) h = (%d)\n", next_touch_x, next_touch_y , data->win_w , data->win_h);
		if(check_wall_at(data, next_touch_y, next_touch_x))
		{
			foundwall = true;
			wallhitx = next_touch_x;
			wallhity = next_touch_y;
			break;
		}
		else
		{
			next_touch_x += x_steps;
			next_touch_y += y_steps;
		}
	}
}
void vertical(t_data* data, double ray_angle)
{
	int x_inters;
	int y_inters;
	int x_steps;
	int y_steps;
	int facing_up;
	int facing_left;

	facing_up = facing_left = 1;
	if(ray_angle < M_PI_2 || ray_angle > M_PI_2 * 3)
		facing_left = 0;
	if(ray_angle >= 0 && ray_angle < M_PI)
		facing_up = 0;
	//find the x-cordinate of the closest vertical grid intersection
	x_inters = floor(data->ppos_x / data->sq_dim) * data->sq_dim;
	if(!facing_left)
		x_inters += data->sq_dim;
	//find the y  -cordinate of the closest vertical grid intersection
	y_inters = (data->ppos_x - x_inters) * tanf(ray_angle);
	y_inters += data->ppos_y;
	// if(facing_up)
	// 	x_inters *= -1;
	// else
	// 	y_inters += data->sq_dim;

	x_steps = data->sq_dim;
	if(facing_left)
	{
		x_steps *= -1;
	}


	y_steps = data->sq_dim * tan(ray_angle);
	if((facing_up && x_steps > 0)||(!facing_up && x_steps < 0))
		x_steps *= -1;

	int next_touch_x;
	int next_touch_y;

	int wallhitx;
	int wallhity;
	int foundwall;

	next_touch_x = x_inters;
	next_touch_y = y_inters;
	
	if(facing_left)
		next_touch_x --;
	wallhity = wallhitx = 0;
	while(next_touch_x >= 0 && next_touch_x <= data->win_w && next_touch_y >=0 && next_touch_y <= data->win_h)
	{
		printf("x = (%d) y = (%d)\n", next_touch_x, next_touch_y);
		if(check_wall_at(data, next_touch_x, next_touch_x))
		{
			foundwall = true;
			wallhitx = next_touch_x;
			wallhity = next_touch_y;
			break;
		}
		else
		{
			next_touch_x += x_steps;
			next_touch_y += y_steps;
		}
	}
	//TODO: 10:30 IN 20 SEC4
}
int found_wall(t_data* data, float ray_angle)
{
	// int i;

	horizontal(data, ray_angle);
	horizontal(data, ray_angle+(fabs((float)data->fov/ (float)data->num_rays)));
	(void)ray_angle;

	return 0;
}
void ray_casting(t_data *data)
{
	int i;
	float left_angle;
	float increase;

	increase = fabs((float)data->fov/ (float)data->num_rays);
	normalize_angle(data);
	left_angle = data->p_angle - (data->fov/2);
	// found_wall(data, left_angle);
	i = 1;
	printf("--------------------------\n");
	while(i < data->num_rays)
	{
		horizontal(data, left_angle);
		i++;
		left_angle += increase;
	}
	
}

void draw(void *dt)
{    
    t_data* data;

    data = (t_data*)dt; 
    draw_map(data);
    key_hook(data);
    draw_player(data);
	// printf("cos  = %f , sin = %f\n", cosf(data->p_angle), sinf(data->p_angle));
	ray_casting(data);
	draw_line(data, data->ppos_x, data->ppos_y, (data->ppos_x+cosf(data->p_angle)*15), (data->ppos_y+sinf(data->p_angle)*15));

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
	data->win_w = 1900;
    data->win_h = 1000;
    data->sq_dim = 50;
	data->rotation_angle = 3;
	data->num_rays = 320;
	data->fov = 60*(M_PI / 180);
}

int main(int ac, char **av)
{
    t_data data;

    if(ac!= 2)
        return 1;
	initialize_data(&data);
	lire_map(&data, av[1]);
    len_mapp(&data);
    vue_angle(&data);
    data.mlx_in = mlx_init(data.win_w, data.win_h, "cub3D", 0);
	data.mlx_im = mlx_new_image(data.mlx_in, data.win_w, data.win_h);

    mlx_image_to_window(data.mlx_in, data.mlx_im, 0, 0);
    mlx_loop_hook(data.mlx_in, draw, &data);
    mlx_loop(data.mlx_in);
    return 0;

}