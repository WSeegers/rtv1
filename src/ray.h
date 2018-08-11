/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:21:15 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 19:34:18 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# define DOT_MIN	(1e-6)
# define RAY_T_MIN	(1e-6)
# define RAY_T_MAX	(1.0e30)

# include "libmat.h"
# include "scene.h"
# include "s_vector.h"

typedef	struct				s_ray
{
	t_vec3	p;
	t_vec3	d;
	double	t_max;
}							t_ray;

# define RAY(p, d)	((t_ray){p, d, RAY_T_MAX})

typedef t_vector			*t_vshape_set;
typedef t_vector			*t_vlight_set;
typedef struct s_intersect	t_intersect;

t_vec3						ray_calculate(t_ray ray, double t);
bool						cast_ray(t_ray ray, t_vshape_set shapes,
												t_intersect *intercect);

#endif
