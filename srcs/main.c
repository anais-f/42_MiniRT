#include "miniRT.h"


int main()
{
	printf("here\n");
	printf("Hello Adrien\n");
	t_vec3 a;
	t_vec3 b;
	t_vec3 result;
	//float nb = 6;


	a.x = 1;
	a.y = 2;
	a.z = 3;
	b.x = 4;
	b.y = 5;
	b.z = 6;


	result = cross_vec3(a, b);

	printf("result x= %f, y= %f, z= %f\n", result.x, result.y, result.z);


	return (0);
}