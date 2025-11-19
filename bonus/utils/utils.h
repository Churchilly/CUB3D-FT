/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:15:39 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 01:17:37 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// Utility functions for string and character operations
int		is_space(char c);                    // Fixed: was ft_isspace
int		ft_strlen(const char *s);            // String length function
char	*ft_strjoin(char *str1, char *str2);  // Fixed: was strjoin
int	ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

#endif