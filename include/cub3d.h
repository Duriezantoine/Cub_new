#ifndef CUB3D_H
# define CUB3D_H

// ********** INCLUDES **********
# include <MLX42.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <unistd.h>

// ********** MATH CONSTANTS **********
# define M_3PI_2 4.712388980384690f
# define M_2PI_3 2.09439510239319526264f
# define M_PI_3 1.047197551f
# define M_PI 3.14159265358979323846

// ********** WINDOW AND CAMERA SETTINGS **********
# define CAMERA_W 900
# define CAMERA_H 900
# define PROJPLANE_DIST 1.0f
# define WINDOW_W 900
# define WINDOW_H 900

// ********** MINIMAP SETTINGS **********
# define MMAP_WIDTH 260
# define MMAP_HEIGHT 260
# define MMAP_X 0
# define MMAP_Y (CAMERA_H - MMAP_HEIGHT)
# define MMAP_SQUARE_SIZE 30
# define MMAP_PIXEL_STEP (float)(1 / (float)MMAP_SQUARE_SIZE)
# define FOV M_PI_3

// ********** COLORS **********
# define MMAP_COLOR_1 (uint32_t)0x2E3B56FF
# define MMAP_COLOR_0 (uint32_t)0xFFFFFFFF
# define BLACK (uint32_t)0x000000FF
# define WHITE (uint32_t)0xFFFFFFFF
# define GREEN 0x3DA600FF
# define FLOOR_DEBUG 0x845207FF
# define CEILING_DEBUG 0x2D2D2DFF

// ********** PLAYER MOVEMENT **********
# define ANGLE_INCREMENT 0.05f
# define POS_INCREMENT 0.035f
# define MOUSE_ANGLE_RATIO 0.0016f
# define MIN_DIST_FROM_WALL 0.1f

// ********** TEXTURE DEFINITIONS **********
# define NORTH_TX "NO"
# define SOUTH_TX "SO" 
# define WEST_TX "WE"
# define EAST_TX "EA"
# define DOOR_TX "DO"
# define MMAP_PLAYER_ICON "MMAP_PLAYER_ICON"
# define MMAP_PLAYER_PATH "assets/circle1.png"
# define MMAP_MASK_PATH "assets/mmap_mask.png"
# define MMAP_MASK_NAME "mmap_mask"

// ********** WALL TYPES **********
# define WALL_N 0
# define WALL_S 1
# define WALL_E 2
# define WALL_W 3

// ********** DOOR SETTINGS **********
# define DOOR_OPEN_FRAMES 120
# define DOOR_CHAR_X 'D'
# define DOOR_CHAR_Y 'd'

// ********** DEBUG MAP **********
/*
String equivalent to a simple valid map:
11111111111111
10010101000001
10010100000001
11010100000001
10010101101001
1000000000d001
11100N00001001
11111111111111
*/
# define MAP_DEBUG "1111111111111110010101000001100101000000011101D100000001100101011010011000000000d0011110000000100111111111111111"

// ********** ERROR CODES **********
typedef enum error_code
{
   MLX_ERR = 1,
   MALLOC_ERR,
   ASSET_NAME_ERR,
   ASSET_NOT_FOUND,
   ASSET_DELETE_ERR,
   MMAP_MASK,
   DOOR_RM,
   DOOR_WALK,
   ERR_MAX_VALUE
} t_error_code;

// ********** BASIC STRUCTURES **********
typedef struct s_point
{
   float x;
   float y;
} t_point;

typedef struct s_player
{
   float x;
   float y;
   float angle;
} t_player;

typedef struct s_map
{
   char        *map_str;
   uint32_t    width;
   uint32_t    height;
} t_map;

typedef struct s_asset
{
   char            *name;
   mlx_texture_t   *tx;
   struct s_asset  *next;
} t_asset;

typedef struct s_ray
{
   float           angle;
   float           slope;
   float           ninv_slope;
   float           step_x;
   float           step_y;
   float           v_inter_x;
   float           v_inter_y;
   float           v_dist;
   float           h_inter_x;
   float           h_inter_y;
   float           h_dist;
   float           offset;
   mlx_texture_t   *wall_tx;
   bool            ray_hit;
} t_ray;

typedef struct s_door
{
   int             x;
   int             y;
   int             state;
   char            type;
   struct s_door   *next;
} t_door;

// ********** PARSING STRUCTURES **********
typedef struct s_mini_map_data
{
   float   x;
   float   y;
   char    str;
   float   angle;
} t_mini_map_data;

typedef struct s_insert_data
{
   char            *no;
   char            *ea;
   char            *so;
   char            *we;
   int             nbr_line;
   int             max_line;
   int             max_struct;
   char            *c;
   char            *f;
   int            check;
   int             ctab[3];
   int             ftab[3];
   int             start_map;
   char             orientation;
   t_mini_map_data *map;
   t_player        player_place;
} t_insert_data;

// ********** MAIN STRUCTURE **********
typedef struct s_cubdata
{
   mlx_t           *mlx;
   mlx_image_t     *main_img;
   mlx_texture_t   *camera;
   mlx_texture_t   *mmap;
   t_asset         *asset_list;
   t_door          *active_doors;
   t_player        *player;
   t_map           *map;
   t_ray           rays[CAMERA_W];
   uint32_t        floor_color;
   uint32_t        ceiling_color;
   float           projplane_w;
   uint8_t         mmap_sqr_size;
} t_cubdata;

// ********** FUNCTION PROTOTYPES **********

// Debug Functions
t_cubdata   *debug_data_init(int ac, char **av);
void        draw_line(int x0, int y0, int x1, int y1, mlx_texture_t *tx, int color);

// Base Functions
void        cubdata_mlx_init(t_cubdata *cubdata);
void        delete_cubdata(t_cubdata *cubdata);
void        error_exit(t_error_code code);

// Hook Functions
void        key_hook(mlx_key_data_t keydata, void *cubdata);
void        generic_hook(void *cubdata);
void        input_check(t_cubdata *cubdata);

// Render Functions
void        render(t_cubdata *cubdata);
void        update_rays(t_cubdata *cub);

// Ray Functions
void        save_v_inter(t_ray *ray, t_point *point, t_player *p);
void        save_h_inter(t_ray *ray, t_point *point, t_player *p);
bool        ray_first_step_v(t_point *point, t_player *p, t_ray *ray);
bool        ray_first_step_h(t_point *point, t_player *p, t_ray *ray);
void        v_collision(t_cubdata *cub, int idx);
void        h_collision(t_cubdata *cub, int idx);

// Door Functions
void        update_door_list(t_cubdata *cub);
t_door      *search_door(t_door *list, int x, int y);
bool        is_door_nearby(t_door *door, t_player *player);
void        add_door_to_list(t_door **list, int x, int y, char type);
void        remove_door(t_door **list, t_door *door);
void        remove_all_doors(t_door **list);

// Texture Functions
mlx_texture_t   *new_texture(uint32_t width, uint32_t height);
void            pixel_to_texture(mlx_texture_t *tx, uint32_t x, uint32_t y, uint32_t color);
uint32_t        get_color(const mlx_texture_t *tx, int x, int y);
void            merge_textures(mlx_texture_t *dest, mlx_texture_t *src, int x, int y);
void            texture_to_image(mlx_texture_t *tx, mlx_image_t *img);

// Minimap Functions
void            update_minimap_texture(t_cubdata *cub);
void            apply_minimap_mask(mlx_texture_t *mmap, t_asset *assets);

// Asset Functions
void            load_asset(t_asset **assets, const char *path, const char *name);
void            delete_asset(t_asset **lst, char *name);
bool            asset_exists(t_asset *assets, const char *name);
mlx_texture_t   *get_asset(t_asset *assets, char *name);

// Utility Functions
char            map_element_at_pos(t_map *map, float x, float y);
int             ft_strcmp(const char *s1, const char *s2);
bool            is_pos_walkable(t_cubdata *cub, float x, float y);
float           absolutef(float value);
float           remapf(float n, float in_min, float in_max, float out_min, float out_max);
float           remap(int64_t n, int64_t in_min, int64_t in_max, int64_t out_min, int64_t out_max);
float           map_angle(int idx, float projplane_width, float face_angle);

// Parsing Functions
void            err(char *str);
int             check_file_valid(int fd, char **av);
int             start_parsing(int ac, char **av, t_cubdata **cubdata);
int             ft_search_orientation(char *line, t_insert_data *data, int *count, int x);
void            ft_insert_no(char *line, t_insert_data *data);
void            ft_insert_ea(char *line, t_insert_data *data);
void            ft_insert_so(char *line, t_insert_data *data);
void            ft_insert_we(char *line, t_insert_data *data);
void            ft_insert_c(char *line, t_insert_data *data);
void            ft_insert_f(char *line, t_insert_data *data);
int             dell_space(char *line, int *i);
char            *ft_strdup_new_line(const char *source);
char            *ft_copy_end(char *str, char c);
size_t          ft_strlen_no_new_line(const char *c);
int             insert_map(char *filename, t_insert_data *data, int *i);
int             start_insert_map(t_insert_data *data, char *arg);
int             check_wall(t_insert_data *data);
void            search_player(t_insert_data *data);
void            print_mini_map_data(t_insert_data *data);
void            free_insert_data(t_insert_data *data);


#endif