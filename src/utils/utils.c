/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:59:19 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/07 16:01:48 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	ft_clean( char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


static int	ft_isdigit(int a)
{
	if (a >= 48 && a <= 57)
		return (1);
	else
		return (0);
}

static int	ft_check_number(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i])
	{
		if (ft_isdigit(num[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_is_clear_number(char *str)
{	
	if (!ft_check_number(str))
	{
		ft_putstr_fd("Wrong type form of number\n", 2);
		return (1);
	}
	return 0;
}

int check_arguments(int ac)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (0);
	}
	return (1);
}