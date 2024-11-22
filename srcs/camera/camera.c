#include "camera.h"
#include "miniRT.h"

// t_ray create_ray(t_camera cam, t_vec2 coord)
// {
// 	t_ray ray;

// 	ray.origin = cam.position;

// 	ray.direction = cam.direction;


// 	float fov_scale = tan(cam.FOV * 0.5); // a mettre dans t_camera

// 	/* ray */

// 	coord.px = (2 * (coord.px + 0.5) / (float)WIDTH_WIN - 1) * cam.ratio * fov_scale;
// 	coord.py = (1 - 2 * (coord.py + 0.5) / (float)HEIGHT_WIN) * fov_scale;


// 	return (ray);
// }