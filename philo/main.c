/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:52:14 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/10 14:14:00 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	mrand(void)
{
	long			next;
	struct timeval	time;

	gettimeofday(&time, NULL);
	next = time.tv_sec;
	next = next * 1103515245 + 12345;
	return ((unsigned int)(next / 65536) % 32768);
}

int	*init_input(int argc, int *inputs, char *argv[])
{
	int	i;
	int	*states;

	i = 0;
	inputs[0] = ft_atoi(argv[1]);
	inputs[1] = ft_atoi(argv[2]);
	inputs[2] = ft_atoi(argv[3]);
	inputs[3] = ft_atoi(argv[4]);
	if (argc == 6)
		inputs[4] = ft_atoi(argv[5]);
	else
		inputs[5] = -1;
	states = (int *)malloc(sizeof(int) * (inputs[0] + 1));
	memset(states, 0, sizeof(int) * (inputs[0] + 1));
	return (states);
}

int		leftof(int i, t_info *info)
{
	return ((i + (info->inputs)[0] - 1 % (info->inputs)[0]));
}

int		rightof(int i, t_info *info)
{
	return ((i + 1) % (info->inputs)[0]);
}

void	test(int i, t_info *info)
{
	if ((info->states)[leftof(i, info)] != 2 \
	&& (info->states)[i] == 1 \
	&& (info->states)[rightof(i, info)] != 2)
	{
		(info->states)[i] = 2;
	}
}

void	pickup(int i, t_info *info)
{
	(info->states)[i] = 1;
	test(i, info);
	if ((info->states)[i] != 2)
		usleep()
}

void	putdown(int i, t_info *info)
{
	(info->states)[i] = 0;
	test((i + 4) % 5, info);
	test((i + 1) % 5, info);
}

void	philo(void *id)
{
	int	i;

	i = *((int *)id);
	while (1)
	{
		
	}
}

// 0 : THINK, 1 : HUNGRY, 2 : EATING
int	main(int argc, char *argv[])
{
	int			inputs[6];
	pthread_t	tid;
	int			i;
	t_info		info;

	if (argc != 6 && argc != 5)
		return (0);
	info.states = init_input(argc, inputs, argv);
	pthread_mutex_init(&(info.chop), NULL);
	pthread_mutex_init(&(info.print), NULL);
	i = 1;
	while (i <= inputs[0])
	{
		pthread_create(&tid, NULL, philo, (void *)&i);
		i++;
	}
	i = 1;
	while (i <= inputs[0])
	{
		pthread_join(&tid, NULL);
		i++;
	}
	return (0);
}
