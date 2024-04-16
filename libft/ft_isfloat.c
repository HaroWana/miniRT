/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:31:59 by stgerard          #+#    #+#             */
/*   Updated: 2023/09/06 15:10:44 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_isfloat2(const char *str)
{
	int	pointcount;
	int	i;

	i = 0;
	pointcount = 0;
	while (str[i])
	{
		if (str[i] == '.' && i == 0)
			return (false);
		else if (str[i] == '.')
		{
			pointcount++;
			if (pointcount > 1)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	ft_isfloat(const char *str)
{
	int	signcount;
	int	i;

	i = 0;
	signcount = 0;
	while (str[i] != '\0')
	{
		if (!ft_isfloat2(str))
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
	if (str[ft_strlen(str) - 1] == '.' || signcount > 1
		|| (signcount == 1 && ft_strlen(str) == 1))
		return (false);
	return (true);
}
