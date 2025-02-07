/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:37:08 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/15 22:37:15 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees an array of pointers.
 *
 * This function frees an array of pointers,
 * 	and then frees the array itself.
 *
 * @param array The array of pointers to free.
 */
void
	ft_arrclear(
		void **array)
{
	int	i;

	i = 0;
	if (array)
		while (array[i] != NULL)
			free(array[i++]);
	free(array);
}
