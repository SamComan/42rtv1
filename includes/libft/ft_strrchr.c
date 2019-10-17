/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 01:35:49 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/22 20:34:31 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int pos;

	pos = ft_strlen(s);
	while (pos >= 0)
	{
		if (s[pos] == (char)c)
			return ((char*)&s[pos]);
		pos--;
	}
	return (NULL);
}
