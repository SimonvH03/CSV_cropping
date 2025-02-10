/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:37:50 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/14 18:23:14 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Joins two strings.
 *
 * This function joins the strings @p s1 and @p s2.
 * The newly allocated string is null-terminated.
 *
 * @param s1 The first string to join.
 * @param s2 The second string to join.
 * @return A pointer to the newly allocated string,
 * 	or NULL if memory allocation fails.
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*ptr;
	const size_t	s1len = ft_strlen_null(s1);
	const size_t	s2len = ft_strlen_null(s2);

	ptr = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, s1len + 1);
	ft_strlcat(ptr, s2, s1len + s2len + 1);
	return (ptr);
}
