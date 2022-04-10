/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:31:41 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/10 17:09:52 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_t	**ft_init_thread_array(int nb)
{
	int			i;
	pthread_t	**thread_array;

	if (nb <= 0)
		return (NULL);
	i = 0;
	thread_array = (pthread_t **)ft_calloc(nb + 1, sizeof(pthread_t *));
	while (i < nb)
	{
		thread_array[i] = (pthread_t *)ft_calloc(1, sizeof(pthread_t));
		i++;
	}
	return (thread_array);
}

void	ft_create_threads(t_global *global, pthread_t **thread_array)
{
	t_philo_list	*current_philo;
	int				i;

	current_philo = *global->philo;
	i = 0;
	while (i < global->nb_philo)
	{
		if (pthread_create(thread_array[i], NULL,
				ft_routine, (void *)global) != 0)
			printf("Something went wrong with thread %d\n", (current_philo)->id);
		usleep(1);
		current_philo = current_philo->next;
		*global->philo = current_philo;
		i++;
	}
}

void	ft_destroy_thread_array(pthread_t **thread_array)
{
	int	i;

	i = 0;
	if (!thread_array)
		return ;
	while (thread_array[i])
	{
		pthread_detach(*thread_array[i]);
		free(thread_array[i]);
		i++;
	}
	free(thread_array);
}
