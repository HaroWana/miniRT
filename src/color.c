#include "../inc/miniRT.h"

static int	check_rgb(int nbr)
{
	if (nbr > 0xFF)
		return (0xFF);
	else if (nbr < 0)
		return (0);
	else
		return (nbr);
}

int	color_scale(int colour, float f)
{
	int	r;
	int	g;
	int	b;

	r = check_rgb(f * ((colour >> 24) & 0xFF));
	g = check_rgb(f * ((colour >> 16) & 0xFF));
	b = check_rgb(f * ((colour >> 8) & 0xFF));
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

int	color_prod(int c1, int c2)
{
	int	r;
	int	g;
	int	b;

	r = check_rgb(((float)((c1 >> 24) & 0XFF)
				*((float)((c2 >> 24) & 0xFF) / 0xFF)));
	g = check_rgb((((float)((c1 >> 16) & 0xFF))
				* ((float)((c2 >> 16) & 0xFF) / 0xFF)));
	b = check_rgb((((float)((c1 >> 8) & 0xFF))
				* ((float)((c2 >> 8) & 0xFF) / 0xFF)));
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

int	color_add(int c1, int c2)
{
	int	r;
	int	g;
	int	b;

	r = check_rgb(((c1 >> 24) & 0xFF) + ((c2 >> 24) & 0xFF));
	g = check_rgb((c1 >> 16 & 0xFF) + (c2 >> 16 & 0xFF));
	b = check_rgb((c1 >> 8 & 0xFF) + (c2 >> 8 & 0xFF));
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

int	color_comp(t_lum *light, t_inter hit)
{
	t_vec		light_normal;
	float		gain;
	float		r2;
	float		light_bright;

	light_normal = vecs_sus(light->pos, hit.pos);
	r2 = length2(&light_normal);
	gain = dot(normalized(light_normal), hit.normal);
	if (gain <= 0)
		light_bright = 0;
	else
		light_bright = (light->ratio * gain * 1000)
			/ (4.0 * M_PI * r2);
	return (color_prod(color_add(0, color_scale(hit.rgb, light_bright)),
			light->rgb));
}
