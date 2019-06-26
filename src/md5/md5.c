/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:16:33 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 18:54:31 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_ssl.h"
#include "md5.h"
#include "libftprintf.h"

int						md5(int argc, char **argv)
{
	t_ssl				opt;
	char				*task;

	opt = md5_parse_command(argc, argv);
	while ((task = ft_dequeue(opt.tasks, NULL)))
	{
		if (ft_strnequ(task, "STRING:", 7))
			md5_string(&opt, task + 7);
		else if (ft_strnequ(task, "FILE  :", 7))
			md5_file(&opt, task + 7);
		else if (ft_strnequ(task, "STDIN :", 7))
			md5_stdin(&opt, task + 7);
		else if (ft_strnequ(task, "STDINE:", 7))
			md5_stdin_echo(&opt, task + 7);
		else if (ft_strnequ(task, "PRINT :", 7))
			md5_print(&opt, task + 7);
		ft_strdel(&task);
	}
	ft_queue_del(&(opt.tasks), 1);
	return (0);
}

int						md5_file(t_ssl *opt, const char *path)
{
	int		fd;
	t_md5	result;
	char	*task;

	if (access(path, F_OK) != 0)
		return (-ft_dprintf(2, "./ft_ssl md5: %s: No such file\n", path));
	else if (is_dir(path))
		return (-ft_dprintf(2, "./ft_ssl md5: %s: Is a directory\n", path));
	else if (access(path, R_OK) != 0)
		return (-ft_dprintf(2, "./ft_ssl md5: %s: Permission denied\n", path));
	fd = open(path, O_RDONLY);
	result = md5_master(md5_read, fd);
	close(fd);
	ft_asprintf(&task, "PRINT :%.16m;%s", &(result.a0), path);
	ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
	return (0);
}

int						md5_stdin(t_ssl *opt, const char *nothing)
{
	t_md5	result;
	char	*task;

	(void)nothing;
	opt->quiet = 1;
	result = md5_master(md5_read, 0);
	ft_asprintf(&task, "PRINT :%.16m;", &(result.a0));
	ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
	return (0);
}

int						md5_string(t_ssl *opt, const char *str)
{
	int64_t		len;
	t_md5		result;
	char		*task;

	(void)opt;
	(void)str;
	md5_string_read(FTSSL_STRRD_ACT_INIT, (void *)str, &len, 0);
	result = md5_master(md5_string_read, FTSSL_STRRD_ACT_READ);
	md5_string_read(FTSSL_STRRD_ACT_DEINIT, NULL, NULL, 0);
	ft_asprintf(&task, "PRINT :%.16m;\"%s\"", &(result.a0), str);
	ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
	return (0);
}

int						md5_print(t_ssl *opt, const char *str)
{
	(void)opt;
	(void)str;
	if (opt->quiet)
		ft_printf("%.32s\n", str);
	else if (opt->rev)
		ft_printf("%.32s %s\n", str, str + 33);
	else
		ft_printf("MD5 (%s) = %.32s\n", str + 33, str);
	return (0);
}
