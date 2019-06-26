/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:52:58 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/24 14:01:31 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"
#include "libft.h"

t_queue				*ft_queue_new(int autosize)
{
	t_queue		*q;

	if (!(q = (t_queue *)ft_memalloc(sizeof(t_queue))))
		return (NULL);
	q->autosize = autosize;
	return (q);
}

int					ft_enqueue(t_queue *q, void *data, size_t data_size)
{
	t_queue_ent		*ent;

	if (!q)
		return (-1);
	if (q->autosize == FTQ_AUTO_STR)
		data_size = ft_strlen((char *)data);
	else if (q->autosize)
		data_size = (size_t)(q->autosize);
	if (!(ent = ft_queue_ent_new(data, data_size)))
		return (-1);
	if (q->tail)
	{
		q->tail->next = ent;
		q->tail = ent;
	}
	else
	{
		q->head = ent;
		q->tail = ent;
	}
	q->len++;
	return (1);
}

void				*ft_dequeue(t_queue *q, size_t *data_size)
{
	t_queue_ent		*ent;
	void			*ret;

	if (!q || !(q->head))
		return (NULL);
	ent = q->head;
	q->head = q->head->next;
	if (!(q->head))
		q->tail = NULL;
	ret = ent->data;
	if (data_size)
		*data_size = ent->data_size;
	free(ent);
	q->len--;
	return (ret);
}

void				*ft_queue_peek(t_queue *q, size_t *data_size)
{
	if (!q || !(q->head))
		return (NULL);
	if (data_size)
		*data_size = q->head->data_size;
	return (q->head->data);
}
