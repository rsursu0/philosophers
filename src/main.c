/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:27:02 by wbae              #+#    #+#             */
/*   Updated: 2023/03/14 18:58:32 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	before_init(t_info *info, int ac, char *av[])
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (0);
		if (ft_atoi(av[i]) < 0)
			return (0);
		i++;
	}
	info->num_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->must_eat = 0;
	if (ac == 6)
		info->must_eat = ft_atoi(av[5]);
	if (info->num_philo < 1 || info->time_to_die < 0 || info->time_to_eat < 0 \
		|| info->time_to_sleep < 0 || info->must_eat < 0)
		return (0);
	return (1);
}

int	main(int ac, char *av[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (ac < 5 || ac > 6)
		return (ft_return_error("input error!\n"));
	if (!before_init(&info, ac, av))
		return (ft_return_error("invalid argv error!\n"));
	if (!ft_init(&info))
		return (ft_return_error("init failed!\n"));
	if (!ft_start_philo(&info))
		return (ft_return_error("thread error!\n"));
	return (0);
}
