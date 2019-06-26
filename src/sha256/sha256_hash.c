/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 21:00:37 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 20:32:29 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "sha256.h"

static void				compress(t_sha256 *dat, int i)
{
	dat->s1 = sha256_rotate(dat->e, 6) ^ sha256_rotate(dat->e, 11)
		^ sha256_rotate(dat->e, 25);
	dat->ch = (dat->e & dat->f) ^ (~(dat->e) & dat->g);
	dat->temp1 = sha256_add(5, dat->h, dat->s1, dat->ch,
			g_sha256_k[i], dat->w[i]);
	dat->s0 = sha256_rotate(dat->a, 2) ^ sha256_rotate(dat->a, 13)
		^ sha256_rotate(dat->a, 22);
	dat->maj = (dat->a & dat->b) ^ (dat->a & dat->c) ^ (dat->b & dat->c);
	dat->temp2 = dat->s0 + dat->maj;
	dat->h = dat->g;
	dat->g = dat->f;
	dat->f = dat->e;
	dat->e = dat->d + dat->temp1;
	dat->d = dat->c;
	dat->c = dat->b;
	dat->b = dat->a;
	dat->a = dat->temp1 + dat->temp2;
}

static void				finalize(t_sha256 *dat)
{
	dat->hash[0] += dat->a;
	dat->hash[1] += dat->b;
	dat->hash[2] += dat->c;
	dat->hash[3] += dat->d;
	dat->hash[4] += dat->e;
	dat->hash[5] += dat->f;
	dat->hash[6] += dat->g;
	dat->hash[7] += dat->h;
}

t_sha256				sha256_master(t_md5_readfunc get_next_block,
							int readfunc_arg, const uint32_t h0[8])
{
	t_block		blk;
	t_sha256	dat;
	int64_t		len;
	int			status;
	int			i;

	status = FTSSL_READ_FIRST;
	len = 0;
	sha256_init(&dat, FTSSL_SHA256_INIT_ALL, h0);
	while (1)
	{
		status = get_next_block(readfunc_arg, &blk, &len, status);
		sha256_endian_swap_words(blk.words, 16);
		sha256_init_schedule(&dat, &blk);
		sha256_init(&dat, FTSSL_SHA256_INIT_CHUNK, h0);
		i = -1;
		while (++i < 64)
			compress(&dat, i);
		finalize(&dat);
		if (status == FTSSL_READ_DONE)
			break ;
	}
	return (dat);
}
