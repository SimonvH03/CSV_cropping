/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:11:14 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/16 17:01:04 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdup_gnl(const char *buffer)
{
	size_t	i;
	char	*temptr;

	i = ft_strchr_null(buffer, '\n');
	if (i == 0)
		i = ft_strlen_null(buffer);
	temptr = (char *)malloc((i + 1) * sizeof(char));
	if (temptr == NULL)
		return (NULL);
	temptr[i] = '\0';
	while (i--)
		temptr[i] = buffer[i];
	return (temptr);
}

static char	*ft_strjoin_gnl(char **nextline, const char *buffer)
{
	char			*temptr;
	const size_t	n_len = ft_strlen_null(*nextline);
	const size_t	b_len = ft_strlen_null(buffer);
	const size_t	b_nl = ft_strchr_null(buffer, '\n');
	size_t			i;

	if (b_nl == 0)
		i = n_len + b_len;
	else
		i = n_len + b_nl;
	temptr = (char *)malloc((i + 1) * sizeof(char));
	if (temptr == NULL)
		return (ft_free_null((void *)nextline));
	temptr[i] = '\0';
	while (i-- > n_len)
		temptr[i] = buffer[i - n_len];
	i += 1;
	while (i--)
	{
		temptr[i] = (*nextline)[i];
	}
	ft_free_null((void *)nextline);
	return (temptr);
}

static char	*ft_read_gnl(char **nextline, char *buffer, int fd)
{
	int	bytes_read;

	bytes_read = GNL_BUFFER_SIZE;
	while (bytes_read == GNL_BUFFER_SIZE && !ft_strchr_null(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, GNL_BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free_null((void *)nextline));
		buffer[bytes_read] = '\0';
		*nextline = ft_strjoin_gnl(nextline, buffer);
		if (*nextline == NULL)
			return (NULL);
	}
	return (*nextline);
}

static void	ft_remainder_gnl(char *buffer)
{
	const char	*remainder = buffer + ft_strchr_null(buffer, '\n');
	size_t		i;

	i = 0;
	if (remainder > buffer)
	{
		while (remainder[i])
		{
			buffer[i] = remainder[i];
			i++;
		}
	}
	ft_bzero((void *)buffer + i, GNL_BUFFER_SIZE - i);
}

/**
 * Reads a line from the given file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @return A pointer to the read line,
 * 	or NULL if an error occurs or the end of the file is reached.
 */
char	*ft_get_next_line(int fd)
{
	static char	buffer[GNL_BUFFER_SIZE + 1];
	char		*nextline;

	if (GNL_BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	nextline = ft_strdup_gnl(buffer);
	if (nextline == NULL)
	{
		ft_bzero((void *)buffer, GNL_BUFFER_SIZE + 1);
		return (NULL);
	}
	nextline = ft_read_gnl(&nextline, buffer, fd);
	if (nextline == NULL)
	{
		ft_bzero((void *)buffer, GNL_BUFFER_SIZE + 1);
		return (NULL);
	}
	ft_remainder_gnl(buffer);
	if (nextline[0] == 0)
		return (ft_free_null((void *)&nextline));
	return (nextline);
}
