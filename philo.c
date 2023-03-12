/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 00:00:00 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/12 17:08:07 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_died(t_data *died, int *eat)
{
	int	i;

	i = 0;
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
				print(died, "\033[41m died \033[0m\n", died[0].print);
				return (3);
			}
			pthread_mutex_unlock(&died[i].cont_mutex);
			i++;
		}
	}
}

void	td_create(t_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_create(&philo->philosopher[i], NULL, (void *)dine,
			(t_data *)&philo[i]);
		i++;
	}
}

void	mutex_init(t_data *p, int i)
{
	p[i].t_start = get_time();
	p[i].time_to_eat = p->time_to_eat;
	p[i].time_to_sleep = p->time_to_sleep;
	p[i].number_of_times_eat = p->number_of_times_eat;
	p[i].cont = p->number_of_times_eat;
	pthread_mutex_init(&p[i].cont_mutex, NULL);
	pthread_mutex_init(&p->fork_d[i], NULL);
}

int	main(int argc, char *argv[])
{
	t_data	*p;
	int		i;
	int		*eat;

	p = NULL;
	if (argc == 5 || argc == 6)
	{
		if (!check_arg(argv, argc))
			return (message_error());
		p = allocatin(p, ft_atoi(argv[1]));
		ft_initialisation(argc, argv, p);
		eat = malloc(ft_atoi(argv[1]) * sizeof(int));
		memset(eat, 0, ft_atoi(argv[1]) * sizeof(int));
		i = 0;
		while (i < p->number_of_philosophers)
		{
			mutex_init(p, i);
			i++;
		}
		td_create(p);
		ft_died(p, eat);
	}
	return (0);
}
