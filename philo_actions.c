/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:01:28 by astein            #+#    #+#             */
/*   Updated: 2023/08/10 15:57:05 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	start_eating(t_philo *philo)
{
	while (get_time_diff_last_meal(philo) < philo->table->min_wait_time
		&& get_meal_count(philo) != 0)
		usleep(10);
	if (!grab_forks(philo))
		return (FALSE);
	if (set_state(philo, EATING) == FALSE)
		return (FALSE);
	usleep(philo->table->dur_eat * 1000);
	if (set_state(philo, FINISHED_EATING) == FALSE)
		return (FALSE);
	drop_forks(philo);
	return (TRUE);
}

t_bool	start_thinking(t_philo *philo)
{
	if (set_state(philo, THINKING) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	start_sleeping(t_philo *philo)
{
	if (set_state(philo, SLEEPING) == FALSE)
		return (FALSE);
	usleep(philo->table->dur_sleep * 1000);
	return (TRUE);
}
