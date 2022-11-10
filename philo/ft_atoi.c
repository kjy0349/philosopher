/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:16:12 by jeyoung           #+#    #+#             */
/*   Updated: 2022/11/08 14:29:25 by jeykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	if (c == '\n' || c == '\v' || c == '\t' || \
	c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	return_num;
	long long	tmp;

	sign = 1;
	return_num = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = return_num * 10 + (str[i] - '0');
		if (tmp < return_num)
			return (-1 + (sign < 0));
		return_num = tmp;
		i++;
	}
	return ((int)(return_num * sign));
}
