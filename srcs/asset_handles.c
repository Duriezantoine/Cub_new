/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_handles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:48:07 by abernade          #+#    #+#             */
/*   Updated: 2024/11/20 16:34:59 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	add_asset_to_list(t_asset **lst, t_asset *asset)
{
	t_asset	*node;

	if (!*lst)
	{
		*lst = asset;
		return ;
	}
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = asset;
	asset->next = NULL;
}

void	load_asset(t_asset **assets, const char *path, const char *name)
{
	mlx_texture_t	*tx;
	t_asset			*asset;

	if (asset_exists(*assets, name))
		error_exit(ASSET_NAME_ERR);
	tx = mlx_load_png(path);
	if (!tx)
		error_exit(MLX_ERR);
	asset = malloc(sizeof(t_asset));
	if (!asset)
		error_exit(MALLOC_ERR);
	asset->tx = tx;
	asset->name = ft_strdup(name);
	asset->next = NULL;
	add_asset_to_list(assets, asset);
}

bool	asset_exists(t_asset *assets, const char *name)
{
	t_asset	*node;

	node = assets;
	while (node)
	{
		if (!ft_strcmp(name, node->name))
			return (true);
		node = node->next;
	}
	return (false);
}

void	delete_asset(t_asset **lst, char *name)
{
	t_asset	*node;
	t_asset	*prev;

	if (!*lst)
		error_exit(ASSET_DELETE_ERR);
	prev = NULL;
	node = *lst;
	while (node)
	{
		if (!ft_strcmp(node->name, name))
		{
			if (prev == NULL)
				*lst = node->next;
			else
				prev->next = node->next;
			mlx_delete_texture(node->tx);
			free(node->name);
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}

mlx_texture_t	*get_asset(t_asset *assets, char *name)
{
	while (assets && ft_strcmp(assets->name, name))
		assets = assets->next;
	if (!assets)
		error_exit(ASSET_NOT_FOUND);
	return (assets->tx);
}
