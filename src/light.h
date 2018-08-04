/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 10:16:58 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/04 10:32:37 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vec3.h"
# include "colour.h"
# include "s_vector.h"

/*
** Point Light
*/

typedef struct		s_light
{
	t_vec3		origin;
	t_colour	colour;
}					t_light;

t_light			*light_create(t_vec3 origin, t_colour colour);
void			init_light(t_light *light, t_vec3 origin, t_colour colour);

#endif