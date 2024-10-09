
SRCS=\
		$(addprefix SRCS/int/, $(SRCS_INTEGER)) \
		$(addprefix SRCS/char/, $(SRCS_CHAR)) \
		$(addprefix SRCS/miscellaneous/, $(SRCS_MISCELLANEOUS)) \
		$(addprefix SRCS/mem/, $(SRCS_MEMORY)) \
		$(addprefix SRCS/str/, $(SRCS_STRING)) \
		$(addprefix SRCS/lst/, $(SRCS_LST)) \
		$(addprefix SRCS/get_next_line/, $(SRCS_GNL)) \
		$(addprefix SRCS/ft_printf/, $(SRCS_PRINTF)) \


#----------CHAR----------#
SRCS_CHAR=\
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_tolower.c \
		ft_toupper.c \

#----------INTEGER----------#
SRCS_INTEGER=\
		ft_atoi.c \
		ft_itoa.c \

#----------STRING----------#
SRCS_STRING=\
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_split.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_split_whitespace.c \

#----------MEMORY----------#
SRCS_MEMORY=\
		ft_bzero.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \

#----------LST----------#
SRCS_LST=\
        ft_lstadd_back_bonus.c \
        ft_lstadd_front_bonus.c \
        ft_lstclear_bonus.c \
        ft_lstdelone_bonus.c \
        ft_lstiter_bonus.c \
        ft_lstlast_bonus.c \
        ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
        ft_lstsize_bonus.c \

#----------MISCELLANEOUS----------#
SRCS_MISCELLANEOUS=\
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \

#----------GET_NEXT_LINE----------#
SRCS_GNL=\
		get_next_line.c \
		get_next_line_utils.c \

#----------FT_PRINTF----------#
SRCS_PRINTF=\
		ft_printf.c \
		ft_printf_putnbr.c \
		ft_printf_putstr.c \
