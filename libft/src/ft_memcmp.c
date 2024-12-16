/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:19:47 by abernade          #+#    #+#             */
/*   Updated: 2023/11/14 13:17:48 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = s1;
	ptr2 = s2;
	if (n == 0)
	{
		return (0);
	}
	while (*ptr1 == *ptr2 && n > 0)
	{
		n--;
		if (n == 0)
		{
			return (0);
		}
		ptr1++;
		ptr2++;
	}
	return (*ptr1 - *ptr2);
}
