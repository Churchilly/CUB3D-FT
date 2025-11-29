/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:59:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:51:25 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gc/gc.h"
#include "utils.h"
#include <stdlib.h>

char	*ft_strjoin(char *str1, char *str2)
{
	char	*res;
	char	*ret;

	res = alloc_crit(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
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
