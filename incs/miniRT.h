#ifndef MINIRT_H
#define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>

/******OTHERS HEADERS******/ 
# include "libft.h"
# include "vector.h"
# include "display_mlx.h"
# include "camera.h"
# include "color.h"
# include "objects.h"



typedef struct s_ray
{
	t_vec3	origin; // camera position
	t_vec3	direction; // camera orientation
}	t_ray;

typedef struct s_hit
{
	t_vec3		position;
	t_vec3		normal;
	float		dst;
	t_object	object;
	t_ray		ray;
}	t_hit;


typedef struct s_minirt
{
	t_img			img;
	t_camera		cam;
	t_color			color;
	t_object	 	object[4];
	t_object		*objects;
	t_light			light;
	t_ambient_light	ambient_light;

	float	to_radian;
	float	to_degree;


}	t_minirt;






/* Parsing */
int	check_argv(int argc, char *str);
int	prasing_map(t_minirt *minirt, char *file); //t_minirt *minirt,
void	print_tab(char **tab);


/* Others */
int		test(t_img *img, t_minirt *minirt);


/* a changer de header plus tard */
void	render_scene(t_minirt *minirt, t_img *img);

/* object*/
float	sphere_intersection(t_minirt *minirt, t_ray ray, t_object sphere);
float	cylinder_intersection(t_minirt *minirt, t_ray ray, t_object cylinder);
float	plane_intersection(t_minirt *minirt, t_ray ray, t_object plan);
float	object_intersection(t_minirt *minirt, t_ray ray, t_object object);

void	init_color(t_minirt *minirt);
int		init_camera(t_minirt *minirt);
int		init_minirt(t_minirt *minirt);
int		init_light(t_minirt *minirt);
int	init_object(t_minirt *minirt);
int	init_ambient_light(t_minirt *minirt);

t_vec3 get_ambient_light(t_minirt *minirt);
t_color	get_color_pixel(t_minirt *minirt, t_hit hit);
float	calcul_light_bright(t_minirt *minirt, t_hit hit);


void	hit_point(t_minirt *minirt, t_ray ray, t_hit *hit);
t_vec3	get_normal(t_minirt *minirt, t_hit hit);
t_vec3	get_normal_sphere(t_minirt *minirt, t_hit hit);
t_vec3	get_normal_plane(t_minirt *minirt, t_hit hit);
t_vec3	get_normal_cylinder(t_minirt *minirt, t_hit hit);
t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y);



#endif