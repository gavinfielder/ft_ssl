/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:04:02 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 18:02:11 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"
#include "sha256.h"

static int	sha256_read_helper(t_block *blk, int64_t *len,
				int64_t ret, int64_t bufflen)
{
	if (ret < 0)
		return (FTSSL_READ_ERROR);
	(*len) += bufflen;
	if (bufflen < 56)
	{
		blk->bytes[bufflen] |= 0x80;
		sha256_int64_copy(((unsigned char *)blk) + 56, *len);
		return (FTSSL_READ_DONE);
	}
	if (bufflen < 64)
	{
		blk->bytes[bufflen] |= 0x80;
		return (FTSSL_READ_EOM);
	}
	return (FTSSL_READ_CONTINUE);
}

int			sha256_read(int fd, void *blk_v, int64_t *len,
				int prev_status)
{
	int64_t	ret;
	int64_t	bufflen;
	t_block	*blk;

	blk = (t_block *)blk_v;
	ft_bzero((void *)blk, 64);
	if (prev_status == FTSSL_READ_EOM)
	{
		sha256_int64_copy(((unsigned char *)blk) + 56, *len);
		return (FTSSL_READ_DONE);
	}
	bufflen = 0;
	ret = (int64_t)read(fd, ((unsigned char *)blk), 64);
	bufflen += ret;
	return (sha256_read_helper(blk, len, ret, bufflen));
}
