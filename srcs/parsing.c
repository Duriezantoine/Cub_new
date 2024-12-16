/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:44:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/11/18 09:08:17 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

 int check_extension(char *file, char *ext)
{
   int file_len;
   int ext_len;

   if (!file || !ext)
       return (0);
   file_len = ft_strlen(file);
   ext_len = ft_strlen(ext);
   if (file_len <= ext_len)
       return (0);
   return (!ft_strcmp(&file[file_len - ext_len], ext));
}
int check_textures(t_insert_data *data)
{
   // Vérifier si les chemins des textures sont bien définis
   if (!data->no || !data->so || !data->we || !data->ea)
       return (0);
   
   // Vérifier l'extension
   if (!check_extension(data->no, ".xpm") || !check_extension(data->so, ".xpm") 
       || !check_extension(data->we, ".xpm") || !check_extension(data->ea, ".xpm"))
       return (0);

   // Vérifier que les fichiers sont lisibles
   if (access(data->no, R_OK) == -1 || access(data->so, R_OK) == -1 
       || access(data->we, R_OK) == -1 || access(data->ea, R_OK) == -1)
       return (0);

   return (1);
}

// Fonction auxiliaire pour vérifier l'extension

int insert_len_data(char *filename, t_insert_data *data) //Il faut introduire dans la data les orientations
{
    char *line;
    int count = 0;
    int fd;
    int x;
    
    line = NULL;
    x = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
        
    while ((line = get_next_line(fd)) != NULL)
    {
        if(ft_search_orientation(line, data, &count, x)==-1)
        {
            close(fd);
            //printf("Icici");
            free(line);
            	get_next_line(-1);
            return(-1);
        }
        free(line);
        x++;
    }
    	get_next_line(-1);
    close(fd);
    return (count);
}

static int	while_color(char *str, int *idx)
{
   int	nbr;
   int	start;

   while (str[*idx] && (str[*idx] == ' ' || str[*idx] == '\t'))
   	(*idx)++;
   start = *idx;
   nbr = 0;
   while (str[*idx] && str[*idx] >= '0' && str[*idx] <= '9')
   {
   	nbr = (nbr * 10) + (str[*idx] - '0');
   	(*idx)++;
   }
   if (nbr > 255 || nbr < 0 || *idx == start)
   	return (-1);
   while (str[*idx] && (str[*idx] == ' ' || str[*idx] == '\t'))
   	(*idx)++;
   if (str[*idx] == ',')
   	(*idx)++;
   return (nbr);
}

static int	check_remaining_chars(char *str, int idx)
{
   while (str[idx] && (str[idx] == ' ' || str[idx] == '\t'))
   	idx++;
   if (str[idx] != '\0')
   	return (1);
   return (0);
}

int	check_color(t_insert_data *data)
{
   int	i_c;
   int	i_f;
   int	count;

   i_c = 0;
   i_f = 0;
   count = -1;
   if (!data->c || !data->f)
   	return (1);
   if (ft_isalpha(data->c[0]) || ft_isalpha(data->f[0]))
   	return (1);
   while (++count <= 2)
   {
   	data->ctab[count] = while_color(data->c, &i_c);
   	data->ftab[count] = while_color(data->f, &i_f);
   	if (data->ctab[count] == -1 || data->ftab[count] == -1)
   		return (1);
   }
   if (check_remaining_chars(data->c, i_c) || check_remaining_chars(data->f, i_f))
   	return (1);
   return (0);
}
void	set_player_direction(t_insert_data *data, t_cubdata **cubdata)
{
	if (!data || !cubdata || !(*cubdata)->player)
		return ;
	if (data->orientation == 'N')
		(*cubdata)->player->angle = 3 * M_PI / 2;
	else if (data->orientation == 'S')
		(*cubdata)->player->angle = M_PI / 2;
	else if (data->orientation == 'E')
		(*cubdata)->player->angle = 0;
	else if (data->orientation == 'W')
		(*cubdata)->player->angle = M_PI;
}
void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


unsigned int	str_rgb_to_hex(const char *rgb_str)
{
	char		**split;
	int		r;
	int		g;
	int		b;
	unsigned int	color;

	split = ft_split(rgb_str, ',');
	if (!split)
		return (0);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	ft_free_tab(split);
	return (color);
}

void	ft_free(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
    if(ptr != NULL)
	    free(*ptr);
	*ptr = NULL;
}

void	free_insert_data(t_insert_data *data)
{

	if (!data)
		return ;
	ft_free((void *)&data->no);
	ft_free((void *)&data->ea);
	ft_free((void *)&data->so);
	ft_free((void *)&data->we);
	ft_free((void *)&data->c);
	ft_free((void *)&data->f);
	if (data->map)
		ft_free((void *)&data->map);
	ft_free((void *)&data);
}

void    insert_data(t_cubdata **cubdata, t_insert_data *data)
{
    int i;
    i = 0;
    (*cubdata)->map->map_str = malloc(sizeof(char) * (data->max_struct + 2));//Je ne peux pas mettre +1 je ne comprends pas 
    (*cubdata)->map->map_str[data->max_struct+1] = '\0';
    while(i<data->max_line * data->nbr_line)
    {
        (*cubdata)->map->map_str[i] = data->map[i].str;
        //printf("Ici|%c|",   (*cubdata)->map->map_str[i]);
        //1 er chose verifier ce que l'on insere
        i++;
    }
    //Mise en place de la place du joueurs 
    printf("\nPosition du joueurs |x|%f|y|%f|\n",(float)data->player_place.x+0.5f , (float)data->player_place.y+0.5f );
    (*cubdata)->player->x = (float)data->player_place.y+0.5f;
	(*cubdata)->player->y = (float)data->player_place.x+0.5f;
    printf("\nPosition du joueurs |x|%f|y|%f|\n",(*cubdata)->player->x , (*cubdata)->player->y );
    //Mise en place de la largeur et de la longueur de la map 
    (*cubdata)->map->width = data->max_line;
    (*cubdata)->map->height = data->nbr_line;
    printf("DATAMAX_LINE|%d|Nbr_line|%d|",data->nbr_line, data->max_line );
    //MIse en place de la l'orientation du joueurs 
    printf("\nData=|%c|Cub|%f|\n", data->orientation, (*cubdata)->player->angle);
    set_player_direction(data, cubdata);
    //Mise en place des textures
    printf("\nDataNO|%s|SO|%s|WE|%s|EA|%s|\n", data->no, data->so, data->we, data->ea);
    load_asset(&(*cubdata)->asset_list, data->no, NORTH_TX);
	load_asset(&(*cubdata)->asset_list, data->so, SOUTH_TX);
	load_asset(&(*cubdata)->asset_list, data->we, WEST_TX);
	load_asset(&(*cubdata)->asset_list, data->ea, EAST_TX);
	load_asset(&(*cubdata)->asset_list, "assets/Brick_Texture.png", DOOR_TX);
    //Mise en place des couleurs
    //printf("Color hex: 0x%X\n", str_rgb_to_hex(data->c));
    (*cubdata)->floor_color = str_rgb_to_hex(data->c);
    (*cubdata)->ceiling_color = str_rgb_to_hex(data->f);
}


static int	init_data(t_insert_data **data)
{
	*data = malloc(sizeof(t_insert_data));
	if (!*data)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
    (*data)->check = 0;
	(*data)->max_line = 0;
	(*data)->start_map = 999999999;
	(*data)->no = NULL;
	(*data)->ea = NULL;
	(*data)->so = NULL;
	(*data)->we = NULL;
	(*data)->c = NULL;
	(*data)->f = NULL;
	(*data)->map = NULL;
	return (0);
}

static int	handle_errors(int error_code, t_insert_data *data)
{
    free_insert_data(data);
    if (error_code == 1)
   	    ft_putstr_fd("1Error\nNot correct arguments\n", 2);
    else if (error_code == 2)
   	    ft_putstr_fd("2Error\nFile not valid\n", 2);
    else if (error_code == 3)
   	    ft_putstr_fd("3Error\nCalculate size file failed\n", 2);
    else if (error_code == 4)
   	    ft_putstr_fd("4Error\nMap not valid\n", 2);
    else if (error_code == 5)
   	    ft_putstr_fd("5Error\nColors not valid\n", 2);
    else if(error_code == 6)
        ft_putstr_fd("6Error\nTexture not valid\n", 2);
    else if(error_code == 7)
        ft_putstr_fd("7Error\nNot good organisation\n", 2);
    else if(error_code == 7)
        ft_putstr_fd("8Error\nTextures Not good\n", 2);
   return (1);
}



int	start_parsing(int ac, char **av, t_cubdata **cubdata)
{
   t_insert_data	*data;

    if (!av || !cubdata || !*cubdata)
   	    return (1);
    if (init_data(&data))
   	    return (1);
    if (ac != 2)
   	    return (handle_errors(1, data));
    if (check_file_valid(0, av) == 1)
   	    return (handle_errors(2, data));
    if ((data->nbr_line = insert_len_data(av[1], data)) == -1)
   	    return (handle_errors(3, data));
    if (start_insert_map(data, av[1]) == 1)
   	    return (handle_errors(4, data));
    if (check_color(data) == 1)
   	    return (handle_errors(5, data));
    if (data->check!= 6)
   	    return (handle_errors(7, data));
    // if(check_textures(data) !=1)
    //     return(handle_errors(8, data));
    insert_data(cubdata, data);
   free_insert_data(data);
   return (0);
}
