/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:29:32 by abernade          #+#    #+#             */
/*   Updated: 2024/12/03 18:07:05 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	print_err_msg(const char *str)
{
	write(2, str, ft_strlen(str));
}

void	error_exit(t_error_code code)
{
	if (code == MLX_ERR)
		print_err_msg(mlx_strerror(mlx_errno));
	else if (code == ASSET_NAME_ERR)
		print_err_msg("Error: Asset name already in use\n");
	else if (code == ASSET_NOT_FOUND)
		print_err_msg("Error: Asset not found\n");
	else if (code == ASSET_DELETE_ERR)
		print_err_msg("Error: Could not delete asset\n");
	else if (code == MMAP_MASK)
		print_err_msg("Error: Minimap mask too small\n");
	else if (code == DOOR_RM)
		print_err_msg("Error: Tried removing a door that doesn't exist\n");
	else if (code == DOOR_WALK)
		print_err_msg("Error: Tried walking on a door that doesn't exist\n");
	exit(code);
}
