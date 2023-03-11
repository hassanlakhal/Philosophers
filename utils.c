/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:32:46 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/11 21:55:35 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	t;

	gettimeofday(&tv, NULL);
	t = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (t);
}

void ft_usleep(unsigned long time_sleep)
{
	unsigned long i;
	i = get_time();
	while (get_time() - i < time_sleep)
		usleep(600);
}

int	ft_checkeat(int *a, int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		if(a[i] == 1)
			i++;
		else
			break;
	}
	if(i == n)
		return(1);
	return(0);
}
void ft_initialisation(int ac, char **argv, t_data *info_p)
{
	info_p->number_of_fork = ft_atoi(argv[1]);
	info_p->number_of_philosophers = ft_atoi(argv[1]);
	info_p->time_to_die = ft_atoi(argv[2]);
	info_p->time_to_eat = ft_atoi(argv[3]);
	info_p->time_to_sleep = ft_atoi(argv[4]);
	if (ac == 6)
			info_p->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		else
			info_p->number_of_times_each_philosopher_must_eat = -1;

}
