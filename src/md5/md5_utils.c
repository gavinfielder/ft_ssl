/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 21:17:58 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/27 18:08:03 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

void			md5_init(t_md5 *dat, int level)
{
	dat->f = 0;
	dat->g = 0;
	if (level == FTSSL_MD5_INIT_CHUNK)
	{
		dat->a = dat->a0;
		dat->b = dat->b0;
		dat->c = dat->c0;
		dat->d = dat->d0;
	}
	else if (level == FTSSL_MD5_INIT_ALL)
	{
		dat->a0 = g_a0;
		dat->b0 = g_b0;
		dat->c0 = g_c0;
		dat->d0 = g_d0;
	}
}

uint32_t		md5_left_rotate(uint32_t x, uint32_t c)
{
	return ((x << c) | (x >> (32 - c)));
}

void			int64_copy(unsigned char *dst, int64_t num)
{
	num <<= 3;
	*((uint64_t *)dst) = (uint64_t)num;
}
