/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 10:28:27 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/04 10:30:19 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_vshape_set	vshape_set_create(void)
{
	return (vector_create());
}

void	add_shape(t_vshape_set scene, t_shape *shape)
{
	vector_add(scene, shape);
}

t_shape *get_shape(t_vshape_set scene, int index)
{
	return ((t_shape*)vector_get(scene, index));
}