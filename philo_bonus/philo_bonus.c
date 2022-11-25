/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:06:02 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/25 13:30:47 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	print_state(t_phil *philo, char *str)
{
	sem_wait(philo->info->death);
	if (philo->info->over)
	{
		sem_post(philo->info->death);
		return ;
	}
	printf("%lldms %d %s\n", get_time() - philo->t_start, philo->tid, str);
	sem_post(philo->info->death);
}

void	sleep_think(t_phil *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->info->t_slp);
	print_state(philo, "is thinking");
}

void	eating(t_phil *philo)
{
	sem_wait(philo->info->forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	print_state(philo, "has taken a fork");
	philo->meal = get_time();
	print_state(philo, "is eating");
	ft_usleep(philo->info->t_eat);
	philo->eat_num++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	*philo_loop(void *ptr)
{
	t_phil	*philo;

	philo = (t_phil *)ptr;
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
	info->philo = malloc(sizeof(t_phil) * info->num_philo);
	if (!info->philo)
		return (1);
	init_philo(info, info->philo);
	if (init_thread(info, info->philo))
		return (1);
	thread_end(info, info->philo);
	return (0);
}
