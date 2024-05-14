#include "miniRT.h"

extern	t_data	d;

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

static void	putPixel(int x, int y, uint32_t pixel)
{	
	int index = (y * d.env.width + x) * sizeof(uint32_t);
	d.imgData[index++] = (uint8_t)(pixel >> 24);
	d.imgData[index++] = (uint8_t)(pixel >> 16);
	d.imgData[index++] = (uint8_t)(pixel >> 8);
	d.imgData[index] = (uint8_t)(pixel & 0xFF);
}

void	ray_trace(t_data *d)
{
	int			x;
	int			y;
	t_inter		inter;
	t_ray		ray;

	x = -1;
	y = -1;
	while ((uint32_t)++x < d->env.width)
	{
		while ((uint32_t)++y < d->env.height)
		{
			ray = make_ray(&d->cam, vec2_init(((2.0f * x) / d->env.width) - 1.0f,
							((-2.0f * y) / d->env.height) + 1.0f));
			inter = inter_cpy_ray(&ray);
			if (shapes_intersect(&d->shapes, &inter))
				putPixel(x, y, light_calc(d, inter));
			else
				putPixel(x, y, 0);
		}
		y = -1;
	}
	// expose_img(d);
}

static char *ppm_formatting(uint8_t *color, int *line_len, int *count, char *write_pos)
{
	int digitsNum = snprintf(NULL, 0, "%u", *color); // Calculate the number of digits
	if (*line_len + digitsNum + 1 >= 70) {
		*write_pos++ = '\n'; // Add newline
		*line_len = 0;
		if (*count == (int)d.env.height * 3)
			*count = 0;
	} else if (*line_len != 0) {
		*write_pos++ = ' '; // Add space between color components
		*line_len += 1;
	}
	*line_len += digitsNum;
	return (write_pos);
}

char	*canvas_to_ppm()
{
    int line_len = 0, count = 0;
    char *ppm = (char *)malloc(sizeof(char) * d.env.width * d.env.height * 3 * 4 + 20);
    if (!ppm) {
    	ft_error(9, "while attempting to save to PPM");
	}

    // Construct the PPM header
    sprintf(ppm, "P3\n%d %d\n255\n", (int)d.env.width, (int)d.env.height);

    // Pointer to the position to write in ppm
    char *write_pos = ppm + strlen(ppm);

	for (int y = 0; y < d.env.height; y++)
	{
		for (int x = 0; x < d.env.width; x++)
		{
			int index = (y * d.env.width + x) * sizeof(uint32_t);
			uint8_t r = d.imgData[index++];
			write_pos = ppm_formatting(&r, &line_len, &count, write_pos);
			write_pos += sprintf(write_pos, "%u", r);
			count++;

			uint8_t g = d.imgData[index++];
			write_pos = ppm_formatting(&g, &line_len, &count, write_pos);
			write_pos += sprintf(write_pos, "%u", g);
			count++;

			uint8_t b = d.imgData[index];
			write_pos = ppm_formatting(&b, &line_len, &count, write_pos);
			write_pos += sprintf(write_pos, "%u", b);
			count++;
		}
	}
    return (ppm);
}
