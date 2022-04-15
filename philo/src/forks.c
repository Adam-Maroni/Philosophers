/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:11:05 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/15 12:21:33 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_take_forks_left_then_right(t_global *global,
		pthread_mutex_t	*left_fork, pthread_mutex_t *right_fork,
		t_philo_list *philo)
{
	pthread_mutex_lock(left_fork);
	ft_display_message(global->mutex_message,
		ft_timestamp(global->start_time),
		philo->id, 4);
	pthread_mutex_lock(right_fork);
	ft_display_message(global->mutex_message,
		ft_timestamp(global->start_time), philo->id, 4);
}

void	ft_take_forks_right_then_left(t_global *global,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork,
		t_philo_list *philo)
{
	pthread_mutex_lock(right_fork);
	ft_display_message(global->mutex_message,
		ft_timestamp(global->start_time),
		philo->id, 4);
	pthread_mutex_lock(left_fork);
	ft_display_message(global->mutex_message,
		ft_timestamp(global->start_time), philo->id, 4);
}
