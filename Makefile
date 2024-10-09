# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 18:25:46 by anfichet          #+#    #+#              #
#    Updated: 2024/10/09 14:37:12 by anfichet         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

LIBFT = libft.a
MLX = libmlx_Linux.a

# *********************************VARIABLES**************************************** #

SRCS_DIR = ./srcs

SRCS =\
		main.c \
		


SRCS := $(SRCS:%=$(SRCS_DIR)/%)

SRCS_BONUS =\

SRCS_BONUS := $(SRCS_BONUS:%=$(SRCS_DIR)/%)

OBJS_DIR = ./objs

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INCS = ./incs

INCS_LIBFT = ./libft/INCS
INCS_MLX = ./mlx

DEPS = $(OBJS:.o=.d)
DEPS_BONUS = $(OBJS_BONUS:.o=.d)

LIBFT_TARGET = ./libft/libft.a
MLX_TARGET = ./mlx/libmlx_Linux.a
# **********************************COMMANDS**************************************** #

CC = cc

CFLAGS = -Werror -Wextra -Wall -g3 -MMD -MP -O3

CPPFLAGS = -I$(INCS) -I$(INCS_LIBFT) -I$(INCS_MLX)

MLX_FLAGS = -L$(dir $(MLX_TARGET)) -lmlx_Linux -L/usr/lib -lX11 -lXext -lm -lz

CFSIGSEV = -fsanitize=address

RM = rm -rf

DIR_DUP= mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

# **********************************RULES**************************************** #

all: $(NAME)

bonus:

-include $(DEPS)
-include $(DEPS_BONUS)

$(NAME): $(LIBFT_TARGET) $(MLX_TARGET) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -L$(dir $(LIBFT_TARGET)) -lft $(MLX_FLAGS) -o $(NAME)

$(LIBFT_TARGET): FORCE
	@echo " "
	@echo "\033[1m\033[35m#-------------------------[COMPILATION LIBFT]-------------------------#\033[0m"
	$(MAKE) -C $(@D)
	@echo "\033[1m\033[35m#---------------------------[LIBFT COMPILED]--------------------------#\033[0m"
	@echo " "

$(MLX_TARGET): FORCE
	@echo " "
	@echo "\033[1m\033[36m#-------------------------[COMPILATION MLX]-------------------------#\033[0m"
	$(MAKE) -C $(@D)
	@echo "\033[1m\033[36m#---------------------------[MLX COMPILED]--------------------------#\033[0m"
	@echo " "

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

fsanitize : fclean $(LIBS_TARGET) $(MLX_TARGET) $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(CFSIGSEV) $(CPPFLAGS) $(OBJS) -L$(dir $(LIBS_TARGET)) -lft -L$(dir $(MLX_TARGET)) -lmlx -L$(dir $(MLX_TARGET)) -lmlx_Linux -o $(NAME)

clean :
	$(RM) $(OBJS_DIR)
	$(MAKE) $@ -C ./libft
	$(MAKE) $@ -C ./mlx

fclean : clean
	$(RM) $(NAME)
	$(MAKE) $@ -C ./libft
	$(MAKE) $@ -C ./mlx

re : fclean all

print% :
	@echo $(patsubst print%,%,$@)=
	@echo $($(patsubst print%,%,$@))

.PHONY: all clean fclean re FORCE bonus fsanitize print%
FORCE:

# Colors
BLACK=\033[30m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
PURPLE=\033[35m
CYAN=\033[36m
WHITE=\033[37m

# Text
ERASE=\033[2K\r
RESET=\033[0m
BOLD=\033[1m
FAINT=\033[2m
ITALIC=\033[3m
UNDERLINE=\033[4m
