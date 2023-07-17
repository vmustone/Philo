/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: villemustonen <villemustonen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:24:20 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/11 15:13:37 by villemuston      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void test_initialization()
{
    // Create a t_vars structure to hold the test values
    t_vars vars;

    // Set the test values for the arguments
    char *argv[] = {"./program", "4", "200", "150", "100", NULL};

    // Test the parse_argv function
    if (parse_argv(&vars, argv) != 0)
    {
        printf("parse_argv failed\n");
        return;
    }

    // Test the init_mutex function
    if (init_mutex(&vars) != 0)
    {
        printf("init_mutex failed\n");
        return;
    }

    // Test the init_philo function
    init_philo(&vars);

    // Check if the values are set correctly
    printf("Number of philosophers: %d\n", vars.num_of_philos);
    printf("Time to die: %d\n", vars.time_to_die);
    printf("Time to eat: %d\n", vars.time_to_eat);
    printf("Time to sleep: %d\n", vars.time_to_sleep);
    printf("Number of times to eat: %d\n", vars.num_of_time_must_eat);

    // Check if the mutexes are initialized correctly
    for (int i = 0; i < vars.num_of_philos; i++)
    {
        if (pthread_mutex_trylock(&(vars.fork[i])) != 0)
        {
            printf("Mutex %d failed to initialize\n", i);
            return;
        }
    }

    // Clean up: free the memory allocated for the mutexes
    for (int i = 0; i < vars.num_of_philos; i++)
    {
        pthread_mutex_destroy(&(vars.fork[i]));
    }
    free(vars.fork);

    printf("Initialization tests passed\n");
}


int	main(int argc, char **argv)
{
	t_vars 	vars;

	if (argc != 5 && argc != 6)
		return (1);
	if (parse_argv(&vars, argv) == 1)
		return (1);
	if (init_mutex(&vars) == 1)
		return (1);
	if (init_philo(&vars) == 1)
		return (1);
	create_philo_threads(&vars);
	return (0);
}