#include <mez/merize/merize.h> //make sure this is included first
#include "mezvector.h"

Vector Vector::normalize()
{
	float m = magnitude();
	if (!m) return Vector();
	return Vector(x / m, y / m, z / m);
}

void Vector::normalize_inplace()
{
	float m = magnitude();
	if (!m) return;
	x /= m;
	y /= m;
	z /= m;
}

float Vector::magnitude()
{
	return sqrtf((x*x)+(y*y)+(z*z));
}

// 1 / sqrt(2)
const float norma = 0.70710678118654752440084436210485f;

float clampm11(float i) { if (i < -1) return -1; if (i > 1) return 1; return i; }
void Vector::fakenormalize_inplace()
{
	x = clampm11(x / norma);
	z = clampm11(z / norma);
	y = clampm11(y / norma);
}
