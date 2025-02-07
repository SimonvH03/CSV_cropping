/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:19:24 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/19 18:23:47 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares two strings.
 *
 * This function compares the first @p n bytes of the strings @p a and @p b.
 * The comparison is case-sensitive.
 *
 * @param a The first string to compare.
 * @param b The second string to compare.
 * @param n The number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero
 * if the first @p n bytes of @p a are found to be
 * less than, equal to, or greater than the first @p n bytes of @p b.
 */
int	ft_strncmp(const char *a, const char *b, size_t n)
{
	const unsigned char	*uca = (unsigned char *)a;
	const unsigned char	*ucb = (unsigned char *)b;

	while (n-- && (*uca || *ucb))
		if (*uca++ != *ucb++)
			return (*(uca - 1) - *(ucb - 1));
	return (0);
}
