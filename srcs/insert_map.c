/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:03:27 by aduriez           #+#    #+#             */
/*   Updated: 2024/11/18 12:21:17 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//I est l'iterateur permettant d'avanver jusqu'a la fin
//X c'est ce qui permet de pouvoir voir la ligne
//Y est ce qui permet l'axe des y

int insert_data_map(char *line, t_insert_data *data, int x, int *i)
{
    int count;

    count = 0;
    while (count < data->max_line)
    {
        // printf("\nIcije suis count_line|%c|\n", line[count]);
        data->map[*i].x = x;
        data->map[*i].y = count;
        // printf("Caractère trouvé: '%c' (ASCII: %d) à la position %d\n", line[count], line[count], count);
        // Gestion des caractères valides
        if ( line[count] == '\n' || line[count] == '\0')
        {
                // printf("\nJe suis  a la fin de la premier ligne je dois breack\n");
                break;
        }
        else if (line[count] == '1' || line[count] == '0' || line[count] == 'S' ||
            line[count] == 'D' || line[count] == 'd')
            data->map[*i].str = line[count];
        // Gestion des espaces et caractères spéciaux
        else if (line[count] == ' ' || line[count] == '\t' || 
                line[count] == '\n' || line[count] == '\0')
            data->map[*i].str = '1';
        else
        {
            // printf("Caractère invalide: |%c| position: |%d|\n", line[count], count);
            return (1);
        }
        (*i)++;
        count++;
    }
    if(line[count] == '\n' || line[count] == '\0')//Cela permet de rajouter des 1 si la line est trop courte comparer aux autres
    {
        //MIse en place d'un modulo permettant de determier si on est la fin de la line
        while(count < data->max_line)
        {
                data->map[*i].str = '1';
                data->map[*i].x = x;
                data->map[*i].y = count;
                (*i)++;
                count++;
        }
        // printf("Je suis coount|%d|je suis i|%d|", count, *i);
    }
    return (0);
}

int insert_map(char *filename, t_insert_data *data, int *i) //Il faut introduire dans la data les orientations
{
    char *line = NULL;
    int x = 0;
    int fd;
    int count;
    
    count = 0;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        if (count >= data->start_map)
        {
            if(insert_data_map(line, data,x, i)==1)
            {
                get_next_line(-1);
                printf("\n|Je suis max_line|%d|nbr_line|%d|\n", data->max_line, data->nbr_line);
                close(fd);
                free(line);
                return(1);
            }
            x++;
        }
        count++;
        free(line);
    }
    get_next_line(-1);

    // free(line);
    close(fd);
    return (0);
}

int start_insert_map( t_insert_data *data, char *arg)
{
    (void)arg;
    int i ;

    i = 0;
    (*data).map = malloc(sizeof(t_mini_map_data) * ((*data).nbr_line * (*data).max_line));
    if (!(*data).map)
    {
        printf("Il y a un probleme dans la maps");
         return (1);
    }
    if(insert_map(arg , data, &i)== 1)
    {
        printf("\n|NBR X|%d|NBR Y|%d|\n", data->nbr_line, data->max_line);
        return(1);
    }
    if(check_wall(data) == 0)
    {
        return(1);
    }


    //La data est bonne a partir d'ici
            // //printf("Je suis le dernier I=|%d|\n", i);//IL y en a 3 ca part de zero
            data->max_struct = i;
            print_mini_map_data(data);//Ce qui permet de verififer la map 
    //Ce qui permet de verifier la data
    return(0);
}