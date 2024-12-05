#include "miniRT.h"
# include <stdio.h>
# define EPSILON 1e-6

void move_camera(t_minirt *mini, t_vec3 direction, float distance)
{
    t_vec3 delta;

    delta = mult_nb_vec3(direction, distance);
    mini->cam.position = add_vec3(mini->cam.position, delta);
}

t_vec3 rotate_vec3(t_vec3 v, t_vec3 axis, float angle)
{
    t_vec3	rotated_v;
    float	cos_angle = cos(angle);
    float	sin_angle = sin(angle);
	float	dot = dot_vec3(axis, v);
	t_vec3	cross = cross_vec3(axis, v);

	// if (norm_vec3(cross) < 1e-6) // Cas particulier : colinéaire ou antiparallèle
    // {
    //     float dot = dot_vec3(v, axis);
    //     if (dot > 0) // Parallèle
    //     {
    //         return v; // Le vecteur reste inchangé
    //     }
    //     else // Antiparallèle
    //     {
    //         // Le vecteur doit être inversé selon l'angle
    //         rotated_v.x = -v.x;
    //         rotated_v.y = -v.y;
    //         rotated_v.z = -v.z;
    //         return rotated_v;
    //     }
    // }


	rotated_v.x = v.x * cos_angle + cross.x * sin_angle + axis.x * dot * (1 - cos_angle);
	rotated_v.y = v.y * cos_angle + cross.y * sin_angle + axis.y * dot * (1 - cos_angle);
	rotated_v.z = v.z * cos_angle + cross.z * sin_angle + axis.z * dot * (1 - cos_angle);
	rotated_v = normalize_vec3(rotated_v);
	return rotated_v;
}

// t_vec3 project_on_horizontal(t_vec3 v) {
//     return (t_vec3){v.x, 0, v.z};
// }

t_mat	rotate_camera(t_minirt *mini, t_vec3 axis, float angle)
{
	float	theta;
	// axis = (t_vec3){0, 1, 0};

    // float original_y = mini->cam.direction.y; // Conserver la composante Y
    // t_vec3 horizontal_dir = project_on_horizontal(mini->cam.direction);
    // horizontal_dir = normalize_vec3(horizontal_dir);

    // // Effectuer la rotation
    // t_vec3 rotated_dir = rotate_vec3(horizontal_dir, axis, angle);

    // // Réintroduire la composante Y d'origine
    // rotated_dir.y = original_y;
    // mini->cam.direction = normalize_vec3(rotated_dir);

	mini->cam.direction = normalize_vec3(rotate_vec3(mini->cam.direction, axis, angle));
	theta = theta_calc(mini->cam.world_dir, mini->cam.direction);
	if (theta * mini->to_degree == 0)
		return (matrix_identity());
	if ((int)(theta * mini->to_degree) == 180)
		return (mult_float_matrix(-1, matrix_identity()));
	t_vec3 normal_cam;
	normal_cam = cross_vec3(mini->cam.world_dir, mini->cam.direction);
	return(rodrigues_rot(mini, normal_cam, theta));
}


int	kb_event(int key, t_minirt *mini)
{
	float move_dst = 0.3;
    t_vec3 up ;
	up = (t_vec3){0, 1, 0};
	up = mult_vec3_matrix((t_vec3){0, 1, 0}, mini->cam.rot_mat);
	up = normalize_vec3(up);
	//printf("up = %f %f %f\n", up.x, up.y, up.z);
	float angle = 30 * mini->to_radian;

	if (key == ESC_KB)
		mlx_loop_end(mini->img.mlx_ptr);

	if (key == W_KB)
		move_camera(mini, mini->cam.direction, move_dst);
    else if (key == S_KB) // on se deplace sur l'axe z
		move_camera(mini, mini->cam.direction, -move_dst);
    else if (key == A_KB)
		move_camera(mini, cross_vec3(up, mini->cam.direction), -move_dst);
    else if (key == D_KB) // on se deplace sur l'axe x
		move_camera(mini, cross_vec3(up, mini->cam.direction), move_dst);
	else if (key == R_KB) // on se deplace sur l'axe y
		move_camera(mini, up, move_dst);
    else if (key == F_KB)
		move_camera(mini, up, -move_dst);

	// else if (key == Q_KB)
	// 	mini->cam.rot_mat = rotate_camera(mini, up, -angle);
	// else if (key == E_KB)
	// 	mini->cam.rot_mat = rotate_camera(mini, up, angle);



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
