/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:16:39 by abernade          #+#    #+#             */
/*   Updated: 2023/11/08 13:36:01 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	result_size(int n)
{
	int	len;

	if (!n)
	{
		return (1);
	}
	len = 0;
	if (n < 0)
	{
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_abs(int n)
{
	if (n < 0)
	{
		return (-n);
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		mod;

	len = result_size(n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (result);
	result[len] = '\0';
	if (!n)
	{
		result[0] = '0';
	}
	if (n < 0)
	{
		result[0] = '-';
	}
	while (n)
	{
		mod = n % 10;
		n /= 10;
		len--;
		result[len] = ft_abs(mod) + '0';
	}
	return (result);
}
