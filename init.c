/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:46:25 by mwen              #+#    #+#             */
/*   Updated: 2021/11/29 03:04:03 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_param *p)
{
	int	i;

	i = -1;
	while (++i < p->philo)
	{
		p->phdata[i] = malloc(sizeof(t_philo));
		if (!p->phdata[i])
			return (i);
		p->phdata[i]->id = i;
		p->phdata[i]->eaten = 0;
		p->phdata[i]->last_eat = 0;
		p->phdata[i]->p = p;
		pthread_create(&p->phdata[i]->thread, NULL, simulate, p->phdata[i]);
		usleep(500);
	}
	return (0);
}

int	init_fork(t_param *p)
{
	int	i;

	i = -1;
	while (++i < p->philo)
	{
		p->fork[i] = malloc(sizeof(pthread_mutex_t));
		if (!p->fork[i])
			return (i);
		pthread_mutex_init(p->fork[i], NULL);
	}
	return (0);
}

int	init_param(t_param *p, int argc, char **argv)
{
	int	i;

	p->phdata = NULL;
	p->fork = NULL;
	if (check_input(p, argc, argv) != 1)
		return (-2);
	gettimeofday(&p->start, NULL);
	p->phdata = malloc(p->philo * sizeof(t_philo *));
	if (!p->phdata)
		return (-3);
	p->fork = malloc(p->philo * sizeof(pthread_mutex_t));
	if (!p->fork)
		return (-4);
	i = -1;
	while (++i < p->philo)
	{
		p->phdata[i] = NULL;
		p->fork[i] = NULL;
	}
	pthread_mutex_init(&p->print, NULL);
	p->someone_died = 0;
	return (1);
}
