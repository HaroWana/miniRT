#include "miniRT.h"

float	sqr(float f)
{
	return (f * f);
}

int	get_color(char **split)
{
	int	color;
	int	res = 0;
	int	i = 0;

	while (split[i])
	{
		color = ft_atoi(split[i]);
		res = (res << 8) | color;
		i++;
	}
	res = (res << 8) | 255;
	return (res);
}

int numDigits(int num)
{
    int digits = 0;
    if (num < 0 || num == 0) digits = 1; // remove this line if '-' counts as a digit
    while (num) {
        num /= 10;
        digits++;
    }
    return digits;
}
