/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 19:07:51 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/29 22:15:57 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_memory.h"
#include "f_math.h"

t_sphere	*create_sphere(t_vec3 center, double radius, t_colour colour)
{
	t_sphere *sphere;

	sphere = f_memalloc(sizeof(t_sphere));
	sphere->center = center;
	//printf("%p -", sphere);
	//vec3_print("center", sphere->center);
	sphere->radius = radius;
	sphere->colour = colour;
	sphere->does_intersect = sphere_does_intersect;
	sphere->intersect = sphere_intersect;
	return(sphere);
}

bool		sphere_does_intersect(void *shape, t_ray ray)
{
	t_sphere	*sphere;
	double		b;
	double		c;
	double		des;

	sphere = (t_sphere*)shape;
	ray.p = vec3_subtract(ray.p, sphere->center);
	b = 2.0 * vec3_dot(ray.d, ray.p);
	c = vec3_length2(ray.p) - (sphere->radius * sphere->radius);
	des = (b * b) - (4 * c);
	if (des < 0)
		return (false);
	return (true);

}
bool		sphere_intersect(void *shape, t_ray ray, t_intersect *intersect)
{
	t_sphere	*sphere;
	double		b;
	double		c;
	double		des;
	double		t[2];

	intersect->ray = ray;
	sphere = (t_sphere*)shape;
	ray.p = vec3_subtract(ray.p, sphere->center);
	b = 2.0 * vec3_dot(ray.d, ray.p);
	c = vec3_length2(ray.p) - (sphere->radius * sphere->radius);
	des = (b * b) - (4 * c);
	if (des < 0)
		return (false);
	t[0] = (-b - sqrt(des)) / 2.0;
	t[1] = (-b + sqrt(des)) / 2.0;
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
