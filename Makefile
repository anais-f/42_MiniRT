NAME = miniRT
NAME_BONUS = miniRT_bonus

LIBS = libft.a libmlx_Linux.a

# *********************************VARIABLES**************************************** #

SRCS_DIR = ./srcs/

SRCS_LST= \
		main.c \
		$(addprefix camera/, $(SRCS_CAMERA)) \
		$(addprefix display_mlx/, $(SRCS_DISPLAYMLX)) \
		$(addprefix objects/, $(SRCS_OBJECTS)) \
		$(addprefix parsing/, $(SRCS_PARSING)) \
		$(addprefix render/, $(SRCS_RENDER)) \
		$(addprefix vector/, $(SRCS_VECTOR)) \
		$(addprefix array/, $(SRCS_ARRAY)) \
		$(addprefix utils/, $(SRCS_UTILS)) \
		$(addprefix matrix/, $(SRCS_MATRIX)) \

SRCS_ARRAY=\
		array.c \
		print_array.c \

SRCS_CAMERA=\
		cam_rotation.c \
		cam_move.c \

SRCS_DISPLAYMLX=\
		destroy_mlx.c \
		event_mlx.c \
		init_mlx.c \
		my_pxl_put.c \

SRCS_MATRIX=\
		identity_matrix.c \
		arithmetic_matrix.c \

SRCS_OBJECTS=\
		sphere.c \
		plane.c \
		cylinder.c \
		common_objects.c \
		caps.c \

SRCS_PARSING=\
		array_utils.c \
		check_input.c \
		float_utils.c \
		parsing_cam.c \
		parsing_lights.c \
		parsing_objects.c \
		parsing_utils.c \
		parsing.c \
		split_commas.c

SRCS_RENDER=\
		light.c \
		ray.c \
		render.c \

SRCS_UTILS=\
		utils_error.c \
		initialization.c \

SRCS_VECTOR=\
		arithmetic_vector.c \
		color.c \
		cross_product.c \
		divide.c \
		dot_product.c \
		multiply.c \
		normalize.c \

SRCS := $(addprefix $(SRCS_DIR), $(SRCS_LST))

SRCS_DIR_BONUS = ./srcs_bonus/

SRCS_LST_BONUS =\
		./objects/ellipsoid_bonus.c \
		./display_mlx/get_color_pixel_bonus.c \
		./parsing/parsing_ellipsoid_bonus.c

SRCS_BONUS := $(patsubst $(SRCS_DIR)%, $(SRCS_DIR_BONUS)% , $(patsubst %.c, %_bonus.c, $(SRCS)))
SRCS_BONUS += $(addprefix $(SRCS_DIR_BONUS), $(SRCS_LST_BONUS))

OBJS_DIR = ./.objs/
OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

OBJS_DIR_BONUS = ./.objs_bonus/
OBJS_BONUS = $(SRCS_BONUS:$(SRCS_DIR_BONUS)%.c=$(OBJS_DIR_BONUS)%.o)

INCS = ./incs/ ./mlx/ ./libft/INCS/ 
INCS_BONUS = ./incs_bonus/ ./mlx/ ./libft/INCS/


DEPS = $(OBJS:.o=.d)
DEPS_BONUS = $(OBJS_BONUS:.o=.d)

LIBS_PATH = ./libft/libft.a ./mlx/libmlx_Linux.a
LIBS_TARGET = $(patsubst lib%.a, %, $(notdir $(LIBS_PATH))) X11 Xext m z

# **********************************COMMANDS**************************************** #

CC = cc

CFLAGS = -Werror -Wextra -Wall -O3 

CFLAGS_DEBUG = -Wextra -Wall -g3

CPPFLAGS = $(addprefix -I, $(dir $(INCS))) -MMD -MP
CPPFLAGS_BONUS = $(addprefix -I, $(dir $(INCS_BONUS))) -MMD -MP

LDFLAGS = $(addprefix -L, $(dir $(LIBS_PATH)))
LDLIBS =  $(addprefix -l, $(LIBS_TARGET))

CFSIGSEV = -Wextra -Wall -fsanitize=address

RM = rm -rf

DIR_DUP = mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

# **********************************RULES**************************************** #

.PHONY: all
all: $(NAME)

.PHONY: bonus
bonus: $(NAME_BONUS)

-include $(DEPS)
-include $(DEPS_BONUS)

$(NAME): $(LIBS_PATH) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	
$(NAME_BONUS): $(LIBS_PATH) $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) $(LDFLAGS) $(LDLIBS) -o $(NAME_BONUS)

$(LIBS_PATH): FORCE
	@echo " "
	@echo "\033[1m\033[35m#-------------------------[COMPILATION LIBS]-------------------------#\033[0m"
	$(MAKE) -C $(@D)
	@echo "\033[1m\033[35m#---------------------------[LIBS COMPILED]--------------------------#\033[0m"
	@echo " "


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS_DIR_BONUS)%.o: $(SRCS_DIR_BONUS)%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS_BONUS) -c $< -o $@

.PHONY: clean
clean :
	$(RM) $(OBJS_DIR)
	$(RM) $(OBJS_DIR_BONUS)
	$(MAKE) $@ -C ./libft
	$(MAKE) $@ -C ./mlx

.PHONY: fclean
fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
	$(MAKE) $@ -C ./libft
	$(MAKE) $@ -C ./mlx

.PHONY: re
re : fclean all

.PHONY: FORCE
FORCE:
