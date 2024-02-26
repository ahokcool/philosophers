/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:22:34 by astein            #+#    #+#             */
/*   Updated: 2023/08/10 16:37:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_tab(t_philo *philo)
{
	int	i;

	if (philo->table->num_philos <= 10)
	{
		i = 1;
		while (i < philo->id)
		{
			printf("\t\t");
			i++;
		}
	}
}

static void	put_msg(pthread_mutex_t *m_print, char *msg, char *clr)
{
	if (m_print)
		pthread_mutex_lock(m_print);
	printf("%s%s%s", clr, msg, CLR_RESET);
	if (m_print)
		pthread_mutex_unlock(m_print);
}

void	put_msg_id(t_philo *philo, int msg_id, int fork)
{
	if ((msg_id == MSG_EAT_END || msg_id == MSG_FORK_DROP) && !PUT_MORE_INFOS)
		return ;
	if (msg_id == MSG_ALL_EAT && PUT_MORE_INFOS)
	{
		pthread_mutex_lock(&philo->table->m_print);
		printf("%ld %s\n", get_time_diff(&philo->table->t_start),
			get_msg(msg_id));
		pthread_mutex_unlock(&philo->table->m_print);
	}
	else if (msg_id == MSG_ALL_EAT && !PUT_MORE_INFOS)
		return ;
	else if (!has_ended(philo->table))
	{
		pthread_mutex_lock(&philo->table->m_print);
		if (PUT_MORE_INFOS)
			print_tab(philo);
		printf("%ld %d %s", get_time_diff(&philo->table->t_start), philo->id,
			get_msg(msg_id));
		if (PUT_MORE_INFOS && msg_id == MSG_FORK_TAKE)
			printf("%s: %d%s", CLR_RED, fork, CLR_RESET);
		if (PUT_MORE_INFOS && msg_id == MSG_FORK_DROP)
			printf("%s: %d%s", CLR_GREEN, fork, CLR_RESET);
		printf("\n");
		pthread_mutex_unlock(&philo->table->m_print);
	}
}

void	put_extra_msg(pthread_mutex_t *m_print, char *msg, char *c)
{
	if (PUT_MORE_INFOS)
		put_msg(m_print, msg, c);
}

void	put_exit_msg(t_table *table, char *msg, t_bool success)
{
	pthread_mutex_t	*m_print;

	if (table)
		m_print = &table->m_print;
	else
		m_print = NULL;
	if (success)
		put_msg(m_print, msg, CLR_GREEN);
	else
		put_msg(m_print, msg, CLR_RED);
	exit_dining(table, success);
}
