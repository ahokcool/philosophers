/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:05:45 by astein            #+#    #+#             */
/*   Updated: 2023/08/05 23:50:37 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ini_table(t_table *table, int argc, char **argv)
{
	pthread_mutex_init(&table->m_print, NULL);
	pthread_mutex_init(&table->m_started, NULL);
	pthread_mutex_init(&table->m_ended, NULL);
	set_dinner_start(table, FALSE);
	set_dinner_end(table, FALSE);
	table->num_philos = (int)ft_atol(argv[1]);
	table->dur_die = ft_atol(argv[2]);
	table->dur_eat = ft_atol(argv[3]);
	table->dur_sleep = ft_atol(argv[4]);
	table->times_philo_must_eat = -2;
	table->philos = NULL;
	// table->min_wait_time = ((table->num_philos - (int)(table->num_philos / 2)
	// - 1) * table->dur_eat) + (table->dur_eat * 0.5);
	table->min_wait_time = ((table->num_philos - (int)(table->num_philos / 2)
				- 1) * table->dur_eat) + 5;
	if (argc == 6)
		table->times_philo_must_eat = ft_atol(argv[5]);
	check_times_gt_zero(table);
	check_philos_gt_zero(table);
	check_each_philo_must_eat(table);
}

t_bool	has_started(t_table *table)
{
	t_bool	has_started;

	pthread_mutex_lock(&table->m_started);
	has_started = table->started;
	pthread_mutex_unlock(&table->m_started);
	return (has_started);
}

t_bool	has_ended(t_table *table)
{
	t_bool	has_ended;

	pthread_mutex_lock(&table->m_ended);
	has_ended = table->ended;
	pthread_mutex_unlock(&table->m_ended);
	return (has_ended);
}

void	set_dinner_start(t_table *table, t_bool has_started)
{
	put_extra_msg(&table->m_print, "set dinner start: ...\n", CLR_ORANGE);
	pthread_mutex_lock(&table->m_started);
	gettimeofday(&table->t_start, NULL);
	table->started = has_started;
	pthread_mutex_unlock(&table->m_started);
	put_extra_msg(&table->m_print, "set dinner start: OK\n", CLR_GREEN);
}

void	set_dinner_end(t_table *table, t_bool has_ended)
{
	put_extra_msg(&table->m_print, "set dinner end: ...\n", CLR_ORANGE);
	pthread_mutex_lock(&table->m_ended);
	table->ended = has_ended;
	pthread_mutex_unlock(&table->m_ended);
	put_extra_msg(&table->m_print, "set dinner end: OK\n", CLR_GREEN);
}
