/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:12:13 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/29 14:12:15 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_working(t_philo	*philo, t_info	*info)
{
	while (1)
	{
		philo_take_forks(philo, info);
		philo_eat(philo, info);
		if (philo->eat >= info->num_of_eating_times
			&& info->num_of_eating_times != -1)
			exit(0);
		philo_think(philo, info);
	}
}

void	check_death_helper(t_info *tmp_info, t_philo *tmp_philo,
	long long time_to_die)
{
	if (time_to_die > tmp_info->time_to_die)
	{
		sem_post(tmp_info->eating);
		sem_wait(tmp_info->logs);
		tmp_info->alive = 0;
		printf("%lld %d died\n",
			(philo_get_time() - tmp_info->start_time),
			tmp_info->philos->index + 1);
		exit(1);
	}
}

static void	*check_death(void	*philo)
{
	t_info		*tmp_info;
	t_philo		*tmp_philo;
	long long	time_to_die;
	int			eating_times;

	tmp_philo = (t_philo *)philo;
	tmp_info = tmp_philo->info;
	eating_times = tmp_philo->info->num_of_eating_times;
	while (1)
	{
		sem_wait(tmp_info->eating);
		time_to_die = (philo_get_time() - tmp_philo->last_eat);
		check_death_helper(tmp_info, tmp_philo, time_to_die);
		sem_post(tmp_info->eating);
		usleep(100);
	}
	exit(0);
	return (NULL);
}

static void	philo_start(t_info	*info)
{
	int	i;

	i = -1;
	info->start_time = philo_get_time();
	while (++i < info->num_of_philo)
	{
		info->philos[i].pid = fork();
		if (info->philos[i].pid < 0)
		{
			error(5);
			return ;
		}
		if (info->philos[i].pid == 0)
		{
			if (pthread_create(&info->philos[i].checking_death,
					NULL, &check_death, &info->philos[i]))
			{
				error(2);
				return ;
			}
			philo_working(&info->philos[i], info);
		}
	}
	ft_clean(info, &info->philos[i]);
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
