/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:55:44 by njaber            #+#    #+#             */
/*   Updated: 2018/04/08 21:22:23 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"

static int		tint(double d)
{
	return (rint(trunc(d)));
}

static t_ivec	extra_pixel(t_vec2 pixel, t_vec2 unit)
{
	if ((fmod(pixel.x, 1) - !signbit(unit.x)) * unit.x * -1 <
			(fmod(pixel.y, 1) - !signbit(unit.y)) * unit.y * -1)
		return ((t_ivec){tint(pixel.x + unit.x), tint(pixel.y)});
	else
		return ((t_ivec){tint(pixel.x), tint(pixel.y + unit.y)});
}

static void		draw_line_no_kernel(t_img *img, unsigned int *colors, t_vec2 *v)
{
	t_vec2	unit;
	t_vec2	pixel;
	double	color;

	pixel = (t_vec2){v[0].x, v[0].y};
	if (fabs(v[1].x - v[0].x) > fabs(v[1].y - v[0].y))
		unit = (t_vec2){copysign(1, v[1].x - v[0].x), copysign((v[1].y - v[0].y)
				/ (v[1].x - v[0].x), v[1].y - v[0].y)};
	else
		unit = (t_vec2){copysign((v[1].x - v[0].x) / (v[1].y - v[0].y),
				v[1].x - v[0].x), copysign(1, v[1].y - v[0].y)};
	while (fabs(pixel.x - v[0].x) < fabs(v[1].x - v[0].x) + 0.01
			&& fabs(pixel.y - v[0].y) < fabs(v[1].y - v[0].y) + 0.01)
	{
		color = color_gradiant(colors, fabs(unit.x) > 0.1 ? (pixel.x - v[0].x) /
				(v[1].x - v[0].x) : (pixel.y - v[0].y) / (v[1].y - v[0].y));
		img_px(img, color, (t_ivec){tint(pixel.x), tint(pixel.y)});
		if (img->line_draw_mode == 1 && tint(pixel.x + unit.x) != tint(pixel.x)
				&& tint(pixel.y + unit.y) != tint(pixel.y))
			img_px(img, color, extra_pixel(pixel, unit));
		pixel = (t_vec2){pixel.x + unit.x, pixel.y + unit.y};
	}
}

void			draw_line(t_img *img, unsigned int *colors, t_vec2 *v)
{
	if ((v[0].x < 0 && v[1].x < 0)
			|| (v[0].x > img->size.x && v[1].x > img->size.x)
			|| (v[0].y < 0 && v[1].y < 0)
				|| (v[0].y > img->size.y && v[1].y > img->size.y))
		return ;
	draw_line_no_kernel(img, colors, v);
}
