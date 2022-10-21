/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:34:38 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/21 13:34:39 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_params(t_info *info, int argc, char **argv)
{
	info->num_of_philo = atoi(argv[1]);
	info->time_to_die = atoi(argv[2]);
	info->time_to_eat = atoi(argv[3]);
	info->time_to_sleep = atoi(argv[4]);
	if (!info->num_of_philo && !info->time_to_die
		&& !info->time_to_eat && !info->time_to_sleep)
		return (0);
	if (argc == 6)
	{
		info->num_of_eating_times = atoi(argv[5]);
		if (info->num_of_eating_times < 1)
		{
			error(1);
			return (0);
		}
	}
	else
		info->num_of_eating_times = -1;
	if (info->num_of_philo < 1 || info->time_to_die < 1
		|| info->time_to_eat < 1 || info->time_to_sleep < 1)
	{
		error(1);
		return (0);
	}
	return (1);
}

static void	malloc_info(t_info *info)
{
	info->forks = NULL;
	info->philos = malloc(sizeof(t_philo) * info->num_of_philo);
	info->philosophers = malloc(sizeof(pthread_t) * info->num_of_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->forks || !info->philos || !info->philosophers)
	{
		error(3);
		return ;
	}
	if (pthread_mutex_init(&info->logs, NULL))
	{
		error(4);
		return ;
	}
	if (pthread_mutex_init(&info->philo_check, NULL))
	{
		error(4);
		return ;
	}
	if (pthread_mutex_init(&info->eat, NULL))
	{
		error(4);
		return ;
	}
	info->checking = 1;
}

static int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
		{
			error(4);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philo(t_info *info, int argc, char **argv)
{
	int	i;

	if (!check_params(info, argc, argv))
		return (0);
	malloc_info(info);
	if (!init_mutex(info))
		return (0);
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].index = i;
		info->philos[i].info = info;
		info->philos[i].alive = 1;
		info->philos[i].eat = 0;
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].right_fork = &info->forks[(i + 1) % info->num_of_philo];
		info->philos[i].last_eat = philo_get_time();
		i++;
	}
	return (1);
}
