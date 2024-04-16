/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:16:05 by stgerard          #+#    #+#             */
/*   Updated: 2023/09/05 15:40:06 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (src[nb] != '\0')
		nb++;
	if (dstsize != '\0')
	{
		while (i < dstsize - 1 && src[i] != '\0' && src[i] != '\n'
			&& src[i] != '\r' && src[i] != ' ')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (nb);
}
