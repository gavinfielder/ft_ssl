/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:21:54 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 20:59:29 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"
#include "ft_ssl.h"
#include "sha224.h"
#include "md5.h"

static void			parse_error(const char *str, t_queue *tasks)
{
	ft_queue_del(&tasks, 1);
	if (str)
		ft_dprintf(2, "%s\n", str);
	ft_dprintf(2,
			"usage: ./ft_ssl sha224 [-pqr] [-s string] [files ...]\n");
	exit(-1);
}

static void			parse_single(t_ssl *opt, char c)
{
	static char		buff[38] = "./ft_ssl sha224: unknown option -- c";
	char			*task;

	if (c == 'q')
		opt->quiet = 1;
	else if (c == 'r')
		opt->rev = 1;
	else if (c == 'p')
	{
		ft_asprintf(&task, "STDINE:");
		ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
	}
	else
	{
		buff[37] = c;
		parse_error(buff, opt->tasks);
	}
}

static void			add_task_stdin(t_ssl *opt)
{
	char	*task;

	ft_asprintf(&task, "STDIN :");
	ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
}

static t_ssl		parse_arguments(t_ssl *opt, int count, char **args)
{
	int		i;
	char	*task;

	i = -1;
	while (++i < count)
	{
		if (ft_strequ(args[i], "-s"))
		{
			if (i + 1 >= count)
				parse_error("./ft_ssl sha224: option requires an argument -- s",
						opt->tasks);
			ft_asprintf(&task, "STRING:%s", args[(i++) + 1]);
			ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
		}
		else
		{
			ft_asprintf(&task, "FILE  :%s", args[i]);
			ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
		}
	}
	if (!(ft_queue_peek(opt->tasks, NULL)))
		add_task_stdin(opt);
	return (*opt);
}

t_ssl				sha224_parse_command(int argc, char **argv)
{
	t_ssl			opt;
	int				i;
	int				j;

	ft_bzero(&opt, sizeof(t_ssl));
	if (!(opt.tasks = ft_queue_new(FTQ_AUTO_STR)))
		parse_error("./ft_ssl sha224: task queue creation failure.", opt.tasks);
	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j])
		{
			if (j == 1 && argv[i][j] == 's' && ft_strlen(argv[i]) == 2)
				return (parse_arguments(&opt, argc - i, argv + i));
			else
				parse_single(&opt, argv[i][j]);
		}
	}
	return (parse_arguments(&opt, argc - i, argv + i));
}
