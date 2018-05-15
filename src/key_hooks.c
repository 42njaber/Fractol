/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:52:32 by njaber            #+#    #+#             */
/*   Updated: 2018/05/15 21:16:49 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void			move(t_ptr *p)
{
	if (p->keys[K_LEFT])
		p->dst_pos.x += -0.1 / p->zoom;
	if (p->keys[K_RIGHT])
		p->dst_pos.x += 0.1 / p->zoom;
	if (p->keys[K_DOWN])
		p->dst_pos.y += 0.1 / p->zoom;
	if (p->keys[K_UP])
		p->dst_pos.y += -0.1 / p->zoom;
}

static	void	keys3(int key_code, t_ptr *p)
{
	if (get_key_digit(key_code) > 0 && get_key_digit(key_code) <= 6)
		p->fract_parm ^= 0x1 << (get_key_digit(key_code) - 1);
	if (key_code == K_M)
		p->pow++;
	if (key_code == K_L)
		p->pow = ft_max(p->pow - 1, 2);
}

static	void	keys2(int key_code, t_ptr *p)
{
	move(p);
	if (!p->keys[K_SHIFT])
	{
		if (key_code == K_M)
			p->iter_max++;
		if (key_code == K_L)
			p->iter_max = ft_max(p->iter_max - 1, 4);
		if (get_key_digit(key_code) > 0 && get_key_digit(key_code) <= 6)
			set_fract_parm(p, get_key_digit(key_code) - 1);
		if (key_code == K_0)
			p->palette = (p->palette + 1) % 3;
	}
	else
		keys3(key_code, p);
}

int				key_press_hook(int key_code, void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	p->keys[key_code] = 1;
	if (key_code == K_ESC)
		exit(0);
	if (key_code == K_K)
		p->locked = !p->locked;
	if (key_code == K_C)
		p->coloring = !p->coloring;
	if (key_code == K_G)
		p->rot_mode = (p->rot_mode + 2) % 3 - 1;
	if (key_code == K_R)
	{
		if (p->fract == 0)
			p->locked = 1;
		p->pow = 2;
		p->parm = (t_vec2){0, 0};
		p->dst_pos = (t_vec2){0.0, 0.0};
		p->dst_zoom = 1;
		p->zoom = 1;
	}
	keys2(key_code, p);
	return (0);
}

int				key_release_hook(int key_code, void *parm)
{
	t_ptr	*p;

	p = (t_ptr*)parm;
	p->keys[key_code] = 0;
	return (0);
}
