#include "miniRT.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
	((byte) & 0x80 ? '1' : '0'), \
	((byte) & 0x40 ? '1' : '0'), \
	((byte) & 0x20 ? '1' : '0'), \
	((byte) & 0x10 ? '1' : '0'), \
	((byte) & 0x08 ? '1' : '0'), \
	((byte) & 0x04 ? '1' : '0'), \
	((byte) & 0x02 ? '1' : '0'), \
	((byte) & 0x01 ? '1' : '0')

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
    if (num < 0) digits = 1; // remove this line if '-' counts as a digit
    while (num) {
        num /= 10;
        digits++;
    }
    return digits;
}