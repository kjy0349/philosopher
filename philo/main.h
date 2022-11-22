/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoung <jeyoung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:52:26 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/22 21:19:07 by jeyoung          ###   ########.fr       */
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
	int				num_philo;
	int				ready;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				must_eat;
	int				chk_meal;
	int				over;
	int				start;
	pthread_mutex_t	*death;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct thr
{
	int				tid;
	int				is_die;
	int				eat_num;
	int				t_start;
	int				meal;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_info			*info;
}	t_phil;

int			ft_atoi(const char *str);
int			error_free(char *str, t_info *info, t_phil *philo, int malloc);
int			init_input(t_info *info, int argc, char *argv[]);
void		init_philo(t_info *info, t_phil *philo);
void		init_thread(t_info *info, t_phil *philo);
long long	get_time(void);
int			philo_start(t_info *info);

#endif