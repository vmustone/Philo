/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:25:16 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/03 16:32:45 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_vars
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int 	num_of_time_must_eat;
	pthread_mutex_t lock;
	pthread_mutex_t *fork;
}				t_vars;

typedef struct	s_philo
{
	int				left;
	int				right;
	int 			id;
	int				eat_count;
	int				is_eating;
	long long		last_eat;
	pthread_t		thread;
	t_vars 			*vars;
}				t_philo;

int			ft_atoi(const char *str);
int 		ft_isdigit(int c);
int			parse_argv(t_vars *vars, char **argv);
void		init_mutex(t_vars *vars);
void		init_philo(t_philo **philo, t_vars *vars);
int			is_number(char **argv);
long long	timestamp(void);
void		philo_eating(t_philo *philo);
void		philo_sleeping(t_philo *philo);
void		philo_thinking(t_philo *philo);
void		*philosopher(void *arg);

#endif
