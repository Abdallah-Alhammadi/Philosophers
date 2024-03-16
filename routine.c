/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalhamm <abalhamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:02:28 by abalhamm          #+#    #+#             */
/*   Updated: 2023/08/15 18:14:23 by abalhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*handle_single_philo(t_philo *philo, int ttime)
{
	size_t	ts;
	size_t	target;
	long	n_time;

	ts = timestamp_n();
	target = ts + (ttime * 1000);
	while (ts < target)
	{
		n_time = n_timestamp(&philo->life_t);
		if ((n_time - philo->life) > (philo->philo_info->time_to_die))
			break ;
		ts = timestamp_n();
	}
	print_data(philo, 5);
	return (NULL);
}

bool	sleep_philo(t_philo *philo)
{
	size_t	ts;
	size_t	target;

	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->next->lock);
	ts = timestamp_n();
	target = ts + (philo->philo_info->time_to_sleep * 1000);
	while (ts < target)
	{
		if (p_dead(philo))
			return (false);
		usleep(100);
		ts = timestamp_n();
	}
	if (philo->id % philo->philo_info->num_of_philo)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->next->lock);
	}
	else
	{
		pthread_mutex_lock(&philo->next->lock);
		pthread_mutex_lock(&philo->lock);
	}
	return (true);
}

bool	sleep_time(t_philo *philo, int khana_time)
{
	size_t	ts;
	size_t	target;

	ts = timestamp_n();
	target = ts + (khana_time * 1000);
	while (ts < target)
	{
		if (p_dead(philo))
			return (false);
		usleep(100);
		ts = timestamp_n();
	}
	return (true);
}

void	print_data(t_philo *philo, int print_order)
{
	mutex_func(philo, 1);
	if (!philo->philo_info->philo_dead)
	{
		pthread_mutex_lock(&philo->philo_info->print_lock);
		ft_putnbr(n_timestamp(&philo->life_t));
		ft_putchar(' ');
		ft_putnbr(philo->id);
		if (print_order == 1)
			ft_putstr(" has taken a fork\n");
		else if (print_order == 2)
			ft_putstr(" is eating\n");
		else if (print_order == 3)
			ft_putstr(" is sleeping\n");
		else if (print_order == 4)
			ft_putstr(" is thinking\n");
		else if (print_order == 5)
		{
			ft_putstr(" died\n");
			philo->philo_info->philo_dead = true;
		}
		pthread_mutex_unlock(&philo->philo_info->print_lock);
	}
	mutex_func(philo, 0);
}

bool	philo_eat(t_philo *philo)
{
	philo->fork = 1;
	philo->next->fork = 1;
	philo->m_fork = philo->id;
	philo->next->m_fork = philo->id;
	philo->life = n_timestamp(&philo->life_t);
	pthread_mutex_unlock(&philo->rlock);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->next->lock);
	print_data(philo, 1);
	print_data(philo, 1);
	print_data(philo, 2);
	philo->times_to_eat--;
	if (!sleep_time(philo, philo->philo_info->time_to_eat))
		return (false);
	order_of_lock(philo);
	philo->fork = 0;
	philo->next->fork = 0;
	if (end_t_eat(philo))
		return (false);
	print_data(philo, 3);
	if (!sleep_philo(philo))
		return (false);
	print_data(philo, 4);
	pthread_mutex_lock(&philo->rlock);
	return (true);
}
