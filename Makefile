# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 15:28:01 by sel-mars          #+#    #+#              #
#    Updated: 2023/02/18 17:30:05 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP		=	c++

FLAGS	=	-O3 -g -std=c++98 -Wall -Wextra -Werror -Wpedantic

SRCS	=	main.cpp main.hpp

ITERS	=	$(addprefix iterators/,iterator_traits.hpp reverse_iterator.hpp)

UTILS	=	$(addprefix utils/,$(SRCS) utils.hpp) $(ITERS)

STACK	=	$(addprefix stack/,$(SRCS) stack.hpp)

VECTOR	=	$(addprefix vector/,$(SRCS) vector.hpp) $(ITERS) iterators/random_access_iterator.hpp

MAP		=	$(addprefix map/,$(SRCS) map.hpp) $(ITERS)

TESTS	=	utils stack vector map

BINS	=	$(addprefix ft_,$(TESTS))

all: | $(TESTS)

utils: ft_utils

ft_utils: $(UTILS)
	$(CPP) $(FLAGS) $< -o $@

stack: ft_stack

ft_stack: $(STACK)
	$(CPP) $(FLAGS) $< -o $@

vector: ft_vector

ft_vector: $(VECTOR)
	$(CPP) $(FLAGS) $< -o $@

map: ft_map

ft_map: $(MAP)
	$(CPP) $(FLAGS) $< -o $@

clean:
	@rm -f $(BINS) .logs
	@rm -rf $(addsuffix .dSYM,$(BINS))

fclean: clean

re: fclean all

.PHONY: all $(TESTS) clean fclean re