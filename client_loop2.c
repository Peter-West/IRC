/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_loop2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:13:58 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:14:00 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			check_fd(t_env *e)
{
	if (FD_ISSET(e->sockfd, &e->readfds))
		e->fct_recv(e, e->sockfd);
	if (FD_ISSET(0, &e->readfds))
		e->fct_read(e, e->sockfd);
	if (FD_ISSET(e->sockfd, &e->writefds))
		e->fct_write(e, e->sockfd);
}

void			do_select(t_env *e)
{
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	e->ret_sel = select(e->sockfd + 1, &e->readfds,
		&e->writefds, NULL, &timeout);
}

void			init_fd(t_env *e)
{
	FD_ZERO(&e->readfds);
	FD_ZERO(&e->writefds);
	if (e->type != FD_FREE)
	{
		FD_SET(e->sockfd, &e->readfds);
		FD_SET(0, &e->readfds);
		if (ft_strlen(e->buf_read) > 0)
			FD_SET(e->sockfd, &e->writefds);
	}
}

void			send_msg(t_env *e, int cs)
{
	int		i;
	char	**split;

	(void)cs;
	i = 0;
	send(e->sockfd, e->buf_write, ft_strlen(e->buf_write), 0);
	if (!ft_strncmp(e->buf_write, "/connect ", 9))
	{
		split = ft_strsplit(e->buf_write, ' ');
		while (split[i])
			i++;
		split[2] = ft_strtrim(split[2]);
		ft_bzero(e->buf_write, BUF_SIZE);
		ft_bzero(e->buf_read, BUF_SIZE);
		connect_serv(i, split);
	}
	ft_bzero(e->buf_write, BUF_SIZE);
}

void			rcv_msg(t_env *e, int cs)
{
	int		ret;

	(void)cs;
	ret = 0;
	ft_bzero(e->buf_read, BUF_SIZE);
	ret = recv(e->sockfd, &e->buf_read, BUF_SIZE, 0);
	if (ret <= 0)
	{
		close(e->sockfd);
		printf("Server connection lost\n");
	}
	else
	{
		printf("ret : %d\n", ret);
		printf("%s\n", e->buf_read);
		ft_bzero(e->buf_read, BUF_SIZE);
		sleep(1);
	}
}
