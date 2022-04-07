/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:05:18 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/15 11:06:02 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \mainpage Mainpage
 * \version Code: 1.0.0\n Documentation: 1.0 (Code 1.0.0)
 */

/** \file main.c
 * This file contains the main fuction of our code.\n
 * It is the starting point of our program
 * in which we check for the validaty of input arguments.
 * In case they are valid, call for the ft_philosophers_handler function.
 */

/** \headerfile philosopher.h */
#include "philosopher.h"

/**
 * \fn int main(int argc, char **argv)
 * \paramn argc an integer that stores the number of input arguments + 1
 * \paramn argv a string table that stores the inputs
 * arguments as string (as well as the program name).
 * \return 0 if success, 1 otherwise. 
 */
int	main(int argc, char **argv)
{
	t_timeval	start_time;

	if (!ft_are_args_correct(argc, argv))
	{
		printf("Arguments not correct.\n");
		return (1);
	}
	gettimeofday((struct timeval *)&start_time, NULL);
	ft_philosopher_handler(&start_time, argv);
	return (0);
}
