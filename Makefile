# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 14:59:05 by yoonslee          #+#    #+#              #
#    Updated: 2023/02/21 08:02:43 by yoonslee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRCS = main.c 

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft all
	make -C libft bonus
	cc $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)

clean:
	make -C libft clean

fclean:clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean clean all

.PHONY: all bonus clean fclean re