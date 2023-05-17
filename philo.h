/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:02:32 by cleblais          #+#    #+#             */
/*   Updated: 2023/02/06 16:57:05 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h> 
# include <stdlib.h>

# define YES 1
# define NO 0
# define AVAILABLE 1
# define TAKEN 0

typedef struct s_philo
{
	pthread_mutex_t	*mu_fork;
	pthread_mutex_t	mic;
	pthread_mutex_t	still_eating;
	pthread_mutex_t	frigo;
	pthread_mutex_t	mutex_time_max;
	pthread_t		*thd;
	int				*fork;
	int				phil_nb;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_of_meal;
	int				ac;
	long			begin;
	long long		*time_max;
	struct timeval	time;
	int				diner_finished;
}	t_philo;

typedef struct s_person
{
	t_philo	*philo;
	int		name;	
}	t_person;

long	ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int		arg_are_valid_nb(int ac, char **av);
int		checks_arg(int ac, char **av);

int		arg_are_digit(int ac, char **av);
int		arg_are_digit2(char **av, int i, int j);

void	second_mu_fork(t_philo *philo, int name, int seatmate);
void	eating(t_philo *philo, int name, int seatmate);
void	sleeping(t_philo *philo, int name);
void	thinking(t_philo *philo, int name);
void	dying(t_philo *philo, int name);

void	*diner(void *philo_struct);
int		steps_of_diner(t_philo *philo, int name, int seatmate);
void	the_bill_please(t_philo *philo, int name);

int		all_init(t_philo *philo, int ac, char **av, t_person **p);
void	*status(void *structure);
int		main(int ac, char **av);
int		check_meal_finished(t_philo *philo, int *name, int *status);

void	yummy(t_philo *philo, int name);
int		still_eating(t_philo *philo);
void	ft_sleep(t_philo *philo, long long sleeping_time);
long	ft_clock(t_philo *philo);
void	print_message(t_philo *philo, char *str, int name);

void	philo_join(t_philo *philo);
void	philo_mutex_init(t_philo *philo);
int		fill_struct_pointers(t_philo *philo);
int		fill_struct(t_philo *philo, int ac, char **av);
void	free_struct(t_philo *philo);

#endif