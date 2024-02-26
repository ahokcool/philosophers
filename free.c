/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:39:45 by astein            #+#    #+#             */
/*   Updated: 2023/08/10 15:51:15 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	put_extra_msg(&table->m_print, "free table: ...\n", CLR_ORANGE);
	free_philos(table);
	pthread_mutex_destroy(&table->m_started);
	pthread_mutex_destroy(&table->m_ended);
	pthread_mutex_destroy(&table->m_print);
	free(table);
	put_extra_msg(NULL, "free table: OK\n", CLR_GREEN);
}

void	free_philos(t_table *table)
{
	int		i;
	t_philo	*cur_philo;
	t_philo	*next_philo;

	put_extra_msg(&table->m_print, "free_philos: ...\n", CLR_ORANGE);
	i = 1;
	while (table->philos && i <= table->num_philos)
	{
		cur_philo = table->philos;
		next_philo = cur_philo->right_philo;
		free_philo(cur_philo);
		free(cur_philo);
		cur_philo = NULL;
		table->philos = next_philo;
		i++;
	}
	put_extra_msg(&table->m_print, "free_philos: OK\n", CLR_GREEN);
}

void	free_philo(t_philo *philo)
{
	pthread_mutex_destroy(&philo->m_philo);
	pthread_mutex_destroy(&philo->m_fork);
}
