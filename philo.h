/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: villemustonen <villemustonen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:25:16 by vmustone          #+#    #+#             */
/*   Updated: 2023/06/22 18:17:43 by villemuston      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int				left;
	int				right;
	int 			id;
	int				eat_count;
	long long		last_eat;
	pthread_t		thread;
	struct t_vars 	*vars;
}				t_philo;

typedef struct			s_vars
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int 	num_of_time_must_eat;
	pthread_mutex_t lock;
	pthread_mutex_t *fork;
}						t_vars;

int		ft_atoi(const char *str);
int 	ft_isdigit(int c);
int		parse_argv(t_vars *vars, char **argv);
void	init_mutex(t_vars *vars);
void	init_philo(t_vars *vars, t_philo **philo);
int		is_number(char **argv);

#endif
