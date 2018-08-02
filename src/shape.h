/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:25:02 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/02 00:40:42 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "colour.h"
# include "vec3.h"
# include "ray.h"
# include "s_vector.h"

typedef int		t_shape_type;

# define PLANE		(0)
# define SPHERE		(1)
# define CYLINDER	(2)
# define CONE		(3)

typedef struct s_intersect	t_intersect;

typedef struct		s_shape
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*does_intersect)(void *shape, t_ray);
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

}					t_shape;

typedef t_vector	*t_vshape_set;

t_vshape_set		vshape_set_create(void);
void				add_shape(t_vshape_set scene, t_shape *shape);
t_shape				*get_shape(t_vshape_set scene, int index);

typedef struct		s_plane
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*does_intersect)(void *shape, t_ray);
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3			p;
	t_vec3			n;
}					t_plane;

t_plane				*plane_create(t_vec3 point, t_vec3 normal, t_colour colour);
bool				plane_does_intersect(void *shape, t_ray ray);
bool				plane_intersect(void *shape, t_ray ray,
						t_intersect *intersect);


typedef struct		s_sphere
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*does_intersect)(void *shape, t_ray);
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3			center;
	double			radius;
}					t_sphere;

t_sphere	*create_sphere(t_vec3 center, double radius, t_colour colour);
bool		sphere_does_intersect(void *shape, t_ray ray);
bool		sphere_intersect(void *shape, t_ray ray, t_intersect *intersect);

typedef struct		s_cylinder
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*does_intersect)(void *shape, t_ray);
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3			origin;
	t_vec3			axis;
	double			radius;
}					t_cylinder;

t_cylinder	*create_cylinder(t_vec3 origin, t_vec3 axis,
				double radius, t_colour colour);
bool		cylinder_does_intersect(void *shape, t_ray ray);
bool		cylinder_intersect(void *shape, t_ray ray, t_intersect *intersect);


#endif