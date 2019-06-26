/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:12:59 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 20:57:38 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_H
# define SHA224_H

# include "sha256.h"
# include <stdint.h>

extern const uint32_t				g_sha224_h0[8];

int									sha224(int argc, char **argv);
int									sha224_file(t_ssl *opt, const char *str);
int									sha224_stdin(t_ssl *opt, const char *str);
int									sha224_stdin_echo(t_ssl *opt,
										const char *nothing);
int									sha224_string(t_ssl *opt, const char *str);
t_ssl								sha224_parse_command(int argc, char **argv);
int									sha224_print(t_ssl *opt, const char *str);

#endif
