/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:26:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/29 22:26:22 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_scene(t_scene scene)
{
	t_plane 	*red;
	t_plane		*blue;
	t_sphere	*s;

	//red = create_plane(VEC3(0, 0, 5), VEC3(-1, 0, -1), 0x00ff0000);
	//add_shape(scene, (t_shape*)red);

	//blue = create_plane(VEC3(0, 0, 5), VEC3(1.5, 0.5, -1), 0x000000ff);
	//add_shape(scene, (t_shape*)blue);

	s = create_sphere(VEC3(-1, -1, 6), 4, 0x00ff00ff);
	add_shape(scene, (t_shape*)s);

	s = create_sphere(VEC3(1, 1, 6), 3, 0x0000ff00);
	add_shape(scene, (t_shape*)s);

	s = create_sphere(VEC3(0, 2, 3), 2, 0x00ffffff);
	add_shape(scene, (t_shape*)s);
}

static	void init_camera(t_camera *cam)
{
	camera_set(VEC3(0, 0, -2), VEC3(0, 0, 5), cam);
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
	t_camera	cam;
	t_scene		scene;

	if (!init())
		SDL_Quit();
	init_camera(&cam);
	scene = scene_create();
	init_scene(scene);
	generate_screen(cam, scene);
	SDL_UpdateWindowSurface(g_window);
	loop();
	
	end();
}