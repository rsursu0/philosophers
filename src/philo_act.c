/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:36:55 by wbae              #+#    #+#             */
/*   Updated: 2023/03/09 18:02:32 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_print(t_philo *philo, char *msg, int flag)
{
	long long	time;

	time = ft_get_time() - philo->info->start_time;
	pthread_mutex_lock(&philo->info->m_print);
	if (!philo->info->stop_flag && !philo->info->max_ate)
		printf("%lld %d %s\n", time, philo->id, msg);
	if (flag)
		pthread_mutex_unlock(&philo->info->m_print);
}

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_forks[philo->right_fork]);

	p_print(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->info->m_forks[philo->left_fork]);
	p_print(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->info->m_meal);
	p_print(philo, "is eating", 1);
	philo->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&philo->info->m_meal);
	ft_sleep(philo->info->time_to_eat);
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->info->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->m_forks[philo->right_fork]);
}

void	is_dead(t_info *info, t_philo *philo)
{
	int	i;

	while (!info->max_ate)
	{
		i = 0;
		while (i < info->num_philo && !info->stop_flag)
		{
			pthread_mutex_lock(&info->m_meal);
			if (ft_get_time() - philo[i].last_eat_time >= info->time_to_die)
			{
				p_print(philo, "died", 0);
				info->stop_flag = 1;
			}
			pthread_mutex_unlock(&info->m_meal);
		}
		if (info->stop_flag)
			break ;
		i = 0;
		while (info->max_eat_cnt && i < info->num_philo \
			&& philo[i].eat_cnt >= info->max_eat_cnt)
			i++;
		info->max_ate = (i == info->num_philo);
	}
}
