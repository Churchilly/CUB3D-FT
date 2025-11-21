/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:05:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 03:55:33 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <strings.h>

t_collector	*pointer_storage(void *ptr)
{
	static t_collector *collector = NULL;

	if (ptr)
		collector = ptr;
	return (collector);
}

void	**get_section(t_section section)
{
	t_collector	*gc;

	gc = pointer_storage(NULL);
	if (!gc)
		return (NULL);
	if (section == STATIC)
		return ((void **)&gc->static_section);
	if (section == DYNAMIC)
		return ((void **)&gc->dynamic_section);
	if (section == TEMPORARY)
		return ((void **)&gc->temporary_section);
	if (section == WINDOW)
		return ((void **)&gc->win);
	return (NULL);
}

void	init_collector(t_collector *gc, t_window *win)
{
	bzero(gc, sizeof(t_collector));
	pointer_storage(gc);
	gc->win = win;
}

