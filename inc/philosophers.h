/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:18:26 by wbae              #+#    #+#             */
/*   Updated: 2023/03/14 17:44:47 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define PICKED 0
# define DOWNED 1

struct	s_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_cnt;
	long long		last_eat_time;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				num_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	long long		start_time;
	int				stop_flag;
	int				max_ate;
	int				*forks;
	t_philo			*philos;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_print;
}	t_info;

int			ft_init(t_info *info);
int			ft_start_philo(t_info *info);

void		p_print(t_philo *philo, char *msg);
void		grab_fork(t_info *info, t_philo *philo);
void		p_eat(t_info *info, t_philo *philo);
void		is_dead(t_info *info, t_philo *philo);

int			ft_strlen(char *s);
int			ft_return_error(char *msg);
int			ft_isdigit(char *s);
int			ft_atoi(char *av);
void		ft_end_philo(t_info *info);

void		ft_sleep(long long time);
long long	ft_get_time(void);

#endif
