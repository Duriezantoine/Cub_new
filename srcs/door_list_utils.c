/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:11 by abernade          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:40 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_door	*search_door(t_door *list, int x, int y)
{
	while (list)
	{
		if (list->x == x && list->y == y)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	add_door_to_list(t_door **list, int x, int y, char type)
{
	t_door *new;

	if (search_door(*list, x, y))
		return ;
	new = malloc(sizeof(t_door));
	if (!new)
		error_exit(MALLOC_ERR);
	new->next = NULL;
	new->x = x;
	new->y = y;
	new->type = type;
	new->state = 0;
	if (*list == NULL)
		*list = new;
	else
	{
		new->next = *list;
		*list = new;
	}
}

void	remove_door(t_door **list, t_door *door)
{
	t_door	*node;
	t_door	*prev;

	node = *list;
	prev = NULL;
	while (node && node != door)
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		error_exit(DOOR_RM);
	if (!prev)
		*list = node->next;
	else
		prev->next = node->next;
	free(node);
}

void	remove_all_doors(t_door **list)
{
	t_door	*node;
	t_door	*next;

	node = *list;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	*list = NULL;
}

bool	is_door_nearby(t_door *door, t_player *player)
{
	return (door->x >= (int)player->x - 1 \
		&& door->x <= (int)player->x + 1 \
		&& door->y >= (int)player->y - 1 \
		&& door->y <= (int)player->y + 1);
}
