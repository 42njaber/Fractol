/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 19:13:53 by njaber            #+#    #+#             */
/*   Updated: 2018/04/20 16:14:30 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# define BUFF_SIZE 32

# include "libft.h"
# include <stdio.h>
# include <unistd.h>

typedef struct	s_stock {
	int		fd;
	char	buf[BUFF_SIZE];
	size_t	len;
}				t_stock;

int				get_next_line(const int fd, char **line);

#endif
