#include "vector.h"

/*
OK addition
OK soustraction
OK multipilcation
OK division vectoriel

produit vectoriel
produit scalaire
verif normalisation vecteur (pour le parsing)
normalisation du vecteur (pour le parsing)
calcul de la norme d'un vecteur

A voir diff entre :
dot product = produit scalaire
cross product = produit vectoriel
*/

t_vec3 add_vec3(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 sub_vec3(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3 mult_vec3(t_vec3 a, float nb)
{
	return (t_vec3){a.x * nb, a.y * nb, a.z * nb};
}

t_vec3 div_denom_vec3(t_vec3 a, float nb)
{
	return (t_vec3){a.x / nb, a.y / nb, a.z / nb};
}

t_vec3 div_num_vec3(t_vec3 a, float nb)
{
	return (t_vec3){nb / a.x, nb / a.y, nb / a.z};
}