/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:59:38 by mwen              #+#    #+#             */
/*   Updated: 2021/12/02 18:37:31 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	terminate(t_param *p, int ret, int fork, int pdata)
{
	int	i;

	i = -1;
	while (++i < p->philo)
	{
		if (i < fork)
		{
			pthread_mutex_destroy(p->fork[i]);
			free(p->fork[i]);
		}
		if (i < pdata)
			free(p->phdata[i]);
	}
	pthread_mutex_destroy(&p->print);
	free(p->fork);
	free(p->phdata);
	free(p);
	return (ret);
}

int	check_alive(t_param *p, int i)
{
	double	now;

	now = get_time(p);
	if (now - p->phdata[i]->last_eat >= p->die)
		return (0);
	else
		return (1);
}

void	check_death(t_param *p)
{
	int				i;
	int				j;
	pthread_mutex_t	stop;

	while (1)
	{
		i = -1;
		j = 0;
		while (++i < p->philo)
		{
			if (p->must_eat && p->phdata[i]->eaten == p->must_eat)
				++j;
			if (j == p->philo)
				return ;
			if (!check_alive(p, i))
			{
				pthread_mutex_lock(&stop);
				p->someone_died = 1;
				print_action(p->phdata[i], "died", 0);
				return ;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_param	*p;
	int		ret;

	p = malloc(sizeof(t_param));
	if (!p)
		return (-1);
	ret = init_param(p, argc, argv);
	if (ret < 0)
		return (terminate(p, ret, 0, 0));
	if (p->die < p->philo)
	{
		printf("Time to die shouldn't be smaller than the number of philo.\n");
		return (terminate(p, -5, 0, 0));
	}
	ret = init_fork(p);
	if (ret)
		return (terminate(p, -6, ret, 0));
	ret = init_philo(p);
	if (ret)
		return (terminate(p, -7, p->philo, ret));
	check_death(p);
	return (terminate(p, 1, p->philo, p->philo));
}
