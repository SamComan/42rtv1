/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:09:42 by rkamegne          #+#    #+#             */
/*   Updated: 2019/09/16 12:31:06 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*win_ptr;

	(void) ac;
	(void) av;
	if (!(mlx_ptr = mlx_init()))
		ft_error("Init of the mlx_ptr failed");
	if (!(win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "rtv1")))
		ft_error("Init of the win_ptr failed");
	mlx_key_hook(win_ptr, deal_key, mlx_ptr);
	mlx_loop(mlx_ptr);
	return (0);
}
