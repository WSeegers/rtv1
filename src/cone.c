/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 20:45:55 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/05 21:11:50 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_memory.h"

t_cone	*create_cone(t_vec3 p1, t_vec3 axis, double unit_radius,
				t_colour colour)
{
	t_cone *cone;
	double		angle;
	t_mat4		mat;

	mat4_init(&mat);
	cone = f_memalloc(sizeof(t_cone));
	cone->origin = p1;
	cone->axis = vec3_normalize(axis);
	cone->radius = unit_radius;
	cone->colour = colour;
	cone->does_intersect = cone_does_intersect;
	cone->intersect = cone_intersect;
	angle = acos(vec3_dot(VEC3(0,1,0), axis) / vec3_length(axis));
	cone->imat = mat4_rotate(mat, -angle, vec3_cross(axis, VEC3(0, 1, 0)));
	cone->mat = mat4_inverse(cone->imat);
	return (cone);
}

bool	cone_intersect(void *shape, t_ray ray,
					t_intersect *intersect)
{
	t_cone		*cone;
	
	intersect->ray = ray;
	intersect->shape = shape;
	cone = (t_cone*)shape;

	ray.p = vec3_subtract(ray.p, cone->origin);
	ray.p = vec3_transform(ray.p, cone->imat);
	ray.d = vec3_transform(ray.d, cone->imat);
	double a, b, c, des, t;

	a = pow(ray.d.x, 2) + pow(ray.d.z, 2) - pow(ray.d.y * cone->radius, 2);
	b = 2 * (ray.p.x * ray.d.x + ray.p.z * ray.d.z - ray.p.y * ray.d.y * pow(cone->radius, 2));
	c = pow(ray.p.x, 2) + pow(ray.p.z, 2) - pow(ray.p.y * cone->radius, 2);

	des = (b * b) - (4 * a * c);
	if (des < RAY_T_MIN)
		return (false);
	t = (-b - sqrt(des)) / (2.0 * a);
	if (t > RAY_T_MIN && t < ray.t_max)
		intersect->t = t;
	else
		return (false);
	ray.p = ray_calculate(ray, t);
	intersect->normal = vec3_transform(VEC3(ray.p.x, 1 / cone->radius, ray.p.z), cone->mat);
	return (true);
}

bool	cone_does_intersect(void *shape, t_ray ray)
{
	return (true);
}