/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:16:58 by aduriez           #+#    #+#             */
/*   Updated: 2023/12/20 14:58:43 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_save_line(char *res)
{
	char	*line;
	int		i;
	int		size_to_nl;

	i = 0;
	if (!res)
		return (NULL);
	size_to_nl = ft_strlen_to_nl(res);
	line = malloc(size_to_nl + 2);
	if (line == NULL)
		return (NULL);
	line[size_to_nl] = 0;
	while (res && res[i] != '\n' && res[i])
	{
		line[i] = res[i];
		i++;
	}
	if (res && res[i] == '\n')
		line[i] = '\n';
	line[i + 1] = 0;
	return (line);
}

char	*free_all(char *s1, char *s2, char *s3)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	if (!s3)
		return (NULL);
	return (s3);
}

char	*ft_delete_line(char *res)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!res)
		return (NULL);
	while (res && res[i] && res[i] != '\n')
		i++;
	if (res[i] == '\n')
		i++;
	tmp = ft_strdup(&res[i]);
	if (!tmp)
		return (NULL);
	free_all(res, NULL, NULL);
	return (tmp);
}

char	*ft_next_line(int fd, char *res)
{
	int		reading;
	char	*buffer;
	char	*stash;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!res)
		stash = ft_strdup("");
	else
		stash = ft_strdup(res);
	if (!buffer)
		return (free_all(buffer, res, stash));
	while (!(find_nl(stash)))
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading < 1)
			return (free_all(buffer, res, stash));
		buffer[reading] = 0;
		tmp = ft_strjoin_gnl(stash, buffer);
		free(stash);
		stash = tmp;
	}
	free_all(buffer, res, NULL);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd == -1)  // Cas de nettoyage ici
	{
		if (res)
		{
			free(res);
			res = NULL;
		}
		return (NULL);
	}
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	res = ft_next_line(fd, res);
	if (!res || !*res)  // Protection contre NULL
	{
		if (res)
			free(res);
		res = NULL;
		return (NULL);
	}
	line = ft_save_line(res);
	res = ft_delete_line(res);
	return (line);
}
