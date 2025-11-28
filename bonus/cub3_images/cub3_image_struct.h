/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_image_struct.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:38:34 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 18:42:13 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_IMAGE_STRUCT_H
# define CUB3_IMAGE_STRUCT_H

typedef struct s_cub3_image	t_cub3_image;
typedef t_cub3_image		t_im;

struct						s_cub3_image
{
	int						*image;
	int						width;
	int						height;
};

#endif
