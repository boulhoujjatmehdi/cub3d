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

    int     x;//TODO: CHECK IF NEEDED
    int     y;//TODO: CHECK IF NEEDED
    //window: height
    int     win_h;
    //window: width
    int     win_w;
    //square dimentions
    int     sq_dim;
    //player rotation angle
    int     rotation_angle;
    //player position x
    float     ppos_x;
    //player position y
    float     ppos_y;
    //player view angle
    double     p_angle;

    //raycasting
    //field of view
    float fov;
    //number of rays
    int num_rays;

}t_data;


#endif