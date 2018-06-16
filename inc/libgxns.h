/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgxns.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:56:43 by njaber            #+#    #+#             */
/*   Updated: 2018/06/16 15:13:51 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGXNS_H
# define LIBGXNS_H

# include <time.h>
# include <math.h>
# include "ft_printf.h"
# include "libft.h"

# if AZERTY
#  include "azerty.h"
# else
#  include "qwerty.h"
# endif

# ifdef OPENCL
#  include <OpenCL/opencl.h>

typedef struct	s_ocl {
	cl_context			gpu_context;
	size_t				gpu_nbr;
	cl_device_id		gpus[16];
	cl_command_queue	gpu_command_queue;
	size_t				gpu_wg_sz;
	size_t				gpu_double;
}				t_ocl;

typedef struct	s_kernel {
	cl_program		program;
	cl_mem			*memobjs;
	size_t			memobjs_nbr;
	cl_kernel		cores[8];
	t_ocl			*opencl;
}				t_kernel;

t_ocl			*init_opencl(void);
cl_program		create_program_from_file(cl_context context, char *file);

# else

typedef void	*t_kernel;
typedef void	*t_ocl;

# endif

typedef struct	s_vec2 {
	double	x;
	double	y;
}				t_vec2;

typedef struct	s_vec3 {
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef double	t_mat4[16];

typedef struct	s_ivec {
	int		x;
	int		y;
}				t_ivec;

typedef struct	s_img {
	void			*link;
	unsigned char	*buf;
	t_ivec			size;
	int				px_size;
	int				line;
	int				endian;
	int				line_draw_mode;
}				t_img;

typedef struct	s_win {
	void				*mlx;
	void				*win;
	t_img				img;
	t_ivec				size;
	int					frame;
	double				fps;
	unsigned long		frames[30];
}				t_win;

t_vec3			apply_mat_vec3(t_vec3 v, t_mat4 m);
void			print_mat(t_mat4 m);

void			identity(t_mat4 m);
void			translate(t_mat4 m, t_vec3 v);
void			scale(t_mat4 m, t_vec3 v);
void			rotate(t_mat4 m, t_vec3 v);
void			multiply(t_mat4 m1, t_mat4 m2, int stock_in_m2);

double			sqr(double n);

t_vec2			c_mult(t_vec2 z1, t_vec2 z2);
t_vec2			c_add(t_vec2 z1, t_vec2 z2);
t_vec2			c_pow(t_vec2 z1, int pow);

t_vec3			vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec_mult(t_vec3 v1, double d);
double			length(t_vec3 v1);
double			scalar(t_vec3 v1, t_vec3 v2);

int				init_new_win(void *mlx, t_win *win, t_ivec size, char *title);
void			paint_window(t_win *win, int clear);

void			display_data_float(t_win *win, char *name, double data, int y);
void			display_data_vec2(t_win *win, char *name, t_vec2 data, int y);
void			display_data_vec3(t_win *win, char *name, t_vec3 data, int y);
void			display_data_str(t_win *win, char *name, char *data, int y);

void			init_new_image(void *mlx, t_img *img, t_ivec size);
void			img_px(t_img *img, unsigned int color, t_ivec pixel);
void			clear_img(t_img *img);

void			draw_line(t_img *img, unsigned int *color, t_vec2 *verticies);
unsigned int	color_gradiant(unsigned int *colors, double gradiant);

int				get_key_digit(int key_code);

#endif
