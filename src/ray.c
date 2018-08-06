/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 01:40:44 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 18:14:18 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

bool	cast_ray(t_ray ray, t_vshape_set shapes, t_intersect *intercect)
{
	int			i;
	t_shape		*shape;
	t_intersect	temp;
	t_colour	col;

	i = -1;
	col = C_BLACK;
	ray.t_max = RAY_T_MAX;
	while (++i < shapes->total)
	{
		shape = get_shape(shapes, i);
		if (shape->intersect(shape, ray, &temp))
		{
			if (temp.t < ray.t_max)
			{
				intercect->shape = shape;
				ray.t_max = temp.t;
				*intercect = temp;
			}
		}
	}
	return (ray.t_max != RAY_T_MAX);
}

t_vec3	ray_calculate(t_ray ray, double t)
{
	return (vec3_add(ray.p, vec3_scale(t, ray.d)));
}
