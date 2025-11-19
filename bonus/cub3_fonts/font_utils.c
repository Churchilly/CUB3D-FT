/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:56:56 by root              #+#    #+#             */
/*   Updated: 2025/11/18 15:00:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool is_char(char ch)
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));  // ✅ && olmalı
}

bool is_upper(char ch)
{
    return (ch >= 'A' && ch <= 'Z');
}

bool is_num(char ch)
{
    return (ch >= '0' && ch <= '9');
}

bool is_symbol(char ch)
{
    return (ch >= ' ' && ch <= '/');
}