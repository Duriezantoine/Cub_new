/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 03:51:08 by abernade          #+#    #+#             */
/*   Updated: 2024/12/10 15:46:52 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

uint32_t	get_color(const mlx_texture_t *tx, int x, int y)
{
	uint32_t	color;
	int			idx;

	idx = (y * tx->width + x) * 4;
	color = ((uint32_t)tx->pixels[idx++] << 24);
	color |= ((uint32_t)tx->pixels[idx++] << 16);
	color |= ((uint32_t)tx->pixels[idx++] << 8);
	color |= (uint32_t)tx->pixels[idx];
	return (color);
}

void	merge_textures(mlx_texture_t *dest, mlx_texture_t *src, int x, int y)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	color;

	j = 0;
	while (j < src->height)
	{
		i = 0;
		while (i < src->width)
		{
			color = get_color(src, i, j);
			if (color & 0xFF)
				pixel_to_texture(dest, i + x, j + y, color);
			i++;
		}
		j++;
	}
}

void	texture_to_image(mlx_texture_t *tx, mlx_image_t *img)
{
	float		wratio;
	float		hratio;
	uint32_t	x;
	uint32_t	y;
	int			index;

	if (tx->width == img->width && tx->height == img->height)
		ft_memcpy(img->pixels, tx->pixels, tx->width * tx->height * 4);
	else
	{
		wratio = (float)tx->width / img->width;
		hratio = (float)tx->height / img->height;
		y = 0;
		while (y < img->height)
		{
			x = -1;
			while (++x < img->width)
			{
				index = (int)(y * hratio) *tx->width + (int)(x * wratio);
				((int *)img->pixels)[y * img->width + x] \
					= ((int *)tx->pixels)[index];
			}
			y++;
		}
	}
}

void	pixel_to_texture(mlx_texture_t *tx, uint32_t x, uint32_t y, \
	uint32_t color)
{
	uint8_t	*index;

	index = &tx->pixels[(y * tx->width + x) * 4];
	*(index++) = (uint8_t)(color >> 24);
	*(index++) = (uint8_t)(color >> 16);
	*(index++) = (uint8_t)(color >> 8);
	*index = (uint8_t)(color & 0xFF);
}

mlx_texture_t	*new_texture(uint32_t width, uint32_t height)
{
	mlx_texture_t	*texture;

	texture = malloc(sizeof(mlx_texture_t));
	if (!texture)
		exit(1);
	texture->width = width;
	texture->height = height;
	texture->bytes_per_pixel = 4;
	texture->pixels = malloc(sizeof(uint8_t) * 4 * width * height);
	if (!texture->pixels)
		exit(1);
	ft_bzero(texture->pixels, sizeof(uint8_t) * 4 * width * height);
	return (texture);
}
