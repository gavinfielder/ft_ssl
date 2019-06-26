/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:59:13 by gfielder          #+#    #+#             */
/*   Updated: 2019/06/14 18:14:49 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# define FTSSL_MODE_ENCRYPT 0
# define FTSSL_MODE_DECRYPT 1

# define FTSSL_READ_FIRST -2
# define FTSSL_READ_ERROR -1
# define FTSSL_READ_CONTINUE 0
# define FTSSL_READ_EOM 1
# define FTSSL_READ_DONE 2

# define FTSSL_MD5_INIT_ITER 1
# define FTSSL_MD5_INIT_CHUNK 2
# define FTSSL_MD5_INIT_ALL 3

# define FTSSL_STRRD_ACT_INIT 1
# define FTSSL_STRRD_ACT_READ 2
# define FTSSL_STRRD_ACT_DEINIT 3

# include <stdint.h>
# include "libft.h"

typedef uint32_t					t_block_words[16];
typedef uint8_t						t_block_bytes[64];
typedef union						u_block
{
	t_block_words					words;
	t_block_bytes					bytes;
}									t_block;

typedef	int	(*t_md5_readfunc)	(int num, void *ptr, int64_t *len,
									int prev_status);

typedef	int	(*t_ftssl_command)	(int argc, char **argv);

typedef struct						s_dispatch_entry
{
	const char						*cmd;
	t_ftssl_command					handle;
}									t_dispatch_entry;

typedef struct						s_ssl
{
	uint8_t							quiet;
	uint8_t							rev;
	uint8_t							echo;
	uint8_t							mode;
	char							*key;
	char							*ifile;
	char							*ofile;
	char							*salt;
	char							*passwd;
	char							*initvec;
	char							**randfiles;
	t_queue							*tasks;
}									t_ssl;

int									dispatch(int argc, char **argv, int pn);
int									dispatch_shell(void);
void								debug_print_options(t_ssl opt);
void								int64_copy(unsigned char *dst, int64_t num);

int									is_dir(const char *str);

#endif
