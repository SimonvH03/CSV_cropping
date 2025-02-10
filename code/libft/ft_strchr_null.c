/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_null.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:27:28 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/23 20:27:40 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the index of the first occurrence of a character in a string.
 *
 * This function returns the index of the first occurrence
 * 	of the character @p c in the string @p str.
 * If the character is not found, the function returns 0.
 *
 * @param str The string to search.
 * @param c The character to search for.
 * @return The index of the first occurrence of the character in the string.
 */
size_t	ft_strchr_null(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i] || str[i] == c)
			if (str[i++] == c)
				return (i);
	return (0);
}
