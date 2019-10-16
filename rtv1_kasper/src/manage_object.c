/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:12:55 by rkamegne          #+#    #+#             */
/*   Updated: 2019/09/30 16:50:59 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj		*new_object(void *inf, int id)
{
	t_obj *new;

	if (!(new = (t_obj *)malloc(sizeof(*new))))
		return (NULL);
	new->obj = inf;
	new->id = id;
	new->next = NULL;
	return (new);
}

void		add_object(t_obj **list, t_obj *new)
{
	if (!*list && new)
	{
		*list = new;
		return ;
	}
	if (*list && new)
	{
		new->next = *list;
		*list = new;
	}
}

void		free_obj_list(t_obj **list, char *str)
{
	t_obj	*temp;

	temp = *list;
	while (temp)
	{
		free(temp->obj);
		temp = temp->next;
	}
	*list = NULL;
	if (str)
		ft_putendl(str);
	exit(0);
}

void		free_all_lists(t_rt *specs)
{
	t_obj	*temp;

	temp = specs->obj_list;
	while (temp)
	{
		free(temp->obj);
		temp = temp->next;
	}
	specs->obj_list = NULL;
	temp = specs->light_list;
	while (temp)
	{
		free(temp->obj);
		temp = temp->next;
	}
	specs->light_list = NULL;
}
