/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:01:54 by cleblais          #+#    #+#             */
/*   Updated: 2023/02/06 16:54:33 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_finished(t_philo *philo, int *name, int *status)
{
	pthread_mutex_lock(&(philo->mutex_time_max));
	if (ft_clock(philo) > philo->time_max[*name])
	{
		*status = YES;
		pthread_mutex_unlock(&(philo->mutex_time_max));
		return (0);
	}
	pthread_mutex_unlock(&(philo->mutex_time_max));
	pthread_mutex_lock(&(philo->still_eating));
	if (philo->diner_finished == YES)
	{
		pthread_mutex_unlock(&(philo->still_eating));
		*status = YES;
		return (0);
	}
	pthread_mutex_unlock(&(philo->still_eating));
	(*name)++;
	return (1);
}

void	*status(void *structure)
{
	t_philo	*philo;
	int		name;
	int		status;

	name = 0;
	status = NO;
	philo = (t_philo *)structure;
	while (status == NO)
	{
		while (name < philo->phil_nb)
		{
			if (!check_meal_finished(philo, &name, &status))
				break ;
		}
		if (status == NO)
			name = 0;
	}
	if (still_eating(philo) == YES)
		dying(philo, name);
	return (NULL);
}

int	all_init(t_philo *philo, int ac, char **av, t_person **p)
{
	int	i;

	if (checks_arg(ac, av) == 0)
		return (0);
	if (fill_struct(philo, ac, av) == 0)
		return (0);
	philo_mutex_init(philo);
	*p = (t_person *)malloc(sizeof(t_person) * philo->phil_nb);
	if (!(*p))
	{
		free_struct(philo);
		return (0);
	}
	philo->begin = ft_clock(philo) + 100;
	i = 0;
	while (i < philo->phil_nb)
	{
		philo->time_max[i] = philo->begin + philo->time_to_die;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	t_person	*person;
	int			i;

	i = 0;
	person = NULL;
	if (!all_init(&philo, ac, av, &person))
		return (0);
	pthread_create(&(philo.thd[philo.phil_nb]), NULL, status, (void *)&philo);
	while (i < philo.phil_nb)
	{
		person[i].philo = &philo;
		person[i].name = i;
		pthread_create(&(philo.thd[i]), NULL, diner, (void *)&person[i]);
		i++;
	}
	philo_join(&philo);
	free_struct(&philo);
	free(person);
	return (0);
}
