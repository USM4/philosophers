/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:05:24 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/01 23:23:23 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

extern char	**ft_split(char const *s, char c);
extern void	ft_putstr_fd(char *s, int fd);
extern int	ft_atoi(const char *str);

typedef struct s_philo{
        int n_philos;
        int time_to_die;
        int time_to_eat;
        int time_to_sleep;
        int n_t_e_p_m_e;
}   t_philo;


#endif