/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:52:26 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/24 19:57:06 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>

typedef struct s_info
{
	int				num_philo;
	int				ready;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				must_eat;
	int				chk_meal;
	int				over;
	long long		start;
	sem_t			*death;
	sem_t			*forks;
	void			*philo;
}	t_info;

typedef struct s_thr
{
	int				tid;
	int				is_die;
	int				eat_num;
	long long		t_start;
	long long		meal;
	pthread_t		thread;
	t_info			*info;
}	t_phil;

int			ft_atoi(const char *str);
int			error_free(char *str, t_info *info, t_phil *philo, int malloc);
int			init_input(t_info *info, int argc, char *argv[]);
void		init_philo(t_info *info, t_phil *philo);
int			init_thread(t_info *info, t_phil *philo);
long long	get_time(void);
int			philo_start(t_info *info);
int			ft_usleep(int time);
int			philo_start(t_info *info);
void		*philo_loop(void *job);
void		*check_thread(void *ptr);
void		print_state(t_phil *philo, char *str);
void		thread_end(t_info *info, t_phil *philo);

#endif