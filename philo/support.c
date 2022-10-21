/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:55:10 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/21 13:55:12 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_live(t_philo	*tmp_philo)
{
	int	i;
	int	eating_times;

	i = 0;
	eating_times = tmp_philo->info->num_of_eating_times;
	if (tmp_philo->alive == 0)
	{
		return (0);
	}
	if (tmp_philo->eat >= eating_times && eating_times != -1)
	{
		return (0);
	}
	return (1);
}

static int	check_die(t_philo *philos, int num_of_philo)
{
	int	i;
	int	eating_times;

	eating_times = philos->info->num_of_eating_times;
	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_lock(&philos->info->eat);
		if (philos[i].alive == 0)
		{
			pthread_mutex_unlock(&philos->info->eat);
			return (0);
		}
		if (eating_times != -1 && philos->eat >= eating_times)
		{
			pthread_mutex_unlock(&philos->info->eat);
			return (0);
		}
		pthread_mutex_unlock(&philos->info->eat);
		i++;
	}
	return (1);
}

static void	ft_clean(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
		pthread_join(info->philosophers[i], NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->philo_check);
	free(info->forks);
	free(info->philos);
	free(info->philosophers);
	pthread_mutex_destroy(&info->logs);
}

static void	check_death_helper(t_info	*info, int i)
{
	pthread_mutex_lock(&info->philo_check);
	info->philos[i].alive = 0;
	info->checking = 0;
	pthread_mutex_unlock(&info->philo_check);
	pthread_mutex_lock(&info->logs);
	printf("%lld %d died\n",
		(philo_get_time() - info->start_time),
		info->philos->index + 1);
	pthread_mutex_unlock(&info->logs);
	ft_clean(info);
}

void	check_death(t_info	*info)
{
	int			i;
	long long	time_to_die;

	while (check_die(info->philos, info->num_of_philo))
	{
		i = 0;
		while (i < info->num_of_philo
			&& check_die(info->philos, info->num_of_philo))
		{
			pthread_mutex_lock(&info->logs);
			time_to_die = (philo_get_time() - info->philos[i].last_eat);
			pthread_mutex_unlock(&info->logs);
			if (time_to_die > info->time_to_die)
			{
				check_death_helper(info, i);
				return ;
			}
			i++;
		}
	}
	ft_clean(info);
}
