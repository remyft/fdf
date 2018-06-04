# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 13:53:00 by dbaffier          #+#    #+#              #
#    Updated: 2018/06/04 23:31:43 by rfontain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

RM = rm -rf

LIB_PATH = libft
LIB = $(LIB_PATH)/libft.a
LIB_LINK = -L $(LIB_PATH) -lft

INC_DIR = includes
INCS = -I $(LIB_PATH)/ -I $(INC_DIR)

SRCS =	srcs/fdf.c					\
		srcs/ft_calculate.c			\
		srcs/ft_deal_image.c		\
		srcs/ft_tools.c

OK = "     	\033[32m"[OK]"\033[00m"

CFLAGS +=  -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(INCS) -o $@ $^ $(LIB_LINK) -lmlx -framework OpenGl -framework AppKit
	@echo "Compilling" [ $(NAME) ] $(OK)

$(LIB):
	@make -C $(LIB_PATH)

all: $(NAME)

$(OBJ_DIR)%.o: %.c ft_fillit.h
	@$(CC) $(INCS) -c -o $@ $<
	@echo "Linking" [ $< ] $(OK)

clean:
	@$(RM) $(OBJS)
	@make -C $(LIB_PATH) clean
	@echo "cleaning :" [ $(NAME) ] $(OK)

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Deleting.." [ $(NAME) ] $(OK)

re: fclean all

.PHONY: clean fclean all re
