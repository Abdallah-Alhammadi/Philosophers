/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_the_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalhamm <abalhamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:02:17 by abalhamm          #+#    #+#             */
/*   Updated: 2023/08/15 18:30:22 by abalhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_philo *philo, int argc, char **argv)
{
	philo->fork = 0;
	philo->m_fork = 0;
	philo->philo_info->time_to_die = ft_atoi(argv[2]);
	philo->philo_info->time_to_eat = ft_atoi(argv[3]);
	philo->philo_info->time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&philo->lock, NULL);
	pthread_mutex_init(&philo->rlock, NULL);
	philo->philo_info->num_of_philo = ft_atoi(argv[1]);
	if (argc == 6)
		philo->times_to_eat = ft_atoi(argv[5]);
	else
		philo->times_to_eat = -1;
}

bool	chk_mirr_fork(t_philo *philo)
{
	if (philo->m_fork == philo->id || philo->next->m_fork == philo->id)
		return (true);
	return (false);
}

bool	end_t_eat(t_philo *philo)
{
	if (philo->times_to_eat == 0)
	{
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->next->lock);
		return (true);
	}
	return (false);
}

bool	ft_error(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) > 200)
	{
		ft_putstr("Error : Run philo using ./philo 2 800 200 200 \
					((7) -- optional)");
		return (false);
	}
	i = 1;
	while (argv[i])
	{
		if (*argv[i] == '\0' || ft_atoi(argv[i]) <= 0)
		{
			ft_putstr("Error : Run philo using ./philo 2 800 200 200 \
						((7) --- optional)");
			return (false);
		}
		i++;
	}
	return (true);
}
