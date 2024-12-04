#include "miniRT.h"

int	init_minirt(t_minirt *minirt)
{
	minirt->cam.direction = normalize_vec3(minirt->cam.direction);
	minirt->cam.world_dir = (t_vec3){0, 0, 1};
	minirt->cam.FOV *= M_PI / 180;
	minirt->cam.aspect_ratio = (float)HEIGHT_WIN / (float)WIDTH_WIN;
	minirt->cam.fov_scale = tan(minirt->cam.FOV * 0.5);
	minirt->to_radian = M_PI / 180;
	minirt->to_degree = 180 / M_PI;
	minirt->cam.theta = theta_calc(minirt->cam.world_dir, minirt->cam.direction);
	return (0);
}
