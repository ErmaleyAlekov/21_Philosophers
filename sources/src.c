/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/29 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static void	ft_locked(t_ph *ph, int type)
{
	if (type == 1)
	{
		if (pthread_mutex_lock(&ph->lfork))
		{
			pthread_mutex_unlock(ph->rfork);
			eat(ph);
		}
	}
	if (type == 2)
	{
		if (pthread_mutex_lock(ph->rfork))
		{
			pthread_mutex_unlock(&ph->lfork);
			eat(ph);
		}
	}
}

void	eat(t_ph *ph)
{
	if (!(ph->id % 2))
		pthread_mutex_lock(ph->rfork);
	else
		pthread_mutex_lock(&ph->lfork);
	ft_write(ph, "has taken a fork");
	if (ph->data->phils == 1)
	{
		pthread_mutex_unlock(ph->rfork);
		return ;
	}
	if (!(ph->id % 2))
		ft_locked(ph, 1);
	else
		ft_locked(ph, 2);
	ft_write(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->m_food);
	ph->last_meal = gettime();
	pthread_mutex_unlock(&ph->data->m_food);
	ft_write(ph, "is eating");
	ft_usleep(ph->data->t2e);
	number_meals(ph);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(&ph->lfork);
}

void	*life(void *arg)
{
	t_ph		*ph;
	pthread_t	t_death;

	ph = (t_ph *)arg;
	if (pthread_create(&t_death, 0, &death, ph))
	{
		printf("'\033[0;31m'Error: Pthread create failed\n");
		return (0);
	}
	if (pthread_detach(t_death))
	{
		printf("'\033[0;31m'Error: Pthread detach failed\n");
		return (0);
	}
	while (ph->data->status == 0)
	{
		eat(ph);
		ft_write(ph, "is sleeping");
		ft_usleep(ph->data->t2s);
		ft_write(ph, "is thinking");
	}
	return (0);
}

static int	create_threads(t_ph *ph, int i)
{
	if (pthread_create(&ph[i].t_ph, 0, &life, &ph[i]))
	{
		printf("'\033[0;31m'Error: Pthread create failed\n");
		return (1);
	}
	ft_usleep(1 / 10);
	return (0);
}

int	thread_init(t_ph *ph, int i)
{
	while (i < ph->data->phils)
	{
		if (create_threads(ph, i))
			return (1);
		i += 2;
	}
	ft_usleep(ph->data->t2e / ph->data->phils);
	i = 1;
	while (i < ph->data->phils)
	{
		if (create_threads(ph, i))
			return (1);
		i += 2;
	}
	i = -1;
	while (++i < ph->data->phils)
	{
		if (pthread_join(ph[i].t_ph, 0))
		{
			printf("'\033[0;31m'Error: Pthread detach failed\n");
			return (1);
		}
	}
	destroy(ph);
	return (0);
}
