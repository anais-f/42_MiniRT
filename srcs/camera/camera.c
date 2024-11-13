#include "camera.h"
#include "miniRT.h"

int	init_camera(t_minirt *minirt)
{
	minirt->cam.position = (t_vec3){0.f, 0.f, 2.f};
	minirt->cam.direction = (t_vec3){0.f, 0.f, -1.f};
	minirt->cam.FOV = 60 * M_PI / 180;
	minirt->cam.ratio = (float)WIDTH_WIN / (float)HEIGHT_WIN;
	return (0);
}