#ifndef MINIRT_H
#define MINIRT_H

# define RANGE 10

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
# include "array.h"



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
	t_array			objects;
	t_light			light;
	t_ambient_light	ambient_light;
	double			to_radian;
	double			to_degree;
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
int		parse_color(t_minirt *minirt, char *arg_parsed, t_color *color);
int		parse_coordinates(char *arg_parsed, t_vec3 *position);
int		parse_light(char **line_parsed, t_minirt *minirt);
void	parse_line(char *line, t_minirt *minirt);
int		parsing_map(t_minirt *minirt, char *file);
size_t	arr_len(char **arr);
void	ft_free_arr(char **arr);
void	print_arr(char **arr);
int		parse_sphere(char **line_parsed, t_minirt *minirt);
int		parse_plane(char **line_parsed, t_minirt *minirt);
int		parse_cylinder(char **line_parsed, t_minirt *minirt);
char	**split_commas(char const *s, char c);
void	print_parsing(t_minirt *minirt);


t_mat	rodrigues_rot(t_minirt *mini, t_vec3 axis, float theta);
t_mat	matrix_identity(void);
t_mat	multiply_matrix(t_mat a, t_mat b);


t_mat add_mat(t_mat m1, t_mat m2);
t_mat	mult_float_matrix(float a, t_mat b);

int	kb_event(int key, t_minirt *mini);
float	theta_calc(t_vec3 u, t_vec3 v);

/* a changer de header plus tard */
void	render_scene(t_minirt *minirt, t_img *img);
int		init_minirt(t_minirt *minirt);
void	ft_free_exit(t_minirt *minirt, char *line, \
			char **line_parsed, int exit_code);




/* LIGHTS AND COLORS FUNCTIONS */
t_vec3	get_ambient_light(t_minirt *minirt);
double	calcul_light_bright(t_minirt *minirt, t_hit hit);
t_color	get_color_pixel(t_minirt *minirt, t_hit hit);

/* RAYS FUNCTIONS */
t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y);
bool	check_ray_to_light(t_minirt *minirt, t_hit hit, t_vec3 light_dir);

/* OBJECTS FUNCTIONS */
void	hit_point(t_minirt *minirt, t_ray ray, t_hit *hit);
double	object_intersection(t_ray ray, t_object object, t_hit *hit);
double	sphere_intersection(t_ray ray, t_object sphere);
double	cylinder_intersection(t_ray ray, t_object *cylinder, t_hit *hit);
double	plane_intersection(t_ray ray, t_object plan);
t_vec3	get_normal(t_camera cam, t_hit hit);
t_vec3	get_normal_sphere(t_camera cam, t_hit hit);
t_vec3	get_normal_plane(t_camera cam, t_hit hit);
t_vec3	get_normal_cylinder(t_camera cam, t_hit hit);
void	calculate_cap_positions(t_object *cy);
void	calculate_cap_intersections(t_ray ray, t_object *cy, double radius);

#endif