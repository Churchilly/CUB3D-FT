/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:44:50 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 16:02:05 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
// next spell
void	next_spell(t_main *g)
{
	static int	state = 0;
	
	if (state == 0)
	{
		state++;
	}
	else if (state == 100)
	{
		state = 0;
	}
	else
	{
		state++;
	}
}
// prev spell
// idle spellbook
// cast spell