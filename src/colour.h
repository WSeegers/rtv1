/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:56:30 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 14:20:46 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOUR_H
# define COLOUR_H

# include <SDL2/SDL.h>
# include "f_math.h"

typedef Uint32	t_icolour;

typedef struct	s_colour
{
	double	r;
	double	g;
	double	b;
}				t_colour;

# define COLOUR(r, g, b)	((t_colour){r, g, b})

t_colour	colour_get(double red, double green, double blue);
t_icolour	colour_to_int(t_colour col);
t_colour	colour_add(t_colour c1, t_colour c2);
t_colour	colour_multiply(t_colour c1, t_colour c2);
t_colour	colour_scale(t_colour c, double s);

# define C_BLACK	(COLOUR(0, 0, 0))
# define C_RED		(COLOUR(1, 0, 0))
# define C_GREEN	(COLOUR(0, 1, 0))
# define C_BLUE		(COLOUR(0, 0, 1))
# define C_WHITE	(COLOUR(1, 1, 1))

#endif