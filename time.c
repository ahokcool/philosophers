/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:17:22 by astein            #+#    #+#             */
/*   Updated: 2023/08/10 02:23:26 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time_diff_last_meal(t_philo *philo)
{
	long int	li;

	pthread_mutex_lock(&philo->m_philo);
	li = get_time_diff(&philo->t_last_meal);
	pthread_mutex_unlock(&philo->m_philo);
	return (li);
}

long int	get_time_diff(struct timeval *t1)
{
	long long int	sec;
	long long int	usec;
	struct timeval	t_curr;

	gettimeofday(&t_curr, NULL);
	sec = t_curr.tv_sec - t1->tv_sec;
	usec = t_curr.tv_usec - t1->tv_usec;
	return (sec * 1000 + usec / 1000);
}
