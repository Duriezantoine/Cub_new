/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:32:26 by abernade          #+#    #+#             */
/*   Updated: 2023/11/14 15:17:55 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move_forward(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

static void	move_backward(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = n - 1;
	while (i > 0)
	{
		dest[i] = src[i];
		i--;
	}
	dest[i] = src[i];
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d_ptr;
	const char	*s_ptr;

	if (!n || (!dest && !src))
		return (dest);
	d_ptr = dest;
	s_ptr = src;
	if (dest < src)
	{
		move_forward(d_ptr, s_ptr, n);
	}
	else
	{
		move_backward(d_ptr, s_ptr, n);
	}
	return (dest);
}
