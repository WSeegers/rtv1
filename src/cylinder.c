/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 20:44:50 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 21:02:18 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_memory.h"

t_cylinder	*create_cylinder(t_vec3 p1, t_vec3 axis, double radius,
				t_colour colour)
{
	t_cylinder *cylinder;
	double		angle;
	t_mat4		mat;

	mat4_init(&mat);
	cylinder = f_memalloc(sizeof(t_cylinder));
	cylinder->origin = p1;
	cylinder->axis = vec3_normalize(axis);
	cylinder->radius = radius;
	cylinder->colour = colour;
	cylinder->intersect = cylinder_intersect;
	angle = acos(vec3_dot(VEC3(0,1,0), axis) / vec3_length(axis));
	cylinder->imat = mat4_rotate(mat, -angle, vec3_cross(axis, VEC3(0, 1, 0)));
	cylinder->mat = mat4_inverse(cylinder->imat);
	return (cylinder);
}

bool			cylinder_intersect(void *shape, t_ray ray,
					t_intersect *intersect)
{
	t_cylinder	*cyl;

	intersect->ray = ray;
	intersect->shape = shape;
	cyl = (t_cylinder*)shape;

	ray.p = vec3_subtract(ray.p, cyl->origin);
	ray.p = vec3_transform(ray.p, cyl->imat);
	ray.d = vec3_transform(ray.d, cyl->imat);
	double a, b, c, des, t;

	a = pow(ray.d.x, 2) + pow(ray.d.z, 2);
	b = 2 * (ray.p.x * ray.d.x + ray.p.z * ray.d.z);
	c = pow(ray.p.x, 2) + pow(ray.p.z, 2) - pow(cyl->radius, 2);

	des = (b * b) - (4 * a * c);
	if (des < RAY_T_MIN)
		return (false);
	t = (-b - sqrt(des)) / (2.0 * a);
	if (t > RAY_T_MIN && t < ray.t_max)
		intersect->t = fabs(t);
	else
		return (false);
	// vec3_print("rat->t", ray_calculate(ray, t));
	ray.p = ray_calculate(ray, t);
	ray.p = vec3_normalize(VEC3(ray.p.x, 0.0, ray.p.z));
	intersect->normal = vec3_transform(ray.p, cyl->mat);
	// vec3_print("norm", intersect->normal);
	return (true);
}