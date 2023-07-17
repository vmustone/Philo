# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: villemustonen <villemustonen@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:28:52 by vmustone          #+#    #+#              #
#    Updated: 2023/07/11 15:25:52 by villemuston      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name = philo

Flags = -Wall -Werror -Wextra -pthread -fsanitize=address

Source = main.c utils.c init.c philo.c

Objects = $(Source:%.c=%.o)

all: $(Name)

$(Name): $(Objects)
	cc $(Flags) $(Objects) -o $(Name)

clean:
	rm -f $(Objects)

fclean:	clean
	rm -f $(Name)

re: fclean all

%.o: %.c
	cc $(FLAGS) -c -o $@ $^

.phony: