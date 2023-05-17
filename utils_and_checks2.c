/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_and_checks2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:17:00 by cleblais          #+#    #+#             */
/*   Updated: 2023/02/06 16:22:48 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_are_digit2(char **av, int i, int j)
{
	if (av[i][j] == '+' || av[i][j] == '-')
	{
		if (av[i][j + 1] < '0' || av[i][j + 1] > '9')
			return (0);
	}
	else if (av[i][j] < '0' || av[i][j] > '9')
		return (0);
	return (1);
}

int	arg_are_digit(int ac, char **av)
{
	int		i;
	size_t	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (j < ft_strlen(av[i]))
		{
			while (av[i][j] == ' ' || (av[i][j] > 8 && av[i][j] < 14))
				j++;
			while (j < ft_strlen(av[i]))
			{
				if (!arg_are_digit2(av, i, j))
					return (0);
				j++;
			}
		}
		i++;
		j = 0;
	}
	return (1);
}
