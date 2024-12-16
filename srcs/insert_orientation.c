/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_orientation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:20:13 by aduriez           #+#    #+#             */
/*   Updated: 2024/11/18 10:21:30 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int ft_search_orientation(char *line, t_insert_data *data, int *count, int x)
{
    int i;

    i = 0;
    //printf("\n FT_Search_orientation\n");
    i = dell_space(line, &i);
    if (ft_strncmp(&line[i], "C", 1) == 0)
        ft_insert_c(line, data);
    else if (ft_strncmp(&line[i], "F", 1) == 0)
        ft_insert_f(line, data);
    else if (ft_strncmp(&line[i], "NO", 2) == 0)
        ft_insert_no(line, data);
    else if (ft_strncmp(&line[i], "EA", 2) == 0)
        ft_insert_ea(line, data);
    else if (ft_strncmp(&line[i], "SO", 2) == 0)
        ft_insert_so(&line[i], data);
    else if (ft_strncmp(&line[i], "WE", 2) == 0)
        ft_insert_we(line, data);
    else if(ft_strncmp(&line[i], "\n", 1) == 0)
        return(0);
    else if (ft_strncmp(&line[i], "1", 1) == 0)
    {
        if(data->check != 6)
        {
            //printf("\ndatacheckll|%d|\n", data->check);
            return(-1);
        }
        if(data->start_map > x)
            data->start_map = x;
        if(data->max_line <(int) ft_strlen_no_new_line(line))
            data->max_line = ft_strlen_no_new_line(line);
        (*count)++;
        return(0);
    }
    else
        return(-1);
    return(0);
}

void ft_insert_f(char *line, t_insert_data *data)
{
    char *end;
    int i;
    
    i = 0;
    if (!line || !data)
        return;
    if (!(end = ft_copy_end(line, 'F')))
        return;
    if ((i = dell_space(end, &i)) == -1)
    {
        free(end);
        return;
    }
    if (!end[i])
    {
        free(end);
        return;
    }
    data->f = ft_strdup_new_line(&end[i]);
    if (!data->f)
    {
        free(end);
        return;
    }
    free(end);
    data->check++;

    //printf("Je suis f|%s|\n", data->f);
}

void ft_insert_c(char *line, t_insert_data *data)
{
    char *end;
    int i;
    
    i = 0;
    if (!line || !data)
        return;
    if (!(end = ft_copy_end(line, 'C')))
        return;
    if ((i = dell_space(end, &i)) == -1)
    {
        free(end);
        return;
    }
    if (!end[i])
    {
        free(end);
        return;
    }
    data->c = ft_strdup_new_line(&end[i]);
    if (!data->c)
    {
        free(end);
        return;
    }
    free(end);
        data->check++;

    //printf("Je suis c|%s|\n", data->c);
}

void ft_insert_no(char *line, t_insert_data *data)
{
    char *end;
    int i;
    
    i = 0;
    if (!line || !data)
        return;
    if (!(end = ft_copy_end(line, 'O')))
        return;
    if ((i = dell_space(end, &i)) == -1)
    {
        free(end);
        return;
    }
    if (!end[i])
    {
        free(end);
        return;
    }
    data->no = ft_strdup_new_line(&end[i]);
    if (!data->no)
    {
        free(end);
        return;
    }
    free(end);
        data->check++;

    //printf("Je suis no|%s|\n", data->no);
}

void ft_insert_ea(char *line, t_insert_data *data)
{
    char *end;
    int i;
    
    i = 0;
    if (!line || !data)
        return;
    if (!(end = ft_copy_end(line, 'A')))
        return;
    if ((i = dell_space(end, &i)) == -1)
    {
        free(end);
        return;
    }
    if (!end[i])
    {
        free(end);
        return;
    }
    data->ea = ft_strdup_new_line(&end[i]);
    if (!data->ea)
    {
        free(end);
        return;
    }
    free(end);
        data->check++;

    //printf("Je suis ea|%s|\n", data->ea);
}

void ft_insert_so(char *line, t_insert_data *data)
{
    char *end;
    int i;
    
    i = 0;
    if (!line || !data)
        return;
    if (!(end = ft_copy_end(line, 'O')))
        return;
    if ((i = dell_space(end, &i)) == -1)
    {
        free(end);
        return;
    }
    if (!end[i])
    {
        free(end);
        return;
    }
    data->so = ft_strdup_new_line(&end[i]);
    if (!data->so)
    {
        free(end);
        return;
    }
    free(end);
    data->check++;

    //printf("Je suis so|%s|\n", data->so);
}

void ft_insert_we(char *line, t_insert_data *data)
{
    char *end;
    int i;
    
    i = 0;
    if (!line || !data)
        return;
    if (!(end = ft_copy_end(line, 'E')))
        return;
    if ((i = dell_space(end, &i)) == -1)
    {
        free(end);
        return;
    }
    if (!end[i])
    {
        free(end);
        return;
    }
    data->we = ft_strdup_new_line(&end[i]);
    if (!data->we)
    {
        free(end);
        return;
    }
    free(end);
        data->check++;

    //printf("Je suis we|%s|\n", data->we);
}
