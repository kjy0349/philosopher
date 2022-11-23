/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoung <jeyoung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:06:02 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/23 22:06:39 by jeyoung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_state(t_phil *philo, char *str)
{
	pthread_mutex_lock(philo->info->death);
	if (philo->info->over)
	{
		pthread_mutex_unlock(philo->info->death);
		return ;
	}
	printf("%lldms %d %s\n", get_time() - philo->t_start, philo->tid, str);
	pthread_mutex_unlock(philo->info->death);
}

void	sleep_think(t_phil *philo)
{
	ft_usleep(philo->info->t_slp);
	print_state(philo, "is sleeping");
	print_state(philo, "is thinking");
}

void	eating(t_phil *philo)
{
	pthread_mutex_lock(philo->left);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right);
	print_state(philo, "has taken a fork");
	philo->meal = get_time();
	ft_usleep(philo->info->t_eat);
	print_state(philo, "is eating");
	philo->eat_num++;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*philo_loop(void *job)
{
	t_phil	*philo;

	philo = (t_phil *)job;
	while (!philo->info->ready)
		continue ;
	if (philo->tid % 2 == 0)
		ft_usleep(philo->info->t_eat * 0.9 + 1);
	while (!philo->info->over)
	{
		eating(philo);
		sleep_think(philo);
	}
	return (NULL);
}

int	philo_start(t_info *info)
{
	t_phil	*philo;

	philo = malloc(sizeof(t_phil) * info->num_philo);
	if (!philo)
		return (1);
	init_philo(info, philo);
	if (init_thread(info, philo))
		return (1);
	check_thread(info, philo);
	thread_end(info, philo);
	return (0);
}
