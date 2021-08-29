/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/29 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	number_meals(t_ph *ph)
{
	if (ph->data->status == 0)
	{
		pthread_mutex_lock(&ph->data->m_food);
		ph->num_meals++;
		pthread_mutex_unlock(&ph->data->m_food);
		pthread_mutex_lock(&ph->data->m_food);
		if (ph->num_meals == ph->data->meals)
			ph->data->full++;
		pthread_mutex_unlock(&ph->data->m_food);
		if (ph->data->full == ph->data->phils)
		{
			pthread_mutex_lock(&ph->data->m_status);
			ph->data->status = 2;
			printf("All philos ate %d times\n", ph->data->meals);
			return ;
		}
	}
}

void	*death(void *arg)
{
	t_ph			*ph;
	uint64_t		now;
	uint64_t		diff;

	ph = (t_ph *)arg;
	while (ph->data->status == 0)
	{
		pthread_mutex_lock(&ph->data->m_death);
		now = gettime();
		diff = now - ph->last_meal;
		pthread_mutex_unlock(&ph->data->m_death);
		if (diff > (uint64_t)ph->data->t2d)
		{
			pthread_mutex_lock(&ph->data->m_status);
			ft_write(ph, "'\033[0;31m'died'\033[0;32m'");
			ph->data->status = 1;
			break ;
		}
		ft_usleep(9);
	}
	return (0);
}
