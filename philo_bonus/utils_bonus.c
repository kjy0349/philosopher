/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:16:12 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/24 17:18:51 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

int	ft_usleep(int time)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time)
		usleep(150);
	return (1);
}

long long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	is_space(char c)
{
	if (c == '\n' || c == '\v' || c == '\t' || \
	c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	return_num;
	long long	tmp;

	sign = 1;
	return_num = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = 0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = return_num * 10 + (str[i] - '0');
		if (tmp < return_num)
			return (-1 + (sign < 0));
		return_num = tmp;
		i++;
	}
	return ((int)(return_num * sign));
}

int	error_free(char *str, t_info *info, t_phil *philo, int malloc)
{
	sem_close(info->death);
	sem_unlink("/death");
	sem_close(info->forks);
	sem_unlink("/fork");
	if (malloc)
	{
		if (philo)
			free(philo);
	}
	printf("%s", str);
	return (1);
}
