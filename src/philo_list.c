/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:54:30 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/09 16:13:30 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** \file philo_list.c
 * This file contains the code to handle circular double linked list.\n
 * Each node of this list is a philosopher.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

/**
 * \fn t_philo_list	*ft_new_philo(int id)
 * \brief Create a new philosopher node and return its address.
 * \param id An integer we use to identify the philosopher among others.\n
 * When launch, our programm stored into 
 * a timeval structure the start execution time.
 * \return a new philosopher node.
 */
t_philo_list	*ft_new_philo(int id)
{
	t_philo_list	*rt;

	rt = (t_philo_list *)ft_calloc(1, sizeof(t_philo_list));
	rt->thread = (pthread_t *)ft_calloc(1, sizeof(pthread_t));
	rt->fork = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (!rt || !rt->thread || ! rt->fork)
	{
		ft_destroy_philo(rt);
		return (NULL);
	}
	pthread_mutex_init(rt->fork, NULL);
	rt->id = id;
	rt->isavailable = 1;
	rt->next = rt;
	rt->previous = rt;
	rt->time_of_last_meal_in_ms = 0;
	rt->eat_counter = 0;
	return (rt);
}

/** \fn ft_destroy_philo(t_philo_list *addr_philo)
 *  \brief Destroy a node of philosopher list.
 *  \param addr_philo :The address of the node we desire to clear.
 */
void	ft_destroy_philo(t_philo_list *addr_philo)
{
	if (!addr_philo)
		return ;
	if ((addr_philo)->thread)
	{
		pthread_detach(*(addr_philo)->thread);
		free((addr_philo)->thread);
	}
	if ((addr_philo)->fork)
		free(addr_philo->fork);
	(addr_philo)->thread = NULL;
	(addr_philo)->fork = NULL;
	(addr_philo)->id = 0;
	(addr_philo)->next->previous = addr_philo->previous;
	(addr_philo)->previous->next = addr_philo->next;
	free(addr_philo);
}

/** \fn *ft_lstlast (t_philo_list *first_element)
 *  \brief Go through the circular double 
 *  linked list and identify the last element.
 *  \param first_element : The address of the first element of that list.
 *  \return The address of the last element of that list.
 */
t_philo_list	*ft_lstlast(t_philo_list *first_element)
{
	t_philo_list	*current;

	if (first_element == NULL)
		return (NULL);
	current = first_element->next;
	while (current->next != first_element)
		current = current->next;
	return (current);
}

/** \fn *ft_lstlast(t_philo_list *first_element)
 *  \brief Go through the circular double linked list 
 *  and identify the last element.
 *  \param first_element : The address of the first element of that list.
 *  \return The address of the last element of that list.
 */
void	ft_lstadd_back(t_philo_list **alst, t_philo_list *new)
{
	t_philo_list	*last;

	last = ft_lstlast(*alst);
	if (!last)
		*alst = new;
	else
	{
		new->next = last->next;
		new->previous = last;
		last->next->previous = new;
		last->next = new;
	}
}

void	ft_lstclear(t_philo_list **list)
{
	t_philo_list	*current;
	t_philo_list	*next;
	t_philo_list	*previous;

	if (!list || !*list)
		return ;
	current = *list;
	next = (*list)->next;
	while (next != current)
	{
		previous = next;
		next = next->next;
		ft_destroy_philo(previous);
	}
	ft_destroy_philo(*list);
	(*list) = NULL;
}
