# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:28:52 by vmustone          #+#    #+#              #
#    Updated: 2023/06/07 10:39:13 by vmustone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name = philo

Flags = -Wall -Werror -Wextra -pthread

Source = main.c utils.c init.c

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