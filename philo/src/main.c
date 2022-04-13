/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:05:18 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/13 11:32:10 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \mainpage Mainpage
 * \version Code: 1.0.0\n Documentation: 1.0 (Code 1.0.0)
 */

/** \file main.c
 * This file contains the main fuction of our code.\n
 * It is the starting point of our program
 * in which we check for the validaty of input arguments.
 * In case they are valid, call for the ft_philosophers_handler function.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

/**
 * \fn int main(int argc, char **argv)
 * \paramn argc an integer that stores the number of input arguments + 1
 * \paramn argv a string table that stores the inputs
 * arguments as string (as well as the program name).
 * \return 0 if success, 1 otherwise. 
 */
int	main(int argc, char **argv)
{
	t_timeval	start_time;

	if (!ft_are_args_correct(argc, argv))
	{
		printf("Arguments not correct.\n");
		return (1);
	}
	gettimeofday((struct timeval *)&start_time, NULL);
	ft_philosopher_handler(&start_time, argv);
	return (0);
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
	global->mutex_message = ft_new_mutex();
	global->mutex_total_meals = ft_new_mutex();
	global->mutex_end = ft_new_mutex();
	global->mutex_create_threads = ft_new_mutex();
	thread_array = ft_init_thread_array(global->nb_philo);
	ft_create_threads(global, thread_array);
	while (1)
		if (ft_have_all_philo_eaten_enough(global) || ft_is_too_late(global))
		{
			pthread_mutex_lock(global->mutex_end);
			global->end = 1;
			pthread_mutex_unlock(global->mutex_end);
			break ;
		}
	ft_wait_for_threads_to_be_done(thread_array);
	ft_exit(global, thread_array);
}
