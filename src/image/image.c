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

static void	drawPixel(int x, int y, int pixel)
{	
	(void)x;
	(void)y;
	// (void)pixel;
	// int	i = y * d.env.size_x + x * 3;
	printf("%u\n", pixel);
	// d.img[i] = ((pixel >> 24) & 0xFF);
	// d.img[i + 1] = ((pixel >> 16) & 0xFF);
	// d.img[i + 2] = ((pixel >> 8) & 0xFF);
	// d.img[x][y][0] = (int)((pixel >> 24) & 0xFF);
	// d.img[x][y][1] = (int)((pixel >> 16) & 0xFF);
	// d.img[x][y][2]= (int)((pixel >> 8) & 0xFF);
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
	while (++y < d.env.size_y)
	{
		while (++x < d.env.size_x)
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

	// for (int i = 0; i < (int)d.env.size_x * (int)d.env.size_y * 3; i++)
	// {
	// 	printf("%d ", d.img[i]);
	// 	if (i % (int)d.env.size_x == 0)
	// 		printf("\n");
	// }
}

// static char *ppm_formatting(int *color, int *line_len, int *count, char *write_pos)
// {
// 	if (*color < 0)
// 		*color = 0;
// 	int digitsNum = snprintf(NULL, 0, "%d", *color); // Calculate the number of digits
// 	if (*line_len + digitsNum + 1 >= 70) {
// 		*write_pos++ = '\n'; // Add newline
// 		*line_len = 0;
// 		if (*count == (int)d.env.size_x * 3)
// 			*count = 0;
// 	} else if (*line_len != 0) {
// 		*write_pos++ = ' '; // Add space between color components
// 		*line_len += 1;
// 	}
// 	*line_len += digitsNum;
// 	return (write_pos);
// }

char	*canvas_to_ppm()
{
    int line_len = 0, count = 0;
    char *ppm = (char *)malloc(sizeof(char) * d.env.size_x * d.env.size_y * 3 * 4 + 20);
    if (!ppm) {
    	ft_error(9, "while attempting to save to PPM");
	}
	// bzero(ppm, sizeof(char) * (int)d.env.size_x * (int)d.env.size_y * 3 * 4 + 20);

    // Construct the PPM header
    sprintf(ppm, "P3\n%d %d\n255\n", d.env.size_x, d.env.size_y);

    // Pointer to the position to write in ppm
    char *write_pos = ppm + strlen(ppm);

	// for (int x = 0; x < d.env.size_x; x++)
	// {
	// 	for (int y = 0; y < d.env.size_y; y++)
	// 	{
	// 		int	i = (x * d.env.size_y + y) * 3;

	// 		int r = d.img[i];
	// 		write_pos = ppm_formatting(&r, &line_len, &count, write_pos);
	// 		write_pos += sprintf(write_pos, "%d", r);
	// 		count++;

	// 		int g = d.img[i + 1];
	// 		write_pos = ppm_formatting(&g, &line_len, &count, write_pos);
	// 		write_pos += sprintf(write_pos, "%d", g);
	// 		count++;

	// 		int b = d.img[i + 2];
	// 		write_pos = ppm_formatting(&b, &line_len, &count, write_pos);
	// 		write_pos += sprintf(write_pos, "%d", b);
	// 		count++;
	// 	}
	// }
    for (int i = 0; i < (int)d.env.size_x * (int)d.env.size_y * 3; i++) {
        int color = d.img[i];
        if (color < 0)
            color = 0;
        int digitsNum = snprintf(NULL, 0, "%d", color); // Calculate the number of digits
        if (line_len + digitsNum + 1 >= 70 || count == (int)d.env.size_x * 3) {
            *write_pos++ = '\n'; // Add newline
            line_len = 0;
            if (count == (int)d.env.size_x * 3)
                count = 0;
        } else if (line_len != 0) {
            *write_pos++ = ' '; // Add space between color components
            line_len++;
        }

        // Write color to write_pos
        write_pos += sprintf(write_pos, "%d", color);
        line_len += digitsNum;
        count++;
    }
    return ppm;
}
