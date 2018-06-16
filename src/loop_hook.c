/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 16:00:11 by njaber            #+#    #+#             */
/*   Updated: 2018/06/16 16:09:32 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static char		*fract_name(t_ptr *p)
{
	if (p->fract == 0)
	{
		if (p->fract_parm == 0)
			return (ft_strdup("MANDLEBROT"));
		if ((p->fract_parm & 0x40 || (p->fract_parm & 0x05) == 0x05)
			&& !(p->fract_parm & 0x10))
			return (ft_strdup("BURNING SHIP"));
		if ((p->fract_parm & 0x40 || (p->fract_parm & 0x05) == 0x05)
			&& (p->fract_parm & 0x10))
			return (ft_strdup("ICEBERG"));
		if ((p->fract_parm & 0x55) == 0x14)
			return (ft_strdup("CHARLES"));
		return (ft_strdup("MANDLEBROT*"));
	}
	if (p->fract_parm == 0)
		return (ft_strdup("JULIA"));
	if ((p->fract_parm & 0x55) == 0x4)
		return (ft_strdup("JULIETTE"));
	if ((p->fract_parm & 0x55) == 0x10)
		return (ft_strdup("TOTEM"));
	if ((p->fract_parm & 0x40 || (p->fract_parm & 0x05) == 0x05)
		&& (p->fract_parm & 0x10))
		return (ft_strdup("SNOWFLAKE"));
	return (ft_strdup("JULIA*"));
}

static void		print_data(t_ptr *p)
{
	char	*fract;

	display_data_float(p->win, "FPS", p->win->fps, 10);
	fract = fract_name(p);
	display_data_str(p->win, "Fract:", fract, 30);
	free(fract);
	display_data_vec2(p->win, "Positon:",
			(t_vec2){p->dst_pos.x, p->dst_pos.y}, 50);
	display_data_vec2(p->win, "Parm:",
			(t_vec2){p->parm.x, p->parm.y}, 70);
	display_data_float(p->win, "Pow:", p->pow, 90);
	display_data_float(p->win, "Zoom:", p->dst_zoom, 110);
	display_data_float(p->win, "Prec:", p->iter_max, 130);
	display_data_str(p->win, "Locked:", p->locked ? "true" : "false", 150);
}

static void		update_tranform(t_ptr *p)
{
	t_vec2	mouse_pos;
	double	tmp_zoom;

	tmp_zoom = p->zoom;
	p->zoom = (p->zoom + (p->dst_zoom * 0.08)) / 1.08;
	mouse_pos = (t_vec2){(double)(p->mouse_pos.x - p->win->size.x / 2) /
			(p->zoom * fmin(p->win->size.x, p->win->size.y) / 4) + p->pos.x,
			(double)(p->mouse_pos.y - p->win->size.y / 2) /
			(p->zoom * fmin(p->win->size.x, p->win->size.y) / 4) + p->pos.y};
	p->pos = (t_vec2){(p->pos.x + (p->dst_pos.x * 0.08)) / 1.08,
		(p->pos.y + (p->dst_pos.y * 0.08)) / 1.08};
	p->dst_pos = (t_vec2){(p->dst_pos.x + mouse_pos.x *
			(p->zoom / tmp_zoom - 1)) / (p->zoom / tmp_zoom),
		(p->dst_pos.y + mouse_pos.y *
			(p->zoom / tmp_zoom - 1)) / (p->zoom / tmp_zoom)};
	p->pos = (t_vec2){(p->pos.x + mouse_pos.x *
			(p->zoom / tmp_zoom - 1)) / (p->zoom / tmp_zoom),
		(p->pos.y + mouse_pos.y *
			(p->zoom / tmp_zoom - 1)) / (p->zoom / tmp_zoom)};
	if (p->rot_mode != 0)
		p->color_rot = fmod(p->color_rot +
			copysign((double)1 / (p->win->fps + 1), (double)p->rot_mode), 1);
}

#ifdef OPENCL

int				loop_hook(void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	update_tranform(p);
	move(p);
	draw_fractal(p);
	paint_window(p->win, 1);
	print_data(p);
	return (0);
}

#else

int				loop_hook(void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	update_tranform(p);
	move(p);
	draw_fractal(p);
	paint_window(p->win, 1);
	print_data(p);
	return (0);
}

#endif
