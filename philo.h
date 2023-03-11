/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:59:08 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/11 21:58:20 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILO_H
#define FILO_H

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>

typedef struct philo
{
	int number_of_philosophers;
	int number_of_fork;
	unsigned long time_to_die;
	int number_of_times_each_philosopher_must_eat;
	int fork_left;
	int fork_right;
	int cont;
	unsigned long time_strat;
	unsigned long time_last;
	int time_to_eat;
	int id;
	pthread_t *philosopher;
	pthread_mutex_t *fork_d;
	pthread_mutex_t *print;
	pthread_mutex_t cont_mutex;
	unsigned long time_to_sleep;
	int number_temp;
}t_data;

unsigned long	get_time(void);
void ft_usleep(unsigned long time_sleep);
int	ft_checkeat(int *a, int n);
void ft_initialisation(int ac, char **argv, t_data *info_p);
int	ft_atoi(char *str);
t_data *allocatin(t_data *info_p,int size_of_allocation);

#endif
