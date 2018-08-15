/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 10:11:56 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/15 15:45:31 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "rtv1.h"
# include "shape.h"
# include "s_vector.h"
# include "light.h"
# include "camera.h"
# include "parse_scene.h"

typedef t_vector		*t_vshape_set;
typedef t_vector		*t_vlight_set;

typedef struct			s_scene
{
	t_vshape_set	shapes;
	t_vlight_set	lights;
	t_camera		camera;
	t_colour		ambience;
}						t_scene;

void					scene_init(t_scene *scene);

t_vshape_set			vshape_set_create(void);
void					add_shape(t_vshape_set scene, t_shape *shape);
t_shape					*get_shape(t_vshape_set scene, int index);

t_vlight_set			vlight_set_create(void);
void					add_light(t_vlight_set scene, t_light *light);
t_light					*get_light(t_vlight_set scene, int index);

#endif
