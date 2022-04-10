/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:23:49 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/10 15:36:40 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_timestamp(t_timeval *start_time)
{
	int			start_time_in_us;
	int			current_time_in_us;
	int			timestamp_in_ms;
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
