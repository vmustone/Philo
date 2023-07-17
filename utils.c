/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:45:32 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/17 16:29:56 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long int	res;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res < 0)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		str++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	long long	i;

	i = timestamp();
	while (timestamp() - i < time)
		usleep(time / 10);
}

void	print(t_vars *vars, int philo, char *str)
{
	pthread_mutex_lock(&(vars->print));
	if (!(vars->dead))
	{
		printf("%lld ", timestamp() - vars->start);
		printf("%d ", philo + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(vars->print));
}
