/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoung <jeyoung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:54:48 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/22 19:10:53 by jeyoung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*monitoring(void *ptr)
{
	t_phil			*philo;
	struct timeval	now;
	long long		ms;

	philo = (t_phil *)ptr;
	while (!philo->info->is_die)
	{
		pthread_mutex_lock(&philo->check_mut);
		pthread_mutex_lock(&philo->info->finish_mutex);
		gettimeofday(&now, NULL);
		ms = get_time(now) - get_time(philo->hungry_time);
		gettimeofday(&now, NULL);
		if (ms >= philo->info->t_die && philo->info->is_die == 0)
		{
			printf("%lld\t%d\t %s\n", get_time(now) - \
			get_time(philo->info->start_time), philo->tid, "died");
			philo->info->is_die = 1;
		}
		pthread_mutex_unlock(&philo->info->finish_mutex);
		pthread_mutex_unlock(&philo->check_mut);
	}
	return (NULL);
}

void	*monitor_must_eat(void *ptr)
{
	t_info	*info;

	info = (t_info *)ptr;
	while (!info->is_die)
	{
		pthread_mutex_lock(&info->finish_mutex);
		if (info->num_full_philo == info->num_philo)
			info->is_die = 1;
		pthread_mutex_unlock(&info->finish_mutex);
	}
	return (NULL);
}
