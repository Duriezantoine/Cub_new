/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:50:42 by abernade          #+#    #+#             */
/*   Updated: 2023/11/14 16:04:30 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(size_t s_len, unsigned int start, size_t len)
{
	if (start >= s_len)
	{
		return (0);
	}
	if (s_len - start < len)
	{
		return (s_len - start);
	}
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	size;
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	size = get_size(s_len, start, len);
	substr = malloc(sizeof(char) * (size + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
