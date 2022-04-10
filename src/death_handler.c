/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:29:44 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/10 11:59:15 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file death_handler.c
 * \brief Contains required functions to handle the death of a philosopher.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

int ft_is_alive(t_global *global, t_philo_list *philo)
{
	if (ft_timestamp(global->start_time) - philo->time_of_last_meal_in_ms
			< global->time_to_die)
		return (1);
	return (0);
}

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
	ft_display_message(global->mutex_message, ft_timestamp(global->start_time),philo_next->id, 3);
	return (1);
}
