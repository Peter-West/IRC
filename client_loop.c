/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:13:43 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:13:49 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		cmd(t_env *e, char *line)
{
	if (!ft_strncmp("/nick ", line, 6))
		change_nick(e, line);
	else if (!ft_strncmp("/join ", line, 6))
		join_chan(e, line);
	else if (!ft_strncmp("/leave ", line, 6))
		leave_chan(e, line);
	else if (!ft_strncmp("/msg ", line, 4))
		msg_user(e, line);
	else if (!ft_strncmp("/who\n", line, 5))
		return ;
	else if (!ft_strncmp("/connect ", line, 9))
		return ;
	else
		printf("Command unknown\n");
}

int			check_nl(char *str, char **line)
{
	int			i;

	i = 0;
	if (!(*line))
		*line = "";
	*line = ft_strjoin(*line, str);
	while (str[i] != 0)
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void		input_line(t_env *e, int cs)
{
	int		read_ret;

	(void)cs;
	read_ret = 0;
	ft_bzero(e->buf_read, BUF_SIZE);
	ft_bzero(e->buf_write, BUF_SIZE);
	read_ret = read(0, &e->buf_read, BUF_SIZE);
	e->buf_read[read_ret] = '\0';
	if (e->buf_read[0] == '/')
		cmd(e, e->buf_read);
	ft_strcat(e->buf_write, e->buf_read);
}

void		fd_env(t_env *e)
{
	e->maxfd = e->sockfd;
	e->type = FD_CLIENT;
	e->fct_read = input_line;
	e->fct_recv = rcv_msg;
	e->fct_write = send_msg;
	e->nickname = "user";
	e->chan = NULL;
}

void		client_loop(int sockfd)
{
	t_env	e;

	e.sockfd = sockfd;
	fd_env(&e);
	while (1)
	{
		init_fd(&e);
		do_select(&e);
		check_fd(&e);
	}
}
