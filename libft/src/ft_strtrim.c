/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:44:56 by abernade          #+#    #+#             */
/*   Updated: 2023/11/14 16:26:15 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	first_char_index(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (s[i] && ft_strchr(set, s[i]))
		i++;
	return (i);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*trimmed;
	int		start;
	int		size;
	int		i;

	if (!s || !set)
		return (NULL);
	i = first_char_index(s, set);
	start = i;
	size = 0;
	while (s[i])
	{
		if (!ft_strchr(set, s[i]))
			size = i - start + 1;
		i++;
	}
	trimmed = malloc(sizeof(char) * (size + 1));
	if (!trimmed)
		return (NULL);
	i = -1;
	while (++i < size)
		trimmed[i] = s[start + i];
	trimmed[i] = '\0';
	return (trimmed);
}
