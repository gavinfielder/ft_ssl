/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:16:33 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 21:00:02 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_ssl.h"
#include "sha256.h"
#include "sha224.h"
#include "libftprintf.h"

int						sha224(int argc, char **argv)
{
	t_ssl				opt;
	char				*task;

	(void)opt;
	(void)task;
	(void)argc;
	(void)argv;
	opt = sha224_parse_command(argc, argv);
	while ((task = ft_dequeue(opt.tasks, NULL)))
	{
		if (ft_strnequ(task, "STRING:", 7))
			sha224_string(&opt, task + 7);
		else if (ft_strnequ(task, "FILE  :", 7))
			sha224_file(&opt, task + 7);
		else if (ft_strnequ(task, "STDIN :", 7))
			sha224_stdin(&opt, task + 7);
		else if (ft_strnequ(task, "STDINE:", 7))
			sha224_stdin_echo(&opt, task + 7);
		else if (ft_strnequ(task, "PRINT :", 7))
			sha224_print(&opt, task + 7);
		ft_strdel(&task);
	}
	ft_queue_del(&(opt.tasks), 1);
	return (0);
}

int						sha224_file(t_ssl *opt, const char *path)
{
	int			fd;
	t_sha256	result;
	char		*task;

	if (access(path, F_OK) != 0)
		return (-ft_dprintf(2, "./ft_ssl sha224: %s: No such file\n", path));
	else if (is_dir(path))
		return (-ft_dprintf(2, "./ft_ssl sha224: %s: Is a directory\n", path));
	else if (access(path, R_OK) != 0)
	{
		return (-ft_dprintf(2,
			"./ft_ssl sha224: %s: Permission denied\n", path));
	}
	fd = open(path, O_RDONLY);
	result = sha256_master(sha256_read, fd, g_sha224_h0);
	close(fd);
	sha256_endian_swap_words(result.hash, 8);
	ft_asprintf(&task, "PRINT :%.28m;%s", &(result.hash), path);
	ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
	return (0);
}

int						sha224_stdin(t_ssl *opt, const char *nothing)
{
	t_sha256	result;
	char		*task;

	(void)nothing;
	opt->quiet = 1;
	result = sha256_master(sha256_read, 0, g_sha224_h0);
	sha256_endian_swap_words(result.hash, 8);
	ft_asprintf(&task, "PRINT :%.28m;", &(result.hash));
	ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
	return (0);
}

int						sha224_string(t_ssl *opt, const char *str)
{
	int64_t		len;
	t_sha256	result;
	char		*task;

	(void)opt;
	(void)str;
	sha256_string_read(FTSSL_STRRD_ACT_INIT, (void *)str, &len, 0);
	result = sha256_master(sha256_string_read, FTSSL_STRRD_ACT_READ,
			g_sha224_h0);
	sha256_string_read(FTSSL_STRRD_ACT_DEINIT, NULL, NULL, 0);
	sha256_endian_swap_words(result.hash, 8);
	ft_asprintf(&task, "PRINT :%.28m;\"%s\"", &(result.hash), str);
	ft_enqueue(opt->tasks, task, FTQ_AUTOSIZE);
	return (0);
}

int						sha224_print(t_ssl *opt, const char *str)
{
	(void)opt;
	(void)str;
	if (opt->quiet)
		ft_printf("%.56s\n", str);
	else if (opt->rev)
		ft_printf("%.56s %s\n", str, str + 57);
	else
		ft_printf("SHA224(%s)= %.56s\n", str + 57, str);
	return (0);
}
