NAME		= fractol

# COMPIER

CC				=	gcc
CFLAGS			=	-Wall -Wextra

# OPTIONS

OPTIONS			:=

ifeq ($(OS),Darwin)
	OPTIONS += -framework OpenCL
else
	OPTIONS += -l OpenCL
endif

# COLORS

RED				:=	"\033[31m"
WAVE			:=	"\033[36m"
EOC				:=	"\033[0m"
BLINK			:=	"\033[5m"
GREEN			:=	"\033[32m"

# SRCS & OBJ

SRCS			=	main.c\
					keys.c\
					utils.c\
					terminate.c

OBJ				=	$(addprefix $(OBJDIR),$(SRCS:.c=.o))

# HEADERS

HEADER_LIST		=	visual.h\
					keys.h\
					window.h\
					cl_h.h

HEADERS			=	$(addprefix $(INCDIR), $(HEADER_LIST))

# DIRECTORIES

INCDIR			=	./includes/

SRC_DIR			=	./srcs/

OBJDIR			=	./obj/

# FT LIBRARY

LIBFT			=	$(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY =	./libft/
LIBFT_HEADERS	=	$(LIBFT_DIRECTORY)includes/
LIBFT_LINK		=	 -lft -L$(LIBFT_DIRECTORY)

# MLX LIBRARY

MLX_LINK		=	-I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -framework OpenCL

# INCLUDES

INCLUDES		=	-I $(INCDIR) -I $(LIBFT_HEADERS)

all: $(NAME)

$(OBJDIR):
	@echo " - Creating dir $(OBJDIR)"
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRC_DIR)%.c $(HEADERS)
	@echo $(WAVE) " - Compiling $<  ->  $@" $(EOC)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	@echo $(GREEN) " - Compiling $@" $(EOC)
	@$(CC) $(OBJ) $(MLX_LINK) $(LIBFT_LINK) -o $@

clean:
	@echo " - Deleting $(OBJDIR)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo " - Deleting $(NAME)"
	@echo " - Cleaning $(LIBFT_DIRECTORY)"
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIRECTORY) fclean

re: fclean all

.PHONY: all obj clean fclean re