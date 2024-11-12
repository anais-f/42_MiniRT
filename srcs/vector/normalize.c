#include "vector.h"

/*vector's lenght*/
float	norm_vec3(t_vec3 a)
{
	float length;

	length = sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
	printf("len vecteur =%f\n", length);
	return (length);

}

/* normalize the vector */
t_vec3	normalize_vec3(t_vec3 a)
{
	float length;
	
	length = norm_vec3(a);
	a.x = (a.x / length);
	a.y = (a.y / length);
	a.z = (a.z / length);
	return (a);
}
// A VOIR DANS LE PARSING SI ON RETOURNE UN NOUVEAU VECTEUR OU ON PASSE PAR UN POINTEUR

/* to compare 2 vectors' norms without sqrt -> more efficience */
int	compare_norm_vec3(t_vec3 a, t_vec3 b)
{
	float length_a;
	float length_b;

	length_a = a.x*a.x + a.y*a.y + a.z*a.z;
	length_b = b.x*b.x + b.y*b.y + b.z*b.z;
	if (length_a > length_b)
		return (1);
	else if (length_a < length_b)
		return (2);
	else if (length_a == length_b)
		return (3);
	return (0);
}

