/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:12:59 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 20:51:24 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include <stdint.h>

extern const uint32_t				g_sha256_s[64];
extern const uint32_t				g_sha256_k[64];
extern const uint32_t				g_sha256_h0[8];

# define FTSSL_SHA256_INIT_ITER 1
# define FTSSL_SHA256_INIT_CHUNK 2
# define FTSSL_SHA256_INIT_ALL 3

typedef struct						s_sha256
{
	uint32_t						a;
	uint32_t						b;
	uint32_t						c;
	uint32_t						d;
	uint32_t						e;
	uint32_t						f;
	uint32_t						g;
	uint32_t						h;
	uint32_t						w[64];
	uint32_t						hash[8];
	uint32_t						temp1;
	uint32_t						temp2;
	uint32_t						s1;
	uint32_t						s0;
	uint32_t						ch;
	uint32_t						maj;
}									t_sha256;

t_sha256							sha256_master(t_md5_readfunc readfunc,
										int readfunc_arg, const uint32_t h0[8]);

int									sha256(int argc, char **argv);
int									sha256_file(t_ssl *opt, const char *str);
int									sha256_stdin(t_ssl *opt, const char *str);
int									sha256_stdin_echo(t_ssl *opt,
										const char *nothing);
int									sha256_string(t_ssl *opt, const char *str);
t_ssl								sha256_parse_command(int argc, char **argv);
int									sha256_print(t_ssl *opt, const char *str);
int									sha256_read(int fd, void *blk_v,
										int64_t *len, int prev_status);
int									sha256_string_read(int action, void *blk_v,
										int64_t *len, int prev_status);

void								sha256_init_schedule(t_sha256 *dat,
										t_block *blk);
void								sha256_init(t_sha256 *dat, int level,
										const uint32_t h0[8]);
uint32_t							sha256_rotate(uint32_t x, int32_t c);
void								sha256_int64_copy(unsigned char *dst,
										int64_t num);
uint32_t							sha256_add(int num_args, ...);

uint32_t							endian_swap(uint32_t num);
void								sha256_endian_swap_words(void *arr,
										int len);

#endif
