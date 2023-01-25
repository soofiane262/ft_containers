# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 15:28:01 by sel-mars          #+#    #+#              #
#    Updated: 2023/01/25 20:47:00 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_containers

CPP		=	c++

FLAGS	=	-Wall -Wextra -Werror -std=c++98

HEADERS	=	vector/main.hpp iterators/iterator_traits.hpp iterators/vec_iterator.hpp\
			iterators/_reverse_iterator.hpp vector/vector.hpp utils/utils.hpp

SRCS	=	vector/main.cpp

CTRS	=	ft_vector ft_utils

all: $(NAME)

$(NAME): ft_vector
	@cat ft_vector > $(NAME)
	@chmod +x $(NAME)

ft_vector:	$(SRCS) $(HEADERS)
	@$(CPP) $(FLAGS) $< -o $@

clean:
	@rm -f ft_vector

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all vector clean fclean re
