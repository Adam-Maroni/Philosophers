/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:58:38 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/13 17:03:07 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * \file subrotuines.c
 * \brief This file contains the subroutine 
 * that will be used by threads main routine.
 */

/**
 * \fn int	ft_take_forks(t_global *global,
	pthread_mutex_t *left_fork, pthread_mutex_t *right_fork,
	t_philo_list *philo)
 * \brief This function ensure the mutex are lock by the thread.
 * \param left_fork The fork held by the current philosopher.
 * \param right_fork The fork held by its neighbour.
 * \return 1 if the mutex were locked successfully. 
 * 0 otherwise.
 */
int	ft_take_forks(t_global *global,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork,
		t_philo_list *philo)
{
	if (!left_fork || !right_fork || left_fork == right_fork)
		return (-1);
	if (philo->id % 2 == 0)
		return (ft_take_forks_right_left(global, left_fork, right_fork, philo));
	else
		return (ft_take_forks_left_right(global, left_fork, right_fork, philo));
}

void	ft_clean_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	if (left_fork == right_fork
		|| !left_fork || !right_fork)
		return ;
	if (pthread_mutex_unlock(right_fork) == 0
		&& pthread_mutex_unlock(left_fork) == 0)
		return ;
	else
		printf("PROBLEM.\n");
}

void	ft_eat(t_global *global, t_philo_list *philo)
{
	if (!global)
		return ;
	ft_display_message(global,
		ft_timestamp(global->start_time), philo->id, 0);
	pthread_mutex_lock(global->mutex_total_meals);
	philo->time_of_last_meal_in_ms = ft_timestamp(global->start_time);
	philo->eat_counter++;
	global->total_meals++;
	pthread_mutex_unlock(global->mutex_total_meals);
	usleep(global->time_to_eat * 1000);
}

void	ft_sleep(t_global *global, t_philo_list *philo)
{
	if (!global)
		return ;
	ft_display_message(global,
		ft_timestamp(global->start_time), philo->id, 1);
	usleep(global->time_to_sleep * 1000);
}

void	ft_think(t_global *global, t_philo_list *philo)
{
	if (!global)
		return ;
	ft_display_message(global,
		ft_timestamp(global->start_time), philo->id, 2);
}
