/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:05:24 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/03 10:15:02 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <pthread.h>

typedef struct s_philo{
        int n_philos;
        //philo id
        int time_to_die;
        int time_to_eat;
        int time_to_sleep;
        int n_t_e_p_m_e;
        pthread_t thread;
        
}   t_philo;

typedef struct s_llist {
        pthread_mutex_t         fork;
        unsigned long long      time_eat;
        struct s_llist           *next;
        int                     nbr;
        t_philo philos;
        
}       t_llist;


extern char	**ft_split(char const *s, char c);
extern void	ft_putstr_fd(char *s, int fd);
extern int	ft_atoi(const char *str);
extern int	ft_lstsize(t_llist *lst);
extern void	ft_lstclear(t_llist **lst);
extern void	ft_lstadd_back(t_llist **lst, t_llist *new);
extern t_llist	*ft_lstnew(int nbr);
extern t_llist	*ft_lstlast(t_llist *lst);
extern int      check_arguments(int ac);
extern int	check_is_clear_number(char *str);

#endif