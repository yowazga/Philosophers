/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:47:30 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/08 16:57:57 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(int ac, char **av, t_philo *philo)
{
	philo->nphilo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->num_must_eat = -1;
	philo->id = 0;
	if (ac == 6)
	{
		philo->num_must_eat = ft_atoi(av[5]);
		if (philo->num_must_eat <= 0)
			return (-42);
	}
	if (philo->nphilo < 1 || philo->nphilo > 200 || philo->time_to_die < 60
		|| philo->time_to_eat < 60 || philo->time_to_sleep < 60)
		return (-42);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_death");
	philo->sem_fork = sem_open("/sem_fork", O_CREAT
			| O_EXCL, 0644, philo->nphilo);
	philo->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	philo->sem_death = sem_open("/sem_death", O_CREAT | O_EXCL, 0644, 1);
	return (0);
}

void	*action_philo(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (1)
	{
		if (philo->total_eat == philo->num_must_eat)
			exit(0);
		start_thinking(philo);
		tack_fork(philo);
		start_eating(philo);
		start_sleeping(philo);
	}
	return (0);
}

void	philos(t_philo *philo, int id)
{
	philo->id = id;
	philo->total_eat = 0;
	philo->last_eat = get_curent_time(philo->start_time);
	pthread_create(&philo->thread, NULL, action_philo, philo);
	check_philo_dead(philo);
	pthread_join(philo->thread, NULL);
	exit(0);
}

int	init_philosophers(t_philo *philo)
{
	pid_t	*pids;
	int		i;

	i = -1;
	philo->start_time = get_curent_time(0);
	pids = malloc(sizeof(pid_t) * philo->nphilo);
	if (!pids)
		return (-42);
	while (++i < philo->nphilo)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (-42);
		if (pids[i] == 0)
		{
			philo->id = i + 1;
			philos(philo, philo->id);
		}
	}
	kill_processes(philo, pids);
	free (pids);
	reles_semaphor(philo);
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	philo;

	if (ac < 5 || ac > 6 || init_args(ac, av, &philo) < 0)
		return (1);
	if (init_philosophers(&philo) < 0)
		return (2);
}
