/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:01:02 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/13 17:42:12 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * \fn void	ft_display_message(pthread_mutex_t *mutex_message,
	int timpestamp, int philo_id, int message)
 * \brief This function will decice which message we would display.
*/
void	ft_display_message(t_global *global,
			int timpestamp, int philo_id, int message)
{
	int	end;

	pthread_mutex_lock(global->mutex_end);
	end = global->end;
	pthread_mutex_unlock(global->mutex_end);
	if (end && message != 3)
		return ;
	pthread_mutex_lock(global->mutex_message);
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
	if (pthread_mutex_unlock(global->mutex_message))
		printf("Couldn't unlock mutex message, thread: %d\n", philo_id);
}
