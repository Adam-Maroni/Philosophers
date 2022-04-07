/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:13:27 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/15 11:02:45 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file libft_utils2.c
 * \brief This file contains various string handling functions.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)s + i) = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*rt_pointer;

	rt_pointer = (void *)malloc(nmemb * size);
	if (!rt_pointer)
		return (NULL);
	ft_bzero(rt_pointer, nmemb * size);
	return (rt_pointer);
}
