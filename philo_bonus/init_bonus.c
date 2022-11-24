/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:02:35 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/24 19:31:48 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

int	init_thread(t_info *info, t_phil *philo)
{
	int			i;
	pthread_t	death_thread;

	i = -1;
	info->start = get_time();
	if (pthread_create(&death_thread, NULL, &check_thread, info) == -1)
		return (error_free("Error\n", info, philo, 1));
	while (++i < info->num_philo)
	{
		philo[i].t_start = info->start;
		philo[i].meal = info->start;
		if (pthread_create(&philo[i].thread, NULL, \
		&philo_loop, &philo[i]) == -1)
			return (error_free("Error\n", info, philo, 1));
	}
	info->ready = 1;
	pthread_join(death_thread, NULL);
	return (0);
}

void	init_philo(t_info *info, t_phil *philo)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		philo[i].tid = i + 1;
		philo[i].is_die = 0;
		philo[i].eat_num = 0;
		philo[i].t_start = 0;
		philo[i].meal = 0;
		philo[i].info = info;
		i++;
	}
}

int	init_semaphore(t_info *info)
{
	sem_unlink("/death");
	sem_unlink("/forks");
	info->death = sem_open("/death", O_CREAT, 0660, 1);
	if (info->death == SEM_FAILED)
		return (error_free("Error\n", info, 0, 1));
	info->forks = sem_open("/forks", O_CREAT, 0660, info->num_philo);
	if (info->forks == SEM_FAILED)
		return (error_free("Error\n", info, 0, 1));
	return (0);
}

int	init_input(t_info *info, int argc, char *argv[])
{
	int	sem;

	sem = -1;
	info->num_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_slp = ft_atoi(argv[4]);
	info->must_eat = -2;
	info->chk_meal = 0;
	info->start = 0;
	info->ready = 0;
	if (argc == 6)
	{
		info->chk_meal = 1;
		info->must_eat = ft_atoi(argv[5]);
	}
	info->over = 0;
	if (info->num_philo > 0)
		sem = init_semaphore(info);
	return (sem || info->num_philo <= 0 || info->t_die <= 0 \
	|| info->t_eat <= 0 || info->t_slp <= 0 || info->must_eat == 0);
}
