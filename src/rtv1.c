/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:26:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 12:28:53 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_scene(t_vshape_set shapes, t_vlight_set lights)
{
	t_plane 	*left_wall;
	t_plane		*back_wall;
	t_plane		*right_wall;
	t_plane		*pfloor;
	t_sphere	*s;
	t_cylinder	*c;
	t_light		*light;
	t_cone		*cone;

	left_wall = plane_create(VEC3(-40, 0, 0), VEC3(1, 0, 0), C_BURGANDY);
	add_shape(shapes, (t_shape*)left_wall);

	right_wall = plane_create(VEC3(40, 0, 0), VEC3(-1, 0, 0), C_GREEN);
	add_shape(shapes, (t_shape*)right_wall);

	back_wall = plane_create(VEC3(0, 0, 80), VEC3(0, 0, -1), C_BLUE);
	add_shape(shapes, (t_shape*)back_wall);

	pfloor = plane_create(VEC3(0, 0, -10), VEC3(0, 1, 0), COLOUR(1.0, 0.5, 0.5));
	add_shape(shapes, (t_shape*)pfloor);
	
	// for (int i = -5; i < 5; i++)
	// {
	// 	s = create_sphere(VEC3(i * 2, i + 10, i), fabs(i * 0.342 + 2), COLOUR(fmod(fabs(i / 2.3), 1), fmod(fabs(i / 4.3), 1), fmod(fabs(i / 2.0), 1)));
	// 	add_shape(shapes, (t_shape*)s);
	// }
	// s = create_sphere(VEC3(0, 0, 0), 3, COLOUR(0.8, 0.3, 1.0));
	// add_shape(shapes, (t_shape*)s);

	s = create_sphere(VEC3(-20, 0, 0), 5, COLOUR(1.0, 0, 1));
	add_shape(shapes, (t_shape*)s);

	s = create_sphere(VEC3(20, 0, 0), 5, COLOUR(1.0, 0, 1));
	add_shape(shapes, (t_shape*)s);

	s = create_sphere(VEC3(-20, 0, 40), 5, COLOUR(1.0, 0, 1));
	add_shape(shapes, (t_shape*)s);

	s = create_sphere(VEC3(20, 0, 40), 5, COLOUR(1.0, 0, 1));
	add_shape(shapes, (t_shape*)s);

	c = create_cylinder(VEC3(-20, 0, 0), VEC3(0, 1, 0), 2, COLOUR(0.3, 0.6, 0.9));
	add_shape(shapes, (t_shape*)c);

	c = create_cylinder(VEC3(20, 0, 0), VEC3(0, 1, 0), 2, COLOUR(0.3, 0.6, 0.9));
	add_shape(shapes, (t_shape*)c);

	c = create_cylinder(VEC3(20, 0, 40), VEC3(0, 1, 0), 2, COLOUR(0.3, 0.6, 0.9));
	add_shape(shapes, (t_shape*)c);

	c = create_cylinder(VEC3(-20, 0, 40), VEC3(0, 1, 0), 2, COLOUR(0.3, 0.6, 0.9));
	add_shape(shapes, (t_shape*)c);

	cone = create_cone(VEC3(10, 10, 0), VEC3(0, -1, 0), 0.25, C_GREEN);
	add_shape(shapes, (t_shape*)cone);
	
	cone = create_cone(VEC3(-10, 10, 0), VEC3(0, -1, 0), 0.25, C_GREEN);
	add_shape(shapes, (t_shape*)cone);

	// light = light_create(VEC3(0, 100, 0), colour_scale(C_WHITE, 0.5));
	// add_light(lights, light);

	light = light_create(VEC3(0, 5, -30), colour_scale(C_WHITE, 0.5));
	add_light(lights, light);

	light = light_create(VEC3(0, 15, -30), colour_scale(C_WHITE, 0.5));
	add_light(lights, light);

	// light = light_create(VEC3(5, 0.1, -3), colour_scale(C_WHITE, 0.2));
	// add_light(lights, light);

}

static	void init_camera(t_camera *cam)
{
	camera_set(VEC3(10, 15, -30), VEC3(0, 10, 0), cam);
}

static	bool init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		f_printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (false);
	}
	else
	{
		if (!(g_window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
		{
			f_printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return (false);
		}
		g_wsurface = SDL_GetWindowSurface(g_window);
	}
	//insert FOV check
	return (true);
}

static void	end(void)
{
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

static void loop(void)
{
	SDL_Event e;
	bool quit;

	quit = false;
	while (!quit)
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
}

int	main(void)
{
	t_camera			cam;
	t_vshape_set		shapes;
	t_vlight_set		lights;

	if (!init())
		SDL_Quit();
	init_camera(&cam);
	shapes = vshape_set_create();
	lights = vlight_set_create();
	puts("init scene");
	init_scene(shapes, lights);
	puts("generating scene");
	generate_screen(cam, shapes, lights);
	puts("blit");
	SDL_UpdateWindowSurface(g_window);
	loop();
	end();
}