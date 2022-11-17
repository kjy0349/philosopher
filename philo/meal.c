/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:28:36 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/17 15:52:38 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_thread(t_phil *phl, int chk)
{
	int	state;

	state = phl->state;
	pthread_mutex_lock(phl->print_lock);
	if (*(phl->is_die) == 0)
	{
		if (chk == 0)
		{
			if (state == 0)
				printf("%lld %d is thinking\n", get_time() - phl->start_time, \
				phl->tid);
			else if (state == 1)
				printf("%lld %d is sleeping\n", get_time() - phl->start_time, \
				phl->tid);
			else if (state == 2)
				printf("%lld %d is eating\n", get_time() - phl->start_time, \
				phl->tid);
		}
		else if (chk == 1)
			printf("%d has taken a fork\n", phl->tid);
	}
	pthread_mutex_unlock(phl->print_lock);
}

int	leftof(int i, t_phil *phl)
{
	if (i == 1)
		return (phl->num - 1);
	else
		return (i - 2);
}

int	rightof(int i, t_phil *phl)
{
	if (i == phl->num)
		return (0);
	else
		return (i);
}

// cnt == 0 : 없음, 1 : 왼쪽, 2 : 오른쪽, 3 : 양쪽
int	die_chk(int i, t_phil *phl, int cnt)
{
	if (*(phl->is_die) == 1)
		return (1);
	if (get_time() - (phl->thk_time) > phl->t_die)
	{
		*(phl->is_die) = 1;
		if (cnt == 1)
			pthread_mutex_unlock(&(phl->forks[leftof(i, phl)]));
		else if (cnt == 2)
			pthread_mutex_unlock(&(phl->forks[rightof(i, phl)]));
		else if (cnt == 3)
		{
			pthread_mutex_unlock(&(phl->forks[leftof(i, phl)]));
			pthread_mutex_unlock(&(phl->forks[rightof(i, phl)]));
		}
		pthread_mutex_lock(phl->print_lock);
		printf("%lld %d is died\n", get_time() - phl->start_time, \
		phl->tid);
		pthread_mutex_unlock(phl->print_lock);
		return (1);
	}
	else
		return (0);
}

int	pickup(int i, t_phil *phl)
{
	if (die_chk(i, phl, 0))
		return (-1);
	pthread_mutex_lock(&(phl->forks[leftof(i, phl)]));
	print_thread(phl, 1);
	if (die_chk(i, phl, 1))
		return (-1);
	pthread_mutex_lock(&(phl->forks[rightof(i, phl)]));
	print_thread(phl, 1);
	if (die_chk(i, phl, 2))
		return (-1);
	usleep(10000);
	if (die_chk(i, phl, 0))
		return (-1);
	pthread_mutex_lock(&(phl->forks[leftof(i, phl)]));
	print_thread(phl, 1);
	if (die_chk(i, phl, 1))
		return (-1);
	pthread_mutex_lock(&(phl->forks[rightof(i, phl)]));
	print_thread(phl, 1);
	if (die_chk(i, phl, 2))
		return (-1);
	return (1);
}

void	think(t_phil *phl)
{
	phl->state = 0;
	print_thread(phl, 0);
	phl->thk_time = get_time();
}

void	eat(t_phil *phl)
{
	phl->state = 2;
	print_thread(phl, 0);
	usleep(phl->t_eat * 1000);
}

void	putdown(int i, t_phil *phl)
{
	if (i % 2 == 1)
	{
		pthread_mutex_unlock(&(phl->forks[leftof(i, phl)]));
		pthread_mutex_unlock(&(phl->forks[rightof(i, phl)]));
	}
	else
	{
		pthread_mutex_unlock(&(phl->forks[rightof(i, phl)]));
		pthread_mutex_unlock(&(phl->forks[leftof(i, phl)]));
	}
}

void	start_sleep(t_phil *phl)
{
	phl->state = 1;
	print_thread(phl, 0);
	usleep(phl->t_slp * 1000);
}
