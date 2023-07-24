/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:25:16 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/20 15:40:24 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				left_f;
	int				right_f;
	int				id;
	int				eat_count;
	long long		last_eat;
	pthread_t		thread;
	struct s_vars	*vars;
}					t_philo;

typedef struct s_vars
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_time_must_eat;
	int				all_ate;
	int				dead;
	long long		start;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}					t_vars;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			is_number(char **argv);
void		ft_usleep(int time, t_vars *vars);
void		print(t_vars *vars, int philo, char *str);
int			parse_argv(t_vars *vars, char **argv);
int			init_mutex(t_vars *vars);
int			init_philo(t_vars *vars);
int			create_philo_threads(t_vars *vars);
void		*philo_thread(void *arg);
long long	timestamp(void);
int			check_all_ate(t_vars *vars);
int			check_death(t_vars *vars);

#endif
