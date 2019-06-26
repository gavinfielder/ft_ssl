/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:37:39 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/31 17:45:39 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>
#include <dirent.h>

int	is_dir(const char *str)
{
	DIR	*dir;

	if (((dir = opendir(str)) == NULL) && (errno == 20))
		return (0);
	if (dir != NULL)
		closedir(dir);
	return (1);
}
