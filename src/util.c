/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:31:06 by wbae              #+#    #+#             */
/*   Updated: 2023/03/09 17:57:36 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_return_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (0);
}

int	ft_isdigit(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	ft_atoi(char *av)
{
	int			i;
	int			sign;
	long long	ret;

	i = 0;
	ret = 0;
	sign = 1;
	while (av[i] == 32 || (av[i] >= 9 && av[i] <= 13))
		i++;
	if (av[i] == '-' || av[i] == '+')
	{
		if (av[i] == '-')
			sign = -1;
		i++;
	}
	while (av[i] >= '0' && av[i] <= '9')
	{
		ret = ret * 10 + (av[i] - 48);
		if ((ret > 2147483647 && sign == 1) || (ret > 2147483648 && sign == -1))
			return (0);
		i++;
	}
	return (sign * ret);
}


void	ft_end_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->m_meal);
	pthread_mutex_destroy(&info->m_print);
	// free(info->philos);
	// free(info->m_forks);
	// free(info);
}
