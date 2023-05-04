/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:45:38 by tdubois           #+#    #+#             */
/*   Updated: 2023/05/04 13:49:31 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>

/**
 * Swap two pointers
 * @param[in] ptr1 A pointer toward the first pointer
 * @param[in] ptr2 A pointer toward the second pointer
 */
void	ft_swap(
			void *pptr1,
			void *pptr2)
{
	void	**const ptr1 = pptr1;
	void	**const ptr2 = pptr2;
	void	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}
