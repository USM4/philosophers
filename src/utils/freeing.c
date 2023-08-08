/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:15:29 by oredoine          #+#    #+#             */
/*   Updated: 2023/08/08 02:16:01 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeing(t_table *table)
{
	destroy_philos_mutexes(table);
	pthread_mutex_destroy(&table->death);
	free(table);
	free(table->philos);
}
