/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:26:24 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/10 15:04:14 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file philosopher.h
 * \brief The header of philosopher project.
 */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

/**
 * \struct s_timeval
 * \brief Strcuture is nessecerary for gettimeofday
 * \var s_timeval::tv_sec 
 * A time_t number in which 
 * we held the number of seconds spent from the 1st January 1970.
 * \var s_timeval::tv_usec
 * A suseconds_t number in which 
 * we held the micro-seconds spent since the last iteratiof tv_sec.
 */
typedef struct s_timeval
{
	time_t			tv_sec;
	suseconds_t		tv_usec;
}		t_timeval;

/**
 * \struct s_philo_list
 * \brief This structure contains the property 
 * of a philosopher as a node of a double circular linked list.
 * \var s_philo_list::id 
 * The identifier of our philosopher.
 * \var s_philo_list::time_of_last_meal_in_ms
 * A inting value containing the last 
 * meal timestamp of this philosopher.
 * \var s_philo_list::thread
 * A pointer containing the address of the 
 * thread related to this philosopher node.
 * \var s_philo_list::next
 * A pointer to the next node of our list.
 * \var s_philo_list::previous
 * A pointer to the previous node of our list.
 * \var s_philo_list::fork
 * Contains the address of a mutex 
 * (representing the fork the philosopher is created with).
 */
typedef struct s_philo_list
{
	int					id;
	int				time_of_last_meal_in_ms;
	int					eat_counter;
	struct s_philo_list	*next;
	struct s_philo_list	*previous;
	pthread_mutex_t		*fork;
}	t_philo_list;

/*
 * Stores in one place philo structure and timestamp
 * to be pass to routine in pthread_create.
 */
typedef struct s_global
{
	t_timeval		*start_time;
	t_philo_list	**philo;
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	int			total_meals;
	pthread_mutex_t		*mutex_message;
}	t_global;

/*	timestamp	*/
int					ft_timestamp(t_timeval *start_time);
t_global				*ft_init_global(t_timeval *start_time, char **argv);
/*	check_args.c	*/
int						ft_are_args_correct(int argc, char **argv);

/* 	libft_utils.c		*/
int						ft_isdigit(int c);
int						ft_isspace(int c);
int						ft_issign(char c);
int						ft_atoi(char *nptr);

/*	libft_utils2.c	*/
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);

/*	philo_list.c	*/
t_philo_list			*ft_new_philo(int id);
void					ft_destroy_philo(t_philo_list *addr_philo);
t_philo_list			*ft_lstlast(t_philo_list *list);
void					ft_lstadd_back(t_philo_list **alst, t_philo_list *new);
void					ft_lstclear(t_philo_list **list);

/*	routine.c	*/
void					*ft_routine(void *global);

/*	routine2.c	*/
int	ft_take_forks(t_global *global,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, t_philo_list *philo);
void	ft_clean_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);
void	ft_eat(t_global *global, t_philo_list *philo);
void	ft_sleep(t_global *global, t_philo_list *philo);
void	ft_think(t_global *global, t_philo_list *philo);


/*	death_handler.c	*/
int						ft_is_too_late(t_global *global);
int					ft_is_alive(t_global *global, t_philo_list *philo);

/*	philosophers_handler.c	*/
void					ft_philo_eats_or_thinks(t_global *global);
int						ft_have_all_philo_eaten_enough(t_global *global);
void					ft_philosopher_handler(
							t_timeval *start_time, char **argv);
/*	message.c	*/
void					ft_display_message(pthread_mutex_t *mutex_message, int timpestamp,
							int philo_id, int message);
#endif






