/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:34:52 by abernade          #+#    #+#             */
/*   Updated: 2023/11/14 17:07:01 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (dst[i] != '\0')
	{
		if (i + 1 == size)
			return ((size_t)ft_strlen((char *)src) + size);
		i++;
	}
	while (*src != '\0' && i + 1 < size)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	return ((size_t)(ft_strlen(dst) + ft_strlen((char *)src)));
}
