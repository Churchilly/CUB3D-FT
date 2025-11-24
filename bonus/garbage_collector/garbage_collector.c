/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:05:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 08:20:28 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <strings.h>
#include "../main/main.h"

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
	if (section == TEXTURES)
		return ((void **)gc->textures);
	return (NULL);
}

void	init_collector(t_collector *gc, t_main *g)
{
	bzero(gc, sizeof(t_collector));
	pointer_storage(gc);
	gc->win = &(g->window);
	gc->textures[0] = &(g->map.texture_ea.img);
	gc->textures[1] = &(g->map.texture_we.img);
	gc->textures[2] = &(g->map.texture_so.img);
	gc->textures[3] = &(g->map.texture_no.img);
	gc->textures[4] = &(g->map.texture_f.img);
}

