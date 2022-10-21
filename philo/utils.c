/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:13:35 by mdaryn            #+#    #+#             */
/*   Updated: 2022/06/21 14:13:36 by mdaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo	*tmp_philo, char *msg, void (*call_back)(t_philo *))
{
	pthread_mutex_lock(&tmp_philo->info->logs);
	if (tmp_philo->info->checking)
	{
		printf("%lld %d %s\n",
			(philo_get_time() - tmp_philo->info->start_time),
			tmp_philo->index + 1, msg);
		if (call_back)
			call_back(tmp_philo);
	}
	pthread_mutex_unlock(&tmp_philo->info->logs);
}

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
}
