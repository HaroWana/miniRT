#include "miniRT.h"

void	cam_init(t_cam *c, float aspect_ratio)
{
	t_vec	upguide;

	upguide = vec_init_fs(0.0f, 0.0f, 1.0f);
	if (c->forward.x == 0 && c->forward.y == 0)
		c->right = vec_init_fs(0.0f, -1.0f, 0.0f);
	else
		c->right = normalized(cross(c->forward, upguide));
	c->up = cross(c->right, c->forward);
	c->w = 2 * tan(c->fov / 2);
	c->h = c->w * aspect_ratio;
}

t_ray	make_ray(t_cam *c, t_vec2 point)
{
	t_vec	axe;
	t_ray	ray;
	t_vec	tmp;

	axe = vecs_multf(c->up, c->h);
	axe = vecs_multf(axe, point.v);
	tmp = vecs_multf(c->right, c->w);
	tmp = vecs_multf(tmp, point.u);
	axe = vecs_add(axe, tmp);
	axe = vecs_add(axe, c->forward);
	ray.pos = c->pos;
	ray.axe = normalized(axe);
	ray.t_max = RAY_T_MAX;
	return (ray);
}
