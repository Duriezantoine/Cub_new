/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:32:57 by abernade          #+#    #+#             */
/*   Updated: 2023/11/14 15:55:31 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d_ptr;
	const char	*s_str;

	if (!dest && !src && n)
		return (NULL);
	d_ptr = dest;
	s_str = src;
	i = 0;
	while (i < n)
	{
		d_ptr[i] = s_str[i];
		i++;
	}
	return (dest);
}
