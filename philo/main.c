/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:52:14 by jeykim            #+#    #+#             */
/*   Updated: 2022/11/25 13:16:06 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// 0 : THINK, 1 : SLEEP, 2 : EATING
int	main(int argc, char *argv[])
{
	t_info		info;

	memset(&info, 0, sizeof(info));
	if ((argc != 6 && argc != 5) || init_input(&info, argc, argv))
	{
		printf("Error\n");
		return (1);
	}
	if (philo_start(&info))
		return (1);
	return (0);
}
