/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:22:27 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 19:14:58 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
