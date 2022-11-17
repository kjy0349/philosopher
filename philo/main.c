/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:52:14 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/17 19:17:55 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

unsigned int	mrand(void)
{
	int				next;
	struct timeval	time;

	gettimeofday(&time, NULL);
	next = time.tv_usec;
	next = next * 1103515245 + 12345;
	return ((unsigned int)(next / 65536) % 32768);
}

int	*init_input(int argc, char *argv[])
{
	int	*inputs;

	inputs = (int *)malloc(sizeof(int) * (argc - 1));
	inputs[0] = ft_atoi(argv[1]);
	inputs[1] = ft_atoi(argv[2]);
	inputs[2] = ft_atoi(argv[3]);
	inputs[3] = ft_atoi(argv[4]);
	if (argc == 6)
		inputs[4] = ft_atoi(argv[5]);
	return (inputs);
}

void	philo(void *ptr)
{
	t_phil	*phl;

	phl = (t_phil *)ptr;
	if (phl->tid % 2 == 1)
		usleep(100);
	while (*(phl->is_die) == 0)
	{
		if (think(phl))
			return ;
		if (pickup(phl->tid, phl))
			return ;
		if (eat(phl))
			return ;
		putdown(phl->tid, phl);
		if (start_sleep(phl))
			return ;
	}
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_phil(long long time, t_info *info, t_phil *phl, int i)
{
	phl->tid = i;
	phl->num = info->inputs[0];
	phl->t_die = info->inputs[1];
	phl->t_eat = info->inputs[2];
	phl->t_slp = info->inputs[3];
	phl->state = 0;
	phl->start_time = time;
	phl->is_die = &(info->is_die);
	phl->forks = info->forks;
	phl->eat_time = time;
	i = 0;
	while (i < (info->inputs)[0])
	{
		pthread_mutex_init(&((info->forks)[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(info->print_lock), NULL);
	phl->forks = info->forks;
	phl->print_lock = &(info->print_lock);
}

void	main_philo(void *ptr)
{
	int				i;
	long long		time;
	t_info			*info;
	t_phil			*phl;

	info = (t_info *)ptr;
	phl = (t_phil *)malloc(sizeof(t_phil) * (info->inputs)[0]);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	(info->inputs)[0]);
	i = 1;
	time = get_time();
	info->is_die = 0;
	while (i <= (info->inputs)[0])
	{
		init_phil(time, info, &(phl[i - 1]), i);
		pthread_create(&(phl[i - 1].thread), NULL, (void *)philo, &(phl[i - 1]));
		i++;
	}
	i = 1;
	while (i <= (info->inputs)[0])
	{
		pthread_join((phl[i - 1]).thread, NULL);
		i++;
	}
	return ;
}

// 0 : THINK, 1 : SLEEP, 2 : EATING
int	main(int argc, char *argv[])
{
	pthread_t	m_tid;
	t_info		info;

	if (argc != 6 && argc != 5)
		return (0);
	info.inputs = init_input(argc, argv);
	pthread_create(&m_tid, NULL, (void *)main_philo, (void *)&info);
	pthread_join(m_tid, NULL);
	return (0);
}
