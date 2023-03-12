/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 21:53:09 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/12 17:08:53 by hlakhal-         ###   ########.fr       */
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

int	check_arg(char *argv[], int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || argv[1][0] == '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	print(t_data *info, char *act, pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	printf("\n %lu ms Philosopher %d %s", get_time() - info->t_start, info->id,
		act);
	if (strcmp(act, "die"))
		pthread_mutex_unlock(print);
}

int	message_error(void)
{
	printf("\033[41m Error of invlid args");
	printf(" or number of philo is 0 \033[0m\n");
	return (1);
}
