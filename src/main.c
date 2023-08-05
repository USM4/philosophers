/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:59:23 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/05 04:03:40 by oredoine         ###   ########.fr       */
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
	if (philos.time_to_die < 0 || philos.time_to_eat < 0 || philos.time_to_ft_sleep < 0)
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
	usleep(num * 1000);
}

void	 *to_app(void *arg)
{
	t_table *table;
	t_arg *argument;
	argument = (t_arg *)arg;
	table = argument->table;
	int i = argument->philo_id;
	if (argument->philo_id % 2 != 0)
		ft_sleep(2);
	while (1)
	{
		pthread_mutex_lock(&table->philos[i].fork);
		printf("%lu : %d has taken a fork\n", current_time() - table->start_time, i + 1);
		if (i == table->n_philos)
			pthread_mutex_lock(&table->philos[0].fork); 
		else
			pthread_mutex_lock(&table->philos[i + 1].fork);
		printf("%lu : %d has taken a fork\n",current_time() - table->start_time, i + 1);
		printf("%lu : %d is eating\n",current_time() - table->start_time, i + 1);
		table->philos[i].meal_count++;
		table->philos[i].last_meal_time = current_time() - table->start_time;
		ft_sleep(table->time_to_eat);
		pthread_mutex_unlock(&table->philos[i].fork);
		if (i == table->n_philos)
			pthread_mutex_unlock(&table->philos[0].fork);
		else
			pthread_mutex_unlock(&table->philos[i + 1].fork);
		if (table->max_meals > 0 && table->philos[i].meal_count >= table->max_meals)
		{
			printf("%lu : %d is finish\n",current_time() - table->start_time, i + 1);
			break ;
		}
		printf("%lu : %d is sleeping\n",current_time() - table->start_time, i + 1);
		ft_sleep(table->time_to_ft_sleep);
		printf("%lu : %d is thinking\n",current_time() - table->start_time, i + 1);
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
		philos[i].meal_count = 0;
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
	i = 0;
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
	table->n_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_ft_sleep = ft_atoi(av[4]);
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
	t_arg *arg = malloc(sizeof(t_arg));
	arg->table = table;
	while (i < table->n_philos)
	{
		arg->philo_id = i;
		if (pthread_create(&table->philos[i].thread_id , NULL, to_app, arg) != 0)
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
	// ft_sleep(2);
	i = 0;
	while (1)
	{
		if ((i + 1) == table->n_philos)
			i = 0;
		if(table->time_to_die < (current_time() - table->philos[i].last_meal_time))
		{
			printf("%lu : %d died\n", (current_time() - table->start_time), i + 1);
			break;
		}
		i++;
		ft_sleep(2);
	}
	// sleep(200);
	return (0);
}
