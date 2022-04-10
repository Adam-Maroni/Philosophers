/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:23:49 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/10 11:16:29 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_timestamp(t_timeval *start_time)
{
	int		start_time_in_us;
	int		current_time_in_us;
	int		timestamp_in_ms;
	t_timeval	current_time;

	if (!start_time)
		return (0);
	gettimeofday((struct timeval *)&current_time, NULL);
	start_time_in_us = start_time->tv_usec
		+ (start_time->tv_sec * 1000000);
	current_time_in_us = current_time.tv_usec
		+ (current_time.tv_sec * 1000000);
	timestamp_in_ms = (int)(current_time_in_us - start_time_in_us) / 1000;
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
