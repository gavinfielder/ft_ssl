/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 21:00:37 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/27 18:07:30 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"

static void				process_chunk(t_md5 *dat, int i, t_block *blk)
{
	if (i < 16)
	{
		dat->f = (dat->b & dat->c) | (~(dat->b) & dat->d);
		dat->g = i;
	}
	else if (i < 32)
	{
		dat->f = (dat->d & dat->b) | ((~(dat->d)) & dat->c);
		dat->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		dat->f = (dat->b ^ dat->c ^ dat->d);
		dat->g = (3 * i + 5) % 16;
	}
	else
	{
		dat->f = dat->c ^ (dat->b | (~(dat->d)));
		dat->g = (7 * i) % 16;
	}
	dat->f += dat->a + g_k[i] + blk->words[dat->g];
	dat->a = dat->d;
	dat->d = dat->c;
	dat->c = dat->b;
	dat->b += md5_left_rotate(dat->f, g_s[i]);
}

t_md5					md5_master(t_md5_readfunc get_next_block,
							int readfunc_arg)
{
	t_block		blk;
	t_md5		dat;
	int64_t		len;
	int			status;
	int			i;

	status = FTSSL_READ_FIRST;
	len = 0;
	md5_init(&dat, FTSSL_MD5_INIT_ALL);
	while (1)
	{
		status = get_next_block(readfunc_arg, &blk, &len, status);
		md5_init(&dat, FTSSL_MD5_INIT_CHUNK);
		i = -1;
		while (++i < 64)
			process_chunk(&dat, i, &blk);
		dat.a0 += dat.a;
		dat.b0 += dat.b;
		dat.c0 += dat.c;
		dat.d0 += dat.d;
		if (status == FTSSL_READ_DONE)
			break ;
	}
	return (dat);
}
