/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 20:44:50 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/04 23:29:17 by wseegers         ###   ########.fr       */
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
	cylinder->does_intersect = cylinder_does_intersect;
	cylinder->intersect = cylinder_intersect;
	angle = acos(vec3_dot(VEC3(0,1,0), axis) / vec3_length(axis));
	cylinder->raymat = mat4_rotate(mat, -angle, vec3_cross(axis, VEC3(0, 1, 0)));
	cylinder->mat = mat4_inverse(cylinder->raymat);
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
	ray.p = vec3_transform(ray.p, cyl->raymat);
	ray.d = vec3_transform(ray.d, cyl->raymat);
	double a, b, c, des, t;

	a = pow(ray.d.x, 2) + pow(ray.d.z, 2);
	b = 2 * (ray.p.x * ray.d.x + ray.p.z * ray.d.z);
	c = pow(ray.p.x, 2) + pow(ray.p.z, 2) - pow(cyl->radius, 2);

	des = (b * b) - (4 * a * c);
	if (des < RAY_T_MIN)
		return (false);
	t = (-b - sqrt(des)) / (2.0 * a);
	if (t > RAY_T_MIN && t < ray.t_max)
		intersect->t = t;
	else
		return (false);
	ray.p = ray_calculate(ray, t);
	// vec3_print("p", ray.p);
	intersect->normal = vec3_transform(VEC3(ray.p.x, 0, ray.p.z), cyl->mat);
	// vec3_print("p", intersect->normal);
	// mat4_print(cyl->raymat);
	// mat4_print(cyl->mat);
	// exit (0);
	return (true);
}


bool			cylinder_intersect_v1(void *shape, t_ray ray,
					t_intersect *intersect)
{
	t_cylinder	*cyl;
	
	intersect->ray = ray;
	intersect->shape = shape;
	cyl = (t_cylinder*)shape;

	ray.p = vec3_subtract(ray.p, cyl->origin);
	t_vec3	vCrossNormal = vec3_cross(ray.d, cyl->axis);
	double	mag = vec3_length(vCrossNormal);
	vCrossNormal = vec3_normalize(vCrossNormal);
	double	d = fabs(vec3_dot(ray.p, vCrossNormal));

	if (d < cyl->radius)
	{
		t_vec3 vU = vec3_cross(ray.p, cyl->axis);
      	double t = -(vec3_dot(vU, vCrossNormal) / mag);

		t_vec3 vO = vec3_normalize(vec3_cross(vCrossNormal, cyl->axis));
    	double s = fabs(sqrt(cyl->radius * cyl->radius - d * d) /
                          vec3_dot(ray.d, vO));
		intersect->t = t - s;
		if (intersect->t < 0)
			return (false);
		intersect->normal = vCrossNormal;
	}
	else
		return (false);
	return (true);
}

bool		cylinder_does_intersect(void *shape, t_ray ray)
{
	return (true);
}
