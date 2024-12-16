# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weldo <weldo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:14:48 by abernade          #+#    #+#              #
#    Updated: 2024/11/20 01:27:11 by weldo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d

SRC_DIR := srcs

OBJ_DIR := obj

LIBFT_DIR := libft

LIBFT := $(LIBFT_DIR)/libft.a

INCLUDE_DIR := include

SRC_FILES := main.c \
			asset_handles.c \
			cubdata.c \
			debug.c \
			errors.c \
			hooks.c \
			door.c \
			inputs.c \
			minimap.c \
			math_utils.c \
			ray_utils.c \
			ray_collision.c \
			rays.c \
			render.c \
			texture_utils.c \
			utils.c \
			parsing.c \
			check_pars.c \
			check_wall.c \
			insert_map.c \
			insert_orientation.c \
			utils_pars.c \
			door_list_utils.c \
			a_enlever.c

SRC := $(SRC_FILES:%.c=$(SRC_DIR)/%.c)

#OBJ = $(addsuffix .o,$(basename $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES)))))
OBJ := $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -g

LIBS := -ldl -lglfw -pthread -lm

MLX_DIR := MLX42

MLX := $(MLX_DIR)/build/libmlx42.a

MLX_INCLUDE := $(MLX_DIR)/include/MLX42

INCLUDE := -I/usr/include/X11 \
			-I$(MLX_INCLUDE) \
			-I$(INCLUDE_DIR) \
			-I$(LIBFT_DIR)/include

VPATH = :srcs

define compile-obj
$(CC) $(CFLAGS) $(INCLUDE) -O3 -c $< -o $@
endef

all: $(NAME)

$(MLX):
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(compile-obj)

$(NAME): $(MLX) $(OBJ)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) $(MLX) $(LIBFT) -lm -lz $(INCLUDE) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	rm -rf $(MLX_DIR)/build

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re