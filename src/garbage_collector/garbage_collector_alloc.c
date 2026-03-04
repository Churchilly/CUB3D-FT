/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_alloc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 01:03:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 04:29:31 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include <errno.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

static void	collector_add(void *new, t_section section_name)
{
	t_gc_node	*new_gc_node;
	t_gc_node	**section;

	new_gc_node = (t_gc_node *)malloc(sizeof(t_gc_node));
	if (!new_gc_node)
	{
		printf("MEMORY ALLOCATION FAILED: %d\n", errno);
		exit(1);
	}
	section = (t_gc_node **)get_section(section_name);
	new_gc_node->data = new;
	new_gc_node->next = *section;
	*section = new_gc_node;
}

void	*alloc(size_t size, t_section sec)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		printf("MEMORY ALLOCATION FAILED: %d\n", errno);
		exit(1);
	}
	bzero(new, size);
	collector_add(new, sec);
	return (new);
}
