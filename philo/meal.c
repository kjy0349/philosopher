/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:28:36 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/11 00:12:47 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_thread(t_phil *phl)
{
	int	state;

	state = phl->state;
	if (state == 0)
		printf("%lld %d is thinking\n", phl->start_time - get_time(), \
		phl->tid + 1);
	else if (state == 1)
		printf("%lld %d is sleeping\n", phl->start_time - get_time(), \
		phl->tid + 1);
	else if (state == 2)
		printf("%lld %d is eating\n", phl->start_time - get_time(), \
		phl->tid + 1);
}

int	leftof(int i, t_phil *phl)
{
	return ((i + phl->num - 1) % phl->num);
}

int	rightof(int i, t_phil *phl)
{
	return ((i + 1) % phl->num);
}

void	pickup(int i, t_phil *phl)
{
	pthread_mutex_lock(&(phl->forks[leftof(i, phl)]));
	printf("%d has taken a fork\n", phl->tid + 1);
	pthread_mutex_lock(&(phl->forks[rightof(i, phl)]));
	printf("%d has taken a fork\n", phl->tid + 1);
	phl->state = 2;
	print_thread(phl);
	usleep(phl->t_eat * 1000);
	pthread_mutex_unlock(&(phl->forks[rightof(i, phl)]));
	pthread_mutex_unlock(&(phl->forks[leftof(i, phl)]));
	phl->state = 1;
	print_thread(phl);
	usleep(phl->t_slp * 1000);
	phl->state = 0;
	print_thread(phl);
}
