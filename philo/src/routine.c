/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:19:07 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/12 17:15:01 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file meals_handler.c
 * \brief Contains functions for philosopher to meal.
*/

/** \headerfile philosopher.h */
#include "philosopher.h"

int	ft_thread_should_stop(t_global *global)
{
	int	end;

	if (!global)
		return (-1);
	if (!global->mutex_end)
		return (0);
	pthread_mutex_lock(global->mutex_end);
	end = global->end;
	pthread_mutex_unlock(global->mutex_end);
	return (end);
}

/**
 * \brief The routine we call through 
 * the function pthread_create for the philosopher to eat.\n
 * This also here we lock and unlock the forks (the mutexes).
 * \param global : A structure containing 
 * both the philospher node and times Constants/Variables.
 */
void	*ft_routine(void *global)
{
	t_philo_list	*philo;
	t_global		*cast;

	cast = (t_global *)(global);
	philo = *(cast->philo);
	while (ft_thread_should_stop(cast) == 0)
	{
		if (ft_take_forks(cast, philo->fork, philo->next->fork, philo) < 1)
			continue ;
		ft_eat(cast, philo);
		ft_clean_forks(philo->fork, philo->next->fork);
		ft_sleep(cast, philo);
		ft_think(cast, philo);
	}
	return (NULL);
}
