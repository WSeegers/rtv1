/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:26:58 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 16:07:46 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <stdbool.h>
# include <math.h>
# include "f_print.h"
# include "vec3.h"
# include "s_vector.h"
# include "colour.h"

# define SCREEN_TITLE	"rtv1 - WSeegers"
# define SCREEN_WIDTH	(640 * 2)
# define SCREEN_HEIGHT	(480 * 2)
# define ASPECT_RATIO	((double)SCREEN_HEIGHT / (double)SCREEN_WIDTH)
# define FOV			(3.14159265359 * 0.45)
# define LENS_HEIGHT	(atan(FOV))
# define LENS_WIDTH		(LENS_HEIGHT * ASPECT_RATIO)
# define UP_GUIDE		(VEC3(0, 1, 0))

# define AMBIENT_LIGHT	(COLOUR(0.15, 0.1, 0.1))

SDL_Window	*g_window;
SDL_Surface	*g_wsurface;

# define DOT_MIN	(1e-6)
# define RAY_T_MIN	(1e-6)
# define RAY_T_MAX	(1.0e30)

typedef	struct	s_ray
{
	t_vec3	p;
	t_vec3	d;
	double	t_max;
}				t_ray;

t_vec3	ray_calculate(t_ray ray, double t);

typedef int		t_shape_type;

# define PLANE		(0)
# define SPHERE		(1)
# define CYLINDER	(2)
# define CONE		(3)

typedef struct s_intersect t_intersect;

typedef struct		s_shape
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*does_intersect)(void *shape, t_ray);
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

}					t_shape;

typedef t_vector	*t_vshape_set;
typedef t_vector	*t_vlight_set;

t_vshape_set		vshape_set_create(void);
void				add_shape(t_vshape_set scene, t_shape *shape);
t_shape 			*get_shape(t_vshape_set scene, int index);

typedef struct		s_plane
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*does_intersect)(void *shape, t_ray);
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3	p;
	t_vec3	n;
	
}					t_plane;

t_plane				*create_plane(t_vec3 point, t_vec3 normal, t_colour colour);
bool				plane_does_intersect(void *shape, t_ray);
bool				plane_intersect(void *shape, t_ray ray, t_intersect *intersect);


typedef struct		s_sphere
{
	t_shape_type	shape_type;
	t_colour		colour;
	bool			(*does_intersect)(void *shape, t_ray);
	bool			(*intersect)(void *shape, t_ray, t_intersect*);

	t_vec3	center;
	double	radius;
}					t_sphere;

t_sphere	*create_sphere(t_vec3 center, double radius, t_colour colour);
bool		sphere_does_intersect(void *shape, t_ray ray);
bool		sphere_intersect(void *shape, t_ray ray, t_intersect *intersect);

typedef	struct 	s_intersect
{
	t_ray		ray;
	t_shape		*shape;
	double		t;
	t_colour	colour;
	t_vec3		normal;
}				t_intersect;

# define INTERSECT(r, s, t, c)	((t_intersect){r, s, t, c}) 


typedef	struct	s_camera
{
	t_vec3	origin;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	double	height;
	double	width;
}				t_camera;

void	camera_set(t_vec3 origin, t_vec3 target, t_camera *cam);
void	camera_set_target(t_vec3 target, t_camera *cam);

void	generate_screen(t_camera cam, t_vshape_set scene);
void	putpixel(int x, int y, t_colour pixel);
void 	putipixel(int x, int y, Uint32 pixel);

#endif