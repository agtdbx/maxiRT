/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:35:07 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/17 11:35:10 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

//****************************************************************************//
//**** LIBFT: SIMPLE SELFMADE LIBC *******************************************//

//----------------------------------------------------------------------------//
//---- GET NEXT LINE ---------------------------------------------------------//

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 64
# endif//GNL_BUFFER_SIZE

# define GNL_STATIC_INITIALIZER ""

typedef char	t_gnl_buffer[GNL_BUFFER_SIZE];

char	*ft_gnl_r(
			int fd,
			t_gnl_buffer save_buf);

void	ft_gnl_init_buffer(
			t_gnl_buffer save_buf);

//----------------------------------------------------------------------------//
//---- IO OPERATIONS ---------------------------------------------------------//

ssize_t	ft_putstr_fd(
			char const *str,
			int fd);

ssize_t	ft_putstr(
			char const *str);

ssize_t	ft_puterr(
			char const *str);

//----------------------------------------------------------------------------//
//---- CHAR TESTS ------------------------------------------------------------//

bool	ft_isdigit(
			int c);

//----------------------------------------------------------------------------//
//---- STRING READING --------------------------------------------------------//

size_t	ft_strlen(
			char const *str);

char	*ft_strchr(
			char const *str,
			int c);

size_t	ft_strspn(
			char const *str,
			char const *accept);

size_t	ft_strcspn(
			char const *str,
			char const *reject);

char	*ft_basename(
			char const *path_to_file);

//----------------------------------------------------------------------------//
//---- STRING TESTS ----------------------------------------------------------//

int		ft_strcmp(
			const char *s1,
			const char *s2);

int		ft_strncmp(
			const char *s1,
			const char *s2,
			size_t n);

bool	ft_strendswith(
			char const *str,
			char const *suffix);

//----------------------------------------------------------------------------//
//---- STRING COPY -----------------------------------------------------------//

void	ft_strlcpy(
			char *restrict dst,
			char const *restrict src,
			size_t dst_size);

//----------------------------------------------------------------------------//
//---- STRING DUPLICATION ----------------------------------------------------//

char	*ft_strdup(
			char const *str);

char	*ft_substr(
			char const *src,
			size_t start,
			size_t len);

//----------------------------------------------------------------------------//
//---- STRING TOKENIZATION ---------------------------------------------------//

char	*ft_strtok_r(
			char *restrict str,
			char const *restrict sep,
			char **restrict saveptr);

char	*ft_strsep(
			char **restrict stringp,
			char const *restrict sep);

//----------------------------------------------------------------------------//
//---- STRING TO NUMERIC TYPE CONVERSION -------------------------------------//

int		ft_strtoi(
			char const *restrict nptr,
			char **restrict endptr);

float	ft_strtof(
			char const *restrict nptr,
			char **restrict endptr);

//----------------------------------------------------------------------------//
//---- MEMORY ----------------------------------------------------------------//

// ft_memdel(**ptr) frees *ptr and sets it to NULL
void	ft_memdel(
			void *bufptr);

void	*ft_memcpy(
			void *restrict dst,
			void const *restrict src,
			size_t src_size);

void	*ft_memdup(
			void const *buf,
			size_t buf_size);

#endif//LIBFT_H
