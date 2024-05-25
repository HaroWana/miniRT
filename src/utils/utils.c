#include "miniRT.h"

bool	ft_isrgb(int color)
{
	if (color >= 0 && color <= 255)
		return (true);
	return (false);
}

bool	ft_isint(char *str)
{
	int	i;

	i = 0;
	while (i < (int)strlen(str) && str[i] != '\n' && str[i] != 'r')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static bool	ft_dotcount(const char *str)
{
	int	dotcount = 0;
	int	i = 0;

	while (str[i])
	{
		if (str[i] == '.' && i == 0)
			return (false);
		else if (str[i] == '.')
		{
			dotcount++;
			if (dotcount > 1)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	ft_isfloat(const char *str)
{
	int	signcount = 0;
	int	i = 0;

	while (str[i] != '\0')
	{
		if (!ft_dotcount(str))
			return (false);
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-'
			&& str[i] != '+' && str[i] != '.')
			return (false);
		else if ((str[i] == '-' || str[i] == '+') && i != 0)
			return (false);
		else if ((str[i] == '-' || str[i] == '+'))
			signcount++;
		i++;
	}
	if (str[strlen(str) - 1] == '.' || signcount > 1
		|| (signcount == 1 && strlen(str) == 1))
		return (false);
	return (true);
}

void	shapes_addback(t_elem **lst, t_elem *new, int *qty)
{
	t_elem	*aux;

	aux = (*lst);
	if (!new)
		return ;
	if (!*lst)
		(*lst) = new;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	new->next = NULL;
	(*qty)++;
}

t_elem	*elem_init(void)
{
	t_elem	*elem;

	elem = malloc(sizeof(t_elem));
	if (!elem)
		return (NULL);
	bzero(elem, sizeof(t_elem));
	return (elem);
}

t_vec	get_coor(char **split)
{
	t_vec	coor;

	coor.x = ft_atof(split[0]);
	coor.y = ft_atof(split[1]);
	coor.z = ft_atof(split[2]);
	return (coor);
}
