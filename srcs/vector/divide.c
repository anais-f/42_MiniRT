#include "vector.h"

t_vec3	div_vec3(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x / b.x, a.y / b.y, a.z / b.z});
}

t_vec3	div_denom_vec3(t_vec3 a, float nb)
{
	return ((t_vec3){a.x / nb, a.y / nb, a.z / nb});
}

t_vec3	div_num_vec3(t_vec3 a, float nb)
{
	return ((t_vec3){nb / a.x, nb / a.y, nb / a.z});
}
