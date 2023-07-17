/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: villemustonen <villemustonen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:37:00 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/11 14:21:35 by villemuston      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char **argv)
{
	int i;
	int j;

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
	{
		printf("argument is not number");
		return (1);
	}
	vars->num_of_philos = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		vars->num_of_time_must_eat = ft_atoi(argv[5]);
	if (argv[5] && vars->num_of_time_must_eat == 0)
		return (1);
	return (0);
}

int	init_mutex(t_vars *vars)
{
	int i;

	i = vars->num_of_philos;
	vars->fork = malloc(sizeof(pthread_mutex_t) * vars->num_of_philos);
	if (!vars->fork)
		return (1);
	while (i >= 0)
	{
		i--;
		if (pthread_mutex_init(&(vars->fork[i]), NULL))
			return (1);
	}
	return (0);
}

int	init_philo(t_vars *vars)
{
	int	i;

	i = 0;
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
