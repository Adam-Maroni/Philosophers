/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:29:44 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/08 14:27:01 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file death_handler.c
 * \brief Contains required functions to handle the death of a philosopher.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

int	ft_is_too_late(t_global *global, int current_time)
{
	t_philo_list	*philo;
	t_philo_list	*philo_next;

	if (!global)
		return (-1);
	philo = *global->philo;
	philo_next = philo->next;
	while (philo_next != philo)
	{
		if (current_time - philo_next->time_of_last_meal_in_ms
			< global->time_to_die)
			return (0);
		else
			break ;
		philo_next = philo_next->next;
	}
	if (current_time - philo_next->time_of_last_meal_in_ms
		< global->time_to_die)
		return (0);
	printf("%dms %d died\n", current_time, philo_next->id);
	return (1);
}
