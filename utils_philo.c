/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:21:20 by cleblais          #+#    #+#             */
/*   Updated: 2023/02/06 16:57:44 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	yummy(t_philo *philo, int name)
{
	print_message(philo, "is eating", name);
	if (philo->ac == 6)
		pthread_mutex_unlock(&(philo->frigo));
	pthread_mutex_lock(&(philo->mutex_time_max));
	philo->time_max[name] = ft_clock(philo) + philo->time_to_die;
	pthread_mutex_unlock(&(philo->mutex_time_max));
	ft_sleep(philo, philo->time_to_eat);
}

int	still_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->still_eating));
	if (philo->diner_finished == YES)
	{
		pthread_mutex_unlock(&(philo->still_eating));
		return (NO);
	}
	pthread_mutex_unlock(&(philo->still_eating));
	return (YES);
}

void	ft_sleep(t_philo *philo, long long sleeping_time)
{
	long	begin_of_sleep;
	int		modulo;
	int		i;

	begin_of_sleep = ft_clock(philo);
	if (sleeping_time < 1000000)
		usleep(sleeping_time * 0.95);
	else
	{
		i = 0;
		modulo = sleeping_time % 100000;
		while (i < sleeping_time / 100000)
		{
			if (still_eating(philo) == YES)
				usleep(100000);
			i++;
		}
		usleep(modulo);
	}
	if (still_eating(philo) == YES)
	{
		while (ft_clock(philo) - begin_of_sleep < sleeping_time)
			usleep(1);
	}
}

long	ft_clock(t_philo *philo)
{
	long	time;

	gettimeofday(&(philo->time), NULL);
	time = (philo->time.tv_sec * 1000000 + philo->time.tv_usec);
	return (time);
}

void	print_message(t_philo *philo, char *str, int name)
{
	pthread_mutex_lock(&(philo->mic));
	if (still_eating(philo) == YES)
		printf("%ld	%d	%s\n", (ft_clock(philo) - philo->begin) \
			/ 1000, name + 1, str);
	pthread_mutex_unlock(&(philo->mic));
}
