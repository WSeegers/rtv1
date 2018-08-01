/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .cylinder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 20:44:50 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 21:06:50 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

bool		cylinder_intersect(void *shape, t_ray ray, t_intersect *intersect)
{
	//t_cylinder	*cylinder;
	t_shape		*cylinder;
	double		a;
	double		b;
	double		c;
	double		des;
	double		t[2];

	double		radius;

	intersect->ray = ray;
	//cylinder = (t_cylinder*)shape;
	cylinder = (t_shape*)shape;
	a =	pow(ray.d.x, 2) + pow(ray.d.y, 2);
	b = 2 * ((ray.p.x * ray.d.x) + (ray.p.y * ray.d.y));
	c = pow(ray.p.x, 2) + pow(ray.p.y, 2) - radius;
	des = (b * b) - (4 * c);
	if (des < 0)
		return (false);
	t[0] = (-b - sqrt(des)) / 2.0 * a;
	t[1] = (-b + sqrt(des)) / 2.0 * a;
	if (t[0] > RAY_T_MIN && t[0] < ray.t_max)
		intersect->t = t[0];
	else if (t[1] > RAY_T_MIN && t[1] < ray.t_max)
		intersect->t = t[1];
	else
		return(false);
	intersect->shape = shape;
	intersect->normal = vec3_normalize(ray_calculate(ray, intersect->t));
	return (true);
}

