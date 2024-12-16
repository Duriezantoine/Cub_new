/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:36:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/11/15 13:37:06 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int  check_file_valid(int fd, char **av)//Check open file
{
    fd = open(av[1],O_RDONLY);
    if(fd == -1)
    {
        ft_putstr_fd("Error\nCannot open file\n", 2);
        return (1);
    }
    //Creat conditons with one line
    return(0);
}
