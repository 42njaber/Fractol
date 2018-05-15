/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 19:39:02 by njaber            #+#    #+#             */
/*   Updated: 2018/05/15 21:17:50 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

static unsigned int		color_palette(double gradiant, int iter, t_ptr *p)
{
	if (iter < p->iter_max)
	{
		if (p->palette == 0)
			return (sky(gradiant, p->color_rot));
		else if (p->palette == 1)
			return (black_white(gradiant, p->color_rot));
		else
			return (neon(gradiant, p->color_rot));
	}
	else
		return (0x000000);
}

static t_vec2			iterate(t_vec2 z, t_vec2 c, t_ptr *p)
{
	z = (t_vec2){(p->fract_parm & (0x1 << 0) ? fabs(z.x) : z.x) *
				(p->fract_parm & (0x1 << 1) ? -1 : 1),
				(p->fract_parm & (0x1 << 2) ? fabs(z.y) : z.y) *
				(p->fract_parm & (0x1 << 3) ? -1 : 1)};
	z = c_pow(z, p->pow);
	z = (t_vec2){(p->fract_parm & (0x1 << 4) ? fabs(z.x) : z.x) *
				(p->fract_parm & (0x1 << 5) ? -1 : 1),
				(p->fract_parm & (0x1 << 6) ? fabs(z.y) : z.y) *
				(p->fract_parm & (0x1 << 7) ? -1 : 1)};
	z = (t_vec2){z.x + c.x, z.y + c.y};
	return (z);
}

static unsigned int		mandlebrot_color(t_vec2 pos, t_ptr *p)
{
	int		i;
	int		iter;
	t_vec2	z;
	t_vec2	c;

	iter = 0;
	c = pos;
	z = p->parm;
	i = 0;
	while (hypot(z.x, z.y) <= 2 && ++iter < p->iter_max)
		z = iterate(z, c, p);
	if (p->coloring == 1 && (i = iter) < p->iter_max)
	{
		while (hypot(z.x, z.y) < 1 << 10 && i < p->iter_max + 50)
		{
			z = iterate(z, c, p);
			i++;
		}
		return (color_palette((i - log(log(hypot(z.x, z.y)) / log(p->pow)) /
						log(p->pow)) / 7 + 10, iter, p));
	}
	return (color_palette((double)iter / 7 + 10, iter, p));
}

static unsigned int		julia_color(t_vec2 pos, t_ptr *p)
{
	int		i;
	int		iter;
	t_vec2	z;
	t_vec2	c;

	iter = 0;
	c = pos;
	z = p->parm;
	i = 0;
	while (hypot(c.x, c.y) <= 2 && ++iter < p->iter_max)
		c = iterate(c, z, p);
	if (p->coloring == 1 && (i = iter) < p->iter_max)
	{
		while (hypot(c.x, c.y) < 1 << 10 && i < p->iter_max + 50)
		{
			c = iterate(c, z, p);
			i++;
		}
		return (color_palette((i - log(log(hypot(c.x, c.y)) / log(p->pow)) /
						log(p->pow)) / 7 + 10, iter, p));
	}
	return (color_palette((double)iter / 7 + 10, iter, p));
}

void					draw_fractal(t_ptr *p)
{
	t_ivec			px_pos;
	t_vec2			pos;
	unsigned int	color;

	px_pos = (t_ivec){0, 0};
	while (px_pos.y < p->win->size.y)
	{
		pos = (t_vec2){(double)(px_pos.x - p->win->size.x / 2) /
			(p->zoom * fmin(p->win->size.x, p->win->size.y) / 4) + p->pos.x,
			(double)(px_pos.y - p->win->size.y / 2) /
			(p->zoom * fmin(p->win->size.x, p->win->size.y) / 4) + p->pos.y};
		if (p->fract == 0)
			color = mandlebrot_color(pos, p);
		else
			color = julia_color(pos, p);
		img_px(&p->win->img, color, px_pos);
		px_pos = (t_ivec){(px_pos.x + 1) % p->win->size.x,
			px_pos.y + (px_pos.x + 1) / p->win->size.x};
	}
}
