/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:06:02 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/10 16:10:38 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file check_args.c
 * \brief Checks if input arguments are correct.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

/**
 * \fn int	ft_are_args_correct(int argc, char **argv)
 * \brief This function ensure that the arguments 
 * pass as input inside program are valid.
 */
int	ft_are_args_correct(int argc, char **argv)
{
	int	i;
	int	y;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (++i < argc)
	{
		y = 0;
		while (argv[i][y])
			if (!ft_isdigit(argv[i][y]))
				return (0);
		else
			y++;
	}
	return (1);
}
