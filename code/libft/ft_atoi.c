/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:55:23 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/19 18:23:47 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to an integer.
 *
 * This function converts the initial portion of the string pointed to by @p c
 * to an integer representation.
 * The string may begin with an arbitrary amount of white space,
 * 	followed by an optional plus or minus sign, and then a sequence of digits.
 * The conversion stops at the first character that is not a digit,
 * 	and the result is returned.
 *
 * @param c The string to convert to an integer.
 * @return The integer representation of the string.
 */
int	ft_atoi(const char *c)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*c == ' ' || (*c >= 9 && *c <= 13))
		c++;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			sign = -sign;
		c++;
	}
	while (*c >= '0' && *c <= '9')
		num = (num * 10) + (*c++ - '0');
	return (sign * num);
}
