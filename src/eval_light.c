/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:32:00 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 17:16:44 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_math.h"

static t_colour	get_specular(t_intersect s_intersect, t_intersect l_intersect)
{
	t_vec3		half_dir;
	double		angle;
	t_colour	ret;

	half_dir = vec3_normalize(vec3_subtract(vec3_negate(s_intersect.ray.d),
					l_intersect.ray.d));
	angle = MAX(vec3_dot(half_dir, s_intersect.normal), 0.0);
	ret = colour_scale(C_WHITE, pow(angle, 64 * 8));
	return (ret);
}

static t_colour	get_diffuse(t_intersect s_intersect, t_intersect l_intersect,
					t_light light)
{
	double		angle;
	t_colour	ret;

	angle = MAX(-vec3_dot(l_intersect.ray.d, s_intersect.normal), 0);
	ret = colour_scale(light.colour, angle);
	ret = colour_multiply(s_intersect.shape->colour, ret);
	return (ret);
}

t_colour		eval_light(t_intersect s_intersect, t_vshape_set shapes,
					t_vlight_set lights)
{
	t_intersect		l_intersect;
	t_colour		ret;
	t_vec3			dir;
	t_light			light;
	unsigned int	i;

	ret = s_intersect.shape->colour;
	ret = colour_multiply(ret, AMBIENT_LIGHT);
	i = -1;
	while (++i < lights->total)
	{
		light = *(get_light(lights, i));
		dir = vec3_normalize(vec3_subtract(
			ray_calculate(s_intersect.ray, s_intersect.t), light.origin));
		cast_ray(RAY(light.origin, dir), shapes, &l_intersect);
		if (l_intersect.shape == s_intersect.shape)
		{
			ret = colour_add(ret, get_diffuse(s_intersect, l_intersect, light));
			ret = colour_add(ret, get_specular(s_intersect,
					l_intersect));
		}
	}
	return (ret);
}
