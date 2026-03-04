/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:56:56 by root              #+#    #+#             */
/*   Updated: 2025/11/28 17:24:17 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_char(char ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

bool	is_upper(char ch)
{
	return (ch >= 'A' && ch <= 'Z');
}

bool	is_num(char ch)
{
	return (ch >= '0' && ch <= '?');
}

bool	is_symbol(char ch)
{
	return (ch >= ' ' && ch <= '/');
}
