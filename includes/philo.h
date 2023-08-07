/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:57:17 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/07 18:51:04 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef enum orientation {FORK_TAKEN, EATING, SLEEPING, THINKING, DIED}	t_orientation;

typedef unsigned long t_time;

typedef struct s_philo {
	int 			meal_count;
	t_time			last_meal_time;
	int 			finished;
	pthread_mutex_t fork;
	pthread_mutex_t	finish;
	pthread_mutex_t last_meal;
	pthread_t 		thread_id;
}   t_philo;

typedef struct s_table {
	int		n_philos;
	t_time 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	t_orientation	task;
	int 			max_meals;
	pthread_mutex_t death;
	t_time			start_time;
	t_philo			*philos;
}       t_table;

typedef struct s_arg {
	t_table *table;
	int		philo_id;
}	t_arg;

// extern char	**ft_split(char const *s, char c);
extern int	check_is_clear_number(char *str);
extern void	ft_putstr_fd(char *s, int fd);
extern int	ft_atoi(const char *str);
extern int  check_arguments(int ac);
extern int	check_is_clear_number(char *str);
#endif
