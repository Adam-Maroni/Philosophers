/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:23:49 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/07 11:58:04 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

float	ft_timestamp(t_timeval *start_time)
{
	long		start_time_in_us;
	long		current_time_in_us;
	float		timestamp_in_ms;
	t_timeval	current_time;

	if (!start_time)
		return (0);
	gettimeofday((struct timeval *)&current_time, NULL);
	start_time_in_us = start_time->tv_usec
		+ (start_time->tv_sec * 1000000);
	current_time_in_us = current_time.tv_usec
		+ (current_time.tv_sec * 1000000);
	timestamp_in_ms = (float)(current_time_in_us - start_time_in_us) / 1000;
	return (timestamp_in_ms);
}

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
	rt->philo = (t_philo_list **)ft_calloc(1, sizeof(t_philo_list *));
	rt->time_to_die = (float)ft_atoi(argv[2]);
	rt->time_to_eat = (float)ft_atoi(argv[3]);
	rt->time_to_sleep = (float)ft_atoi(argv[4]);
	if (argv[5])
		rt->number_of_times_each_philosopher_must_eat = (float)ft_atoi(argv[5]);
	else
		rt->number_of_times_each_philosopher_must_eat = 0;
	return (rt);
}
