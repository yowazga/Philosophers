/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:27:42 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/08 16:57:47 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	reles_semaphor(t_philo *philo)
{
	sem_close(philo->sem_death);
	sem_close(philo->sem_print);
	sem_close(philo->sem_fork);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_death");
}

void	tack_fork(t_philo *philo)
{
	sem_wait(philo->sem_fork);
	sem_wait(philo->sem_print);
	printf("%ld %d has taken a fork\n",
		get_curent_time(philo->start_time), philo->id);
	sem_post(philo->sem_print);
	sem_wait(philo->sem_fork);
	sem_wait(philo->sem_print);
	printf("%ld %d has taken a fork\n",
		get_curent_time(philo->start_time), philo->id);
	sem_post(philo->sem_print);
}

void	start_eating(t_philo *philo)
{
	sem_wait(philo->sem_print);
	printf("%ld %d is eating\n",
		get_curent_time(philo->start_time), philo->id);
	sem_post(philo->sem_print);
	sem_wait(philo->sem_death);
	philo->last_eat = get_curent_time(philo->start_time);
	philo->total_eat += 1;
	sem_post(philo->sem_death);
	perfect_usleep(philo->time_to_eat);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
}

void	start_sleeping(t_philo *philo)
{
	sem_wait(philo->sem_print);
	printf("%ld %d is sleeping\n",
		get_curent_time(philo->start_time), philo->id);
	sem_post(philo->sem_print);
	perfect_usleep(philo->time_to_sleep);
}

void	start_thinking(t_philo *philo)
{
	sem_wait(philo->sem_print);
	printf("%ld %d is thinking\n",
		get_curent_time(philo->start_time), philo->id);
	sem_post(philo->sem_print);
}
