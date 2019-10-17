/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 21:37:12 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/23 21:40:46 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *current;

	if (alst == NULL)
		return ;
	current = *alst;
	while (current != NULL)
	{
		tmp = current->next;
		ft_lstdelone(&current, del);
		current = tmp;
	}
	*alst = NULL;
}
