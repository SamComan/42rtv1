/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 19:04:27 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/22 20:26:34 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*str;

	str = s1;
	while (*str)
		str++;
	i = 0;
	while (s2[i] && i < n)
	{
		str[i] = s2[i];
		i++;
	}
	str[i] = '\0';
	return (s1);
}
