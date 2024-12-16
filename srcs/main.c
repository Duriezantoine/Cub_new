/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:36:03 by abernade          #+#    #+#             */
/*   Updated: 2024/12/10 16:04:14 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int ac, char **av)
{
	t_cubdata	*cubdata;

	(void)ac;
	(void)av;
	cubdata = debug_data_init(ac, av);
	cubdata_mlx_init(cubdata);
	if (mlx_image_to_window(cubdata->mlx, cubdata->main_img, 0, 0) == -1)
		error_exit(MLX_ERR);
	mlx_key_hook(cubdata->mlx, &key_hook, cubdata);
	mlx_loop_hook(cubdata->mlx, &generic_hook, cubdata);
	mlx_loop(cubdata->mlx);
	delete_cubdata(cubdata);
	return (0);
}
