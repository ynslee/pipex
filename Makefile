# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 14:59:05 by yoonslee          #+#    #+#              #
#    Updated: 2023/02/24 09:38:31 by yoonslee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRCS = main.c 
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):$(OBJS)
	make -C libft all
	make -C libft bonus
	cc $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

$(OBJS):$(SRCS)
	cc -c $(FLAGS) $(SRCS)

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean:clean
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean clean all

.PHONY: all bonus clean fclean re