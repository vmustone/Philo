/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:37:00 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/20 15:40:11 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_argv(t_vars *vars, char **argv)
{
	if (is_number(argv))
		return (1);
	vars->num_of_philos = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (vars->num_of_philos <= 0 || vars->time_to_die <= 0
		|| vars->time_to_eat <= 0 || vars->time_to_sleep <= 0)
		return (1);
	if (argv[5])
	{
		vars->num_of_time_must_eat = ft_atoi(argv[5]);
		if (vars->num_of_time_must_eat <= 0)
			return (1);
	}
	return (0);
}

int	init_mutex(t_vars *vars)
{
	int	i;

	i = 0;
	vars->fork = malloc(sizeof(pthread_mutex_t) * vars->num_of_philos);
	if (!vars->fork)
		return (1);
	while (i < vars->num_of_philos)
	{
		if (pthread_mutex_init(&(vars->fork[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(vars->lock), NULL))
		return (1);
	if (pthread_mutex_init(&(vars->print), NULL))
		return (1);
	return (0);
}

int	init_philo(t_vars *vars)
{
	int	i;

	i = 0;
	vars->all_ate = 0;
	vars->dead = 0;
	vars->philo = malloc(sizeof(t_philo) * vars->num_of_philos);
	if (!vars->philo)
		return (1);
	while (i < vars->num_of_philos)
	{
		vars->philo[i].id = i;
		vars->philo[i].eat_count = 0;
		vars->philo[i].left_f = i;
		vars->philo[i].right_f = (i + 1) % vars->num_of_philos;
		vars->philo[i].last_eat = 0;
		vars->philo[i].vars = vars;
		i++;
	}
	return (0);
}
