/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:40:51 by villemuston       #+#    #+#             */
/*   Updated: 2023/07/19 18:59:11 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_vars *vars)
{
	int	i;

	pthread_mutex_lock(&(vars->lock));
	i = vars->dead;
	pthread_mutex_unlock(&(vars->lock));
	return (i);
}

int	check_all_ate(t_vars *vars)
{
	int	i;

	pthread_mutex_lock(&(vars->lock));
	i = vars->all_ate;
	pthread_mutex_unlock(&(vars->lock));
	return (i);
}

static void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->vars->fork[philo->right_f]));
	print(philo->vars, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->vars->fork[philo->left_f]));
	print(philo->vars, philo->id, "has taken a fork");
	if (philo->vars->dead == 1)
	{
		pthread_mutex_unlock(&(philo->vars->fork[philo->right_f]));
		pthread_mutex_unlock(&(philo->vars->fork[philo->left_f]));
		return ;
	}
	print(philo->vars, philo->id, "is eating");
	pthread_mutex_lock(&(philo->vars->lock));
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&(philo->vars->lock));
	ft_usleep(philo->vars->time_to_eat);
	pthread_mutex_lock(&(philo->vars->lock));
	(philo->eat_count)++;
	pthread_mutex_unlock(&(philo->vars->lock));
	pthread_mutex_unlock(&(philo->vars->fork[philo->right_f]));
	pthread_mutex_unlock(&(philo->vars->fork[philo->left_f]));
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (1)
	{
		if (philo->vars->num_of_philos == 1)
			break ;
		philo_eating(philo);
		if (check_all_ate(vars) == 1 || vars->dead == 1)
			break ;
		print(vars, philo->id, "is sleeping");
		ft_usleep(vars->time_to_sleep);
		if (check_death(vars))
			break ;
		print(vars, philo->id, "is thinking");
	}
	return (NULL);
}
