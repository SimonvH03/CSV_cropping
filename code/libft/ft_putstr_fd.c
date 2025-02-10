/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:51:42 by simon             #+#    #+#             */
/*   Updated: 2024/09/06 01:20:37 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes a string to a file descriptor.
 *
 * This function writes the string @p s to the file descriptor @p fd.
 *
 * @param s The string to write.
 * @param fd The file descriptor to write to.
 * @return The number of bytes written,
 * 	or -1 if an error occurs.
 */
int	ft_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}
