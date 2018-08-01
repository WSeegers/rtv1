/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:26:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 20:09:31 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_scene(t_vshape_set shapes, t_vlight_set lights)
{
	t_plane 	*left_wall; //r
	t_plane		*back_wall; //g
	t_plane		*right_wall; //b
	t_plane		*pfloor;
	t_sphere	*s;
	t_light		*light;

	left_wall = plane_create(VEC3(-10, 0, 0), VEC3(1, 0, 0), C_RED);
	add_shape(shapes, (t_shape*)left_wall);

	right_wall = plane_create(VEC3(10, 0, 0), VEC3(-1, 0, 0), C_GREEN);
	add_shape(shapes, (t_shape*)right_wall);

	back_wall = plane_create(VEC3(0, 0, 20), VEC3(0, 0, -1), C_BLUE);
	add_shape(shapes, (t_shape*)back_wall);

	pfloor = plane_create(VEC3(0, 0, 0), VEC3(0, 1, 0), COLOUR(1.0, 0.5, 0.5));
	add_shape(shapes, (t_shape*)pfloor);

	s = create_sphere(VEC3(5, 2, 5), 2, COLOUR(1.0, 0, 1));
	add_shape(shapes, (t_shape*)s);

	s = create_sphere(VEC3(-4, 3, 5), 3, COLOUR(1.0, 0, 1));
	add_shape(shapes, (t_shape*)s);

	light = light_create(VEC3(4, 20, 0), colour_scale(C_WHITE, 0.3));
	add_light(lights, light);

	light = light_create(VEC3(-2, 2, 0), colour_scale(C_WHITE, 1));
	add_light(lights, light);
}

static	void init_camera(t_camera *cam)
{
	camera_set(VEC3(2, 5, -20), VEC3(0, 2, 5), cam);
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
	puts("generating shape");
	generate_screen(cam, shapes, lights);
	puts("blit");
	SDL_UpdateWindowSurface(g_window);
	loop();
	
	end();
}