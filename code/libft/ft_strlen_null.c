/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_null.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:26:24 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/23 20:26:57 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the length of a string,
 * 	or 0 if the string is NULL.
 *
 * This function returns the length of the string @p str.
 * 	If the string is NULL, the function returns 0.
 *
 * @param str The string to get the length of.
 * @return The length of the string,
 * 	or 0 if the string is NULL.
 */
size_t	ft_strlen_null(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}
