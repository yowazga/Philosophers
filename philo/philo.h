/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:29:35 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/08 17:07:45 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*******************************************************************/
/*                           INCLUDES                              */
/*******************************************************************/

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*******************************************************************/
/*                            STRUCTS                              */
/*******************************************************************/

typedef struct s_args
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	long			start_time;
	long			check;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	check_dead;
}	t_args;

typedef struct s_philo
{
	int				id;
	long			total_eat;
	long			last_eat;
	pthread_mutex_t	eat;
	pthread_t		philo;
	t_args			*args;
}	t_philo;

/*******************************************************************/
/*                          FUNCTIONS                              */
/*******************************************************************/

/*   		utils function			*/

int		print_error(char *error);
long	get_curent_time(long time);
int		ft_atoi(char *str);
void	perfect_usleep(long time);
long	checkvalue(long *val, pthread_mutex_t *mtx);

/*      	  function check	   	*/

void	*check_threads(t_philo *philo);
void	destroy_allocation(t_philo *philo, t_args *args);

/*   		action function			*/

void	tack_fork(t_philo *philo);
void	start_eating(t_philo *philo);
void	start_sleeping(t_philo *philo);
void	start_thinking(t_philo *philo);

#endif