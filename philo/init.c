/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoung <jeyoung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:02:35 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/23 21:31:50 by jeyoung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init_thread(t_info *info, t_phil *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
	{
		philo[i].right = philo[(i + 1) % info->num_philo].left;
		if (pthread_create(&philo[i].thread, NULL, \
		&philo_loop, &philo[i]) == -1)
			return (error_free("Error\n", info, philo, 1));
	}
	i = -1;
	info->start = get_time();
	while (++i < info->num_philo)
	{
		philo[i].t_start = info->start;
		philo[i].meal = info->start;
	}
	info->ready = 1;
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
		philo[i].left = &info->forks[i];
		philo[i].right = 0;
		i++;
	}
}

int	init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	info->death = 0;
	info->forks = 0;
	info->death = malloc(sizeof(pthread_mutex_t));
	if (!info->death)
		return (error_free("Error\n", info, 0, 1));
	info->forks = malloc(sizeof(pthread_mutex_t) * \
	info->num_philo);
	if (!info->forks)
		return (error_free("Error\n", info, 0, 1));
	if (pthread_mutex_init(info->death, NULL) == -1)
		return (error_free("Error\n", info, 0, 1));
	while (++i < info->num_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) == -1)
			return (error_free("Error\n", info, 0, 1));
	}
	return (0);
}

int	init_input(t_info *info, int argc, char *argv[])
{
	int	mutex;

	mutex = -1;
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
		mutex = init_mutexes(info);
	return (mutex || info->num_philo <= 0 || info->t_die <= 0 \
	|| info->t_eat <= 0 || info->t_slp <= 0 || info->must_eat == 0);
}
