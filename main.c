/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:24:20 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/17 16:18:01 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_and_free(t_vars *vars, int error)
{
	if (error == 1)
		exit(1);
	else
	{
		free(vars->fork);
		free(vars->philo);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
		return (1);
	if (parse_argv(&vars, argv) == 1)
		error_and_free(&vars, 1);
	if (init_mutex(&vars) == 1)
		error_and_free(&vars, 1);
	if (init_philo(&vars) == 1)
		error_and_free(&vars, 1);
	create_philo_threads(&vars);
	error_and_free(&vars, 0);
	return (0);
}
