/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:12:41 by yowazga           #+#    #+#             */
/*   Updated: 2023/04/10 14:09:11 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tack_fork(t_philo *philo)
{
	int	neighbor_fork;

	neighbor_fork = philo->id - 1;
	pthread_mutex_lock(&philo->args->fork[neighbor_fork]);
	pthread_mutex_lock(&philo->args->print);
	if (!checkvalue(&philo->args->check, &philo->args->check_dead))
		printf("%ld %d has taken a fork\n",
			get_curent_time(philo->args->start_time), philo->id);
	pthread_mutex_unlock(&philo->args->print);
	pthread_mutex_lock(&philo->args->fork[philo->id % philo->args->num_philo]);
	pthread_mutex_lock(&philo->args->print);
	if (!checkvalue(&philo->args->check, &philo->args->check_dead))
		printf("%ld %d has taken a fork\n",
			get_curent_time(philo->args->start_time), philo->id);
	pthread_mutex_unlock(&philo->args->print);
}

void	start_eating(t_philo *philo)
{
	int	neighbor_fork;

	neighbor_fork = philo->id - 1;
	pthread_mutex_lock(&philo->eat);
	philo->total_eat += 1;
	pthread_mutex_lock(&philo->args->print);
	if (!checkvalue(&philo->args->check, &philo->args->check_dead))
		printf("%ld %d is eating\n",
			get_curent_time(philo->args->start_time), philo->id);
	pthread_mutex_unlock(&philo->args->print);
	philo->last_eat = get_curent_time(philo->args->start_time);
	pthread_mutex_unlock(&philo->eat);
	if (!checkvalue(&philo->args->check, &philo->args->check_dead))
		perfect_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->args->fork[neighbor_fork]);
	pthread_mutex_unlock(&philo->args->fork[philo->id
		% philo->args->num_philo]);
}

void	start_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print);
	if (!checkvalue(&philo->args->check, &philo->args->check_dead))
		printf("%ld %d is sleeping\n",
			get_curent_time(philo->args->start_time), philo->id);
	pthread_mutex_unlock(&philo->args->print);
	if (!checkvalue(&philo->args->check, &philo->args->check_dead))
		perfect_usleep(philo->args->time_to_sleep);
}

void	start_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print);
	if (!checkvalue(&philo->args->check, &philo->args->check_dead))
		printf("%ld %d is thinking\n",
			get_curent_time(philo->args->start_time), philo->id);
	pthread_mutex_unlock(&philo->args->print);
}
