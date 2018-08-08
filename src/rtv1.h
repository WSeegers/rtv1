/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:26:58 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 17:04:41 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include "f_print.h"
# include "vec3.h"
# include "ray.h"
# include "s_vector.h"
# include "shape.h"
# include "light.h"
# include "scene.h"
# include "colour.h"
# include "mat4.h"
# include "camera.h"

# define SCREEN_TITLE	"rtv1 - WSeegers"
# define SCREEN_WIDTH	(640 * 2)
# define SCREEN_HEIGHT	(480 * 2)
# define ASPECT_RATIO	((double)SCREEN_HEIGHT / (double)SCREEN_WIDTH)
# define FOV			(3.14159265359 * 0.25)
# define LENS_HEIGHT	(atan(FOV))
# define LENS_WIDTH		(LENS_HEIGHT * ASPECT_RATIO)
# define UP_GUIDE		(VEC3(0, 1, 0))

# define AMBIENT_LIGHT	(COLOUR(0.1, 0.1, 0.1))

SDL_Window		*g_window;
SDL_Surface		*g_wsurface;

typedef struct	s_intersect
{
	t_ray		ray;
	t_shape		*shape;
	double		t;
	t_vec3		normal;
}				t_intersect;

# define INTERSECT(r, s, t, c)	((t_intersect){r, s, t, c})

void			generate_screen(t_camera cam, t_vshape_set scene,
					t_vlight_set light);
void			putpixel(int x, int y, t_colour pixel);
void			putipixel(int x, int y, Uint32 pixel);

#endif
