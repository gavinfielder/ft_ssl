/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:23:08 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 18:01:03 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include "ft_ssl.h"

void			debug_print_options(t_ssl opt)
{
	ft_putstr("Options selected:\n");
	ft_putstr(opt.quiet ? "    quiet mode (-q)\n" : "");
	ft_putstr(opt.rev ? "    reversed output (-r)\n" : "");
	ft_putstr(opt.echo ? "    echo stdin (-p)\n" : "");
	ft_queue_print(opt.tasks);
}
