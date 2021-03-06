/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:25:02 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 19:34:32 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include <stdbool.h>
# include "rtv1.h"
# include "colour.h"
# include "libmat.h"
# include "ray.h"
# include "s_vector.h"

typedef int		t_shape_type;

# define PLANE		(0)
# define SPHERE		(1)
# define CYLINDER	(2)
# define CONE		(3)

typedef struct s_ray		t_ray;
typedef struct s_intersect	t_intersect;

typedef struct				s_shape
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

}							t_shape;

typedef struct				s_plane
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3			p;
	t_vec3			n;
}							t_plane;

t_plane						*plane_create(t_vec3 point, t_vec3 normal,
								t_colour colour);
bool						plane_intersect(void *shape, t_ray ray,
								t_intersect *intersect);

typedef struct				s_sphere
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3			center;
	double			radius;
}							t_sphere;

t_sphere					*create_sphere(t_vec3 center, double radius,
								t_colour colour);
bool						sphere_intersect(void *shape, t_ray ray,
								t_intersect *intersect);

typedef struct				s_cylinder
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3			origin;
	t_vec3			axis;
	double			radius;
	t_mat4			mat;
	t_mat4			imat;
}							t_cylinder;

t_cylinder					*create_cylinder(t_vec3 origin, t_vec3 axis,
								double radius, t_colour colour);
bool						cylinder_intersect(void *shape, t_ray ray,
								t_intersect *intersect);

typedef struct				s_cone
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3			origin;
	t_vec3			axis;
	double			radius;
	t_mat4			mat;
	t_mat4			imat;
}							t_cone;

t_cone						*create_cone(t_vec3 p1, t_vec3 axis,
								double unit_radius, t_colour colour);
bool						cone_intersect(void *shape, t_ray ray,
								t_intersect *intersect);

#endif
