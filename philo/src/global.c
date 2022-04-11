/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:35:57 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/11 17:27:12 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * \fn t_global	*ft_init_global(
	t_timeval *start_time, char **argv)
 * \brief This function create a global structure 
 * which will contains the data we use through our algorithm.
 * \param time_stamp corresponding to the begining of the simulation.
 */
t_global	*ft_init_global(
		t_timeval *start_time, char **argv)
{
	t_global	*rt;

	if (!start_time || !argv)
		return (NULL);
	rt = (t_global *)ft_calloc(1, sizeof(t_global));
	if (!rt)
		return (NULL);
	rt->start_time = start_time;
	rt->nb_philo = ft_atoi(argv[1]);
	rt->time_to_die = (int)ft_atoi(argv[2]);
	rt->time_to_eat = (int)ft_atoi(argv[3]);
	rt->time_to_sleep = (int)ft_atoi(argv[4]);
	rt->total_meals = 0;
	if (argv[5])
		rt->number_of_times_each_philosopher_must_eat = (int)ft_atoi(argv[5]);
	else
		rt->number_of_times_each_philosopher_must_eat = 0;
	return (rt);
}
