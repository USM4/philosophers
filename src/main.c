/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:59:23 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/08 14:00:37 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	executing_tasks(t_table *table, int index, t_tasks task)
{
	if (task == FORK_TAKEN)
	{
		pthread_mutex_lock(&table->philos[index].fork);
		pthread_mutex_lock(&table->death);
		printf("%lu %d has taken a fork\n", current_time() - \
		table->start_time, index + 1);
		pthread_mutex_unlock(&table->death);
		pthread_mutex_lock(&table->philos[(index + 1) % table->n_philos].fork);
		pthread_mutex_lock(&table->death);
		printf("%lu %d has taken a fork\n", current_time() - \
		table->start_time, index + 1);
		pthread_mutex_unlock(&table->death);
	}
	else if (task == EATING)
	{
		pthread_mutex_lock(&table->death);
		printf("%lu %d is eating\n", current_time() - \
		table->start_time, index + 1);
		pthread_mutex_unlock(&table->death);
		pthread_mutex_lock(&table->philos[index].last_meal);
		table->philos[index].last_meal_time = current_time();
		pthread_mutex_unlock(&table->philos[index].last_meal);
	}
}

void	executing_tasks_2(t_table *table, int index, t_tasks task)
{
	if (task == SLEEPING)
	{
		pthread_mutex_lock(&table->death);
		printf("%lu %d is sleeping\n", current_time() - \
		table->start_time, index + 1);
		pthread_mutex_unlock(&table->death);
	}
	else if (task == THINKING)
	{
		pthread_mutex_lock(&table->death);
		printf("%lu %d is thinking\n", current_time() - \
		table->start_time, index + 1);
		pthread_mutex_unlock(&table->death);
	}
}

void	*to_app(void *arg)
{
	t_table	*table;
	t_arg	*argument;
	int		i;

	argument = (t_arg *)arg;
	table = argument->table;
	i = argument->philo_id;
	if ((i + 1) % 2 != 0)
		usleep(200);
	while (1)
	{
		executing_tasks(table, i, FORK_TAKEN);
		executing_tasks(table, i, EATING);
		ft_sleep(table->time_to_eat);
		table->philos[i].meal_count++;
		pthread_mutex_unlock(&table->philos[i].fork);
		pthread_mutex_unlock(&table->philos[(i + 1) % table->n_philos].fork);
		if (confirm_philosopher_death(table, i) == 1)
			break ;
		executing_tasks_2(table, i, SLEEPING);
		ft_sleep(table->time_to_sleep);
		executing_tasks_2(table, i, THINKING);
	}
	return (NULL);
}

void	monitor_progress(t_table *table)
{
	int	i;
	int	flag;

	while (1)
	{
		i = 0;
		if (check_death(table) == 1)
			break ;
		flag = 0;
		while (i < table->n_philos)
		{
			pthread_mutex_lock(&table->philos[i].finish);
			if (table->philos[i].finished == 1)
				flag++;
			pthread_mutex_unlock(&table->philos[i].finish);
			i++;
		}
		if (table->n_philos == flag)
			break ;
	}
	freeing(table);
}

int	main(int ac, char **av)
{
	t_table	*table;
	t_arg	*arg;

	if (check_arguments(ac, av) == 1)
		return (1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	fill_structure(table, av);
	if (!check_envirement(table))
		return (free(table), 1);
	pthread_mutex_init(&table->death, NULL);
	if (check_the_optional_argument(ac, av, table) == 1)
		return (free(table), 1);
	table->philos = create_list_philos(table);
	table->start_time = current_time();
	arg = malloc(sizeof(t_arg) * table->n_philos);
	if (!arg)
		return (1);
	create_and_launch(table, arg);
	free(arg);
	monitor_progress(table);
	return (0);
}
