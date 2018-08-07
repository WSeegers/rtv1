/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 14:03:22 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/07 11:53:40 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "rtv1.h"
#include "f_memory.h"

t_plane	*plane_create(t_vec3 point, t_vec3 normal, t_colour colour)
{
	t_plane	*plane;

	plane = f_memalloc(sizeof(t_plane));
	plane->shape_type = PLANE;
	plane->p = point;
	plane->n = vec3_normalize(normal);
	plane->colour = colour;
	plane->intersect = plane_intersect;
	return (plane);
}

bool	plane_intersect(void *shape, t_ray ray, t_intersect *intersect)
{
	double	dot;
	t_plane	*plane;
	double	t;

	plane = (t_plane*)shape;
	dot = vec3_dot(ray.d, plane->n);
	if (fabs(dot) < DOT_MIN)
		return (false);
	t = vec3_dot(vec3_subtract(plane->p, ray.p), plane->n) / dot;
	if (t <= RAY_T_MIN || t >= ray.t_max)
		return (false);
	intersect->ray = ray;
	intersect->shape = shape;
	intersect->t = t;
	intersect->normal = plane->n;
	return (true);
}