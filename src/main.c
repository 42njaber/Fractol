/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:01:19 by njaber            #+#    #+#             */
/*   Updated: 2018/05/15 23:01:25 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

#define NO_FRACTS 6

void			set_fract_parm(t_ptr *p, int fract)
{
	if (fract < 2)
	{
		p->fract = 0;
		p->locked = 1;
		p->parm = (t_vec2){0.0, 0.0};
	}
	else
		p->fract = 1;
	p->fract_parm = 0x0;
	if (fract == 1)
		p->fract_parm = 0x40;
	if (fract == 3)
		p->fract_parm = 0x4;
	if (fract == 4)
		p->fract_parm = 0x50;
	if (fract == 5)
		p->fract_parm = 0x10;
}

static void		parse_arguments(t_ptr *p, int argc, char **argv)
{
	int		i;
	char	**fracts;

	fracts = (char*[NO_FRACTS]){"MANDLEBROT", "BURNING_SHIP", "JULIA",
			"JULIETTE", "SNOWFLAKE", "TOTEM"};
	if (argc < 2)
		ft_error("Usage: ./fractol <fractal_name>\n");
	if (argc > 2)
		ft_error("[Erreur] Trop d'arguments.\n");
	i = -1;
	while (++i < NO_FRACTS)
		if (ft_strcmp(fracts[i], argv[1]) == 0)
			break ;
	if (i >= NO_FRACTS)
		ft_error("Fractales disponibles:\n - MANDLEBROT\n - BURNING_SHIP\n"
			" - JULIA\n - JULIETTE\n - SNOWFLAKE\n - TOTEM\n");
	set_fract_parm(p, i);
}

int				main(int argc, char **argv)
{
	t_ptr	p;

	(void)argv;
	parse_arguments(&p, argc, argv);
	if ((p.win = (t_win*)ft_memalloc(sizeof(t_win))) == NULL)
		ft_error("[Erreur] Echec d'allocation mémoire.\n");
	init_struct(&p);
	set_hooks(&p);
	mlx_loop(p.win->mlx);
}
