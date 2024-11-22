#ifndef MINIRT_H
#define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

/******OTHERS HEADERS******/ 
# include "libft.h"
# include "display_mlx.h"
# include "camera.h"
# include "color.h"
# include "objects.h"



typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_hit
{
	t_vec3		position;
	t_vec3		normal;
	double		dst;
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

typedef enum e_items
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	OBJECTS,
}			t_items;
 


/* Parsing */
bool	check_range_items(t_minirt *minirt, t_items items);
bool	is_in_range(float value, float min, float max);
bool	is_valid_float(char *str_float);
char	*ft_iswspace(char *str);
float	ft_atof(const char *str);
int		check_argv(int argc, char *str);
int		convert_color(char **args_color, int *colors_int);
int		parse_ambient_light(char **line_parsed, t_minirt *minirt);
int		parse_camera(char **line_parsed, t_minirt *minirt);
int		parse_color(char *arg_parsed, t_color *color);
int		parse_coordinates(char *arg_parsed, t_vec3 *position);
int		parse_light(char **line_parsed, t_minirt *minirt);
int		parse_line(char *line, t_minirt *minirt);
int		prasing_map(t_minirt *minirt, char *file);
size_t	arr_len(char **arr);
void	ft_free_arr(char **arr);
void	print_arr(char **arr);
int		parse_sphere(char **line_parsed, t_minirt *minirt);
int		parse_plane(char **line_parsed, t_minirt *minirt);
int		parse_cylinder(char **line_parsed, t_minirt *minirt);




/* a changer de header plus tard */
void	render_scene(t_minirt *minirt, t_img *img);

void	init_color(t_minirt *minirt);
int		init_camera(t_minirt *minirt);
int		init_minirt(t_minirt *minirt);
int		init_light(t_minirt *minirt);
int	init_object(t_minirt *minirt);
int	init_ambient_light(t_minirt *minirt);



/* LIGHTS AND COLORS FUNCTIONS */
t_vec3	get_ambient_light(t_minirt *minirt);
double	calcul_light_bright(t_minirt *minirt, t_hit hit);
t_color	get_color_pixel(t_minirt *minirt, t_hit hit);

/* RAYS FUNCTIONS */
t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y);
bool	check_ray_to_light(t_minirt *minirt, t_hit hit, t_vec3 light_dir);

/* OBJECTS FUNCTIONS */
void	hit_point(t_minirt *minirt, t_ray ray, t_hit *hit);
double	object_intersection(t_ray ray, t_object object);
double	sphere_intersection(t_ray ray, t_object sphere);
double	cylinder_intersection(t_ray ray, t_object cylinder);
double	plane_intersection(t_ray ray, t_object plan);
t_vec3	get_normal(t_camera cam, t_hit hit);
t_vec3	get_normal_sphere(t_camera cam, t_hit hit);
t_vec3	get_normal_plane(t_camera cam, t_hit hit);
t_vec3	get_normal_cylinder(t_camera cam, t_hit hit);

#endif