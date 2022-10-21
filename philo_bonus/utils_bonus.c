/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:08:38 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/29 14:08:40 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (sign == -1 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i++] - '0');
		if (result > 2147483647 && sign == 1)
			return (0);
		else if (result > 2147483648 && sign == -1)
			return (0);
	}
	return (result * sign);
}

long	philo_get_time(void)
{
	struct timeval	time;
	long long		t;

	gettimeofday(&time, NULL);
	t = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (t);
}

void	error(int flag)
{
	if (flag == 1)
		printf("Argument error\n");
	if (flag == 2)
		printf("Pthread error\n");
	if (flag == 3)
		printf("Malloc error\n");
	if (flag == 4)
		printf("Mutex error\n");
	if (flag == 5)
		printf("Pid error\n");
	if (flag == 6)
		printf("Semaphore error\n");
}

void	kill_all(t_info	*info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		kill(info->philos[i].pid, SIGKILL);
		waitpid(info->philos[i].pid, NULL, 0);
	}
}

void	ft_clean(t_info *info, t_philo *philo)
{
	int	i;
	int	exit_status;

	i = -1;
	while (++i < info->num_of_philo)
	{
		waitpid(-1, &exit_status, 0);
		if (WEXITSTATUS(exit_status) == 1)
		{
			kill_all(info);
			break ;
		}
	}
	free (info->philos);
	sem_unlink("/fork");
	sem_close(info->fork);
	sem_unlink("/logs");
	sem_close(info->logs);
	sem_unlink("/eating");
	sem_close(info->eating);
	sem_unlink("/ending");
	sem_close(info->ending);
}
