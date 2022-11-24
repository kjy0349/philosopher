/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:02:50 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/24 17:42:50 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

int	philo_die(t_phil *philo, int unlock, int print)
{
	if (unlock)
	{
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
	}
	if (print)
	{
		sem_wait(philo->info->death);
		printf("%lldms %d %s\n", get_time() - philo->t_start, \
		philo->tid, "is died");
		sem_post(philo->info->death);
	}
	return (1);
}

int	check_death(t_phil *philo)
{
	long long	now;

	sem_wait(philo->info->death);
	now = get_time() - philo->meal;
	if (now >= philo->info->t_die)
	{
		philo->info->over = 1;
		philo->is_die = 1;
		sem_post(philo->info->death);
		return (philo_die(philo, 1, 1));
	}
	sem_post(philo->info->death);
	return (0);
}

int	check_meal(t_phil philo, int idx)
{
	if (philo.info->chk_meal && idx == philo.info->num_philo - 1 && \
	philo.eat_num == philo.info->must_eat)
		return (ft_usleep(300));
	return (0);
}

void	*check_thread(void *ptr)
{
	int		i;
	t_info	*info;
	t_phil	*philo;

	info = (t_info *)ptr;
	philo = (t_phil *)info->philo;
	while (!info->ready)
		continue ;
	while (!info->over)
	{
		i = -1;
		while (++i < info->num_philo)
			if (check_death(&philo[i]) || check_meal(philo[i], i))
				info->over = 1;
	}
	if (info->chk_meal && philo[info->num_philo - 1].eat_num == info->must_eat)
	{
		ft_usleep(info->num_philo * 5);
		printf("eating %d times\n", info->must_eat);
		return (NULL);
	}
	return (NULL);
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
	ft_usleep(5 * info->num_philo);
	sem_close(info->death);
	sem_unlink("/death");
	sem_close(info->forks);
	sem_unlink("/forks");
	free(philo);
}
