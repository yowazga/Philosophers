/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:12:44 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/08 15:34:17 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *error)
{
	printf("%s\n", error);
	return (-42);
}

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-42);
		if (res > INT_MAX)
			return (-42);
		res = res * 10 + *str - '0';
		str++;
	}
	return (res);
}

long	checkvalue(long *value, pthread_mutex_t *mtx)
{
	long	retur;

	pthread_mutex_lock(mtx);
	retur = *value;
	pthread_mutex_unlock(mtx);
	return (retur);
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
