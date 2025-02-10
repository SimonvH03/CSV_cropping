/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:53:50 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/16 16:50:08 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 1500
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

enum	e_return
{
	RETURN_ERROR = -1,
	RETURN_SUCCESS,
	RETURN_FAILURE
};

void	ft_arrclear(void **array);

int		ft_atoi(const char *c);
void	ft_bzero(void *src, size_t n);
void	*ft_free_null(void **pp);

char	*ft_get_next_line(int fd);
int		ft_intlen(int n);

char	*ft_itoa(int n);

int		ft_putstr_fd(char *str, int fd);

char	**ft_split(const char *str, char c);
char	*ft_strchr(const char *str, int c);
size_t	ft_strchr_null(const char *str, int c);

char	*ft_strdup_d(const char *str, const char delim);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t l);
size_t	ft_strlcpy(char *dst, const char *src, size_t l);
size_t	ft_strlen(const char *c);
size_t	ft_strlen_null(const char *str);
int		ft_strncmp(const char *a, const char *b, size_t n);

#endif
