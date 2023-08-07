/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:59:23 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/07 01:03:09 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_envirement(t_table philos)
{
	if(philos.n_philos <= 0)
	{
		ft_putstr_fd("must be atleast one philosopher \n", 2);
		return(0);
	}
	if (philos.time_to_die < 0 || philos.time_to_eat < 0 || philos.time_to_sleep < 0)
	{
		ft_putstr_fd("the number must be positive\n", 2);
		return (0);
	}
	return(1);
}

t_time current_time(void)
{
	struct timeval time;
    if (gettimeofday(&time, NULL) == 0)
		return((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return(0);
}

void ft_sleep(t_time num)
{
	t_time	start;

	start = current_time();
	usleep(num * 1000 * 0.85);
	while (current_time() - start < num)
		usleep(100);
}

void	 *to_app(void *arg)
{
	t_table *table;
	t_arg *argument;
	argument = (t_arg *)arg;
	table = argument->table;
	int i = argument->philo_id;
	if ((i + 1) % 2 != 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&table->philos[i].fork);
		pthread_mutex_lock(&table->death);
		printf("%lu : %d has taken a fork\n", current_time() - table->start_time, i + 1);
		pthread_mutex_unlock(&table->death);
		pthread_mutex_lock(&table->philos[(i + 1) % table->n_philos].fork);
		pthread_mutex_lock(&table->death);
		printf("%lu : %d has taken a fork\n", current_time() - table->start_time, i + 1);
		pthread_mutex_unlock(&table->death);
		pthread_mutex_lock(&table->death);
		printf("%lu : %d is eating\n", current_time() - table->start_time, i + 1);
		pthread_mutex_unlock(&table->death);
		table->philos[i].last_meal_time = current_time();
		ft_sleep(table->time_to_eat);
		table->philos[i].meal_count++;
		pthread_mutex_unlock(&table->philos[i].fork);
		pthread_mutex_unlock(&table->philos[(i + 1) % table->n_philos].fork);
		if (table->max_meals > 0 && table->philos[i].meal_count >= table->max_meals)
		{
			pthread_mutex_lock(&table->death);
			printf("%lu : %d is finish\n", current_time() - table->start_time, i + 1);
			table->philos[i].finished = 1;
			pthread_mutex_unlock(&table->death);
			break ;
		}
		pthread_mutex_lock(&table->death); 
		printf("%lu : %d is sleeping\n", current_time() - table->start_time, i + 1);
		pthread_mutex_unlock(&table->death);
		ft_sleep(table->time_to_sleep);
		pthread_mutex_lock(&table->death);
		printf("%lu : %d is thinking\n", current_time() - table->start_time, i + 1);
		pthread_mutex_unlock(&table->death);
	}
	return (NULL);
}

t_philo	*create_list_philos(t_table *table)
{
	int i = 0;
	t_philo *philos;

	philos = malloc(sizeof(t_philo) * table->n_philos);
	if (!philos)
		return (NULL);
	while (i < table->n_philos)
	{
		philos[i].last_meal_time = current_time();
		philos[i].meal_count = 0;
		philos[i].finished = 0;
		pthread_mutex_init(&philos[i].fork, NULL);
		i++;
	}
	return (philos);
}

int main(int ac,char **av)
{
	int		i;
	// t_philo	philos;
	t_table *table;
	// int setter = 0;
	// if (!check_arguments(ac))
	// 	return (1);
	// while (i < ac)
	// {
	// 	if (check_is_clear_number(av[i]) == 1)
	// 		break;
	// 	i++;
	// }
	// fill_struct(&philos, av, ac);
	// if (!check_envirement(philos))
	// 	return(1);
	table = malloc(sizeof(t_table));
	// if (!table)
	// 	return(1);
	pthread_mutex_init(&table->death, NULL);
	table->n_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);

	if (ac == 6)
	{
		table->max_meals = ft_atoi(av[5]);
		if(table->max_meals <= 0)
		{
			ft_putstr_fd("must be atleast the number one \n", 2);
			return(1);
		}
	}
	else
		table->max_meals = -1;
	table->philos = create_list_philos(table);
	table->start_time = current_time();
	t_arg *arg = malloc(sizeof(t_arg) * table->n_philos);
	
	i = 0;
	while (i < table->n_philos)
	{
		arg[i].table = table;
		arg[i].philo_id = i;
		if (pthread_create(&table->philos[i].thread_id , NULL, to_app, arg + i) != 0)
		{
			perror("failed to create");
			exit(1);
		}
		// if dead or finish
		if (pthread_detach(table->philos[i].thread_id) != 0)
		{
			perror("failed to detach");
			exit(1);
		}
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < table->n_philos)
		{
			if (table->time_to_die <= (current_time() - table->philos[i].last_meal_time))
			{
				pthread_mutex_lock(&table->death);
				printf("%lu : %d died\n", current_time() - table->start_time, i + 1);
				return (0);
			}
			i++;
		}
		i = 0;
		int flag = 0;
		while (i < table->n_philos)
		{
			if (table->philos[i].finished == 1)
				flag++;
			i++;
		}
		if (table->n_philos == flag)
			break;
	}
	return (0);
}
