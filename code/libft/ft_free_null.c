/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:24:45 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/15 21:57:51 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a pointer and sets it to NULL.
 *
 * This function frees the memory pointed to by @p pp,
 * 	and then sets the pointer to NULL.
 *
 * @param pp The pointer to free and set to NULL.
 * @return NULL.
 */
void	*ft_free_null(void **pp)
{
	free(*pp);
	*pp = NULL;
	return (NULL);
}
