#include "miniRT.h"

t_vec	vec_cpy(t_vec *v1)
{
	t_vec	vec;

	vec.x = v1->x;
	vec.y = v1->y;
	vec.z = v1->z;
	return (vec);
}

t_vec	vec_init_fs(float x, float y, float z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec2	vec2_init(float u, float v)
{
	t_vec2	vec;

	vec.u = u;
	vec.v = v;
	return (vec);
}
