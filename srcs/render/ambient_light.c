#include "miniRT.h"

void get_ambient_light(t_minirt *minirt)
{
	float r;
	float g;
	float b;

	r = minirt->ambient_light.color.r / 255.f * minirt->ambient_light.brightness;
	g = minirt->ambient_light.color.g / 255.f * minirt->ambient_light.brightness;
	b = minirt->ambient_light.color.b / 255.f * minirt->ambient_light.brightness;
	minirt->ambient_light.color.r = r * 255;
	minirt->ambient_light.color.g = g * 255;
	minirt->ambient_light.color.b = b * 255;
}





// couleur_finale = couleur_objet * (lumière_ambiante * intensité_ambiante) + couleur_directe



// ultiplication de couleurs en RGB

// Pour multiplier deux couleurs, on applique la multiplication composant par composant. Autrement dit, pour deux couleurs C1=(r1,g1,b1)C1​=(r1​,g1​,b1​) et C2=(r2,g2,b2)C2​=(r2​,g2​,b2​), leur multiplication donne une nouvelle couleur C=(r,g,b)C=(r,g,b), où chaque composant est calculé comme suit :

//     r=r1×r2r=r1​×r2​
//     g=g1×g2g=g1​×g2​
//     b=b1×b2b=b1​×b2​

// Cela donne une nouvelle couleur qui est le produit de la couleur de l'objet et de la couleur de la lumière incidente (ou d'autres sources comme l'ambiante).
// Exemple d'application

// Prenons l'exemple d'une lumière ambiante et d'un objet dans la scène. Supposons que l'objet ait une couleur de texture Cobj=(0.5,0.2,0.1)Cobj​=(0.5,0.2,0.1) (un ton rougeâtre), et que la couleur de la lumière ambiante soit Camb=(1.0,1.0,1.0)Camb​=(1.0,1.0,1.0) (lumière blanche). Si l’intensité de la lumière ambiante est 0.30.3, l'effet de la lumière ambiante sur l'objet sera calculé en multipliant chaque composant de couleur :

//     La couleur de la lumière ambiante à intensité 0.3 : Camb=(1.0,1.0,1.0)×0.3=(0.3,0.3,0.3)Camb​=(1.0,1.0,1.0)×0.3=(0.3,0.3,0.3)

//     Multiplier la couleur de l'objet par la lumière ambiante : Cobj×Camb=(0.5,0.2,0.1)×(0.3,0.3,0.3)=(0.5×0.3,0.2×0.3,0.1×0.3)Cobj​×Camb​=(0.5,0.2,0.1)×(0.3,0.3,0.3)=(0.5×0.3,0.2×0.3,0.1×0.3) =(0.15,0.06,0.03)=(0.15,0.06,0.03)

// Cela donne la contribution de la lumière ambiante sur la couleur de l'objet.

// t_color 