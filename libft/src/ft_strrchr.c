/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:47:31 by abernade          #+#    #+#             */
/*   Updated: 2023/11/08 13:42:10 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*save;
	char		chr;

	chr = c;
	save = (char *)0;
	while (*s)
	{
		if (chr == *s)
		{
			save = s;
		}
		s++;
	}
	if (chr == '\0')
	{
		save = s;
	}
	return ((char *)save);
}
