#ifndef PHILO_H
#define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <pthread.h>

typedef struct s_philo {
	int 		meal_count;
	pthread_mutex_t fork;
	pthread_t 	thread_id;
	int		philo_id;
}   t_philo;

typedef struct s_table {
	int		n_philos;
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		max_meals;
	t_philo		*philos;
}       t_table;

typedef struct s_arg {
	t_table *table;
	int	philo_id;
}	t_arg;

// extern char	**ft_split(char const *s, char c);
// extern void	ft_putstr_fd(char *s, int fd);
extern int	ft_atoi(const char *str);
// extern int	ft_lstsize(t_table *lst);
// extern void	ft_lstclear(t_table **lst);
// extern void	ft_lstadd_back(t_table **lst, t_table *new);
// extern t_table	*ft_lstnew(int nbr);
// extern t_table	*ft_lstlast(t_table *lst);
// extern int      check_arguments(int ac);
// extern int	check_is_clear_number(char *str);

#endif