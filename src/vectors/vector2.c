#include "miniRT.h"

float	length2(t_vec *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

float	length(t_vec *vec)
{
	return (sqrt(length2(vec)));
}

float	normalize(t_vec *vec)
{
	float	l;

	l = length(vec);
	vec->x /= l;
	vec->y /= l;
	vec->z /= l;
	return (l);
}

t_vec	normalized(t_vec vec)
{
	t_vec	v;

	v = vec_cpy(&vec);
	normalize(&v);
	return (v);
}
