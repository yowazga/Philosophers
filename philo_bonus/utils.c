/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:22:47 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/08 16:40:55 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-42);
		res = res * 10 + *str - '0';
		if (res > INT_MAX)
			return (-42);
		str++;
	}
	return (res);
}

long	get_curent_time(long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3 + tv.tv_usec / 1e3) - time);
}

void	perfect_usleep(long time)
{
	long	curent_time;

	curent_time = get_curent_time(0) + time;
	while (get_curent_time(0) < curent_time)
		usleep(200);
}

void	kill_processes(t_philo *philo, pid_t *pids)
{
	int	i;
	int	exit_status;

	i = -1;
	while (++i < philo->nphilo)
	{
		if (waitpid(-1, &exit_status, 0) == -1)
		{
			reles_semaphor(philo);
			free(pids);
			exit(0);
		}
		if (exit_status)
		{
			i = -1;
			while (++i < philo->nphilo)
				kill(pids[i], SIGKILL);
		}
	}
}

void	check_philo_dead(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->sem_death);
		if (get_curent_time(philo->start_time)
			- philo->last_eat >= philo->time_to_die)
		{
			sem_wait(philo->sem_print);
			printf("%ld %d died\n",
				get_curent_time(philo->start_time), philo->id);
			exit(1);
		}
		sem_post(philo->sem_death);
		usleep(100);
	}
}
