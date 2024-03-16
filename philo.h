/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalhamm <abalhamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:02:42 by abalhamm          #+#    #+#             */
/*   Updated: 2023/08/15 18:11:45 by abalhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct info
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			philo_dead;
	int				num_of_philo;
	pthread_mutex_t	dlock;
	pthread_mutex_t	print_lock;
}	t_info;

typedef struct philo
{
	int				id;
	int				fork;
	int				m_fork;
	long			life;
	int				times_to_eat;
	pthread_t		thread;
	pthread_mutex_t	lock;
	pthread_mutex_t	rlock;
	struct timeval	start_t;
	struct timeval	life_t;
	struct info		*philo_info;
	struct philo	*next;
}	t_philo;

int		*handle_single_philo(t_philo *philo, int ttime);
long	n_timestamp(struct timeval *time);
bool	in_game_philo(t_philo *philo, int argc, char **argv);
void	init_data(t_philo *philo, int argc, char **argv);
void	print_data(t_philo *philo, int print_order);
size_t	timestamp_n(void);
void	mutex_func(t_philo *philo, int lock_flag);
bool	philo_eat(t_philo *philo);
int		p_dead(t_philo *philo);
bool	end_t_eat(t_philo *philo);
bool	chk_mirr_fork(t_philo *philo);
void	order_of_lock(t_philo *philo);
void	ft_putstr(char *s);
size_t	ft_strlen(const char *s);
void	print_data(t_philo *philo, int print_order);
bool	in_game_philo(t_philo *philo, int argc, char **argv);
bool	ft_error(int argc, char **argv);
void	ft_putchar(char c);
void	ft_putnbr(int n);
int		ft_atoi(const char	*str);

#endif