#include "vector.h"

/* The dot product gives a scalar (a numerical value), not a new vector.
Several applications : 
- angle measurement: it allows you to calculate the angle between two vectors. 
A positive dot product indicates that the vectors point in similar directions, 
a negative dot product indicates opposite directions, 
and a zero dot product indicates that the vectors are perpendicular.
(A⋅B = ∣∣A∣∣ ∣∣B∣∣ cos(θ))
- vector projection
- calculate diffuse light intensity
- length calculation (to calculate the norm)

A⋅B = A1​B1 ​+ A2​B2 ​+ A3​B3
*/

double	dot_vec3(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
