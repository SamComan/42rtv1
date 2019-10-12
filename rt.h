/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:56:39 by sacoman           #+#    #+#             */
/*   Updated: 2019/10/12 17:10:14 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_H_
# define _RT_H_


typedef	struct	s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_vec4;

typedef	struct 	s_camera
{
	t_vec4	lookat;
	t_vec4	position;
	t_vec4	up;
	t_vec4	forward;
	t_vec4	left;
	double	focal_lenght;
	double	frame_width;
	double	frame_height;
	
}				t_camera;


typedef	struc	s_ray
{
	t_vec4	origin;
	t_vec4	dir;
	double	t;
}				t_ray;

#endif
