/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_stdin_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:19:44 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 19:06:12 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
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

int						md5_stdin_echo(t_ssl *opt, const char *nothing)
{
	t_md5	result;
	char	*all;
	int64_t	len;

	(void)nothing;
	(void)opt;
	read_stdin_to_str(&all);
	md5_string_read(FTSSL_STRRD_ACT_INIT, (void *)all, &len, 0);
	result = md5_master(md5_string_read, FTSSL_STRRD_ACT_READ);
	md5_string_read(FTSSL_STRRD_ACT_DEINIT, NULL, NULL, 0);
	ft_printf("%s", all);
	free(all);
	ft_printf("%.16m\n", &(result.a0));
	return (0);
}
