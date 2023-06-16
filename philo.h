/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:25:16 by vmustone          #+#    #+#             */
/*   Updated: 2023/06/16 19:19:32 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct	s_philo
{
	int 			n;
	pthread_t		thread;
	pthread_mutex_t right_fork;
	pthread_mutex_t left_fork;
}				t_philo;

typedef struct			s_vars
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int 	num_of_time_must_eat;
	t_philo *philo;
}						t_vars;

int	ft_atoi(const char *str);
int ft_isdigit(int c);
int	parse_argv(t_vars *vars, char **argv);
int	is_number(char **argv);
#endif
