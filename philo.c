#include "philo.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->fork[philo->left]);
	pthread_mutex_lock(&philo->vars->fork[philo->right]);
	philo->is_eating = 1;
	philo->last_eat = timestamp();
	usleep(philo->vars->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->vars->fork[philo->left]);
	pthread_mutex_unlock(&philo->vars->fork[philo->right]);
	philo->is_eating = 0;
	philo->eat_count++;
}
void	philo_sleeping(t_philo *philo)
{
	philo->last_eat = timestamp();
	usleep(philo->vars->time_to_sleep * 1000);
}

void	philo_thinking(t_philo *philo)
{
	philo->last_eat = timestamp();
	usleep(philo->vars->time_to_sleep * 1000);
}

void	*philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if ((timestamp() - philo->last_eat) > philo->vars->time_to_die)
		{
			pthread_mutex_lock(&philo->vars->lock);
			printf("%lld died %d\n", timestamp(), philo->id + 1);
			pthread_mutex_unlock(&philo->vars->lock);
			break;	
		}
		philo_eating(philo);
		if (philo->vars->num_of_time_must_eat > 0 && philo->eat_count >= philo->vars->num_of_time_must_eat)
		{
			break;
		}
		philo_thinking(philo);
		philo_sleeping(philo);
	}
	return (NULL);
}