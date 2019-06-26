/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:17:27 by gfielder          #+#    #+#             */
/*   Updated: 2019/06/14 18:24:12 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl.h"
#include "libftprintf.h"
#include "md5.h"
#include "sha256.h"
#include "sha224.h"

const static t_dispatch_entry	g_dispatch_dict[] =
{
	{"md5", md5},
	{"sha256", sha256},
	{"sha224", sha224},
	{NULL, NULL}
};

int						dispatch_shell_get_command_line(char **line)
{
	int		ret;

	ft_printf("ft_ssl > ");
	ret = ft_get_next_line(0, line);
	return (ret);
}

int						dispatch_shell(void)
{
	int			ret;
	t_argsarr	*args;
	char		*line;
	int			done;

	done = 0;
	while (!done)
	{
		if ((ret = dispatch_shell_get_command_line(&line)) < 1)
			break ;
		args = ft_strsplit_args(line, " \t\r\n", "\"\"");
		if (ft_strequ(args->argv[0], "exit"))
			done = 1;
		else
			ret = dispatch(args->argc, args->argv, 0);
		ft_argsarr_del(&args);
		ft_strdel(&line);
	}
	return (0);
}

int						dispatch(int argc, char **argv, int pn)
{
	int			i;

	i = 0;
	while (g_dispatch_dict[i].cmd)
	{
		if (ft_strequ(argv[pn], g_dispatch_dict[i].cmd))
			return (g_dispatch_dict[i].handle(argc - pn, argv + pn));
		i++;
	}
	ft_dprintf(2, "Not a valid command: %s\n", argv[pn]);
	ft_dprintf(2, "Commands: ");
	i = 0;
	while (g_dispatch_dict[i].cmd)
	{
		ft_dprintf(2, "%s ", g_dispatch_dict[i].cmd);
		i++;
	}
	return (-ft_dprintf(2, "\n"));
}
