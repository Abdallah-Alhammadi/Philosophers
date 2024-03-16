/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_utils_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalhamm <abalhamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:27:12 by abalhamm          #+#    #+#             */
/*   Updated: 2023/08/15 18:30:38 by abalhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char	*str)
{
	unsigned int	num;
	int				count_minus;

	num = 0;
	count_minus = 1;
	while (*str == ' ' || (*str >= 19 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			count_minus = -count_minus;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (num > 2147483648 && count_minus == -1)
		return (0);
	if ((num > 2147483647 && count_minus == 1)
		|| (*str || (str[0] == '+' && !str[1]) || (str[0] == '-' && !str[1])))
		return (-1);
	str = NULL;
	return (num * count_minus);
}

void	ft_putnbr(int n)
{
	char	i;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	i = (n % 10) + '0';
	write(1, &i, 1);
}
