/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:15:39 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/30 00:35:05 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>

int		is_space(char c);
int		ft_strlen(const char *s);
char	*ft_strjoin(char *str1, char *str2);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);

#endif