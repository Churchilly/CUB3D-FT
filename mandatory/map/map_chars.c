/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 23:17:24 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/30 00:41:10 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_space(c) || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	char_to_int(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (48);
	else if (c == '1')
		return (49);
	else if (is_space(c))
		return (50);
	return (83);
}
