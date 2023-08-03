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

void* to_app(void *arg)
{
	t_table	*table;
	int		i;
	
	table = ((t_arg *)arg)->table;
	i = ((t_arg *)arg)->philo_id;
	while (1)
	{
		printf("%d is eating\n",i);
		sleep(table->time_to_eat);
		printf("%d is sleeping\n",i);
		sleep(table->time_to_sleep);
		printf("philosopher is thinking\n");
	}
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
		philos[i].philo_id = i;
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
	while (i < table->n_philos)
	{
		t_arg arg;
		arg.table = table;
		arg.philo_id = i;
		if (pthread_create(&table->philos[i].thread_id , NULL, to_app, &arg) != 0)
		{
			perror("failed to create");
			exit(1);
		}
		if (pthread_detach(table->philos[i].thread_id) != 0)
		{
			perror("failed to detach");
			exit(1);
		}
		i++;
	}
	sleep (200);
		return (0);
}
