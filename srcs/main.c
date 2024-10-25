#include "miniRT.h"


int main()
{
	printf("here\n");
	printf("Hello Adrien\n");
	t_vec3 a;
	t_vec3 b;
	t_vec3 result;
	float nb = 6;


	a.x = 8;
	a.y = 12;
	a.z = 10;
	b.x = 4;
	b.y = 5;
	b.z = 6;


	result = div_vec3(a, b);
	nb =  norm_vec3(a);

	printf("result x= %f, y= %f, z= %f\n", result.x, result.y, result.z);
	printf("result lenght before= %f\n", nb);
	printf("avant normalisation x=%f, y=%f, z=%f\n", a.x, a.y, a.z);

	result = normalize_vec3(a);
	nb =  norm_vec3(result);
	printf("result lenght after= %f\n", nb);
	printf("apres normalisation x=%f, y=%f, z=%f\n", result.x, result.y, result.z);


	return (0);
}