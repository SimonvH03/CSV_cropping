/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:44:15 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/14 18:22:44 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends a string to a buffer.
 *
 * This function appends the string @p src to the buffer @p dst,
 * 	up to a maximum of @p size - 1 characters.
 * The buffer is null-terminated.
 *
 * @param dst The buffer to append the string to.
 * @param src The string to append.
 * @param size The size of the buffer.
 * @return The total length of the string that would have been created if there
 * was enough space, excluding the null-terminator.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	slen;
	size_t	dlen;
	size_t	i;

	dlen = ft_strlen_null(dst);
	slen = ft_strlen_null(src);
	i = 0;
	while (dlen + i + 1 < size && src[i])
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	if (dlen < size)
		return (dlen + slen);
	else
		return (size + slen);
}
