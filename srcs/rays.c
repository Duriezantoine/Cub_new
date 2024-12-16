/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:00:54 by abernade          #+#    #+#             */
/*   Updated: 2024/12/10 17:02:15 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	prepare_ray(t_ray *ray, float projplane_w, float p_angle, int i)
{
	ray->angle = map_angle(i, projplane_w, p_angle);
	if (ray->angle > 2.0f * M_PI)
		ray->angle -= 2.0f * M_PI;
	else if (ray->angle < 0.0f)
		ray->angle += 2.0f * M_PI;
	ray->slope = tanf(ray->angle);
	if (ray->slope == 0.0f)
		ray->ninv_slope = INFINITY;
	else if (ray->slope != INFINITY && ray->slope != NAN && ray->slope)
		ray->ninv_slope = -1 / ray->slope;
	else
		ray->ninv_slope = 0.0f;
	if (ray->angle < M_PI_2 || ray->angle > M_3PI_2)
		ray->step_x = 0.5f;
	else
		ray->step_x = -0.5f;
	if (ray->angle < M_PI)
		ray->step_y = 0.5f;
	else
		ray->step_y = -0.5f;
}

static void	update_ray_door(t_cubdata *cub, int idx, char ray_type)
{
	t_door	*door;
	float	door_state;
	float	discard;

	cub->rays[idx].wall_tx = get_asset(cub->asset_list, DOOR_TX);
	if (ray_type == 'v')
		door = search_door(cub->active_doors, cub->rays[idx].v_inter_x, \
			cub->rays[idx].v_inter_y);
	else
		door = search_door(cub->active_doors, cub->rays[idx].h_inter_x, \
			cub->rays[idx].h_inter_y);
	if (!door)
		door_state = 0;
	else
		door_state = door->state;
	if (ray_type == 'v')
		cub->rays[idx].offset = modff(cub->rays[idx].v_inter_y, &discard) \
			- ((float)door_state / DOOR_OPEN_FRAMES);
	else
		cub->rays[idx].offset = modff(cub->rays[idx].h_inter_x, &discard) \
			- ((float)door_state / DOOR_OPEN_FRAMES);
	(void)discard;
}

static void	update_ray_wall(t_cubdata *cub, int idx, char ray_type)
{
	float	discard;

	if (ray_type == 'v')
	{
		if (cub->rays[idx].angle > M_PI_2 && cub->rays[idx].angle < M_3PI_2)
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, EAST_TX);
		else
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, WEST_TX);
		cub->rays[idx].offset = modff(cub->rays[idx].v_inter_y, &discard);
	}
	else
	{
		if (cub->rays[idx].angle < M_PI)
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, NORTH_TX);
		else
			cub->rays[idx].wall_tx = get_asset(cub->asset_list, SOUTH_TX);
		cub->rays[idx].offset = modff(cub->rays[idx].h_inter_x, &discard);
	}
	(void)discard;
}

static void	update_ray(t_cubdata *cub, int idx)
{
	float	discard;

	if (cub->rays[idx].v_dist > 1000.f && cub->rays[idx].h_dist > 1000.f)
		cub->rays[idx].ray_hit = false;
	else
	{
		cub->rays[idx].ray_hit = true;
		if (cub->rays[idx].v_dist < cub->rays[idx].h_dist)
		{
			if (map_element_at_pos(cub->map, cub->rays[idx].v_inter_x, \
				cub->rays[idx].v_inter_y) == DOOR_CHAR_Y)
				update_ray_door(cub, idx, 'v');
			else
				update_ray_wall(cub, idx, 'v');
		}
		else
		{
			if (map_element_at_pos(cub->map, cub->rays[idx].h_inter_x, \
				cub->rays[idx].h_inter_y) == DOOR_CHAR_X)
				update_ray_door(cub, idx, 'h');
			else
				update_ray_wall(cub, idx, 'h');
		}
	}
	(void)discard;
}

void	update_rays(t_cubdata *cub)
{
	int	i;

	i = 0;
	while (i < CAMERA_W)
	{
		prepare_ray(&cub->rays[i], cub->projplane_w, cub->player->angle, i);
		v_collision(cub, i);
		h_collision(cub, i);
		update_ray(cub, i);
		i++;
	}
}
