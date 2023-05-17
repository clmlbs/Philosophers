/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:19:44 by cleblais          #+#    #+#             */
/*   Updated: 2023/02/06 16:47:54 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	second_mu_fork(t_philo *philo, int name, int seatmate)
{
	pthread_mutex_lock(&(philo->mu_fork[seatmate]));
	philo->fork[seatmate] = TAKEN;
	if (still_eating(philo) == YES)
		print_message(philo, "has taken a fork", name);
}

void	eating(t_philo *philo, int name, int seatmate)
{
	if (still_eating(philo) == YES)
	{	
		if (philo->ac == 6)
		{
			pthread_mutex_lock(&(philo->frigo));
			philo->nb_of_meal--;
			if (philo->nb_of_meal == 0)
				the_bill_please(philo, name);
			else
				yummy(philo, name);
		}
		else
			yummy(philo, name);
	}
	philo->fork[name] = AVAILABLE;
	pthread_mutex_unlock(&(philo->mu_fork[name]));
	philo->fork[seatmate] = AVAILABLE;
	pthread_mutex_unlock(&(philo->mu_fork[seatmate]));
}

void	sleeping(t_philo *philo, int name)
{
	if (still_eating(philo) == YES)
	{
		print_message(philo, "is sleeping", name);
		ft_sleep(philo, philo->time_to_sleep);
	}
}

void	thinking(t_philo *philo, int name)
{
	if (still_eating(philo) == YES)
		print_message(philo, "is thinking", name);
}

void	dying(t_philo *philo, int name)
{
	pthread_mutex_lock(&(philo->still_eating));
	philo->diner_finished = YES;
	pthread_mutex_unlock(&(philo->still_eating));
	printf("%ld	%d	died\n", (ft_clock(philo) - philo->begin) / 1000, name + 1);
}
