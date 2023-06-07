/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:25:16 by vmustone          #+#    #+#             */
/*   Updated: 2023/06/07 10:40:54 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>

typedef struct s_philo
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}				t_philo;

int	ft_atoi(const char *str);
void	init(t_philo *philo, char **argv);
#endif
