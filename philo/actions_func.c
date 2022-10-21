/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:28:43 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/21 13:28:46 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_take_forks_helper(t_philo	*tmp_philo)
{
	pthread_mutex_lock(tmp_philo->left_fork);
	message(tmp_philo, "has taken a fork", NULL);
	if (tmp_philo->right_fork == tmp_philo->left_fork)
	{
		pthread_mutex_lock(&tmp_philo->info->philo_check);
		tmp_philo->info->checking = 0;
		pthread_mutex_unlock(&tmp_philo->info->philo_check);
		pthread_mutex_unlock(tmp_philo->right_fork);
		return ;
	}
	pthread_mutex_lock(tmp_philo->right_fork);
	message(tmp_philo, "has taken a fork", NULL);
}

void	philo_take_forks(t_philo	*tmp_philo)
{
	if (tmp_philo->index % 2 == 0)
	{
		pthread_mutex_lock(tmp_philo->right_fork);
		message(tmp_philo, "has taken a fork", NULL);
		if (tmp_philo->right_fork == tmp_philo->left_fork)
		{
			pthread_mutex_lock(&tmp_philo->info->philo_check);
			tmp_philo->info->checking = 0;
			pthread_mutex_unlock(&tmp_philo->info->philo_check);
			pthread_mutex_unlock(tmp_philo->right_fork);
			return ;
		}
		pthread_mutex_lock(tmp_philo->left_fork);
		message(tmp_philo, "has taken a fork", NULL);
	}
	else
		philo_take_forks_helper(tmp_philo);
}

void	update_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->eat);
	philo->eat++;
	philo->last_eat = philo_get_time();
	pthread_mutex_unlock(&philo->info->eat);
}

void	philo_eat(t_philo	*tmp_philo)
{
	long long	current_time;

	message(tmp_philo, "is eating", update_eating);
	current_time = philo_get_time();
	while (philo_get_time() - current_time < tmp_philo->info->time_to_eat)
		usleep(500);
	pthread_mutex_unlock(tmp_philo->left_fork);
	pthread_mutex_unlock(tmp_philo->right_fork);
}

void	philo_think(t_philo	*tmp_philo)
{
	long long	current_time;

	message(tmp_philo, "is sleeping", NULL);
	current_time = philo_get_time();
	while (philo_get_time() - current_time < tmp_philo->info->time_to_sleep)
		usleep(500);
	message(tmp_philo, "is thinging", NULL);
	usleep(100);
}
