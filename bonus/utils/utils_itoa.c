/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:13:02 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/20 01:17:31 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	count_digits(int n)
{
	unsigned int	digits;
	unsigned int	h;

	if (n == 0)
		return (1);
	digits = 0;
	if (n == -2147483648)
		h = n;
	else if (n < 0)
		h = -n;
	else
		h = n;
	while (h >= 1)
	{
		digits++;
		h = h / 10;
	}
	if (n < 0)
		digits++;
	return (digits);
}

static unsigned int	power_of10(unsigned int len)
{
	unsigned int	i;

	i = 1;
	while (len--)
		i = i * 10;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;
	int				cnt;

	len = count_digits(n);
	cnt = 0;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[cnt++] = '-';
		len--;
		n = n * -1;
	}
	while (len--)
	{
		res[cnt++] = n / power_of10(len) + 48;
		n = n % power_of10(len);
	}
	res[cnt] = '\0';
	return (res);
}