/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_func_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:48:00 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/29 13:48:02 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_take_forks(t_philo	*philo, t_info	*info)
{
	sem_wait(info->fork);
	sem_wait(info->logs);
	printf("%lld %d has taken a fork\n",
		(philo_get_time() - info->start_time),
		philo->index + 1);
	sem_post(info->logs);
	sem_wait(info->fork);
	sem_wait(info->logs);
	printf("%lld %d has taken a fork\n",
		(philo_get_time() - info->start_time),
		philo->index + 1);
	sem_post(info->logs);
}

void	philo_eat(t_philo	*philo, t_info	*info)
{
	long long	current_time;

	sem_wait(info->logs);
	printf("%lld %d is eating\n",
		(philo_get_time() - info->start_time),
		philo->index + 1);
	sem_post(info->logs);
	sem_wait(info->eating);
	philo->eat++;
	philo->last_eat = philo_get_time();
	sem_post(info->eating);
	current_time = philo_get_time();
	while (philo_get_time() - current_time < info->time_to_eat)
		usleep(500);
	sem_post(info->fork);
	sem_post(info->fork);
}

void	philo_think(t_philo	*philo, t_info	*info)
{
	long long	current_time;

	sem_wait(info->logs);
	printf("%lld %d is sleeping\n",
		(philo_get_time() - info->start_time),
		philo->index + 1);
	sem_post(info->logs);
	current_time = philo_get_time();
	while (philo_get_time() - current_time < info->time_to_sleep)
		usleep(500);
	sem_wait(info->logs);
	printf("%lld %d is thinking\n",
		(philo_get_time() - info->start_time),
		philo->index + 1);
	sem_post(info->logs);
	usleep(100);
}
