/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:29:00 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/08 15:36:45 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(char **av, int ac, t_args *args)
{
	args->num_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->num_must_eat = -1;
	if (ac == 6)
	{
		args->num_must_eat = ft_atoi(av[5]);
		if (args->num_must_eat <= 0)
			return (-42);
	}
	if (args->num_philo < 1 || args->num_philo > 200 || args->time_to_die < 60
		|| args->time_to_eat < 60 || args->time_to_sleep < 60)
		return (-42);
	args->check = 0;
	args->start_time = get_curent_time(0);
	return (0);
}

int	init_philosophers(t_args *args, t_philo *philo)
{
	int	i;

	i = 0;
	args->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* args->num_philo);
	if (!args->fork)
	{
		free(philo);
		return (print_error("error malloc"));
	}
	args->start_time = get_curent_time(0);
	while (i < args->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_eat = get_curent_time(args->start_time);
		philo[i].total_eat = 0;
		philo[i].args = args;
		pthread_mutex_init(&philo[i].eat, NULL);
		pthread_mutex_init(&args->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->print, NULL);
	pthread_mutex_init(&args->check_dead, NULL);
	return (0);
}

void	*action_philo(void *single_philo)
{
	t_philo	*philo;

	philo = (t_philo *)single_philo;
	while (1)
	{
		if (checkvalue(&philo->args->check, &philo->args->check_dead))
			break ;
		start_thinking(philo);
		tack_fork(philo);
		start_eating(philo);
		start_sleeping(philo);
	}
	return (0);
}

int	start_philosophers(t_args args, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args.num_philo)
	{
		pthread_create(&philo[i].philo, NULL, action_philo, &philo[i]);
		usleep(60);
		i += 2;
	}
	i = 1;
	while (i < args.num_philo)
	{
		pthread_create(&philo[i].philo, NULL, action_philo, &philo[i]);
		usleep(60);
		i += 2;
	}
	check_threads(philo);
	i = 0;
	while (i < args.num_philo)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	*philo;
	t_args	args;

	if (ac < 5 || ac > 6 || init_args(av, ac, &args) < 0)
		return (print_error("invalid arguments"));
	philo = (t_philo *)malloc(sizeof(t_philo) * args.num_philo);
	if (!philo)
		return (-42);
	if (init_philosophers(&args, philo) < 0)
		return (-42);
	start_philosophers(args, philo);
	destroy_allocation(philo, &args);
}
