/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:53:28 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/08 15:13:57 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file philosophers_handler.c
 * \brief This file contain the core code of our algorithm.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

void	ft_exit(t_global *global)
{
	if (!global)
		exit(1);
	ft_lstclear(global->philo);
	free(global->philo);
	free(global);
	exit(0);
}

/**
 * \fn void ft_philo_eats_or_thinks(t_global *global)
 * \brief This function decide whether a philosopher should eat or think
 * \param global Address of structure containing information 
 * about current philosopher node and time's Constant/variables.
 * \param philo Address of pointer of current philosopher.
 * 
void	ft_philo_eats_or_thinks(t_global *global)
{
	t_philo_list	*philo;
	pthread_t		*thread;
	if (!global)
		return ;
	philo = *global->philo;
	thread = philo->thread;
	if (!philo->isavailable)
		return ;
	if (ft_are_forks_available(philo->fork, philo->next->fork))
	{
		pthread_create(thread, NULL, ft_routine, (void *)global);
		pthread_detach(*thread);
		usleep(10);
	}
	else
		ft_display_message(ft_timestamp(global->start_time), philo->id, 2);
}
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
	if (!global
		|| !global->number_of_times_each_philosopher_must_eat
		|| !global->nb_philo)
		return (0);
	if (global->total_meals >= global->nb_philo
		* global->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

void	ft_create_threads(t_global *global, int pair)
{
	t_philo_list	*philo;
	t_philo_list	*last;

	philo = *global->philo;
	last = ft_lstlast(*global->philo);
	while (philo != last)
	{
		if (pair && philo->id % 2 == 0)
			pthread_create(philo->thread, NULL, ft_routine, (void *)global);
		else if (!pair && philo->id % 2 == 1)
			pthread_create(philo->thread, NULL, ft_routine, (void *)global);
		philo = philo->next;
	}
	if (pair && philo->id % 2 == 0)
		pthread_create(philo->thread, NULL, ft_routine, (void *)global);
	else if (!pair && philo->id % 2 == 1)
		pthread_create(philo->thread, NULL, ft_routine, (void *)global);
}

/** 
 * \fn void	ft_philosopher_handler(t_timeval *start_time, char **argv)
 *  \brief This function create philosophers and manage their life cycle.
 *  \param start_time :  The address of start_time structure.
 *  \param argv : Table of string in which are stored the input arguments.
 */
void	ft_philosopher_handler(t_timeval *start_time, char **argv)
{
	t_global		*global;
	int				i;
	t_philo_list	*philo;

	i = 0;
	global = ft_init_global(start_time, argv);
	if (!global)
		return ;
	while (++i <= global->nb_philo)
	{
		philo = ft_new_philo(i);
		if (philo)
			ft_lstadd_back(global->philo, philo);
		else
			ft_exit(global);
	}
	ft_create_threads(global, 1);
	ft_create_threads(global, 0);
	while (1)
		if (ft_have_all_philo_eaten_enough(global)
			|| ft_is_too_late(global, ft_timestamp(global->start_time)))
			break ;
	ft_exit(global);
}
