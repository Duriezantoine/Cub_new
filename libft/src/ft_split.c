/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:15:02 by abernade          #+#    #+#             */
/*   Updated: 2023/11/14 17:00:52 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			in_word = 1;
			count++;
		}
		else if (in_word && *s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static void	free_alls(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	*next_str(const char *s, char c)
{
	char	*next_c;
	char	*substr;

	next_c = ft_strchr(s, c);
	if (!next_c)
	{
		next_c = ft_strchr(s, '\0');
	}
	substr = ft_substr(s, 0, next_c - s);
	return (substr);
}

static void	fill_result(char **result, int size, char const *s, char c)
{
	int	i;

	i = 0;
	while (i < size)
	{
		while (*s == c)
			s++;
		result[i] = next_str(s, c);
		if (!result[i])
		{
			free_alls(result);
			result = NULL;
			return ;
		}
		s += ft_strlen(result[i]);
		i++;
	}
	result[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**result;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	fill_result(result, count, s, c);
	return (result);
}
