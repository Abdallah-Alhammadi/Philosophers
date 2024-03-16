/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalhamm <abalhamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:02:38 by abalhamm          #+#    #+#             */
/*   Updated: 2023/08/15 18:30:10 by abalhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	while (philo->philo_info->num_of_philo == 1)
		return (handle_single_philo(philo, philo->philo_info->time_to_die));
	while (1)
	{
		if (p_dead(philo) || !philo->times_to_eat)
			break ;
		order_of_lock(philo);
		pthread_mutex_lock(&philo->rlock);
		if (!(philo->fork) && !(philo->next->fork)
			&& philo->times_to_eat && !chk_mirr_fork(philo))
			if (!philo_eat(philo))
				return (NULL);
		pthread_mutex_unlock(&philo->rlock);
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->next->lock);
		usleep(100);
	}
	return (NULL);
}

bool	in_game_philo(t_philo *philo, int argc, char **argv)
{
	int		i;
	t_info	*philo_info;

	i = 0;
	philo_info = malloc(sizeof(t_info));
	if (!philo_info)
		return (false);
	philo_info->philo_dead = false;
	pthread_mutex_init(&philo_info->print_lock, NULL);
	pthread_mutex_init(&philo_info->dlock, NULL);
	while (i < ft_atoi(argv[1]))
	{
		philo[i].philo_info = philo_info;
		philo[i].id = i + 1;
		init_data(&philo[i], argc, argv);
		gettimeofday(&philo[i].life_t, NULL);
		philo[i].life = n_timestamp(&philo[i].life_t);
		if (i == (ft_atoi(argv[1]) - 1))
			philo[i].next = &philo[0];
		else
			philo[i].next = &philo[i + 1];
		i++;
	}
	return (true);
}

int	p_dead(t_philo *philo)
{
	long	n_time;
	int		flag;

	flag = 0;
	mutex_func(philo, 1);
	if (philo->philo_info->philo_dead)
		flag = 1;
	else
	{
		n_time = n_timestamp(&philo->life_t);
		if ((n_time - philo->life) > (philo->philo_info->time_to_die))
		{
			mutex_func(philo, 0);
			print_data(philo, 5);
			mutex_func(philo, 1);
			philo->philo_info->philo_dead = true;
			flag = 1;
		}
	}
	mutex_func(philo, 0);
	return (flag);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;

	if (!ft_error(argc, argv))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (1);
	if (!in_game_philo(philo, argc, argv))
		return (1);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&philo[i].thread, NULL, p_routine, (void *)&philo[i]);
		usleep(100);
		i++;
	}
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(philo[i].thread, NULL);
	free(philo->philo_info);
	free(philo);
	return (0);
}
