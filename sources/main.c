/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/29 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static int	init_phils(t_ph *ph, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phils)
	{
		ph[i].id = i + 1;
		ph[i].data = data;
		ph[i].last_meal = data->start;
		ph[i].num_meals = 0;
		if (pthread_mutex_init(&ph[i].lfork, NULL))
		{
			printf("'\033[0;31m'Error: Fork mutex init failed\n");
			return (1);
		}
		if (i == data->phils - 1)
			ph[i].rfork = &ph[0].lfork;
		else
			ph[i].rfork = &ph[i + 1].lfork;
		i++;
	}
	if (thread_init(ph, 0))
		return (1);
	return (0);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	data->phils = ft_atoi(argv[1]);
	data->t2d = ft_atoi(argv[2]);
	data->t2e = ft_atoi(argv[3]);
	data->t2s = ft_atoi(argv[4]);
	data->meals = 0;
	data->full = 0;
	data->start = gettime();
	data->status = 0;
	if (argc == 6)
		data->meals = ft_atoi(argv[5]);
	if (pthread_mutex_init(&data->m_print, NULL) \
	|| pthread_mutex_init(&data->m_death, NULL) \
	|| pthread_mutex_init(&data->m_food, NULL) \
	|| pthread_mutex_init(&data->m_status, NULL))
	{
		printf("'\033[0;31m'Error: Mutex init failed\n");
		return (1);
	}
	if (!data->phils || !data->t2d || !data->t2e || !data->t2s \
	|| (argc == 6 && !data->meals) || !data->start)
	{
		printf("'\033[0;31m'Error: Data init failed\n");
		return (1);
	}
	return (0);
}

static int	validate_argv(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("'\033[0;31m'Error: Type of arguments must be integer\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_ph	*ph;
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("'\033[0;31m'Error: Number of arguments must be 4 or 5\n");
		return (1);
	}
	if (validate_argv(argv) || init_data(&data, argc, argv))
		return (1);
	ph = (t_ph *)malloc(sizeof(t_ph) * data.phils);
	if (ph == 0)
	{
		printf("'\033[0;31m'Error: Memmory allocate failed\n");
		return (1);
	}
	if (init_phils(ph, &data))
		return (1);
	free(ph);
	return (0);
}
