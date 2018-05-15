/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:19:13 by njaber            #+#    #+#             */
/*   Updated: 2018/05/15 21:26:36 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libgxns.h"

typedef struct	s_ptr {
	t_win				*win;
	char				keys[512];
	int					button;
	t_ivec				mouse_pos;
	int					fract;
	int					iter_max;
	int					pow;
	t_vec2				pos;
	t_vec2				dst_pos;
	t_vec2				parm;
	double				zoom;
	double				dst_zoom;
	double				color_rot;
	unsigned char		fract_parm;
	char				rot_mode;
	char				coloring;
	char				palette;
	char				locked;
	t_ocl				*opencl;
	t_kernel			*kernel;
}				t_ptr;

void			set_fract_parm(t_ptr *p, int fract);

void			init_struct(t_ptr *p);
void			set_hooks(t_ptr *p);

void			draw_fractal(t_ptr *p);

int				loop_hook(void *parm);
int				key_press_hook(int key_code, void *parm);
int				key_release_hook(int key_code, void *parm);
void			move(t_ptr *p);

int				button_press_hook(int button, int x, int y, void *parms);
int				button_release_hook(int button, int x, int y, void *parms);
int				motion_hook(int x, int y, void *parm);

unsigned int	sky(double gradiant, double shift);
unsigned int	neon(double gradiant, double shift);
unsigned int	black_white(double gradiant, double shift);

# ifdef OPENCL

t_kernel		*create_kernel(t_ptr *p);
# endif
#endif
