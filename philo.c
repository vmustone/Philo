/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:40:51 by villemuston       #+#    #+#             */
/*   Updated: 2023/07/17 16:28:42 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo_status(t_vars *vars, t_philo *philo)
{
	int	i;

	i = 0;
	while (vars->all_ate == 0)
	{
		while (i < vars->num_of_philos && vars->dead == 0)
		{
			pthread_mutex_lock(&(vars->lock));
			if ((timestamp() - philo[i].last_eat) > vars->time_to_die)
			{
				print(vars, i, "died");
				vars->dead = 1;
			}
			pthread_mutex_unlock(&(vars->lock));
			usleep(100);
			i++;
		}
		if (vars->dead)
			break ;
		i = -1;
		while (++i < vars->num_of_philos
			&& philo[i].eat_count >= vars->num_of_time_must_eat)
			if (i == vars->num_of_philos)
				vars->all_ate = 1;
	}
}

void	philo_eating(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&(vars->fork[philo->left_f]));
	print(vars, philo->id, "has taken a fork");
	pthread_mutex_lock(&(vars->fork[philo->right_f]));
	print(vars, philo->id, "has taken a fork");
	pthread_mutex_lock(&(vars->lock));
	print(vars, philo->id, "is eating");
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&(vars->lock));
	ft_usleep(vars->time_to_eat);
	(philo->eat_count)++;
	pthread_mutex_unlock(&(vars->fork[philo->left_f]));
	pthread_mutex_unlock(&(vars->fork[philo->right_f]));
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	if (philo->id % 2)
		usleep(15000);
	while (vars->dead == 0)
	{
		philo_eating(philo);
		if (vars->all_ate)
			break ;
		print(vars, philo->id, "is sleeping");
		ft_usleep(vars->time_to_sleep);
		print(vars, philo->id, "is thinking");
	}
	return (NULL);
}

void	destroy_philo(t_vars *vars, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < vars->num_of_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < vars->num_of_philos)
	{	
		pthread_mutex_destroy(&(vars->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(vars->print));
}

int	create_philo_threads(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = vars->philo;
	vars->start = timestamp();
	while (i < vars->num_of_philos)
	{
		if (pthread_create(&(vars->philo[i].thread),
				NULL, philo_thread, &(vars->philo[i])))
			return (1);
		vars->philo[i].last_eat = timestamp();
		i++;
	}
	check_philo_status(vars, philo);
	destroy_philo(vars, philo);
	return (0);
}
