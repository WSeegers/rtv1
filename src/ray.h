/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:21:15 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 18:16:40 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RAY_H
# define RAY_H

# define DOT_MIN	(1e-6)
# define RAY_T_MIN	(1e-6)
# define RAY_T_MAX	(1.0e30)

# include "vec3.h"

typedef	struct	s_ray
{
	t_vec3	p;
	t_vec3	d;
	double	t_max;
}				t_ray;

# define RAY(p, d)	((t_ray){p, d, RAY_T_MAX})

t_vec3	ray_calculate(t_ray ray, double t);

#endif