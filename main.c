/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:24:20 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/20 15:35:16 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_and_free(t_vars *vars, int error)
{
	if (error == 1)
	{
		write(2, "error\n", 6);
		return (1);
	}
	else
	{
		free(vars->fork);
		free(vars->philo);
		return (0);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
	{
		error_and_free(&vars, 1);
		return (1);
	}
	if (parse_argv(&vars, argv) == 1 || init_mutex(&vars) == 1
		|| init_philo(&vars) == 1)
	{
		error_and_free(&vars, 1);
		return (1);
	}
	if (create_philo_threads(&vars) == 1)
	{
		error_and_free(&vars, 1);
		return (1);
	}
	error_and_free(&vars, 0);
	return (0);
}
