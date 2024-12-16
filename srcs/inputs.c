/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:32:25 by abernade          #+#    #+#             */
/*   Updated: 2024/12/03 19:46:21 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	strafe_left(t_cubdata *cub)
{
	float	x;
	float	y;
	float	new_angle;

	new_angle = cub->player->angle - M_PI_2;
	x = cub->player->x + POS_INCREMENT * cosf(new_angle);
	y = cub->player->y + POS_INCREMENT * sinf(new_angle);
	if (is_pos_walkable(cub, x, y)==1)
	{
		cub->player->x = x;
		cub->player->y = y;
	}
}

static void	strafe_right(t_cubdata *cub)
{
	float	x;
	float	y;
	float	new_angle;

	new_angle = cub->player->angle + M_PI_2;
	x = cub->player->x + POS_INCREMENT * cosf(new_angle);
	y = cub->player->y + POS_INCREMENT * sinf(new_angle);
	if (is_pos_walkable(cub, x, y)==1)
	{
		cub->player->x = x;
		cub->player->y = y;
	}
}

static void	forward(t_cubdata *cub)
{
	float	x;
	float	y;

	// printf("La\n");
	x = cub->player->x + POS_INCREMENT * cosf(cub->player->angle);
	y = cub->player->y + POS_INCREMENT * sinf(cub->player->angle);
	// printf("Result|%i|",is_pos_walkable(cub, x, y) );
	if (is_pos_walkable(cub, x, y)==1)
	{
		// printf("\n|Xbase|%f|XneW|%f|",cub->player->x, x );
		cub->player->x = x;
		cub->player->y = y;
	}
}

static void	backward(t_cubdata *cub)
{
	float	x;
	float	y;

	x = cub->player->x - POS_INCREMENT * cosf(cub->player->angle);
	y = cub->player->y - POS_INCREMENT * sinf(cub->player->angle);
	if (is_pos_walkable(cub, x, y)==1)
	{
		cub->player->x = x;
		cub->player->y = y;
	}
}

void	input_check(t_cubdata *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_Q))
	{
		cub->player->angle -= ANGLE_INCREMENT;
		if (cub->player->angle < 0.0f)
			cub->player->angle += 2.0f * M_PI;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_E))
	{
		cub->player->angle += ANGLE_INCREMENT;
		if (cub->player->angle > 2.0f * M_PI)
			cub->player->angle -= 2.0f * M_PI;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		forward(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		backward(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		strafe_left(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		strafe_right(cub);
}
