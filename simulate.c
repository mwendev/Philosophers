/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:20:17 by mwen              #+#    #+#             */
/*   Updated: 2021/11/29 03:37:13 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	int	i;

	i = philo->p->philo;
	pthread_mutex_lock(philo->p->fork[philo->id]);
	print_action(philo, "has taken a fork", philo->p->someone_died);
	pthread_mutex_lock(philo->p->fork[(philo->id + 1) % i]);
	print_action(philo, "has taken a fork", philo->p->someone_died);
	philo->last_eat = get_time(philo->p);
	print_action(philo, "is eating", philo->p->someone_died);
	if (!philo->p->must_eat)
		--philo->eaten;
	else
		++philo->eaten;
	if (philo->p->die < philo->p->eat)
		usleep(philo->p->die * 1000);
	else
		usleep(philo->p->eat * 1000);
	pthread_mutex_unlock(philo->p->fork[philo->id]);
	pthread_mutex_unlock(philo->p->fork[(philo->id + 1) % i]);
}

void	*simulate(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->eaten <= philo->p->must_eat && !philo->p->someone_died)
	{
		print_action(philo, "is thinking", philo->p->someone_died);
		eat(philo);
		print_action(philo, "is sleeping", philo->p->someone_died);
		if (philo->p->die < philo->p->eat + philo->p->sleep)
			usleep((philo->p->die - philo->p->eat) * 1000);
		else
			usleep(philo->p->sleep * 1000);
	}
	return (philo);
}
