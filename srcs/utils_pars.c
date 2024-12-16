/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:34:13 by aduriez           #+#    #+#             */
/*   Updated: 2024/11/18 08:51:02 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

size_t	ft_strlen_no_new_line(const char *c)
{
	int	count;

	count = 0;
	while (c[count] != '\0' && c[count] != '\n')
		count++;
	return (count);
}

char	*ft_copy_end(char *str, char c)
{
	char	*dest;
	int		x;
	int		i;

	x = 0;
	i = 0;
	while (str[x])
	{
		if (str[x] == c)
			break ;
		x++;
	}
	dest = malloc((sizeof(char *) * (ft_strlen(str) - x + 1)));
	x++;
	while (str[x])
	{
		dest[i] = str[x];
		i++;
		x++;
	}
	dest[i] = '\0';
	return (dest);
}

int dell_space(char *line, int *i)
{

    while(line[*i] == ' ')
        ++(*i);
    return(*i);
}
char	*ft_strdup_new_line(const char *source)
{
	char	*copy;
	int		count;

	count = 0;
	copy = malloc(sizeof(char) * (ft_strlen((char *)source) + 1));
	if (copy == NULL)
		return (NULL);
	while (source[count] != '\n' )
	{
		copy[count] = (char) source[count];
		count++;
	}
	copy[count] = '\0';
	//printf("\n|Je suis copy|%s|", copy);
	return (copy);
}