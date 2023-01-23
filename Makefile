# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 15:28:01 by sel-mars          #+#    #+#              #
#    Updated: 2023/01/23 19:28:47 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Containers

CPP		=	c++

FLAGS	=	-Wall -Wextra -Werror -std=c++98

HEADERS	=	main.hpp vector/vector.hpp iterators/* utils/*

SRCS	=	main.cpp

all:		$(NAME)

$(NAME):	$(SRCS) $(HEADERS)
	@$(CPP) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
