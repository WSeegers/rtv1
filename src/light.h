/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 10:16:58 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/20 03:44:57 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "libmat.h"
# include "scene.h"
# include "colour.h"
# include "s_vector.h"

/*
** Point Light
*/

typedef struct s_scene	t_scene;
typedef t_vector		*t_vshape_set;
typedef t_vector		*t_vlight_set;

typedef struct		s_light
{
	t_vec3		origin;
	t_colour	colour;
}					t_light;

t_light				*light_create(t_vec3 origin, t_colour colour,
						double intensity);
void				init_light(t_light *light, t_vec3 origin, t_colour colour,
						double intensity);
t_colour			eval_light(t_intersect s_intersect, t_scene *scene);

#endif
