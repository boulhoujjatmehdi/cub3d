#ifndef MEHDICUBE3D_H
#define MEHDICUBE3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <math.h>
# include "MLX42/Include/MLX42.h"

#include"stdio.h"

char	*get_next_line(int fd);

typedef struct s_data
{
    char    **mat;
    int     height;
    int     width;

    void*   mlx_in;
    void*   mlx_im;
    void*   mlx_wi;

    //window: height
    int     win_h;
    //window: width
    int     win_w;

    //square dimentions
    int     sq_dim;
    //player position x
    int     ppos_x;
    //player position y
    int     ppos_y;
    //player view angle
    double     p_angle;

}t_data;


#endif