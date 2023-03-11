/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 00:00:00 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/11 22:32:52 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(unsigned long time,int id, char *act, pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	printf("\n %lu ms Philosopher %d %s",time, id, act);
	if(strcmp(act,"die"))
		pthread_mutex_unlock(print);
}

void	dine(t_data *data)
{
	if (data->id % 2)
		usleep(350);
	while (data->cont)
	{
		pthread_mutex_lock(&data->fork_d[data->fork_left]);
		print(get_time() - data->time_strat , data->id,"has take a fork",data->print);
		pthread_mutex_lock(&data->fork_d[(data->fork_right)]);
		print(get_time() - data->time_strat , data->id,"has take a fork",data->print);
		print(get_time() - data->time_strat , data->id,"is eating",data->print);
		pthread_mutex_lock(&data->cont_mutex);
		if(data->cont && data->cont != -1)
			data->cont--;
		data->time_last = get_time();
		pthread_mutex_unlock(&data->cont_mutex);
		ft_usleep(data->time_to_eat);
		pthread_mutex_unlock(&data->fork_d[data->fork_right]);
		pthread_mutex_unlock(&data->fork_d[(data->fork_left)]);
		print(get_time() - data->time_strat , data->id, "is sleeping",data->print);
		ft_usleep(data->time_to_sleep);
		print(get_time() - data->time_strat , data->id,"is thinking",data->print);
	}
}

int main(int argc, char *argv[])
{

	t_data	*p;
	int		message;
	int		i;
	int *eat ;
	p = NULL;
	if (argc == 5 || argc == 6)
	{
		eat = malloc(ft_atoi(argv[1]) * sizeof(int));
		memset(eat,0,ft_atoi(argv[1]) * sizeof(int));
		p = allocatin(p,ft_atoi(argv[1]));
		ft_initialisation(argc,argv,p);
		i = 0;
		while (i < p->number_of_philosophers)
		{
			p[i].time_strat = get_time();
			p[i].time_to_eat = p->time_to_eat;
			p[i].time_to_sleep = p->time_to_sleep;
			p[i].number_of_times_each_philosopher_must_eat = p->number_of_times_each_philosopher_must_eat;
			p[i].cont = p->number_of_times_each_philosopher_must_eat;
			p[i].number_temp = ft_atoi(argv[1]);
			pthread_mutex_init(&p[i].cont_mutex, NULL);
			message = pthread_mutex_init(&p->fork_d[i], NULL);
			if (message == -1)
			{
				printf("failed");
				exit(1);
			}
			i++;
		}
		i = 0;
		while (i < p->number_of_philosophers)
		{

			message = pthread_create(&p->philosopher[i], NULL, (void *)dine,
					(t_data *)&p[i]);
			if (message != 0)
			{
				printf("\nfailed");
				exit(1);
			}
			i++;
		}
		while (1)
		{
			i = 0;
			while (i < p->number_of_philosophers)
			{

				if(ft_checkeat(eat, p->number_of_philosophers))
					return(0);
				pthread_mutex_lock(&p[i].cont_mutex);
				if(!p[i].cont)
					eat[i] = 1;
				if (get_time() -  p[i].time_last >= p->time_to_die && p[i].cont)
				{
					printf("\n");
					print(get_time() - p[i].time_strat, p[i].id,"died", p[0].print);
					printf("\n");
					return (1);
				}
				pthread_mutex_unlock(&p[i].cont_mutex);
				i++;
			}
	}
	}
	return 0;
}
