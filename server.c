/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:15:46 by ppellegr          #+#    #+#             */
/*   Updated: 2016/04/26 18:15:48 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_server.h"

void		ft_error(int i, char *s)
{
	printf("ERROR : %s\n", s);
	exit(i);
}

void		ft_check_port(t_env *e, char *port)
{
	int		i;

	i = 0;
	while (port[i] != 0)
	{
		if (!ft_isdigit(port[i]))
		{
			printf("port : digit only\n");
			exit(-1);
		}
		i++;
	}
	e->port = atoi(port);
}

void		init_env(t_env *e)
{
	if ((e->sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		ft_error(1, "Can't open socket");
	e->serv_ad.sin_family = AF_INET;
	e->serv_ad.sin_port = htons(e->port);
	e->serv_ad.sin_addr.s_addr = INADDR_ANY;
	if (bind(e->sockfd,
		(struct sockaddr *)&e->serv_ad, sizeof(e->serv_ad)) < 0)
		ft_error(1, "Can't bind");
	listen(e->sockfd, 5);
	e->cli_len = sizeof(e->cli_ad);
	e->fds[e->sockfd].type = FD_SERV;
	e->fds[e->sockfd].fct_read = srv_accept;
}

void		fd_env(t_env *e)
{
	struct rlimit	rlp;
	int				i;

	getrlimit(RLIMIT_NOFILE, &rlp);
	e->maxfd = rlp.rlim_cur;
	e->fds = (t_fd*)malloc(sizeof(t_fd) * e->maxfd);
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_env	e;

	if (argc == 2)
		ft_check_port(&e, argv[1]);
	else
		ft_error(1, "Usage : serveur <port>");
	fd_env(&e);
	init_env(&e);
	server_loop(&e);
	return (0);
}
