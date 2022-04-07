/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:53:28 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/07 12:09:34 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file philosophers_handler.c
 * \brief This file contain the core code of our algorithm.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

/**
 * \fn void ft_philo_eats_or_thinks(t_global *global,
		t_philo_list **philo)
 * \brief This function decide whether a philosopher should eat or think
 * \param global Address of structure containing information 
 * about current philosopher node and time's Constant/variables.
 * \param philo Address of pointer of current philosopher.
 * 
 */
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
	//	pthread_detach(*thread);
		usleep(10);
	}
	else
		ft_display_message(ft_timestamp(global->start_time), philo->id, 2);
}

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
int	ft_have_all_philo_eaten_enough(t_philo_list *philo, char **argv)
{
	t_philo_list	*tmp;

	if (!philo || !argv)
		return (1);
	if (!argv[5])
		return (0);
	tmp = philo->next;
	while (tmp != philo)
		if (tmp->eat_counter < ft_atoi(argv[5]))
			return (0);
	else
		tmp = tmp->next;
	if (tmp->eat_counter < ft_atoi(argv[5]))
		return (0);
	return (1);
}

/** 
 * \fn void	ft_philosopher_handler(t_timeval *start_time, char **argv)
 *  \brief This function create philosophers and manage their life cycle.
 *  \param start_time :  The address of start_time structure.
 *  \param argv : Table of string in which are stored the input arguments.
 */
void	ft_philosopher_handler(t_timeval *start_time, char **argv)
{
	t_global	*global;
	int			nb_philo;
	int			i;

	nb_philo = ft_atoi(argv[1]);
	i = 0;
	global = ft_init_global(start_time, argv);
	while (++i <= nb_philo)
		ft_lstadd_back(global->philo, ft_new_philo(i));
	while (!ft_have_all_philo_eaten_enough(*(global->philo), argv))
	{
		/* if (ft_is_too_late(global->philo, global->time_to_die, */
		/* 		ft_timestamp(global->start_time))) */
		/* 	break ; */
		ft_philo_eats_or_thinks(global);
		*(global->philo) = (*global->philo)->next;
	}
	ft_lstclear(global->philo);
	free(global->philo);
	free(global);
}
