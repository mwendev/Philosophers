/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:10:32 by mwen              #+#    #+#             */
/*   Updated: 2021/11/28 22:20:25 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	nb_to_p(t_param *p, int i, int nb)
{
	if (i == 1)
		p->philo = nb;
	else if (i == 2)
		p->die = nb;
	else if (i == 3)
		p->eat = nb;
	else if (i == 4)
		p->sleep = nb;
	p->must_eat = 0;
	if (i == 5)
		p->must_eat = nb;
}

int	ft_atoi(char *str)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (!str)
		return (-1);
	while (str[++i])
		if (str[i] > '9' || str[i] < '0' )
			return (-1);
	while (*str)
	{
		ret *= 10;
		ret += *str - '0';
		str++;
	}
	if (ret <= 2147483647)
		return (ret);
	else
		return (-1);
}

int	check_input(t_param *p, int argc, char **argv)
{
	int	i;
	int	nb;

	i = 0;
	if (argc < 5 || argc > 6)
		return (printf("Wrong input\n"));
	while (argv[++i])
	{
		nb = ft_atoi(argv[i]);
		if (nb < 0)
			return (printf("Please use positive integers as arguments\n"));
		else if (nb == 0)
			return (printf("Come on, zero?\n"));
		else
			nb_to_p(p, i, nb);
	}
	return (1);
}
