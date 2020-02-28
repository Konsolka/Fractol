# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburl <mburl@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 19:30:25 by mburl             #+#    #+#              #
#    Updated: 2020/02/28 16:50:05 by mburl            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

# headers

HEADER_LIST		= libft.h get_next_line.h
INCDIR			= ./includes/
HEADERS			= $(addprefix $(INCDIR), $(HEADER_LIST))

INCLUDES		= -I $(INCDIR)
SRCSDIR	= ./srcs/
OBJDIR	= ./obj/

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_islower.c ft_isprint.c ft_isupper.c ft_memalloc.c \
	  ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
	  ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c ft_strclr.c \
	  ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_striter.c \
	  ft_striteri.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strncat.c \
	  ft_strncmp.c ft_strncpy.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
	  ft_strstr.c ft_tolower.c ft_toupper.c ft_strmapi.c ft_strequ.c \
	  ft_strsub.c ft_strjoin.c ft_strnequ.c ft_strtrim.c ft_itoa.c \
	  ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
	  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
	  ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	  ft_strsplit.c ft_strnch.c ft_intlen.c ft_countwords.c ft_chrcmp.c \
	  ft_putstr_err.c ft_lstcount.c ft_lstrev.c get_next_line.c ft_pow.c \
	  ft_strtab_free.c ft_strmerge.c

OBJ		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))

# color
WAVE	:= "\033[36m"
EOC		:= "\033[0m"
GREEN	:= "\033[32m"

all: obj $(NAME) $(HEADERS)

obj:
	@echo " - Creating dir $(OBJDIR)"
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCSDIR)%.c $(HEADERS)
	@echo $(WAVE) " - Compiling $<  ->  $@" $(EOC)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJ)
	@echo $(GREEN) " - Running $@" $(EOC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
