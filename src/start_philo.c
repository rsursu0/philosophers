/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:27:31 by wbae              #+#    #+#             */
/*   Updated: 2023/03/14 19:33:39 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*run_philo(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)arg;
	info = philo->info;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (!info->stop_flag && !info->max_ate)
	{
		grab_fork(info, philo);
		p_eat(info, philo);
		p_print(philo, "is sleeping");
		ft_sleep(info->time_to_sleep);
		p_print(philo, "is thinking");
		usleep(100);
	}
	return (NULL);
}

static void	collect_thread(t_info *info)
{
	int	i;

	if (info->num_philo == 1)
		pthread_detach(info->philos[0].thread);
	else
	{
		i = -1;
		while (++i < info->num_philo)
			pthread_join(info->philos[i].thread, NULL);
	}
}

int	ft_start_philo(t_info *info)
{
	int	i;

	info->start_time = ft_get_time();
	i = 0;
	while (i < info->num_philo)
	{
		info->philos[i].last_eat_time = ft_get_time();
		if (pthread_create(&info->philos[i].thread, \
			NULL, run_philo, &(info->philos[i])))
			return (0);
		i++;
	}
	is_dead(info, info->philos);
	if (info->max_ate)
		printf("All philosophers finished their meal\n");
	collect_thread(info);
	ft_end_philo(info);
	return (1);
}
