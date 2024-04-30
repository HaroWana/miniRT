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

static int	light_calc(t_data *d, t_inter inter)
{
	int	color;
	bool		visible;

	color = color_prod(inter.rgb, color_scale(d->amb.rgb, d->amb.ratio));
	visible = !in_shadow(d, inter, d->lum.pos);
	color = color_add(color, visible * color_comp(&d->lum, inter));
	return (color);
}

static void	drawPixel(int x, int y, unsigned int pixel)
{	
	mlx_put_pixel(d.img, x, y, pixel);
	d.img_data[y][x] = pixel;
}

void	ray_trace()
{
	t_inter		inter;
	t_ray		ray;

	printf("%u %u\n", d.env.width, d.env.height);
	for (int y = 0; y < d.env.height; y++)
	{
		for (int x = 0; x < d.env.width; x++)
		{
			ray = make_ray(&d.cam, vec2_init(((2.0f * x) / d.env.width)
						- 1.0f, ((-2.0f * y) / d.env.height) + 1.0f));
			inter = inter_cpy_ray(&ray);
			if (shapes_intersect(&d.shapes, &inter))
				drawPixel(x, y, light_calc(&d, inter));
			else
				drawPixel(x, y, 0);
		}
	}

	// for (int i = 0; i < (int)d.env.width * (int)d.env.height * 3; i++)
	// {
	// 	printf("%d ", d.img[i]);
	// 	if (i % (int)d.env.width == 0)
	// 		printf("\n");
	// }
}

static char *ppm_formatting(int *color, int *line_len, int *count, char *write_pos)
{
	if (*color < 0)
		*color = 0;
	int digitsNum = snprintf(NULL, 0, "%d", *color); // Calculate the number of digits
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
	// bzero(ppm, sizeof(char) * (int)d.env.width * (int)d.env.height * 3 * 4 + 20);

    // Construct the PPM header
    sprintf(ppm, "P3\n%d %d\n255\n", d.env.width, d.env.height);

    // Pointer to the position to write in ppm
    char *write_pos = ppm + strlen(ppm);

	for (int y = 0; y < d.env.height; y++)
	{
		for (int x = 0; x < d.env.width; x++)
		{
			// int	i = (x * d.env.height + y) * 3;

			int r = (d.img_data[y][x] >> 24) & 0xFF;
			write_pos = ppm_formatting(&r, &line_len, &count, write_pos);
			write_pos += sprintf(write_pos, "%u", r);
			count++;

			int g = (d.img_data[y][x] >> 16) & 0xFF;
			write_pos = ppm_formatting(&g, &line_len, &count, write_pos);
			write_pos += sprintf(write_pos, "%u", g);
			count++;

			int b = (d.img_data[y][x] >> 8) & 0xFF;
			write_pos = ppm_formatting(&b, &line_len, &count, write_pos);
			write_pos += sprintf(write_pos, "%u", b);
			count++;
		}
	}
    // for (int i = 0; i < (int)d.env.width * (int)d.env.height * 3; i++) {
    //     int color = d.img[i];
    //     if (color < 0)
    //         color = 0;
    //     int digitsNum = snprintf(NULL, 0, "%d", color); // Calculate the number of digits
    //     if (line_len + digitsNum + 1 >= 70 || count == (int)d.env.width * 3) {
    //         *write_pos++ = '\n'; // Add newline
    //         line_len = 0;
    //         if (count == (int)d.env.width * 3)
    //             count = 0;
    //     } else if (line_len != 0) {
    //         *write_pos++ = ' '; // Add space between color components
    //         line_len++;
    //     }

    //     // Write color to write_pos
    //     write_pos += sprintf(write_pos, "%d", color);
    //     line_len += digitsNum;
    //     count++;
    // }
    return ppm;
}
