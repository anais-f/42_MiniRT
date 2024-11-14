#include "vector.h"

t_vec3	mult_vec3(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

t_vec3	mult_nb_vec3(t_vec3 a, float nb)
{
	return ((t_vec3){a.x * nb, a.y * nb, a.z * nb});
}
