#ifndef MINIRT_H
#define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

/******OTHERS HEADERS******/ 
#include "vector.h"
#include "libft.h"
#include "display_mlx.h"
#include "color.h"

typedef struct s_minirt
{
	t_img	img;

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



/* Others */

int test(t_img *img);


#endif