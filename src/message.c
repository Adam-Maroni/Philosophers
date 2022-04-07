/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:01:02 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/05 17:48:03 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_display_message(float timpestamp, int philo_id, int message)
{
	printf("%f: %d ", timpestamp, philo_id);
	if (message == 0)
		printf("is eating\n");
	else if (message == 1)
		printf("is sleeping\n");
	else if (message == 2)
		printf("is thinking\n");
	else if (message == 3)
		printf("has died\n");
	else if (message == 4)
		printf("has taken a fork\n");
	else
		return ;
}
