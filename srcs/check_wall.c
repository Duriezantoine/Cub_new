/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:02:44 by aduriez           #+#    #+#             */
/*   Updated: 2024/11/18 12:19:58 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


static int is_accessible(t_insert_data *data, int index)
{
    // Si on est sur le bord de la map
    if (index < data->max_line || index >= data->max_struct - data->max_line ||
        index % data->max_line == 0 || (index + 1) % data->max_line == 0)
        return (1);  // Case sur le bord = exposée

    // Vérifie les 4 directions autour de la case
    char up = data->map[index - data->max_line].str;
    char down = data->map[index + data->max_line].str;
    char left = data->map[index - 1].str;
    char right = data->map[index + 1].str;

    // Si une des cases adjacentes n'est pas un mur ('1')
    // et n'est pas un espace valide ('0', 'N', 'S', 'E', 'W')
    if (up != '1' && up != '0' && up != 'N' && up != 'S' && up != 'E' && up != 'W' && up!= 'd' && up!='D')
        return (1);
    if (down != '1' && down != '0' && down != 'N' && down != 'S' && down != 'E' && down != 'W' && down!= 'd' && down!='D')
        return (1);
    if (left != '1' && left != '0' && left != 'N' && left != 'S' && left != 'E' && left != 'W' && left!= 'd' && left!='D')
        return (1);
    if (right != '1' && right != '0' && right != 'N' && right != 'S' && right != 'E' && right != 'W' && right!= 'd' && right!='D')
        return (1);

    return (0);  // La case est entourée correctement
}

int is_valid_index(t_insert_data *data, int index)
{
    // Vérification des limites globales
    if (index < 0 || index >= data->max_struct)
        return (0);

    // Pour mouvement gauche
    if ((index % data->max_line) == 0 && data->map[index].str == '1')
        return (0);
    
    // Pour mouvement droite
    if ((index + 1) % data->max_line == 0 && data->map[index].str == '1')
        return (0);

    return (1);
}
void print_visited_map(t_insert_data *data, int *visited)
{
    printf("\nCarte avec positions visitées:\n");
    for (int i = 0; i < data->max_struct; i++)
    {
        printf("%c", visited[i] ? 'V' : data->map[i].str);
        if ((i + 1) % data->max_line == 0)
            printf("\n");
    }
    printf("\n");
}

void flood_fill(t_insert_data *data, int index, int *visited)
{
    // Vérifications de base
    if (!is_valid_index(data, index) || visited[index])
        return;
    if (data->map[index].str == '1')
        return;

    // Marquer comme visité
    visited[index] = 1;

    // Récursion dans les 4 directions
    flood_fill(data, index - data->max_line, visited);  // haut
    flood_fill(data, index + data->max_line, visited);  // bas
    flood_fill(data, index - 1, visited);              // gauche
    flood_fill(data, index + 1, visited);              // droite

        print_visited_map(data, visited);  // Ajoutez cette ligne

}


void search_player(t_insert_data *data)
{
    //Creer une verfification si il ya 2 joueurs dans la maps 
    //Mise en place d'un max si depasser augmenter y de 1;
    //printf("MaxLINEX= %d",data->max_line );
    int i;
    int count;
    int count_y;
    count_y  = 0;
    i = 0;
    count = 0;
    while (i < data->max_struct)
    {
    
        if (data->map[i].str == 'N' || data->map[i].str == 'S' || 
            data->map[i].str == 'E' || data->map[i].str == 'W')
        {
            data->orientation = data->map[i].str;
            data->player_place.y =i%data->max_line;
            data->player_place.x = i / data->max_line;
            count++;
        }
        i++;
    }
    if (count != 1)
    {
        ft_putstr_fd("Error\nInvalid number of players\n", 2);
        exit(1);
    }
        //printf("\nPlacey|%f|\n", data->player_place.y);
}

int check_wall(t_insert_data *data)
{
    int *visited;
    int i;
    int start_index;

    if (!data || !data->map)
    {
        ft_putstr_fd("Error\nInvalid map structure\n", 2);
        return (0);
    }
    data->max_struct = data->max_line * data->nbr_line;
    //printf("MaxStrcut|%d|", data->max_struct);
    visited = ft_calloc(data->max_struct, sizeof(int));
    if (!visited)
    {
        ft_putstr_fd("Error\nMemory allocation failed\n", 2);
        return (0);
    }
    search_player(data);
    start_index = (int)(data->player_place.x * data->max_line + data->player_place.y);    
    flood_fill(data, start_index, visited);

    printf("\n|Je suis visited|%d\n", visited[0]);
    if (visited[0] == 1)
    {
        ft_putstr_fd("Error\nMap is not properly closed (space found)\n", 2);
        free(visited);
        return (0);
    }

    // On vérifie uniquement les cases qui ont été visitées par le flood_fill
    i = 0;
    while (i < data->max_struct)
    {
        if (visited[i] == 1)  // Si la case a été visitée par le flood_fill
        {
            if (is_accessible(data, i))
            {
                ft_putstr_fd("Error\nMap is not properly closed (hole found)\n", 2);
                free(visited);
                return (0);
            }
        }
        i++;
    }

    free(visited);
    return (1);
}
