/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:52:26 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/17 18:55:15 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct info
{
	int				*inputs;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				is_die;	
}	t_info;

typedef struct thr
{
	int				tid;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				state;
	long long		start_time;
	long long		eat_time;
	int				*is_die;
	int				num;
	pthread_t		thread;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*forks;
}	t_phil;

unsigned int	mrand(void);
int				pickup(int i, t_phil *phl);
void			putdown(int i, t_phil *phl);
long long		get_time(void);
int				think(t_phil *phl);
int				eat(t_phil *phl);
void			putdown(int i, t_phil *phl);
int				ft_atoi(const char *str);
int				start_sleep(t_phil *phl);

#endif