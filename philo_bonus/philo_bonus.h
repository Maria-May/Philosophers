/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:06:45 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/29 14:06:50 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int				index;
	int				eat;
	long long		last_eat;
	pid_t			pid;
	pthread_t		checking_death;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_eating_times;
	int			alive;
	int			must_eat;
	sem_t		*fork;
	sem_t		*logs;
	sem_t		*eating;
	sem_t		*ending;
	t_philo		*philos;
	long long	start_time;
}	t_info;

int		init_philo(t_info *info, int argc, char **argv);
long	philo_get_time(void);
void	error(int flag);
void	philo_take_forks(t_philo	*philo, t_info	*info);
void	philo_eat(t_philo	*philo, t_info	*info);
void	philo_think(t_philo	*philo, t_info	*info);
void	ft_clean(t_info *info, t_philo *philo);
#endif
