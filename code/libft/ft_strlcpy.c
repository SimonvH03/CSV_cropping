/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:18:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/14 18:23:00 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies a string to a buffer.
 *
 * This function copies @p size - 1 characters from the string @p src
 * 	to the buffer @p dst.
 * The buffer is null-terminated.
 *
 * @param dst The buffer to copy the string to.
 * @param src The string to copy.
 * @param size The size of the buffer.
 * @return The total length of the string that would have been created if there
 * was enough space, excluding the null-terminator.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	return (ft_strlen_null(src));
}
