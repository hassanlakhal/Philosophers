/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 21:53:09 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/12 15:25:03 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*allocatin(t_data *info_p, int size_of_allocation)
{
	int	i;

	i = 0;
	info_p = (t_data *)malloc(sizeof(t_data) * size_of_allocation);
	info_p->philosopher = (pthread_t *)malloc(sizeof(pthread_t)
			* size_of_allocation);
	info_p[0].fork_d = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* size_of_allocation);
	info_p[0].print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info_p[0].print, NULL);
	while (i < size_of_allocation)
	{
		info_p[i].print = info_p[0].print;
		info_p[i].fork_d = info_p[0].fork_d;
		info_p[i].id = i + 1;
		info_p[i].fork_l = i;
		info_p[i].fork_r = (i + 1) % size_of_allocation;
		info_p[i].time_last = get_time();
		i++;
	}
	info_p->t_start = 0;
	return (info_p);
}
