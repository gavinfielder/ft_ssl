/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_stdin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:19:44 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 20:52:43 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"
#include "sha256.h"
#include "sha224.h"
#include "libftprintf.h"

static void				read_stdin_to_str(char **str)
{
	char	c[2];
	int		ret;

	c[1] = '\0';
	*str = ft_strnew(0);
	while (1)
	{
		ret = read(0, c, 1);
		if (ret <= 0)
			break ;
		ft_strjoin_inplace(str, c);
	}
}

int						sha224_stdin_echo(t_ssl *opt, const char *nothing)
{
	t_sha256	result;
	char		*all;
	int64_t		len;

	(void)nothing;
	(void)opt;
	read_stdin_to_str(&all);
	sha256_string_read(FTSSL_STRRD_ACT_INIT, (void *)all, &len, 0);
	result = sha256_master(sha256_string_read, FTSSL_STRRD_ACT_READ,
			g_sha224_h0);
	sha256_string_read(FTSSL_STRRD_ACT_DEINIT, NULL, NULL, 0);
	ft_printf("%s", all);
	free(all);
	sha256_endian_swap_words(result.hash, 8);
	ft_printf("%.32m\n", &(result.hash));
	return (0);
}
