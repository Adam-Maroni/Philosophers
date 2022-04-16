/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:32:44 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/16 11:18:06 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * \file quit.c
 * \brief This file contains the functions we use to check 
 * if the simulation is over and the function to exit 
 * from the simulation the cleanest way possible.
 */

/** 
 * \fn int	ft_have_all_philo_eaten_enough(t_philo_list *philo, char **argv)
 *  \brief This function go through philo_list and check if 
 *  they have reached number_of_times_each_philosopher_must_eat. 
 *  In case this parameter is not specified, 
 *  this function always return 0.
 *  \param philo : Address of philosophers list.
 *  \param argv : Table of string in which are stored the input arguments.
 *  \return 1 if they have, 0 if they have not.
 */
int	ft_have_all_philo_eaten_enough(t_global *global)
{
	int	rt;

	if (!global
		|| !global->number_of_times_each_philosopher_must_eat
		|| !global->nb_philo)
		return (0);
	pthread_mutex_lock(global->mutex_message);
	if (global->total_meals >= global->nb_philo
		* global->number_of_times_each_philosopher_must_eat)
		rt = 1;
	else
		rt = 0;
	pthread_mutex_unlock(global->mutex_message);
	return (rt);
}

/**
 * \fn t_philo_list	**ft_lstinit(t_global *global)
 * \brief This function ensure to free all alocated data and then exit cleanly.
 */
void	ft_exit(t_global *global, pthread_t **thread_array)
{
	if (!global)
		exit(1);
	pthread_mutex_lock(global->mutex_message);
	if (thread_array)
		ft_destroy_thread_array(thread_array);
	ft_lstclear(global->philo);
	free(global->philo);
	pthread_mutex_unlock(global->mutex_message);
	pthread_mutex_destroy(global->mutex_message);
	free(global->mutex_message);
	global->mutex_message = NULL;
	free(global);
	global = NULL;
	exit(0);
}

/**
 * \fn int	ft_is_alive(t_global *global, t_philo_list *philo)
 * \brief This function checks if a philosophers are alive.
 * \param The philosopher wchich we want to check if is alive.
 * \param global The global structure.
 * \return 1 if philosopher is alive and 0 otherwise.
 */
int	ft_is_alive(t_global *global, t_philo_list *philo)
{
	int	rt;

	pthread_mutex_lock(global->mutex_message);
	if (ft_timestamp(global->start_time) - philo->time_of_last_meal_in_ms
		< global->time_to_die)
		rt = 1;
	else
		rt = 0;
	pthread_mutex_unlock(global->mutex_message);
	return (rt);
}

/**
 * \fn int	ft_is_too_late(t_global *global)
 * \brief Check if one philosopher among the list died.
 * \return 0 They are all alive, 1 at least one philo is dead.
 */
int	ft_is_too_late(t_global *global)
{
	t_philo_list	*philo;
	t_philo_list	*philo_next;

	if (!global)
		return (-1);
	philo = (*global->philo);
	philo_next = philo->next;
	while (philo_next != philo)
	{
		if (ft_is_alive(global, philo_next))
			return (0);
		else
			break ;
		philo_next = philo_next->next;
	}
	if (ft_is_alive(global, philo_next))
		return (0);
	ft_display_message(global->mutex_message,
		ft_timestamp(global->start_time), philo_next->id, 3);
	return (1);
}
