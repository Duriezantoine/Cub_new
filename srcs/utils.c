/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernade <abernade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:01:42 by abernade          #+#    #+#             */
/*   Updated: 2024/12/05 17:04:49 by abernade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// Récupère le caractère de la map à une position donnée
char map_element_at_pos(t_map *map, float x, float y)
{
   int intx = (int)x;
   int inty = (int)y;
   char element;

   if (intx < 0 || inty < 0 || 
       (uint32_t)intx >= map->width || 
       (uint32_t)inty >= map->height)
       return ('1');

   element = map->map_str[inty * map->width + intx];
//    printf("Position: (%.2f, %.2f) -> Caractère: '%c'\n", x, y, element);
   
   // Si c'est le S (position de départ), traiter comme un 0
   if (element == 'S')
       return '0';
       
   return (element);
}

// Vérifie si une position avec une porte est accessible
static bool is_door_pos_walkable(t_cubdata *cub, char door_type, float x, float y)
{
   t_door *door;
   float fract;
   float discard;

   door = search_door(cub->active_doors, x, y);
   if (!door)
       error_exit(DOOR_WALK);

   fract = (door_type == DOOR_CHAR_X) ? modff(y, &discard) : modff(x, &discard);
   return (door->state == DOOR_OPEN_FRAMES 
       || fract > 0.5f + MIN_DIST_FROM_WALL 
       || fract < 0.5f - MIN_DIST_FROM_WALL);
}

// Vérifie si une position est valide sur la map
static bool is_pos_valid(t_cubdata *cub, float x, float y)
{
   char map_char;

   map_char = map_element_at_pos(cub->map, x, y);
   if (!map_char || map_char == '1')
       return (false);
   if (map_char == '0')
       return (true);
   if (map_char == DOOR_CHAR_X || map_char == DOOR_CHAR_Y)
       return (is_door_pos_walkable(cub, map_char, x, y));
   return (false);
}

// Vérifie si une position est accessible pour le joueur
bool is_pos_walkable(t_cubdata *cub, float x, float y)
{
    float discard;
   float step_x = 0.0f;
   float step_y = 0.0f;

//    printf("Position sur la map : x=%.2f, y=%.2f, caractère=%c\n", 
//        x, y, map_element_at_pos(cub->map, x, y));

   if (!is_pos_valid(cub, x, y))
       return (false);
   step_x = 0.0f;
   if (modff(x, &discard) < MIN_DIST_FROM_WALL)
       step_x = -MIN_DIST_FROM_WALL;
   else if (modff(x, &discard) > 1.0f - MIN_DIST_FROM_WALL)
       step_x = MIN_DIST_FROM_WALL;

   step_y = 0.0f;
   if (modff(y, &discard) < MIN_DIST_FROM_WALL)
       step_y = -MIN_DIST_FROM_WALL;
   else if (modff(y, &discard) > 1.0f - MIN_DIST_FROM_WALL)
       step_y = MIN_DIST_FROM_WALL;

   return (is_pos_valid(cub, x + step_x, y) 
       && is_pos_valid(cub, x, y + step_y) 
       && is_pos_valid(cub, x + step_x, y + step_y));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
