/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:12:48 by yowazga           #+#    #+#             */
/*   Updated: 2023/04/10 14:09:49 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num_must_eat(t_philo *philo)
{
	int	check;
	int	i;

	i = -1;
	check = 1;
	if (philo->args->num_must_eat == -1)
		return (0);
	while (++i < philo->args->num_philo)
		if (checkvalue(&philo[i].total_eat, &philo[i].eat)
			< philo->args->num_must_eat)
			check = 0;
	if (check)
	{
		pthread_mutex_lock(&philo->args->check_dead);
		philo->args->check = 1;
		pthread_mutex_unlock(&philo->args->check_dead);
		return (1);
	}
	return (0);
}

void	*death(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->check_dead);
	philo->args->check = 1;
	pthread_mutex_unlock(&philo->args->check_dead);
	pthread_mutex_lock(&philo->args->print);
	printf("%ld %d died\n", get_curent_time(philo->args->start_time), philo->id);
	if (philo->args->num_philo == 1)
		pthread_mutex_unlock(&philo->args->fork[0]);
	pthread_mutex_unlock(&philo->args->print);
	return (0);
}

void	*check_threads(t_philo *philo)
{
	int		i;
	long	time;

	while (1)
	{
		i = -1;
		while (++i < philo->args->num_philo)
		{
			time = get_curent_time(philo->args->start_time);
			if (time - checkvalue(&philo[i].last_eat, &philo[i].eat)
				>= philo->args->time_to_die)
				return (death(&philo[i]));
			if (num_must_eat(philo))
				return (0);
		}
	}
	return (0);
}

void	destroy_allocation(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < philo->args->num_philo)
	{
		pthread_mutex_destroy(&philo[i].eat);
		pthread_mutex_destroy(&args->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&args->print);
	pthread_mutex_destroy(&args->check_dead);
	free(args->fork);
	free(philo);
}
