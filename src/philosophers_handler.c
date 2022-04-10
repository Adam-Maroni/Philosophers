/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:53:28 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/10 15:09:56 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file philosophers_handler.c
 * \brief This file contain the core code of our algorithm.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

void	ft_exit(t_global *global, pthread_t **thread_array)
{
	int i;

	i = 0;
	if (!global)
		exit(1);
	while (thread_array && thread_array[i])
	{
		free(thread_array[i]);
		i++;
	}
	if (thread_array)
		free(thread_array);
	ft_lstclear(global->philo);
	free(global->philo);
	pthread_mutex_destroy(global->mutex_message);
	free(global->mutex_message);
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

void	ft_create_threads(t_global *global, pthread_t **thread_array)
{
	t_philo_list	*current_philo;
	int i;

	current_philo = *global->philo;
	i = 0;
	while (i < global->nb_philo)
	{
		if (pthread_create(thread_array[i], NULL, ft_routine, (void *)global) != 0)
			printf("Something went wrong with thread %d\n", (current_philo)->id);
		usleep(1);
		current_philo = current_philo->next;
		*global->philo = current_philo;
		i++;
	}
}

t_philo_list	**ft_lstinit(t_global *global)
{
	int	i;
	t_philo_list	*philo;
	t_philo_list	**rt;

	i = 0;
	philo = NULL;
	rt = NULL;
	if (!global)
		ft_exit(global, NULL);
	rt = (t_philo_list **)ft_calloc(1, sizeof(t_philo_list *));
	if (!rt)
		ft_exit(global, NULL);
	while (++i <= global->nb_philo)
	{
		philo = ft_new_philo(i);
		if (philo)
			ft_lstadd_back(rt, philo);
		else
			ft_exit(global, NULL);
	}
	return (rt);
}

pthread_t	**ft_init_thread_array(int nb)
{
	int	i;
	pthread_t **thread_array;

	if (nb <= 0)
		return (NULL);
	i = 0;
	thread_array = (pthread_t **)ft_calloc(nb + 1, sizeof(pthread_t *));
	while (i < nb)
	{
		thread_array[i] = (pthread_t *)ft_calloc(1, sizeof(pthread_t));
		i++;
	}
	return (thread_array);
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
	pthread_t		**thread_array;

	global = ft_init_global(start_time, argv);
	global->philo = ft_lstinit(global);
	global->mutex_message = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(global->mutex_message, NULL);
	thread_array = ft_init_thread_array(global->nb_philo);
	ft_create_threads(global, thread_array);
	while (1)
		if (ft_have_all_philo_eaten_enough(global) || ft_is_too_late(global))
			break ;
	ft_exit(global, thread_array);
}

