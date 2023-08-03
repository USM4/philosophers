/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:06:48 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/03 20:08:12 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (philos.time_to_die < 0 || philos.time_to_eat < 0 || philos.time_to_sleep < 0)
	{
		ft_putstr_fd("the number must be positive\n", 2);
		return (0);
	}
	return(1);	
}

void* to_app(void *arg)
{
	t_philo *philos;

	philos = (t_philo *) arg;
	while (1)
	{
		printf("philosopher is eating\n");
		sleep(1);
		printf("philosopher is sleeping\n");
		sleep(1);
	}
}

t_llist	*create_list_philos(t_philo *philo)
{
	int i = 0;
	t_llist *head;
	
	head = NULL;
	while(i < philo->n_philos)
	{
		ft_lstadd_back(&head, ft_lstnew(i + 1));
		i++;
	}
	return(head);
}

int main(int ac,char **av)
{

	int		i;
	t_philo	philos;
	t_llist *mylist = NULL;

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
	i = 0;
	mylist = create_list_philos(&philos);


	while (i < philos.n_philos)
	{
		if (pthread_create(&philos.thread , NULL, to_app, mylist) != 0)
		{
			perror("failed to create");
			exit (1);
		}
		if (pthread_detach(philos.thread) != 0)
		{
			perror("failed to detach");
			exit (1);
		}
		i++;
	}

	// sleep(10);
	return (0);
}
