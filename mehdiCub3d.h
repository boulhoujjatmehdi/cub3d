#ifndef MEHDICUBE3D_H
#define MEHDICUBE3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/Include/MLX42.h"

#include "stdio.h"


#define NORTH 0;
#define SOUTH 1;
#define EAST  2;
#define WEST  3;


char	*get_next_line(int fd);

typedef struct s_wall
{
    float horz_found_wall;
    float horz_distance;
    int horz_x;
    int horz_y;

    float vert_found_wall;
    float vert_distance;
    int vert_x;
    int vert_y;
    int direction;
} t_wall;

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
    //player rotation angle
    int     rotation_angle;
    //player radius
    int     p_rad;;
    //player position x
    float   ppos_x;
    //player position y
    float   ppos_y;
    //player view angle
    double  p_angle;


    //raycasting
    //field of view
    float   fov;
    //number of rays
    int     num_rays;
    //minimap scale
    float   mini_scale;

}t_data;


#endif