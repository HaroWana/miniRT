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
		color = atoi(split[i]);
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

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !(s))
		return ;
	
	int i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

double	ft_atof(const char *str)
{
	double	int_part;
	double	dec_part;
	double	sign;
	int		i;

	int_part = 0.0;
	dec_part = 0.0;
	sign = 1.0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1.0;
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			dec_part += (pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (int_part + dec_part));
}

char	*get_next_line(int fd)
{
	char	*s;
	char	*c;

	s = malloc(10000);
	c = s;
	while (read(fd, c, 1) > 0 && *c++ != '\n')
		;
	if (c > s)
	{
		*c = 0;
		return (s);
	}
	else
	{
		free(s);
		return (NULL);
	}
}