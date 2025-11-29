/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:15:39 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:57:25 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../garbage_collector/garbage_collector.h"

char	*ft_strjoin(char *str1, char *str2, t_section section);
char	**ft_split(char const *s, char c, t_section section);
char	*ft_itoa(int n, t_section section);

#endif