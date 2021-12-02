/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:21:57 by mwen              #+#    #+#             */
/*   Updated: 2021/12/02 18:37:44 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int					id;
	int					eaten;
	double				last_eat;
	pthread_t			thread;
	struct s_param		*p;
}						t_philo;

typedef struct s_param
{
	struct timeval		start;
	int					philo;
	int					die;
	int					eat;
	int					sleep;
	int					must_eat;
	int					someone_died;
	t_philo				**phdata;
	pthread_mutex_t		**fork;
	pthread_mutex_t		print;
}						t_param;

int		init_param(t_param *p, int argc, char **argv);
int		init_fork(t_param *p);
int		init_philo(t_param *p);
int		check_input(t_param *p, int argc, char **argv);
double	get_time(t_param *p);
void	*simulate(void *arg);
void	print_action(t_philo *philo, char *str, int someone_died);

#endif