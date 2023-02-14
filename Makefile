# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 15:28:01 by sel-mars          #+#    #+#              #
#    Updated: 2023/02/14 11:16:27 by sel-mars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP		=	c++

FLAGS	=	-g -Wall -Wextra -Werror -std=c++98

SRCS	=	main.cpp main.hpp

ITERS	=	$(addprefix iterators/,iterator_traits.hpp vec_iterator.hpp _reverse_iterator.hpp)

TESTS	=	utils vector stack

BINS	=	$(addprefix ft_,$(TESTS))

all: | $(TESTS)

utils: ft_utils

ft_utils: $(addprefix utils/,$(SRCS) utils.hpp) $(ITERS)
	@$(CPP) $(FLAGS) $< -o $@

vector: ft_vector

ft_vector: $(addprefix vector/,$(SRCS) vector.hpp) $(ITERS)
	@$(CPP) $(FLAGS) $< -o $@

stack: ft_stack

ft_stack: $(addprefix stack/,$(SRCS) stack.hpp)
	@$(CPP) $(FLAGS) $< -o $@

clean:
	@rm -f $(BINS) .logs

fclean: clean

re: fclean all

.PHONY: all $(TESTS) clean fclean re