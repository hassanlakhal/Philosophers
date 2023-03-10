/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treads.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 00:00:00 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/10 21:50:54 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		usleep(200);
}

void	dine(t_data *data)
{
	unsigned long	time;
	if (data->id % 2)
		usleep(350);
	while (data->cont)
	{
		pthread_mutex_lock(&data->fork_d[data->fork_left]);
		printf("\n %lu ms Philosopher %d has taken a fork", (get_time() - data->time_strat), data->id);
		pthread_mutex_lock(&data->fork_d[(data->fork_right)]);
		printf("\n %lu ms Philosopher %d has taken a fork", get_time() - data->time_strat , data->id);
		printf("\n %lu ms Philosopher %d is eating",get_time() - data->time_strat , data->id);
		if(data->cont && data->cont != -1)
			data->cont--;
		data->time_last = get_time();
		ft_usleep(data->time_to_eat);
		pthread_mutex_unlock(&data->fork_d[data->fork_right]);
		pthread_mutex_unlock(&data->fork_d[(data->fork_left)]);
		printf("\n %lu ms Philosopher %d is sleeping",get_time() - data->time_strat , data->id);
		ft_usleep(data->time_to_sleep);
		printf("\n %lu ms Philosopher %d is thinking",get_time() - data->time_strat , data->id);
	}
}

t_data *allocatin(t_data *info_p,int size_of_allocation)
{
	int i;
	i = 0;
	info_p = (t_data *)malloc(sizeof(t_data) * size_of_allocation);
	info_p->philosopher = (pthread_t *)malloc(sizeof(pthread_t) * size_of_allocation);
	info_p[0].fork_d = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size_of_allocation);
	while (i < size_of_allocation)
	{
		info_p[i].fork_d = info_p[0].fork_d;
		info_p[i].id = i + 1;
		info_p[i].fork_left = i;
		info_p[i].fork_right = (i + 1) % size_of_allocation;
		info_p[i].time_last = get_time();
		i++;
	}
	info_p->time_strat = 0;
	return info_p;
}

void ft_initialisation(int ac, char **argv, t_data *info_p)
{
	info_p->number_of_fork = atoi(argv[1]);
	info_p->number_of_philosophers = atoi(argv[1]);
	info_p->time_to_die = atoi(argv[2]);
	info_p->time_to_eat = atoi(argv[3]);
	info_p->time_to_sleep = atoi(argv[4]);
	if (ac == 6)
			info_p->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		else
			info_p->number_of_times_each_philosopher_must_eat = -1;

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

int main(int argc, char *argv[])
{

	t_data	*p;
	int		message;
	int		i;
	int size_of_allocation;
	if (argc == 5 || argc == 6)
	{
		size_of_allocation = atoi(argv[1]);
		p = allocatin(p,size_of_allocation);
		ft_initialisation(argc,argv,p);
		i = 0;
		while (i < p->number_of_philosophers)
		{
			p[i].time_strat = get_time();
			p[i].time_to_eat = p->time_to_eat;
			p[i].time_to_sleep = p->time_to_sleep;
			p[i].number_of_times_each_philosopher_must_eat = p->number_of_times_each_philosopher_must_eat;
			p[i].cont = p->number_of_times_each_philosopher_must_eat;
			p[i].number_temp = size_of_allocation;
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
		int *eat ;
		eat = malloc(size_of_allocation * sizeof(int));
		memset(eat,0,size_of_allocation * sizeof(int));
		while (1)
		{
			i = 0;
			while (i < p->number_of_philosophers)
			{
				if(!p[i].cont)
					eat[i] = 1;
				if(ft_checkeat(eat, p->number_of_philosophers))
					return(0);
				if (get_time() -  p[i].time_last >= p->time_to_die && p[i].cont)
				{
					printf("\n");
					printf("\n\t\033[31m Philosopher %d died\033[0m\n", p[i].id);
					printf("\n");
					return (1);
				}
				if (!p[i].number_temp)
					return 2;
				i++;
			}
	}
	}
	return 0;
}
