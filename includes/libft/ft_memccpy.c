/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 13:04:03 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/22 20:23:41 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *src_cpy;
	unsigned char *dest_cpy;
	unsigned char ch;

	src_cpy = (unsigned char*)src;
	dest_cpy = (unsigned char*)dst;
	ch = (unsigned char)c;
	while (n > 0)
	{
		*dest_cpy = *src_cpy;
		if (*src_cpy == ch)
			return ((void*)dest_cpy + 1);
		dest_cpy++;
		src_cpy++;
		n--;
	}
	return (NULL);
}
