/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_opencl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:24:15 by njaber            #+#    #+#             */
/*   Updated: 2018/06/16 13:28:12 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void				set_args_float(t_ptr *p)
{
	clSetKernelArg(p->kernel->cores[0], 4, sizeof(int), &p->iter_max);
	clSetKernelArg(p->kernel->cores[0], 5,
			sizeof(float), (float[1]){p->zoom});
	clSetKernelArg(p->kernel->cores[0], 6,
			sizeof(float[2]), (float[2]){p->pos.x, p->pos.y});
	clSetKernelArg(p->kernel->cores[0], 7,
			sizeof(float[2]), (float[2]){p->parm.x, p->parm.y});
	clSetKernelArg(p->kernel->cores[0], 8, sizeof(int), &p->pow);
	clSetKernelArg(p->kernel->cores[0], 9, sizeof(int), &p->fract);
	clSetKernelArg(p->kernel->cores[0], 10, sizeof(char), &p->fract_parm);
	clSetKernelArg(p->kernel->cores[0], 11, sizeof(char), &p->coloring);
	clSetKernelArg(p->kernel->cores[0], 12,
			sizeof(float), (float[1]){p->color_rot});
	clSetKernelArg(p->kernel->cores[0], 13, sizeof(char), &p->palette);
}

#ifdef DOUBLE_P

static void				set_args_double(t_ptr *p)
{
	clSetKernelArg(p->kernel->cores[0], 4, sizeof(int), &p->iter_max);
	clSetKernelArg(p->kernel->cores[0], 5,
			sizeof(double), (double[1]){p->zoom});
	clSetKernelArg(p->kernel->cores[0], 6,
			sizeof(double[2]), (double[2]){p->pos.x, p->pos.y});
	clSetKernelArg(p->kernel->cores[0], 7,
			sizeof(double[2]), (double[2]){p->parm.x, p->parm.y});
	clSetKernelArg(p->kernel->cores[0], 8, sizeof(int), &p->pow);
	clSetKernelArg(p->kernel->cores[0], 9, sizeof(int), &p->fract);
	clSetKernelArg(p->kernel->cores[0], 10, sizeof(char), &p->fract_parm);
	clSetKernelArg(p->kernel->cores[0], 11, sizeof(char), &p->coloring);
	clSetKernelArg(p->kernel->cores[0], 12,
			sizeof(double), (double[1]){p->color_rot});
	clSetKernelArg(p->kernel->cores[0], 13, sizeof(char), &p->palette);
}

void					draw_fractal(t_ptr *p)
{
	cl_event	event;
	cl_int		err;

	if (p->opencl->gpu_double == 0)
		set_args_float(p);
	else
		set_args_double(p);
	if ((err = clEnqueueNDRangeKernel(p->opencl->gpu_command_queue,
			p->kernel->cores[0], 1, NULL, (size_t[1]){
			(((p->win->size.x * p->win->size.y) / p->opencl->gpu_wg_sz) + 1) *
			p->opencl->gpu_wg_sz},
			(size_t[1]){p->opencl->gpu_wg_sz}, 0, NULL, &event)) != CL_SUCCESS)
		ft_error("[Erreur] Echec d'execution du kernel"
				"%<R>  (Error code: %<i>%2d)%<0>\n", err);
	if ((err = clEnqueueReadBuffer(p->opencl->gpu_command_queue,
			p->kernel->memobjs[0], CL_TRUE, 0,
			p->win->img.line * p->win->size.y,
			p->win->img.buf, 1, &event, NULL)) != CL_SUCCESS)
		ft_error("[Erreur] Echec durant la lecture du buffer"
				"%<R>  (Error code: %<i>%2d)%<0>\n", err);
	clReleaseEvent(event);
	clFinish(p->opencl->gpu_command_queue);
}

#else

void					draw_fractal(t_ptr *p)
{
	cl_event	event;
	cl_int		err;

	set_args_float(p);
	if ((err = clEnqueueNDRangeKernel(p->opencl->gpu_command_queue,
			p->kernel->cores[0], 1, NULL, (size_t[1]){
			(((p->win->size.x * p->win->size.y) / p->opencl->gpu_wg_sz) + 1) *
			p->opencl->gpu_wg_sz},
			(size_t[1]){p->opencl->gpu_wg_sz}, 0, NULL, &event)) != CL_SUCCESS)
		ft_error("[Erreur] Echec d'execution du kernel"
				"%<R>  (Error code: %<i>%2d)%<0>\n", err);
	if ((err = clEnqueueReadBuffer(p->opencl->gpu_command_queue,
			p->kernel->memobjs[0], CL_TRUE, 0,
			p->win->img.line * p->win->size.y,
			p->win->img.buf, 1, &event, NULL)) != CL_SUCCESS)
		ft_error("[Erreur] Echec durant la lecture du buffer"
				"%<R>  (Error code: %<i>%2d)%<0>\n", err);
	clReleaseEvent(event);
	clFinish(p->opencl->gpu_command_queue);
}

#endif
