#include "miniRT.h"

static bool	in_shadow(t_data *d, t_inter inter, t_vec light)
{
	t_inter	shadow;
	t_vec	tmp;

	shadow = inter_init();
	tmp = vecs_sus(light, inter.pos);
	shadow.t = length(&tmp);
	shadow.ray.pos = vecs_multf(inter.normal, 0.0001);
	shadow.ray.pos = vecs_add(inter.pos, shadow.ray.pos);
	shadow.ray.axe = normalized(vecs_sus(light, shadow.ray.pos));
	return (shapes_intersect(&d->shapes, &shadow));
}

static uint32_t	light_calc(t_data *d, t_inter inter)
{
	uint32_t	color;
	bool		visible;

	color = color_prod(inter.rgb, color_scale(d->amb.rgb, d->amb.ratio));
	visible = !in_shadow(d, inter, d->lum.pos);
	color = color_add(color, visible * color_comp(&d->lum, inter));
	return (color);
}

void	ray_trace(t_data *d)
{
	int			x;
	int			y;
	t_inter		inter;
	t_ray		ray;

	x = -1;
	y = -1;
	while ((uint32_t)++x < d->img->width)
	{
		while ((uint32_t)++y < d->img->height)
		{
			ray = make_ray(&d->cam, vec2_init(((2.0f * x) / d->img->width)
						- 1.0f, ((-2.0f * y) / d->img->height) + 1.0f));
			inter = inter_cpy_ray(&ray);
			if (shapes_intersect(&d->shapes, &inter))
				mlx_put_pixel(d->img, x, y, light_calc(d, inter));
			else
				mlx_put_pixel(d->img, x, y, 255);
		}
		y = -1;
	}
	expose_img(d);
}
