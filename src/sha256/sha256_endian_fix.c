/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_endian_fix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:04:28 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 18:04:45 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t	endian_swap(uint32_t num)
{
	uint32_t	dst;

	((uint8_t *)(&dst))[0] = ((uint8_t *)(&num))[3];
	((uint8_t *)(&dst))[1] = ((uint8_t *)(&num))[2];
	((uint8_t *)(&dst))[2] = ((uint8_t *)(&num))[1];
	((uint8_t *)(&dst))[3] = ((uint8_t *)(&num))[0];
	return (dst);
}

void		sha256_endian_swap_words(void *arr, int len)
{
	int			i;

	i = -1;
	while (++i < len)
		((uint32_t *)arr)[i] = endian_swap(((uint32_t *)arr)[i]);
}
