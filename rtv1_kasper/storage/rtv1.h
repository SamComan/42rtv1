/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:15:34 by rkamegne          #+#    #+#             */
/*   Updated: 2019/09/16 15:57:41 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"

# define HEIGHT 800
# define WIDTH 800
# define FOV 60

/*
** ############ VECTOR STRUCT ###########
*/

int		deal_key(int key, void *param);

typedef struct	s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

typedef struct	s_vec3f
{
	float	x;
	float	y;
	float	z;
	float	length;
}				t_vec3f;

/*
**	########## FORMS STRUCT ##########
*/

typedef struct	s_sphere
{
	t_vec3f	c;
	float	r;
	int		color;
}				t_sphere;

/*
**	###################################
*/

/*
**	o = origin
**	dir = direciton
**	t = distance
*/

typedef struct	s_ray
{
	t_vec3f	o;
	t_vec3f	dir;
	int		t;
}				t_ray;

typedef struct	s_viewplane
{
	float	width;
	float	height;
	float	dist;
}				t_viewplane;

typedef struct	s_camera
{
	t_vec3f	pos;
	t_vec3f	dir;
}				t_camera;

typedef	struct	s_pixel
{
	float	x;
	float	y;
	float	xN;
	float	yN;
	float	xS;
	float	yS;
}				t_pixel;

typedef struct	s_data
{
	t_ray		ray;
	t_camera	camera;
	t_viewplane	vp;
	t_sphere	sphere;
}				t_data;

#endif
