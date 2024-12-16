/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:29:28 by weldo             #+#    #+#             */
/*   Updated: 2024/11/22 01:12:30 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	map_angle(int idx, float projplane_width, float face_angle)
{
	float	proj_x;
	float	angle;

	proj_x = ((((float)idx * 2.0f) - ((float)CAMERA_W - 1.0f)) / \
		((float)CAMERA_W - 1.0f)) * (projplane_width / 2.0f);
	angle = atan2f(proj_x, PROJPLANE_DIST) + face_angle;
	if (angle > 2.0f * M_PI)
		angle -= 2.0f * M_PI;
	else if (angle < 0.0f)
		angle += 2.0f * M_PI;
	return (angle);
}

float	remap(int64_t n, int64_t in_min, int64_t in_max, int64_t out_min, int64_t out_max)
{
	return ((n - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

float	remapf(float n, float in_min, float in_max, \
	float out_min, float out_max)
{
	return ((n - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

float	absolutef(float value)
{
	if (value >= 0)
		return (value);
	return (-value);
}
