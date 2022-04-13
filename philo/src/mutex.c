/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:57:28 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/13 11:05:24 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	*ft_new_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (!mutex)
		return (NULL);
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

int	ft_destroy_and_free_mutex(pthread_mutex_t *mutex)
{
	if (!mutex)
		return (-1);
	pthread_mutex_destroy(mutex);
	free(mutex);
	mutex = NULL;
	return (1);
}
