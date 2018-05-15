/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 20:17:32 by njaber            #+#    #+#             */
/*   Updated: 2018/04/23 02:49:02 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static t_list	**get_file_buf(const int fd)
{
	static t_list	*g_file_buf;
	t_list			**tmp;

	tmp = &g_file_buf;
	while (*tmp != NULL
		&& ((t_stock*)((*tmp)->content))->fd != fd)
		tmp = &((*tmp)->next);
	return (tmp);
}

static int		stock_extra(int fd, char *buf, int len)
{
	t_list	**f_buf;
	t_stock	*stock;

	if ((len <= 0) || (stock = (t_stock*)ft_memalloc(sizeof(t_stock))) == NULL)
	{
		ft_lstdelone(get_file_buf(fd), ft_lstcontdel);
		return ((len > 0) ? 0 : 1);
	}
	if (*(f_buf = get_file_buf(fd)) == NULL)
		if ((*f_buf = ft_lstnew(stock, sizeof(t_stock))) == NULL)
		{
			free(stock);
			return (0);
		}
	stock->fd = fd;
	stock->len = len;
	ft_memcpy(stock->buf, buf, len);
	ft_memcpy((*f_buf)->content, stock, sizeof(t_stock));
	free(stock);
	return (1);
}

static char		*cp_buf(char **line, t_list *buf, size_t len, int fd)
{
	char	*pos;
	size_t	to_cp;

	((to_cp = (size_t)ft_memchr(buf->content, '\n', buf->content_size)) &&
		((to_cp -= (size_t)buf->content) || 1)) || (to_cp += buf->content_size);
	len += (size_t)to_cp;
	if (fd != -1)
		if (!(stock_extra(fd, buf->content + to_cp + 1,
			buf->content_size - to_cp - 1)))
			return (NULL);
	if (buf->next != NULL)
	{
		if (!(pos = cp_buf(line, buf->next, len, -1)))
			return (NULL);
	}
	else
	{
		if (!(*line = ft_strnew(len)))
			return (NULL);
		pos = *line;
	}
	ft_memcpy(pos, buf->content, to_cp);
	return (pos + to_cp);
}

int				get_next_line(const int fd, char **line)
{
	t_list	*f_buf;
	int		rd;
	char	tmp[BUFF_SIZE];

	rd = 0;
	if ((f_buf = *get_file_buf(fd)))
		f_buf = ft_lstnew(((t_stock*)(f_buf->content))->buf,
			((t_stock*)(f_buf->content))->len);
	while (!f_buf || !(ft_memchr(f_buf->content, '\n', f_buf->content_size)))
	{
		if ((rd = read(fd, tmp, BUFF_SIZE)) > 0)
			ft_lstadd(&f_buf, ft_lstnew(tmp, rd));
		if (rd == -1 || (f_buf == NULL && rd == 0))
		{
			ft_lstdel(&f_buf, ft_lstcontdel);
			return (rd);
		}
		if (rd != BUFF_SIZE)
			break ;
	}
	if (!cp_buf(line, f_buf, 0, fd))
		return (-1);
	ft_lstdel(&f_buf, ft_lstcontdel);
	return (1);
}
