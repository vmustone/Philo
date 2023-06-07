/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:24:20 by vmustone          #+#    #+#             */
/*   Updated: 2023/06/07 15:12:57 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *data)
{
	t_philo *philo;
	
	philo = (t_philo *)data;
	printf("testi %d\n", philo->num_of_philos);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo 	philo;
	pthread_t	thread;

	if (argc == 5)
	{
		init(&philo, argv);
		while (philo.num_of_philos > 0)
		{
			printf("num %d\n", philo.num_of_philos);
			pthread_create(&thread, NULL, thread_routine, &philo);
			pthread_join(thread, NULL);
			philo.num_of_philos--;
		}
	}
	else
		printf("wrong input\n");
	return (0);
}