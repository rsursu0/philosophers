/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:59:24 by wbae              #+#    #+#             */
/*   Updated: 2023/03/09 17:40:57 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_init_mutex(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->m_meal, NULL) \
		|| pthread_mutex_init(&info->m_print, NULL))
		return (1);
	while (i < info->num_philo)
	{
		if (pthread_mutex_init(&info->m_forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->philos[i].info = info;
		info->philos[i].id = i + 1;
		info->philos[i].right_fork = i;
		info->philos[i].left_fork = (i + 1) % info->num_philo;
		info->philos[i].eat_cnt = 0;
		i++;
	}
}

int	ft_init(t_info *info)
{
	info->philos = malloc(sizeof(t_philo) * info->num_philo);
	info->m_forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (ft_init_mutex(info))
	{
		free(info->philos);
		free(info->m_forks);
		return (0);
	}
	ft_init_philos(info);
	return (1);
}
