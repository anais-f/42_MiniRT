#include "miniRT.h"
# include <stdio.h>
# define EPSILON 1e-6

static void move_camera(t_minirt *mini, t_vec3 direction, float distance)
{
    t_vec3 delta;

    delta = mult_nb_vec3(direction, distance);
    mini->cam.position = add_vec3(mini->cam.position, delta);
}

t_vec3 rotate_vec3(t_vec3 v, t_vec3 axis, float angle)
{
    t_vec3 rotated_v;
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
	float dot = dot_vec3(axis, v);
	t_vec3 cross = cross_vec3(axis, v);

	rotated_v.x = v.x * cos_angle + cross.x * sin_angle + axis.x * dot * (1 - cos_angle);
	rotated_v.y = v.y * cos_angle + cross.y * sin_angle + axis.y * dot * (1 - cos_angle);
	rotated_v.z = v.z * cos_angle + cross.z * sin_angle + axis.z * dot * (1 - cos_angle);
	return rotated_v;
	
	axis = normalize_vec3(axis);

    
    // Calcul de la rotation de Rodrigues
    rotated_v.x = v.x * cos_angle + cross_vec3(axis, v).x * sin_angle + axis.x * dot_vec3(axis, v) * (1 - cos_angle);
    rotated_v.y = v.y * cos_angle + cross_vec3(axis, v).y * sin_angle + axis.y * dot_vec3(axis, v) * (1 - cos_angle);
    rotated_v.z = v.z * cos_angle + cross_vec3(axis, v).z * sin_angle + axis.z * dot_vec3(axis, v) * (1 - cos_angle);
    return rotated_v;
}

t_vec3 rotate_y(t_vec3 v, float angle)
{
    t_vec3 rotated_v;
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);

    rotated_v.x = v.x * cos_angle - v.z * sin_angle;
    rotated_v.y = v.y;
    rotated_v.z = v.x * sin_angle + v.z * cos_angle;

    return rotated_v;
}

t_mat	rotate_camera(t_minirt *mini, t_vec3 axis, float angle)
{
	float	theta;
	t_vec3	new;
	//axis = (t_vec3){0, 1, 0};

	new = normalize_vec3(rotate_vec3(mini->cam.direction, axis, angle));
	//new = rotate_y(mini->cam.direction, angle);
	mini->cam.direction = new;
	theta = theta_calc(mini->cam.world_dir, new);
  	if (fabs(theta) < EPSILON)
		return (matrix_identity());
    if (fabs(theta - M_PI) < EPSILON)
		return (mult_float_matrix(-1, matrix_identity()));
	t_vec3 normal_cam;
	normal_cam = cross_vec3(mini->cam.world_dir, new);
	if (norm_vec3(normal_cam) < EPSILON)
		return (matrix_identity());
		
	return(rodrigues_rot(mini, normal_cam, theta));
}

// t_vec3 rotate_vec3(t_vec3 v, t_vec3 axis, float angle)
// {
//     t_vec3 rotated_v;
//     float cos_angle = cos(angle);
//     float sin_angle = sin(angle);
    
//     rotated_v.x = v.x * cos_angle 
//                 + cross_vec3(axis, v).x * sin_angle 
//                 + axis.x * (1 - cos_angle) * (axis.x * v.x + axis.y * v.y + axis.z * v.z);
//     rotated_v.y = v.y * cos_angle 
//                 + cross_vec3(axis, v).y * sin_angle 
//                 + axis.y * (1 - cos_angle) * (axis.x * v.x + axis.y * v.y + axis.z * v.z);
//     rotated_v.z = v.z * cos_angle 
//                 + cross_vec3(axis, v).z * sin_angle 
//                 + axis.z * (1 - cos_angle) * (axis.x * v.x + axis.y * v.y + axis.z * v.z);

//     return rotated_v;
// }

// void rotate_camera_y(t_minirt *mini, float angle)
// {
//     t_vec3 y_axis = {0, 1, 0}; // Axe Y pour la rotation
// 	//t_vec3 right = normalize_vec3(cross_vec3(y_axis, mini->cam.direction));
//     mini->cam.direction = normalize_vec3(rotate_vec3(mini->cam.direction, y_axis, angle));
    
//     // Mettre à jour l'axe horizontal (right)
//     mini->cam.right = normalize_vec3(cross_vec3(y_axis, mini->cam.direction));
    
//     // Mettre à jour la matrice de rotation
//     // On utilise une méthode explicite si nécessaire ou on construit la matrice avec l'axe actuel
//     // (ici simplifié pour garder le contexte clair)
// }

// 	// else if (key == Q_KB)
// 	// 	rotate_camera_y(mini, -angle);
// 	// else if (key == E_KB)
// 	// 	rotate_camera_y(mini, angle);


int	kb_event(int key, t_minirt *mini)
{
	float move_speed = 0.3;
    t_vec3 up ;
	up = mult_vec3_matrix((t_vec3){0, 1, 0}, mini->cam.rot_mat);
	up = normalize_vec3(up);
	printf("up = %f %f %f\n", up.x, up.y, up.z);
	float angle = 45 * mini->to_radian;

	if (key == ESC_KB)
		mlx_loop_end(mini->img.mlx_ptr);
	if (key == W_KB)
		move_camera(mini, mini->cam.direction, move_speed);
    else if (key == S_KB) // on se deplace sur l'axe z
		move_camera(mini, mini->cam.direction, -move_speed);
    else if (key == A_KB)
		move_camera(mini, cross_vec3(up, mini->cam.direction), -move_speed);
    else if (key == D_KB) // on se deplace sur l'axe x
		move_camera(mini, cross_vec3(up, mini->cam.direction), move_speed);
	else if (key == R_KB) // on se deplace sur l'axe y
		move_camera(mini, up, move_speed);
    else if (key == F_KB)
		move_camera(mini, up, -move_speed);
	else if (key == Q_KB)
		mini->cam.rot_mat = rotate_camera(mini, up, -angle);
	else if (key == E_KB)
		mini->cam.rot_mat = rotate_camera(mini, up, angle);



	render_scene(mini, &mini->img);
    mlx_put_image_to_window(mini->img.mlx_ptr, mini->img.win_ptr, mini->img.img, 0, 0);
	return (0);
}

int	ft_mouse_event(int button, int x, int y, t_img *img)
{
	(void) x;
	(void) y;
	(void)button;
	(void)img;
	return (0);
}

void	mlx_launch_event_and_loop(t_img *img)
{
	mlx_mouse_hook(img->win_ptr, ft_mouse_event, img);
	mlx_hook(img->win_ptr, 02, 1L << 0, kb_event, img);
	mlx_hook(img->win_ptr, 17, 0L, mlx_loop_end, img->mlx_ptr);
	mlx_loop(img->mlx_ptr);
}
