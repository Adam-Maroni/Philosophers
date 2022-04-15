/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:01:02 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/15 11:55:56 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * \fn void	ft_display_message(pthread_mutex_t *mutex_message,
	int timpestamp, int philo_id, int message)
 * \brief This function will decice which message we would display.
*/
void	ft_display_message(pthread_mutex_t *mutex_message,
			int timpestamp, int philo_id, int message)
{
	if (!mutex_message)
		return ;
	pthread_mutex_lock(mutex_message);
	printf("%d %d ", timpestamp, philo_id);
	if (message == 0)
		printf("is eating\n");
	else if (message == 1)
		printf("is sleeping\n");
	else if (message == 2)
		printf("is thinking\n");
	else if (message == 3)
		printf("died\n");
	else if (message == 4)
		printf("has taken a fork\n");
	pthread_mutex_unlock(mutex_message);
}
