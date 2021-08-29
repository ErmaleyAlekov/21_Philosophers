/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:33:14 by uterese           #+#    #+#             */
/*   Updated: 2021/08/29 19:42:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>

typedef struct s_data
{
	int				phils;
	int				meals;
	int				status;
	int				full;
	int				t2d;
	int				t2e;
	int				t2s;
	uint64_t		start;
	pthread_t		t_death;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_food;
	pthread_mutex_t	m_death;
	pthread_mutex_t	m_status;	
}				t_data;

typedef struct s_ph
{
	int				id;
	int				num_meals;
	uint64_t		last_meal;
	pthread_t		t_ph;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	t_data			*data;
}				t_ph;

int			thread_init(t_ph *ph, int i);
void		*life(void *arg);
void		eat(t_ph *ph);
void		number_meals(t_ph *ph);
void		*death(void *arg);
void		ft_usleep(uint64_t time);
uint64_t	gettime(void);
void		ft_write(t_ph *ph, char *str);
void		destroy(t_ph *ph);
int			ft_atoi(char *str);

#endif