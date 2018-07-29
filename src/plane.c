/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 14:03:22 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/29 22:09:27 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "rtv1.h"
#include "f_memory.h"

t_plane	*create_plane(t_vec3 point, t_vec3 normal, t_colour colour)
{
	t_plane	*plane;

	plane = f_memalloc(sizeof(t_plane));
	plane->shape_type = PLANE;
	plane->p = point;
	plane->n = vec3_normalize(normal);
	plane->colour = colour;
	plane->intersect = plane_intersect;
	plane->does_intersect = plane_does_intersect;
	return (plane);
}

bool		plane_does_intersect(void *shape, t_ray ray)
{
	double	dot;
	t_plane	*plane;
	double	t;

	plane = (t_plane*)shape;
	dot = fabs(vec3_dot(ray.d, plane->n));
	if (!dot)
		return (false);
	t = vec3_dot(plane->p, ray.d) / dot;
	if (t <= RAY_T_MIN || t >= ray.t_max)
		return (false);
	return (true);
}

bool	plane_intersect(void *shape, t_ray ray, t_intersect *intersect)
{
	double	dot;
	t_plane	*plane;
	double	t;

	plane = (t_plane*)shape;
	dot = fabs(vec3_dot(ray.d, plane->n));
	//printf("ray: (%f, %f, %f)\n", ray.d.x, ray.d.y, ray.d.z);
	//printf("plane_n: (%f, %f, %f)\n", plane->n.x, plane->n.y, plane->n.z);
	//printf("%f\n", dot);
	//exit(0);
	if (!dot)
		return (false);
	t = vec3_dot(plane->p, ray.d) / dot;
	if (t <= RAY_T_MIN || t >= ray.t_max)
		return (false);
	intersect->ray = ray;
	intersect->shape = shape;
	intersect->t = t;
	intersect->normal = plane->n;
	return (true);
}