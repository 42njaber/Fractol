/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 01:32:56 by njaber            #+#    #+#             */
/*   Updated: 2018/05/15 21:25:34 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		button_press_hook(int button, int x, int y, void *parms)
{
	t_ptr	*p;

	(void)(x + y);
	p = (t_ptr*)parms;
	if (button == 4 || button == 5)
	{
		p->dst_zoom *= (button == 5) ? 0.96 : 1.04;
		if (p->dst_zoom < 0.5)
			p->dst_zoom = 0.5;
	}
	else
		p->button = button;
	return (0);
}

int		button_release_hook(int button, int x, int y, void *parms)
{
	t_ptr	*p;

	p = (t_ptr*)parms;
	(void)(button + x + y);
	p->button = -1;
	return (0);
}

int		motion_hook(int x, int y, void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	p->mouse_pos = (t_ivec){x, y};
	if (!p->locked)
		p->parm = (t_vec2){(float)(x - p->win->size.x / 2) / p->win->size.x * 3,
			(float)(y - p->win->size.y / 2) / p->win->size.y * 3};
	return (0);
}
