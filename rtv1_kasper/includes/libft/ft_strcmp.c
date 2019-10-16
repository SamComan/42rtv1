/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:17:16 by rkamegne          #+#    #+#             */
/*   Updated: 2018/10/12 21:57:15 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *c1;
	unsigned char *c2;

	c1 = (unsigned char*)s1;
	c2 = (unsigned char*)s2;
	while (*c1 != '\0' && *c2 != '\0' && *c1 == *c2)
	{
		c1++;
		c2++;
	}
	return (*c1 - *c2);
}
