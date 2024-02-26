/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:35:53 by astein            #+#    #+#             */
/*   Updated: 2023/08/11 01:30:46 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->m_philo);
	state = philo->state;
	pthread_mutex_unlock(&philo->m_philo);
	return (state);
}

t_bool	set_state(t_philo *philo, int state)
{
	if (get_state(philo) == DIED)
		return (FALSE);
	if (check_if_alive(philo) == FALSE)
		state = DIED;
	pthread_mutex_lock(&philo->m_philo);
	philo->state = state;
	if (state == EATING)
	{
		put_msg_id(philo, MSG_EAT, NO_FORK);
		gettimeofday(&philo->t_last_meal, NULL);
		philo->count_meals++;
	}
	else if (state == FINISHED_EATING)
		put_msg_id(philo, MSG_EAT_END, NO_FORK);
	else if (state == SLEEPING)
		put_msg_id(philo, MSG_SLEEP, NO_FORK);
	else if (state == THINKING)
		put_msg_id(philo, MSG_THINK, NO_FORK);
	else if (state == DIED)
	{
		put_msg_id(philo, MSG_DIED, NO_FORK);
		set_dinner_end(philo->table, TRUE);
	}
	pthread_mutex_unlock(&philo->m_philo);
	return (TRUE);
}

int	get_meal_count(t_philo *philo)
{
	int	count;

	pthread_mutex_lock(&philo->m_philo);
	count = philo->count_meals;
	pthread_mutex_unlock(&philo->m_philo);
	return (count);
}

int	get_meal_diff(t_philo *philo)
{
	int	diff;

	pthread_mutex_lock(&philo->m_philo);
	diff = philo->count_meals - philo->table->times_philo_must_eat;
	pthread_mutex_unlock(&philo->m_philo);
	return (diff);
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (has_started(philo->table) == FALSE)
		;
	pthread_mutex_lock(&philo->m_philo);
	philo->t_last_meal = philo->table->t_start;
	pthread_mutex_unlock(&philo->m_philo);
	if (philo->id % 2 != 0)
		usleep((philo->table->dur_eat * 1000) / 2);
	while (get_state(philo) != DIED && !has_ended(philo->table))
	{
		if (get_state(philo) == SLEEPING && !start_thinking(philo))
			return (NULL);
		else if (get_state(philo) == FINISHED_EATING && !start_sleeping(philo))
			return (NULL);
		else if (get_state(philo) == THINKING && !start_eating(philo))
			return (NULL);
	}
	return (NULL);
}
