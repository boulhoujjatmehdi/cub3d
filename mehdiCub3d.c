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
int check_mov(t_data *param, double k, double l)
{
	// return 1; //TODO: remove this line

	// printf("-------------------%d -- %d\n" , (int)(l/50), (int)(k/50));
	// printf("-------------------%f -- %f\n", l , k);
	if (param->mat[(int)(k/50)][(int)(l/50)] == '1')
	{
		// printf("was here\n");
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

	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_W) && check_mov(pr, (pr->ppos_y + tmpy) , (pr->ppos_x + tmpx) ))
	{
		pr->ppos_x += cosf(pr->p_angle);
		pr->ppos_y += sinf(pr->p_angle);
		// printf("W = %f - %f\n", pr->ppos_x, pr->ppos_y);

	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_S) && check_mov(pr, (pr->ppos_y-tmpy)  , (pr->ppos_x - tmpx) ))
	{
		pr->ppos_x -= cosf(pr->p_angle);
		pr->ppos_y -= sinf(pr->p_angle);
		// printf("S = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	tmpx = cosf(pr->p_angle + 90 * (M_PI / 180));
	tmpy = sinf(pr->p_angle + 90 * (M_PI / 180));
	if (mlx_is_key_down(pr->mlx_in, MLX_KEY_A) && check_mov(pr, (pr->ppos_y - tmpy) , (pr->ppos_x - tmpx) ))
	{
		pr->ppos_x -= cosf(pr->p_angle + 90 * (M_PI / 180));
		pr->ppos_y -= sinf(pr->p_angle + 90 * (M_PI / 180));
		// printf("A = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_D) && check_mov(pr, (pr->ppos_y + tmpy) , roundf(pr->ppos_x + tmpx) ))
	{
		pr->ppos_x += cosf(pr->p_angle + 90 * (M_PI / 180));
		pr->ppos_y += sinf(pr->p_angle + 90 * (M_PI / 180));
		// printf("D = %f - %f\n", pr->ppos_x, pr->ppos_y);
	}
	else if (mlx_is_key_down(pr->mlx_in, MLX_KEY_Q))
		exit(1);
}
void ray_casting(t_data *data)
{
	int i;
	float left_angle;
	float increase;


	i = 1;
	increase = fabs((float)data->fov/ (float)data->num_rays);
	left_angle = data->p_angle - (data->fov/2);

	// while(1)
	// {
	// 	if(data->ppos_x + cos(left_angle)*i == )
	// }
	// 	draw_line(data, data->ppos_x, data->ppos_y, data->ppos_x + cos(left_angle) * 200, data->ppos_y + sin(left_angle) * 200);
	while(i < data->num_rays)
	{
		draw_line(data, data->ppos_x, data->ppos_y, data->ppos_x + cos(left_angle) * 200, data->ppos_y + sin(left_angle) * 200);
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
	// draw_line(data, data->ppos_x, data->ppos_y, (data->ppos_x+cosf(data->p_angle)*15), (data->ppos_y+sinf(data->p_angle)*15));

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
    data.mlx_in = mlx_init(1900, 1000, "cub3D", 0);
	data.mlx_im = mlx_new_image(data.mlx_in, 1900, 1000);

    mlx_image_to_window(data.mlx_in, data.mlx_im, 0, 0);
    mlx_loop_hook(data.mlx_in, draw, &data);
    mlx_loop(data.mlx_in);
    return 0;

}