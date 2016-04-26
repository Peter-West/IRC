/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_io2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:13:15 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:13:17 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

int			len_buf_msg(char *s)
{
	int		i;

	i = 0;
	while (s[i] != ' ')
		i++;
	return (i);
}

void		client_write(t_env *e, int cs)
{
	int	fd;
	int len;

	fd = -1;
	len = ft_strlen(e->fds[cs].buf_write) - len_buf_msg(e->fds[cs].buf_write);
	if (e->fds[cs].buf_write[0] == '#')
	{
		fd = ret_fd_value(e->fds[cs].buf_write);
		ft_strncpy(e->fds[cs].buf_write,
			&e->fds[cs].buf_write[len_buf_msg(e->fds[cs].buf_write) + 1], len);
	}
	else
		fd = cs;
	send(fd, e->fds[cs].buf_write, ft_strlen(e->fds[cs].buf_write), 0);
	ft_bzero(e->fds[cs].buf_write, BUF_SIZE);
}
