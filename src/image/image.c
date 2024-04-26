#include "miniRT.h"

extern t_data	d;

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

static void	drawPixel(int x, int y, uint32_t pixel)
{	
	(void)pixel;
	int	i = (y * d.env.size_x + x) * 3;

	// d.img[i] = ((pixel >> 24) & 0xFF);
	// d.img[i + 1] = ((pixel >> 16) & 0xFF);
	// d.img[i + 2] = ((pixel >> 8) & 0xFF);
	d.img[i] = (unsigned char)0;
	d.img[i + 1] = (unsigned char)0;
	d.img[i + 2] = (unsigned char)0;
	// printf("%u %u %u\n", d.img[i], d.img[i + 1], d.img[i + 2]);
}

void	ray_trace(t_data *d)
{
	int			x;
	int			y;
	t_inter		inter;
	t_ray		ray;

	x = 0;
	y = 0;
	printf("%u %u\n", d->env.size_x, d->env.size_y);
	while ((uint32_t)++x < d->env.size_x)
	{
		while ((uint32_t)++y < d->env.size_y)
		{
			ray = make_ray(&d->cam, vec2_init(((2.0f * x) / d->env.size_x)
						- 1.0f, ((-2.0f * y) / d->env.size_y) + 1.0f));
			inter = inter_cpy_ray(&ray);
			if (shapes_intersect(&d->shapes, &inter))
				drawPixel(x, y, light_calc(d, inter));
			else
				drawPixel(x, y, 0);
		}
		y = -1;
	}
	// expose_img(d);
}
