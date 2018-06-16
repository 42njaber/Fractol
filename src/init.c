/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:17:27 by njaber            #+#    #+#             */
/*   Updated: 2018/06/16 15:12:22 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

#ifdef OPENCL

static void	set_opencl(t_ptr *p)
{
	p->opencl = init_opencl();
	if (create_kernel(p) == NULL)
		ft_error("Stopping program, "
				"try compiling with the OPENCL=FALSE flag\n");
	p->coloring = 1;
	p->iter_max = 100;
}

#else

static void	set_opencl(t_ptr *p)
{
	p->opencl = NULL;
	p->kernel = NULL;
	p->coloring = 0;
	p->iter_max = 10;
}

#endif

void		init_struct(t_ptr *p)
{
	if ((init_new_win(NULL, p->win, (t_ivec){1200, 800}, "fractol")) == 0)
		ft_error("[Erreur] Echec de l'intialization de la fenètre\n");
	p->mouse_pos = (t_ivec){0, 0};
	p->parm = (t_vec2){0.0, 0.0};
	p->pos = (t_vec2){0.0, 0.0};
	p->dst_pos = (t_vec2){0.0, 0.0};
	p->zoom = 1;
	p->dst_zoom = 1;
	p->pow = 2;
	p->locked = 0;
	p->color_rot = 0;
	p->palette = 0;
	if (p->fract == 0)
		p->locked = 1;
	set_opencl(p);
}

static int	close_hook(void *parm)
{
	(void)parm;
	exit(0);
}

void		set_hooks(t_ptr *p)
{
	mlx_loop_hook(p->win->mlx, loop_hook, (void*)p);
	mlx_expose_hook(p->win->win, loop_hook, (void*)p);
	mlx_hook(p->win->win, 6, 0, motion_hook, (void*)p);
	mlx_hook(p->win->win, 4, 0, button_press_hook, (void*)p);
	mlx_hook(p->win->win, 5, 0, button_release_hook, (void*)p);
	mlx_hook(p->win->win, 2, 0, key_press_hook, (void*)p);
	mlx_hook(p->win->win, 3, 0, key_release_hook, (void*)p);
	mlx_hook(p->win->win, 17, 0, close_hook, (void*)p);
}
