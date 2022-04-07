/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:19:07 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/07 15:39:18 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file meals_handler.c
 * \brief Contains functions for philosopher to meal.
*/

/** \headerfile philosopher.h */
#include "philosopher.h"

/**
 * \fn void *ft_eat_a_meal(void *global)
 * \brief The routine we call through 
 * the function pthread_create for the philosopher to eat.\n
 * This also here we lock and unlock the forks (the mutexes).
 * \param global : A structure containing 
 * both the philospher node and times Constants/Variables.
 */
void	*ft_routine(void *global)
{
	t_global		*cast;
	t_philo_list				*philo;
	t_timeval					*start_time;

	cast = (t_global *)(global);
	philo = *(cast->philo);
	philo->isavailable = 0;
	start_time = (cast->start_time);
	pthread_mutex_lock(philo->fork);
	ft_display_message(ft_timestamp(start_time), philo->id, 4);
	pthread_mutex_lock(philo->next->fork);
	ft_display_message(ft_timestamp(start_time), philo->id, 4);
	ft_display_message(ft_timestamp(start_time), philo->id, 0);
	philo->eat_counter++;
	cast->total_meals++;
	usleep(cast->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	ft_display_message(ft_timestamp(start_time), philo->id, 1);
	usleep(cast->time_to_sleep * 1000);
	philo->isavailable = 1;
	return (NULL);
}

/**
 * \fn int ft_are_forks_available(
 * pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
 * \brief This function checks if the forks given as parameters are available.
 * \param right_fork The first fork (mutex) 
 * the philosopher need to eat its meal.
 * \param left_fork The second fork (mutex) 
 * the philosopher need to eat its meal.
 * \return 1 if both forks are available and 
 * doesn't reference to the same mutex, 0 otherwise.
 */
int	ft_are_forks_available(
		pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	if (!right_fork || !left_fork || right_fork == left_fork)
		return (0);
	if (pthread_mutex_unlock(right_fork) == 0
		&& pthread_mutex_unlock(left_fork) == 0)
		return (1);
	return (0);
}
