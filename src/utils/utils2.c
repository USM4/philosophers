/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:41:26 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/08 14:31:32 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	confirm_philosopher_death(t_table *table, int i)
{
	if (table->max_meals > 0 && table->philos[i].meal_count >= table->max_meals)
	{
		pthread_mutex_lock(&table->death);
		pthread_mutex_lock(&table->philos[i].finish);
		table->philos[i].finished = 1;
		pthread_mutex_unlock(&table->philos[i].finish);
		pthread_mutex_unlock(&table->death);
		return (1);
	}
	return (0);
}

int	check_the_optional_argument(int ac, char **av, t_table *table)
{
	if (ac == 6)
	{
		table->max_meals = ft_atoi(av[5]);
		if (table->max_meals <= 0)
		{
			ft_putstr_fd("number of meals must be at least 1.\n", 2);
			return (1);
		}
	}
	else
		table->max_meals = -1;
	return (0);
}

void	create_and_launch(t_table *table, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		arg[i].table = table;
		arg[i].philo_id = i;
		if (pthread_create(&table->philos[i].thread_id, \
		NULL, to_app, arg + i) != 0)
		{
			ft_putstr_fd("failed to create", 2);
			return ;
		}
		if (pthread_detach(table->philos[i].thread_id) != 0)
		{
			ft_putstr_fd("failed to detach", 2);
			return ;
		}
		i++;
	}
}

void	destroy_philos_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->philos[i].fork);
		pthread_mutex_destroy(&table->philos[i].last_meal);
		i++;
	}
}

int	check_death(t_table *table)
{
	int		i;
	t_time	tmp;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_lock(&table->philos[i].last_meal);
		tmp = current_time() - table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->philos[i].last_meal);
		if (table->time_to_die <= (int)tmp)
		{
			pthread_mutex_lock(&table->death);
			printf("%lu %d died\n", current_time() - table->start_time, i + 1);
			destroy_philos_mutexes(table);
			pthread_mutex_destroy(&table->death);
			return (1);
		}
		i++;
	}
	return (0);
}
