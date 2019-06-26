/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_string_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:06:05 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 18:03:21 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"
#include "libftprintf.h"
#include "sha256.h"

static int64_t	sha256_string_read_init(char **msg, char *raw, int64_t *len,
					int64_t *next)
{
	size_t	alen;

	*len = ft_strlen(raw);
	alen = (*len / 64 + 1 + (*len % 64 >= 56 ? 1 : 0)) * 64;
	*msg = ft_strnew(alen);
	ft_strcpy(*msg, raw);
	(*msg)[*len] = (char)0x80;
	sha256_int64_copy(((unsigned char *)(*msg)) + alen - 8, *len);
	*next = 0;
	return (alen);
}

int				sha256_string_read(int action, void *ptr, int64_t *len,
				int prev_status)
{
	static char		*msg = NULL;
	static int64_t	next = 0;
	static int64_t	total_size;

	(void)prev_status;
	if (action == FTSSL_STRRD_ACT_INIT)
	{
		return ((total_size = sha256_string_read_init(&msg,
						(char *)ptr, len, &next)));
	}
	else if (action == FTSSL_STRRD_ACT_DEINIT)
		ft_strdel(&msg);
	else if (action == FTSSL_STRRD_ACT_READ)
	{
		ft_memcpy(ptr, msg + next, 64);
		next += 64;
		if (next >= total_size)
			return (FTSSL_READ_DONE);
	}
	return (FTSSL_READ_CONTINUE);
}
