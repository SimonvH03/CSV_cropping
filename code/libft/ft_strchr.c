/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:43:44 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/19 18:23:47 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the first occurrence of a character in a string.
 *
 * This function returns a pointer
 * 	to the first occurrence of the character @p c in the string @p str.
 * If the character is not found,the function returns NULL.
 *
 * @param str The string to search.
 * @param c The character to search for.
 * @return A pointer to the first occurrence of the character in the string.
 */
char	*ft_strchr(const char *str, int c)
{
	while (*str || *str == (char)c)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
