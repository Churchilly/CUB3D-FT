/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:22:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/27 18:55:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	create_objects_static(t_main *g)
{
	create_fireballs(g);
	create_particles(g);
	create_enemies(g);
}

void	create_objects_dynamic(t_main *g)
{
	create_barriers(g);
	create_orbs(g);
}
