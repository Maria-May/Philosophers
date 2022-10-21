/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:45:47 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/21 13:51:15 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				index;
	int				alive;
	int				eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long long		last_eat;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	pthread_t		*philosophers;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eating_times;
	int				checking;
	pthread_mutex_t	*forks;
	pthread_mutex_t	logs;
	pthread_mutex_t	eat;
	pthread_mutex_t	philo_check;
	t_philo			*philos;
	long long		start_time;
}	t_info;

int		init_philo(t_info *info, int argc, char **argv);
int		ft_atoi(const char *str);
long	philo_get_time(void);
void	philo_take_forks(t_philo	*tmp_philo);
void	philo_eat(t_philo	*tmp_philo);
void	philo_think(t_philo	*tmp_philo);
int		is_philo_live(t_philo	*tmp_philo);
void	check_death(t_info	*info);
void	error(int flag);
void	message(t_philo	*tmp_philo, char *msg, void (*call_back)(t_philo *));
#endif
