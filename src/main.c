/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:59:23 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/04 05:48:55 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_envirement(t_table philos)
// {
// 	if(philos.max_meals <= 0)
// 	{
// 		ft_putstr_fd("must be atleast the number one \n", 2);
// 		return(0);
// 	}
// 	if(philos.n_philos <= 0)
// 	{
// 		ft_putstr_fd("must be atleast one philosopher \n", 2);
// 		return(0);
// 	}
// 	if (philos.time_to_die < 0 || philos.time_to_eat < 0 || philos.time_to_sleep < 0)
// 	{
// 		ft_putstr_fd("the number must be positive\n", 2);
// 		return (0);
// 	}
// 	return(1);	
// }

void	 *to_app(void *arg)
{
	int	count_meals;
	t_table *ta;
	t_arg *argument;
	argument = (t_arg *)arg;
	ta = argument->table;
	int i = argument->philo_id;
	int flg = argument->flag;
	if (argument->philo_id % 2 != 0)
		sleep(2);
	count_meals = 0;
	while (1)
	{
		pthread_mutex_lock(&ta->philos[i].fork);
		printf("%d has taken a fork\n",i + 1);
		if (i == ta->n_philos)
			pthread_mutex_lock(&ta->philos[0].fork);
		else
			pthread_mutex_lock(&ta->philos[i + 1].fork);
		printf("%d has taken a fork\n",i + 1);
		printf("%d is eating\n",i + 1);
		sleep(ta->time_to_eat);
		pthread_mutex_unlock(&ta->philos[i].fork);
		if (i == ta->n_philos)
			pthread_mutex_unlock(&ta->philos[0].fork);
		else
			pthread_mutex_unlock(&ta->philos[i + 1].fork);
		count_meals++;
		if (count_meals >= ta->max_meals)
		{
			printf("%d is finish\n",i + 1);
			flg++;
			break ;
		}
		printf("%d is sleeping\n",i + 1);
		sleep(ta->time_to_sleep);
		printf("%d is thinking\n", i + 1);
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
	while(i < table->n_philos)
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
	table->n_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->max_meals = ft_atoi(av[5]);
	else
		table->max_meals = 1;
	table->philos = create_list_philos(table);
	while (i < table->n_philos)
	{
		t_arg *arg = malloc(sizeof(t_arg));
		arg->table = table;
		arg->philo_id = i;
		arg->flag = 0;
		if (pthread_create(&table->philos[i].thread_id , NULL, to_app, arg) != 0)
		{
			perror("failed to create");
			exit(1);
		}
		// if dead or finish
		// while(1)
		// {
		// 	if(arg->flag != 0)
		// 		printf("%d died\n", arg->philo_id);
		// }
		if (pthread_detach(table->philos[i].thread_id) != 0)
		{
			perror("failed to detach");
			exit(1);
		}
		i++;
	}
		return (0);
}
