# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 13:53:00 by dbaffier          #+#    #+#              #
#    Updated: 2018/08/28 02:48:57 by rfontain         ###   ########.fr        #
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
		srcs/calculate.c			\
		srcs/deal_key.c				\
		srcs/grid.c					\
		srcs/deal_image.c			\
		srcs/tools.c

OK = "     	\033[32m"[OK]"\033[00m"

CFLAGS +=  -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(INCS) -o $@ $^ $(LIB_LINK) -lmlx -framework OpenGl -framework AppKit
	@echo "Compilling" [ $(NAME) ] $(OK)

$(LIB):
	@make -C $(LIB_PATH)

all: $(NAME)

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
