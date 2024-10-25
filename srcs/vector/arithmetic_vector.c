#include "vector.h"

/*
OK addition
OK soustraction
OK multipilcation
OK division vectoriel

OK produit vectoriel
OK produit scalaire
verif normalisation vecteur (pour le parsing)
normalisation du vecteur (pour le parsing)
calcul de la norme d'un vecteur

*/

t_vec3 add_vec3(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 sub_vec3(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}
