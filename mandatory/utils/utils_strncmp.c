/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:56:13 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 22:11:17 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && *s1 == *s2 && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
