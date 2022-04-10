/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:57:14 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/14 18:15:44 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file libft_utils.c
 * \brief This file contains the necessary for ft_atoi.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

int	ft_isdigit(int c)
{
	if (((c >= '0') && (c <= '9')))
		return (2048);
	return (0);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_issign(char c)
{
	if (c == '+')
		return (1);
	else if (c == '-')
		return (-1);
	else
		return (0);
}

int	ft_atoi(char *nptr)
{
	unsigned long	x10;
	int				sign;
	double			rt;

	rt = 0;
	x10 = 1;
	sign = 1;
	while (ft_isspace((int)(*nptr)) != 0)
		nptr++;
	if (ft_issign(*nptr) != 0)
	{
		sign = ft_issign(*nptr);
		nptr++;
	}
	while (ft_isdigit(nptr[(int)(rt++)]) != 0)
		x10 *= 10;
	rt = 0;
	x10 /= 10;
	while (ft_isdigit(*nptr) != 0)
	{
		rt += ((*nptr) - '0') * (x10);
		x10 /= 10;
		nptr++;
	}
	return ((int)(rt)*sign);
}
