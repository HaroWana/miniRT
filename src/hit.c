#include "../inc/miniRT.h"

static void	bhaskara(float a, float b, float c, float *res)
{
	float		sqrt_discriminant;
	float		aux[2];

	sqrt_discriminant = sqrt(pow(b, 2) - 4 * a * c);
	aux[0] = (-b - sqrt_discriminant) / (2 * a);
	aux[1] = (-b + sqrt_discriminant) / (2 * a);
	if (aux[0] < aux[1])
	{
		res[0] = aux[0];
		res[1] = aux[1];
	}
	else
	{
		res[0] = aux[1];
		res[1] = aux[0];
	}
}

bool	hit_sp(t_inter *inter, t_elem *elem)
{
	t_vec		v_sp2ray;
	float		time[2];

	v_sp2ray = vecs_sus(inter->ray.pos, elem->pos);
	bhaskara(length2(&inter->ray.axe), 2 * dot(inter->ray.axe, v_sp2ray),
		dot(v_sp2ray, v_sp2ray) - pow(elem->radius, 2), time);
	if ((inter->t > time[0]) && (time[0] > 0))
	{
		inter->t = time[0];
		inter->pos = ray_calculate(&inter->ray, inter->t);
		inter->normal = normalized(vecs_sus(inter->pos, elem->pos));
		inter->rgb = elem->rgb;
		return (true);
	}
	return (false);
}

static float	cy_calc(t_inter inter, t_elem cy, float *y, bool ret[2])
{
	t_vec	v[2];
	t_vec	v_cy2ray;
	float	time[2];
	float	dist[2];

	v[0] = vecs_sus(inter.ray.axe, vecs_multf(cy.axe,
				dot(inter.ray.axe, cy.axe)));
	v[1] = vecs_sus(vecs_sus(inter.ray.pos, cy.pos),
			vecs_multf(cy.axe, dot(vecs_sus(inter.ray.pos, cy.pos), cy.axe)));
	bhaskara(length2(&v[0]), 2 * dot(v[0], v[1]),
		length2(&v[1]) - pow(cy.radius, 2), time);
	v_cy2ray = vecs_sus(cy.pos, inter.ray.pos);
	dist[0] = dot(cy.axe, vecs_sus(vecs_multf(inter.ray.axe, time[0]),
				v_cy2ray));
	dist[1] = dot(cy.axe, vecs_sus(vecs_multf(inter.ray.axe, time[1]),
				v_cy2ray));
	ret[0] = ((dist[0] >= 0) && (dist[0] <= cy.height) && (time[0] > 0.0001));
	ret[1] = ((dist[1] >= 0) && (dist[1] <= cy.height) && (time[1] > 0.0001));
	if ((ret[0] == false) & (ret[1] == true))
	{
		*y = dist[1];
		return (time[1]);
	}
	*y = dist[0];
	return (time[0]);
}

bool	hit_cy(t_inter *inter, t_elem *elem)
{
	bool		ret[2];
	float		time;
	float		y;

	time = cy_calc(*inter, *elem, &y, ret);
	if ((ret[0] || ret[1]) && (inter->t > time) && (time > 0.0001))
	{
		inter->t = time;
		inter->pos = ray_calculate(&inter->ray, inter->t);
		if ((ret[0] == false) & (ret[1] == true))
		{
			inter->normal = normalized(vecs_sus(inter->pos,
						vecs_add(vecs_multf(elem->axe, y), elem->pos)));
			inter->normal = vecs_multf(inter->normal, -1);
		}
		else
			inter->normal = normalized(vecs_sus(inter->pos,
						vecs_add(vecs_multf(elem->axe, y), elem->pos)));
		inter->rgb = elem->rgb;
	}
	return (ret[0] || ret[1]);
}

bool	hit_pl(t_inter *inter, t_elem *elem)
{
	double	time;
	double	den;

	den = dot(normalized(inter->ray.axe), elem->normal);
	if (!den)
		return (false);
	time = dot(vecs_sus(elem->pos, inter->ray.pos), elem->normal) / den;
	if ((inter->t > time) && (time > 0.0001))
	{
		inter->t = time;
		inter->pos = ray_calculate(&inter->ray, inter->t);
		if (dot(inter->ray.axe, elem->normal) > 0)
			elem->normal = vecs_multf(elem->normal, -1);
		inter->normal = elem->normal;
		inter->rgb = elem->rgb;
		return (true);
	}
	return (false);
}
