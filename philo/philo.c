/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoung <jeyoung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:06:02 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/22 21:19:19 by jeyoung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	philo_start(t_info *info)
{
	t_phil	*philo;

	philo = (t_phil *)malloc(sizeof(t_phil) * info->num_philo);
	if (!philo)
		return (1);
	init_philo(info, philo);
	init_thread(info, philo);
}
