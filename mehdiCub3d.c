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


void draw(void *dt)
{
    t_data* data;
    data = (t_data*)dt;
    int i;
    int j;
    i = 0;

    while(data->mat[i])
    {
        j = 0;
        while (data->mat[i][j])
        {
            if(data->mat[i][j] == '1')
                draw_square(data, j, i, 0x42f5ad);
            else if(data->mat[i][j] == '0')
                draw_square(data, j, i, 0xffffff);
            j++;
        }
        i++;
    }

}
void vue_angle(t_data *param)
{
	int y = 0;
	int x;
	while (param->mat[y] != NULL)
	{
		x = 0;
		while (param->mat[y][x] != '\0')
		{
			if(param->mat[y][x] == 'N')
				param->p_angle = 0;
			else if(param->mat[y][x] == 'E')
				param->p_angle = M_PI_2;
			else if(param->mat[y][x] == 'S')
				param->p_angle = M_PI;
			else if(param->mat[y][x] == 'W')
				param->p_angle = M_PI_2 * 3;
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
    t_data data;

    if(ac!= 2)
        return 1;
	lire_map(&data, av[1]);
    len_mapp(&data);
    vue_angle(&data);
    data.win_w = 1900;
    data.win_h = 1000;
    data.sq_dim = 50;
    data.mlx_in = mlx_init(1900, 1000, "cub3D", 0);
	data.mlx_im = mlx_new_image(data.mlx_in, 1900, 1000);

    mlx_image_to_window(data.mlx_in, data.mlx_im, 0, 0);
    mlx_loop_hook(data.mlx_in, draw, &data);
    mlx_loop(data.mlx_in);
    return 0;

}