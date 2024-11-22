NAME = miniRT

LIBFT = libft.a
MLX = libmlx_Linux.a

# *********************************VARIABLES**************************************** #

SRCS_DIR = ./srcs

SRCS=\
		main.c \
		init.c \
		$(addprefix camera/, $(SRCS_CAMERA)) \
		$(addprefix display_mlx/, $(SRCS_DISPLAYMLX)) \
		$(addprefix objects/, $(SRCS_OBJECTS)) \
		$(addprefix parsing/, $(SRCS_PARSING)) \
		$(addprefix render/, $(SRCS_RENDER)) \
		$(addprefix vector/, $(SRCS_VECTOR)) \
		

SRCS_CAMERA=\
		camera.c \

SRCS_DISPLAYMLX=\
		init_mlx.c \
		destroy_mlx.c \
		event_mlx.c \
		my_pxl_put.c \

SRCS_CAMERA=\
		camera.c \

SRCS_OBJECTS=\
		sphere.c \
		plane.c \
		cylinder.c \
		common_objects.c \

SRCS_PARSING=\
		check_input.c \
		parsing.c \
		array_utils.c \
		parsing_lights.c \
		parsing_cam.c \
		parsing_utils.c \
		parsing_objects.c \
		float_utils.c

SRCS_RENDER=\
		render.c \
		light.c \
		ray.c \

SRCS_VECTOR=\
		arithmetic_vector.c \
		multiply.c \
		divide.c \
		dot_product.c \
		cross_product.c \
		normalize.c \
		color.c \


SRCS := $(SRCS:%=$(SRCS_DIR)/%) \

SRCS_BONUS =\

SRCS_BONUS := $(SRCS_BONUS:%=$(SRCS_DIR)/%)

OBJS_DIR = ./.objs

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

CFLAGS = -Werror -Wextra -Wall -g3 -O3 

CFLAGS_DEBUG = -Wextra -Wall -g3

CPPFLAGS = -I$(INCS) -I$(INCS_LIBFT) -I$(INCS_MLX) -MMD -MP

MLX_FLAGS = -L$(dir $(MLX_TARGET)) -lmlx_Linux -L/usr/lib -lX11 -lXext -lm -lz -lmlx

CFSIGSEV = -Wextra -Wall -fsanitize=address

RM = rm -rf

DIR_DUP= mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

# **********************************RULES**************************************** #

.PHONY: all
all: $(NAME)

.PHONY: bonus
bonus:

-include $(DEPS)
-include $(DEPS_BONUS)

$(NAME): $(LIBFT_TARGET) $(MLX_TARGET) $(OBJS)
	$(CC) $(CFLAGS) -g3 $(CPPFLAGS) $(OBJS) -L$(dir $(LIBFT_TARGET)) -lft $(MLX_FLAGS) -o $(NAME)

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

.PHONY: fsanitize
fsanitize: CFLAGS = $(CFSIGSEV)
fsanitize : fclean $(LIBFT_TARGET) $(MLX_TARGET) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -L$(dir $(LIBFT_TARGET)) -lft $(MLX_FLAGS) -o $(NAME)


.PHONY: debug
debug: CFLAGS = $(CFLAGS_DEBUG)
debug : $(LIBFT_TARGET) $(MLX_TARGET) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -L$(dir $(LIBFT_TARGET)) -lft $(MLX_FLAGS) -o $(NAME)

.PHONY: clean
clean :
	$(RM) $(OBJS_DIR)
	$(MAKE) $@ -C ./libft
	$(MAKE) $@ -C ./mlx

.PHONY: fclean
fclean : clean
	$(RM) $(NAME)
	$(MAKE) $@ -C ./libft
	$(MAKE) $@ -C ./mlx

.PHONY: re
re : fclean all

.PHONY: print%
print% :
	@echo $(patsubst print%,%,$@)=
	@echo $($(patsubst print%,%,$@))

.PHONY: FORCE
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
