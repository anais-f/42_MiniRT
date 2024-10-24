#include "vector.h"

//produit vectoriel
/*
Dot Product : Produit scalaire, résultat scalaire, utilisé pour des mesures d'angle et des projections.
Cross Product : Produit vectoriel, résultat vectoriel,
 utilisé pour des directions perpendiculaires et des calculs de surfaces.


*/

/* donne un nouveau vecteur

cross = 0 -> ls deux vecteurs sont parralleles
w(uyvz - uzvy, uzvx - uxvz, uxvy - uyvx)
*/

t_vec3	cross_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y*b.z - a.z*b.y;
	result.y = a.z*b.x - a.x*b.z;
	result.z = a.x*b.y - a.y*b.x;
	return (result);
}