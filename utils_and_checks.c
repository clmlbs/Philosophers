/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_and_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 07:48:05 by cleblais          #+#    #+#             */
/*   Updated: 2023/02/06 16:22:48 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	total;

	i = 0;
	sign = 1;
	total = 0;
	while (str[i] && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		total = total * 10 + (str[i] - '0');
		i++;
	}
	return (total * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	arg_are_valid_nb(int ac, char **av)
{
	int		i;
	long	nb;

	i = 1;
	while (i < ac)
	{
		nb = ft_atoi(av[i]);
		if (nb < 0 || nb > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	checks_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "error: bad number of arguments\n", 31);
		return (0);
	}
	if (arg_are_digit(ac, av) == 0)
	{	
		write(2, "error: arguments should be numbers\n", 35);
		return (0);
	}
	if (arg_are_valid_nb(ac, av) == 0)
	{
		write(2, "error: arguments should be positive int\n", 40);
		return (0);
	}
	return (1);
}
