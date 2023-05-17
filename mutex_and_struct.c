/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_and_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:24:43 by cleblais          #+#    #+#             */
/*   Updated: 2023/02/06 16:40:48 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_nb + 1)
	{
		pthread_join(philo->thd[i], NULL);
		i++;
	}
}

void	philo_mutex_init(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_nb)
	{
		pthread_mutex_init(&(philo->mu_fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(philo->mic), NULL);
	pthread_mutex_init(&(philo->still_eating), NULL);
	pthread_mutex_init(&(philo->frigo), NULL);
	pthread_mutex_init(&(philo->mutex_time_max), NULL);
}

int	fill_struct_pointers(t_philo *philo)
{
	philo->mu_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		philo->phil_nb);
	if (!philo->mu_fork)
		return (0);
	philo->time_max = (long long *)malloc(sizeof(long long) * philo->phil_nb);
	if (!philo->time_max)
	{
		free(philo->mu_fork);
		return (0);
	}
	philo->thd = (pthread_t *)malloc(sizeof(pthread_t) * (philo->phil_nb + 1));
	if (!philo->thd)
	{
		free(philo->mu_fork);
		free(philo->time_max);
		return (0);
	}
	philo->fork = (int *)malloc(sizeof(int) * (philo->phil_nb));
	if (!philo->fork)
	{
		free(philo->mu_fork);
		free(philo->time_max);
		free(philo->thd);
	}
	return (1);
}

int	fill_struct(t_philo *philo, int ac, char **av)
{
	philo->mu_fork = NULL;
	philo->thd = NULL;
	philo->time_max = NULL;
	philo->ac = ac;
	philo->phil_nb = (int)ft_atoi(av[1]);
	philo->time_to_die = (long long)ft_atoi(av[2]) * 1000;
	philo->time_to_eat = (long long)ft_atoi(av[3]) * 1000;
	philo->time_to_sleep = (long long)ft_atoi(av[4]) * 1000;
	if (ac == 6)
	{
		philo->nb_of_meal = (int)ft_atoi(av[5]) * philo->phil_nb;
		if (philo->nb_of_meal == 0)
			return (0);
	}
	philo->diner_finished = NO;
	if (!fill_struct_pointers(philo))
		return (0);
	return (1);
}

void	free_struct(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->phil_nb)
	{
		pthread_mutex_destroy(&(philo->mu_fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(philo->mic));
	pthread_mutex_destroy(&(philo->still_eating));
	pthread_mutex_destroy(&(philo->frigo));
	pthread_mutex_destroy(&(philo->mutex_time_max));
	free(philo->mu_fork);
	free(philo->thd);
	free(philo->time_max);
	free(philo->fork);
}
