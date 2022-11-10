/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:52:26 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/10 23:50:24 by jeykim           ###   ########.fr       */
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
	int				inputs[5];
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
	int				*is_die;
	int				num;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*forks;
}	t_phil;

unsigned int	mrand(void);
void			pickup(int i, t_phil *phl);
void			putdown(int i, t_phil *phl);
long long		get_time(void);
int	ft_atoi(const char *str);

#endif