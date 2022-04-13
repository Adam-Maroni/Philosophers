/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:19:29 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/13 17:38:10 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_take_forks_left_right(t_global *global,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork,
		t_philo_list *philo)
{
	if (!left_fork || !right_fork || left_fork == right_fork)
		return (-1);
	if (pthread_mutex_lock(left_fork) == 0)
	{	
		ft_display_message(global,
			ft_timestamp(global->start_time),
			philo->id, 4);
		if (pthread_mutex_lock(right_fork) == 0)
		{
			ft_display_message(global,
				ft_timestamp(global->start_time), philo->id, 4);
			return (1);
		}
		pthread_mutex_unlock(left_fork);
	}
	return (0);
}

int	ft_take_forks_right_left(t_global *global,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork,
		t_philo_list *philo)
{
	if (!left_fork || !right_fork || left_fork == right_fork)
		return (-1);
	if (pthread_mutex_lock(right_fork) == 0)
	{	
		ft_display_message(global,
			ft_timestamp(global->start_time),
			philo->id, 4);
		if (pthread_mutex_lock(left_fork) == 0)
		{
			ft_display_message(global,
				ft_timestamp(global->start_time), philo->id, 4);
			return (1);
		}
		pthread_mutex_unlock(right_fork);
	}
	return (0);
}
