/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 13:24:20 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/24 18:12:19 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *str1;
	char *str2;

	str1 = (char*)src;
	str2 = (char*)dst;
	if (str1 < str2)
	{
		str1 = str1 + len - 1;
		str2 = str2 + len - 1;
		while (len > 0)
		{
			*str2-- = *str1--;
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
