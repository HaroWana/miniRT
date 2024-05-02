#include "miniRT.h"

t_inter	inter_init(void)
{
	t_inter	inter;

	inter.ray.pos.x = 0.0f;
	inter.ray.pos.y = 0.0f;
	inter.ray.pos.z = 0.0f;
	inter.ray.axe.x = 0.0f;
	inter.ray.axe.y = 1.0f;
	inter.ray.axe.z = 0.0f;
	inter.ray.t_max = INFINITY;
	inter.t = INFINITY;
	return (inter);
}

t_inter	inter_cpy(t_inter *inter1)
{
	t_inter	inter;

	ray_eq(&inter.ray, &inter1->ray);
	inter.t = inter1->t;
	inter.rgb = inter1->rgb;
	return (inter);
}

t_inter	inter_cpy_ray(t_ray *ray1)
{
	t_inter	inter;

	ray_eq(&inter.ray, ray1);
	inter.t = ray1->t_max;
	ft_bzero(&inter.pos, 0);
	return (inter);
}

void	inter_eq(t_inter *inter1, t_inter *inter2)
{
	*inter1 = inter_cpy_ray(&inter2->ray);
	inter1->t = inter2->t;
	inter1->rgb = inter2->rgb;
}
