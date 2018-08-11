/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:38:55 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 19:35:36 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "libmat.h"

typedef	struct	s_camera
{
	t_vec3	origin;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	double	height;
	double	width;
}				t_camera;

void			camera_set(t_vec3 origin, t_vec3 target, t_camera *cam);
void			camera_set_target(t_vec3 target, t_camera *cam);

#endif
