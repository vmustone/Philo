/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: villemustonen <villemustonen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:40:51 by villemuston       #+#    #+#             */
/*   Updated: 2023/07/16 21:07:48 by villemuston      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	long long i;

	i = timestamp();
	while (timestamp() - i < time)
		usleep(time / 10);
}

void	print(t_vars *vars, int philo, char *str)
{
	printf("%lld ", timestamp() - vars->start);
	printf("%d ", philo + 1);
	printf("%s\n", str);
}

void philo_eating(t_philo *philo)
{
    t_vars *vars = philo->vars;

    pthread_mutex_lock(&(vars->fork[philo->left_f]));
    print(vars, philo->id, "has taken a fork");
    pthread_mutex_lock(&(vars->fork[philo->right_f]));
    print(vars, philo->id, "has taken a fork");

    ft_usleep(vars->time_to_eat);

    (philo->eat_count)++;

    pthread_mutex_unlock(&(vars->fork[philo->left_f]));
    pthread_mutex_unlock(&(vars->fork[philo->right_f]));
}


void	Philo_quit(t_vars *vars, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < vars->num_of_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	while(1)
	{
		philo_eating(philo);
		print(vars, philo->id, "is sleeping");
		ft_usleep(vars->time_to_sleep);
		print(vars, philo->id, "is thinking");
	}
	return (NULL);
}

void	create_philo_threads(t_vars *vars)
{
	int	i;
	t_philo *philo;
	
	i = 0;
	philo = vars->philo;
	vars->start = timestamp();
	while (i < vars->num_of_philos)
	{
		if (pthread_create(&(vars->philo[i].thread), NULL, philo_thread, &(vars->philo[i])))
		{
			printf("error in creating threads");
			return ;
		}
		vars->philo[i].last_eat = timestamp();
		i++;
	}
	Philo_quit(vars, philo);
}