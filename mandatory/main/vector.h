/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:03:40 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 22:44:28 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector		t_vector;
typedef struct s_vector_int	t_vector_int;

struct						s_vector
{
	double					x;
	double					y;
};

struct						s_vector_int
{
	int						x;
	int						y;
};

#endif