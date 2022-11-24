/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:02:50 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/24 15:19:59 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	philo_die(t_phil *philo)
{
	print_state(philo, "is died");
	philo->info->over = 1;
	philo->is_die = 1;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (1);
}

int	check_death(t_phil *philo)
{
	long long	now;

	pthread_mutex_lock(philo->info->death);
	now = get_time() - philo->meal;
	if (now >= philo->info->t_die)
	{
		pthread_mutex_unlock(philo->info->death);
		return (philo_die(philo));
	}
	pthread_mutex_unlock(philo->info->death);
	return (0);
}

int	check_meal(t_phil philo, int idx)
{
	if (philo.info->chk_meal && idx == philo.info->num_philo - 1 && \
	philo.eat_num == philo.info->must_eat)
		return (ft_usleep(300));
	return (0);
}

void	check_thread(t_info *info, t_phil *philo)
{
	int	i;

	while (!info->ready)
		continue ;
	while (!info->over)
	{
		i = 0;
		while (i < info->num_philo)
		{
			if (check_death(&philo[i]) || check_meal(philo[i], i))
				info->over = 1;
			i++;
		}
	}
	if (info->chk_meal && philo[info->num_philo - 1].eat_num == info->must_eat)
	{
		ft_usleep(5 * info->num_philo);
		printf("eating %d times\n", info->must_eat);
	}
}

void	thread_end(t_info *info, t_phil *philo)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(philo[i].thread, (void *)&philo[i]);
		i++;
	}
	pthread_mutex_destroy(info->death);
	pthread_mutex_destroy(info->forks);
	free(info->death);
	free(info->forks);
	free(philo);
}
