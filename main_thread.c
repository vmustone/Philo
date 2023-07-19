/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:03:26 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/19 19:05:38 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_eat_enough(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_of_philos)
	{
		pthread_mutex_lock(&(vars->lock));
		if (vars->philo[i].eat_count < vars->num_of_time_must_eat)
		{
			pthread_mutex_unlock(&(vars->lock));
			break ;
		}
		pthread_mutex_unlock(&(vars->lock));
		i++;
	}
	if (i == vars->num_of_philos)
	{
		pthread_mutex_lock(&(vars->lock));
		vars->all_ate = 1;
		pthread_mutex_unlock(&(vars->lock));
	}
	return (vars->all_ate);
}

static void	check_philo_status(t_vars *vars, t_philo *philo)
{
	int	i;

	while (check_all_ate(vars) == 0 && vars->dead == 0)
	{
		i = -1;
		while (++i < vars->num_of_philos && vars->dead == 0)
		{
			pthread_mutex_lock(&(vars->lock));
			if ((timestamp() - philo[i].last_eat) > vars->time_to_die)
			{
				print(vars, i, "died");
				vars->dead = 1;
				pthread_mutex_unlock(&(vars->lock));
				break ;
			}
			pthread_mutex_unlock(&(vars->lock));
		}
		if (vars->dead == 1)
			break ;
		if (vars->num_of_time_must_eat > 0)
		{
			vars->all_ate = check_eat_enough(vars);
		}
	}
}

static void	join_and_destroy(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_of_philos)
	{
		pthread_join(vars->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < vars->num_of_philos)
	{	
		pthread_mutex_destroy(&(vars->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(vars->print));
	pthread_mutex_destroy(&(vars->lock));
}

int	create_philo_threads(t_vars *vars)
{
	int	i;

	i = 0;
	vars->start = timestamp();
	while (i < vars->num_of_philos)
	{
		if (pthread_create(&(vars->philo[i].thread),
				NULL, philo_thread, &(vars->philo[i])))
			return (1);
		pthread_mutex_lock(&(vars->lock));
		vars->philo[i].last_eat = timestamp();
		pthread_mutex_unlock(&(vars->lock));
		i++;
	}
	check_philo_status(vars, vars->philo);
	join_and_destroy(vars);
	return (0);
}
