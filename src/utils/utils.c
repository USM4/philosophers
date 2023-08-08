/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:59:19 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/08 14:12:51 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_envirement(t_table *table)
{
	if (table->n_philos <= 0)
	{
		ft_putstr_fd("must be atleast one philosopher \n", 2);
		return (0);
	}
	if (table->time_to_die < 0 || table->time_to_eat < 0 \
	|| table->time_to_sleep < 0)
	{
		ft_putstr_fd("the number must be positive\n", 2);
		return (0);
	}
	return (1);
}

void	fill_structure(t_table *table, char **av)
{
	table->n_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
}

t_time	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 0)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (0);
}

void	ft_sleep(t_time num)
{
	t_time	start;

	start = current_time();
	usleep(num * 1000 * 0.85);
	while (current_time() - start < num)
		usleep(100);
}

t_philo	*create_list_philos(t_table *table)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * table->n_philos);
	if (!philos)
		return (NULL);
	while (i < table->n_philos)
	{
		philos[i].last_meal_time = current_time();
		philos[i].meal_count = 0;
		philos[i].finished = 0;
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_mutex_init(&philos[i].last_meal, NULL);
		pthread_mutex_init(&philos[i].finish, NULL);
		i++;
	}
	return (philos);
}
