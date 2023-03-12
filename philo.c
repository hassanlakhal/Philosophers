/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 00:00:00 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/12 15:31:59 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_data *info, char *act, pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	printf("\n %lu ms Philosopher %d %s", get_time() - info->t_start, info->id,
			act);
	if (strcmp(act, "die"))
		pthread_mutex_unlock(print);
}

void	dine(t_data *data)
{
	if (data->id % 2)
		usleep(600);
	while (data->cont)
	{
		pthread_mutex_lock(&data->fork_d[data->fork_l]);
		print(data, "has take a fork", data->print);
		pthread_mutex_lock(&data->fork_d[(data->fork_r)]);
		print(data, "has take a fork", data->print);
		print(data, "is eating", data->print);
		pthread_mutex_lock(&data->cont_mutex);
		if (data->cont && data->cont != -1)
			data->cont--;
		data->time_last = get_time();
		pthread_mutex_unlock(&data->cont_mutex);
		ft_usleep(data->time_to_eat);
		pthread_mutex_unlock(&data->fork_d[data->fork_r]);
		pthread_mutex_unlock(&data->fork_d[(data->fork_l)]);
		print(data, "is sleeping", data->print);
		ft_usleep(data->time_to_sleep);
		print(data, "is thinking", data->print);
	}
}

int	ft_died(t_data *died, int size)
{
	int	i;
	int	*eat;

	i = 0;
	eat = malloc(size * sizeof(int));
	memset(eat, 0, size * sizeof(int));
	while (1)
	{
		i = 0;
		while (i < died->number_of_philosophers)
		{
			if (ft_checkeat(eat, died->number_of_philosophers))
				return (0);
			pthread_mutex_lock(&died[i].cont_mutex);
			if (!died[i].cont)
				eat[i] = 1;
			if (get_time() - died[i].time_last >= died->time_to_die
				&& died[i].cont)
			{
				print(died, "died", died[0].print);
				return (3);
			}
			pthread_mutex_unlock(&died[i].cont_mutex);
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_data	*p;
	int		i;

	p = NULL;
	if (argc == 5 || argc == 6)
	{
		p = allocatin(p, ft_atoi(argv[1]));
		ft_initialisation(argc, argv, p);
		i = 0;
		while (i < p->number_of_philosophers)
		{
			p[i].t_start = get_time();
			p[i].time_to_eat = p->time_to_eat;
			p[i].time_to_sleep = p->time_to_sleep;
			p[i].number_of_times_eat = p->number_of_times_eat;
			p[i].cont = p->number_of_times_eat;
			p[i].number_temp = ft_atoi(argv[1]);
			pthread_mutex_init(&p[i].cont_mutex, NULL);
			pthread_mutex_init(&p->fork_d[i], NULL);
			i++;
		}
		i = 0;
		while (i < p->number_of_philosophers)
		{
			pthread_create(&p->philosopher[i], NULL, (void *)dine,
					(t_data *)&p[i]);
			i++;
		}
		ft_died(p, ft_atoi(argv[1]));
	}
	return (0);
}
