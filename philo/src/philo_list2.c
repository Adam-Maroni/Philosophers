/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:34:32 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/10 15:34:42 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo_list	**ft_lstinit(t_global *global)
{
	int				i;
	t_philo_list	*philo;
	t_philo_list	**rt;

	i = 0;
	philo = NULL;
	rt = NULL;
	if (!global)
		ft_exit(global, NULL);
	rt = (t_philo_list **)ft_calloc(1, sizeof(t_philo_list *));
	if (!rt)
		ft_exit(global, NULL);
	while (++i <= global->nb_philo)
	{
		philo = ft_new_philo(i);
		if (philo)
			ft_lstadd_back(rt, philo);
		else
			ft_exit(global, NULL);
	}
	return (rt);
}
