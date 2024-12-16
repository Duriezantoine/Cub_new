/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 04:00:11 by abernade          #+#    #+#             */
/*   Updated: 2024/12/05 17:07:24 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static float	get_door_state(t_cubdata *cub, t_point *p)
{
	t_door	*door;

	door = search_door(cub->active_doors, p->x, p->y);
	if (!door)
		return (0.f);
	else
		return (door->state);
}

static bool	check_for_collision_v(t_cubdata *cub, int idx, t_point *p, \
	bool check_for_doors)
{
	float	int_part;

	if (!check_for_doors)
	{
		if (map_element_at_pos(cub->map, p->x + 0.01f * cub->rays[idx].step_x\
			, p->y) == '1')
		{
			save_v_inter(&cub->rays[idx], p, cub->player);
			return (true);
		}
		else
			return (false);
	}
	else if (map_element_at_pos(cub->map, p->x, p->y) == DOOR_CHAR_Y)
	{
		if (modff(p->y, &int_part) >= get_door_state(cub, p) / DOOR_OPEN_FRAMES)
		{
			save_v_inter(&cub->rays[idx], p, cub->player);
			return (true);
		}
	}
	return (false);
}

static bool	check_for_collision_h(t_cubdata *cub, int idx, t_point *p, \
	bool check_for_doors)
{
	float	int_part;

	if (!check_for_doors)
	{
		if (map_element_at_pos(cub->map, p->x, \
			p->y + 0.01f * cub->rays[idx].step_y) == '1')
		{
			save_h_inter(&cub->rays[idx], p, cub->player);
			return (true);
		}
		else
			return (false);
	}
	else if (map_element_at_pos(cub->map, p->x, p->y) == DOOR_CHAR_X)
	{
		if (modff(p->x, &int_part) \
			>= get_door_state(cub, p) / DOOR_OPEN_FRAMES)
		{
			save_h_inter(&cub->rays[idx], p, cub->player);
			return (true);
		}
	}
	return (false);
}

void	v_collision(t_cubdata *cub, int idx)
{
	t_point	pos;
	float	yo;
	int		dof;
	bool	check_for_doors;

	cub->rays[idx].v_dist = 1000000.f;
	pos.x = cub->player->x;
	pos.y = cub->player->y;
	if (cub->rays[idx].slope == INFINITY)
		return ;
	check_for_doors = ray_first_step_v(&pos, cub->player, &cub->rays[idx]);
	yo = cub->rays[idx].step_x * cub->rays[idx].slope;
	dof = 0;
	while (dof++ < 30)
	{
		if (check_for_collision_v(cub, idx, &pos, check_for_doors))
			break ;
		pos.y += yo;
		pos.x += cub->rays[idx].step_x;
		check_for_doors = !check_for_doors;
	}
}

void	h_collision(t_cubdata *cub, int idx)
{
	t_point	pos;
	float	xo;
	int		dof;
	bool	check_for_doors;

	cub->rays[idx].h_dist = 1000000.f;
	pos.x = cub->player->x;
	pos.y = cub->player->y;
	if (cub->rays[idx].ninv_slope == INFINITY)
		return ;
	check_for_doors = ray_first_step_h(&pos, cub->player, &cub->rays[idx]);
	xo = -cub->rays[idx].step_y * cub->rays[idx].ninv_slope;
	dof = 0;
	while (dof++ < 30)
	{
		if (check_for_collision_h(cub, idx, &pos, check_for_doors))
			break ;
		pos.x += xo;
		pos.y += cub->rays[idx].step_y;
		check_for_doors = !check_for_doors;
	}
}
