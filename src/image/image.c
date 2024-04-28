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
	int	i = y * d.env.size_x + x;

	// d.img[i] = ((pixel >> 24) & 0xFF);
	// d.img[i + 1] = ((pixel >> 16) & 0xFF);
	// d.img[i + 2] = ((pixel >> 8) & 0xFF);
	d.img[i] = (unsigned char)255;
	d.img[i + 1] = (unsigned char)0;
	d.img[i + 2] = (unsigned char)0;
	// d.img[i] = pixel;
	// printf("%u %u %u\n", d.img[i], d.img[i + 1], d.img[i + 2]);
}

void	ray_trace()
{
	int			x;
	int			y;
	t_inter		inter;
	t_ray		ray;

	x = -1;
	y = -1;
	printf("%u %u\n", d.env.size_x, d.env.size_y);
	while ((uint32_t)++x < d.env.size_x)
	{
		while ((uint32_t)++y < d.env.size_y)
		{
			ray = make_ray(&d.cam, vec2_init(((2.0f * x) / d.env.size_x)
						- 1.0f, ((-2.0f * y) / d.env.size_y) + 1.0f));
			inter = inter_cpy_ray(&ray);
			if (shapes_intersect(&d.shapes, &inter))
				drawPixel(x, y, light_calc(&d, inter));
			else
				drawPixel(x, y, 0);
		}
		y = -1;
	}
	// expose_img(d);
}

char	*canvas_to_ppm()
{
    int line_len = 0;
	char	*tmp1, *tmp2, *tmp3, *freer;
	tmp1 = ft_strjoin("P3\n", ft_itoa(d.env.size_x));
	tmp2 = ft_strjoin(" ", ft_itoa(d.env.size_y));
	tmp3 = ft_strjoin(tmp1, tmp2);
    char* ppm = ft_strjoin(tmp3, "\n255\n");
	free(tmp1);
	free(tmp2);
	free(tmp3);
	
    for (int i = 0; d.img[i]; i++)
    {
		int color = (int)(d.img[i]);
		if (color < 0)
			color = 0;
		int digitsNum = numDigits(color);
		printf("color: %d | line_len: %d\n", d.img[i], line_len);
		if (line_len + digitsNum + 1 >= 70)
		{
			freer = ppm;
			ppm = ft_strjoin(ppm, "\n");
			free(freer);
			line_len = 0;
		}
		else if (line_len != 0)
		{
			freer = ppm;
			ppm = ft_strjoin(ppm, " ");
			free(freer);
			line_len++;
		}

		freer = ppm;
		ppm = ft_strjoin(ppm, ft_itoa(color));
		free(freer);
		line_len += digitsNum;

		// if (i % d.env.size_x == 0 && line_len != 0)
		// {
		// 	freer = ppm;
		// 	ppm = ft_strjoin(ppm, "\n");
		// 	free(freer);
		// }
    }
    return (ppm);
}
