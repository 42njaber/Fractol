/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:23:49 by njaber            #+#    #+#             */
/*   Updated: 2018/06/16 13:53:47 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		set_args(t_ptr *p, t_ocl *opencl, t_kernel *kernel, t_img *img)
{
	int err;

	(void)p;
	if ((kernel->memobjs = (cl_mem*)ft_memalloc(sizeof(cl_mem) * 8)) == NULL)
		ft_error("[Erreur] Echec d'allocation mémoire.");
	kernel->memobjs[0] = clCreateBuffer(opencl->gpu_context, CL_MEM_READ_WRITE,
			img->line * img->size.y, NULL, &err);
	err |= clSetKernelArg(kernel->cores[0], 0,
			sizeof(cl_mem), (void*)&kernel->memobjs[0]);
	err |= clSetKernelArg(kernel->cores[0], 1, sizeof(int), &img->px_size);
	err |= clSetKernelArg(kernel->cores[0], 2, sizeof(int), &img->line);
	err |= clSetKernelArg(kernel->cores[0], 3, sizeof(int[2]), &img->size);
	err |= clSetKernelArg(kernel->cores[1], 0,
			sizeof(cl_mem), (void*)&kernel->memobjs[0]);
	return (err);
}

#ifdef DOUBLE_P

static int		build_program(t_ocl *opencl, t_kernel *kernel)
{
	char		*tmp;
	size_t		tmp2;
	int			err;

	kernel->program = create_program_from_file(opencl->gpu_context,
			opencl->gpu_double == 0 ? "src/fkernel.cl" : "src/dkernel.cl");
	if (opencl->gpu_double == 0)
		ft_printf("Unable to launch with double-point precision\n"
				"Launching with single-point precision\n");
	else
		ft_printf("Launching with double-point precision\n");
	err = clBuildProgram(kernel->program, 0, NULL,
					"", NULL, NULL);
	tmp = (char*)ft_memalloc(4096);
	clGetProgramBuildInfo(kernel->program, opencl->gpus[0],
			CL_PROGRAM_BUILD_LOG, 4096, tmp, &tmp2);
	ft_printf("Build log :\n%.*s\n", tmp2, tmp);
	free(tmp);
	if (err != CL_SUCCESS)
		return (err);
	kernel->cores[0] = clCreateKernel(kernel->program, "draw_fract", &err);
	if (err != CL_SUCCESS)
		return (err);
	kernel->cores[1] = clCreateKernel(kernel->program, "clear_buf", &err);
	return (err);
}

#else

static int		build_program(t_ocl *opencl, t_kernel *kernel)
{
	char		*tmp;
	size_t		tmp2;
	int			err;

	kernel->program = create_program_from_file(opencl->gpu_context,
			"src/fkernel.cl");
	ft_printf("Launching with single-point precision\n");
	err = clBuildProgram(kernel->program, 0, NULL,
					"", NULL, NULL);
	tmp = (char*)ft_memalloc(4096);
	clGetProgramBuildInfo(kernel->program, opencl->gpus[0],
			CL_PROGRAM_BUILD_LOG, 4096, tmp, &tmp2);
	ft_printf("Build log :\n%.*s\n", tmp2, tmp);
	free(tmp);
	if (err != CL_SUCCESS)
		return (err);
	kernel->cores[0] = clCreateKernel(kernel->program, "draw_fract", &err);
	if (err != CL_SUCCESS)
		return (err);
	kernel->cores[1] = clCreateKernel(kernel->program, "clear_buf", &err);
	return (err);
}

#endif

t_kernel		*create_kernel(t_ptr *p)
{
	t_kernel	*kernel;
	t_img		*img;
	int			err;

	p->kernel = NULL;
	if ((kernel = (t_kernel*)ft_memalloc(sizeof(t_kernel))) == NULL)
		ft_error("[Erreur] Echec d'allocation mémoire.");
	img = &p->win->img;
	kernel->opencl = p->opencl;
	if ((err = build_program(p->opencl, kernel)) != CL_SUCCESS ||
		(err = set_args(p, p->opencl, kernel, img)) != CL_SUCCESS)
	{
		ft_printf("[Error] Could not build kernel program"
				"%<R>  (Error code: %<i>%2d)%<0>\n", err);
		if (kernel->program != NULL)
			clReleaseProgram(kernel->program);
		free(kernel);
		return (NULL);
	}
	p->kernel = kernel;
	return (kernel);
}
