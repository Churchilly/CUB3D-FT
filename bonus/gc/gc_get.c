/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:22:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/21 01:18:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc *get_gc()
{
    static t_gc *gc = NULL;

    if (!gc)
    {
        gc = new_gc();
        if (!gc)
            mem_err();
    }
    return (gc);
}

t_gc *get_crit_gc()
{
    static t_gc *gc = NULL;

    if (!gc)
    {
        gc = new_gc();
        if (!gc)
            mem_err();
    }
    return (gc);
}