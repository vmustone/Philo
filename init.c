/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: villemustonen <villemustonen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:37:00 by vmustone          #+#    #+#             */
/*   Updated: 2023/06/23 17:06:22 by villemuston      ###   ########.fr       */
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

void	init_mutex(t_vars *vars)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(vars->lock), NULL))
		printf("error");
	vars->fork = malloc(sizeof(pthread_mutex_t)
					* vars->num_of_philos);
	if (!vars->fork)
		printf("error");
	while (i < vars->num_of_philos)
	{
		if (pthread_mutex_init(&(vars->fork[i]), NULL))
			printf("error");
		i++;
	}
	
}

void	init_philo(t_philo **philo, t_vars *vars)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * vars->num_of_philos);
	if (!(philo))
		printf("error");
	while (i < vars->num_of_philos)
	{
		(*philo)[i].id = i;
		(*philo)[i].vars = vars;
		(*philo)[i].left = i;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat = get_time_in_ms();
		(*philo)[i].right = ((i + 1) % vars->num_of_philos);
	}
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