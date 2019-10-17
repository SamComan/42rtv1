/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 01:24:27 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/22 19:42:03 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		deslen;

	d = dst;
	s = src;
	n = size;
	while (*d && n-- > 0)
		d++;
	deslen = d - dst;
	n = size - deslen;
	if (n == 0)
		return (deslen + ft_strlen(s));
	while (*s)
	{
		if (n > 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (deslen + ft_strlen(src));
}
