/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:52:51 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/29 13:52:58 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_params_helper(t_info *info, int argc, char **argv)
{
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
	return (1);
}

static int	check_params(t_info *info, int argc, char **argv)
{
	info->num_of_philo = atoi(argv[1]);
	info->time_to_die = atoi(argv[2]);
	info->time_to_eat = atoi(argv[3]);
	info->time_to_sleep = atoi(argv[4]);
	if (!info->num_of_philo && !info->time_to_die
		&& !info->time_to_eat && !info->time_to_sleep)
		return (0);
	if (!check_params_helper(info, argc, argv))
		return (1);
	if (info->num_of_philo < 1 || info->time_to_die < 1
		|| info->time_to_eat < 1 || info->time_to_sleep < 1)
	{
		error(1);
		return (0);
	}
	info->alive = 1;
	info->must_eat = 0;
	return (1);
}

static void	malloc_info(t_info *info)
{
	info->philos = malloc(sizeof(t_philo) * info->num_of_philo);
	if (!info->philos)
	{
		error(3);
		return ;
	}
	sem_unlink("/fork");
	sem_unlink("/logs");
	sem_unlink("/eating");
	sem_unlink("/ending");
	info->fork = sem_open("/fork", O_CREAT | O_EXCL, 7777, info->num_of_philo);
	info->logs = sem_open("/logs", O_CREAT | O_EXCL, 7777, 1);
	info->eating = sem_open("/eating", O_CREAT | O_EXCL, 777, 1);
	info->ending = sem_open("/ending", O_CREAT | O_EXCL, 777, 0);
	if (info->fork <= 0 || info->logs <= 0
		|| info->eating <= 0 || info->ending <= 0)
	{
		error(6);
		return ;
	}
}

int	init_philo(t_info *info, int argc, char **argv)
{
	int	i;

	if (!check_params(info, argc, argv))
		return (0);
	malloc_info(info);
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].index = i;
		info->philos[i].info = info;
		info->philos[i].eat = 0;
		info->philos[i].last_eat = philo_get_time();
		i++;
	}
	return (1);
}
