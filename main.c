/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:24:20 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/03 17:28:58 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_vars 	vars;
	t_philo *philo;
	int	i;

	i = 0;	
	if (argc != 5 && argc != 6)
		return (0);
	
	if (parse_argv(&vars, argv) == 1)
	{
		return (0);
	}
	init_philo(&philo, &vars);
	init_mutex(&vars);
	while (i < vars.num_of_philos)
	{
		pthread_create(&(philo[i].thread), NULL, philosopher, &philo[i]);
		i++;
	}
	i = 0;
	while (i < vars.num_of_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	
	return (0);
}