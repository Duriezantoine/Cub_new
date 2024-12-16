/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:37:49 by abernade          #+#    #+#             */
/*   Updated: 2024/03/06 03:15:28 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long	get_integer(char **s)
{
	long	integer;

	integer = 0;
	while (**s >= '0' && **s <= '9')
	{
		integer *= 10;
		integer += (**s - 48);
		(*s)++;
	}
	return (integer);
}

static double	get_decimal(char *s)
{
	double	decimal;
	double	power;

	decimal = 0;
	power = 0.1;
	while (*s >= '0' && *s <= '9')
	{
		decimal += (*s++ - 48) * power;
		power /= 10;
	}
	return (decimal);
}

double	ft_atof(char *s)
{
	long	integer;
	double	decimal;
	int		sign;

	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	while (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	integer = get_integer(&s);
	if (*s == '.')
		s++;
	decimal = get_decimal(s);
	return ((integer + decimal) * sign);
}
