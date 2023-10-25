#ifndef MEHDICUBE3D_H
#define MEHDICUBE3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/Include/MLX42.h"
# include "libft/libft.h"
#include "stdio.h"


#define NORTH 0;
#define SOUTH 1;
#define EAST  2;
#define WEST  3;


char	*get_next_line(int fd);

typedef struct s_wall
{
    int horz_found_wall;
    float horz_distance;
    int horz_x;
    int horz_y;

    int vert_found_wall;
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
    int     p_rad;
    //player speed
    int     p_speed;
    //player position x
    float   ppos_x;
    //player position y
    float   ppos_y;
    //player view angle
    float  p_angle;

    //texture for north wall
    mlx_texture_t* txt_n;
    //texture for south wall
    mlx_texture_t* txt_s;
    //texture for east wall
    mlx_texture_t* txt_e;
    //texture for west wall
    mlx_texture_t* txt_w;
    //texture to draw
    mlx_texture_t* txt;
    //floor color
    uint32_t floor_color;
    //ceiling color
    uint32_t ceiling_color;

    //raycasting
    //field of view
    float   fov;
    //number of rays
    int     num_rays;
    //minimap scale
    float   mini_scale;

}t_data;

typedef struct s_ray
{
    //x coordinate of the intersection
	float x_inter;
    //y coordinate of the intersection
	float y_inter;
    //x step
	float x_stp;
    //y step
	float y_stp;
    //ray direction
	int is_up;
    //ray direction
	int is_left;
    //x intersection + x step
	float next_touch_x;
    //y intersection + y step
	float next_touch_y;
    //variable to check if the ray hit a wall
	float check_x;
    //variable to check if the ray hit a wall
	float check_y;
    /*OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO*/
    //iterator i 
    int i;
    //iterator j
    int j;
    //ray angle
    float angle;
    //ray step
    float step;
    //ray test
    bool test;
    //ray lenght
    float lenght;
    //distance to projected plan
    float dist_proj_plan;
    //wall height
    float wall_height;
    //wall x_offset
    float x_offset;
    //wall y_offset
    float y_offset;


}t_ray;



#endif