/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/29 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	ft_atoi(char *str)
{
	int					a;
	long				znak;
	unsigned long long	otvet;

	a = 0;
	otvet = 0;
	znak = 1;
	while ((str[a] >= '\a' && str[a] <= '\r') || str[a] == ' ')
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a++] == '-')
			znak = -1;
	}
	while (str[a] >= '0' && str[a] <= '9')
		otvet = ((otvet * 10) + (str[a++] - '0'));
	if (a > 19 || otvet >= 9223372036854775808ULL)
	{
		if (znak == 1)
			return (-1);
		return (0);
	}
	return ((int)(otvet * znak));
}

void	destroy(t_ph *ph)
{
	pthread_mutex_destroy(&ph->data->m_death);
	pthread_mutex_destroy(&ph->data->m_food);
	pthread_mutex_destroy(&ph->data->m_print);
	pthread_mutex_destroy(&ph->data->m_status);
}

void	ft_usleep(uint64_t time)
{
	uint64_t	timer;

	timer = gettime();
	while ((gettime() - timer) < time)
		usleep(100);
}

uint64_t	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_write(t_ph *ph, char *str)
{
	uint64_t	now;

	pthread_mutex_lock(&ph->data->m_print);
	now = ((gettime() - ph->data->start));
	if (ph->data->status == 0)
		printf("'\033[0;32m'Time:[%llu] Phil_id:[%d] Action:[%s]\n", \
		now, ph->id, str);
	pthread_mutex_unlock(&ph->data->m_print);
}
