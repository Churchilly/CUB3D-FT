/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:59:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 02:15:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string.h"
#include "../garbage_collector/garbage_collector.h"

char	*ft_strjoin(char *str1, char *str2, t_section sec)
{
	char	*res;
	char	*ret;

	res = alloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1), sec);
	if (!res)
		return (NULL);
	ret = res;
	while (*str1)
		*res++ = *str1++;
	while (*str2)
		*res++ = *str2++;
	*res = '\0';
	return (ret);
}
// note that shi