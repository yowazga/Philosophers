/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:47:34 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/08 17:08:44 by yowazga          ###   ########.fr       */
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
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <limits.h>

/*******************************************************************/
/*                            STRUCTS                              */
/*******************************************************************/

typedef struct s_philo
{
	int			nphilo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_must_eat;
	long		start_time;
	int			id;
	long		total_eat;
	long		last_eat;
	sem_t		*sem_fork;
	sem_t		*sem_print;
	sem_t		*sem_death;
	pthread_t	thread;
}	t_philo;

/*******************************************************************/
/*                          FUNCTIONS                              */
/*******************************************************************/

/*   		utils function			*/

int		ft_atoi(char *str);
long	get_curent_time(long time);
void	perfect_usleep(long time);
void	check_philo_dead(t_philo *philo);
void	kill_processes(t_philo *philo, pid_t *pids);

/*   		action function			*/

void	tack_fork(t_philo *philo);
void	start_eating(t_philo *philo);
void	start_sleeping(t_philo *philo);
void	start_thinking(t_philo *philo);
void	reles_semaphor(t_philo *philo);

#endif