/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 21:17:58 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 20:31:53 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_ssl.h"
#include "md5.h"
#include "sha256.h"

void			sha256_init_schedule(t_sha256 *dat, t_block *blk)
{
	int		i;

	ft_memcpy(dat->w, blk, 64);
	i = 15;
	while (++i < 64)
	{
		dat->s0 = sha256_rotate(dat->w[i - 15], 7)
			^ sha256_rotate(dat->w[i - 15], 18)
			^ (dat->w[i - 15] >> 3);
		dat->s1 = sha256_rotate(dat->w[i - 2], 17)
			^ sha256_rotate(dat->w[i - 2], 19)
			^ (dat->w[i - 2] >> 10);
		dat->w[i] = sha256_add(4, dat->w[i - 16],
				dat->s0, dat->w[i - 7], dat->s1);
	}
}

void			sha256_init(t_sha256 *dat, int level, const uint32_t h0[8])
{
	int		i;

	if (level == FTSSL_SHA256_INIT_CHUNK)
	{
		dat->a = dat->hash[0];
		dat->b = dat->hash[1];
		dat->c = dat->hash[2];
		dat->d = dat->hash[3];
		dat->e = dat->hash[4];
		dat->f = dat->hash[5];
		dat->g = dat->hash[6];
		dat->h = dat->hash[7];
	}
	i = -1;
	while (level == FTSSL_SHA256_INIT_ALL && ++i < 8)
		dat->hash[i] = h0[i];
}

uint32_t		sha256_rotate(uint32_t x, int32_t c)
{
	if (c < 0)
		return ((x << (-c)) | (x >> (32 - (-c))));
	else if (c > 0)
		return ((x >> (c)) | (x << (32 - (c))));
	return (x);
}

void			sha256_int64_copy(unsigned char *dst, int64_t num)
{
	num <<= 3;
	((uint8_t *)dst)[0] = ((uint8_t *)(&num))[7];
	((uint8_t *)dst)[1] = ((uint8_t *)(&num))[6];
	((uint8_t *)dst)[2] = ((uint8_t *)(&num))[5];
	((uint8_t *)dst)[3] = ((uint8_t *)(&num))[4];
	((uint8_t *)dst)[4] = ((uint8_t *)(&num))[3];
	((uint8_t *)dst)[5] = ((uint8_t *)(&num))[2];
	((uint8_t *)dst)[6] = ((uint8_t *)(&num))[1];
	((uint8_t *)dst)[7] = ((uint8_t *)(&num))[0];
}

uint32_t		sha256_add(int num_args, ...)
{
	va_list		args;
	int			i;
	uint64_t	result;
	uint32_t	tmp;

	va_start(args, num_args);
	i = -1;
	result = 0;
	while (++i < num_args)
	{
		tmp = va_arg(args, uint32_t);
		result += tmp;
	}
	va_end(args);
	result &= 0xFFFFFFFF;
	return ((uint32_t)result);
}
