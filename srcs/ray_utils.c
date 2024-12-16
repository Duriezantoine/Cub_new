/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:02:59 by abernade          #+#    #+#             */
/*   Updated: 2024/12/05 15:22:21 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	ray_first_step_v(t_point *point, t_player *p, t_ray *ray)
{
	static int count = 0;
	float	int_part;
	bool	half_block;

	if (modff(point->x, &int_part) < 0.5f)
	{
		point->x = floorf(p->x) + (ray->step_x > 0.f) / 2.f;
		half_block = (ray->step_x > 0.f);
	}
	else
	{
		point->x = int_part + 0.5f + (ray->step_x > 0.f) / 2.f;
		half_block = !(ray->step_x > 0.f);
	}
	point->y = -ray->slope * (p->x - point->x) + p->y;
	count++;
	return (half_block);
}

bool	ray_first_step_h(t_point *point, t_player *p, t_ray *ray)
{
	float	int_part;
	bool	half_block;

	if (modff(point->y, &int_part) < 0.5f)
	{
		point->y = floorf(p->y) + (ray->step_y > 0.f) / 2.f;
		half_block = (ray->step_y > 0.f);
	}
	else
	{
		point->y = int_part + 0.5f + (ray->step_y > 0.f) / 2.f;
		half_block = !(ray->step_y > 0.f);
	}
	point->x = p->x + ray->ninv_slope * (p->y - point->y);
	return (half_block);
}

void	save_v_inter(t_ray *ray, t_point *point, t_player *p)
{
	ray->v_inter_x = point->x;
	ray->v_inter_y = point->y;
	ray->v_dist = sqrtf((p->x - point->x) * (p->x - point->x) \
		+ (p->y - point->y) * (p->y - point->y));
}

void	save_h_inter(t_ray *ray, t_point *point, t_player *p)
{
	ray->h_inter_x = point->x;
	ray->h_inter_y = point->y;
	ray->h_dist = sqrtf((p->x - point->x) * (p->x - point->x) \
		+ (p->y - point->y) * (p->y - point->y));
}
