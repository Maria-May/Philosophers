/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:39:37 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/21 13:39:40 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_working(void	*philo)
{
	t_philo	*tmp_philo;

	tmp_philo = (t_philo *)philo;
	while (is_philo_live(tmp_philo))
	{
		pthread_mutex_lock(&tmp_philo->info->philo_check);
		if (!tmp_philo->info->checking)
		{
			pthread_mutex_unlock(&tmp_philo->info->philo_check);
			return (NULL);
		}
		pthread_mutex_unlock(&tmp_philo->info->philo_check);
		philo_take_forks(tmp_philo);
		philo_eat(tmp_philo);
		philo_think(tmp_philo);
	}
	return (NULL);
}

static void	philo_start(t_info	*info)
{
	int	i;

	i = 0;
	info->start_time = philo_get_time();
	while (i < info->num_of_philo)
	{
		if (pthread_create(&info->philosophers[i],
				NULL, &philo_working, &info->philos[i]))
		{
			error(2);
			return ;
		}
		usleep(50);
		i++;
	}
	check_death(info);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
	{
		error(1);
		return (0);
	}
	if (!init_philo(&info, argc, argv))
		return (0);
	philo_start(&info);
}
