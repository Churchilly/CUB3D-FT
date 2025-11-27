/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:11:35 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/27 19:31:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../garbage_collector/garbage_collector.h"
#include <stdlib.h>

static unsigned int	split_count(char const *s, char c)
{
	unsigned int	counter;

	counter = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			counter++;
			while (*s != c && *s)
				s++;
		}
	}
	return (counter);
}

static unsigned int	short_len(const char *s, char c)
{
	unsigned int	counter;

	counter = 0;
	while (*s != c && *s)
	{
		counter++;
		s++;
	}
	return (counter);
}

static void	write_word(char **str, const char **s, unsigned int len)
{
	unsigned int	counter;

	counter = 0;
	while (counter < len)
	{
		(*str)[counter] = **s;
		counter++;
		(*s)++;
	}
	(*str)[counter] = '\0';
}

char	**ft_split(char const *s, char c, t_section sec)
{
	char			**splitted;
	unsigned int	word_count;
	unsigned int	counter;

	if (!s)
		return (NULL);
	word_count = split_count(s, c);
	splitted = alloc((word_count + 1) * sizeof(char *), sec);
	counter = 0;
	while (counter < word_count)
	{
		while (*s == c && *s)
			s++;
		splitted[counter] = alloc(short_len(s, c) + 1, sec);
		write_word(&splitted[counter], &s, short_len(s, c));
		counter++;
	}
	splitted[counter] = NULL;
	return (splitted);
}
