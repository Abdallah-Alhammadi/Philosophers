/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_mutex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalhamm <abalhamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:02:25 by abalhamm          #+#    #+#             */
/*   Updated: 2023/08/15 18:31:04 by abalhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	order_of_lock(t_philo *philo)
{
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
}

void	mutex_func(t_philo *philo, int lock_flag)
{
	if (lock_flag)
		pthread_mutex_lock(&philo->philo_info->dlock);
	else
		pthread_mutex_unlock(&philo->philo_info->dlock);
}

long	n_timestamp(struct timeval *time)
{
	struct timeval	c_time;
	long			res;

	gettimeofday(&c_time, NULL);
	res = ((c_time.tv_sec - time->tv_sec) * 1000) + ((c_time.tv_usec
				- time->tv_usec) / 1000);
	return (res);
}

size_t	timestamp_n(void)
{
	struct timeval	c_time;
	size_t			time;

	gettimeofday(&c_time, NULL);
	time = (c_time.tv_sec * 1000000 + c_time.tv_usec);
	return (time);
}
