#ifndef MINIRT_H
#define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

/******OTHERS HEADERS******/ 
#include "libft.h"
#include "vector.h"
#include "display_mlx.h"
#include "camera.h"
#include "color.h"


typedef struct s_minirt
{
	t_img		img;
	t_camera	cam;
	t_color		color;

	float	to_radian; // a initialiser : M_PI / 180 // a voir pour mettre dans la structure principale car sera utilise plein de fois a plein d'endroit pour les calculs
	float	to_degree; // radian / 180 * PI -> 180 / M_PI

}	t_minirt;


typedef struct s_ray
{
	t_vec3	origin; // camera position
	t_vec3	direction; // camera orientation
}	t_ray;



/* Parsing */
int	check_argv(int argc, char *str);
int	prasing_map(t_minirt *minirt, char *file); //t_minirt *minirt,
void	print_tab(char **tab);



/* Others */


int test(t_img *img, t_minirt *minirt);
void	render_scene(t_minirt *minirt, t_img *img);
void	init_color(t_minirt *minirt);
int	init_camera(t_minirt *minirt);
void	display_sphere(t_minirt *minirt, int x, int y);



#endif