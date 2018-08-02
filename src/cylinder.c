/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 20:44:50 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/02 02:01:29 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_memory.h"

t_cylinder	*create_cylinder(t_vec3 p1, t_vec3 p2, double radius,
				t_colour colour)
{
	t_cylinder *cylinder;

	cylinder = f_memalloc(sizeof(t_cylinder));
	cylinder->origin = p1;
	cylinder->axis = p2;
	cylinder->radius = radius;
	cylinder->colour = colour;
	cylinder->does_intersect = cylinder_does_intersect;
	cylinder->intersect = cylinder_intersect;
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
