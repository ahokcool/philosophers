/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:53:43 by astein            #+#    #+#             */
/*   Updated: 2023/08/10 16:47:49 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	grab_left_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_fork);
	put_msg_id(philo, MSG_FORK_TAKE, philo->id);
	if (has_ended(philo->table))
	{
		pthread_mutex_unlock(&philo->m_fork);
		put_msg_id(philo, MSG_FORK_DROP, philo->id);
		return (FALSE);
	}
	pthread_mutex_lock(&philo->right_philo->m_fork);
	put_msg_id(philo, MSG_FORK_TAKE, philo->right_philo->id);
	if (has_ended(philo->table))
	{
		pthread_mutex_unlock(&philo->m_fork);
		put_msg_id(philo, MSG_FORK_DROP, philo->id);
		pthread_mutex_unlock(&philo->right_philo->m_fork);
		put_msg_id(philo, MSG_FORK_DROP, philo->right_philo->id);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	grab_right_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_philo->m_fork);
	if (has_ended(philo->table))
	{
		pthread_mutex_unlock(&philo->right_philo->m_fork);
		return (FALSE);
	}
	put_msg_id(philo, MSG_FORK_TAKE, philo->right_philo->id);
	pthread_mutex_lock(&philo->m_fork);
	if (has_ended(philo->table))
	{
		pthread_mutex_unlock(&philo->right_philo->m_fork);
		pthread_mutex_unlock(&philo->m_fork);
		return (FALSE);
	}
	put_msg_id(philo, MSG_FORK_TAKE, philo->id);
	return (TRUE);
}

// Resource hierarchy solution
// https://en.wikipedia.org/wiki/Dining_philosophers_problem
t_bool	grab_forks(t_philo *philo)
{
	if (philo->table->num_philos == 1)
	{
		pthread_mutex_lock(&philo->m_fork);
		put_msg_id(philo, MSG_FORK_TAKE, philo->id);
		while (!has_ended(philo->table))
			usleep(10);
		pthread_mutex_unlock(&philo->m_fork);
		put_msg_id(philo, MSG_FORK_DROP, philo->id);
		return (FALSE);
	}
	if (philo->right_philo->id > philo->id)
	{
		if (grab_left_right(philo) == FALSE)
			return (FALSE);
	}
	else
	{
		if (grab_right_left(philo) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

void	drop_forks(t_philo *philo)
{
	if (PUT_MORE_INFOS)
		put_msg_id(philo, MSG_FORK_DROP, philo->id);
	pthread_mutex_unlock(&philo->m_fork);
	if (PUT_MORE_INFOS)
		put_msg_id(philo, MSG_FORK_DROP, philo->right_philo->id);
	pthread_mutex_unlock(&philo->right_philo->m_fork);
}
