/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:06:48 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/02 09:51:06 by oredoine         ###   ########.fr       */
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

int check_arguments(int ac)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (0);
	}
	return (1);
}

int	ft_isdigit(int a)
{
	if (a >= 48 && a <= 57)
		return (1);
	else
		return (0);
}

int	ft_check_number(char *num)
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

void fill_struct(t_philo *philos, char **av, int ac)
{
	philos->n_philos = ft_atoi(av[1]);
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philos->n_t_e_p_m_e = ft_atoi(av[5]);
	else
		philos->n_t_e_p_m_e = 1;
}

int	check_envirement(t_philo philos)
{

	if(philos.n_t_e_p_m_e <= 0)
	{
		ft_putstr_fd("must be atleast the number one \n", 2);
		return(0);
	}
	if(philos.n_philos <= 0)
	{
		ft_putstr_fd("must be atleast one philosopher \n", 2);
		return(0);
	}
	 if (philos.time_to_die < 0 || philos.time_to_eat < 0 
		|| philos.time_to_sleep < 0)
	{
		ft_putstr_fd("the number must be positive\n", 2);
		return (0);
	}
	return(1);	
}

int main(int ac,char **av)
{

	int		i;
	t_philo	philos;

	i = 1;
	if (!check_arguments(ac))
		return (1);
	while (i < ac)
	{
		if (check_is_clear_number(av[i]) == 1)
			break;
		i++;
	}
	fill_struct(&philos, av, ac);
	if(!check_envirement(philos))
		return(1);

	while (1)
	{
	}
	return (0);
}
