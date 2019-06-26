/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:04:11 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 18:33:56 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define FTSSL_MD5_INIT_ITER 1
# define FTSSL_MD5_INIT_CHUNK 2
# define FTSSL_MD5_INIT_ALL 3

# include <stdint.h>

typedef	int	(*t_md5_readfunc)	(int num, void *ptr, int64_t *len,
									int prev_status);

extern const uint32_t				g_s[64];
extern const uint32_t				g_k[64];
extern const uint32_t				g_a0;
extern const uint32_t				g_b0;
extern const uint32_t				g_c0;
extern const uint32_t				g_d0;

typedef struct						s_md5
{
	uint32_t						a;
	uint32_t						b;
	uint32_t						c;
	uint32_t						d;
	uint32_t						f;
	uint32_t						g;
	uint32_t						a0;
	uint32_t						b0;
	uint32_t						c0;
	uint32_t						d0;
}									t_md5;

t_md5								md5_master(t_md5_readfunc readfunc,
										int readfunc_arg);

int									md5(int argc, char **argv);
int									md5_file(t_ssl *opt, const char *str);
int									md5_stdin(t_ssl *opt, const char *str);
int									md5_stdin_echo(t_ssl *opt,
										const char *nothing);
int									md5_string(t_ssl *opt, const char *str);
t_ssl								md5_parse_command(int argc, char **argv);
int									md5_print(t_ssl *opt, const char *str);
int									md5_read(int fd, void *blk_v,
										int64_t *len, int prev_status);
int									md5_string_read(int action, void *blk_v,
										int64_t *len, int prev_status);

void								md5_init(t_md5 *dat, int level);
uint32_t							md5_left_rotate(uint32_t x, uint32_t c);

#endif
