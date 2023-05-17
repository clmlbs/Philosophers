/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:46:56 by cleblais          #+#    #+#             */
/*   Updated: 2023/02/06 16:33:53 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*diner(void *person)
{
	t_person	*p;
	t_philo		*philo;
	int			name;
	int			seatmate;

	p = (t_person *)person;
	name = p->name;
	philo = p->philo;
	if (name == philo->phil_nb - 1)
		seatmate = 0;
	else
		seatmate = name + 1;
	if (name % 2 != 0)
		ft_sleep(philo, 250);
	while (still_eating(philo) == YES)
	{
		if (steps_of_diner(philo, name, seatmate) == 0)
			break ;
	}
	return (NULL);
}

int	steps_of_diner(t_philo *philo, int name, int seatmate)
{
	pthread_mutex_lock(&(philo->mu_fork[name]));
	philo->fork[name] = TAKEN;
	if (still_eating(philo) == YES)
		print_message(philo, "has taken a fork", name);
	if (philo->phil_nb == 1)
	{
		ft_sleep(philo, philo->time_to_die - (ft_clock(philo) - philo->begin));
		return (0);
	}
	second_mu_fork(philo, name, seatmate);
	eating(philo, name, seatmate);
	sleeping(philo, name);
	thinking(philo, name);
	return (1);
}

void	the_bill_please(t_philo *philo, int name)
{
	pthread_mutex_unlock(&(philo->frigo));
	pthread_mutex_lock(&(philo->mic));
	pthread_mutex_lock(&(philo->still_eating));
	philo->diner_finished = YES;
	pthread_mutex_unlock(&(philo->still_eating));
	printf("%ld	%d	is eating\n", (ft_clock(philo) - philo->begin) / 1000, \
		name + 1);
	pthread_mutex_unlock(&(philo->mic));
}
