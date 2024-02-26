/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:20:27 by astein            #+#    #+#             */
/*   Updated: 2023/08/10 16:38:32 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_params(t_table *table)
{
	if (PUT_MORE_INFOS)
	{
		pthread_mutex_lock(&table->m_print);
		printf("===========================================\n");
		printf("\tnum_philos:\t\t%d\n", table->num_philos);
		printf("\tdur_die:\t\t%ld\n", table->dur_die);
		printf("\tdur_eat:\t\t%ld\n", table->dur_eat);
		printf("\tdur_sleep:\t\t%ld\n", table->dur_sleep);
		printf("\ttimes_philo_must_eat:\t%d\n", table->times_philo_must_eat);
		printf("===========================================\n");
		pthread_mutex_unlock(&table->m_print);
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		put_exit_msg(NULL, "wrong number of arguments\n", FALSE);
	table = malloc(sizeof(t_table));
	if (!table)
		put_exit_msg(NULL, "malloc for table failed\n", FALSE);
	ini_table(table, argc, argv);
	put_params(table);
	ini_philos(table);
	set_dinner_start(table, TRUE);
	usleep(1000);
	while (1)
	{
		if (check_if_any_philo_died(table))
			exit_dining(table, FALSE);
		if (check_if_all_philo_have_eaten_enough(table))
		{
			put_msg_id(table->philos, MSG_ALL_EAT, NO_FORK);
			exit_dining(table, TRUE);
		}
		usleep(10);
	}
}

void	exit_dining(t_table *table, t_bool success)
{
	if (!table)
		exit(EXIT_FAILURE);
	set_dinner_end(table, TRUE);
	join_philos(table);
	if (table)
		free_table(table);
	if (success)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
