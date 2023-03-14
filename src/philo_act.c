/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:36:55 by wbae              #+#    #+#             */
/*   Updated: 2023/03/14 19:33:41 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_print(t_philo *philo, char *msg)
{
	long long	time;

	time = ft_get_time() - philo->info->start_time;
	pthread_mutex_lock(&philo->info->m_print);
	if (!philo->info->stop_flag && !philo->info->max_ate)
		printf("%lld %d %s\n", time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->info->m_print);
}

void	grab_fork(t_info *info, t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&info->m_forks[philo->left_fork]);
		info->forks[philo->left_fork] = PICKED;
		p_print(philo, "has taken a fork");
		pthread_mutex_lock(&info->m_forks[philo->right_fork]);
		info->forks[philo->right_fork] = PICKED;
		p_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&info->m_forks[philo->right_fork]);
		info->forks[philo->right_fork] = PICKED;
		p_print(philo, "has taken a fork");
		pthread_mutex_lock(&info->m_forks[philo->left_fork]);
		info->forks[philo->left_fork] = PICKED;
		p_print(philo, "has taken a fork");
	}
}

void	p_eat(t_info *info, t_philo *philo)
{
	p_print(philo, "is eating");
	philo->last_eat_time = ft_get_time();
	ft_sleep(info->time_to_eat);
	philo->eat_cnt++;
	info->forks[philo->right_fork] = DOWNED;
	info->forks[philo->left_fork] = DOWNED;
	pthread_mutex_unlock(&info->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&info->m_forks[philo->right_fork]);
}

void	is_dead(t_info *info, t_philo *philo)
{
	int	i;

	while (!info->max_ate)
	{
		i = -1;
		while (++i < info->num_philo && !info->stop_flag)
		{
			if (ft_get_time() - philo[i].last_eat_time > info->time_to_die)
			{
				p_print(&philo[i], "died");
				info->stop_flag = 1;
			}
		}
		if (info->stop_flag)
			break ;
		i = 0;
		while (info->must_eat && i < info->num_philo \
			&& philo[i].eat_cnt >= info->must_eat)
			i++;
		info->max_ate = (i == info->num_philo);
	}
}
