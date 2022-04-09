/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:58:38 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/09 14:51:53 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_take_forks(t_global *global,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	if (left_fork == right_fork
		|| !left_fork || !right_fork
		|| !global)
		return ;
	if (!pthread_mutex_lock(left_fork) && !pthread_mutex_lock(right_fork))
	{
		ft_display_message(ft_timestamp(global->start_time),
			(*global->philo)->id, 4);
		ft_display_message(ft_timestamp(global->start_time),
			(*global->philo)->id, 4);
	}
}

void	ft_clean_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	if (left_fork == right_fork
		|| !left_fork || !right_fork)
		return ;
	if (!pthread_mutex_unlock(right_fork) && !pthread_mutex_unlock(left_fork))
		return ;
	else
		printf("PROBLEM.\n");
}

void	ft_eat(t_global *global)
{
	t_philo_list	*philo;

	if (!global)
		return ;
	philo = *global->philo;
	ft_display_message(ft_timestamp(global->start_time), philo->id, 0);
	philo->eat_counter++;
	global->total_meals++;
	usleep(global->time_to_eat * 1000);
}

void	ft_sleep(t_global *global)
{
	if (!global)
		return ;
	ft_display_message(ft_timestamp(global->start_time),
		(*global->philo)->id, 1);
	usleep(global->time_to_sleep * 1000);
}

void	ft_think(t_global *global)
{
	if (!global)
		return ;
	ft_display_message(ft_timestamp(global->start_time),
		(*global->philo)->id, 2);
	usleep(5);
}
