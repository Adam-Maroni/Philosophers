/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:29:44 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/07 15:47:07 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file death_handler.c
 * \brief Contains required functions to handle the death of a philosopher.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

/**
 * \fn int ft_is_too_late(int time_of_last_meal_in_ms, t_timeval *current_time)
 * \brief This function compared the time of the last meal 
 * of given philosopher with the current_time.\n
 * In case that difference exceed time_to_die then a interger code 
 * is returned to indicate on the life state of such philosopher 
 * in addtion of an information message.
 * \param philosopher Address of philosopher pointer.
 * \param time_to_die The maximum time between each meal 
 * before the death of a philosopher (in ms).
 * \param current_time The current timestamp of simulation (in ms).
 * \return 1 if the philosopher should die, 0 otherwise.
 */
int	ft_is_too_late(t_philo_list **philo,
		int time_to_die, int current_time)
{
	if (!philo || !*philo)
		return (1);
	if (current_time - (*philo)->time_of_last_meal_in_ms < time_to_die)
		return (0);
	printf("%dms %d died\n", current_time, (*philo)->id);
	if ((*philo)->id != 0)
		(*philo)->id = 0;
	return (1);
}
